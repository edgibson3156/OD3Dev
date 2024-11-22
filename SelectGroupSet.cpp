// SelectGroupSet.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "SelectGroupSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectGroupSet

IMPLEMENT_DYNAMIC(CSelectGroupSet, CDaoRecordset)

CSelectGroupSet::CSelectGroupSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSelectGroupSet)
	m_Product_group = _T("");
	m_DisplayFlag = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CSelectGroupSet::GetDefaultDBName()
{
	return _T("C:\\OD3Demo\\OD3DB_vhf.MDB");
}

CString CSelectGroupSet::GetDefaultSQL()
{
	return _T("[ProductGroups]");
}

void CSelectGroupSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSelectGroupSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Product_group]"), m_Product_group);
	DFX_Byte(pFX, _T("[DisplayFlag]"), m_DisplayFlag);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSelectGroupSet diagnostics

#ifdef _DEBUG
void CSelectGroupSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSelectGroupSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
