//-----------------------------------------------------------------------------------------
//	MISC.CPP
//	Miscellaneous routines.
//-----------------------------------------------------------------------------------------

#include "stdafx.h"
#include "misc.h"

extern bool SimpleFindAndReplace( LPTSTR szSource, LPTSTR szFind, LPSTR szReplace )
{	
	int iStrLenSource  = lstrlen( szSource );
	int iStrLenFind    = lstrlen( szFind );
	int iStrLenReplace = lstrlen( szReplace );
	
	if( iStrLenFind != iStrLenReplace )
		return FALSE;
	
	LPTSTR psz 	    = szSource;
  	LPTSTR pszStart = szSource;
  	LPTSTR pszEnd   = szSource + iStrLenSource - iStrLenFind;

  	while( psz <= pszEnd )
	{
		if( !strncmp( psz, szFind, iStrLenFind ) )
		{
			memcpy( psz, szReplace, iStrLenReplace );
		}
			
		++psz;   	  		
	}	

	return TRUE;
};
	
extern int QtyOfNewLinesInString( LPCSTR lpsz )
{
	int iStrLen = lstrlen( lpsz );
	int iNewLineCount =0;
	LPCTSTR p1 = lpsz;
	LPCTSTR pEnd = lpsz + iStrLen;
	
	while( p1 != pEnd )
	{
		if( *p1 == '\n' )
			++iNewLineCount;
			
		++p1;
	}
	
	return iNewLineCount;
}