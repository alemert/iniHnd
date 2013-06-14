/******************************************************************************/
/* change title on for new project                                            */
/*  functions                                                                 */
/*   - initIniNode                                                            */
/*   - setIniTagName                                                          */
/*   - createStrValue                                                         */
/*   - createIntValue                                                         */
/*   - addValueNode                                                           */
/*   - addChildNode                                                           */
/*   - getNode                                                                */
/*   - shiftFilter                                                        */
/*   - getFilterTag                                                  */
/*   - getFilterKey                                                    */
/*   - getFilterVal                                                           */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <string.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <initypes.h>
#include <inihnd.h>

#include <genlib.h>

#include <msgcat/lgstd.h>
#include <ctl.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
const char* shiftFilter(  char* filter ) ;
const char* getFilterTag( char* singleFilter ) ;
const char* getFilterKey( char* singleFilter ) ;
const char* getFilterVal( char* singleFilter ) ;

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* init node                                                                  */
/******************************************************************************/
tIniNode* initIniNode()
{
  tIniNode *node = NULL ;

  node = (tIniNode*) malloc( sizeof(tIniNode) ); 
  if( node == NULL )
  {
    logger( LSTD_MEM_ALLOC_ERROR ) ;
    goto _door ;
  } 

  node->tag       = NULL ;
  node->nextNode  = NULL ;
  node->value     = NULL ;
  node->childNode = NULL ;

_door :
  return node ; 
}

/******************************************************************************/
/* set ini tag name                                              */
/******************************************************************************/
int setIniTagName( tIniNode *node, const char* tag, int lng )
{
  int sysRc = 0 ;

  if( lng < 0 )                        // tag ends with '\0' if lng<0 
    lng   = strlen( tag ) + 1 ;        //
                                       //
  errno = 0 ;                          //
                                       //
  if( node->tag != NULL )              // if node already set 
  {                                    //   free memory
    free( node->tag ) ;                //
  }                                    //
                                       //
  node->tag = (char*) malloc( lng * sizeof(char) ) ;      
  if( node->tag == NULL )              // alloc memory 
  {                                    //  & handle error
    logger( LSTD_MEM_ALLOC_ERROR ) ;   //
    sysRc = errno ;                    //
    goto _door ;                       //
  }                                    //
                                       //
  memcpy( node->tag, tag, lng ) ;      // copy to struct
  node->tag[lng-1] = '\0' ;            // set end of string
                                       //
_door:
  return sysRc ;
}

/******************************************************************************/
/* create string value tag                                          */
/******************************************************************************/
tIniVal* createStrValue( char* key, char* value )
{ 
  tIniVal *this;
  tIniVal *pRc = NULL ;

  this = (tIniVal*) malloc( sizeof(tIniVal) ) ;
  if( this == NULL ) 
  {
    logger( LSTD_MEM_ALLOC_ERROR ) ;
    goto _door ;
  }
  
  this->nextVal = NULL ;
  this->type    = STRING ;
  this->key     = key ;
  this->value.strVal   = value ;
  
  pRc = this ;

_door :
  return pRc ;  
}

/******************************************************************************/
/* create intiger value flag                                                  */
/******************************************************************************/
tIniVal* createIntValue( char* key, int value )
{ 
  tIniVal *this;
  tIniVal *pRc = NULL ;

  this = (tIniVal*) malloc( sizeof(tIniVal) ) ;
  if( this == NULL ) 
  {
    logger( LSTD_MEM_ALLOC_ERROR ) ;
    goto _door ;
  }
  
  this->nextVal = NULL ;
  this->type    = INTIGER ;
  this->key     = key ;
  this->value.intVal   = value ;
  
  pRc = this ;

_door :
  return pRc ;  
}

/******************************************************************************/
/* add value node                                                             */
/******************************************************************************/
int addValueNode( tIniNode* iniNode, tIniVal *value )
{
  tIniVal *p ;
  int sysRc = 0 ;

  p = iniNode->value ;
  if( p == NULL )
  {
    iniNode->value = value ;
    sysRc = 0 ;
    goto _door ;    // return ok
  }

  while( 1 )
  {
    if( strcmp( p->key, value->key ) == 0 )
    {
      logger( LSTD_INI_DUPLICATED_KEY, value->key ) ;
      sysRc = 1 ;
      goto _door ;
    }
    if( p->nextVal == NULL ) break ;
    p = p->nextVal ;
  }
 
  p->nextVal = value ; 

_door:
  return sysRc ;
}

/******************************************************************************/
/* add child node                                                             */
/******************************************************************************/
int addChildNode( tIniNode* parent, tIniNode* child )
{
  tIniNode *p ;
  int sysRc = 0 ;

  if( parent->childNode == NULL )
  {
    parent->childNode = child ;
    sysRc = 0 ;
    goto _door ;    // return ok
  }

  p = parent->childNode ;

  while( 1 )
  {
    if( p->nextNode == NULL ) 
    {
      p->nextNode = child ;
      break ;
    }
    p = p->nextNode ;
  }

_door:
  return sysRc ;
}

/******************************************************************************/
/* get node      */
/******************************************************************************/
tIniNode* getNode( tIniNode *anchor, char *filter )
{
  tIniNode* node = anchor ;

  char* singleFilter ;
  char* tag ;
  char* key ;
  char* val ;

  if( anchor == NULL ) node = mainIniAnchor ;
  if( node   == NULL ) goto _door ;

  singleFilter = shiftFilter( filter ) ; 
  tag = getFilterTag( singleFilter ) ;
  key = getFilterKey( singleFilter ) ;
  val = getFilterVal( singleFilter ) ;

  _door :

    return node ;
}

/******************************************************************************/
/* shift filter      */
/******************************************************************************/
const char* shiftFilter( char* filter ) 
{}

/******************************************************************************/
/* get Filter Tag      */
/******************************************************************************/
const char* getFilterTag( char* singleFilter ) 
{}

/******************************************************************************/
/* get Filter Key      */
/******************************************************************************/
const char* getFilterKey( char* singleFilter ) 
{}

/******************************************************************************/
/* get Filter Val      */
/******************************************************************************/
const char* getFilterVal( char* singleFilter ) 
{}

