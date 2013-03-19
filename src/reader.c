/******************************************************************************/
/* ini file handler - ini file reader                                         */
/*                                                                            */
/* functions:                                                                 */
/*   - iniReader                                                              */
/*   - ini2cfg                                                                */
/*   - iniHandleOpenTag                                                       */
/*   - iniHandleCloseTag                                                      */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <initypes.h>
#include <inihnd.h>

#include <msgcat/lgstd.h>
#include <ctl.h>

#include <genlib.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*  ini file reader                                                           */
/*                                                                            */
/*  read ini file in memomry as one line                                      */
/*  return code:                                                              */
/*    ok:     0                                                               */
/*    error:  i.g. errno                                                      */
/*            if error occures *_iniMem = NULL                                */
/******************************************************************************/
int iniReader( const char* fileName, char **_iniMem )
{
  int sysRc = 0 ;
  long memSize ;
  int  realSize ;
  FILE* ini ;

  char *p ;

  char *iniMem = NULL ;
  errno = 0 ;
                                                 //
  if( (ini = fopen( fileName, "r" ) ) == NULL )  // open ini file
  {                                              //  & handle error
    logger( LSTD_OPEN_FILE_FAILED, fileName ) ;  //
    sysRc = errno ;                              //
    goto _door ;                                 //
  }                                              //
                                                 //
  memSize = fileSize( fileName ) ;               // get the size of the 
  if( memSize < 0 )                              //   ini-file
  {                                              // handle error
    logger( LSTD_GET_FILE_SIZE, fileName ) ;     //
    sysRc = -memSize ;                           // if memSize < 0 then 
    goto _door ;                                 //   errno = -memSize 
  }                                              //
  memSize++ ;                                    // increase memSize for '\0'
                                                 //
  iniMem = (char*) malloc(memSize*sizeof(char)); // alloc memory in size 
  if( iniMem == NULL )                           //   of the ini-file
  {                                              //  & handle alloc error
    logger( LSTD_MEM_ALLOC_ERROR ) ;             //
    sysRc = errno ;                              //
    goto _door ;                                 //
  }                                              //
                                                 //
  realSize = fread( iniMem, sizeof(char), memSize-1, ini ) ;
  if( memSize - realSize != 1 )                  // read whole file in one step
  {                                              //  & handle error
    logger( LSTD_ERR_READING_FILE, fileName ) ;  //
    sysRc = 1 ;                                  //
    goto _door ;                                 //
  }                                              //
  *(iniMem+realSize) = '\0' ;                    // set the end of ini file flag
                                                 //
  for( p=iniMem; *p!='\0'; p++  )                // replace '\n' with blanks
  {                                              //
    if( *p == '\n' ) *p = ' ' ;                  //
  }                                              //

_door :
  if( ini != NULL ) fclose( ini ) ;

  *_iniMem = iniMem ;

  return sysRc ;
}

/******************************************************************************/
/* find close tag                  */
/******************************************************************************/
char* iniHandleCloseTag( char *mem,  const char* tag, int *rc )
{
  int sysRc = 0 ;    // ok return code
  char *endTag = NULL ;

  int loop = 0 ;
  char *endP ;
  char *p = mem ;

  while( *p != '<' )                              // find start of tag (open 
  {                                               //   or close)
    switch( *p )                                  //
    {                                             //
      case '\0' :                                 // early eof
        sysRc = 1 ;                               // 
        goto _door ;                              //
      default  :                                  //
        break ;                                   //
    }                                             //
    p++ ;                                         //
  }                                               //
  endP = p ;                                      // set pointer end of values 
  p++ ;                                           //   to the start of close tag
                                                  // 
  loop = 0 ;                                      // check if it is a close tag
  while( !loop )                                  //
  {                                               //
    switch( *p )                                  // 
    {                                             // close tag id
      case '/' :                                  //
        loop = 1 ;                                //
        break ;                                   //
      case ' ' : break ;                          //
      case '\0' :                                 // early eof
        sysRc = 2 ;                               //
        goto _door ;                              //
      default :                                   // if sub open tag found, call
        endP = iniHandleCloseTag(p,tag,&sysRc);   //   this function  recrusivly
        if( sysRc != 0 )                          // handle error 
        {                                         //   (i.g. to early eof) 
          sysRc = 3  ;                            //
          goto _door ;                            //
        }                                         //
        loop = 1 ;                                //
    }                                             //
    p++ ;                                         //
  }                                               //
                                                  //
  if( memcmp(p,tag,sizeof(char)*strlen(tag))!=0)  // compare open and close 
  {                                               //   tag name 
    endP = iniHandleCloseTag( p, tag, &sysRc );   // if open and close name are
    if( sysRc != 0 )                              //   not the same, go to the
    {                                             //   next close tag recrusivly
      sysRc = 4  ;                                //
      goto _door ;                                //
    }                                             //
  }                                               //
                                                  //
  endTag = endP ;                                 // set rc pointer to endP
                                                  //
_door :
  *rc = sysRc ;
  return endTag ;
}

/******************************************************************************/
/* convert memory to cfg                        */
/******************************************************************************/
tIniNode* ini2cfg( char* iniMem, int *rc )
{
  int sysRc = 0 ;
  char *startSubMem ;
  char *endSubMem ;

  tIniNode *iniCfg    = initIniNode() ;
  tIniNode *anchorCfg = iniCfg ;

  char *memP = iniMem ;

  while(1)
  {
    startSubMem = iniHandleOpenTag( memP, iniCfg, &sysRc ) ;
    if( sysRc != 0 )           // handle error
    {                          //
      goto _door ;             //
    }                          //
    if( startSubMem == NULL )  // sysRc == 0; startSubMem == NULL
    {                          // ok -> eof reached
      break ;                  //
    }                          //
                               // 
    endSubMem = iniHandleCloseTag( startSubMem, iniCfg->tag, &sysRc ) ;
    if( sysRc != 0 )           // handle error
    {                          //
      goto _door ;             //
    }                          //

    startSubMem = iniHandleValues( startSubMem, endSubMem, iniCfg, &sysRc ) ;
    if( sysRc != 0 )
    {
      goto _door ;
    }

    for( memP=endSubMem; *memP != '>'; memP++ ) ;
  }


_door :
  *rc = sysRc ;
  return anchorCfg ;  
}

/******************************************************************************/
/* find open tag in ini file                                                  */
/******************************************************************************/
char* iniHandleOpenTag( char* iniMem, tIniNode* iniCfg, int *rc )
{
  int sysRc = 0 ;
  int loop ;

  char *p    = iniMem ;
  char *endP = NULL ;

  char *startP ;

  tIniNode *node ;

  while( *p != '<' )                  // find start of the opening tag
  {                                   //
    switch( *p )                      //
    {                                 //
      case ' ' : break ;              // ignore blank
      case '\0' :                     // eof file found, stop processing
        sysRc = 0 ;                   //
        goto _door ;                  //
      default  :                      //
        sysRc = 1 ;                   // anything but '<' or ' ' is an error
        goto _door ;                  //
    }                                 //
    p++ ;                             //
  }                                   //
  p++ ;                               //
                                      //
  loop = 1 ;                          //
  while( loop )                       // 
  {                                   // 
    switch( *p )                      //
    {                                 // find char not eq to
      case ' '  : break ;             // blank 
      case '<'  :                     // '<'
      case '>'  :                     // '>'
      case '/'  :                     // '/'
      case '\0' :                     // end of memory
        sysRc = 2  ;                  //
        goto _door ;                  //
      default :                       //
        loop = 0 ;                    //
    }                                 //
    p++ ;                             //
  }                                   //
  p-- ;                               //
  startP = p ;                        //
                                      //
  loop = 1 ;                          //
  while( loop )                       // search for tag name
  {                                   //
    switch( *p )                      //
    {                                 // stop if blank
      case  ' '  :                    //
      case '>'   :                    // 
        loop = 0 ;                    //
        break    ;                    //
      case '<'   :                    // some chars -> error
      case '/'   :                    //
      case '\0'  :                    //
        sysRc = 3 ;                   //
        goto _door ;                  //
      default : break ;               //
    }                                 //
    p++ ;                             //
  }                                   //
  p-- ;      //
                                      //
#if(0)                                // parent of this node is given as 
                                      //  function argument
  node = initIniNode( ) ;             //
  if( node == NULL )                  //
  {                                   //
    sysRc = 4 ;                       //
    goto _door ;                      //
  }                                   //
  iniCfg->nextNode = node ;           //
                                      //
#else                                 //
                                      //
  node = iniCfg ;                     // node is given as a function argument
                                      //
#endif                                //
                                      //
  sysRc = setIniTagName( node, startP, p-startP+1 ) ;     
  if( sysRc != 0 )                    //
  {                                   //
    sysRc = 5 ;                       //
    goto _door ;                      //
  }                                   //
                                      //
  while( *p != '>' )                  // find end of opening tag
  {                                   //
    switch( *p )                      //
    {                                 //
      case ' ' : break ;              //
      default  :                      //
        sysRc = 6 ;                   //
        goto _door ;                  //
    }                                 //
    p++ ;                             //
  }                                   //
                                      //
 endP = p+1 ;

_door :
  *rc = sysRc ;
  return endP ;
}

/******************************************************************************/
/*   handle ini node values                                                   */
/*                                                                            */
/*   rc:                                                                      */
/*    ok rc                                                                   */
/*     -1 if start of next tag found '<'                                      */
/*      0 if value found and added to iniCfg                                  */
/*    error rc                                                                */
/*      1 if end or start of some tag found '>','<'                           */
/*      2 if unexpected end of file found                                     */
/*      3 if unexpected '='                                                   */
/*      4 if unexpected char                                                  */
/******************************************************************************/
char* iniHandleValues( char     *startValMem, 
                       char     *endValMem  ,
                       tIniNode *iniCfg     , 
                       int      *rc         ) 
{
  int sysRc = 0 ;

  char *p = startValMem ;

  char *keyStart = NULL ;
  char *keyEnd   = NULL ;
  char *valStart = NULL ;
  char *valEnd   = NULL ;
                              //
  while(1)                    // loop until first non-blank
  {                           //
    switch( *p )              //
    {                         //
      case ' ' : break ;      // ignore blank
      case '<' :              // start of some tag found (ok)
      {                       //
        sysRc = -1 ;          //
        goto _door ;          //
      }                       //
      case '>' :              // unexpected end of tag found (error)
      {                       //
        p = NULL ;            //
        sysRc = 1 ;           //
        goto _door ;          //
      }                       //
      case '\0' :             // unexpected end of file (error)
      {                       //
        p = NULL ;            //
        sysRc = 2 ;           //
        goto _door ;          //
      }                       //
      case '=' :              // early = found (error)
      {                       //
        p = NULL ;            //
        sysRc = 3 ;           //
        goto _door ;          //
      }                       //
      default :               // start of text found (ok break loop)
        keyStart = p ;        //
        break ;               //
    }                         //
    if( keyStart )            // break loop, start of text found 
      break ;                 //
    p++ ;                     //
  }                           //
                              //
#if(0)
  if( keyStart )              // handle key  (key = value)
  {                           //
    while( 1 )                //
    {                         //
      switch( *p )            //
      {                       //
        case ' ' :            // blank after key found key = value
        case '=' :            // equal afte ke found   key= value
        {                     //  end of key text found break loop
          keyEnd = p-1 ;      //
          break ;             //
        }                     //
        case '>' :            // unexpected start or end of tag (error)
        case '<' :            //
        {                     //
          sysRc = 1 ;         //
          p = NULL ;          //
          goto _door ;        //
        }                     //
        case '\0' :           // unexpected end of file
          p = NULL ;          //
          sysRc = 2 ;         //
          goto _door ;        //
        default :             // some letter
          break ;             //
      }                       //
      if( keyEnd )            // end of key text found, break the loop
        break ;               //
      p++ ;                   //
    }                         //
  }                           //
                              //
  while( *p != '=' )          // search for '=' in key = value
  {                           //
    switch( *p )              //
    {                         //
      case ' ' :              //
      case '=' :              //
        break  ;              //
      case '>' :            // unexpected start or end of tag (error)
      case '<' :            //
      {                       //
        sysRc = 1 ;           //
        p = NULL ;            //
        goto _door ;          //
      }                       //
      case '\0' :             // unexpected end of file
      {                       //
        p = NULL ;            //
        sysRc = 2 ;           //
        goto _door ;          //
      }                       //
      default :               // some letter (somthing but eof, <, >, blank, =
      {                       //
        sysRc = 4 ;           //
        p = NULL ;            //
        goto _door ;          //
      }                       //
    }                         //
    p++ ;                     //
  }                           //
                              //
  while( 1 )                  // find start of value
  {                           //
    switch( *p )              //
    {                         //
      case ' ' :              //
        break  ;              //
      case '<' :              //
      case '>' :              //
      {                       //
        sysRc = 1 ;           //
        p = NULL ;            //
        goto _door ;          //
      }                       //
      case '\0' :             // unexpected end of file
      {                       //
        p = NULL ;            //
        sysRc = 2 ;           //
        goto _door ;          //
      }                       //
      default :               //
        valStart = p ;        //
        break ;               //
    }                         //
    p++ ;                     //
  }                           //
                              //
  while( 1 )                  // find end of value
  {                           //
    switch( *p )              //
    {                         //
      case ' ' :              // search for blank or start of next tag
      case '<' :              //
      {                       //
        valEnd = p-1 ;        //
        break ;               //
      }                       //
      case '\0' :             // early end of file
      {                       //
        p = NULL ;            //
        sysRc = 2 ;           //
        goto _door ;          //
      }                       //
      case '=' :              // late =
      {                       //
        p = NULL ;            //
        sysRc = 3 ;           //
        goto _door ;          //
      }                       //
      default :               //
        break ;               //
    }                         //
    p++ ;                     //
  }                           //
#endif
                              //
_door :    
  *rc = sysRc ;
  return p ;
}
