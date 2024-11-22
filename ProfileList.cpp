// ProfileList.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "ProfileList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileList

IMPLEMENT_DYNAMIC(CProfileList, CDaoRecordset)

CProfileList::CProfileList(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CProfileList)
	m_ProductName = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_nParams = 1;
	m_Customer_Filter = _T("");

}


CString CProfileList::GetDefaultDBName()
{
	return _T("C:\\OD3Demo\\OD3DB_vhf.MDB");
}

CString CProfileList::GetDefaultSQL()
{
	return _T("[Type1Products]");
}

void CProfileList::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CProfileList)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	//}}AFX_FIELD_MAP
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("Customer_Filter"), m_Customer_Filter);

}

/////////////////////////////////////////////////////////////////////////////
// CProfileList diagnostics

#ifdef _DEBUG
void CProfileList::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CProfileList::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
