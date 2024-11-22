// ProductData.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "ProductData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProductData

IMPLEMENT_DYNAMIC(CProductData, CDaoRecordset)

CProductData::CProductData(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CProductData)
	m_Aviion_Prodcode = _T("");
	m_ProductCode = _T("");
	m_Product_Type = _T("");
	m_ProductName = _T("");
	m_Aviion_Desc = _T("");
	m_Section_ID = _T("");
	m_Gauge = 0.0;
	m_Weight = 0.0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_Product_Ident = _T("");

}


CString CProductData::GetDefaultDBName()
{
	return _T("C:\\OD3Demo\\OD3DB_vhf.MDB");
}

CString CProductData::GetDefaultSQL()
{
	return _T("[SelectProductDataByCode]");
}

void CProductData::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CProductData)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Aviion Prodcode]"), m_Aviion_Prodcode);
	DFX_Text(pFX, _T("[ProductCode]"), m_ProductCode);
	DFX_Text(pFX, _T("[Product Type]"), m_Product_Type);
	DFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	DFX_Text(pFX, _T("[Aviion Desc]"), m_Aviion_Desc);
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
	DFX_Text(pFX, _T("Product_Ident"), m_Product_Ident);

}

/////////////////////////////////////////////////////////////////////////////
// CProductData diagnostics

#ifdef _DEBUG
void CProductData::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CProductData::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
