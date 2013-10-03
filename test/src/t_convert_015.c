/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*                                                                            */
/* testing functions :                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// std
// ---------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <errno.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <tutl.h>
#include <inihnd.h>
#include <initypes.h>

#include <ctl.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  sysRc = initLogging( "test/log/t_convert_015.log", INF ) ;
  if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    doPointTest( "basic test" , \
            RC_IS_NULL        , \
            str2arg           , \
            NULL, NULL        ) ;
  
    checkMessage( TEST_OK_TXT, str2arg ) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    char start[] = "\"qmgr\",\"name\",\"admt01\"" ;
    char *end = start + 22 ;

    doPointTest( "basic test" , \
            RC_NOT_NULL       , \
            str2arg           , \
            start, end        ) ;

    char** attr = (char**) gRcVoidPointer  ;

    printf("0 %s\n", attr[0] ) ;
    printf("1 %s\n", attr[1] ) ;
    printf("2 %s\n", attr[2] ) ;
  
    checkMessage( TEST_OK_TXT, str2arg ) ;
  }
#endif

  // -------------------------------------------------------
  // some test 
  // -------------------------------------------------------
#if(1)
  {
    char start[] = "\"qmgr\",\"name\",\"admt01\">" ;
    char *end = NULL ;

    doPointTest( "basic test" , \
            RC_NOT_NULL       , \
            str2arg           , \
            start, end        ) ;

    char** attr = (char**) gRcVoidPointer  ;

    printf("0 %s\n", attr[0] ) ;
    printf("1 %s\n", attr[1] ) ;
    printf("2 %s\n", attr[2] ) ;
  
    checkMessage( TEST_OK_TXT, str2arg ) ;
  }
#endif


 _door:
  return sysRc ;
}
