// ManualInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "ManualInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManualInputPage property page

IMPLEMENT_DYNCREATE(CManualInputPage, CPropertyPage)

CManualInputPage::CManualInputPage() : CPropertyPage(CManualInputPage::IDD)
{
	//{{AFX_DATA_INIT(CManualInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CManualInputPage::~CManualInputPage()
{
}

void CManualInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManualInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManualInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CManualInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualInputPage message handlers
