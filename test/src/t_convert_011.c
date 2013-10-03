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

  sysRc = initLogging( "test/log/t_convert_011.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  char *iniMem = NULL ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_convert_011_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    char *_shrtMem = shrtMem ;
    tIniNode *pNode ;
    doPointTest( "open tag"       , \
                  RC_NOT_NULL     , \
                  tag2node        , \
                  &shrtMem    ) ;
    pNode = (tIniNode*) gRcVoidPointer ;

    if( strcmp(pNode->tag,"qmgr") != 0 ) 
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->value.intVal != 25 ) 
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }

    checkMessage( TEST_OK_TXT, tag2node ) ;
    free(_shrtMem) ;
    free(iniMem) ;
  }
#endif

_door:
  return sysRc ;
}
