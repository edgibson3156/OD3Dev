// ImportD3Beam.cpp: implementation of the CImportD3Beam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "ImportD3Beam.h"
//#include "strset.h"
#include "element.h"
#include "ImportDet3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern const int cIllegalHolePosition =0;

extern bool SimpleFindAndReplace( LPSTR szSource, LPSTR szFind, LPSTR szReplace );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImportD3Beam::CImportD3Beam()
{
	this->SetBeamDefaults();
}

CImportD3Beam::~CImportD3Beam()
{
	CDet3BeamHole	*pHoles=NULL;
	POSITION		pos;
	
	// Get the head postiom
	pos = m_tplHoleList.GetHeadPosition();

	while(pos)
	{
		// Get the pointer
		pHoles = m_tplHoleList.GetNext(pos);
		// Free memory
		delete pHoles;
	}

	// Remove pointers
	m_tplHoleList.RemoveAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetDefaults
//
void CImportD3Beam::SetBeamDefaults( void )
{
	eArrangement		=NonStandardArrangement;
	ePosition			=NonStandardPosition;
	eMemberType	 		=Purlin;
	eBracing			=NoBracing;
	eBracing2			=NoBracing;
	m_iQty				=1;
	m_lProductGroupID	=0;
	m_iLength 			=0;
	m_iSpan1			=0;
	m_iSpan2			=0;
	m_iSpan3			=0;
	m_iOverhang1		=0;
	m_iOverhang2		=0;
	m_iSlope			=0;
	m_iColumn1			=0;
	m_iColumn2			=0;

	m_iDimA				=0;
	m_iDimB				=0;
	m_iDimC				=0;
	m_iDimE				=0;
	m_iDimF				=0;
	m_iDimG				=0;
	m_iDimH				=0;
	m_iDimJ				=0;
	m_iDimT				=0;

	m_iCleatHoleCentres =0;
	m_iTPBSlope			=0;
	m_dGauge			=0.0f;
	m_iLipLengthBottom	=0;
	m_iLipLengthTop		=0;
	m_iServiceHoles		=0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ComputeSPC
//
void CImportD3Beam::ComputeSPC( void )
{
	this->m_szStandardPartCode = ComputeSPCPrefix();
	this->m_szStandardPartCode += ComputeSPCBracingAttribute();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ComputeSPCPrefix
//
LPSTR CImportD3Beam::ComputeSPCPrefix( void )
{
	switch( this->ePosition )
	{
	case SleevedInternal:
		if( this->eMemberType == Purlin )
		{
			return "01";	
		}
		else
		{
			return "12";	
		}
		break;

	case SleevedLeftGable:
		if( this->eMemberType == Purlin )
		{
			return "02";	
		}
		else
		{
			return "13";	
		}
		break;

	case SleevedRightGable:
		if( this->eMemberType == Purlin )
		{
			return "03";	
		}
		else
		{
			return "14";	
		}
		break;

	case DoubleInternal:
		if( this->eMemberType == Purlin )
		{
			return "04";	
		}
		else
		{
			return "15";	
		}
		break;

	case DoubleLeftGable:
		if( this->eMemberType == Purlin )
		{
			return "05";	
		}
		else
		{
			return "16";	
		}
		break;

	case DoubleRightGable:
		if( this->eMemberType == Purlin )
		{
			return "06";	
		}
		else
		{
			return "17";	
		}
		break;

	case ButtedInternal:
		if( this->eMemberType == Purlin )
		{
			return "01";	
		}
		else
		{
			return "12";	
		}
		break;

	case ButtedLeftGable:
		if( this->eMemberType == Purlin )
		{
			return "02";	
		}
		else
		{
			return "13";	
		}
		break;

	case ButtedRightGable:
		if( this->eMemberType == Purlin )
		{
			return "03";	
		}
		else
		{
			return "14";	
		}
		break;
		
	case OverlapLeftEnd:
		return "09";	
		break;

	case OverlapLeftPenultimate:
		return "08";	
		break;

	case OverlapInternal:
		return "07";	
		break;

	case OverlapRightPenultimate:
		return "10";	
		break;

	case OverlapRightEnd:
		return "11";	
		break;

	case FireScreenInternal:
		return "F12";	
		break;

	case FireScreenLeft:
		return "F13";
		break;

	case FireScreenRight:
		return "F14";
		break;

	case EavesBeamStandOffInternal:
		return "EB01";
		break;
			
	case EavesBeamStandOffLeftGable:
		return "EB02";
		break;
			
	case EavesBeamStandOffRightGable:
		return "EB03";
		break;
		
	case EavesBeamFlushInternal:
		return "EB18";
		break;

	case EavesBeamNonStandardPosition:
		return "EBNON";
		break;

	case NonStandardPosition:
	default:
		if( this->eMemberType == Purlin )
		{
			return "NONP";
		}
		else
		{
			return "NONR";
		}
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ComputeSPCBracingAttribute
//
LPCSTR CImportD3Beam::ComputeSPCBracingAttribute( void )
{
	if( this->m_szStandardPartCode == "NON" ||
		this->m_szStandardPartCode == "NONP" ||
		this->m_szStandardPartCode == "NONR" ||
		this->m_szStandardPartCode == "EBNON" )
	{
		return "";
	}
	
	if( this->eBracing == NoBracing )
	{
		return "P";
	}

	else if( this->eBracing == MidSpan )
	{
		return "S";
	}

	else if( this->eBracing == ThirdPoints )
	{
		return "R";
	}

	else
	{
		return "?";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ComputeDimensionFromScript
//
LPCSTR CImportD3Beam::szComputeDimensionFromScript( LPSTR lpszSource )
{
	static char szBuffer[256];

	int iDimension = this->IntComputeDimensionFromScript( lpszSource );
	wsprintf( szBuffer, "%i", iDimension  );

  //default, return source
	return (LPCSTR)szBuffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	IntComputeDimensionFromScript
//
//-----------------------------------------------------------------------------------------
/*	Design:

	for all tokens
		compute token length
		translate token
		seek to next token
	return dimension
*/
//-----------------------------------------------------------------------------------------
int CImportD3Beam::IntComputeDimensionFromScript( LPSTR lpszSource )
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
		if( !lstrcmp( szThisToken, "+Span1" ) )
		{
			iTokenTranslation = this->m_iSpan1;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Span2" ) )
		{
			iTokenTranslation = this->m_iSpan2;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Span3" ) )
		{
			iTokenTranslation = this->m_iSpan3;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "/3" ) )
		{
			iCurrentDim /= 3;
		}
		else if( !lstrcmp( szThisToken, "/2" ) )
		{
			iCurrentDim /= 2;
		}
		else if( !lstrcmp( szThisToken, "*2" ) )
		{
			iCurrentDim *= 2;
		}
		else if( !lstrcmp( szThisToken, "-25" ) )
		{
			iCurrentDim -= 25;
		}
		else if( !lstrcmp( szThisToken, "-3" ) )
		{
			iCurrentDim -= 3;
		}
		else if( !lstrcmp( szThisToken, "-2" ) )
		{
			iCurrentDim -= 2;
		}
		else if( !lstrcmp( szThisToken, "+Overhang1" ) )
		{
			iTokenTranslation = this->m_iOverhang1;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+Overhang2" ) )
		{
			iTokenTranslation = this->m_iOverhang2;
			iCurrentDim += iTokenTranslation;
		}
		else if( !lstrcmp( szThisToken, "+a" ) )
		{
			iCurrentDim += this->m_iDimA;
		}
		else if( !lstrcmp( szThisToken, "+b" ) )
		{
			iCurrentDim += this->m_iDimB;
		}
		else if( !lstrcmp( szThisToken, "+c" ) )
		{
			iCurrentDim += this->m_iDimC;
		}
		else if( !lstrcmp( szThisToken, "+e" ) )
		{
			iCurrentDim += this->m_iDimE;
		}
		else if( !lstrcmp( szThisToken, "+f" ) )
		{
			iCurrentDim += this->m_iDimF;
		}
		else if( !lstrcmp( szThisToken, "+g" ) )
		{
			iCurrentDim += this->m_iDimG;
		}
		else if( !lstrcmp( szThisToken, "-g" ) )
		{
			iCurrentDim -= this->m_iDimG;
		}
		else if( !lstrcmp( szThisToken, "+Slope" ) )
		{
			iCurrentDim += this->m_iSlope;
		}
		else if( !lstrcmp( szThisToken, "-Column1" ) )
		{
			iCurrentDim -= this->m_iColumn1;
		}
		else if( !lstrcmp( szThisToken, "-Column2" ) )
		{
			iCurrentDim -= this->m_iColumn2;
		}
		else if( !lstrcmp( szThisToken, "+Column1" ) )
		{
			iCurrentDim += this->m_iColumn1;
		}
		else if( !lstrcmp( szThisToken, "+Column2" ) )
		{
			iCurrentDim += this->m_iColumn2;
		}
		else if( !lstrcmp( szThisToken, "+Column1Offset" ) )
		{
			iCurrentDim += this->m_iColumn1 /2 +5;
		}
		else if( !lstrcmp( szThisToken, "+Column2Offset" ) )
		{
			iCurrentDim += this->m_iColumn2 /2 +5;
		}
		else if( !lstrcmp( szThisToken, "-Column1Offset" ) )
		{
			iCurrentDim -= this->m_iColumn1 /2 +5;
		}
		else if( !lstrcmp( szThisToken, "-Column2Offset" ) )
		{
			iCurrentDim -= this->m_iColumn2 /2 +5;
		}
		else if( !lstrcmp( szThisToken, "+Span1h" ) )
		{
			if( this->m_iDimH == 0 ) 
			{
				iCurrentDim += (int)((double)this->m_iSpan1 * 0.1 );
			}
			else
			{
				iCurrentDim += this->m_iDimH;
			}
		}
		else if( !lstrcmp( szThisToken, "-Span1h" ) )
		{
			if( this->m_iDimH == 0 ) 
			{
				iCurrentDim -= (int)((double) this->m_iSpan1 * 0.1 );
			}
			else
			{
				iCurrentDim -= this->m_iDimH;
			}
		}
		else if( !lstrcmp( szThisToken, "+Span1j" ) )
		{
			if( this->m_iDimJ == 0 ) 
			{
				iCurrentDim += (int)((double)this->m_iSpan1 * 0.15 );
			}
			else
			{
				iCurrentDim += this->m_iDimJ;
			}
		}
		else if( !lstrcmp( szThisToken, "-Span1j" ) )
		{
			if( this->m_iDimJ == 0 ) 
			{
				iCurrentDim -= (int)((double)this->m_iSpan1 * 0.15 );
			}
			else
			{
				iCurrentDim -= this->m_iDimJ;
			}
		}
		else if( !lstrcmp( szThisToken, "+Span2h" ) )
		{
			if( this->m_iDimH == 0 ) 
			{
				iCurrentDim += (int)((double)this->m_iSpan2 * 0.1 );
			}
			else
			{
				iCurrentDim += this->m_iDimH;
			}
		}
		else if( !lstrcmp( szThisToken, "-Span2h" ) )
		{
			if( this->m_iDimH == 0 ) 
			{
				iCurrentDim -= (int)((double)this->m_iSpan2 * 0.1 );
			}
			else
			{
				iCurrentDim -= this->m_iDimH;
			}
		}
		else if( !lstrcmp( szThisToken, "+Span2j" ) )
		{
			if( this->m_iDimJ == 0 ) 
			{
				iCurrentDim += (int)((double)this->m_iSpan2 * 0.15 );
			}
			else
			{
				iCurrentDim += this->m_iDimJ;
			}
		}
		else if( !lstrcmp( szThisToken, "-Span2j" ) )
		{
			if( this->m_iDimJ == 0 ) 
			{
				iCurrentDim -= (int)((double)this->m_iSpan2 * 0.15 );
			}
			else
			{
				iCurrentDim -= this->m_iDimJ;
			}
		}
		else if( !lstrcmp( szThisToken, "+Span3h" ) )
		{
			if( this->m_iDimH == 0 ) 
			{
				iCurrentDim += (int)((double)this->m_iSpan3 * 0.1 );
			}
			else
			{
				iCurrentDim += this->m_iDimH;
			}
		}
		else if( !lstrcmp( szThisToken, "-Span3h" ) )
		{
			if( this->m_iDimH == 0 ) 
			{
				iCurrentDim -= (int)((double)this->m_iSpan3 * 0.1 );
			}
			else
			{
				iCurrentDim -= this->m_iDimH;
			}
		}
		else if( !lstrcmp( szThisToken, "+Span3j" ) )
		{
			if( this->m_iDimJ == 0 ) 
			{
				iCurrentDim += (int)((double)this->m_iSpan3 * 0.15 );
			}
			else
			{
				iCurrentDim += this->m_iDimJ;
			}
		}
		else if( !lstrcmp( szThisToken, "-Span3j" ) )
		{
			if( this->m_iDimJ == 0 ) 
			{
				iCurrentDim -= (int)((double)this->m_iSpan3 * 0.15 );
			}
			else
			{
				iCurrentDim -= this->m_iDimJ;
			}
		}
		else if( !lstrcmp( szThisToken, "+Length" ) )
		{
			iCurrentDim += this->m_iLength;
		}
		else if( !lstrcmp( szThisToken, "0" ) )
		{
			iTokenTranslation = 0;
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetDateToday
//
/*
	Design:

	compute current time/date
	build date string
	assign date
*/
//----------------------------------------------------------------------------
void CImportD3Beam::SetDateToday( void )
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


//----------------------------------------------------------------------------
//	Procedure:	Read()	read beam from target.
/*
	Design:

	read:				
		Arrangement
		Position
		MemberType
		Bracing
		Bracing2
		StandardPartCode
		Section
		DrawingNumber
		Mark
		iQty 
		Length
		Span1
		Span2
		Span3
		Overhang1
		Overhang2
		Slope
		Column1
		Column2
		LipBottom
		LipTop
		Comment
		Date
	  	DataEntryCode

		DimA
		DimB
		DimC
		DimE
		DimF
		DimG		
		DimH
		DimJ

		ExtraHoles
*/
//----------------------------------------------------------------------------
bool CImportD3Beam::Read( CBigIni& ABigIni, int iBeamIndex )
{
	CString			szSection;
	CString			szDefault;
	CString			szEntry;
	CString			szReturnBuffer;
	CDet3BeamHole	*pNewHole=NULL;
	bool			holes=true;
	int				iHoleIndex=0;

	szSection.Format( "Beam#%i", iBeamIndex );

  //Arrangement
	szEntry	= "Arrangement"; 
	this->eArrangement = ( arragement_e )ABigIni.GetPrivateProfileInt( szSection, szEntry, -1 );
	if( this->eArrangement == -1 )
		return FALSE;

  //Position
	szEntry	= "Position"; 
	this->ePosition = ( beamposition_e )ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //ProductType
	szEntry	= "ProductType"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szProductType = szReturnBuffer;

  //MemberType
	szEntry	= "MemberType";
	if (this->m_szProductType == _T("ASSOCIATED_SECTION"))
	{
		this->eMemberType = ( membertype_e )8;
	}
	else if(m_szProductType == _T("STUD"))
	{
		eMemberType = ( membertype_e )9;
	}
	else if(m_szProductType == _T("FLOOR_JOIST"))
	{
		eMemberType = ( membertype_e )9;
		// Temp fix if the ASF section is 010 (Floor Joist) convert it to 009 (stud)
		// there are no products in the database with the type 010, will require a set of duplicate
		// products in AViiON
		//eMemberType = ( membertype_e )10;
	}
	else
	{
		this->eMemberType = ( membertype_e )ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
	}
	
  //Bracing
	szEntry	= "Bracing"; 
	this->eBracing = ( bracing_e )ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
  
  //Bracing2
	szEntry	= "Bracing2"; 
	this->eBracing2 = ( bracing_e )ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
  
  //StandardPartCode
	szEntry	= "SPC"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szStandardPartCode = szReturnBuffer;

  //Section
	szEntry	= "Section"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szProductID = szReturnBuffer;

  //DrawingNumber
	szEntry	= "DrawingNumber"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDrawingNumber = szReturnBuffer;

  //Mark
	szEntry	= "Mark"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szMark = szReturnBuffer;
	// Strip any underscores found in the mark number
	m_szMark.Replace(_T("_"), _T("#"));

  //iQty 
	szEntry	= "Quantity"; 
	this->m_iQty = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Length
	szEntry	= "Length"; 
	this->m_iLength = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Span1
	szEntry	= "Span1"; 
	this->m_iSpan1 = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Span2 
	szEntry	= "Span2"; 
	this->m_iSpan2 = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Span3 
	szEntry	= "Span3"; 
	this->m_iSpan3 = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Overhang1 
	szEntry	= "Overhang1"; 
	this->m_iOverhang1 = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Overhang2
	szEntry	= "Overhang2"; 
	this->m_iOverhang2 = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //TPBottomSlope 
	szEntry	= "TPBottomSlope"; 
	this->m_iTPBSlope = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Slope
	szEntry	= "Slope"; 
	this->m_iSlope = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Column1
	szEntry	= "Column1"; 
	this->m_iColumn1 = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Column2
	szEntry	= "Column2"; 
	this->m_iColumn2 = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //Thickness
	szEntry	= "Thickness"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szGauge = szReturnBuffer;
	this->m_dGauge = atof(szReturnBuffer);
	
	
  //LipBottom
	szEntry	= "LipLengthBottom"; 
	this->m_iLipLengthBottom = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
  
  //LipTop
	szEntry	= "LipLengthTop"; 
	this->m_iLipLengthTop = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
  
  //Comment
	szEntry	= "Comment"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szComment = szReturnBuffer;
	SimpleFindAndReplace( (LPSTR)(const char*)m_szComment, "~~", "\r\n" );

  //Date
	szEntry	= "Date"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDate = szReturnBuffer;

  //DataEntryCode
	szEntry	= "DataEntryCode"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDataEntryCode = szReturnBuffer;

  //ProductGroup
	szEntry	= "ProductGroup"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szProductGroup = szReturnBuffer;

  //ProductGroupID
	szEntry	= "ProductGroupID"; 
	this->m_lProductGroupID = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimA
	szEntry	= "DimensionA"; 
	this->m_iDimA = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimB
	szEntry	= "DimensionB"; 
	this->m_iDimB = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimC
	szEntry	= "DimensionC"; 
	this->m_iDimC = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimE
	szEntry	= "DimensionE"; 
	this->m_iDimE = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimF
	szEntry	= "DimensionF"; 
	this->m_iDimF = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimG		
	szEntry	= "DimensionG"; 
	this->m_iDimG = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimH
	szEntry	= "DimensionH"; 
	this->m_iDimH = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

  //DimJ
	szEntry	= "DimensionJ"; 
	this->m_iDimJ = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	// SectionType
	szEntry	= "SectionType"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szSectionType = szReturnBuffer;

	// SectionSize
	szEntry	= "SectionSize"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szSectionSize = szReturnBuffer;

	// ArrangementTxt
	szEntry	= "ArrangementTxt"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szArrangementTxt = szReturnBuffer;

	// SubArrangementTxt
	szEntry	= "SubArrangementTxt"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szSubArrangementTxt = szReturnBuffer;

	// CleatHoleCentres
	szEntry	= "CleatHoleCentres"; 
	m_iCleatHoleCentres = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	// Service holes (ASF)
	szEntry	= "ServiceHoles"; 
	m_iServiceHoles = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	// Set comments in ASF sections
	if(GetMemberType() == 9 || GetMemberType() == 10)
	{
		// Set comment for service holes
		if(m_iServiceHoles)
			SetComment(_T("Service Holes"));
		else
			SetComment(_T("No Service Holes"));
	}



	//ExtraHoles
	while(holes)
	{
		// Create new hole
		pNewHole = new CDet3BeamHole;

		// Read in hole data
		if(pNewHole->Read(ABigIni, szSection, iHoleIndex++))
		{
			// Add hole to the list
			m_tplHoleList.AddTail(pNewHole);
		}
		else
		{
			// Set flag to no more holes
			holes = false;
			// Free memory
			delete pNewHole;
		}
	}
    
	return TRUE;
}

// Extract ASF sections from d3 file
bool CImportD3Beam::readASFPanels(void *pvImport, int index)
{
	CString			sPanel, sKey, sIndex, sPanelItem;
	CString			sMark, sText, path, sSection, sPanelMark;
	char			buffer[512];
	int				itemIndex=0, test;
	bool			bResult=false, bMoreItems=true;
	CImportDet3		*pImport = (CImportDet3 *)pvImport;
	CImportD3Beam	*pNewBeam=NULL;


	// Set the path name
	path = pImport->getD3FileName();
	// Format the panel name
	sPanel.Format("CStudPanel#%i", index);

	sKey = _T("Quantity");
	if((test=GetPrivateProfileInt(sPanel, sKey, -1, path)) != -1)
	{
		bResult=true;

		// Mark
		sKey = _T("Mark");
		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
		sPanelMark = buffer;
		// Strip any underscores found in the mark number
		sPanelMark.Replace(_T("_"), _T("#"));

		// Drawing number
		sKey = _T("DrawingNumber");
		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
		SetDrawingNumber(buffer);

		// Date
		sKey = _T("Date");
		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
		SetDate(buffer);

		// Stud section
//		sKey = _T("StudSection");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		pPanelHeader->m_sStudSection = buffer;

		// Stud runner top
//		sKey = _T("StudRunnerTopSection");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		pPanelHeader->m_sStudRunnerTopSection = buffer;

		// Stud runner bottom
//		sKey = _T("StudRunnerBottomSection");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		pPanelHeader->m_sStudRunnerBottomSection = buffer;

		// Panel head detail
//		sKey = _T("PanelHeadDetail");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		pPanelHeader->m_sPanelHeadDetail = buffer;

		// Stud orientation
//		sKey = _T("StudOrientation");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		pPanelHeader->m_sStudOrientation = buffer;

		// Comment
//		sKey = _T("Comment");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		SetComment(buffer);

		// SPC
//		sKey = _T("SPC");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		SetSPC(buffer);

		// Data entry code
//		sKey = _T("DataEntryCode");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		pPanelHeader->m_sDataEntryCode = buffer;

		// Product group
//		sKey = _T("ProductGroup");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		SetProductGroup(buffer);

		// Product group ID
//		sKey = _T("ProductGroupID");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		SetProductGroupID(atoi(buffer));


		// Product type
		sKey = _T("ProductType");
		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
		SetProductType(buffer);

		// Stud ProductName
//		sKey = _T("ProductName");
//		GetPrivateProfileString(sPanel, sKey, NULL, buffer, sizeof(buffer), path);
//		pPanelHeader->m_sProductName = buffer;

		// Width
//		sKey = _T("Width");
//		pPanelHeader->m_iWidth = GetPrivateProfileInt(sPanel, sKey, 0, path);

		// Height
//		sKey = _T("Height");
//		pPanelHeader->m_iHeight = GetPrivateProfileInt(sPanel, sKey, 0, path);

		// Stud spacing
//		sKey = _T("StudSpacing");
//		pPanelHeader->m_iStudSpacing = GetPrivateProfileInt(sPanel, sKey, 0, path);

		// Panel quantity
//		sKey = _T("PanelQty");
//		pPanelHeader->m_iPanelQty = GetPrivateProfileInt(sPanel, sKey, 0, path);

		// Cross bracing
//		sKey = _T("CrossBracing");
//		pPanelHeader->m_iCrossBracing = GetPrivateProfileInt(sPanel, sKey, 0, path);

		// Service holes
		sKey = _T("ServiceHoles");
		m_iServiceHoles = GetPrivateProfileInt(sPanel, sKey, 0, path);

		// Panel quantity
//		sKey = _T("LateralBracingY#0");
//		pPanelHeader->m_iLateralBracingY0 = GetPrivateProfileInt(sPanel, sKey, 0, path);


		while(bMoreItems)
		{
			// Format the panel item index name
			sIndex.Format("ItemIndex#%i", itemIndex++);

			// Append strings
			sPanelItem = sPanel+sIndex;

			sKey = _T("Quantity");
			if((test=GetPrivateProfileInt(sPanelItem, sKey, -1, path)) != -1)
			{
				// Create new beam object
				pNewBeam = new CImportD3Beam();

				// Quantity
				pNewBeam->SetQty(test);

				// Mark from D3 file
				sKey = _T("Mark");
				GetPrivateProfileString(sPanelItem, sKey, NULL, buffer, sizeof(buffer), path);
				sMark = buffer;

				// Support old D3 format
				if(sMark.GetLength()==0)
					sMark.Format("%s#%i", sPanelMark, itemIndex);

				// Strip any underscores found in the mark number
				sMark.Replace(_T("_"), _T("#"));
				pNewBeam->SetMark(sMark.GetBuffer(1));


				// Section and product name
				sKey = _T("Section");
				GetPrivateProfileString(sPanelItem, sKey, NULL, buffer, sizeof(buffer), path);
				pNewBeam->SetSectionSize(buffer);
				pNewBeam->SetProductName(buffer);
				sSection = buffer;
				//pNewBeam->SetSectionType(pNewBeam->GetSectionSize().Left(2));

				// Product type
				pNewBeam->SetProductType((char *)GetProductType());
				pNewBeam->SetMemberType(Stud);

				// SPC
				pNewBeam->SetSPC(_T("NON"));

				// Length
				sKey = _T("Length");
				pNewBeam->SetLength(GetPrivateProfileInt(sPanelItem, sKey, -1, path));

				// Set comment for service holes
				if(m_iServiceHoles && sSection.Find("CS70", 0) != 0)
					pNewBeam->SetComment(_T("Service Holes"));
				else
					pNewBeam->SetComment(_T("No Service Holes"));

				// Drawing number
				pNewBeam->SetDrawingNumber((char *)GetDrawingNumber());

				// Date
				pNewBeam->SetDate((char *)GetDate());

				// Function
//				sKey = _T("Function");
//				GetPrivateProfileString(sPanelItem, sKey, NULL, buffer, sizeof(buffer), path);
//				pPanel->m_sFunction = buffer;

				// Add beam to the import pointer list
				pImport->m_tplBeamList.AddTail(pNewBeam);
			}
			else
			{
				// No more items for this panel
				bMoreItems=false;
			}
		}
	}


	return(bResult);
}

//----------------------------------------------------------------------------
void CImportD3Beam::AddExtraHolesToList(CBeamElement* pBeam)
{
	CBeamOps		*pBeamOp;
	int				i, nScriptID=10;
	CString			szOperation;
	CString			szOpType;
	int				nOpSeq=0;
	POSITION		pos;
	CDet3BeamHole	*pHole=NULL;

	// Get the head position
	pos = m_tplHoleList.GetHeadPosition();

	while(pos)
	{
		// Get the data pointer
		pHole = m_tplHoleList.GetNext(pos);

		// Loop squence
		for (i=0; i<2; i++)
		{
			nOpSeq++;
			switch (i)
			{
			case 0:
				szOpType = "Dim";
				szOperation.Format("%i", pHole->GetPosition());//szHolePosition;
				break;
			case 1:
				szOpType = "Punch";
				szOperation = pHole->GetHoleSetType();//szHoleSetType;
				break;
			}
			
			// Create new beam op
			pBeamOp = new CBeamOps();

			// Set data
			pBeamOp->SetOpSeqID(nOpSeq);
			pBeamOp->SetOpType(szOpType);
			pBeamOp->SetAbsolute(true);
			pBeamOp->SetPositive(true);
			pBeamOp->SetMultiplied(true);
			pBeamOp->SetMultiplier(1);
			pBeamOp->SetOperation(szOperation);

			if(szOpType == "Punch")
			{
				pBeamOp->SetComment(pHole->GetComment());
				pBeamOp->SetCSunk(pHole->GetCSunk());
			}
			
			pBeamOp->SetScriptID(nScriptID);
			// Store in list
			pBeam->m_tplAddList.AddTail(pBeamOp);
		}
	}

	return;
}
//----------------------------------------------------------------------------
//	Procedure:	Write()	Write beam to target.
/*
	Design:

	write:				
		Date
		DrawingNumber
		Mark
		iQty 
		Section
		StandardPartCode
		Bracing
		MemberType
		Arrangement
		Position
		Comment
        
        DataEntryCode
		Length
		Span1
		Span2
		Span3
		Overhang1
		Overhang2
		Slope
		Column1
		Column2

		DimA
		DimB
		DimC
		DimE
		DimF
		DimG		
		DimH
		DimJ

		ExtraHoles
*/
//----------------------------------------------------------------------------
BOOL CImportD3Beam::Write( CBigIni& ABigIni, int iBeamIndex )
{
	CString			szEntry;
	CString			szSection;
	CString			szText;
	POSITION		pos;
	CDet3BeamHole	*pHole=NULL;
	int				iHoleIndex=0;

	szSection.Format( "Beam#%i", iBeamIndex );

  //Date
	szEntry = "Date";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szDate );	

  //DrawingNumber
	szEntry = "DrawingNumber";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szDrawingNumber );	

  //Mark
	szEntry = "Mark";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szMark );	

  //iQty 
	szText.Format( "%i", this->m_iQty );
	szEntry = "Quantity";
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	

  //Section
	szEntry = "Section";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szProductID );	
  
  //StandardPartCode
	szEntry = "SPC";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szStandardPartCode );	

  //Bracing
	szText.Format( "%i", this->eBracing );
	szEntry = "Bracing";
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
	
	// Bracing2
	szText.Format( "%i", eBracing2);
	szEntry = "Bracing2";
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
  
  //MemberType
	szText.Format( "%i", this->eMemberType );
	szEntry = "MemberType";                                   
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	
  //Arrangement
	szText.Format( "%i", this->eArrangement );
	szEntry = "Arrangement";                                   
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	

  //Position
	szText.Format( "%i", this->ePosition );
	szEntry = "Position";                                   
	ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	

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

  //DataEntryCode
	szEntry = "DataEntryCode";                                   
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szDataEntryCode );	

  //Length
	if( this->m_iLength != 0 )
		{
		szText.Format( "%i", this->m_iLength );
		szEntry = "Length";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Span1
	if( this->m_iSpan1 != 0 )
		{
		szText.Format( "%i", this->m_iSpan1 );
		szEntry = "Span1";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Span2
	if( this->m_iSpan2 != 0 )
		{
		szText.Format( "%i", this->m_iSpan2 );
		szEntry = "Span2";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Span3
	if( this->m_iSpan3 != 0 )
		{
		szText.Format( "%i", this->m_iSpan3 );
		szEntry = "Span3";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Overhang1
	if( this->m_iOverhang1 != 0 )
		{
		szText.Format( "%i", this->m_iOverhang1 );
		szEntry = "Overhang1";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Overhang2
	if( this->m_iOverhang2 != 0 )
		{
		szText.Format( "%i", this->m_iOverhang2 );
		szEntry = "Overhang2";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Slope
	if( this->m_iSlope != 0 )
		{
		szText.Format( "%i", this->m_iSlope );
		szEntry = "Slope";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Column1
	if( this->m_iColumn1 != 0 )
		{
		szText.Format( "%i", this->m_iColumn1 );
		szEntry = "Column1";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

  //Column2
	if( this->m_iColumn2 != 0 )
		{
		szText.Format( "%i", this->m_iColumn2 );
		szEntry = "Column2";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	   	}

	// ProductType
	szEntry = "ProductType";
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szProductType);

  //ProductGroup
	szEntry = "ProductGroup";
	ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szProductGroup );	

  //ProductGroupID
	if(m_lProductGroupID > 0)
	{
		szText.Format( "%i", this->m_lProductGroupID );
		szEntry = "ProductGroupID";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimA
	if(m_iDimA > 0)
	{
		szText.Format( "%i", this->m_iDimA );
		szEntry = "DimensionA";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
	}

  //DimB
	if(m_iDimB > 0)
	{
		szText.Format( "%i", this->m_iDimB );
		szEntry = "DimensionB";                                  
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimC
	if(m_iDimC > 0)
	{
		szText.Format( "%i", this->m_iDimC );
		szEntry = "DimensionC";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimE
	if(m_iDimE > 0)
	{
		szText.Format( "%i", this->m_iDimE );
		szEntry = "DimensionE";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimF
	if(m_iDimF > 0)
	{
		szText.Format( "%i", this->m_iDimF );
		szEntry = "DimensionF";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimG
	if(m_iDimG > 0)
	{
		szText.Format( "%i", this->m_iDimG );
		szEntry = "DimensionG";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimH
	if(m_iDimH > 0)
	{
		szText.Format( "%i", this->m_iDimH );
		szEntry = "DimensionH";                                   
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

  //DimJ
	if(m_iDimJ > 0)
	{
		szText.Format( "%i", this->m_iDimJ );
		szEntry = "DimensionJ";
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	}

	// SectionType
	szEntry	= "SectionType"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szSectionType );

	// SectionSize
	szEntry	= "SectionSize"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szSectionSize );

	// ArrangementTxt
	if(m_szArrangementTxt.GetLength())
	{
		szEntry	= "ArrangementTxt"; 
		ABigIni.WritePrivateProfileString( szSection, szEntry, m_szArrangementTxt );
	}

	// SubArrangementTxt
	if(m_szSubArrangementTxt.GetLength())
	{
		szEntry	= "SubArrangementTxt"; 
		ABigIni.WritePrivateProfileString( szSection, szEntry, m_szSubArrangementTxt );
	}

	// CleatHoleCentres
	if(m_iCleatHoleCentres > 0)
	{
		szEntry	= "CleatHoleCentres"; 
		szText.Format("%i", m_iCleatHoleCentres);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
	}

	// TPBottomSlope
	if(m_iTPBSlope > 0)
	{
		szEntry	= "TPBottomSlope"; 
		szText.Format("%i", m_iTPBSlope);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
	}

	// Thickness
	if(m_dGauge > 0.0f)
	{
		szEntry	= "Thickness"; 
		szText.Format("%f", m_dGauge);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
	}

	// LipLengthTop
	if(m_iLipLengthTop > 0)
	{
		szEntry	= "LipLengthTop"; 
		szText.Format("%i", m_iLipLengthTop);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
	}

	// LipLengthBottom
	if(m_iLipLengthBottom > 0)
	{
		szEntry	= "LipLengthBottom"; 
		szText.Format("%i", m_iLipLengthBottom);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
	}

	//ExtraHoles
	// Get the head position
	pos = m_tplHoleList.GetHeadPosition();
	
	while(pos)
	{
		pHole = m_tplHoleList.GetNext(pos);
		pHole->Write(ABigIni, szSection, iHoleIndex++);
	}


	return TRUE;
}


//----------------------------------------------------------------------------
//	Procedure:	ComputeDataEntryString()
/*	Design:

	query for beam length script
		SELECT Script FROM SPC_Length_Script WHERE Spc = this spc
	
	
	set data entry code = amp,bqty,type,mark,qty,len,spc,oh1,oh2,sp1,sp2,sp3,...,version
*/
//-----------------------------------------------------------------------------------------
void CImportD3Beam::ComputeDataEntryString( void )
	{
	char szBuffer[1024];
	
  //set data entry code = amp,bqty,type,mark,qty,len,spc,oh1,oh2,sp1,sp2,sp3,...
  //amp
  	this->m_szDataEntryCode = "?";
	this->m_szDataEntryCode += ",";

  //bqty
  	this->m_szDataEntryCode += "?";
	this->m_szDataEntryCode += ",";

  //type
  	if( this->eMemberType == Purlin )
  		{
  		this->m_szDataEntryCode += "1";
  		}
  	else if( this->eMemberType == Rail )
  		{
  		this->m_szDataEntryCode += "2";
  		}
	this->m_szDataEntryCode += ",";

  //mark
	this->m_szDataEntryCode += this->m_szMark;
	this->m_szDataEntryCode += ",";

  //qty	
	wsprintf( szBuffer, "%i" ,this->m_iQty );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //len
	wsprintf( szBuffer, "%i" ,this->m_iLength );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";
      
  //spc
	this->m_szDataEntryCode += this->m_szStandardPartCode;
	this->m_szDataEntryCode += ",";

  //oh1
	wsprintf( szBuffer, "%i" ,this->m_iOverhang1 );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //oh2
	wsprintf( szBuffer, "%i" ,this->m_iOverhang2 );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //sp1
	wsprintf( szBuffer, "%i" ,this->m_iSpan1 );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //sp2
	wsprintf( szBuffer, "%i" ,this->m_iSpan2 );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";

  //sp3
	wsprintf( szBuffer, "%i" ,this->m_iSpan3 );
	this->m_szDataEntryCode += szBuffer;
	this->m_szDataEntryCode += ",";
	
	this->m_szDataEntryCode += "...,";

  //version
  	this->m_szDataEntryCode += APPLICATION_VERSION;
}	



//CDet3BeamHole /////////////////////////////////////////////////////////////////////////
CDet3BeamHole::CDet3BeamHole()
{
	m_Position = cIllegalHolePosition;
	m_lHoleSetBitfield = 0;
	m_bIsCountersunk = false;
}
CDet3BeamHole::~CDet3BeamHole()
{
}

BOOL CDet3BeamHole::Write( CBigIni& ABigIni, CString& szSection, int iHoleIndex )
{
	CString szEntry;
	CString szText;

  	if( this->m_Position != 0 )
  		{
	  //write comment
		szEntry.Format( "HoleComment#%i", iHoleIndex );
		ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szComment );	

	  //write position  	
		szEntry.Format( "HolePosition#%i", iHoleIndex );
	   	szText.Format( "%i", this->m_Position );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	
	
	  //write holetype
		szEntry.Format( "HoleType#%i", iHoleIndex );
		ABigIni.WritePrivateProfileString( szSection, szEntry, this->m_szHoleSetType );	

	  //write holetype paint bitfield
		szEntry.Format( "HolePaint#%i", iHoleIndex );
	   	szText.Format( "%i", this->m_lHoleSetBitfield );
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );	

		// Write if countersunk
		szEntry.Format("HoleIsCountersunk#%i", iHoleIndex);
		szText.Format("%i", m_bIsCountersunk);
		ABigIni.WritePrivateProfileString( szSection, szEntry, szText );
		
	   	}
	
	return TRUE;
}


BOOL CDet3BeamHole::Read( CBigIni& ABigIni, CString& szSection, int iHoleIndex )
{
	CString szEntry;
	CString szReturnBuffer;
	CString szDefault;
	int		iEntry = 0;

  //read position  	
	szEntry.Format( "HolePosition#%i", iHoleIndex );
	this->m_Position = ABigIni.GetPrivateProfileInt( szSection, szEntry, -1/*0*/ );
	if( this->m_Position == -1 )
		return FALSE;


  //read holetype paint bitfield
	szEntry.Format( "HolePaint#%i", iHoleIndex );
	this->m_lHoleSetBitfield = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );
	if( this->m_lHoleSetBitfield == -1 )
	{
		this->m_Position = 0;
		return FALSE;
	}

  //read comment
	szEntry.Format( "HoleComment#%i", iHoleIndex );
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szComment = szReturnBuffer;

  //read holetype
	szEntry.Format( "HoleType#%i", iHoleIndex );
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szHoleSetType = szReturnBuffer;
	
  //read countersink
	szEntry.Format( "HoleIsCountersunk#%i", iHoleIndex );
	iEntry = ABigIni.GetPrivateProfileInt( szSection, szEntry, 0 );

	if (iEntry != 1)
		m_bIsCountersunk = false;
	else 
		m_bIsCountersunk = true;


	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////////