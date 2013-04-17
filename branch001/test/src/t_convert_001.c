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

  sysRc = initLogging( "test/log/t_convert_001.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  char *iniMem = NULL ;
//tIniNode *iniAnchor = initIniNode() ; 

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_convert_001_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem, &sysRc ) ;
    char *tag ;
    doPointTest( "open tag"             , \
                  RC_NOT_NULL           , \
                  getOpenTag            , \
                  shrtMem, &tag ) ;
    if( strcmp( tag, "qmgr") != 0 )
    {
      checkMessage( TEST_ERR_TXT, getOpenTag ) ;
      sysRc = 1 ;
      goto _door ;
    }
    checkMessage( TEST_OK_TXT, getOpenTag ) ;
    free(iniMem) ;
#endif

  // -------------------------------------------------------
  // conitnuing
  // -------------------------------------------------------
#if(1)
    char* mem =  (char*) gRcVoidPointer ;
    char* key ;

    doPointTest( "get value"        , \
                  RC_NOT_NULL       , \
                  getKey            , \
                  mem, &key ) ;
    if( strcmp( key, "hello") != 0 )
    {
      checkMessage( TEST_ERR_TXT, getKey ) ;
      sysRc = 1 ;
      goto _door ;
    }
    checkMessage( TEST_OK_TXT, getKey ) ;
#endif

#if(0)
    mem =  (char*) gRcVoidPointer ;
    doPointTest( "close tag"        , \
                  RC_NOT_NULL       , \
                  getCloseTag       , \
                  mem, tag ) ;
    printf(">>%s<<\n",(char*) gRcVoidPointer ) ;
  }
#endif

_door:
  return sysRc ;
}
