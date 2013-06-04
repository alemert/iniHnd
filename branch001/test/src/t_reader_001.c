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

  sysRc = initLogging( "test/log/t_reader_000.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    char *iniMem ;
    iniReader( "test/cfg/t_reader_000_000.ini", &iniMem ) ;
    doPointTest( "no include found"  , \
                  RC_IS_NULL         , \
                  getInclude         , \
                  iniMem             ) ;
    if( sysRc != 1 )
    {
      checkMessage( TEST_ERR_TXT, iniHandleCloseTag ) ;
      sysRc = 1 ;
      goto _door ;
    }
    checkMessage( TEST_OK_TXT, iniHandleCloseTag ) ;
    free(iniMem) ;
  }
#endif

_door:
  return sysRc ;
}
