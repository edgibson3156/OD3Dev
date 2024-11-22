// DaoCoilGetByOrder.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoCoilGetByOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilGetByOrder

IMPLEMENT_DYNAMIC(CDaoCoilGetByOrder, CDaoRecordset)

CDaoCoilGetByOrder::CDaoCoilGetByOrder(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoCoilGetByOrder)
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
	m_nParams = 1;
	m_SearchOrder = _T("");

}


CString CDaoCoilGetByOrder::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\CoilPlanning.mdb");
}

CString CDaoCoilGetByOrder::GetDefaultSQL()
{
	return _T("[QRY_GetByOrderNum]");
}

void CDaoCoilGetByOrder::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoCoilGetByOrder)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[ID]"), m_ID);
	DFX_Text(pFX, _T("[Job_Number]"), m_Job_Number);
	DFX_Text(pFX, _T("[Section]"), m_Section);
	DFX_Double(pFX, _T("[Metres]"), m_Metres);
	DFX_Double(pFX, _T("[Tonnage]"), m_Tonnage);
	DFX_Text(pFX, _T("[Coil_Code]"), m_Coil_Code);
	DFX_Bool(pFX, _T("[Complete]"), m_Complete);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("SearchOrder"), m_SearchOrder);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilGetByOrder diagnostics

#ifdef _DEBUG
void CDaoCoilGetByOrder::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoCoilGetByOrder::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
