// DaoGetIgnore.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoGetIgnore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoGetIgnore

IMPLEMENT_DYNAMIC(CDaoGetIgnore, CDaoRecordset)

CDaoGetIgnore::CDaoGetIgnore(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoGetIgnore)
	m_Product_Name = _T("");
	m_Product_Type = _T("");
	m_Description = _T("");
	m_Gauge = 0.0;
	m_Weight = 0.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_Sel_Name = _T("");

}


CString CDaoGetIgnore::GetDefaultDBName()
{
	return _T("C:\\Ayrshire\\OD3\\Database\\Od3_2_5_6.mdb");
}

CString CDaoGetIgnore::GetDefaultSQL()
{
	return _T("[GetIgnoredProduct]");
}

void CDaoGetIgnore::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoGetIgnore)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Product_Name]"), m_Product_Name);
	DFX_Text(pFX, _T("[Product_Type]"), m_Product_Type);
	DFX_Text(pFX, _T("[Description]"), m_Description);
	DFX_Double(pFX, _T("[Gauge]"), m_Gauge);
	DFX_Double(pFX, _T("[Weight]"), m_Weight);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("Sel_Name"), m_Sel_Name);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoGetIgnore diagnostics

#ifdef _DEBUG
void CDaoGetIgnore::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoGetIgnore::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
