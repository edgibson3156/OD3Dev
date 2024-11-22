// ProductionLine.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "ProductionLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProductionLine

IMPLEMENT_DYNAMIC(CProductionLine, CDaoRecordset)

CProductionLine::CProductionLine(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CProductionLine)
	m_Line_ID = _T("");
	m_Line_Type = 0;
	m_Auto = 0;
	m_Description = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CProductionLine::GetDefaultDBName()
{
	return _T("D:\\Soft_Eng\\Development\\Od3db.mdb");
}

CString CProductionLine::GetDefaultSQL()
{
	return _T("[PRODUCTION_LINES]");
}

void CProductionLine::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CProductionLine)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Line_ID]"), m_Line_ID);
	DFX_Byte(pFX, _T("[Line_Type]"), m_Line_Type);
	DFX_Byte(pFX, _T("[Auto]"), m_Auto);
	DFX_Text(pFX, _T("[Description]"), m_Description);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CProductionLine diagnostics

#ifdef _DEBUG
void CProductionLine::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CProductionLine::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
