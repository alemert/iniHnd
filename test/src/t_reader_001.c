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
  tIniNode *iniAnchor = initIniNode() ; 

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_reader_002_000.ini", &iniMem ) ;
    char *startP = iniHandleOpenTag( iniMem, iniAnchor, &sysRc  ) ;
    doPointTest( "base test "         , \
                  RC_IS_NULL          , \
                  iniHandleCloseTag   , \
                  startP, iniAnchor->tag, &sysRc ) ;
    sysRc = 1 ;
    goto _door ;
  }
#endif

_door:
  return sysRc ;
}
