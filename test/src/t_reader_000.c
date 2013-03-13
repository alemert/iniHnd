/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  reader.c      */
/*                                                                            */
/* testing functions :                                                        */
/*   - iniReader               */
/*   - iniHandleOpenTag              */
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
#include <tutl.h>

#include <initypes.h>
#include <inihnd.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  char    *iniMem = NULL ;
#if(1)
  tIniNode *iniAnchor = initIniNode() ;
#else
  tIniNode *iniAnchor = NULL ;
#endif

  sysRc = initLogging( "test/log/t_reader_000.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
#if(1)
  doIntTest( "no file found"    , \
              2                 , \
              iniReader         , \
             "test/cfg/does_not_exists.ini", &iniMem ) ;
#endif

  // -------------------------------------------------------
  // file opened
  // -------------------------------------------------------
#if(1)
  doIntTest( "file open ok"              , \
              0                          , \
              iniReader                  , \
             "test/cfg/t_reader_000_000.ini", &iniMem ) ;
  printf( ">>%s<<\n", iniMem ) ;
  free( iniMem ) ;
#endif

  // -------------------------------------------------------
  // file opened
  // -------------------------------------------------------
#if(1)
  doIntTest( "file open ok"              , \
              0                          , \
              iniReader                  , \
             "test/cfg/t_reader_000_001.ini", &iniMem ) ;
  printf( ">>%s<<\n", iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // ini starting with <
  // -------------------------------------------------------
#if(1)
  doPointTest( "ini stating with <"   , \
               RC_NOT_NULL            , \
              iniHandleOpenTag        , \
              iniMem, iniAnchor, &sysRc ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // ini starting with blank
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_002.ini", &iniMem ) ;
  doPointTest( "ini stating with blank"   , \
                RC_NOT_NULL                , \
                iniHandleOpenTag          , \
                iniMem, iniAnchor, &sysRc         ) ;
  free( iniMem ) ;
#endif

  // -------------------------------------------------------
  // unexpected char found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_003.ini", &iniMem ) ;
  doPointTest( "wrong char found"   , \
               RC_IS_NULL                   , \
              iniHandleOpenTag             , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 1 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif

  // -------------------------------------------------------
  // unexpected < found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_004.ini", &iniMem ) ;
  doPointTest( "wrong char found"        , \
              RC_IS_NULL                 , \
              iniHandleOpenTag           , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 2 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected > found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_005.ini", &iniMem ) ;
  doPointTest( "wrong char found"   , \
                RC_IS_NULL                   , \
              iniHandleOpenTag             , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 2 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_006.ini", &iniMem ) ;
  doPointTest( "wrong char found"     , \
               RC_IS_NULL                   , \
              iniHandleOpenTag             , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 2 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected \0 found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_007.ini", &iniMem ) ;
  doPointTest( "wrong char found"          , \
              RC_IS_NULL                   , \
              iniHandleOpenTag             , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 2 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected < found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_008.ini", &iniMem ) ;
  doPointTest( "wrong char found"            , \
                RC_IS_NULL                   , \
                iniHandleOpenTag             , \
                iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 3 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_009.ini", &iniMem ) ;
  doPointTest( "wrong char found"      , \
               RC_IS_NULL              , \
              iniHandleOpenTag         , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 3 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_010.ini", &iniMem ) ;
  doPointTest( "wrong char found"       , \
               RC_NOT_NULL              , \
              iniHandleOpenTag          , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 0 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  if( strcmp( iniAnchor->tag, "qmgr" ) )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_011.ini", &iniMem ) ;
  doPointTest( "wrong char found"        , \
                RC_IS_NULL               , \
              iniHandleOpenTag           , \
              iniMem, iniAnchor, &sysRc  ) ;
  if( sysRc != 6 )
  {
    checkMessage( TEST_ERR_TXT, iniHandleOpenTag ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, iniHandleOpenTag ) ;
  free( iniMem ) ;
#endif
  
_door:
  return sysRc ;
}
