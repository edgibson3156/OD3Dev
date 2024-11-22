// ImportD3Beam.h: interface for the CImportD3Beam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTD3BEAM_H__C32195C9_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_IMPORTD3BEAM_H__C32195C9_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bigini.h"
#include "element.h"


enum arragement_e
	{
	IllegalArrangement,
	Butted,
	DoubleSpan,
	FireScreen,
	HeavyEndBay,
	NonStandardArrangement,
	Overlap,
	Sleeved,
	EavesBeamNonStandardArrangement,
	EavesBeamStandOff,
	EavesBeamFlush,
	CWSleeved,
	};

enum beamposition_e
	{
	IllegalPosition,
	SleevedInternal,
	SleevedLeftGable,
	SleevedRightGable,
	DoubleInternal,
	DoubleLeftGable,
	DoubleRightGable,
	OverlapLeftEnd,
	OverlapLeftPenultimate,
	OverlapInternal,
	OverlapRightPenultimate,
	OverlapRightEnd,
	FireScreenInternal,
	FireScreenLeft,
	FireScreenRight,
	NonStandardPosition,
	ButtedInternal,
	ButtedLeftGable,
	ButtedRightGable,
	EavesBeamNonStandardPosition,
	EavesBeamStandOffInternal,
	EavesBeamStandOffLeftGable,
	EavesBeamStandOffRightGable,
	EavesBeamFlushInternal,
	};

enum membertype_e
	{
	IllegalMember,
	Purlin,
	Rail,
	Pressed = 8,
	Stud = 9,
	Floor_Joist = 10
	};

enum bracing_e
	{
	NoBracing,
	MidSpan,
	ThirdPoints,
	};

extern const int cIllegalHolePosition;


class CDet3BeamHole: public CObject
	{
	private:
		int		m_Position;
		bool	m_bIsCountersunk;
		long 	m_lHoleSetBitfield;
		CString m_szHoleSetType;
		CString m_szComment;
	
	public:
		CDet3BeamHole();
		~CDet3BeamHole();
		
		BOOL Read( CBigIni& ABigIni, CString& lpszSection, int iHoleIndex );
		BOOL Write( CBigIni& ABigIni, CString& szSection, int iHoleIndex );

		int	GetCSunk()			{ return this->m_bIsCountersunk; }
		void SetCSunk( bool b )	{ this->m_bIsCountersunk = b; }

		int	GetPosition()			{ return this->m_Position; }
		void SetPosition( int i )	{ this->m_Position = i; }

		LPCSTR GetHoleSetType()				{ return (LPCSTR)(const char*)this->m_szHoleSetType; }
		void SetHoleSetType( LPSTR lpsz )	{ this->m_szHoleSetType = lpsz; }

		long GetHoleSetBitfield()			{ return this->m_lHoleSetBitfield; }
		void SetHoleSetBitfield( long l )	{ this->m_lHoleSetBitfield = l; }

		LPCSTR GetComment()				{ return (LPCSTR)(const char*)this->m_szComment; }
		void SetComment( LPSTR lpsz )	{ this->m_szComment = lpsz; }
};

class CImportD3Beam : public CObject  
{
public:
	CTypedPtrList<CObList, CDet3BeamHole*>	m_tplHoleList;

private:
	arragement_e 	eArrangement;	
	beamposition_e  ePosition;
	membertype_e	eMemberType;
	bracing_e       eBracing;
	bracing_e       eBracing2;
	CString 	m_szDataEntryCode;
	CString		m_szStandardPartCode;
	CString 	FindElementByID;
	CString 	m_szDrawingNumber;
	CString 	m_szMark;
	int 		m_iQty; 
	int			m_iLength;
	int			m_iSpan1;
	int			m_iSpan2;
	int			m_iSpan3;
	int			m_iOverhang1;
	int			m_iOverhang2;
	int			m_iTPBSlope;
	int			m_iSlope;
	int			m_iColumn1;
	int			m_iColumn2;
	double		m_dGauge;
	int			m_iLipLengthBottom;
	int			m_iLipLengthTop;

	CString		m_szComment;
	CString		m_szGauge;
	CString		m_szDate;
	CString 	m_szProductType;
	CString 	m_szProductGroup;
	CString 	m_szProductID;
	long		m_lProductGroupID;

	int		m_iDimA;
	int		m_iDimB;
	int		m_iDimC;
	int		m_iDimE;
	int		m_iDimF;
	int		m_iDimG;
	int		m_iDimH;
	int		m_iDimJ;
	int		m_iDimT;

	int	m_iCleatHoleCentres;
	int	m_iServiceHoles;

	CString m_szSectionType;
	CString m_szSectionSize;
	CString m_szArrangementTxt;
	CString m_szSubArrangementTxt;

public:
	CImportD3Beam();
	virtual ~CImportD3Beam();

	bool Read( CBigIni& ABigIni, int iBeamIndex );
	bool readASFPanels(void *pvImport, int index);
	BOOL Write( CBigIni& ABigIni, int iIndex );


	LPCSTR GetComment()				{ return (LPCSTR)(const char*)this->m_szComment; }
	void SetComment( LPSTR lpsz )	{ this->m_szComment = lpsz; }

	LPCSTR GetProductGroup()			{ return (LPCSTR)(const char*)this->m_szProductGroup; }
	void SetProductGroup( LPSTR lpsz )	{ this->m_szProductGroup = lpsz; }

	LPCSTR GetProductType()			{ return (LPCSTR)(const char*)this->m_szProductType; }
	void SetProductType( LPSTR lpsz )	{ this->m_szProductType = lpsz; }

	long GetProductGroupID()			{ return this->m_lProductGroupID; }
	void SetProductGroupID( long l )	{ this->m_lProductGroupID = l; }

	void SetLength( LPSTR lpsz ){ this->m_iLength = atoi( lpsz ); }
	void SetLength( int i )		{ this->m_iLength = i; }
	int GetLength( void )		{ return this->m_iLength; }

	void SetSpan1( LPSTR lpsz )	{ this->m_iSpan1 = atoi( lpsz ); }
	void SetSpan1( int i )		{ this->m_iSpan1 = i; }
	int GetSpan1( void )		{ return this->m_iSpan1; }

	void SetSpan2( LPSTR lpsz )	{ this->m_iSpan2 = atoi( lpsz ); }
	void SetSpan2( int i )		{ this->m_iSpan2 = i; }
	int GetSpan2( void )		{ return this->m_iSpan2; }

	void SetSpan3( LPSTR lpsz )	{ this->m_iSpan3 = atoi( lpsz ); }
	void SetSpan3( int i )		{ this->m_iSpan3 = i; }
	int GetSpan3( void )		{ return this->m_iSpan3; }

	void SetOverhang1( LPSTR lpsz )	{ this->m_iOverhang1 = atoi( lpsz ); }
	void SetOverhang1( int i )		{ this->m_iOverhang1 = i; }
	int GetOverhang1( void )		{ return this->m_iOverhang1; }

	void SetOverhang2( LPSTR lpsz )	{ this->m_iOverhang2 = atoi( lpsz ); }
	void SetOverhang2( int i )		{ this->m_iOverhang2 = i; }
	int GetOverhang2( void )		{ return this->m_iOverhang2; }

	void SetTPBSlope( LPSTR lpsz )	{ this->m_iTPBSlope = atoi( lpsz ); }
	void SetTPBSlope( int i )		{ this->m_iTPBSlope = i; }
	int GetTPBSlope( void )			{ return this->m_iTPBSlope; }

	void SetSlope( LPSTR lpsz )		{ this->m_iSlope = atoi( lpsz ); }
	void SetSlope( int i )			{ this->m_iSlope = i; }
	int GetSlope( void )			{ return this->m_iSlope; }

	void SetColumn1( LPSTR lpsz )	{ this->m_iColumn1 = atoi( lpsz ); }
	void SetColumn1( int i )		{ this->m_iColumn1 = i; }
	int GetColumn1( void )			{ return this->m_iColumn1; }

	void SetColumn2( LPSTR lpsz )	{ this->m_iColumn2 = atoi( lpsz ); }
	void SetColumn2( int i )		{ this->m_iColumn2 = i; }
	int GetColumn2( void )			{ return this->m_iColumn2; }
//
	void SetGauge( LPSTR lpsz )		{ this->m_dGauge = atof( lpsz ); }
	void SetGauge( double x )		{ this->m_dGauge = x; }
	double GetGauge( void )			{ return this->m_dGauge; }

	void SetTopLip( LPSTR lpsz )	{ this->m_iLipLengthTop = atoi( lpsz ); }
	void SetTopLip( int i )			{ this->m_iLipLengthTop = i; }
	int GetTopLip( void )			{ return this->m_iLipLengthTop; }

	void SetBottomLip( LPSTR lpsz )	{ this->m_iLipLengthBottom = atoi( lpsz ); }
	void SetBottomLip( int i )		{ this->m_iLipLengthBottom = i; }
	int GetBottomLip( void )		{ return this->m_iLipLengthBottom; }
//
	void SetProductName(LPSTR lpsz)	{this->m_szProductID = lpsz;}
	LPCSTR GetProductName(void) 	{return (LPCSTR)(const char*)this->m_szProductID;}	

	void SetDrawingNumber( LPSTR lpsz )	{ this->m_szDrawingNumber = lpsz; }
	LPCSTR GetDrawingNumber( void ) 	{ return (LPCSTR)(const char*)this->m_szDrawingNumber; }	

	void SetMark( LPSTR lpsz )	{ this->m_szMark =lpsz; }
	LPCSTR GetMark( void ) 		{ return (const char*)this->m_szMark; }	

	void SetQty( int i )		{ this->m_iQty =i; }
	int GetQty( void ) 			{ return this->m_iQty; }	

	void SetDate( LPSTR lpsz )	{ this->m_szDate =lpsz; }
	LPCSTR GetDate( void ) 		{ return (const char*)this->m_szDate; }	
	void SetDateToday( void );

	arragement_e GetArrangement( void )				{ return this->eArrangement; }			
	void SetArrangement( arragement_e eArrangement ){ this->eArrangement = eArrangement; }			

	beamposition_e GetPosition( void )				{ return this->ePosition; }			
	void SetPosition( beamposition_e ePosition )	{ this->ePosition = ePosition; }			
       
    void ComputeSPC( void );
    LPSTR CImportD3Beam::ComputeSPCPrefix( void );
    LPCSTR ComputeSPCBracingAttribute( void );
    LPCSTR GetSPC( void )		{ return (LPCSTR)(const char*)this->m_szStandardPartCode; }
    void SetSPC( LPCSTR lpsz )	{ this->m_szStandardPartCode =lpsz; }
        
	membertype_e GetMemberType( void ) 				{ return eMemberType; }
	void SetMemberType( membertype_e eMemberType ) 	{ this->eMemberType = eMemberType; }
		
	bracing_e GetBracing( void )	{ return this->eBracing; }
	void SetBracing( bracing_e e )	{ this->eBracing = e; }
			
	void SetBeamDefaults( void );

	LPCSTR szComputeDimensionFromScript( LPSTR lpszSource );
	int IntComputeDimensionFromScript( LPSTR lpszSource );

    void ComputeDataEntryString( void );
    LPCSTR GetDataEntryString( void ) 	{ return (LPCSTR)(const char*)this->m_szDataEntryCode; }

	void SetDimA( int i )		{ this->m_iDimA = i; }
	int GetDimA( void )			{ return this->m_iDimA; }

	void SetDimB( int i )		{ this->m_iDimB = i; }
	int GetDimB( void )			{ return this->m_iDimB; }

	void SetDimC( int i )		{ this->m_iDimC = i; }
	int GetDimC( void )			{ return this->m_iDimC; }

	void SetDimE( int i )		{ this->m_iDimE = i; }
	int GetDimE( void )			{ return this->m_iDimE; }

	void SetDimF( int i )		{ this->m_iDimF = i; }
	int GetDimF( void )			{ return this->m_iDimF; }

	void SetDimG( int i )		{ this->m_iDimG = i; }
	int GetDimG( void )			{ return this->m_iDimG; }

	void SetDimH( int i )		{ this->m_iDimH = i; }
	int GetDimH( void )			{ return this->m_iDimH; }

	void SetDimJ( int i )		{ this->m_iDimJ = i; }
	int GetDimJ( void )			{ return this->m_iDimJ; }

	void SetDimT( int i )		{ this->m_iDimT = i; }
	int GetDimT( void )			{ return this->m_iDimT; }

	CString GetSectionType(void)		{ return(m_szSectionType); };
	void SetSectionType(CString sType)	{ m_szSectionType=sType; };

	CString GetSectionSize(void)		{ return(m_szSectionSize); };
	void SetSectionSize(CString sSize)	{ m_szSectionSize=sSize; };

	
	bool ReadList( CBigIni& ABigIni );
	bool WriteList( CBigIni& ABigIni );
	void Free( void );	

	BOOL ItemMarkExists( LPCSTR lpszTestMark );
	CImportD3Beam* FindRecord( LPCSTR lpszTestMark );
    int GetIndex( CImportD3Beam* pBeam );
	BOOL IsHead( CImportD3Beam* pBeam );
	BOOL IsTail( CImportD3Beam* pBeam );
	BOOL DeleteRecord( CImportD3Beam* pBeam );
		
	void SortByAssendingProductName( void );
	void SortByAssendingMark( void );
	void Swap( CImportD3Beam* pBeam1, CImportD3Beam* pBeam2 );
	void AddExtraHolesToList(CBeamElement* pBeam);
};
/*
	class CImportD3BeamList: public CObList
	{
	private:
	
	public:
		CImportD3BeamList();
		~CImportD3BeamList();

		BOOL ReadList( CBigIni& ABigIni );
		BOOL WriteList( CBigIni& ABigIni );
		void Free( void );	

		BOOL ItemMarkExists( LPCSTR lpszTestMark );
		CImportD3Beam* FindRecord( LPCSTR lpszTestMark );
		BOOL Copy( CImportD3Beam* pTarget, LPCSTR lpszTestMark );	
        int GetIndex( CImportD3Beam* pBeam );
		BOOL IsHead( CImportD3Beam* pBeam );
		BOOL IsTail( CImportD3Beam* pBeam );
		BOOL DeleteRecord( CImportD3Beam* pBeam );
		
		void SortByAssendingProductName( void );
		void SortByAssendingMark( void );
		void Swap( CImportD3Beam* pBeam1, CImportD3Beam* pBeam2 );
};
*/


#endif // !defined(AFX_IMPORTD3BEAM_H__C32195C9_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
