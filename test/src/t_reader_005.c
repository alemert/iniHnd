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

  char *iniMem = NULL ;
  tIniNode *iniRcNode ;
//tIniNode *iniAnchor = initIniNode() ; 

  sysRc = initLogging( "test/log/t_reader_005.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_005_000.ini", &iniMem ) ;
  doPointTest( "zero size file "      , \
               RC_NOT_NULL                 , \
               ini2cfg           , \
               iniMem, &sysRc ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_005_001.ini", &iniMem ) ;
  doPointTest( "empty tag"      , \
               RC_NOT_NULL                 , \
               ini2cfg           , \
               iniMem, &sysRc ) ;
  iniRcNode = (tIniNode*) gRcVoidPointer ;
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, ini2cfg ) ;
  free(iniMem) ;
#endif

_door:
  return sysRc ;
}
