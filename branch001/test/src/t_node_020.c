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

  sysRc = initLogging( "test/log/t_node_020.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    iniHandler( "test/cfg/t_node_020.ini" );
    tIniNode *filter = setIniSingleSearchNode( NULL, "qmgr", "name", 
                                               "AMXT01", 0 ) ;

    doPointTest( "basic failed test" , \
                  RC_IS_NULL         , \
                  buildNodeCursor    , \
                  NULL               , \
                  filter              ) ;

   tIniNode* result = (tIniNode*) gRcVoidPointer ; 
   printTree( result ) ;

   checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  _door:
  return sysRc ;
}

