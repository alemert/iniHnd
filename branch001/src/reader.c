/******************************************************************************/
/* ini file handler - ini file reader                                         */
/*                                                                            */
/* functions:                                                                 */
/*   - iniReader                                                              */
/*   - iniHandler            */
/*   - getInclude        */
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
int iniReader( char* fileName, char **_iniMem )
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
/* ini File Handler      */
/******************************************************************************/
int iniHandler( const char *mainCfg )
{
  char* mem     = NULL ;
  char* mainMem = NULL ;
 
  int sysRc = 0 ; 

  sysRc = iniReader( (char*) mainCfg, &mem ) ;

  if( sysRc != 0 ) goto _door ;

  mainMem = precompile( mem ) ;
  if( mainMem == NULL )
  {
    goto _door ; 
    sysRc = 1 ;
  }
  if( strlen( mainMem ) == 0 )
  {
    logger( LSTD_INI_EMPTY_MAIN_FILE, mainCfg ) ;
    sysRc = 1 ;
    goto _door ; 
  }

  sysRc = 0 ;     

  _door :

  return sysRc ;
}

/******************************************************************************/
/* get config Include      */
/******************************************************************************/
char** getInclude( char *mem, int inclLevel )
{
  #define OPEN_INCL "<!include="
  #define MAX_FILE_NAME   128 

//char *rcMem = NULL ;
  char *inclMem ;
  char *shrtMem ;
  char *p      = mem ;

  char *openIncl = NULL ;
  char *closeIncl ;

  char  **fileName ;
  char **subFileName ;

  int lng ;
  int fileNameCnt = 0 ;
  int i = 0 ;

  if( inclLevel > 20 )
  { 
    logger( LSTD_INI_MAX_INCLUDE_LEVEL, inclLevel ) ;
    fileName = NULL ;
    goto _door ;
  }

  fileName    = (char**) malloc( sizeof(char*) * MAX_FILE_NAME )  ;
  fileName[0] = NULL ;

  while( *p != '\0' )                     // search in whole memory
  {                                       //   for inlcude start
    if( memcmp( p, OPEN_INCL, strlen(OPEN_INCL) ) == 0 )
    {                                     // if include open found
      openIncl = p ;                      //
      p+= strlen( OPEN_INCL ) + 1 ;       //
      continue ;                          //
    }                                     //
    if( *p == '>' )                       // if include close found
    {                                     //
      closeIncl = p ;                     //
      p++ ;                               //
      break ;                             //
    }                                     //
    p++ ;                                 //
  }                                       //
                                          //
  if( openIncl != NULL )                  // include found
  {                                       // get file name
    lng = ( closeIncl - openIncl - strlen( OPEN_INCL )  ) ;
    fileName[fileNameCnt] = (char*) malloc( sizeof(char) * (lng+1) ) ;
    memcpy( fileName[fileNameCnt], ( openIncl + strlen( OPEN_INCL ) ), lng ) ;
    fileName[fileNameCnt][lng] = '\0' ;   //
    fileName[fileNameCnt+1] = NULL ;      //
                                          // 
    lng += strlen( OPEN_INCL ) + 1 ;      //
    p = mem ;                             //
    if( lng > 0 )                         //
    {                                     //
      while( 1 )                          //
      {                                   //
        *p = *(p+lng) ;                   //
        if( *p == '\0' ) break ;          //
        p++ ;                             //
      }                                   //
    }                                     //
                                          //
    if( iniReader( fileName[fileNameCnt], &inclMem)!=0 ) 
    {                                     //
      fileName = NULL ;        //
      goto _door ;          //
    }                              //
                              //
    shrtMem = precompile( inclMem ) ;     //
    subFileName = getInclude( shrtMem, inclLevel + 1 ) ;
    if( subFileName == NULL )      //
    {                              //
      fileName = NULL ;        //
    // free fehlt
      goto _door ;                //
    }                            //
                                      //
    i = 0 ;                          //
    while( subFileName[i] != NULL )       //
    {                                  //
      fileNameCnt++ ;                  //
      fileName[fileNameCnt] = subFileName[i] ;      //
      i++ ;                          //
    }                                    //
  }                                       //
                                          // 
  if( strlen( mem ) == 0 )            //
  {                                       //
    goto _door ;                          //
  }                                       //
                                          //
  _door :

  return fileName ;   
}
