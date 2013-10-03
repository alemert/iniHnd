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
#include <inihnd.h>
#include <initypes.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_node_011.log", INF ) ;
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

   doPointTest( "basic test"        , \
                 RC_NOT_NULL        , \
                 setIniSingleSearchNode , \
                 filter             , \
                 "channel"          , \
                 "name"             , \
                 "CHL1", 0        ) ;

   filter = (tIniNode*) gRcVoidPointer ; 
   printTree( filter ) ;

   doPointTest( "basic test"        , \
                 RC_NOT_NULL        , \
                 setIniSingleSearchNode , \
                 filter             , \
                 "time"             , \
                 "min"              , \
                  ""  , 0           ) ;

   filter = (tIniNode*) gRcVoidPointer ; 
   printTree( filter ) ;

   freeIniNode( filter ) ;

   checkMessage( TEST_OK_TXT, setIniSearchFilter ) ;
  }
  #endif

  _door:
  return sysRc ;
}

