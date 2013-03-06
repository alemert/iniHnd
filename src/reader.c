/******************************************************************************/
/* ini file handler - ini file reader                                         */
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
/* ini memory to config                                                       */
/******************************************************************************/
int ini2cfg( char* iniMem, tIniNode* iniCfg )
{
  int sysRc = 0 ;
  int loop ;

  char *p = iniMem ;

  char *startP ;

  tIniNode *node ;
  


  while( *p != '<' )                  // find start of the opening tag
  {                                   //
    switch( *p )                      //
    {                                 //
      case ' ' : break ;              // ignore blank
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
                                      //
#if(0)                                //
                                      //
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
  node = iniCfg ;                     //
                                      //
#endif                                //
                                      //
  sysRc = setIniTagName( node, startP, p-startP ) ;     
  if( sysRc != 0 )                    //
  {                                   //
    sysRc = 5 ;                       //
    goto _door ;                      //
  }                                   //
                                      //
#if(0)  
  lng = p-startP ;                    //
  tagName = (char*) malloc( lng* sizeof(char) ) ;
  memcpy( tagName, startP, lng ) ;    //
  tagName[lng-1] = '\0' ;             //
                                      //
  while( *p != '>' )
  {
    switch( *p )
    {
      case ' ' : break ;
      default  :
        sysRc = 4 ;
        goto _door ;
    }
    p++ ;
  }
#endif
//printf(">-%c-<\n",*p) ;

//while( 1 ) 

_door :
  return sysRc ;
}

/******************************************************************************/
/* find opening tag    */
/******************************************************************************/
//char* findOpenTag( char* iniMem )
