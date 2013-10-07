/******************************************************************************/
/* ini file handler major header file                                         */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdlib.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <msgcat/lgstd.h>
#include <ctl.h>

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define  A_MAIN     1
#define  A_INCLUDE  2
#define  A_FREE     3

/******************************************************************************/
/*   T Y P E S                                                                */
/******************************************************************************/
typedef struct tagIniNode   tIniNode   ;
typedef struct tagIniVal    tIniVal    ;
typedef union  tagValue     tVal       ;
typedef enum   tagValType   tValType   ;

/******************************************************************************/
/*   S T R U C T S                                                            */
/******************************************************************************/
enum tagValType { UNKNOWN, STRING, INTIGER } ;

union tagValue
{
  char* strVal ;
  int   intVal ;
} ;

struct tagIniVal
{
  char      *key  ;
  tVal      value ;
  tValType  type  ;
  tIniVal   *nextVal ;
} ;

struct tagIniNode
{
  char     *tag ;
  tIniNode *nextNode ;
  tIniVal  *value ;
  tIniNode *childNode ;
} ;

/******************************************************************************/
/*   G L O B A L E S                                                          */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
#define existsInclIniNode( search   ) existsIniNode( A_INCLUDE, NULL  , search )
#define existsMainIniNode( search   ) existsIniNode( A_MAIN,    NULL  , search )
#define findIniNode( anchor, search ) existsIniNode( A_FREE,    anchor, search )

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
int iniHandler( const char *mainCfg ) ;
tIniNode*  existsIniNode( int anchorType    ,
                          tIniNode *_anchor ,
                          tIniNode *_search ) ;
char* iniStrValue( tIniNode *iniNode, char* key ) ;

tIniNode* getIniNode( char* first, ... );
tIniNode* getNextIniNode( tIniNode* anchor, ... );
char* getIniStrValue( tIniNode *node, const char *key );
int* getIniIntValue( tIniNode *node, const char *key );
tValType getIniTypeValue( tIniVal *val );

