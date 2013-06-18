/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  node.c                                                                    */
/*                                                                            */
/* testing functions :                                                        */
/*  - addValueNode                                                            */
/*  - addChildNode                                                            */
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

  sysRc = initLogging( "test/log/t_node_003.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
{
  tIniNode *anchor = initIniNode() ;
  tIniVal  *val ; 

  addValueNode( anchor, createStrValue( "hell0", "world1" ) ) ;
  addValueNode( anchor, createStrValue( "hell1", "world2" ) ) ;
  addValueNode( anchor, createStrValue( "hell2", "world3" ) ) ;



  checkMessage( TEST_OK_TXT, addChildNode ) ;
}
#endif




_door:
  return sysRc ;
}

