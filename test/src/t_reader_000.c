/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
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
#include "tutl.h"
#include <inihnd.h>
#include <initypes.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_reader_000.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_reader_000_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "no include found"  , \
                  RC_NOT_NULL        , \
                  getInclude         , \
                  shrtMem, 0         ) ;

    char **fileName = (char**) gRcVoidPointer ;
    if( fileName[0] != 0 )
    {
      checkMessage( TEST_ERR_TXT, getInclude ) ;
      sysRc = 1 ;
      goto _door ;
    }

    checkMessage( TEST_OK_TXT, getInclude ) ;
    free( iniMem  ) ;
    free( shrtMem ) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_reader_000_001.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "include found"  , \
                  RC_NOT_NULL     , \
                  getInclude      , \
                  shrtMem, 0      ) ;

    checkMessage( TEST_OK_TXT, getInclude ) ;
    char **fileName = (char**) gRcVoidPointer ;
    printf(">>%s<<\n",(char*) fileName[0] ) ;

    free( iniMem  ) ;
    free( shrtMem ) ;
  }
#endif

_door:
  return sysRc ;
}
