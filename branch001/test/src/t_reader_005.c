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
  tIniNode *iniRcNode ;
//tIniNode *iniAnchor = initIniNode() ; 

  sysRc = initLogging( "test/log/t_reader_005.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_005_000.ini", &iniMem ) ;
  doPointTest( "zero size file " , \
               RC_NOT_NULL       , \
               ini2cfg           , \
               iniMem, &sysRc    ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_005_001.ini", &iniMem ) ;
  doPointTest( "empty tag"    , \
               RC_NOT_NULL    , \
               ini2cfg        , \
               iniMem, &sysRc ) ;
  iniRcNode = (tIniNode*) gRcVoidPointer ;
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, ini2cfg ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_005_003.ini", &iniMem ) ;
  doPointTest( "tag with 2 values" , \
               RC_NOT_NULL         , \
               ini2cfg             , \
               iniMem, &sysRc      ) ;
  iniRcNode = (tIniNode*) gRcVoidPointer ;
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->value.strVal, "ADMT01" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->key, "logging" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->value.strVal, "linear" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  checkMessage( TEST_OK_TXT, ini2cfg ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // 2 nodes with 2 values
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_005_004.ini", &iniMem ) ;
  doPointTest( "2 same level nodes with 2 values"  , \
               RC_NOT_NULL         , \
               ini2cfg             , \
               iniMem, &sysRc      ) ;
  iniRcNode = (tIniNode*) gRcVoidPointer ;

  // -------------------------------------------------------
  // test first node
  // -------------------------------------------------------
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode != NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->value.strVal, "ADMT01" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->key, "logging" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->value.strVal, "linear" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->value->nextVal->nextVal != NULL  ) 
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }

  // -------------------------------------------------------
  // test second node
  // -------------------------------------------------------
  iniRcNode = iniRcNode->nextNode ;
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode != NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->nextNode != NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->value.strVal, "ADMT02" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->key, "logging" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->value.strVal, "linear" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->value->nextVal->nextVal != NULL  ) 
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }

  checkMessage( TEST_OK_TXT, ini2cfg ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // 2 nodes with two values, 1st node with child node with 2 values
  // -------------------------------------------------------
#if(1)
  iniReader( "test/cfg/t_reader_005_005.ini", &iniMem ) ;
  doPointTest( "simple tree 2(2)-1(2),2(2)" , \
               RC_NOT_NULL         , \
               ini2cfg             , \
               iniMem, &sysRc      ) ;
  iniRcNode = (tIniNode*) gRcVoidPointer ;

  // -------------------------------------------------------
  // test first node
  // -------------------------------------------------------
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->value.strVal, "ADMT01" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->key, "logging" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->value.strVal, "linear" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->value->nextVal->nextVal != NULL  ) 
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }

  // -------------------------------------------------------
  // test second node
  // -------------------------------------------------------
  iniRcNode = iniRcNode->nextNode ;
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode != NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->nextNode != NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->value.strVal, "ADMT02" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->key, "logging" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->value.strVal, "linear" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->value->nextVal->nextVal != NULL  ) 
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }

  checkMessage( TEST_OK_TXT, ini2cfg ) ;
  free(iniMem) ;
#endif

  // -------------------------------------------------------
  // complete tree
  // -------------------------------------------------------
  iniReader( "test/cfg/t_reader_005_006.ini", &iniMem ) ;
  doPointTest( "complete tree"     , \
               RC_NOT_NULL         , \
               ini2cfg             , \
               iniMem, &sysRc      ) ;
  iniRcNode = (tIniNode*) gRcVoidPointer ;

  // -------------------------------------------------------
  // test first node
  // -------------------------------------------------------
  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->value.strVal, "ADMT01" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->key, "logging" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->value.strVal, "linear" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->value->nextVal->nextVal != NULL  ) 
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }

  // -------------------------------------------------------
  // test second node
  // -------------------------------------------------------

  if( iniRcNode->nextNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  iniRcNode = iniRcNode->nextNode ;

  if( strcmp( iniRcNode->tag, "qmgr" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->nextNode != NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->value.strVal, "ADMT02" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->key, "logging" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->value.strVal, "linear" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->value->nextVal->nextVal == NULL  ) 
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->value->nextVal->nextVal->key, "trigger" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if(  iniRcNode->value->nextVal->nextVal->value.intVal != 5  )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->value->nextVal->nextVal->nextVal != NULL  )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->childNode->tag, "qlocal" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->value->key == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->childNode->value->key, "name" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp(iniRcNode->childNode->value->value.strVal, "XQ.GATEWAT01.00")!=0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->value->nextVal == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->childNode->value->nextVal->key, "depth") != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->value->nextVal->value.intVal != 10000 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->childNode->nextNode->tag, "qlocal" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->value == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->childNode->nextNode->value->key, "name" )  != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp(iniRcNode->childNode->nextNode->value->value.strVal,
      "XQ.GATEWAT02.00") != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->value->nextVal == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp(iniRcNode->childNode->nextNode->value->nextVal->key,"depth") != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->value->nextVal->value.intVal != 20000 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->value->nextVal->nextVal == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->childNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp(iniRcNode->childNode->nextNode->childNode->tag,"statistic") !=  0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp(iniRcNode->childNode->nextNode->childNode->value->key, "short" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->childNode->value->value.intVal != 1 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( strcmp( iniRcNode->childNode->nextNode->childNode->value->nextVal->key,
              "long" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->childNode->value->nextVal->value.intVal
      != 0  )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniRcNode->childNode->nextNode->childNode->value->nextVal->nextVal!=NULL )
  {
    checkMessage( TEST_ERR_TXT, ini2cfg ) ;
    sysRc = 1 ;
    goto _door ;
  }

  checkMessage( TEST_OK_TXT, ini2cfg ) ;
  free(iniMem) ;

_door:
  return sysRc ;
}
