// ImportD3Acc.cpp: implementation of the CImportD3Acc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "ImportD3Acc.h"
#include "math.h"

#include "bigini.h"

extern bool SimpleFindAndReplace( LPSTR szSource, LPSTR szFind, LPSTR szReplace );

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImportD3Acc::CImportD3Acc()
{
	this->Reset();
}

CImportD3Acc::~CImportD3Acc()
{
//	this->Free();
}

//////////////////////////////////////////////////////////////////////
void CImportD3Acc::Reset( void )
	{
	this->m_szDataEntryCode =_T("");
	this->m_szDrawingNumber =_T("");
	this->m_szComment		=_T("");
	this->m_szDate			=_T("");
	this->m_szType			=_T("");
	this->m_szMark			=_T("");
	this->m_iQty			=1;

	this->m_iDimA			=0;
	this->m_iDimB			=0;
	//this->m_iDimC			=0;
	//this->m_iDimE			=0;
	//this->m_iDimF			=0;
	this->m_iDimG			=0;
	this->m_iDimH			=0;
	//this->m_iDimJ			=0;
	this->m_iSleeveLength	=0;
	this->m_iCleatEndDim	=0;

	m_iSlope=m_iCentres=m_iDimX=m_iSheetLine=m_iCleatHoleCentres = 0;
	
	for( short i=0; i<5; ++i )
		{
		this->m_iField[i] =0;
		}
	} 

//////////////////////////////////////////////////////////////////////
/*void CImportD3Acc::Free( void )
{	
	CImportD3Acc* pAcc;

	while(!m_listImportD3Acc.IsEmpty())
	{
		pAcc = m_listImportD3Acc.GetTail();
		pAcc = m_listImportD3Acc.RemoveTail
		delete pAcc;
	}
}
*/

//-----------------------------------------------------------------------------------------
BOOL CImportD3Acc::CheckValid( void )
{
//debug
	return TRUE;
}


//---------------------------------------------------------------------------
//	Procedure:	Copy()		Copy this object into target.
/*
	Design:
*/
//---------------------------------------------------------------------------
/*
void CImportD3Acc::Copy(CImportD3Acc* pTarget)
{
	pTarget->SetType((LPCTSTR) this->m_szType);
	pTarget->SetMark((LPCTSTR) this->m_szMark);
	pTarget->SetQty(this->m_iQty);	
	
	for(short i=0; i<5; ++i)
	{
		pTarget->SetField( i, this->m_iField[i] );
	}
}	
*/

//----------------------------------------------------------------------------
//	Procedure:	SetDateToday()	Set date stamp to todays date.
/*
	Design:

	compute current time/date
	build date string
	assign date
*/
//----------------------------------------------------------------------------
void CImportD3Acc::SetDateToday( void )
{
  //compute current time/date
	time_t osBinaryTime;
	time( &osBinaryTime ) ;
	CTime TimeNow( osBinaryTime );
	TimeNow.GetCurrentTime();
	
  //build date string
	int iDay = TimeNow.GetDay();
	int iMonth = TimeNow.GetMonth();
	int iYear = TimeNow.GetYear();

	char szBuffer[80];
	wsprintf( (LPSTR)szBuffer, "%i/%i/%i", iDay, iMonth, iYear );	
	
  //assign date
	this->m_szDate =szBuffer;
}



    

/*----------------------------------------------------------------------------
BOOL CImportD3AccList::DeleteRecord( CImportD3Acc* pAccessory )
{

	POSITION p =this->FindRecord( pAccessory );
	if( p )
	{
		this->RemoveAt( p );
		delete pAccessory;
		return TRUE;
	}
    
    return FALSE;
}
*/

//----------------------------------------------------------------------------
//	Procedure:	ItemMarkExists()	Test if item mark is in accessory list.
//	Returns 	TRUE/FALSE indicating if item is in accessory list
/*
	Design:
	
	find accessory in list
	if accessory found	
		return success
			
	return failure
*/
/*----------------------------------------------------------------------------
BOOL CImportD3AccList::ItemMarkExists( LPCSTR lpszTestMark )
{
  //find accessory in list
  	CImportD3Acc* pRecord =this->FindRecord( lpszTestMark );
  	
  //if accessory found	
  	if( pRecord!=NULL )
  	{
	  //return success
	  	return TRUE;
  	}
			
  //return failure
  	return FALSE;
}    
*/	

//---------------------------------------------------------------------------
//	Procedure:	Copy()		Copy this object marked as specified into target.
/*
	Design:
	
	find accessory by itemmark
	if accessory found
		then copy accessory attributes into target
		return success
	                  
	return failure	                  
*/
/*---------------------------------------------------------------------------
BOOL CImportD3AccList::Copy( CImportD3Acc* pTarget, LPCSTR lpszTestMark )
	{
  //find accessory by itemmark
  	CImportD3Acc* pRecord =this->FindRecord( lpszTestMark );
  	
  //if accessory found
  	if( pRecord!=NULL )
  		{
	  //then copy accessory attributes into target
	  	pRecord->Copy( pTarget );
	  	
	  //return success
	  	return TRUE;
	  	}
	                  
  //return failure	                  
  	return FALSE;
	}	
*/

//----------------------------------------------------------------------------
//	Procedure:	Find()	Test if item mark is in accessory list.
//	Returns 	TRUE/FALSE indicating if item is in accessory list
/*
	Design:
	
	for each mark in list
		if test mark = this mark
			return accessory
			
	return null
*/
/*----------------------------------------------------------------------------
CImportD3Acc* CImportD3AccList::FindRecord( LPCSTR lpszTestMark )
{
  //for each mark in list
  	POSITION p =this->GetHeadPosition();
  	while( p )
	{
  	  	CImportD3Acc* pRecord =(CImportD3Acc*)this->GetNext( p );
  	  	
  	  //if test mark = this mark
  	  	if( !lstrcmp( pRecord->GetMark(), lpszTestMark ) )
  		{
		  //return existance
		  	return pRecord;
	  	}
	}
			
  //return non existance
  	return NULL;
}    
*/

//----------------------------------------------------------------------------
//	Procedure:	GetIndex()	return zero based index of object in list.
/*
	Design:
	
	for each object in list
		if test object = this object
			return index
			
	return 0
*/
/*----------------------------------------------------------------------------
int CImportD3AccList::GetIndex( CImportD3Acc* pThisAccessory )
{
	int iIndex =0;
	
	POSITION p = this->GetHeadPosition();
  //for each object in list
	while( p )
	{
		CImportD3Acc* pTestObject =(CImportD3Acc*)this->GetNext( p );

      //if test object = this object
		if( pTestObject == pThisAccessory )
		{		
		  //return index
		  	return iIndex;
		}

		++iIndex;
	}
			
	//return 0
	return 0;
}
*/

//----------------------------------------------------------------------------
//	Procedure:	IsHead()	Test for first accessory
/*
	Design:
*/
/*----------------------------------------------------------------------------
BOOL CImportD3AccList::IsHead( CImportD3Acc* pAccessory )
{
  	if( pAccessory==NULL )
  		return -1;
  	
  	if( this->IsEmpty() ||
  		pAccessory != ( CImportD3Acc* )this->GetHead() )
  		{
	   		return FALSE;
   		}
	else
		{
			return TRUE;
		}
}
*/

	
	
//----------------------------------------------------------------------------
//	Procedure:	IsTail()	Test for lst accessory
/*
	Design:
*/
/*----------------------------------------------------------------------------
BOOL CImportD3AccList::IsTail( CImportD3Acc* pAccessory )
{
  	if( pAccessory==NULL )
  		return -1;
  	
  	if( this->IsEmpty() ||
  		pAccessory != ( CImportD3Acc* )this->GetTail() )
   		{
	   		return FALSE;
   		}
	else
		{
			return TRUE;
		}
}
*/


//----------------------------------------------------------------------------
//	Procedure:	Write()	Write accessory list to target.
/*
	Design:
*/
/*----------------------------------------------------------------------------
BOOL CImportD3AccList::WriteAccList( CBigIni& ABigIni )
{

	POSITION p =this->GetHeadPosition();
	int iIndex = 0;
	while( p )
	{
		CImportD3Acc* pAccessory = (CImportD3Acc*)this->GetNext( p );
		pAccessory->Write( ABigIni, iIndex );
		++iIndex;
	}

	return TRUE;
}
*/


//----------------------------------------------------------------------------
//	Procedure:	Read()	Read accessory list from source.
/*
	Design:
*/
/*----------------------------------------------------------------------------
BOOL CImportD3AccList::ReadAccList( CBigIni& ABigIni )
{
    int iIndex = 0;
	
	do
	{	
	    CImportD3Acc* pNewAccessory = new CImportD3Acc();
	
		if( pNewAccessory->Read( ABigIni, iIndex ) == TRUE )
		{
			this->AddTail( pNewAccessory );
			++iIndex;
		}
		else
		{
			delete pNewAccessory;
			break;
		}
		
	}
	while( TRUE );


	if( iIndex == 0 )
		return FALSE;

	return TRUE;
}
*/


//----------------------------------------------------------------------------
//	Procedure:	Write()	Write accessory to target.
/*
	Design:

	write:				
		DrawingNumber
		Comment
		Date
		Type
		Mark
		Qty
		DataEntryCode
		Fields
*/
//----------------------------------------------------------------------------
BOOL CImportD3Acc::Write( CBigIni& ABigIni, int iAccessoryIndex )
{
	CString szText = _T("");
	CString szEntry = _T("");
	CString szSection = _T("");
	
	szSection.Format( "Accessory#%i", iAccessoryIndex );

  //DrawingNumber
	szEntry = "DrawingNumber";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szDrawingNumber );	

  //Comment
	//if( this->m_szComment.GetLength() != 0 )
	{
   	  //WritePrivateProfileString ignors \r\n pairs,
   	  //so translate /r/n pairs to ~~
   	  	CString szCopyOfComment = this->m_szComment;
		SimpleFindAndReplace( (LPSTR)(const char*)szCopyOfComment, "\r\n", "~~" );
		szEntry = "Comment";
		ABigIni.WritePrivateProfileString( szSection, szEntry, szCopyOfComment );	
	}

  //Date
	szEntry = "Date";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szDate );	

  //Type
	szEntry = "Type";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szType );	

  //Mark
	szEntry = "Mark";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szMark );	

  //iQty 
	szEntry = "Quantity";
   	szText.Format( "%i", this->m_iQty );
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	

  //cleat end dim
	szEntry = "CleatEndDim";
	if(m_iCleatEndDim > 0)
	{
   		szText.Format( "%i", this->m_iCleatEndDim );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //sleeve length
	if( m_iSleeveLength != 0 )
	{
		szEntry = "SleeveLength";
	   	szText.Format( "%i", this->m_iSleeveLength );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
   	}

  //DimA
	if(m_iDimA > 0)
	{
		szEntry = "DimensionA";
   		szText.Format( "%i", this->m_iDimA );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimB
	if(m_iDimB > 0)
	{
		szEntry = "DimensionB";
   		szText.Format( "%i", this->m_iDimB );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

/* //DimC
	szEntry = "DimensionC";
   	szText.Format( "%i", this->m_iDimC );
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	

  //DimE
	szEntry = "DimensionE";
   	szText.Format( "%i", this->m_iDimE );
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	

  //DimF
	szEntry = "DimensionF";
   	szText.Format( "%i", this->m_iDimF );
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
*/
  //DimG	
	if(m_iDimG > 0)
	{
		szEntry = "DimensionG";
   		szText.Format( "%i", this->m_iDimG );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimH
	if(m_iDimH > 0)
	{
		szEntry = "DimensionH";
   		szText.Format( "%i", this->m_iDimH );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

/* //DimJ
	szEntry = "DimensionJ";
   	szText.Format( "%i", this->m_iDimJ );
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
*/
  //DataEntryCode
	szEntry = "DataEntryCode";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szDataEntryCode );	

	// ProductType
	szEntry = "ProductType";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szProductType );

	// SectionType
	szEntry	= "SectionType"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szSectionType );

	// SectionSize
	szEntry	= "SectionSize"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szSectionSize );

	// ProductName
	szEntry	= "ProductName"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szProductName );

	// Slope
	if(m_iSlope > 0)
	{
		szEntry	= "Slope"; 
		szText.Format("%i", m_iSlope);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText);
	}

	// Centres
	if(m_iCentres > 0)
	{
		szEntry	= "Centres"; 
		szText.Format("%i", m_iCentres);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText);
	}

	// DimX
	if(m_iDimX > 0)
	{
		szEntry	= "DimensionX"; 
		szText.Format("%i", m_iDimX);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText);
	}

	// Sheet line
	if(m_iSheetLine > 0)
	{
		szEntry	= "SheetLine"; 
		szText.Format("%i", m_iSheetLine);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText);
	}

	// CleatHoleCentres
	if(m_iCleatHoleCentres > 0)
	{
		szEntry	= "CleatHoleCentres"; 
		szText.Format("%i", m_iCleatHoleCentres);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText);
	}

  //Fields
   	for( int iFieldIndex = 0; iFieldIndex < 5; ++iFieldIndex )
	{
		if(m_iField[iFieldIndex] > 0)
		{
			szEntry.Format( "Field#%i", iFieldIndex );
	   		szText.Format( "%i", this->m_iField[iFieldIndex] );
			ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
		}
   	}

	return TRUE;
}


//----------------------------------------------------------------------------
//	Procedure:	Read()	read accessory from target.
/*
	Design:

	read:				
		DrawingNumber
		Comment
		Date
		Type
		Mark
		Qty
		DataEntryCode
		Fields
*/
//----------------------------------------------------------------------------
bool CImportD3Acc::Read( CBigIni& ABigIni, int iAccessoryIndex )
{
	CString szSection = _T("");
	CString szDefault = ""; 
	CString szEntry = _T("");
	CString szReturnBuffer = _T("");

	szSection.Format( "Accessory#%i", iAccessoryIndex );

  //DrawingNumber
	szEntry	= "DrawingNumber"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDrawingNumber = szReturnBuffer;
	if( this->m_szDrawingNumber.GetLength() == 0 )
		return FALSE;

  //Comment
	szEntry	= "Comment"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szComment = szReturnBuffer;
	SimpleFindAndReplace( (LPSTR)(const char*)m_szComment, "~~", "\r\n" );

  //Date
	szEntry	= "Date"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDate = szReturnBuffer;

  //Type
	szEntry	= "Type"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szType = szReturnBuffer;

  //Mark
	szEntry	= "Mark"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szMark = szReturnBuffer;
	// Strip any underscores found in the mark number
	m_szMark.Replace(_T("_"), _T("#"));

  //iQty 
	szEntry	= "Quantity"; 
	this->m_iQty = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //cleat end dim
	szEntry	= "CleatEndDim"; 
	this->m_iCleatEndDim = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //sleeve length
	szEntry	= "SleeveLength"; 
	this->m_iSleeveLength = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimA
	szEntry	= "DimensionA"; 
	this->m_iDimA = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimB
	szEntry	= "DimensionB"; 
	this->m_iDimB = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

/* //DimC
	szEntry	= "DimensionC"; 
	this->m_iDimC = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimE
	szEntry	= "DimensionE"; 
	this->m_iDimE = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimF
	szEntry	= "DimensionF"; 
	this->m_iDimF = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
*/
  //DimG		
	szEntry	= "DimensionG"; 
	this->m_iDimG = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimH
	szEntry	= "DimensionH"; 
	this->m_iDimH = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

/* //DimJ
	szEntry	= "DimensionJ"; 
	this->m_iDimJ = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
*/
  //DataEntryCode
	szEntry	= "DataEntryCode"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDataEntryCode = szReturnBuffer;

	// ProductType
	szEntry	= "ProductType"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szProductType = szReturnBuffer;

	// SectionType
	szEntry	= "SectionType"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szSectionType = szReturnBuffer;

	// SectionSize
	szEntry	= "SectionSize"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szSectionSize = szReturnBuffer;

	// ProductName
	szEntry	= "ProductName"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szProductName = szReturnBuffer;

	// Slope
	szEntry	= "Slope"; 
	this->m_iSlope = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	// Centres
	szEntry	= "Centres"; 
	this->m_iCentres = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	// DimX
	szEntry	= "DimensionX"; 
	this->m_iDimX = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	// Sheet line
	szEntry	= "SheetLine"; 
	this->m_iSheetLine = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	// CleatHoleCentres
	szEntry	= "CleatHoleCentres"; 
	this->m_iCleatHoleCentres = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Fields
   	for( int iFieldIndex = 0; iFieldIndex < 5; ++iFieldIndex )
	{
		szEntry.Format( "Field#%i", iFieldIndex );
		this->m_iField[iFieldIndex] = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
   	}

	return TRUE;
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
LPCSTR CImportD3Acc::szComputeDimensionFromScript( LPSTR lpszSource )
{
	static char szBuffer[256];

	int iDimension = this->IntComputeDimensionFromScript( lpszSource );
	wsprintf( szBuffer, "%i", iDimension  );

  //default, return source
	return (LPCSTR)szBuffer;
}


//-----------------------------------------------------------------------------------------
/*	Design:

	for all tokens
		compute token length
		translate token
		seek to next token
	return dimension
*/
//-----------------------------------------------------------------------------------------
int CImportD3Acc::IntComputeDimensionFromScript( LPSTR lpszSource )
{
	LPSTR p 		  		= lpszSource;
	int iStringLength 		= lstrlen( lpszSource );
	int iCurrentDim   		= 0;
	int iTokenLength  		= 0;
	int iTokenTranslation	= 0;
	char szThisToken[80] 	= "";
	
  //for all tokens
	while( iStringLength > 0 )
	{
	  //compute token length
		iTokenLength = 0;
		LPSTR pszTemp = p;
		while( *pszTemp != 0 && *pszTemp!=',' )
		{
			++pszTemp;
			++iTokenLength;
		}

	  //translate token
		lstrcpyn( szThisToken, p, iTokenLength +1 );			
		
		if( !lstrcmp( szThisToken, "+Field1" ) )
		{
			iTokenTranslation = this->m_iField[0];
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Field2" ) )
		{
			iTokenTranslation = this->m_iField[1];
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Field3" ) )
		{
			iTokenTranslation = this->m_iField[2];
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Field4" ) )
		{
			iTokenTranslation = this->m_iField[3];
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Field5" ) )
		{
			iTokenTranslation = this->m_iField[4];
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+a" ) )
		{
			iTokenTranslation = this->m_iDimA;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-a" ) )
		{
			iTokenTranslation = this->m_iDimA;
			iCurrentDim -= iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+b" ) )
		{
			iTokenTranslation = this->m_iDimB;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-b" ) )
		{
			iTokenTranslation = this->m_iDimB;
			iCurrentDim -= iTokenTranslation;
		}
	/*	else if( !lstrcmp( szThisToken, "+c" ) )
		{
			iTokenTranslation = this->m_iDimC;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-c" ) )
		{
			iTokenTranslation = this->m_iDimC;
			iCurrentDim -= iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+e" ) )
		{
			iTokenTranslation = this->m_iDimE;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-e" ) )
		{
			iTokenTranslation = this->m_iDimE;
			iCurrentDim -= iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+f" ) )
		{
			iTokenTranslation = this->m_iDimF;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-f" ) )
		{
			iTokenTranslation = this->m_iDimF;
			iCurrentDim -= iTokenTranslation;
		}*/
		else if( !lstrcmp( szThisToken, "+g" ) )
		{
			iTokenTranslation = this->m_iDimG;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-g" ) )
		{
			iTokenTranslation = this->m_iDimG;
			iCurrentDim -= iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+h" ) )
		{
			iTokenTranslation = this->m_iDimH;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-h" ) )
		{
			iTokenTranslation = this->m_iDimH;
			iCurrentDim -= iTokenTranslation;
		}
		/*else if( !lstrcmp( szThisToken, "+j" ) )
		{
			iTokenTranslation = this->m_iDimJ;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-j" ) )
		{
			iTokenTranslation = this->m_iDimJ;
			iCurrentDim -= iTokenTranslation;
		}*/
		else if( !lstrcmp( szThisToken, "+SleeveLength" ) )
		{
			iTokenTranslation = this->m_iSleeveLength;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-SleeveLength" ) )
		{
			iTokenTranslation = this->m_iSleeveLength;
			iCurrentDim -= iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+CleatEndDim" ) )
		{
			iTokenTranslation = this->m_iCleatEndDim;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "-CleatEndDim" ) )
		{
			iTokenTranslation = this->m_iCleatEndDim;
			iCurrentDim -= iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "/2" ) )
		{
			iCurrentDim /= 2;
		}
		else if( !lstrcmp( szThisToken, "/1000" ) )
		{
			iCurrentDim /= 1000;
		}
		else if( !lstrcmp( szThisToken, "0" ) )
		{
			iTokenTranslation = 0;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Sqrt( Field1^2 + Field2^2 )" ) )
		{
			double lfField1Squared = (double)this->m_iField[0] * (double)this->m_iField[0];
			double lfField2Squared = (double)this->m_iField[1] * (double)this->m_iField[1];
            double lfSqrt = sqrt( lfField1Squared + lfField2Squared );
			iTokenTranslation = (int)lfSqrt;
			iCurrentDim += iTokenTranslation;
		}
		else if( atoi( szThisToken ) )
		{
			iTokenTranslation = atoi( szThisToken );
			iCurrentDim += iTokenTranslation;
		}
		else
		{
			#ifdef _DEBUG
			::MessageBox( GetFocus(), szThisToken, "Translation Error:" , MB_OK );			
			#endif //_DEBUG
		}
			
	  //seek to next token	
		iStringLength -= iTokenLength;
		p += iTokenLength;
		if( *p ==',' )
		{
			++p;
			--iStringLength;		
		}
	}
	
  //return dimension
	return iCurrentDim;
}


//----------------------------------------------------------------------------
//	Procedure:	ComputeDataEntryString()
/*	Design:
		set data entry code = mark,qty,f1,f2,f3,f4,f5
*/
//-----------------------------------------------------------------------------------------
void CImportD3Acc::ComputeDataEntryString( void )
{
  	char szBuffer[1024];
	  	
  //set data entry code = mark,qty,f1,f2,f3,f4,f5,version
  //mark
	this->m_szDataEntryCode = this->m_szMark;
	this->m_szDataEntryCode += ",";

  //qty	
	wsprintf( szBuffer, "%i" ,this->m_iQty );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //f1
	wsprintf( szBuffer, "%i" ,this->m_iField[0] );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";
      
  //f2
	wsprintf( szBuffer, "%i" ,this->m_iField[1] );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //f3
	wsprintf( szBuffer, "%i" ,this->m_iField[2] );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";
          
  //f4
	wsprintf( szBuffer, "%i" ,this->m_iField[3] );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //f5
	wsprintf( szBuffer, "%i" ,this->m_iField[4] );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //version
  	this->m_szDataEntryCode += APPLICATION_VERSION;
}


//----------------------------------------------------------------------------
//	Procedure:	SortByAssendingProductName()
/*	Design:
	Bubble sort...
*/
//-----------------------------------------------------------------------------------------
/*
void CImportD3AccList::SortByAssendingProductName( void )
{
	POSITION ResultsPosition;
	CImportD3Acc* pRecord1;
	CImportD3Acc* pRecord2;
	BOOL fModified =FALSE;
	char szProductName1[80];
	char szProductName2[80];

  start:
	fModified =FALSE;

  //get results head for sort
  	ResultsPosition =this->GetHeadPosition();
  	if( !ResultsPosition )
  		return;

  //bubble sort 	
  	do	{
	  //get record1	
		pRecord1 =(CImportD3Acc*)this->GetNext( ResultsPosition );
		if( !ResultsPosition )
			break;
				
	  //get record2	
		pRecord2 =(CImportD3Acc*)this->GetNext( ResultsPosition );
			
	  //do comparison
		lstrcpy( (LPSTR)szProductName1, pRecord1->GetType() );
		lstrcpy( (LPSTR)szProductName2, pRecord2->GetType() );
		if( lstrcmp( (LPSTR)szProductName1, (LPSTR)szProductName2 )>0 )
	  		{
	  	  //do swap	
	  	  	this->Swap( pRecord1, pRecord2 );
	  		fModified=TRUE;
	  		}

  		ResultsPosition =(CImportD3Acc*)this->Find( pRecord2 );
	  	  	
  	  	}while( ResultsPosition );
		
	if( fModified==TRUE )
		goto start;
}
*/


//----------------------------------------------------------------------------
//	Procedure:	SortByAssendingMark()
/*	Design:
	Bubble sort...
*/
//-----------------------------------------------------------------------------------------
/*
void CImportD3AccList::SortByAssendingMark( void )
{
	POSITION ResultsPosition;
	CImportD3Acc* pRecord1;
	CImportD3Acc* pRecord2;
	BOOL fModified =FALSE;
	char szProductName1[80];
	char szProductName2[80];

  start:
	fModified =FALSE;

  //get results head for sort
  	ResultsPosition =this->GetHeadPosition();
  	if( !ResultsPosition )
  		return;

  //bubble sort 	
  	do	{
	  //get record1	
		pRecord1 =(CImportD3Acc*)this->GetNext( ResultsPosition );
		if( !ResultsPosition )
			break;
				
	  //get record2	
		pRecord2 =(CImportD3Acc*)this->GetNext( ResultsPosition );
			
	  //do comparison
		lstrcpy( (LPSTR)szProductName1, pRecord1->GetMark() );
		lstrcpy( (LPSTR)szProductName2, pRecord2->GetMark() );
		if( lstrcmp( (LPSTR)szProductName1, (LPSTR)szProductName2 )>0 )
	  		{
	  	  //do swap	
	  	  	this->Swap( pRecord1, pRecord2 );
	  		fModified=TRUE;
	  		}

  		ResultsPosition =(CImportD3Acc*)this->Find( pRecord2 );
	  	  	
  	  	}while( ResultsPosition );
		
	if( fModified==TRUE )
		goto start;
}
*/


//----------------------------------------------------------------------------
//	Procedure:	Swap()
/*	Design:
*/
//-----------------------------------------------------------------------------------------
/*
void CImportD3AccList::Swap( CImportD3Acc* pAccessory1, CImportD3Acc* pAccessory2 )
{
	POSITION ResultsPosition1;
	POSITION ResultsPosition2;

  //remove
	ResultsPosition1 =this->Find( pAccessory1 );
	this->RemoveAt( ResultsPosition1 );						  		

  //insert after	 
	ResultsPosition2 =this->Find( pAccessory2 );
	this->InsertAfter( ResultsPosition2, pAccessory1 );						  		
}
*/

	
