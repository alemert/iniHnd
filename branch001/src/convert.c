/******************************************************************************/
/* ini file handler - ini file reader                                         */
/*                                                                            */
/* functions:                                                                 */
/*   - getOpenTag                                                             */
/*   - getCloseTag                                                            */
/*   - getKey                                                                 */
/*   - getValueType                                                           */
/*   - getStrVal                                                              */
/*   - getIntVal                                                              */
/*   - tag2node                                                               */
/*   - val2node                                                               */
/*   - str2arg            */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <initypes.h>
#include <inihnd.h>

#include <msgcat/lgstd.h>
#include <ctl.h>

#include <genlib.h>

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
/* get tag type                                                               */
/******************************************************************************/
char* getOpenTag( char *mem, char **pTag )
{
  char* p = mem ;
  char* tag ;
  int loop = 1 ;
  int lng ;

  if( *p     != '<' ) { p = NULL ; goto _door ; }
  if( *(p+1) == '/' ) { p = NULL ; goto _door ; }

  while( loop )
  {
    switch( *p )
    {
      case '>'  :
      {
        loop = 0 ;
        break ;
      }
      case '\0' :
      {
        p = NULL ;
        goto _door ;
      }
      default :
      {
        p++ ;
        break ;
      }
    }
  }

  lng = p - mem - 1 ;
  tag = (char*) malloc( (lng+1) * sizeof(char) ) ;
  memcpy( tag, (mem+1), lng ) ;
  *(tag+lng) = '\0' ;
  *pTag = tag ;
  p++ ;

_door :
  return p ;
}

/******************************************************************************/
/* get close tag                                                              */
/******************************************************************************/
char* getCloseTag( const char *mem, const char *tag )
{
  char* p = (char*) mem ;
  int lng ;
  int loop ;
  char buff[1024] ;

  sprintf( buff, "</%s>", tag ) ;
  lng  = strlen(buff) ;

  loop = 1 ; 
  while( loop )
  {
    if( *p == '\0' )  { p = NULL ; goto _door ; } 
    if( memcmp( p, buff, lng ) == 0 ) loop = 0 ;
    p++ ;
  }

  p += lng -1 ;

_door :   

  return p ; 
}

/******************************************************************************/
/* get key out of key=value                                                   */
/******************************************************************************/
char *getKey( const char *mem, char **pKey )
{
  char* p = (char*) mem ;
  char *key ;
  int lng   ;

  switch( *p )
  {
    case '\0' :
    case '<'  :
    {
      goto _door ;
    }
    case '>'  :
    case '='  :
    {
      p = NULL ;
      goto _door ;
    }
    default :
    {
      break ;
    }
  }

  while( *p != '=' )
  {
    switch( *p )
    {
      case '"' : 
      case '>' : 
      case '<' : 
      case '\0' : 
      {
        p = NULL ;
        goto _door ;
      }
      default :
      {
        p++ ;
        break ;
      }
    }
  }

  lng = p - mem ;
  key = (char*) malloc( (lng+1) * sizeof(char) ) ;
  memcpy( key, mem, lng ) ;
  key[lng] = '\0' ;

  *pKey = key ;
  p++ ;

_door :

  return p ;
}

/******************************************************************************/
/* get value type                                                             */
/******************************************************************************/
tValType getValueType( char *mem )
{
  switch( *mem )
  {
    case '"' : return STRING  ;
    case '#' : return INTIGER ;
    default :  return UNKNOWN  ;
  }
}

/******************************************************************************/
/* get string value                                                           */
/******************************************************************************/
char *getStrVal( const char* mem, char** pValue )
{
  char *p = (char*) mem ;
  char *value ;
  int lng ;

  switch( *p )
  {
    case '"' : break ;
    default  : 
    {
      p = NULL ;
      goto _door ;
    } 
  }
  p++ ;

  while( *p != '"' )
  {
    switch( *p )
    {
      case '\0' :
      {
        p = NULL ;
        goto _door ;
      }
      default :
      {
        p++ ;
        break ;
      }
    }
  }

  lng = p - mem - 1 ;
  value = (char*) malloc( (lng+1) * sizeof(char) ) ; 
  memcpy( value, (mem+1), lng ) ;
  value[lng] = '\0' ;
  *pValue =  value ;

  p++ ; 
_door :
  return p ;  
}

/******************************************************************************/
/* get string value                                                           */
/******************************************************************************/
char *getIntVal( const char* mem, int *value )
{
  #define STR_LEN  32

  char *p = (char*) mem ;
  char strVal[STR_LEN] ;
  int lng ;

  switch( *p )
  {
    case '#' : break ;
    default  : 
    {
      p = NULL ;
      goto _door ;
    } 
  }
  p++ ;
 
  while( *p != '#' )
  {
    switch( *p )
    {
      case '\0' :
      {
        p = NULL ;
        goto _door ;
      }
      default :
      {
        p++ ;
        break ;
      }
    }
  }

  lng = p - mem - 1 ; 
  if( lng > (STR_LEN-1) ) 
  {
    p = NULL ;
    goto _door ;
  }

  memcpy( strVal, (mem+1), STR_LEN ) ;
  strVal[lng]='\0' ; 
  *value = atoi( strVal ) ;

  p++ ;
_door :
  return p ;
}

/******************************************************************************/
/* val to node                              */
/******************************************************************************/
tIniVal* val2node( char** mem )
{
  tIniVal *vNode = NULL ;

  char *key ;
  char *sVal ;
  int   iVal ;
  char *p = *mem ;

  p = getKey( p, &key ) ;

  switch( getValueType( p ) )
  {
    case INTIGER :
    {
      p = getIntVal( p, &iVal ) ;
      vNode = createIntValue( key, iVal ) ;
      break ;
    }
    case STRING  :
    {
      p= getStrVal(  p, &sVal ) ;
      vNode = createStrValue( key, sVal ) ;
      break ;
    }
    default      :
    {
      goto _door ;
    }
  }

_door:
  *mem = p ;
  return vNode ; 
}

/******************************************************************************/
/* create linked tree                                                      */
/******************************************************************************/
tIniNode* tag2node( char **_mem )
{
  char *tagStart ;
  char *tagEnd   ;
  tIniNode *cNode ;
  tIniNode *rcNode = NULL ;
  char *mem = *_mem ;

  if( mem == NULL ) goto _door ;
  // check if strlen(mem) is empty might be necessary
  char *tag ;

  tIniVal  *vNode ;

  tIniNode *pNode ;
  tIniNode *anchorNode = initIniNode() ;

  char *pMem = mem ;
  char *pEndStream ;
  char *pLink      ;
  char **search     ;

  int loop ;

  pNode = anchorNode ;

  loop = 1 ; 
  while( loop )                                 //                   |
  {                                             //                   v
    
    pLink = getLinkString( pMem ) ;             // 
handle link wie weiter unten
    tagStart = getOpenTag( pMem, &tag ) ;       // start of tag <tag>some
    if( tagStart == NULL )                      //
    {                                           //
      logger( LSTD_INI_OPEN_TAG_ERROR, mem ) ;  //
      rcNode = NULL ;                           //
      goto _door ;                              //
    }                                           //
    pMem = tagStart ;                           //                  |
                                                //                  v
    tagEnd = getCloseTag( tagStart, tag ) ;     // end of tag </tag>.
    if( tagEnd == NULL )                        //
    {                                           //
      logger( LSTD_INI_CLOSE_TAG_ERROR, tag );  //
      rcNode = NULL ;                           //
      goto _door ;                              //               | 
    }                                           //               v 
    pEndStream = tagEnd - strlen(tag) - 3 ;     // end of stream .</tag>
                                                //
    setIniTagName( pNode, tag, -1 ) ;           //
                                                //
    while( pEndStream != pMem )                 // go through a single tag
    {                                           //
      switch( *pMem )                           //
      {                                         //
        case '<' :                              // assume sub tag (child tag)
        {                                       //
          pLink = getLinkString( pMem ) ;       // check fot the link 
          if( pLink != NULL )                   //
          {                                     //
            pMem = getLinkEnd( pLink ) ;        //
            search = str2arg( pLink, pMem ) ;   //
            cNode = existsIniNode( NULL, setIniSearchNodeArray(search) ) ;
memory leak rc setIniSearch
            free( search ) ;                    //
            addChildNode( pNode, cNode ) ;      //
            continue ;                          //
          }                                     //
          cNode = tag2node( &pMem ) ;           //
          if( cNode == NULL )                   //
          {                                     //
            rcNode = NULL ;                     //
            goto _door ;                        //
          }                                     //
          addChildNode( pNode, cNode )  ;       //
          if( *tagEnd != '<' )                  // check if next tag is on the
          {                                     //  same level (is it also a 
            loop = 0 ;                          //  child node)
          }                                     //
          break ;                               //
        }                                       //
        default  :                              // assume key=value paar
        {                                       //  (of any type)
          vNode = val2node ( &pMem ) ;          //
          if( vNode == NULL ) goto _door ;      //
          addValueNode( pNode, vNode ) ;        //
        }                                       //
      }                                         //
    }                                           //
                                                //
    switch( *tagEnd )                           // 
    {                                           //
      case '<' :                                // start of some tag
      {                                         //
        if( *(tagEnd+1) == '/' )                // next tag is on higher level
        {                                       //
          loop = 0 ;                            //
        }                                       //
        else                                    // next tag is on same level
        {                                       //
handle link as a nexte node, wird wahrscheinlich gelöst am anfang der schleife
          pNode->nextNode = initIniNode() ;     //
          pNode = pNode->nextNode ;             //
          pMem = tagEnd ;                       //
        }                                       //
        break ;                                 //
      }                                         //
      case '\0' :                               // end of stream
      {                                         //
        loop = 0 ;                              //
        break ;                                 //
      }                                         //
      default :                                 // tag is follwed by some value
      {                                         //  which is on higher level
        loop = 0 ;                              //
        break ;                                 //
      }                                         //
    }                                           //
  }                                             //

  rcNode = anchorNode ;
  *_mem = tagEnd ;

_door :
  return rcNode ;
}

/******************************************************************************/
/*  string to arg                        */
/*                                        */
/*  description:                              */
/*    convert "qmgr","name","ADMT02" into char** = {"qmgr","name","ADMT02"}   */
/******************************************************************************/
char** str2arg( char *_start, char *_end )
{
  char *p ;
  char **arg ;
  int argv = 0 ;
  int argOpen = 0 ;
  int i ;

  char *start = _start ;
  char *end   = _end   ;

  if( start == NULL )
  {
    arg = NULL ; 
    goto _door ;
  }

  if( end == NULL )
  {
    end = getLinkEnd(start) ;
  }

  // -------------------------------------------------------
  // count ',' 
  // -------------------------------------------------------
  for( p=start; p<end; p++ )
  {
    switch( *p )
    {
      case '"' :
      {
        if( argOpen ) { argOpen = 0 ; }
        else          { argOpen = 1 ; }
        break ;
      }
      case ',' :
      {
        if( !argOpen ) { argv++ ; }
        break ;
      }
      case '\0' :
      {
        arg = NULL ;
        goto _door ;
      }
      default :
      {
        break ;
      }
    }
  }
  argv++ ;

  // -------------------------------------------------------
  // alloc argv, has to be freed outside this function
  // -------------------------------------------------------
  arg = (char**) malloc( sizeof(char*) * (argv+1) ) ;

  // -------------------------------------------------------
  // split the words
  // -------------------------------------------------------
  argOpen = 0 ;                   // init vara
  i = 0 ;                         //
                                  //
  for( p=start; p<end; p++ )      //
  {                               //
    switch( *p )                  //
    {                             //
      case '"' :                  // find out if it is an openening
      {                           //  or closing '"'
        if( argOpen )             // replace " by EO-String '\0' if closing '"'
        {                         //
          argOpen = 0 ;           //
          *p = '\0' ;             //
        }                         //
        else                      // it is an opening '"'
        {                         //
          argOpen = 1 ;           //
        }                         //
        break ;                   //
      }                           //
      default :                   //
      {                           //
        if( argOpen == 1 )        // set arg pointer to first char 
        {                         //   after opening "'"
          arg[i] = p ;            //
          argOpen = 2 ;           //
          i++ ;                   //
        }                         //
        break ;                   //
      }                           //
    }                             //
  }                               //
                                  //
  _door :

  return arg ;
}
