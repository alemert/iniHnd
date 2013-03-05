/******************************************************************************/
/* ini file handler - ini file reader            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
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
  memSize++ ;            // increase memSize for '\0'
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
  *(iniMem+memSize) = '\0' ;                     // set the end of ini file flag
                                                 //
  for( p=iniMem; *p!='\0'; p++ )                // replace '\n' with blanks
  {                                              //
    if( *p == '\n' ) *p = ' ' ;                  //
  }                                              //

_door :
  if( ini != NULL ) fclose( ini ) ;

  *_iniMem = iniMem ;

  return sysRc ;
}
