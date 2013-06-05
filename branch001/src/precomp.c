/******************************************************************************/
/* ini file handler - ini file reader                                         */
/*                                                                            */
/* functions:                                                                 */
/*  - precompile                                                */
/*  - isIntiger                */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <initypes.h>
#include <inihnd.h>

#include <msgcat/lgstd.h>
#include <ctl.h>

#include <genlib.h>

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
/******************************************************************************/
char* precompile( const char* inMem )
{
  char *outMem = NULL ;

  char *pIn ;
  char *pOut ;

  int inLen  = strlen( inMem ) ;
  int outLen = 2 * countChar( inMem, '=' ) + inLen ;

  int copyFlag  ;
  int quoteFlag ;
  int intFlag   ;
  int commentFlag ;
  int commandFlag ;

  outMem = (char*) malloc( (outLen+1) * sizeof(char) ) ;
  if( outMem == NULL )
  {
    logger( LSTD_MEM_ALLOC_ERROR ) ;
    goto _door ;
  }
 
  outMem[outLen] = '\0' ;

  pIn  = (char*) inMem  ;
  pOut = outMem ;

  quoteFlag = 0 ;
  intFlag   = 0 ;
  commentFlag = 0 ;
  commandFlag = 0 ;

  while( *pIn != '\0' )
  {

    copyFlag = 0 ;

    switch( *pIn )
    {
      case ' '  : 
      case '\t' : 
      case '\n' : 
      {
        if( quoteFlag == 2 )
        {
          quoteFlag = 0 ;
          *pOut = '"' ;
          pOut++ ;
        }
        if( intFlag )
        {
          intFlag = 0 ;
          *pOut = '#' ;
          pOut++ ;
        }
        break ;
      }
      case '"'  :
      {
        quoteFlag = quoteFlag ?  0 : 1 ;
        copyFlag  = 1 ;
        break ;
      }
      case '<' :
      {
        if( memcmp( pIn, "<!--", strlen("<!--") ) == 0  )
        {
          commentFlag = 1 ;
          pIn += strlen( "<!--" ) - 1 ;
        }
        else
        {
          copyFlag = 1 ;
        }
        if( *(pIn+1) == '!' )
        {
          commandFlag = 1 ;
        }
        break ;
      }
      case '-' :
      {
        if( memcmp( pIn, "-->", strlen("-->") ) == 0  )
        {
          commentFlag = 0 ;
          pIn += strlen( "-->" ) - 1 ;
        }
        else
        {
          copyFlag = 1 ;
        }
        break ;
      }
      case '>' :
      {
        commandFlag = commandFlag ?  1 : 0 ;
        copyFlag = 1 ;
        break ;
      }
      default    :
      {
        copyFlag = 1 ;
        break ;
      }
    }

    if( quoteFlag )   copyFlag = 1 ;
    if( commentFlag ) copyFlag = 0 ;
    if( copyFlag  )
    {
      if( *(pOut-1) == '=' )
      {
        if( !commandFlag )
        {
          if( !quoteFlag   )
          {
            if( isIntiger( pIn ) > 0 )
            {
              *pOut = '#' ;
              pOut++ ;
              intFlag = 1 ;
            }
            else
            {
              *pOut = '"' ;
              pOut++ ;
              quoteFlag = 2 ;
            }
          }
        }
      }
      *pOut = *pIn ;
      pOut++ ;
    }
    pIn++ ;
  } 

  if( quoteFlag == 2 )
  {
    *pOut='"' ;
    pOut++ ;
  }
  if( intFlag )
  {
    *pOut = '#' ;
    pOut++ ;
  }
  *pOut='\0' ;

_door :

  return outMem ;

}

/******************************************************************************/
/* is initger           */
/******************************************************************************/

int isIntiger( const char* mem)
{
  int lng = 0 ;
  char *p = (char*) mem ;

  if( *p == '-' ) 
  {
    p++ ;
    lng++ ;
  }

  while( 1 )
  {
    switch( *p )
    {
      case '0' :
      case '1' :
      case '2' :
      case '3' :
      case '4' :
      case '5' :
      case '6' :
      case '7' :
      case '8' :
      case '9' :
      {
        lng++ ;
        break ;
      }
      case ' ' :
      case '\t' :
      case '\n' :
      case '\0' :
      {
        return lng ;
      }
      default :
      {
        return -1 ;
      }
    }
  p++ ;
  }
}
