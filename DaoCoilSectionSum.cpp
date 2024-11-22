// DaoCoilSectionSum.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoCoilSectionSum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilSectionSum

IMPLEMENT_DYNAMIC(CDaoCoilSectionSum, CDaoRecordset)

CDaoCoilSectionSum::CDaoCoilSectionSum(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoCoilSectionSum)
	m_Section = _T("");
	m_SumOfMetres = 0.0;
	m_SumOfTonnage = 0.0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDaoCoilSectionSum::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\CoilPlanning.mdb");
}

CString CDaoCoilSectionSum::GetDefaultSQL()
{
	return _T("[QRY_WeightSumBySection]");
}

void CDaoCoilSectionSum::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoCoilSectionSum)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Section]"), m_Section);
	DFX_Double(pFX, _T("[SumOfMetres]"), m_SumOfMetres);
	DFX_Double(pFX, _T("[SumOfTonnage]"), m_SumOfTonnage);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilSectionSum diagnostics

#ifdef _DEBUG
void CDaoCoilSectionSum::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoCoilSectionSum::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
