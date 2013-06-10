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

#include <initypes.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_reader_005.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_reader_005_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    doPointTest( "recrusiv include"  , \
                  RC_NOT_NULL        , \
                  getInclude         , \
                  shrtMem, 0         ) ;
    checkMessage( TEST_OK_TXT, getInclude ) ;
    char** inclList = (char**) gRcVoidPointer ;
    int i ;
    for( i=0; i<30; i++)
    {
      printf( ">>%s<<\n", inclList[i] ) ;
    }
    free( iniMem  ) ;
    free( shrtMem ) ;

    doPointTest( "recrusiv include"  , \
                  RC_NOT_NULL        , \
                  uniqueFileName     , \
                  inclList         ) ;

    for( i=0; i<30; i++)
    {
      printf( ">>%s<<\n", inclList[i] ) ;
    }


    checkMessage( TEST_OK_TXT, getInclude ) ;
        

  }
#endif

_door:
  return sysRc ;
}
