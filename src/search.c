/******************************************************************************/
/*   I N I   H A N D L E R                         */
/*                                                                */
/*  description:                                    */
/*    get information from ini files                  */
/*                                */
/*  functions:                      */
/*    - getIniNode            */
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
#include <inihnd.h>
#include <initypes.h>

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
/* get ini node for absolute node path            */
/******************************************************************************/
tIniNode* getIniNode( char* first, ... )
{
  logger( LSYS_FUNC_ENTRY ) ;

  tIniNode *node  = NULL ;
  tIniNode *found = NULL ;

  char *tag =first ;

  if( tag == NULL ) goto _door ;

  node = mainIniAnchor ;

  va_list list;
  va_start( list, first );

  tag = first ;

  while( tag && node )
  {
    if( strcmp( tag, node->tag) == 0 )
    {
      tag = va_arg( list, char*) ;
      found = node ;
      node = node->childNode ;
      continue ;
    }
    else
    {
      node = node->nextNode ;
    }
  }

  _door :

  va_end( list );
  logger( LSYS_FUNC_EXIT ) ;
  return found ;
}


/******************************************************************************//* get next ini node            */
/******************************************************************************/
tIniNode* getNextIniNode( tIniNode* anchor, ... )
{
  logger( LSYS_FUNC_ENTRY ) ;

  tIniNode *node  = anchor ;
  tIniNode *found = NULL ;

  va_list list;
  va_start( list, anchor );

  char *nextTag = va_arg( list, char*) ;
  char *tag = nextTag ;

  while( nextTag )
  {
    tag = nextTag ;
    nextTag = va_arg( list, char*) ;
  }

  if( strcmp( tag, node->tag ) != 0 ) 
  {
    goto _door ;
  }

  node = node->nextNode ;
  while( node )
  {
    if( strcmp( node->tag, tag ) == 0 ) 
    {
      found = node ;
      break ;
    }
    node = node->nextNode ;
  }

  _door :

  va_end( list );
  logger( LSYS_FUNC_EXIT ) ;
  return found ;
}


/******************************************************************************//* get next ini node            */
/******************************************************************************/
