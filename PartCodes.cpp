// PartCodes.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "PartCodes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPartCodes

IMPLEMENT_DYNAMIC(CPartCodes, CDaoRecordset)

CPartCodes::CPartCodes(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPartCodes)
	m_Description = _T("");
	m_PartCodeID = _T("");
	m_ValidationID = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CPartCodes::GetDefaultDBName()
{
//	VHF TODO: For implementation change this to suit the 'real world' directory structure
	return _T("D:\\SOFT_ENG\\DEVELOPMENT\\Od3db.mdb");
}

CString CPartCodes::GetDefaultSQL()
{
	return _T("[SPC]");
}

void CPartCodes::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPartCodes)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Description]"), m_Description);
	DFX_Text(pFX, _T("[SPC_ID]"), m_PartCodeID);
	DFX_Long(pFX, _T("[Validation_ID]"), m_ValidationID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPartCodes diagnostics

#ifdef _DEBUG
void CPartCodes::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CPartCodes::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
