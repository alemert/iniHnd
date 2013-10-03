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

#include <inihnd.h>
#include <initypes.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_search_000.log", INF ) ;
  if( sysRc != 0 ) goto _door ;


  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniHandler( "test/cfg/t_search_000_000.ini" ) ;

    doPointTest( "basic failed test"  , \
                 RC_IS_NULL           , \
                 getIniNode           , \
                 NULL                 ) ;

    tIniNode* result = (tIniNode*) gRcVoidPointer ;
    printTree( result ) ;

    doPointTest( "basic failed test"  , \
                 RC_IS_NULL           , \
                 getIniNode           , \
                 "system"             ) ;

    result = (tIniNode*) gRcVoidPointer ;
    printTree( result ) ;

    doPointTest( "basic failed test"  , \
                 RC_NOT_NULL           , \
                 getIniNode           , \
                 "qmgr", NULL             ) ;

    result = (tIniNode*) gRcVoidPointer ;
    printTree( result ) ;

    doPointTest( "basic failed test"  , \
                 RC_NOT_NULL          , \
                 getIniNode           , \
                 "qmgr"               , \
                 "channel"            , \
                 NULL                 ) ;

    result = (tIniNode*) gRcVoidPointer ;
    printTree( result ) ;
 
    doPointTest( "basic failed test"  , \
                 RC_NOT_NULL          , \
                 getNextIniNode       , \
                 result               , \
                 "qmgr"               , \
                 "channel"            , \
                 NULL                 ) ;

    result = (tIniNode*) gRcVoidPointer ;
    printTree( result ) ;

    doPointTest( "basic failed test"  , \
                 RC_IS_NULL          , \
                 getNextIniNode       , \
                 result               , \
                 "qmgr"               , \
                 "channel"            , \
                 NULL                 ) ;

    result = (tIniNode*) gRcVoidPointer ;
    printTree( result ) ;

    checkMessage( TEST_OK_TXT, getIniNode ) ;
    
  }
#endif

_door:
  return sysRc ;
}
