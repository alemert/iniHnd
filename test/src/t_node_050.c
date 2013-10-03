/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  node.c                                                                    */
/*                                                                            */
/* testing functions : setIniSearchNode      */
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

#include <inihnd.h>
#include <initypes.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_node_050.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"  , \
                  RC_IS_NULL         , \
                  setIniSearchNode    ) ;

    tIniNode* result = (tIniNode*) gRcVoidPointer ; 
    printTree( result ) ;
 
    checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"  , \
                  RC_IS_NULL         , \
                  setIniSearchNode    , \
                  NULL                ) ;

    tIniNode* result = (tIniNode*) gRcVoidPointer ; 
    printTree( result ) ;
 
    checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"      , \
                  RC_IS_NULL       , \
                  setIniSearchNode , \
                  "qmgr"           ) ;

    tIniNode* result = (tIniNode*) gRcVoidPointer ; 
    printTree( result ) ;
 
    checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"      , \
                  RC_IS_NULL       , \
                  setIniSearchNode , \
                  "qmgr", "name"   ) ;

    tIniNode* result = (tIniNode*) gRcVoidPointer ; 
    printTree( result ) ;
 
    checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "basic test"              , \
                  RC_NOT_NULL              , \
                  setIniSearchNode         , \
                  "qmgr", "name", "ADMT01" ) ;

    tIniNode* result = (tIniNode*) gRcVoidPointer ; 
    printTree( result ) ;
 
    checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  _door:
  return sysRc ;
}

