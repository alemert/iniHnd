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

  sysRc = initLogging( "test/log/t_convert_003.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  char *iniMem = NULL ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_convert_003_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    char *pMem = shrtMem ;
    tIniVal *pNode ;
    doPointTest( "int node"       , \
                  RC_NOT_NULL     , \
                  val2node        , \
                  &pMem    ) ;
    pNode = (tIniVal*) gRcVoidPointer ;

    if( strcmp(pNode->key,"hello") != 0 ) 
    {
      checkMessage( TEST_ERR_TXT, val2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value.intVal != 25 ) 
    {
      checkMessage( TEST_ERR_TXT, val2node ) ;
      sysRc = 1 ;
      goto _door ;
    }

    checkMessage( TEST_OK_TXT, val2node ) ;
    free(shrtMem) ;
    free(iniMem) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_convert_003_001.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    char *pMem = shrtMem ;
    tIniVal *pNode ;
    doPointTest( "string node"       , \
                  RC_NOT_NULL     , \
                  val2node        , \
                  &pMem       ) ;
    pNode = (tIniVal*) gRcVoidPointer ;

    if( strcmp(pNode->key,"bye") != 0 ) 
    {
      checkMessage( TEST_ERR_TXT, val2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value.strVal ,"world") != 0 ) 
    {
      checkMessage( TEST_ERR_TXT, val2node ) ;
      sysRc = 1 ;
      goto _door ;
    }

    checkMessage( TEST_OK_TXT, val2node ) ;
    free(shrtMem) ;
    free(iniMem) ;
  }
#endif

_door:
  return sysRc ;
}
