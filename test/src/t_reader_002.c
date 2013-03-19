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

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  char *iniMem = NULL ;
  char *startVal = NULL ;
  char *endVal   = NULL ;
  tIniNode *iniAnchor = initIniNode() ; 
  tIniNode *iniCfg    = iniAnchor ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_000.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "no values found"  , \
               RC_NOT_NULL        , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != -1 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_001.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "no values found"  , \
               RC_NOT_NULL        , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != -1 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_002.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early > "         , \
               RC_IS_NULL        , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 1 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_003.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early eof "         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 2 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 2 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_004.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early = "         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 3 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 2 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_005.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "value found"         , \
               RC_NOT_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 0 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 2 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free(iniMem) ;

#endif

_door:
  return sysRc ;
}
