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

/******************************************************************************/
/*   T Y P E S                                                   */
/******************************************************************************/
typedef struct tagIniNode tIniNode ;

/******************************************************************************/
/*   S T R U C T S                                           */
/******************************************************************************/
struct tagIniNode
{
  char     *tag ;
  tIniNode *nextNode ; 
} ;

/******************************************************************************/
/*   G L O B A L E S                                                          */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

// ---------------------------------------------------------
// reader.c
// ---------------------------------------------------------
int iniReader( const char* fileName, char **iniMem ) ;
int ini2cfg( char* iniMem, tIniNode *iniCfg ) ;

// ---------------------------------------------------------
// node.c
// ---------------------------------------------------------
tIniNode* initIniNode( ) ;
int       setIniTagName( tIniNode *node, const char* tag, int lng ) ;
