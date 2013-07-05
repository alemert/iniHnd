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

  tIniNode *iniAnchor ;

  iniAnchor = initIniNode() ;

  sysRc = initLogging( "test/log/t_node_001.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  doIntTest( "set tag name" , \
              0             , \
              setIniTagName ,
              iniAnchor,
              "hugo    ", 4+1 ) ;
  if( memcmp(iniAnchor->tag,"hugo",5) != 0 )
  {
    checkMessage( TEST_ERR_TXT, setIniTagName ) ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniAnchor ) ;
#endif

  // -------------------------------------------------------
  // reinit 
  // -------------------------------------------------------
#if(1)
  doIntTest( "re-set tag name" , \
              0             , \
              setIniTagName ,
              iniAnchor,
              "hugo1   ", 5+1 ) ;
  if( memcmp(iniAnchor->tag,"hugo1",6) != 0 )
  {
    checkMessage( TEST_ERR_TXT, setIniTagName ) ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniAnchor ) ;
#endif

  // -------------------------------------------------------
  // string with '\0'
  // -------------------------------------------------------
#if(1)
  doIntTest( "real string with \\0" , \
              0             , \
              setIniTagName ,
              iniAnchor,
              "hugo12", -1 ) ;
  if( strcmp(iniAnchor->tag,"hugo12") != 0 )
  {
    checkMessage( TEST_ERR_TXT, setIniTagName ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniAnchor ) ;
#endif

_door:
  return sysRc ;
}
