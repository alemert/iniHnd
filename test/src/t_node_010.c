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

  sysRc = initLogging( "test/log/t_node_010.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"        , \
                  RC_NOT_NULL        , \
                  setIniSingleSearchNode , \
                  NULL               , \
                  "qmgr"             , \
                  "name"             , \
                  "AMXT01", 0        ) ;

   tIniNode* filter = (tIniNode*) gRcVoidPointer ; 

   printTree( filter ) ;

   freeIniNode( filter ) ;

   checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"        , \
                  RC_IS_NULL         , \
                  setIniSingleSearchNode , \
                  NULL               , \
                  NULL               , \
                  "name"             , \
                  "AMXT01", 0        ) ;

   tIniNode* filter = (tIniNode*) gRcVoidPointer ; 

   printTree( filter ) ;

   freeIniNode( filter ) ;

   checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"        , \
                  RC_NOT_NULL         , \
                  setIniSingleSearchNode , \
                  NULL               , \
                  "qmgr"             , \
                  NULL               , \
                  NULL, 0            ) ;

   tIniNode* filter = (tIniNode*) gRcVoidPointer ; 

   printTree( filter ) ;

   freeIniNode( filter ) ;

   checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

_door:
  return sysRc ;
}

