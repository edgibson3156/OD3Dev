// DaoCoilLiveDuplicateSections.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoCoilLiveDuplicateSections.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilLiveDuplicateSections

IMPLEMENT_DYNAMIC(CDaoCoilLiveDuplicateSections, CDaoRecordset)

CDaoCoilLiveDuplicateSections::CDaoCoilLiveDuplicateSections(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoCoilLiveDuplicateSections)
	m_Section = _T("");
	m_Job_Number = _T("");
	m_Tonnage = 0.0;
	m_Metres = 0.0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDaoCoilLiveDuplicateSections::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\CoilPlanning.mdb");
}

CString CDaoCoilLiveDuplicateSections::GetDefaultSQL()
{
	return _T("[ORY_DuplicatedSectionEntries]");
}

void CDaoCoilLiveDuplicateSections::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoCoilLiveDuplicateSections)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Section]"), m_Section);
	DFX_Text(pFX, _T("[Job_Number]"), m_Job_Number);
	DFX_Double(pFX, _T("[Tonnage]"), m_Tonnage);
	DFX_Double(pFX, _T("[Metres]"), m_Metres);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilLiveDuplicateSections diagnostics

#ifdef _DEBUG
void CDaoCoilLiveDuplicateSections::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoCoilLiveDuplicateSections::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
