// DaoCoilJobDetails.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoCoilJobDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilJobDetails

IMPLEMENT_DYNAMIC(CDaoCoilJobDetails, CDaoRecordset)

CDaoCoilJobDetails::CDaoCoilJobDetails(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoCoilJobDetails)
	m_ID = _T("");
	m_Job_Number = _T("");
	m_Section = _T("");
	m_Metres = 0.0;
	m_Tonnage = 0.0;
	m_Coil_Code = _T("");
	m_Complete = FALSE;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDaoCoilJobDetails::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\CoilPlanning.mdb");
}

CString CDaoCoilJobDetails::GetDefaultSQL()
{
	return _T("[TBL_Job_Details]");
}

void CDaoCoilJobDetails::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoCoilJobDetails)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[ID]"), m_ID);
	DFX_Text(pFX, _T("[Job_Number]"), m_Job_Number);
	DFX_Text(pFX, _T("[Section]"), m_Section);
	DFX_Double(pFX, _T("[Metres]"), m_Metres);
	DFX_Double(pFX, _T("[Tonnage]"), m_Tonnage);
	DFX_Text(pFX, _T("[Coil_Code]"), m_Coil_Code);
	DFX_Bool(pFX, _T("[Complete]"), m_Complete);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilJobDetails diagnostics

#ifdef _DEBUG
void CDaoCoilJobDetails::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoCoilJobDetails::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
