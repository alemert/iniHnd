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

#include <initypes.h>
#include <inihnd.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_precomp_002.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // test
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_precomp_002_000.ini", &iniMem ) ;
    doPointTest( "general test"   , \
                  RC_NOT_NULL     , \
                  precompile       , \
                  iniMem         ) ;
 
    char *shrtMem = (char*)gRcVoidPointer ;

    printf( ">>-%s-<<\n", shrtMem ) ;

    free( iniMem ) ;
    free( shrtMem ) ;

    checkMessage( TEST_OK_TXT, precompile ) ;
  }
#endif


_door:
  return sysRc ;
}
