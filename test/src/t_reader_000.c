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
#include <tutl.h>

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
  doIntTest( "ini stating with <"   , \
              0              , \
              ini2cfg        , \
              iniMem, iniAnchor ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // ini starting with blank
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_002.ini", &iniMem ) ;
  doIntTest( "ini stating with blank"   , \
              0                , \
              ini2cfg          , \
              iniMem, iniAnchor         ) ;
  free( iniMem ) ;
#endif

  // -------------------------------------------------------
  // unexpected char found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_003.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              1                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif

  // -------------------------------------------------------
  // unexpected < found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_004.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              2                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected > found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_005.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              2                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_006.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              2                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected \0 found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_007.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              2                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected < found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_008.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              3                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_009.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              3                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_000_010.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              0                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
  // -------------------------------------------------------
  // unexpected / found
  // -------------------------------------------------------
#if(0)
  iniReader( "test/cfg/t_reader_000_011.ini", &iniMem ) ;
  doIntTest( "wrong char found"   , \
              4                   , \
              ini2cfg             , \
              iniMem, iniAnchor  ) ;
  free( iniMem ) ;
#endif
  
_door:
  return sysRc ;
}
