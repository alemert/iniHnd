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

  sysRc = initLogging( "test/log/t_reader_001.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_reader_001_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "recrusiv include"  , \
                  RC_IS_NULL        , \
                  getInclude         , \
                  shrtMem, 0         ) ;
    checkMessage( TEST_OK_TXT, getInclude ) ;
    printf(">>%s<<\n",(char*) gRcVoidPointer ) ;

    free( iniMem  ) ;
    free( shrtMem ) ;
  }
#endif

_door:

#if(0)
  logger( LSYS_FLOW_DUMP ) ;
#endif
  return sysRc ;
}
