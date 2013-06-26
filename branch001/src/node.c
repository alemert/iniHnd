/******************************************************************************/
/* change title on for new project                                            */
/*  functions                                                                 */
/*   - initIniNode                                                            */
/*   - setIniTagName                                                          */
/*   - createStrValue                                                         */
/*   - createIntValue                                                         */
/*   - adddNode                                                               */
/*   - addValueNode                                                           */
/*   - addChildNode                                                           */
/*   - setIniSingleSearchNode                                                 */
/*   - freeValNode                                                            */
/*   - freeIniNode                                                            */
/*   - buildNodeCursor                                                        */
/*   - compareValueNode                                                       */
/*   - existsIniNode                                                */
/*   - fSetIniSearchNode                          */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <string.h>
#include <stdarg.h>

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
/* add node                                                                   */
/******************************************************************************/
int addNode( tIniNode* this, tIniNode* next )
{
  tIniNode *p = this ;
  int sysRc = 0 ;

  if( next == NULL )
  {
    goto _door ;
  }

  if( this == NULL )
  {
    this = next ;
    goto _door ;
  }

  if( this->nextNode == NULL ) 
  {
    this->nextNode = next ;
    goto _door ;
  }

  while( p->nextNode != NULL )
  {
    p = p->nextNode ;
  }

  p->nextNode = next ; 

  _door :
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
/* set ini search filter                                                      */
/*                                                                            */
/*   set search filter, start searching at anchor                             */
/*   rules:                                                                   */
/*    anchor:                                                                 */
/*      if _anchor is NULL, top level search filter will be set               */
/*      if _anchor in not NULL, add filter to search filter                   */
/*                              (starting at _anchor, as a "linear" tree)     */
/*    tag:                                                                    */
/*      if tag is NULL, error, free complete tree                             */
/*    key:                                                                    */
/*      if key is NULL, tag will be set,                                      */
/*                      all tags on this level will be searched               */
/*    strVal:                                                                 */
/*      if strVal is not NULL, strVal is set as a filter                      */
/*      if strVal is NULL, _intVal is set as a filter                         */
/*      if strVal is "\0", a value to key is to be found                      */
/*    intVal:                                                                 */
/*      only if strVal is set to NULL, intVal will be set as a filter         */
/******************************************************************************/
tIniNode* setIniSingleSearchNode( tIniNode* _anchor ,
                                  char*     _tag    , 
                                  char*     _key    ,
                                  char*     _strVal ,
                                  int       _intVal )
{
  tIniNode *filter ;
  tIniNode *p ;

  char *strVal ;
  char *key ;

  int addRc = 0 ;

  if( _tag == NULL )
  {
    logger( LSTD_INI_TAG_NULL ) ;
    filter = NULL ;
    goto _door ;
  }

  filter = initIniNode() ;

  setIniTagName( filter, _tag, -1 ) ;   // allocated by setIniTagName
                                        //
  if( _key == NULL ) goto _door ;       //
                                        //
  if( _strVal != NULL )                 // key & strVal not allocated 
  {                                     //   by createStrValue
    key    = (char*) malloc ( sizeof(char) * (strlen(_key)   +1) ) ; 
    strVal = (char*) malloc ( sizeof(char) * (strlen(_strVal)+1) ) ; 
    strcpy( strVal, _strVal ) ;         // 
    strcpy( key   , _key    ) ;         // 
    addRc = addValueNode( filter, createStrValue( key, strVal ) ) ;
  }                                     // 
  else                                  // key not allocated by createIntValue
  {                                     //
    key = (char*) malloc ( sizeof(char) * (strlen(_key)   +1) ) ; 
    strcpy( key, _key ) ;               // 
    addRc = addValueNode( filter, createIntValue( key, _intVal ) ) ;
  }                                     //
                                        //
  if( addRc != 0 )                      //
  {                                     //
    freeIniNode( filter ) ;             //
    filter = NULL ;                     //
    goto _door ;                        //
  }                                     //
                                        //
  _door :                               //
                                        //
  if( filter == NULL )                  // error handling
  {                                     // ( filter could not be set )
    freeIniNode( _anchor ) ;            //
  }                                     //
                                        //
  if( _anchor != NULL )                 // function called with _anchor == NULL
  {                                     //   filter is anchor of the search tree
    p = _anchor ;                       // _anchor != NULL
    while( p->childNode != NULL )       //   add filter at the botom of the
    {                                   //   "linear" tree 
      p = p->childNode ;                //
    }                                   //
    p->childNode = filter ;             //
    filter = _anchor ;                  //
  }                                     //
                                        //
  return filter ;
}

/******************************************************************************/
/* free value node                                                            */
/******************************************************************************/
void freeValNode( tIniVal *val ) 
{
  if( val == NULL ) goto _door ;

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

  _door :

  return ;
} 

/******************************************************************************/
/* free ini node                                                              */
/******************************************************************************/
void freeIniNode( tIniNode *ini )
{
  if( ini == NULL ) goto _door ;

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

  _door :

  return ;
}


/******************************************************************************/
/* find node                                                                  */
/******************************************************************************/
tCursorCfg* buildNodeCursor( tIniNode *_anchor, tIniNode *_search )
{
  tIniNode *iNode ;
  tIniNode *search ;
  tIniVal  *vNode  ;
  tCursorCfg *cursor = NULL ;
  tCursorCfg *rcNode ;

  iNode = _anchor ;                                // check and init 
  if( _anchor == NULL )                            //   function arguments
  {                                                //
    iNode = mainIniAnchor ;                        //
  }                                                //
  if( iNode == NULL )                              //
  {                                                //
    cursor = NULL ;                                //
    goto _door ;                                   //
  }                                                //
                                                   //
  if( _search == NULL )                            //
  {                                                //
    cursor = NULL ;                                //
    goto _door ;                                   //
  }                                                //
  search = _search ;                               //
                                                   //
  while( iNode != NULL )                           //
  {                                                //
    if( strcmp( search->tag, iNode->tag ) == 0 )   // compare tags on this level
    {                                              //
      vNode = findValueNode( search->value ,       // check if searchd value is 
                             iNode->value ) ;      //   attached to this node
                                                   //
      if( vNode != NULL )                          // if node found 
      {                                            //   (on this level)
        if( search->childNode == NULL )            //
        {                                          // check if recrusive search 
          if( cursor == NULL )                     //
          {                                        //
            cursor = createCursorNode( iNode ) ;   //
          }                                        //
          goto _door ;                             // if not, found, return
        }                                          //
                                                   //
        if( iNode->childNode == NULL )             // check if recrusive search
        {                                          //   is possible
          cursor = NULL ;                          //
          goto _door ;                             //
        }                                          //
                                                   //
        rcNode=buildNodeCursor( iNode->childNode,  // recrusive search
                                search->childNode);//
        cursor = addCursorNode( cursor, rcNode ) ; //
                                                   //
      }                                            //
    }                                              //
    iNode = iNode->nextNode ;                      // move to next node on 
  }                                                //   same level
                                                   //
  _door :

  return cursor ;
}

/******************************************************************************/
/* find node                                                                  */
/******************************************************************************/
tIniVal * findValueNode( tIniVal *_search, tIniVal *_anchor ) 
{
  tIniVal *result ;

  if( _search == NULL ) 
  {
    result = NULL ;
    goto _door ;
  }

  if( compareValueNode( _search, _anchor ) == 0 )
  {
    result = _anchor ;
    goto _door ;
  }

  if( _anchor->nextVal == NULL) 
  {
    result = NULL ;
    goto _door ;
  }

  result = findValueNode( _search, _anchor->nextVal ) ;

  _door :
  
  return result ;
}

/******************************************************************************/
/* comapre value nodes                                             */
/******************************************************************************/
int compareValueNode( tIniVal* a, tIniVal* b )
{
  int rc = 0 ;

  if( a == NULL ) { rc = -1 ; goto _door ; }
  if( b == NULL ) { rc = -1 ; goto _door ; }

  if( a->type != b->type ) { rc = 1 ; goto _door ; }

  if( a->key == NULL ) { rc = -1 ; goto _door ; }
  if( b->key == NULL ) { rc = -1 ; goto _door ; }

  if( strcmp( a->key, b->key ) != 0 )
  {
    rc = 1 ;
    goto _door ;
  }

  switch( a->type )
  {
    case INTIGER :
    {
      if( a->value.intVal == b->value.intVal )
      {
        rc = 0 ; 
        goto _door ;
      }
    }
    case STRING  :
    {
      if( a->value.strVal == NULL ) { rc = -1 ; goto _door ; }
      if( b->value.strVal == NULL ) { rc = -1 ; goto _door ; }
      if( strcmp( a->value.strVal, b->value.strVal ) == 0 )
      {
        rc = 0 ; 
        goto _door ;
      }
    }
    case UNKNOWN :
    {
      rc = -1 ; 
      goto _door ; 
    }
  }

  _door :

  return rc ;
}

/******************************************************************************/
/* exists ini node                                  */
/******************************************************************************/
tIniNode*  existsIniNode( tIniNode *_anchor, tIniNode *_search )
{
  tIniNode *result = NULL ;
  tIniNode *search ;
  tIniNode *iNode ;

  tIniVal *vNode ;

  iNode = _anchor ;                             //
  if( iNode == NULL ) iNode=inclIniAnchor ;     //
  if( iNode == NULL ) goto _door ;              //
                                                //
  search = _search ;                            //
  if( search == NULL ) goto _door ;             //
                                                //
  while( iNode != NULL )                        //
  {                                             //
    if( strcmp(iNode->tag,search->tag) == 0 )   //
    {                                           //
      vNode = findValueNode( iNode->value  ,    //
                             search->value );   //
      if( vNode != NULL )                       //
      {                                         //
        if( search->childNode == NULL )         //
        {                                       //
          result = iNode ;                      //
          goto _door ;                          //
        }                                       //
        result=existsIniNode(iNode->childNode  ,//
                             search->childNode);//
        if( result != NULL ) goto _door ;       //
      }                                         //
    }                                           //
    iNode = iNode->nextNode ;                   //
  }                                             //
                                                //
  _door :

  return result ;
}

/******************************************************************************/
/* create ini search node                               */
/*                                                              */
/*   description:                                                */
/*     this function convert string search attributes to the iniNode search   */
/*     structure. it is an interface to setIniSearchFilter which only set     */
/*     one search node.                                                 */
/******************************************************************************/
tIniNode* fSetIniSearchNode( int cnt , ... )
{
  tIniNode *pNode ;   
  tIniNode *result = NULL ;   

  va_list argp ;
  char *arg[3] ;

  int i,j ;

  if( cnt == 0 )                             // check if result empty
  {                                          //
    result = NULL ;                          //
    goto _door ;                             //
  }                                          //
                                             //
  if( (cnt % 3) > 0 )                        // check for <tag> key=value </tag>
  {                                          //             ^    ^    ^
    result = NULL ;                          //             |    |    |
    logger(LSTD_INI_SEARCH_STR_CNT_ERR);     //             1    2    3
    goto _door ;                             //
  }                                          //
                                             //
  va_start( argp, cnt ) ;                    // init va_arg
                                             //
  for( i=0; i<cnt; i+=3 )                    // handle one complete 
  {                                          //   troika (tag,key,value)
    for( j=0; j<3; j++ )                     //
    {                                        //
      arg[j] = va_arg( argp, char* ) ;       //
      if( arg[j] == NULL )                   //
      {                                      //
        logger(LSTD_INI_SEARCH_STR_CNT_ERR); //
      }                                      //
    }                                        //
    result = setIniSingleSearchNode( result, //
                                     arg[0], // <tag>
                                     arg[1], // key
                                     arg[2], // value
                                     0    ); // (intiger dummy)
  }                                          //
                                             //
  _door :     

  return result ;
}

