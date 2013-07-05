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

  sysRc = initLogging( "test/log/t_node_003.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
{
  tIniNode *anchor = initIniNode() ;
  tIniVal  *val ; 
  tIniVal  *search ; 

  addValueNode( anchor, createStrValue( "hell0", "world1" ) ) ;
  addValueNode( anchor, createStrValue( "hell1", "world2" ) ) ;
  addValueNode( anchor, createStrValue( "hell2", "world3" ) ) ;

  doPointTest( "find anchor"  , 
                RC_IS_NULL    ,
                findValueNode , 
                NULL          ,
                anchor->value );

  checkMessage( TEST_OK_TXT, findValueNode ) ;

  search = createStrValue( "hell0", "world1" ) ;

  doPointTest( "find anchor"  , 
                RC_NOT_NULL   ,
                findValueNode , 
                search        ,
                anchor->value );

  val = (tIniVal*) gRcVoidPointer ;

  printVal( val, "" ) ;

  checkMessage( TEST_OK_TXT, findValueNode ) ;

  search = createStrValue( "hell1", "world2" ) ;

  doPointTest( "find anchor"  , 
                RC_NOT_NULL   ,
                findValueNode , 
                search        ,
                anchor->value );

  val = (tIniVal*) gRcVoidPointer ;

  printVal( val, "" ) ;

  checkMessage( TEST_OK_TXT, findValueNode ) ;

  search = createStrValue( "hell2", "world3" ) ;

  doPointTest( "find anchor"  , 
                RC_NOT_NULL   ,
                findValueNode , 
                search        ,
                anchor->value );

  val = (tIniVal*) gRcVoidPointer ;

  printVal( val, "" ) ;

  checkMessage( TEST_OK_TXT, findValueNode ) ;

  search = createStrValue( "!exists", "world3" ) ;

  doPointTest( "find anchor"  , 
                RC_IS_NULL   ,
                findValueNode , 
                search        ,
                anchor->value );

  val = (tIniVal*) gRcVoidPointer ;

  printVal( val, "" ) ;

  checkMessage( TEST_OK_TXT, findValueNode ) ;

  search = createStrValue( "hell2", "l" ) ;

  doPointTest( "find anchor"  , 
                RC_IS_NULL   ,
                findValueNode , 
                search        ,
                anchor->value );

  val = (tIniVal*) gRcVoidPointer ;

  printVal( val, "" ) ;

  checkMessage( TEST_OK_TXT, findValueNode ) ;
}
#endif




_door:
  return sysRc ;
}

