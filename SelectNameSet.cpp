// SelectNameSet.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "SelectNameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectNameSet

IMPLEMENT_DYNAMIC(CSelectNameSet, CDaoRecordset)

CSelectNameSet::CSelectNameSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSelectNameSet)
	m_Description = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CSelectNameSet::GetDefaultDBName()
{
	return _T("C:\\OD3Demo\\OD3DB_vhf.MDB");
}

CString CSelectNameSet::GetDefaultSQL()
{
	return _T("[Type1Products]");
}

void CSelectNameSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSelectNameSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Description]"), m_Description);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSelectNameSet diagnostics

#ifdef _DEBUG
void CSelectNameSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSelectNameSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
