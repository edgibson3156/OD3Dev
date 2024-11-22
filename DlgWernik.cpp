// DlgWernik.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DlgWernik.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWernik dialog


CDlgWernik::CDlgWernik(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWernik::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWernik)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgWernik::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWernik)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWernik, CDialog)
	//{{AFX_MSG_MAP(CDlgWernik)
	ON_BN_CLICKED(IDC_ISWERNIK, OnIswernik)
	ON_BN_CLICKED(IDC_NOTWERNIK, OnNotwernik)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWernik message handlers

BOOL CDlgWernik::OnInitDialog() 
{
	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWernik::OnIswernik() 
{
	EndDialog(IDYES);	
}

void CDlgWernik::OnNotwernik() 
{	
	EndDialog(IDNO);	
}
