// DaoDimValue.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DaoDimValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoDimValue

IMPLEMENT_DYNAMIC(CDaoDimValue, CDaoRecordset)

CDaoDimValue::CDaoDimValue(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoDimValue)
	m_Dimension_Value = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 2;
	m_Section_Ident = _T("");
	m_Dim_Ident = _T("");

}


CString CDaoDimValue::GetDefaultDBName()
{
	return _T("C:\\OD3\\Development\\Od3_jrdev\\OD3DB_vhf.MDB");
}

CString CDaoDimValue::GetDefaultSQL()
{
	return _T("[SelectDimValueBySection]");
}

void CDaoDimValue::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoDimValue)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Dimension_Value]"), m_Dimension_Value);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("Section_Ident"), m_Section_Ident);
	DFX_Text(pFX, _T("Dim_Ident"), m_Dim_Ident);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoDimValue diagnostics

#ifdef _DEBUG
void CDaoDimValue::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoDimValue::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
