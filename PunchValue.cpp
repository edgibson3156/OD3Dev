// PunchValue.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "PunchValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPunchValue

IMPLEMENT_DYNAMIC(CPunchValue, CDaoRecordset)

CPunchValue::CPunchValue(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPunchValue)
	m_Value = 0.0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 4;
	m_Line_Ident = _T("");
	m_Section_Ident = _T("");
	m_Script_Ident = 0;
	m_Punch_Ident = _T("");

}


CString CPunchValue::GetDefaultDBName()
{
	return _T("D:\\Soft_Eng\\Development\\Od3db.mdb");
}

CString CPunchValue::GetDefaultSQL()
{
	return _T("[SelectPunchbyLineSecScript]");
}

void CPunchValue::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPunchValue)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Double(pFX, _T("[Value]"), m_Value);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("Line_Ident"), m_Line_Ident);
	DFX_Text(pFX, _T("Section_Ident"), m_Section_Ident);
	DFX_Long(pFX, _T("Script_Ident"), m_Script_Ident);
	DFX_Text(pFX, _T("Punch_Ident"), m_Punch_Ident);

}

/////////////////////////////////////////////////////////////////////////////
// CPunchValue diagnostics

#ifdef _DEBUG
void CPunchValue::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CPunchValue::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
