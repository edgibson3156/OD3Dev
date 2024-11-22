// DaoProductCode.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DaoProductCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoProductCode

IMPLEMENT_DYNAMIC(CDaoProductCode, CDaoRecordset)

CDaoProductCode::CDaoProductCode(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoProductCode)
	m_ProductCode = _T("");
	m_Product_Type = _T("");
	m_ProductName = _T("");
	m_Section_ID = _T("");
	m_Gauge = 0.0;
	m_Weight = 0.0;
	m_Aviion_Desc = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 2;
	m_Type_Ident = _T("");
	m_Product_Name_Ident = _T("");

}


CString CDaoProductCode::GetDefaultDBName()
{
	return _T("C:\\OD3\\Development\\Od3_jrdev\\OD3DB_vhf.MDB");
}

CString CDaoProductCode::GetDefaultSQL()
{
	return _T("[SelectProductByNameType]");
}

void CDaoProductCode::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoProductCode)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[ProductCode]"), m_ProductCode);
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
	DFX_Text(pFX, _T("Type_Ident"), m_Type_Ident);
	DFX_Text(pFX, _T("Product_Name_Ident"), m_Product_Name_Ident);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoProductCode diagnostics

#ifdef _DEBUG
void CDaoProductCode::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoProductCode::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
