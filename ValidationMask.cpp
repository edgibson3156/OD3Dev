// ValidationMask.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "ValidationMask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValidationMask

IMPLEMENT_DYNAMIC(CValidationMask, CDaoRecordset)

CValidationMask::CValidationMask(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CValidationMask)
	m_Validation_ID = 0;
	m_Ohang1 = FALSE;
	m_Ohang2 = FALSE;
	m_Span1 = FALSE;
	m_Span2 = FALSE;
	m_Span3 = FALSE;
	m_AdjustmentDim = 0;
	m_SpanSummingMask = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_SPC_Ident = _T("");

}


CString CValidationMask::GetDefaultDBName()
{
	return _T("C:\\Virtual_Net\\Production\\Od3\\Od3db.mdb");
}

CString CValidationMask::GetDefaultSQL()
{
	return _T("[ValidationMaskbySPC]");
}

void CValidationMask::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CValidationMask)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[Validation_ID]"), m_Validation_ID);
	DFX_Bool(pFX, _T("[Ohang1]"), m_Ohang1);
	DFX_Bool(pFX, _T("[Ohang2]"), m_Ohang2);
	DFX_Bool(pFX, _T("[Span1]"), m_Span1);
	DFX_Bool(pFX, _T("[Span2]"), m_Span2);
	DFX_Bool(pFX, _T("[Span3]"), m_Span3);
	DFX_Long(pFX, _T("[AdjustmentDim]"), m_AdjustmentDim);
	DFX_Byte(pFX, _T("[SpanSummingMask]"), m_SpanSummingMask);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("SPC_Ident"), m_SPC_Ident);

}

/////////////////////////////////////////////////////////////////////////////
// CValidationMask diagnostics

#ifdef _DEBUG
void CValidationMask::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CValidationMask::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
