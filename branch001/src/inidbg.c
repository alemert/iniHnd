/******************************************************************************/
/* ini handler debug features                                                */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <initypes.h>
#include <inihnd.h>

#include <msgcat/lgstd.h>
#include <ctl.h>

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define OFFSET "  "

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
void printNode( tIniNode *node, char* offset ) ;
// void printVal( tIniVal *val, char* offset )  ;

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*  print tree                                                                */
/******************************************************************************/
void fPrintTree( tIniNode *node, char* offset ) 
{
  char offsetSum[256] ;

  if( node == NULL ) 
  {
    printf( "%snull\n", offset ) ; 
    return ;
  }

  printNode( node, offset ) ;

  sprintf( offsetSum, OFFSET"%s",offset );
  if( node->childNode != NULL) fPrintTree( node->childNode, offsetSum ) ;

  if( node->tag == NULL )
  {
    printf( "%s<\\NULL>\n\n", offset ) ;
  }
  else
  {
    printf( "%s<\\%s>\n\n", offset, node->tag ) ;
  }

  if( node->nextNode != NULL ) fPrintTree( node->nextNode, offset ) ;
}

/******************************************************************************/
/* print node                                                                 */
/******************************************************************************/
void printNode( tIniNode *node, char* offset ) 
{

  if( node->tag == NULL )
  {
    printf( "%s<NULL>\n", offset ) ;
  }
  else
  {
    printf( "%s<%s>\n", offset, node->tag ) ;
  }

  if( node->value != NULL ) printVal( node->value, offset ) ;

}

/******************************************************************************/
/* print values                                                               */
/******************************************************************************/
void printVal( tIniVal *val, char* offset ) 
{

  if( val == NULL ) 
  {
    printf( OFFSET"(tIniVal*) NULL\n");
    goto _door ;
  }

  switch( val->type )
  {
    case STRING :
    {
      printf( OFFSET"%s%s = %s\n", offset, val->key, val->value.strVal ) ;
      break ;
    }
    case INTIGER :
    {
      printf( OFFSET"%s %s = %d\n", offset, val->key, val->value.intVal ) ;
      break ;
    }
    default :
    {
      break ;
    }
  }

  if( val->nextVal != NULL ) printVal( val->nextVal, offset ) ;

  _door :

  return ;
}

/******************************************************************************/
/* print cursor                                                               */
/******************************************************************************/
void printCursor( tCursorCfg *cursor )
{
  tCursorCfg *p = cursor ; 

  while( p != NULL )
  {
    printTree( p->iniNode ) ;
    p = p->nextCursor ;
  }
}
