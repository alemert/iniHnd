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
typedef struct tagFileCfg tFileCfg ;
typedef union  tagValue   tVal     ;
typedef enum   tagValType tValType    ;

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

struct tagFileCfg
{
  tIniNode *include ;
  tIniNode *main    ;
} ;

/******************************************************************************/
/*   G L O B A L E S                                                          */
/******************************************************************************/

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
// ---------------------------------------------------------
// reader.c
// ---------------------------------------------------------

// ---------------------------------------------------------
// node.c
// ---------------------------------------------------------

// ---------------------------------------------------------
// general
// ---------------------------------------------------------

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
// ---------------------------------------------------------
// convert.c
// ---------------------------------------------------------
char* getOpenTag( char *mem, char **tag ) ;
char* getCloseTag( const char *mem, const char *tag ) ;
char *getKey( const char *mem, char **pKey ) ;
tValType getValueType( char *mem ) ;
char *getStrVal( const char* mem, char** value ) ;
char *getIntVal( const char* mem, int *value ) ;

tIniNode* tag2node( char** mem ) ;
tIniVal* val2node(  char** mem ) ;


// ---------------------------------------------------------
// reader.c
// ---------------------------------------------------------
int iniReader( const char* fileName, char **iniMem ) ;

#if(1)
char* iniHandleOpenTag( char* iniMem, tIniNode* iniCfg, int *rc ) ;
char* iniHandleCloseTag( char* iniMem, const char* tagName, int *rc ) ;
char* iniHandleValues( char    *startSubMem, 
                       char    *endSubMem  , 
                       tIniNode *iniCfg    ,
                       int      *rc       );
tIniNode* ini2cfg( char* iniMem, int *rc ) ;
char* ignWhiteChar( char *p) ;
#endif

// ---------------------------------------------------------
// node.c
// ---------------------------------------------------------
tIniNode* initIniNode( ) ;
int       setIniTagName( tIniNode *node, const char* tag, int lng ) ;

tIniVal* createStrValue( char* key, char* value ) ;
tIniVal* createIntValue( char* key, int   value ) ;

int addValueNode( tIniNode* iniNode, tIniVal *value ) ;
int addChildNode( tIniNode* parent, tIniNode* child ) ;

// ---------------------------------------------------------
// precomp.c
// ---------------------------------------------------------
char* precompile( const char* inMem ) ;
int isIntiger( const char* mem) ;

