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

//char *iniMem = NULL ;
//char *startVal = NULL ;
//char *endVal   = NULL ;
  tIniVal* p ;

  sysRc = initLogging( "test/log/t_node_002.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
{
  tIniNode *iniAnchor = initIniNode() ;

  p = createStrValue( "first_str", "some_string" ) ;

  doIntTest( "first value added"  , \
              0                   , \
              addValueNode        , \
              iniAnchor, p        ) ;
  
  p = createIntValue( "first_int", 0 ) ;
  doIntTest( "second value added"  , \
              0                   , \
              addValueNode        , \
              iniAnchor, p        ) ;
  
  p = createStrValue( "first_str", "duplicated" ) ;
  doIntTest( "same value duplicated"   , \
              1                   , \
              addValueNode        , \
              iniAnchor, p        ) ;

  p = createIntValue( "first_int", 2 ) ;
  doIntTest( "some value duplicated"  , \
              1                   , \
              addValueNode        , \
              iniAnchor, p        ) ;
}
#endif

_door:
  return sysRc ;
}
