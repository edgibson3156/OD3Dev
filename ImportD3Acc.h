// ImportD3Acc.h: interface for the CImportD3Acc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTD3ACC_H__C32195C8_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_IMPORTD3ACC_H__C32195C8_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BigIni.h"

class CImportD3Acc : public CObject  
{
private:
	CString m_szDataEntryCode;
	CString m_szDrawingNumber;
	CString	m_szComment;
	CString	m_szDate;
	CString m_szType;
	CString m_szMark;

	/********* NEW *********/
	CString m_szProductType;
	CString m_szSectionType;
	CString m_szSectionSize;
	CString m_szProductName;
	// Bracings //
	int m_iSlope;
	int m_iCentres;
	//////////////

	// Cleats
	int m_iDimX;
	int m_iSheetLine;
	//////////////

	// Sleeves //
	int m_iCleatHoleCentres;
	/////////////
	/******* END NEW *******/

	short 	m_iQty;
	short 	m_iField[5];
	
	int		m_iDimA;
	int		m_iDimB;
	//int		m_iDimC;
	//int		m_iDimE;
	//int		m_iDimF;
	int		m_iDimG;
	int		m_iDimH;
	//int		m_iDimJ;
	int  	m_iSleeveLength;
	int  	m_iCleatEndDim;

public:
	CImportD3Acc();
	virtual ~CImportD3Acc();

	bool Read( CBigIni& ABigIni, int iAccessoryIndex );
	BOOL Write( CBigIni& ABigIni, int iAccessoryIndex );

	void Reset( void );
	BOOL CheckValid( void );
	
	LPCSTR GetComment()				{ return (LPCSTR)(const char*)this->m_szComment; }
	void SetComment( LPSTR lpsz )	{ this->m_szComment = lpsz; }

	void SetType( LPSTR lpsz )	{ this->m_szType =lpsz; }
	LPCSTR GetType( void ) 		{ return (const char*)this->m_szType; }	

	void SetMark( LPSTR lpsz )	{ this->m_szMark =lpsz; }
	LPCSTR GetMark( void ) 		{ return (const char*)this->m_szMark; }
	
	void SetProductType(LPSTR lpsz)	{ this->m_szProductType =lpsz; }
	LPCSTR GetProductType(void) 	{ return (const char*)this->m_szProductType; }	

	void SetSectionType(LPSTR lpsz)	{ this->m_szSectionType =lpsz; }
	LPCSTR GetSectionType(void)		{ return (const char*)this->m_szSectionType; }	

	void SetSectionSize(LPSTR lpsz)	{ this->m_szSectionSize =lpsz; }
	LPCSTR GetSectionSize(void) 	{ return (const char*)this->m_szSectionSize; }
	
	void SetProductName(LPSTR lpsz)	{ this->m_szProductName =lpsz; }
	LPCSTR GetProductName(void) 	{ return (const char*)this->m_szProductName; }	

	void SetQty(short i)		{this->m_iQty =i;}
	short GetQty(void)	 		{return this->m_iQty;}
	
	void SetSlope(short i)		{this->m_iSlope =i;}
	short GetSlope(void) 		{return this->m_iSlope;}

	void SetCentres(short i)	{this->m_iCentres =i;}
	short GetCentres(void) 		{return this->m_iCentres;}

	void SetDimX(short i)		{this->m_iDimX =i;}
	short GetDimX(void) 		{return this->m_iDimX;}

	void SetSheetLine(short i)	{this->m_iSheetLine =i;}
	short GetSheetLine(void) 	{return this->m_iSheetLine;}

	void SetCleatHoleCentres(short i)	{this->m_iCleatHoleCentres =i; }
	short GetCleatHoleCentres(void) 	{return this->m_iCleatHoleCentres; }

	void SetField1( short i )	{ this->m_iField[0] =i; }
	short GetField1( void ) 	{ return this->m_iField[0]; }	
	void SetField2( short i )	{ this->m_iField[1] =i; }
	short GetField2( void ) 	{ return this->m_iField[1]; }	
	void SetField3( short i )	{ this->m_iField[2] =i; }
	short GetField3( void ) 	{ return this->m_iField[2]; }	
	void SetField4( short i )	{ this->m_iField[3] =i; }
	short GetField4( void ) 	{ return this->m_iField[3]; }	
	void SetField5( short i )	{ this->m_iField[4] =i; }
	short GetField5( void ) 	{ return this->m_iField[4]; }	
	void SetField( short iIndex, short i )	{ this->m_iField[iIndex] =i; }
	short GetField( short iIndex ) 	{ return this->m_iField[iIndex]; }	
	
	void SetDimA( int i )		{ this->m_iDimA = i; }
	int GetDimA( void )			{ return this->m_iDimA; }
	void SetDimB( int i )		{ this->m_iDimB = i; }
	int GetDimB( void )			{ return this->m_iDimB; }

	//void SetDimC( int i )		{ this->m_iDimC = i; }
	//int GetDimC( void )			{ return this->m_iDimC; }
	//void SetDimE( int i )		{ this->m_iDimE = i; }
	//int GetDimE( void )			{ return this->m_iDimE; }

	//void SetDimF( int i )		{ this->m_iDimF = i; }
	//int GetDimF( void )			{ return this->m_iDimF; }

	void SetDimG( int i )		{ this->m_iDimG = i; }
	int GetDimG( void )			{ return this->m_iDimG; }

	void SetDimH( int i )		{ this->m_iDimH = i; }
	int GetDimH( void )			{ return this->m_iDimH; }

	//void SetDimJ( int i )		{ this->m_iDimJ = i; }
	//int GetDimJ( void )			{ return this->m_iDimJ; }

	void SetSleeveLength( int i ) { this->m_iSleeveLength = i; }
	int GetSleeveLength( void )	  { return this->m_iSleeveLength; }

	void SetCleatEndDim( int i )  { this->m_iCleatEndDim = i; }
	int GetCleatEndDim( void )	  { return this->m_iCleatEndDim; }

	void SetDate( LPSTR lpsz )	{ this->m_szDate =lpsz; }
	LPCSTR GetDate( void ) 		{ return (const char*)this->m_szDate; }	
	void SetDateToday( void );

	void SetDrawingNumber( LPSTR lpsz )	{ this->m_szDrawingNumber = lpsz; }
	LPCSTR GetDrawingNumber( void ) 	{ return (LPCSTR)(const char*)this->m_szDrawingNumber; }	

//	void Copy( CImportD3Acc* pTarget );	

	int IntComputeDimensionFromScript( LPSTR lpszSource );
    LPCSTR szComputeDimensionFromScript( LPSTR lpszSource );
        
    void ComputeDataEntryString( void );
    LPCSTR GetDataEntryString( void ) 	{ return (LPCSTR)(const char*)this->m_szDataEntryCode; }

/*	BOOL ReadAccList( CBigIni& ABigIni );
	BOOL WriteAccList( CBigIni& ABigIni );

	BOOL ItemMarkExists( LPCSTR lpszTestMark );
	CImportD3Acc* FindRecord( LPCSTR lpszTestMark );
//	BOOL Copy( CImportD3Acc* pTarget, LPCSTR lpszTestMark );	
    int GetIndex( CImportD3Acc* pAccessory );
    BOOL IsHead( CImportD3Acc* pAccessory );
    BOOL IsTail( CImportD3Acc* pAccessory );
	BOOL DeleteRecord( CImportD3Acc* pAccessory );

	void SortByAssendingProductName( void );
	void SortByAssendingMark( void );
	void Swap( CImportD3Acc* pAccessory1, CImportD3Acc* pAccessory2 );

	void Free( void );	
*/
};

/*
class CImportD3AccList: public CObList
{
private:
	
public:
	CImportD3AccList();
	~CImportD3AccList();

	BOOL ReadList( CBigIni& ABigIni );
	BOOL WriteList( CBigIni& ABigIni );

	BOOL ItemMarkExists( LPCSTR lpszTestMark );
	CImportD3Acc* FindRecord( LPCSTR lpszTestMark );
	BOOL Copy( CImportD3Acc* pTarget, LPCSTR lpszTestMark );	
    int GetIndex( CImportD3Acc* pAccessory );
    BOOL IsHead( CImportD3Acc* pAccessory );
    BOOL IsTail( CImportD3Acc* pAccessory );
	BOOL DeleteRecord( CImportD3Acc* pAccessory );

	void SortByAssendingProductName( void );
	void SortByAssendingMark( void );
	void Swap( CImportD3Acc* pAccessory1, CImportD3Acc* pAccessory2 );

	void Free( void );	
};
*/

#endif // !defined(AFX_IMPORTD3ACC_H__C32195C8_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
