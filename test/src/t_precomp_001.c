/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  reader.c                                                                  */
/*                                                                            */
/* testing functions :                                                        */
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

#include <inihnd.h>
#include <initypes.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_precomp_001.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_precomp_001_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "general test"   , \
                  RC_IS_NULL      , \
                  rmInclude       , \
                  shrtMem         ) ;
 
//char *noIncl = (char*)gRcVoidPointer ;

    free( iniMem ) ;

    checkMessage( TEST_OK_TXT, rmInclude ) ;
  }
#endif

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_precomp_001_001.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "general test"   , \
                  RC_NOT_NULL     , \
                  rmInclude       , \
                  shrtMem         ) ;
   
    char *noIncl = (char*)gRcVoidPointer ;
  
    printf( ">>-%s-<<\n", noIncl ) ;
  
    free( iniMem ) ;
    free( shrtMem ) ;
  
    checkMessage( TEST_OK_TXT, rmInclude ) ;
  }
#endif

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_precomp_001_002.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "general test"   , \
                  RC_NOT_NULL     , \
                  rmInclude       , \
                  shrtMem         ) ;
  
    char *noIncl = (char*)gRcVoidPointer ;
 
    printf( ">>-%s-<<\n", noIncl ) ;
 
    free( iniMem ) ;
    free( shrtMem ) ;
 
    checkMessage( TEST_OK_TXT, rmInclude ) ;
  }
#endif


  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_precomp_001_003.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "general test"   , \
                  RC_NOT_NULL     , \
                  rmInclude       , \
                  shrtMem         ) ;
 
    char *noIncl = (char*)gRcVoidPointer ;

    printf( ">>-%s-<<\n", noIncl ) ;

    free( iniMem ) ;
    free( shrtMem ) ;

    checkMessage( TEST_OK_TXT, rmInclude ) ;
  }
#endif


_door:
  return sysRc ;
}
