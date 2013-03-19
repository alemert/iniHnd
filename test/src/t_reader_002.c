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

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  char *iniMem = NULL ;
  char *startVal = NULL ;
  char *endVal   = NULL ;
  tIniNode *iniAnchor = initIniNode() ; 
  tIniNode *iniCfg    = iniAnchor ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_000.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "base test "     , \
               RC_NOT_NULL      , \
               iniHandleValues  , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != -1 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free(iniMem) ;
#endif

_door:
  return sysRc ;
}
