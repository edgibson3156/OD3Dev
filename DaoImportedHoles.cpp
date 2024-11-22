// DaoImportedHoles.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DaoImportedHoles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoImportedHoles

IMPLEMENT_DYNAMIC(CDaoImportedHoles, CDaoRecordset)

CDaoImportedHoles::CDaoImportedHoles(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoImportedHoles)
	m_Additional_Hole_ID = 0;
	m_Section_ID = _T("");
	m_Punch_Code = _T("");
	m_Description = _T("");
	m_Dim_ID = _T("");
	m_On_Line = FALSE;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 2;
	m_Section_Ident = _T("");
	m_D3_HoleName = _T("");

}


CString CDaoImportedHoles::GetDefaultDBName()
{
	return _T("C:\\OD3\\Development\\Od3_jrdev\\OD3DB_vhf.MDB");
}

CString CDaoImportedHoles::GetDefaultSQL()
{
	return _T("[ExtraHoleCodesByD3Name]");
}

void CDaoImportedHoles::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoImportedHoles)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[Additional_Hole_ID]"), m_Additional_Hole_ID);
	DFX_Text(pFX, _T("[Section_ID]"), m_Section_ID);
	DFX_Text(pFX, _T("[Punch_Code]"), m_Punch_Code);
	DFX_Text(pFX, _T("[Description]"), m_Description);
	DFX_Text(pFX, _T("[Dim_ID]"), m_Dim_ID);
	DFX_Bool(pFX, _T("[On_Line]"), m_On_Line);
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
	DFX_Text(pFX, _T("D3_HoleName"), m_D3_HoleName);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoImportedHoles diagnostics

#ifdef _DEBUG
void CDaoImportedHoles::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoImportedHoles::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
