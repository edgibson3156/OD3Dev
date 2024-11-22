// SpcScript.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "SpcScript.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpcScript

IMPLEMENT_DYNAMIC(CSpcScript, CDaoRecordset)

CSpcScript::CSpcScript(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSpcScript)
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
}


CString CSpcScript::GetDefaultDBName()
{
	return _T("I:\\SOFT_ENG\\OD3\\D_BASE\\Od3db.mdb");
}

CString CSpcScript::GetDefaultSQL()
{
	return _T("[OPERATION_SCRIPTS]");
}

void CSpcScript::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSpcScript)
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
}

/////////////////////////////////////////////////////////////////////////////
// CSpcScript diagnostics

#ifdef _DEBUG
void CSpcScript::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSpcScript::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
