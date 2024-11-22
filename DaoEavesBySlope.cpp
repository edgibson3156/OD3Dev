// DaoEavesBySlope.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoEavesBySlope.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoEavesBySlope

IMPLEMENT_DYNAMIC(CDaoEavesBySlope, CDaoRecordset)

CDaoEavesBySlope::CDaoEavesBySlope(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoEavesBySlope)
	m_ProductCode = _T("");
	m_ProductName = _T("");
	m_Angle = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 2;
	m_iAngle = 0;
	m_Prod_name = _T("");

}


CString CDaoEavesBySlope::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\Od3_2_5_13.mdb");
}

CString CDaoEavesBySlope::GetDefaultSQL()
{
	return _T("[SelectEavesBySlope]");
}

void CDaoEavesBySlope::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoEavesBySlope)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[ProductCode]"), m_ProductCode);
	DFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	DFX_Short(pFX, _T("[Angle]"), m_Angle);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Short(pFX, _T("iAngle"), m_iAngle);
	DFX_Text(pFX, _T("Prod_name"), m_Prod_name);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoEavesBySlope diagnostics

#ifdef _DEBUG
void CDaoEavesBySlope::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoEavesBySlope::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
