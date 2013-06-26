/******************************************************************************/
/* ini file handler - ini file reader                                         */
/*                                                                            */
/* functions:                                                                 */
/*   - iniReader                                                              */
/*   - iniHandler                                                             */
/*   - getInclude                                                          */
/*   - freeFileName                                                    */
/*   - uniqueFileName                                                         */
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

#define C_MODULE_INI_HANDLER

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
/* ini File Handler                                                           */
/******************************************************************************/
int iniHandler( const char *mainCfg )
{
  char* mem           = NULL ;
  char* mainMem       = NULL ;
  char* mainMem4Free  ;
  char* inclMem       = NULL ;
  char* inclMem4Free  ;
  char* singleInclMem = NULL ;

  int inclMemLen ;
  int singleInclMemLen ;

  char** inclFiles ;
  char** myInclFile ;
 
  int sysRc = 0 ; 

  // -------------------------------------------------------
  // read main config file
  // -------------------------------------------------------
  sysRc = iniReader( (char*)mainCfg, &mem ) ;  // read main ini file
                                               //
  if( sysRc != 0 ) goto _door ;                // handle error
                                               //
  mainMem = precompile( mem ) ;                // precompile main mem
  mainMem4Free = mainMem ;                     // pointer 3 main mem for free()
  free( mem ) ;                                //
  if( mainMem == NULL )                        // handle error 
  {                                            //
    goto _door ;                               //
    sysRc = 1 ;                                //
  }                                            //
  if( strlen( mainMem ) == 0 )                 // handle main file empty
  {                                            //
    logger( LSTD_INI_EMPTY_MAIN_FILE, mainCfg ) ;
    sysRc = 1 ;                                //
    goto _door ;                               //
  }                                            //
                                               //
  // -------------------------------------------------------
  // get and read include files
  // -------------------------------------------------------
  inclFiles = getInclude( mainMem, 0 ) ;       // recrusive get of all include 
  if( inclFiles == NULL )                      //   files, 0 stands for top 
  {                                            //   recrusive level
    sysRc = 1 ;                                //
    goto _door ;                               // error handle
  }                                            //
                                               //
  mainMem = rmInclude( mainMem ) ;             //
  if( strlen( mainMem ) == 0 )                 // handle main file empty
  {                                            //
    logger( LSTD_INI_EMPTY_MAIN_FILE, mainCfg ) ;
    sysRc = 1 ;                                //
    goto _door ;                               //
  }                                            //
                                               //
  inclFiles = uniqueFileName( inclFiles ) ;    // sort file names to unique
                                               //   keeping logical order
  myInclFile = inclFiles ;                     //
                                               //
  inclMemLen = 0 ;                             //
  while( *myInclFile != NULL )                 // handle all include files
  {                                            //
    sysRc = iniReader( *myInclFile, &mem ) ;   // read include file
    if( sysRc != 0 )                           // 
    {                                          //
      sysRc = 1 ;                              //
      goto _door ;                             //
    }                                          //
    myInclFile++ ;                             //
                                               //
    singleInclMem = precompile( mem ) ;        // read a single include file
    singleInclMem = rmInclude( singleInclMem );//
    free( mem ) ;                              //
    singleInclMemLen = strlen(singleInclMem) ; //
    if( inclMemLen == 0 )                      // handle first single include
    {                                          //
      inclMem      = singleInclMem    ;        //
      inclMem4Free = singleInclMem    ;        //
      inclMemLen   = singleInclMemLen ;        //
      continue ;                               //
    }                                          //
                                               // concanated single file to
    inclMem = (char*) realloc( inclMem,        //  a major include memory
                               inclMemLen*sizeof(char*)) ;
    inclMem4Free = inclMem ;                   //
    memcpy( (inclMem+inclMemLen)   ,           // 
            singleInclMem          ,           // 
            singleInclMemLen     ) ;           //
    inclMemLen += singleInclMemLen ;           //
    free( singleInclMem ) ;                    //
  }                                            //
                                               //
  // -------------------------------------------------------
  // conert stream to tree for include
  // -------------------------------------------------------
  if( inclMem != NULL )                        // if no include files 
  {                                            // or all include files empty
    inclIniAnchor = tag2node( &inclMem ) ;     //
    free( inclMem4Free ) ;                     //
    if( inclIniAnchor == NULL )                //
    {                                          //
      sysRc = 1 ;                              //
      goto _door ;                             //
    }                                          //
  }                                            //

  // -------------------------------------------------------
  // conert stream to tree for include
  // -------------------------------------------------------
  mainIniAnchor = tag2node( &mainMem ) ;
  if( mainIniAnchor == NULL ) 
  {
    sysRc = 1 ;
    goto _door ;
  }
  free( mainMem4Free ) ;

  sysRc = 0 ;     

  _door :

  return sysRc ;
}

/******************************************************************************/
/* get config Include                                                         */
/*                                                                            */
/*  get all include files from main config memory                             */
/*                                                                            */
/*  RC:                                                                       */
/*    ok - array (char**) of all include files in logical sort                */
/*                                                                            */
/******************************************************************************/
char** getInclude( char *mem, int inclLevel )
{
  #define MAX_FILE_NAME   512

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
  if( openIncl == NULL ) goto _door ;     // include not found, return from
                                          //  function
  lng = ( closeIncl - openIncl - strlen( OPEN_INCL )  ) ;
  fileName[fileNameCnt] = (char*) malloc( sizeof(char) * (lng+1) ) ;
  memcpy( fileName[fileNameCnt], ( openIncl + strlen( OPEN_INCL ) ), lng ) ;
  fileName[fileNameCnt][lng] = '\0' ;     //
  fileName[fileNameCnt+1] = NULL ;        //
                                          // 
  lng += strlen( OPEN_INCL ) + 1 ;        //
  p = mem ;                               //
  if( lng > 0 )                           //
  {                                       //
    while( 1 )                            //
    {                                     //
      *p = *(p+lng) ;                     //
      if( *p == '\0' ) break ;            //
      p++ ;                               //
    }                                     //
  }                                       //
                                          //
  if( iniReader( fileName[fileNameCnt], &inclMem)!=0 ) 
  {                                       //
    fileName = NULL ;                     //
    goto _door ;                          //
  }                                       //
                                          //
  shrtMem = precompile( inclMem ) ;       // recrusive
  free( inclMem ) ;                       //
  subFileName = getInclude( shrtMem, inclLevel + 1 ) ;
  free( shrtMem ) ;                       //
  if( subFileName == NULL )               //
  {                                       //
    freeFileName( fileName ) ;            //
    fileName = NULL ;                     //
    goto _door ;                          //
  }                                       //
                                          //
  i = 0 ;                                 //
  while( subFileName[i] != NULL )         //
  {                                       //
    if( fileNameCnt == MAX_FILE_NAME )    //
    {                                     //
      logger( LSTD_INI_MAX_INCLUDE_FILES, MAX_FILE_NAME ) ;
    }                                     //
    fileNameCnt++ ;                       //
    fileName[fileNameCnt]   = subFileName[i] ;  
    fileName[fileNameCnt+1] = NULL ;      //
    i++ ;                                 //
  }                                       //
                                          //
  if( strlen( mem ) == 0 ) goto _door ;   //
                                          // serial
  subFileName = getInclude( mem, inclLevel ) ;
  if( subFileName == NULL )               //
  {                                       //
    freeFileName( fileName ) ;            //
    fileName = NULL ;                     //
    goto _door ;                          //
  }                                       //
                                          //
  i = 0 ;                                 //
  while( subFileName[i] != NULL )         //
  {                                       //
    fileNameCnt++ ;                       //
    fileName[fileNameCnt] = subFileName[i] ;  
    fileName[fileNameCnt+1] = NULL ;      //
    i++ ;                                 //
  }                                       //
                                          //
  if( strlen( mem ) == 0 ) goto _door ;   //
                                          //
  _door :

  return fileName ;   
}

/******************************************************************************/
/* free file name array                                                       */
/******************************************************************************/
void freeFileName( char** _fileName )
{
  char **fileName ;

  if( _fileName == NULL ) goto _door ;

  fileName = _fileName ;

  while( *fileName != NULL )
  {
    free( *fileName ) ;
    *fileName = NULL ;
    fileName++ ;
  }

  _fileName = NULL ;

  _door :

  return ;
}

/******************************************************************************/
/* unique file name                                                           */
/******************************************************************************/
char** uniqueFileName( char** _fileName )
{
  char  **p ;
  char  **q ;

  char **fileName = _fileName ;

  if( *fileName     == NULL ) goto _door ;
  if( *(fileName+1) == NULL ) goto _door ;

  while( *fileName != NULL )
  {
    p = fileName + 1 ;
    while(  *p != NULL )
    {
      if( strcmp( *fileName, *p ) == 0 )
      {
        q = p ;
        free( *p ) ;
        while( *q != NULL )
        {
          *q = *(q + 1) ; 
          q++ ;
        }
      }
      p++ ;
    }
    fileName++ ;
  }
 
  _door :
  
  return _fileName ;
}

