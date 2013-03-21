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

//char *iniMem = NULL ;
//char *startVal = NULL ;
//char *endVal   = NULL ;
  tIniVal* p ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
{
  tIniNode *iniAnchor = initIniNode() ;

  p = createStrValue( "first_str", "some_string" ) ;
  addValueNode( iniAnchor, p ) ;
  
  p = createIntValue( "first_int", 0 ) ;
  addValueNode( iniAnchor, p ) ;
  
sysRc = 0 ;
goto _door ;

  if( sysRc != -1 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
}
#endif

_door:
  return sysRc ;
}
