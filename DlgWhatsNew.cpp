// DlgWhatsNew.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DlgWhatsNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWhatsNew dialog


CDlgWhatsNew::CDlgWhatsNew(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWhatsNew::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWhatsNew)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgWhatsNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWhatsNew)
	DDX_Control(pDX, IDC_DISPLAYTEXT, m_display);
	DDX_Control(pDX, IDC_DONTSHOW, m_dontShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWhatsNew, CDialog)
	//{{AFX_MSG_MAP(CDlgWhatsNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWhatsNew message handlers

BOOL CDlgWhatsNew::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString filePath, sLine, sWhatsNew;
	
	filePath = getenv(_T("OD3_HOME"));
	filePath+=_T("whatsNew.txt");

	m_display.FmtLines(true);

	try
	{
		CStdioFile file(filePath, CFile::modeRead);

		// Read the file contents
		while(file.ReadString(sLine))
			sWhatsNew += sLine + _T("\r\n");
		
		// Set contents to the edit box
		m_display.SetWindowText(sWhatsNew);

		// Release file
		file.Close();
	}
	catch(CFileException *e)
	{
		// Delete exception
		e->Delete();
		// Close dialog
		EndDialog(-2);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWhatsNew::OnOK() 
{
	if(m_dontShow.GetCheck())
	{
		// Change registry value
		AfxGetApp()->WriteProfileInt("Settings", "whatsNew", 1);
	}

	CDialog::OnOK();
}
