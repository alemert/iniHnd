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

  sysRc = initLogging( "test/log/t_convert_014.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  char *iniMem = NULL ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_convert_014_000.ini", &iniMem ) ;
    char *shrtMem = precompile( iniMem ) ;
    char *_shrtMem = shrtMem ;
    tIniNode *pNode ;
    doPointTest( "two values"       , \
                  RC_NOT_NULL     , \
                  tag2node        , \
                  &shrtMem       ) ;
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
    if( strcmp( pNode->value->nextVal->key, "bye" ) != 0 ) 
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->nextVal->value.strVal, "world" ) != 0 ) 
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }

    if( pNode->childNode == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->childNode->tag,"channel" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value->key == NULL ) 
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->childNode->value->key, "name" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value->key == NULL ) 
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value->type != STRING ) 
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->childNode->value->value.strVal, "not.me" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value->nextVal == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value->nextVal->key == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->childNode->value->nextVal->key, "hausNr" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value->nextVal->type != INTIGER )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->value->nextVal->value.intVal != 5 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }

    if( pNode->childNode->nextNode != NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->childNode->childNode != NULL )
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
