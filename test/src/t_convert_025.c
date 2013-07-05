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

  sysRc = initLogging( "test/log/t_convert_025.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  char *iniMem = NULL ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    iniReader( "test/cfg/t_convert_025_000.ini", &iniMem ) ;
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
    if( strcmp( pNode->value->value.strVal, "QM1" ) != 0 )
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
    if( pNode->childNode->tag == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->childNode->tag, "channel" ) != 0 )
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
    if( strcmp( pNode->childNode->value->value.strVal, "CH1" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }

    if( pNode->nextNode == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    pNode = pNode->nextNode ;
    if( pNode->tag == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp(pNode->tag, "qmgr" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->key, "name" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->nextVal == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->nextVal->key == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->nextVal->key, "logging" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->nextVal->value.strVal, "linear" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->nextVal->nextVal == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->nextVal->nextVal->key == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->nextVal->nextVal->key, "time" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->nextVal->nextVal->value.intVal != 5 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->nextVal->nextVal->nextVal != NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->value.strVal, "QM2" ) != 0 )
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
    pNode = pNode->childNode ;
    if( pNode->tag == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->tag, "channel" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value->key == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->key, "name" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->value.strVal, "CH1" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->nextNode == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    pNode=pNode->nextNode ; 
   
    if( pNode->tag == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->tag, "channel" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( pNode->value == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ; 
      goto _door ; 
    }
    if( pNode->value->key == NULL )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->key, "name" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( strcmp( pNode->value->value.strVal, "CH2" ) != 0 )
    {
      checkMessage( TEST_ERR_TXT, tag2node ) ;
      sysRc = 1 ; 
      goto _door ;
    }
    if( pNode->nextNode != NULL )
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
