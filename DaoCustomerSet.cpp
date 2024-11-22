// DaoCustomerSet.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DaoCustomerSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoCustomerSet

IMPLEMENT_DYNAMIC(CDaoCustomerSet, CDaoRecordset)

CDaoCustomerSet::CDaoCustomerSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoCustomerSet)
	m_Aviion_Prodcode = _T("");
	m_Product_Type = _T("");
	m_ProductName = _T("");
	m_Section_ID = _T("");
	m_Gauge = 0.0;
	m_Weight = 0.0;
	m_Aviion_Desc = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_Customer_Filter = _T("");

}


CString CDaoCustomerSet::GetDefaultDBName()
{
	return _T("C:\\OD3\\Development\\Od3_jrdev\\OD3DB_vhf.MDB");
}

CString CDaoCustomerSet::GetDefaultSQL()
{
	return _T("[SelectProductByCustomer]");
}

void CDaoCustomerSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoCustomerSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Aviion Prodcode]"), m_Aviion_Prodcode);
	DFX_Text(pFX, _T("[Product Type]"), m_Product_Type);
	DFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	DFX_Text(pFX, _T("[Section_ID]"), m_Section_ID);
	DFX_Double(pFX, _T("[Gauge]"), m_Gauge);
	DFX_Double(pFX, _T("[Weight]"), m_Weight);
	DFX_Text(pFX, _T("[Aviion Desc]"), m_Aviion_Desc);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("Customer_Filter"), m_Customer_Filter);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoCustomerSet diagnostics

#ifdef _DEBUG
void CDaoCustomerSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoCustomerSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
