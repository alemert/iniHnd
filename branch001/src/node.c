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
/*   - setIniSearchFilter                                    */
/*   - freeValNode                                                  */
/*   - freeIniNode                                                */
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
/* set ini tag name                                                           */
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
/* create string value tag                                                    */
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
/* get node                                            */
/******************************************************************************/
tIniNode* getNode( tIniNode *anchor, tIniNode *filter )
{
  tIniNode* node = anchor ;

  if( anchor == NULL ) node = mainIniAnchor ;
  if( node   == NULL ) goto _door ;

  _door :

    return node ;
}

/******************************************************************************/
/* set ini search filter                                  */
/******************************************************************************/
tIniNode* setIniSearchFilter( char* _tag    , 
                              char* _key    ,
                              char* _strVal ,
                              int   _intVal )
{
  tIniNode *filter ;

  char *strVal ;
  char *key ;

  int addRc = 0 ;

  if( _tag == NULL )
  {
    logger(
    filter = NULL ;
    goto _door ;
  }

  filter = initIniNode() ;

  setIniTagName( filter, _tag, -1 ) ;   // allocated by setIniTagName
                                        //
  if( _strVal != NULL )                 // key & strVal not allocated 
  {                                     //   by createStrValue
    key    = (char*) malloc ( sizeof(char) * (strlen(_key)   +1) ) ; 
    strVal = (char*) malloc ( sizeof(char) * (strlen(_strVal)+1) ) ; 
    strcpy( strVal, _strVal ) ;         // 
    strcpy( key   , _key    ) ;         // 
    addRc = addValueNode( filter, createStrValue( key, strVal ) ) ;
  }                                     // key not allocated by createIntValue
  else                                  //
  {                                     //
    key = (char*) malloc ( sizeof(char) * (strlen(_key)   +1) ) ; 
    strcpy( key, _key ) ;               // 
    addRc = addValueNode( filter, createIntValue( key, _intVal ) ) ;
  }

  if( addRc != 0 )
  {
    freeIniNode( filter ) ;
    filter = NULL ;;
    goto _door ;
  }

  _door :

  return filter ;
}

/******************************************************************************/
/* free value node                                          */
/******************************************************************************/
void freeValNode( tIniVal *val ) 
{
  if( val->nextVal != NULL )
  {
    freeValNode( val->nextVal ) ;
    val->nextVal = NULL ;
  }

  switch( val->type )
  {
    case INTIGER :
    {
      break ;
    }
    case STRING  :
    {
      if( val->value.strVal != NULL ) free( val->value.strVal ) ;
    }
    default :
    {
      break ;
    }
  }
  val->type = UNKNOWN ;
  
  free( val->key ) ;

  free( val ) ;

  return ;
} 

/******************************************************************************/
/* free ini node                                                */
/******************************************************************************/
void freeIniNode( tIniNode *ini )
{
  if( ini->childNode != NULL ) 
  {
    freeIniNode( ini->childNode ) ;
    ini->childNode = NULL ;
  }

  if( ini->nextNode != NULL  ) 
  {
    freeIniNode( ini->nextNode ) ;
    ini->nextNode = NULL ;
  }

  freeValNode( ini->value ) ;

  free( ini ) ;

  return ;
}
