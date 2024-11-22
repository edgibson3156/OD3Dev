// DaoCoilJob.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoCoilJob.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilJob

IMPLEMENT_DYNAMIC(CDaoCoilJob, CDaoRecordset)

CDaoCoilJob::CDaoCoilJob(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoCoilJob)
	m_Job_Number = _T("");
	m_Customer_name = _T("");
	m_Due_date = (DATE)0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDaoCoilJob::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\CoilPlanning.mdb");
}

CString CDaoCoilJob::GetDefaultSQL()
{
	return _T("[TBL_Job]");
}

void CDaoCoilJob::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoCoilJob)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Job_Number]"), m_Job_Number);
	DFX_Text(pFX, _T("[Customer_name]"), m_Customer_name);
	DFX_DateTime(pFX, _T("[Due_date]"), m_Due_date);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilJob diagnostics

#ifdef _DEBUG
void CDaoCoilJob::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoCoilJob::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
