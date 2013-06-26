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

  sysRc = initLogging( "test/log/t_convert_030.log", INF ) ;
  if( sysRc != 0 ) goto _door ;


  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniHandler( "test/cfg/t_convert_030_000.ini" ) ;
    
    printTree( mainIniAnchor ) ;
  }
#endif

_door:
  return sysRc ;
}
