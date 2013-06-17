/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  reader.c                                                                  */
/*                                                                            */
/* testing functions :                                                        */
/*   - iniReader                                                              */
/*   - iniHandleOpenTag                                                       */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// std
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <tutl.h>

#include <initypes.h>
#include <inihnd.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_reader_013.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test
  // -------------------------------------------------------
  doIntTest( "one incl file" , \
              0              , \
              iniHandler    ,
              "test/cfg/t_reader_013_000.ini" ) ;

  printf("\n == main == \n" );
  printTree( mainIniAnchor ) ;

  printf("\n == include == \n" );
  printTree( icnlIniAnchor ) ;
  printf("\n");

  checkMessage( TEST_OK_TXT, iniHandler ) ;
  
_door:
  return sysRc ;
}
