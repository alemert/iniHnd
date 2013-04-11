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
  char *startVal = NULL ;
  char *endVal   = NULL ;
  tIniNode *iniAnchor = initIniNode() ; 
  tIniNode *iniCfg    = iniAnchor ;

  sysRc = initLogging( "test/log/t_reader_002.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

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
  doPointTest( "eof "                           , \
               RC_IS_NULL                       , \
               iniHandleValues                  , \
               startVal, endVal, iniCfg, &sysRc ) ;
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
  doPointTest( "early >"         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 1 )
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
  iniReader( "test/cfg/t_reader_002_006.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early <"         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 1 )
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
  iniReader( "test/cfg/t_reader_002_007.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early eof"         , \
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
  iniReader( "test/cfg/t_reader_002_008.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early >"         , \
               RC_IS_NULL           , \
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
  iniReader( "test/cfg/t_reader_002_009.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early <"         , \
               RC_IS_NULL           , \
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
  iniReader( "test/cfg/t_reader_002_010.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early eof"         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 2 )
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
  iniReader( "test/cfg/t_reader_002_011.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "missing ="         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 4 )
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
  iniReader( "test/cfg/t_reader_002_012.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early <"         , \
               RC_IS_NULL           , \
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
  iniReader( "test/cfg/t_reader_002_013.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early >"         , \
               RC_IS_NULL           , \
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
  iniReader( "test/cfg/t_reader_002_014.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "late ="         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 3 )
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
  iniReader( "test/cfg/t_reader_002_015.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "late ="         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 3 )
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
  iniReader( "test/cfg/t_reader_002_016.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "early eof"         , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 2 )
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
  iniReader( "test/cfg/t_reader_002_017.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "late ="             , \
               RC_IS_NULL           , \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( sysRc != 3 )
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
  iniReader( "test/cfg/t_reader_002_049.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "checking node"  ,  \
               RC_NOT_NULL       ,  \
               iniHandleValues    , \
               startVal, endVal, iniCfg, &sysRc   ) ;
  if( strcmp( iniCfg->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniCfg->value->value.strVal, "ADMT01" ) != 0 )
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
  iniReader( "test/cfg/t_reader_002_050.ini", &iniMem ) ;
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

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_051.ini", &iniMem ) ;
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

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_052.ini", &iniMem ) ;
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
  if( iniCfg->value->nextVal->nextVal->nextVal->type != INTIGER )
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
  iniReader( "test/cfg/t_reader_002_053.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "value found <$"            , \
               RC_NOT_NULL              , \
               iniHandleValues          , \
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

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_054.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "value found eof$"            , \
               RC_NOT_NULL              , \
               iniHandleValues          , \
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

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_002_055.ini", &iniMem ) ;
  startVal = iniMem ;
  doPointTest( "value found eof$"            , \
               RC_NOT_NULL              , \
               iniHandleValues          , \
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
