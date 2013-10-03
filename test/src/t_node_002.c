/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  node.c                                                                    */
/*                                                                            */
/* testing functions :                                                        */
/*  - addValueNode                                                            */
/*  - addChildNode                                                            */
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

//char *iniMem = NULL ;
//char *startVal = NULL ;
//char *endVal   = NULL ;
  tIniVal* p ;

  sysRc = initLogging( "test/log/t_node_002.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
{
  tIniNode *iniAnchor = initIniNode() ;

  p = createStrValue( "first_str", "some_string" ) ;

  doIntTest( "first value added"  , \
              0                   , \
              addValueNode        , \
              iniAnchor, p        ) ;
  
  p = createIntValue( "first_int", 0 ) ;
  doIntTest( "second value added"  , \
              0                   , \
              addValueNode        , \
              iniAnchor, p        ) ;
  
  p = createStrValue( "first_str", "duplicated" ) ;
  doIntTest( "same value duplicated"   , \
              1                   , \
              addValueNode        , \
              iniAnchor, p        ) ;

  p = createIntValue( "first_int", 2 ) ;
  doIntTest( "some value duplicated"  , \
              1                   , \
              addValueNode        , \
              iniAnchor, p        ) ;

  // -------------------------------------------------------
  // add first child
  // -------------------------------------------------------
  tIniNode *iniChild = initIniNode() ;

  p = createStrValue( "first_str", "some_string" ) ;

  doIntTest( "first value added"  , \
              0                   , \
              addValueNode        , \
              iniChild, p        ) ;
  
  p = createIntValue( "first_int", 0 ) ;
  doIntTest( "second value added"  , \
              0                   , \
              addValueNode        , \
              iniChild, p        ) ;

  doIntTest( "child added" , \
              0            , \
              addChildNode , \
              iniAnchor    , iniChild ) ;

  // -------------------------------------------------------
  // add second child
  // -------------------------------------------------------
  iniChild = initIniNode() ;

  p = createIntValue( "first_int", 3 ) ;

  doIntTest( "add value "  , \
              0                   , \
              addValueNode        , \
              iniChild, p        ) ;

  doIntTest( "add child "  , \
              0            , \
              addChildNode , \
              iniAnchor    , iniChild ) ;

  // -------------------------------------------------------
  // check the tree
  // -------------------------------------------------------

  // -------------------------------------------------------
  // check the anchor
  // -------------------------------------------------------
  if( iniAnchor->childNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }
  if( iniAnchor->childNode->value == NULL )
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  // -------------------------------------------------------
  // check the first child
  // -------------------------------------------------------
  if( strcmp( iniAnchor->childNode->value->key, "first_str" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  if( strcmp( iniAnchor->childNode->value->value.strVal, "some_string" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  if(strcmp(iniAnchor->childNode->value->nextVal->key,"first_int")!=0)
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  if(  iniAnchor->childNode->value->nextVal->value.intVal != 0 ) 
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  // -------------------------------------------------------
  // check the second child
  // -------------------------------------------------------
  if( iniAnchor->childNode->nextNode == NULL )
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  if( strcmp( iniAnchor->childNode->nextNode->value->key, "first_int" ) != 0 )
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  if( iniAnchor->childNode->nextNode->value->value.intVal != 3 )
  {
    checkMessage( TEST_ERR_TXT, addChildNode ) ;
    sysRc = 1 ;
    goto _door ;
  }

  checkMessage( TEST_OK_TXT, addChildNode ) ;
}
#endif




_door:
  return sysRc ;
}

