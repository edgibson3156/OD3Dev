// Scripts.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "Scripts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScripts

IMPLEMENT_DYNAMIC(CScripts, CDaoRecordset)

CScripts::CScripts(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CScripts)
	m_Op_Script_ID = 0;
	m_Operation_Sequence_No = 0;
	m_Operation = _T("");
	m_Operation_Code = _T("");
	m_Operation_Type = _T("");
	m_Absolute = FALSE;
	m_Positive = FALSE;
	m_Multiplied = FALSE;
	m_MultiplierValue = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 3;
	m_Line_Ident = _T("");
	m_Section_Ident = _T("");
	m_SPC_Ident = _T("");

}


CString CScripts::GetDefaultDBName()
{
	return _T("D:\\Soft_Eng\\Development\\Od3db.mdb");
}

CString CScripts::GetDefaultSQL()
{
	return _T("[SelectOpScriptbyLineSecSPC]");
}

void CScripts::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CScripts)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[Op_Script_ID]"), m_Op_Script_ID);
	DFX_Long(pFX, _T("[Operation_Sequence_No]"), m_Operation_Sequence_No);
	DFX_Text(pFX, _T("[Operation]"), m_Operation);
	DFX_Text(pFX, _T("[Operation_Code]"), m_Operation_Code);
	DFX_Text(pFX, _T("[Operation_Type]"), m_Operation_Type);
	DFX_Bool(pFX, _T("[Absolute]"), m_Absolute);
	DFX_Bool(pFX, _T("[Positive]"), m_Positive);
	DFX_Bool(pFX, _T("[Multiplied]"), m_Multiplied);
	DFX_Short(pFX, _T("[MultiplierValue]"), m_MultiplierValue);
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
	DFX_Text(pFX, _T("SPC_Ident"), m_SPC_Ident);

}

/////////////////////////////////////////////////////////////////////////////
// CScripts diagnostics

#ifdef _DEBUG
void CScripts::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CScripts::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
