// DlgListAcc.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DlgListAcc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDlgListAcc dialog


CDlgListAcc::CDlgListAcc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListAcc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgListAcc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgListAcc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgListAcc)
	DDX_Control(pDX, IDC_ACC_LIST, m_accList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgListAcc, CDialog)
	//{{AFX_MSG_MAP(CDlgListAcc)
	ON_NOTIFY(NM_CLICK, IDC_ACC_LIST, OnClickAccList)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ACC_LIST, OnKillfocusAccList)
	ON_BN_CLICKED(IDC_PRINT_ACC, OnPrintAcc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgListAcc message handlers

void CDlgListAcc::OnClickAccList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint	point;

	// Get the cursor pos
	GetCursorPos(&point);

	// Convert to object coordinates
	m_accList.ScreenToClient(&point);
	// Perform hit test
	m_index = m_accList.HitTest(point, NULL);

	// No item found
	if(m_index==-1)
	{
		// Set cursor pos to emulate psuedo double click on item
		point.x = 2;
		m_index = m_accList.HitTest(point, NULL);
	}

	if(m_index>-1)
		m_accList.SetItemState(m_index,LVIS_SELECTED, LVSIL_STATE);
	
	*pResult = 0;
}

void CDlgListAcc::OnKillfocusAccList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(m_index>-1)
		m_accList.SetItemState(m_index,~LVIS_SELECTED, LVSIL_STATE);
	
	*pResult = 0;
}

LRESULT CDlgListAcc::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
		case WM_ACTIVATE:
			m_accList.SetFocus();
			break;
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgListAcc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect	rect;


	m_index=-1;
	m_printed = false;

	// Get  the size of the list control
	m_accList.GetClientRect(rect);

	// Add headers to list control
	m_accList.InsertColumn(1, "Product Name", LVCFMT_LEFT, rect.Width()/2,-1);
	m_accList.InsertColumn(2, "Quantity", LVCFMT_LEFT,rect.Width()/2,-1);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgListAcc::OnPrintAcc() 
{
	// TODO: Add your control notification handler code here
	CPrintDialog	print(false);
	DOCINFO			docInfo;
	TEXTMETRIC		tMetric;
	int				i, count=m_accList.GetItemCount();
	char			sName[150], sQuantity[10];
	int				height,width, yPos=0, xPos=0, lineY;
	CDC				dcMem, printerDC;
	CBitmap			logo, *pOldBitmap=NULL;
	BITMAP			pBmapInfo;
	CPoint			size;
	CPoint			org(0, 0);
	

	if(count)
	{
		// Open common print dialog
		if(print.DoModal()==IDOK)
		{
			// Get the printer device
			HDC dc = print.GetPrinterDC();

			// Get device area
			height = GetDeviceCaps(dc, VERTRES);
			width = GetDeviceCaps(dc, HORZRES);
			
			GetTextMetrics(dc, &tMetric);

			xPos = width/4;

			// Clean struct
			ZeroMemory(&docInfo, sizeof(DOCINFO));

			// Set up printing structure
			docInfo.cbSize=sizeof(DOCINFO);
			docInfo.lpszDocName = "Accessory Print";
			docInfo.lpszOutput = NULL;
			docInfo.fwType = NULL;

			// Start the document
			StartDoc(dc, &docInfo);
			// Start the page
			StartPage(dc);

			// Attach printer DC to CDC object
			printerDC.Attach(dc);

			// Load printer compatible bitmap		
			VERIFY(logo.Attach (::LoadImage (::AfxFindResourceHandle(
						 MAKEINTRESOURCE (IDB_LOGO), RT_BITMAP),
						 MAKEINTRESOURCE (IDB_LOGO), IMAGE_BITMAP, 0, 0,
						 (LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

	
			// Get the information about the image
			logo.GetBitmap(&pBmapInfo);

			// Set the size values
			size.x = pBmapInfo.bmWidth;
			size.y = pBmapInfo.bmHeight;

			// Convert coordinate values
			printerDC.DPtoLP (&size);
			printerDC.DPtoLP (&org);

			// Set up memory DC for image printing
			dcMem.CreateCompatibleDC(&printerDC);
			// Set image to the object
			pOldBitmap = dcMem.SelectObject(&logo);
			// Set mapping mode
			dcMem.SetMapMode(printerDC.GetMapMode());

			// Draw logo on to paper
			printerDC.BitBlt (0, 0, size.x, size.y, &dcMem, org.x, org.y, SRCCOPY);

			// Select old object
			dcMem.SelectObject (pOldBitmap);

			// Release printer DC
			printerDC.Detach();


			yPos += size.y/2;
			// Print job details
			TextOut(dc, size.x+10, yPos, m_sJobDetails.GetBuffer(m_sJobDetails.GetLength()), m_sJobDetails.GetLength());
			lineY=yPos += tMetric.tmHeight*3;

			// Print table headers
			TextOut(dc, 0, yPos, "Product Code", 12);
			TextOut(dc, xPos, yPos, "Quantity", 8);

			MoveToEx(dc, 0, yPos+tMetric.tmHeight+5 , NULL);
			LineTo(dc, width/2, yPos+tMetric.tmHeight+5);

			yPos += tMetric.tmHeight*2;

			// Loop through data
			for(i=0; i<count; i++)
			{
				m_accList.GetItemText(i, 0, sName, sizeof(sName));
				m_accList.GetItemText(i, 1, sQuantity, sizeof(sQuantity));

				TextOut(dc, 0, yPos, sName, strlen(sName));
				TextOut(dc, xPos, yPos, sQuantity, strlen(sQuantity));

				yPos+=tMetric.tmHeight;
			}

			MoveToEx(dc,xPos-15,lineY, NULL);
			LineTo(dc, xPos-15, yPos);

			// Page complete
			EndPage(dc);
			// End print job
			EndDoc(dc);

			// Set print flag
			m_printed = true;
		}
	}
	
	return;
}

void CDlgListAcc::OnOK() 
{
	// TODO: Add extra validation here

	if(!m_printed)
	{
		// Ask user to print
		if(AfxMessageBox(IDS_SD_PRINTWARN, MB_ICONQUESTION|MB_YESNO)==IDYES)
			OnPrintAcc();
			
	}
	// Clear the list
	m_accList.DeleteAllItems();

	// Clear the print flag
	m_printed = false;
	
	CDialog::OnOK();
}
