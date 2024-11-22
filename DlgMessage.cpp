// DlgMessage.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DlgMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EXITDLG 101
/////////////////////////////////////////////////////////////////////////////
// CDlgMessage dialog


CDlgMessage::CDlgMessage(CWnd* pParent /*=NULL*/, CString sMessage)
	: CDialog(CDlgMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMessage)
	//}}AFX_DATA_INIT

	m_sMessage = sMessage;
}


void CDlgMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMessage)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMessage, CDialog)
	//{{AFX_MSG_MAP(CDlgMessage)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMessage message handlers

BOOL CDlgMessage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// Start close timer
	SetTimer(EXITDLG, 750, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMessage::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==EXITDLG)
	{
		// Stop timer
		KillTimer(EXITDLG);
		// Exit dialog
		EndDialog(1);
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgMessage::OnPaint() 
{
	CPaintDC	dc(this);
	CRect		rect;
	CBrush		bru, *old;
	int			oldMode;
	CSize		txSize;
	CFont		font, *oldF;
	COLORREF	oldCol;
	

	oldCol = dc.SetTextColor(RGB(0,0,255));
	// Create the brush
	bru.CreateSolidBrush(RGB(210,210,240));
	old = dc.SelectObject(&bru);

	// Create the font
	font.CreatePointFont(130, "Ariel", &dc);
	oldF = dc.SelectObject(&font);

	// Get text size
	txSize = dc.GetTextExtent(m_sMessage);

	// Get the dialog size
	GetClientRect(&rect);
	// Draw bk colour
	dc.Rectangle(&rect);

	oldMode = dc.SetBkMode(TRANSPARENT);
	dc.TextOut((rect.Width()/2)-(txSize.cx/2), (rect.Height()/2)-txSize.cy, m_sMessage);
	dc.SetBkMode(oldMode);

	dc.SelectObject(old);
	dc.SelectObject(oldF);
	dc.SetTextColor(oldCol);
	
	// Do not call CDialog::OnPaint() for painting messages
}
