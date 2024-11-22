// SelectSectionSet.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "SelectSectionSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectSectionSet

IMPLEMENT_DYNAMIC(CSelectSectionSet, CDaoRecordset)

CSelectSectionSet::CSelectSectionSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSelectSectionSet)
	m_RollSet_ID = _T("");
	m_Product_group = _T("");
	m_Depth = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CSelectSectionSet::GetDefaultDBName()
{
	return _T("C:\\OD3Demo\\OD3DB_vhf.MDB");
}

CString CSelectSectionSet::GetDefaultSQL()
{
	return _T("[ROLL_SETS]");
}

void CSelectSectionSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSelectSectionSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[RollSet_ID]"), m_RollSet_ID);
	DFX_Text(pFX, _T("[Product_group]"), m_Product_group);
	DFX_Long(pFX, _T("[Depth]"), m_Depth);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSelectSectionSet diagnostics

#ifdef _DEBUG
void CSelectSectionSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSelectSectionSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
