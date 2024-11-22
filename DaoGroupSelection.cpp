// DaoGroupSelection.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DaoGroupSelection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoGroupSelection

IMPLEMENT_DYNAMIC(CDaoGroupSelection, CDaoRecordset)

CDaoGroupSelection::CDaoGroupSelection(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoGroupSelection)
	m_Product_group = _T("");
	m_Section_ID = _T("");
	m_ProductName = _T("");
	m_Product_Type = _T("");
	m_RollSet_ID = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_ProductGroup = _T("");

}


CString CDaoGroupSelection::GetDefaultDBName()
{
	return _T("C:\\OD3\\Development\\Od3_jrdev\\OD3DB_vhf.MDB");
}

CString CDaoGroupSelection::GetDefaultSQL()
{
	return _T("[SectionsByProdGroup]");
}

void CDaoGroupSelection::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoGroupSelection)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Product_group]"), m_Product_group);
	DFX_Text(pFX, _T("[Section_ID]"), m_Section_ID);
	DFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	DFX_Text(pFX, _T("[Product Type]"), m_Product_Type);
	DFX_Text(pFX, _T("[RollSet_ID]"), m_RollSet_ID);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("ProductGroup"), m_ProductGroup);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoGroupSelection diagnostics

#ifdef _DEBUG
void CDaoGroupSelection::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoGroupSelection::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
