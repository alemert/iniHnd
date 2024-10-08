/******************************************************************************/
/* change title on for new project                                            */
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
#include "main.h"

#include <inihnd.h>
#include <initypes.h>

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
/*                                  M A I N                                   */
/*                                                                            */
/******************************************************************************/
//#ifndef __TDD__

int main(int argc, const char* argv[] )
{
  int sysRc = 0 ;
  char * iniFile ;
  char * treeType ;
  char **filter ;
  char * key ;

  // -------------------------------------------------------
  // read and check command line attributes
  // -------------------------------------------------------
  sysRc = handleCmdLn( argc, argv ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // get ini file name from cmdln and read it
  // -------------------------------------------------------
  iniFile = getStrAttr( "ini" ) ;

  iniHandler( iniFile ) ;

  // -------------------------------------------------------
  // cmdln --all 
  // -------------------------------------------------------
  treeType = getStrAttr( "all" ) ;
  if(  treeType )
  {
    if( strcmp( treeType, "main" ) )
    {
      printTree( mainIniAnchor ) ;
      goto _door ;
    }
    if( strcmp( treeType, "include" ) )
    {
      printTree( mainIniAnchor ) ;
      goto _door ;
    }
  }

  // -------------------------------------------------------
  // cmdln --list
  // -------------------------------------------------------
  filter = getStrArrayAttr( "list" ) ;
  if(  filter )
  {
    printCursor( buildNodeCursor( NULL, setIniSearchNodeArray( filter ) ) ) ;
    goto _door ;
  }
  
  // -------------------------------------------------------
  // cmdln --path
  // -------------------------------------------------------
  filter = getStrArrayAttr( "path" ) ;
  if(  filter )
  {
    key = getStrAttr( "key" ) ;    
    printf( "%s\t:%s\n", 
            key, 
            iniStrValue(existsMainIniNode(setIniSearchNodeArray(filter)),key));
    
    goto _door ;
  }
  
_door :

  return sysRc ;
}

//#endif

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

