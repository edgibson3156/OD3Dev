// DaoAccOffset.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DaoAccOffset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoAccOffset

IMPLEMENT_DYNAMIC(CDaoAccOffset, CDaoRecordset)

CDaoAccOffset::CDaoAccOffset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoAccOffset)
	m_product_code = _T("");
	m_aviion = _T("");
	m_description = _T("");
	m_section_id = _T("");
	m_weight = 0.0;
	m_offset = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_prod_code = _T("");

}


CString CDaoAccOffset::GetDefaultDBName()
{
	return _T("C:\\ControledSource\\OD3_Development\\Od3_2_5_12.mdb");
}

CString CDaoAccOffset::GetDefaultSQL()
{
	return _T("[GetAccessoryOffset]");
}

void CDaoAccOffset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoAccOffset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[product_code]"), m_product_code);
	DFX_Text(pFX, _T("[aviion]"), m_aviion);
	DFX_Text(pFX, _T("[description]"), m_description);
	DFX_Text(pFX, _T("[section_id]"), m_section_id);
	DFX_Double(pFX, _T("[weight]"), m_weight);
	DFX_Double(pFX, _T("[offset]"), m_offset);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("prod_code"), m_prod_code);

}

/////////////////////////////////////////////////////////////////////////////
// CDaoAccOffset diagnostics

#ifdef _DEBUG
void CDaoAccOffset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoAccOffset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
