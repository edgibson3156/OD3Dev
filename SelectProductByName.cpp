// SelectProductByName.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "SelectProductByName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectProductByName

IMPLEMENT_DYNAMIC(CSelectProductByName, CDaoRecordset)

CSelectProductByName::CSelectProductByName(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSelectProductByName)
	m_ProductCode = _T("");
	m_Aviion_Prodcode = _T("");
	m_Product_Type = _T("");
	m_ProductName = _T("");
	m_Section_ID = _T("");
	m_Gauge = 0.0;
	m_Weight = 0.0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 2;
	m_Aviion_Name = _T("");
	m_Customer_Filter = _T("");
}


CString CSelectProductByName::GetDefaultDBName()
{
	return _T("C:\\OD3Demo\\OD3DB_vhf.MDB");
}

CString CSelectProductByName::GetDefaultSQL()
{
	return _T("[SelectProductByName]");
}

void CSelectProductByName::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSelectProductByName)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[ProductCode]"), m_ProductCode);
	DFX_Text(pFX, _T("[Aviion Prodcode]"), m_Aviion_Prodcode);
	DFX_Text(pFX, _T("[Product Type]"), m_Product_Type);
	DFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	DFX_Text(pFX, _T("[Section_ID]"), m_Section_ID);
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
	DFX_Text(pFX, _T("Aviion_Name"), m_Aviion_Name);
	DFX_Text(pFX, _T("Customer_Filter"), m_Customer_Filter);

}

/////////////////////////////////////////////////////////////////////////////
// CSelectProductByName diagnostics

#ifdef _DEBUG
void CSelectProductByName::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSelectProductByName::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
