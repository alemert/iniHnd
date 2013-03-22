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

  sysRc = initLogging( "test/log/t_reader_001.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  char *iniMem = NULL ;
  tIniNode *iniAnchor = initIniNode() ; 

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_reader_001_001.ini", &iniMem ) ;
    char *startP = iniHandleOpenTag( iniMem, iniAnchor, &sysRc  ) ;
    doPointTest( "no close tag"         , \
                  RC_IS_NULL            , \
                  iniHandleCloseTag     , \
                  startP, iniAnchor->tag, &sysRc ) ;
    if( sysRc != 1 )
    {
      checkMessage( TEST_ERR_TXT, iniHandleCloseTag ) ;
      sysRc = 1 ;
      goto _door ;
    }
    checkMessage( TEST_OK_TXT, iniHandleCloseTag ) ;
    free(iniMem) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_reader_001_002.ini", &iniMem ) ;
    char *startP = iniHandleOpenTag( iniMem, iniAnchor, &sysRc  ) ;
    doPointTest( "no close tag"         , \
                  RC_IS_NULL            , \
                  iniHandleCloseTag     , \
                  startP, iniAnchor->tag, &sysRc ) ;
    if( sysRc != 2 )
    {
      checkMessage( TEST_ERR_TXT, iniHandleCloseTag ) ;
      sysRc = 1 ;
      goto _door ;
    }
    checkMessage( TEST_OK_TXT, iniHandleCloseTag ) ;
    free(iniMem) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_reader_001_003.ini", &iniMem ) ;
    char *startP = iniHandleOpenTag( iniMem, iniAnchor, &sysRc  ) ;
    doPointTest( "no close tag"         , \
                  RC_IS_NULL            , \
                  iniHandleCloseTag     , \
                  startP, iniAnchor->tag, &sysRc ) ;
    if( sysRc != 3 )
    {
      checkMessage( TEST_ERR_TXT, iniHandleCloseTag ) ;
      sysRc = 1 ;
      goto _door ;
    }
    checkMessage( TEST_OK_TXT, iniHandleCloseTag ) ;
    free(iniMem) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_reader_001_004.ini", &iniMem ) ;
    char *startP = iniHandleOpenTag( iniMem, iniAnchor, &sysRc  ) ;
    doPointTest( "no close tag"         , \
                  RC_IS_NULL            , \
                  iniHandleCloseTag     , \
                  startP, iniAnchor->tag, &sysRc ) ;
    if( sysRc != 3 )
    {
      checkMessage( TEST_ERR_TXT, iniHandleCloseTag ) ;
      sysRc = 1 ;
      goto _door ;
    }
    checkMessage( TEST_OK_TXT, iniHandleCloseTag ) ;
    free(iniMem) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_reader_001_000.ini", &iniMem ) ;
    char *startP = iniHandleOpenTag( iniMem, iniAnchor, &sysRc  ) ;
    doPointTest( "base test "          , \
                  RC_NOT_NULL          , \
                  iniHandleCloseTag    , \
                  startP, iniAnchor->tag, &sysRc ) ;
    printf("start >>-%s<<-\n",startP);
    printf("end   >>-%s<<-\n",(char*)gRcVoidPointer);
    free(iniMem) ;
  }
#endif

_door:
  return sysRc ;
}
