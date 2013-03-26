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
        logger( LSTD_INI_CLOSE_TAG_ERROR, tag ) ; //
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
        logger( LSTD_INI_CLOSE_TAG_ERROR, tag ) ; //
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
/* convert memory to cfg                                                      */
/******************************************************************************/
tIniNode* ini2cfg( char* iniMem, int *rc )
{
  int sysRc = 0 ;
  int loop ;

  char *startSubMem ;
  char *endSubMem ;

  tIniNode *iniCfg    = initIniNode() ;
  tIniNode *anchorCfg = iniCfg ;

  char *memP = iniMem ;

  loop = 1 ;
  while( loop )
  {
    switch( *memP )
    {
      // ---------------------------------------------------
      // ignore white spaces
      // ---------------------------------------------------
      case ' '  :           //
      {                     //
        break ;             //
      }                     //
      // ---------------------------------------------------
      // eof found (ok)
      // ---------------------------------------------------
      case '\0' :           // 
      {                     //
        loop = 0 ;          // break out of the loop
        break ;             //
      }                     //
      // ---------------------------------------------------
      // tag found
      // ---------------------------------------------------
      case '<'  :                                    // tag found, find and
      {                                              //  set it's name
        if( iniCfg->tag != NULL )                    //
        {                                            // more then one tag
          iniCfg->nextNode = initIniNode() ;         //  on same level
          iniCfg = iniCfg->nextNode ;                //
        }                                            //
        startSubMem = iniHandleOpenTag( memP   ,     //
                                        iniCfg ,     //
                                        &sysRc );    //
        if( sysRc != 0 )                             // some error occured
        {                                            //   check function source
          logger( LSTD_INI_SYNTAX_ERROR ,            //   for error reason
                  iniMem                ) ;          // i.g ini syntax err
          goto _door ;                               //   (not an oppening tag)
        }                                            //
        if( startSubMem == NULL )                    // if  sysRc==0
        {                                            // and startSubMem == NULL
          loop = 0 ;                                 // eof reached (ok)
          break ;                                    //
        }                                            //
                                                     // search for close tag
        endSubMem = iniHandleCloseTag( startSubMem,  //  belonging to open tag
                                       iniCfg->tag,  // some error occured
                                       &sysRc     ); //  check function source
        if( sysRc != 0 )                             //  for error reason i.g.
        {                                            //  ini syntax error: not 
          logger( LSTD_INI_SYNTAX_ERROR, iniMem );   //   a close tag, close 
          goto _door ;                               //   name not existing, not
        }                                            //   fiting open tag name
                                                     //
        *endSubMem = '\0' ;                          //
        iniCfg->childNode = ini2cfg( endSubMem ,     //
                                     &sysRc   );     //
        if( iniCfg->childNode == NULL  )             //
        {                                            //
           logger( LSTD_INI_SYNTAX_ERROR, iniMem );  //
           goto _door ;                              //
        }                                           //
        if( iniCfg->childNode->tag == NULL )        //
        {                                           //
          if( iniCfg->childNode->value    ==NULL && //
              iniCfg->childNode->nextNode ==NULL && //
              iniCfg->childNode->childNode==NULL  ) //
          {                                         //
            free( iniCfg->childNode ) ;             //
            iniCfg->childNode = NULL ;              //
          }                                         //
          else                                      //
          {                                         //
            logger(LSTD_INI_SYNTAX_ERROR,iniMem);   //
            goto _door ;                            //
          }                                         //
        }                                           //
        memP=startSubMem ;
        *endSubMem = '<' ;                          // start of close tag found
      }                                              // no break, continue with
                                                     //  values (default:)
                                                     //
      // ---------------------------------------------------
      // value
      // ---------------------------------------------------
      default :                                      //
      {                                              //
        startSubMem = iniHandleValues( startSubMem, endSubMem, iniCfg, &sysRc );
        if( sysRc > 0  )                             //
        {                                            //
          logger( LSTD_INI_SYNTAX_ERROR, iniMem );   //
          goto _door ;                               //
        }                                            //
      }                                              //
    }                                                //
                                                     //
    memP++ ;                                         //
    if( memP == endSubMem )                          // 
    {                                                // endSubMem is pointing
      for( memP=endSubMem; *memP != '>'; memP++ );   //  to '<' in </name>, 
    }                                                //  move memP to '>'
  }                                                  //


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
        logger( LSTD_INI_OPEN_TAG_ERROR, iniMem ) ;
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
        logger( LSTD_INI_EARLY_EOF ); //
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
      case '<'   :                    // < or / are error at this stage
      case '/'   :                    //
      {                               //
        sysRc = 3 ;                   //
        logger( LSTD_INI_WRONG_CHAR, *p, iniMem ); 
        goto _door ;                  //
      }                               //
      case '\0'  :                    // early eof
      {                               //
        sysRc = 3 ;                   //
        logger( LSTD_INI_EARLY_EOF ); //
        goto _door ;                  //
      }                               //
      default : break ;               //
    }                                 //
    p++ ;                             //
  }                                   //
  p-- ;                               //
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
      {      //
        sysRc = 6 ;                   //
        logger( LSTD_INI_MISSING_CHAR, *p, iniMem ) ;
        goto _door ;                  //
      }      //
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
/*      5 if alloc error                                                      */
/*      6 if creating value node failed                                       */
/*      7 if adding value to config list failed                               */
/******************************************************************************/
char* iniHandleValues( char     *startValMem, 
                       char     *endValMem  ,
                       tIniNode *iniCfg     , 
                       int      *rc         ) 
{
  int sysRc = 0 ;
  int lng   ;              // yet another length buffer
                           //
  char *p = startValMem ;  // yet another pointer
                           //
  char *keyStart = NULL ;  // pointer to the first letter of the key
  char *keyEnd   = NULL ;  // pointer to the last letter of the key
  char *valStart = NULL ;  // pointer to the first letter of the key
  char *valEnd   = NULL ;  // pointer to the last letter of the key
  char *pCheck   ;         // for checking if value is int or str
                           //
  char *key    ;           // pointer to the key   (will be allocated)
  char *valStr ;           // pointer to the value (will be allocated)
  int   valInt ;           // intiger value 
                           //
  tIniVal *iniVal = NULL ; // pointer to key/val node
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
        logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
        p = NULL ;            //
        sysRc = 1 ;           //
        goto _door ;          //
      }                       //
      case '\0' :             // unexpected end of file (error)
      {                       //
        logger( LSTD_INI_EARLY_EOF ); //
        p = NULL ;            //
        sysRc = 2 ;           //
        goto _door ;          //
      }                       //
      case '=' :              // early = found (error)
      {                       //
        logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
        p = NULL ;            //
        sysRc = 3 ;           //
        goto _door ;          //
      }                       //
      default :               // start of text found (ok break loop)
      {                       //
        keyStart = p ;        //
        break ;               //
      }                       //
    }                         //
    if( keyStart )            // break loop, start of text found 
      break ;                 //
    p++ ;                     //
  }                           //
                              //
  if( keyStart )              // handle key  (key = value)
  {                           //
    while( 1 )                //
    {                         //
      switch( *p )            //
      {                       //
        case ' ' :            // blank after key found (key = value)
        case '=' :            // equal after key found (key= value)
        {                     //  end of key text found break loop
          keyEnd = p-1 ;      //
          break ;             //
        }                     //
        case '>' :            // unexpected start or end of tag (error)
        case '<' :            //
        {                     //
          logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
          sysRc = 1 ;         //
          p = NULL ;          //
          goto _door ;        //
        }                     //
        case '\0' :           // unexpected end of file
        {                     //
          logger( LSTD_INI_EARLY_EOF ) ;
          p = NULL ;          //
          sysRc = 2 ;         //
          goto _door ;        //
        }                     //
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
  //  case '=' :              // this shuold not occure
        break  ;              //
      case '>' :              // unexpected start or end of tag (error)
      case '<' :              //
      {                       //
        logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
        sysRc = 1 ;           //
        p = NULL ;            //
        goto _door ;          //
      }                       //
      case '\0' :             // unexpected end of file
      {                       //
        logger( LSTD_INI_EARLY_EOF ) ;
        p = NULL ;            //
        sysRc = 2 ;           //
        goto _door ;          //
      }                       //
      default :               // some letter (somthing but eof, <, >, blank, =
      {                       //
        logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
        sysRc = 4 ;           //
        p = NULL ;            //
        goto _door ;          //
      }                       //
    }                         //
    p++ ;                     //
  }                           //
  p++ ;                       //
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
        logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
        sysRc = 1 ;           //
        p = NULL ;            //
        goto _door ;          //
      }                       //
      case '=' :              //
      {                       //
        logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
        p = NULL ;            //
        sysRc = 3 ;           //
        goto _door ;          //
      }                       //
      case '\0' :             // unexpected end of file
      {                       //
        logger( LSTD_INI_EARLY_EOF ) ;
        p = NULL ;            //
        sysRc = 2 ;           //
        goto _door ;          //
      }                       //
      default :               //
      {                       //
        valStart = p ;        //
        break ;               //
      }                       //
    }                         //
    if( valStart )            //
      break ;                 //
    p++ ;                     //
  }                           //
                              //
  while( 1 )                  // find end of value
  {                           //
    switch( *p )              //
    {                         //
      case ' ' :              // search for blank or start of next tag
      case '<' :              //
      case '\0' :             // end of file
      {                       //
        valEnd = p-1 ;        //
        break ;               //
      }                       //
  //  case '\0' :             // early end of file
  //  {                       //
  //    p = NULL ;            //
  //    sysRc = 2 ;           //
  //    goto _door ;          //
  //  }                       //
      case '=' :              // late =
      {                       //
        logger( LSTD_INI_WRONG_CHAR, *p, startValMem ) ;
        p = NULL ;            //
        sysRc = 3 ;           //
        goto _door ;          //
      }                       //
      default :               //
        break ;               //
    }                         //
    if( valEnd )              //
      break ;                 //
    p++ ;                     //
  }                           //
                              //
  // -------------------------------------------------------
  // setup value node
  // -------------------------------------------------------
  lng = keyEnd - keyStart + 1 ;                   // the length of the key
  key = (char*) malloc( (lng+1)*sizeof(char) ) ;  // alloc memory for the key
  if( key == NULL )                               // allocation failed
  {                                               //
    logger( LSTD_MEM_ALLOC_ERROR ) ;              //
    sysRc = 5 ;                                   //
    goto _door ;                                  //
  }                                               //
  memcpy( key, keyStart, lng ) ;                  // copy to allocated memory
  key[lng] = '\0' ;                               // set end of the string
                                                  //
  valInt = (int) strtol( valStart, &pCheck, 10 ); // check if it is intiger
  if( pCheck == keyEnd )                          // handle initiger value
  {                                               //
    iniVal = createIntValue( key, valInt ) ;      //
  }                                               //
  else                                            // handle string
  {                                               //
    lng = valEnd - valStart +1 ;                  //
    valStr=(char*)malloc( (lng+1)*sizeof(char) ); //
    if( valStr == NULL )                          //
    {                                             //
      logger( LSTD_MEM_ALLOC_ERROR ) ;            //
      sysRc = 5 ;                                 //
      goto _door ;                                //
    }                                             //
    memcpy( valStr, valStart, lng ) ;             //
    valStr[lng] = '\0' ;                          //
    iniVal = createStrValue( key, valStr ) ;      //
  }                                               //

  if( iniVal == NULL )
  {
    sysRc = 6 ;
    goto _door ;
  }  

  sysRc = addValueNode( iniCfg, iniVal ) ;
  if( sysRc != 0 )
  {
    sysRc = 7 ;
    goto _door ;
  }

_door :    
  *rc = sysRc ;
  return p ;
}
