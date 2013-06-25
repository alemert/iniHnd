/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  node.c                                                                    */
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
#include <inihnd.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_node_039.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  iniHandler( "test/cfg/t_node_039_000.ini" );

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    tIniNode *filter = setIniSingleSearchNode(NULL,"qmgr","name","ADMT01",0) ;

    filter = setIniSingleSearchNode( filter, "channel", "name", "CHL1", 0 ) ;

    doPointTest( "basic failed test"  , \
                  RC_NOT_NULL         , \
                  buildNodeCursor     , \
                  NULL                , \
                  filter              ) ;

    tCursorCfg* result = (tCursorCfg*) gRcVoidPointer ; 
    printCursor( result ) ;
 
    checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;

    freeIniNode( filter ) ;
  }
  #endif

  _door:
  return sysRc ;
}

