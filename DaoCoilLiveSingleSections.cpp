// DaoCoilLiveSingleSections.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoCoilLiveSingleSections.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilLiveSingleSections

IMPLEMENT_DYNAMIC(CDaoCoilLiveSingleSections, CDaoRecordset)

CDaoCoilLiveSingleSections::CDaoCoilLiveSingleSections(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoCoilLiveSingleSections)
	m_Section = _T("");
	m_Job_Number = _T("");
	m_Tonnage = 0.0;
	m_Metres = 0.0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDaoCoilLiveSingleSections::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\CoilPlanning.mdb");
}

CString CDaoCoilLiveSingleSections::GetDefaultSQL()
{
	return _T("[QRY_SingleSectionEntries]");
}

void CDaoCoilLiveSingleSections::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoCoilLiveSingleSections)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Section]"), m_Section);
	DFX_Text(pFX, _T("[Job_Number]"), m_Job_Number);
	DFX_Double(pFX, _T("[Tonnage]"), m_Tonnage);
	DFX_Double(pFX, _T("[Metres]"), m_Metres);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilLiveSingleSections diagnostics

#ifdef _DEBUG
void CDaoCoilLiveSingleSections::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoCoilLiveSingleSections::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
