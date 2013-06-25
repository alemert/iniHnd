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
#define OPEN_INCL "<!include="

/******************************************************************************/
/*   T Y P E S                                                                */
/******************************************************************************/
typedef struct tagIniNode   tIniNode   ;
typedef struct tagIniVal    tIniVal    ;
typedef struct tagFileCfg   tFileCfg   ;
typedef struct tagCfgCursor tCursorCfg ;
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

struct tagFileCfg
{
  tIniNode *include ;
  tIniNode *main    ;
} ;

struct tagCfgCursor
{
  tIniNode   *iniNode ;
  tCursorCfg *nextCursor ;
} ;

/******************************************************************************/
/*   G L O B A L E S                                                          */
/******************************************************************************/
#ifdef C_MODULE_INI_HANDLER

  tIniNode *mainIniAnchor ;
  tIniNode *inclIniAnchor ;

#else

  extern tIniNode *mainIniAnchor ;
  extern tIniNode *inclIniAnchor ;

#endif

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
// inidbg.c
// ---------------------------------------------------------
#define printTree( pNode ) fPrintTree( pNode, "" )

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
  int iniReader( char* fileName, char **_iniMem ) ;
  char** getInclude( char *mem, int inclLev ) ;
  void freeFileName( char** _fileName ) ;
  char** uniqueFileName( char** fileName ) ;
  char* rmInclude( char *_mem ) ;

// ---------------------------------------------------------
// node.c
// ---------------------------------------------------------

  // -------------------------------------
  // constructor, set, add
  // -------------------------------------
  tIniNode* initIniNode( ) ;
  int       setIniTagName( tIniNode *node, const char* tag, int lng ) ;

  tIniVal* createStrValue( char* key, char* value ) ;
  tIniVal* createIntValue( char* key, int   value ) ;

  int addNode( tIniNode* this, tIniNode* next ) ;
  int addValueNode( tIniNode* iniNode, tIniVal *value ) ;
  int addChildNode( tIniNode* parent, tIniNode* child ) ;

  // -------------------------------------
  // get & search
  // -------------------------------------
  tIniNode* setIniSingleSearchNode( tIniNode* anchor, char* tag , 
                                                      char* key , 
                                                      char* sVal, 
                                                      int iVal  ) ;

  tCursorCfg* buildNodeCursor( tIniNode *anchor, tIniNode *search ) ;
  tIniVal * findValueNode( tIniVal* search, tIniVal *anchor ) ;
  tIniNode*  existsIniNode( tIniNode *_anchor, tIniNode *_search ) ;

  // -------------------------------------
  // compare
  // -------------------------------------
  int compareValueNode( tIniVal* a, tIniVal* b ) ;

  // -------------------------------------
  // desctuctor
  // -------------------------------------
  void freeValNode( tIniVal *val ) ;
  void freeIniNode( tIniNode *ini ) ;

// ---------------------------------------------------------
// precomp.c
// ---------------------------------------------------------
  char* precompile( const char* inMem ) ;
  int isIntiger( const char* mem) ;

// ---------------------------------------------------------
// inidbg.c
// ---------------------------------------------------------
  void fPrintTree( tIniNode *_node, char* offset ) ;
  void printVal( tIniVal *val, char* offset )  ;
  void printCursor( tCursorCfg *cursor ) ;

// ---------------------------------------------------------
// cursor.c
// ---------------------------------------------------------
  tCursorCfg* addCursorNode( tCursorCfg *_anchor, tCursorCfg *_next ) ;
  tCursorCfg* createCursorNode( tIniNode *_ini ) ;



