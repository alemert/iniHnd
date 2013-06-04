/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  reader.c                                                                  */
/*                                                                            */
/* testing functions :                                                        */
/*   - iniReader                                                              */
/*   - iniHandleOpenTag                                                       */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// std
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <tutl.h>

#include <initypes.h>
#include <inihnd.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_precomp_000.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  doPointTest( "general test"    , \
                RC_NOT_NULL      , \
                precompile       , \
               "  key1 = value1 <!-- hello wrold --> key2=value2  " ) ;
  
  if( strcmp( (char*)gRcVoidPointer, "key1=\"value1\"key2=\"value2\"" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, precompile ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, ini2cfg ) ;
#endif

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  doPointTest( "general test"   , \
                RC_NOT_NULL     , \
                precompile      , \
               "  key1= \"value1\" key2=\"value 2\"  " ) ;
  
  if( strcmp( (char*)gRcVoidPointer, "key1=\"value1\"key2=\"value 2\"" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, precompile ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, ini2cfg ) ;
#endif

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  doPointTest( "eof test"       , \
                RC_NOT_NULL     , \
                precompile      , \
               "  key1= \"value1\" key2=value2" );
  
  if( strcmp( (char*)gRcVoidPointer, "key1=\"value1\"key2=\"value2\"" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, precompile ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, precompile ) ;
#endif

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  doPointTest( "digit test"          , \
                RC_NOT_NULL          , \
                precompile           , \
               "  key1= 1 key2= -5 " ) ;
  
  if( strcmp( (char*)gRcVoidPointer, "key1=#1#key2=#-5#" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, precompile ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, ini2cfg ) ;
#endif

_door:
  return sysRc ;
}
