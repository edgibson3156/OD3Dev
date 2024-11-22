// SelectBySection.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "SelectBySection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectBySection

IMPLEMENT_DYNAMIC(CSelectBySection, CDaoRecordset)

CSelectBySection::CSelectBySection(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSelectBySection)
	m_RollSet_ID = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_Section_Ident = _T("");

}


CString CSelectBySection::GetDefaultDBName()
{
	return _T("C:\\OD3Demo\\OD3DB_vhf.MDB");
}

CString CSelectBySection::GetDefaultSQL()
{
	return _T("[SelectRollSetBySection]");
}

void CSelectBySection::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSelectBySection)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[RollSet_ID]"), m_RollSet_ID);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("Section_Ident"), m_Section_Ident);

}

/////////////////////////////////////////////////////////////////////////////
// CSelectBySection diagnostics

#ifdef _DEBUG
void CSelectBySection::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSelectBySection::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
