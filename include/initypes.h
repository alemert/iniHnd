/******************************************************************************/
/* ini file handler major header file                                         */
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

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   T Y P E S                                                                */
/******************************************************************************/
typedef struct tagIniNode tIniNode ;
typedef struct tagIniVal  tIniVal  ;

/******************************************************************************/
/*   S T R U C T S                                                            */
/******************************************************************************/
struct tagIniVal
{
  char    *key     ;
  int      intVal  ;
  char    *strVal  ;
  tIniVal *nextVal ;
} ;

struct tagIniNode
{
  char     *tag ;
  tIniNode *nextNode ; 
  tIniVal  *value ;
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
int ini2cfgHandleTag( char* iniMem, tIniNode *iniCfg ) ;
int ini2cfg( char* iniMem, tIniNode *iniCfg ) ;

// ---------------------------------------------------------
// node.c
// ---------------------------------------------------------
tIniNode* initIniNode( ) ;
int       setIniTagName( tIniNode *node, const char* tag, int lng ) ;

