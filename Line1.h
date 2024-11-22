// Line1.h: interface for the CLine1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE1_H__89DC71E1_2F93_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_LINE1_H__89DC71E1_2F93_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "OD3Doc.h"
#include "Element.h"
#include "Item.h"

class CItem;

class CLine1 : public CObject  
{
private:
	static const int MAX_MARK_LENGTH;

public:
	COD3Doc* m_pDoc;

public:
	CLine1() {};
	virtual ~CLine1() {};

	void GetNewFileName(CString& szFileName);
	void GetPartFileName( CString* psz, CString& szItemID);	
	void BuildDetails(CItem* pItem);
	BOOL ValidMarkLength (short MarkLength) 
			 { return (MarkLength > 0 && MarkLength <= MAX_MARK_LENGTH); }
};

#endif // !defined(AFX_LINE1_H__89DC71E1_2F93_11D3_913F_00104BBA02E4__INCLUDED_)
