// DlgSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DlgSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitter dialog


CDlgSplitter::CDlgSplitter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSplitter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSplitter)
	//}}AFX_DATA_INIT
}


void CDlgSplitter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSplitter)
	DDX_Control(pDX, IDC_EXPORTPRODUCTS_TREE, m_tree);
	DDX_Control(pDX, IDC_EXPORTWARLEY, m_exportWarley);
	DDX_Control(pDX, IDC_EXPORTIRVINE, m_exportIrvine);
	DDX_Control(pDX, IDC_WARLEY_RAD, m_warleyRad);
	DDX_Control(pDX, IDC_IRVINE_RAD, m_irvineRad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSplitter, CDialog)
	//{{AFX_MSG_MAP(CDlgSplitter)
	ON_BN_CLICKED(IDC_WARLEY_RAD, OnWarleyRad)
	ON_BN_CLICKED(IDC_IRVINE_RAD, OnIrvineRad)
	ON_BN_CLICKED(IDC_EXPORTWARLEY, OnExportwarley)
	ON_BN_CLICKED(IDC_EXPORTIRVINE, OnExportirvine)
	ON_BN_CLICKED(IDC_PRINTEXPORTS, OnPrintexports)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitter message handlers

BOOL CDlgSplitter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	bool			found=false;
	CImportD3Acc	*pAcc=NULL;
	POSITION		pos;
	CString			title;

	m_printed=m_exportedWarley=m_exportedIrvine = false;
	m_pageNum = 1;


	if(m_splitClass->m_tplIrvineAcc.GetCount() ||
		m_splitClass->m_tplIrvineBeam.GetCount())
	{
		// Irvine products found
		m_irvineRad.EnableWindow(true);
		m_exportIrvine.EnableWindow(true);
		found = true;
	}

	if(m_splitClass->m_tplWarleyAcc.GetCount() ||
		m_splitClass->m_tplWarleyBeam.GetCount())
	{
		// Warley products found
		m_warleyRad.EnableWindow(true);
		m_exportWarley.EnableWindow(true);
		found = true;
	}

	// Special case, no beams only accessories
	if(!found && m_splitClass->m_tplOtherAcc.GetCount())
	{
		// Load and change title
		title.LoadString(IDS_DAVACCESSORIES);
		SetWindowText(title);
		
		// Get head position of accessories
		pos = m_splitClass->m_tplOtherAcc.GetHeadPosition();

		while(pos)
		{
			// Get data pointer
			pAcc = m_splitClass->m_tplOtherAcc.GetNext(pos);
			// Add other (Daventry) accessories to the tree object
			addAccToTree(pAcc);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSplitter::OnOK() 
{
	// TODO: Add extra validation here

	if((m_splitClass->m_tplWarleyAcc.GetCount() || m_splitClass->m_tplWarleyBeam.GetCount())
		&& !m_exportedWarley)
	{
		// Have not exported Warley items
		AfxMessageBox(IDS_NOT_EXPORTED_WARLEY, MB_ICONINFORMATION);
		return;
	}

	if((m_splitClass->m_tplIrvineAcc.GetCount() || m_splitClass->m_tplIrvineBeam.GetCount())
		&& !m_exportedIrvine)
	{
		// Have not exported Irvine items
		AfxMessageBox(IDS_NOT_EXPORTED_IRVINE, MB_ICONINFORMATION);
		return;
	}

	if(!m_printed)
	{
		// Not printed out items
		AfxMessageBox(IDS_NOT_PRINTED, MB_ICONINFORMATION);
		return;
	}

	// Continue and close dialog
	CDialog::OnOK();
}

void CDlgSplitter::OnWarleyRad() 
{
	// TODO: Add your control notification handler code here
	POSITION		pos;
	CImportD3Beam	*pBeam=NULL;
	CImportD3Acc	*pAcc=NULL;


	// Clear any tree entries
	m_tree.DeleteAllItems();

	// Get head position for imported beams
	pos = m_splitClass->m_tplWarleyBeam.GetHeadPosition();

	while(pos)
	{
		pBeam = m_splitClass->m_tplWarleyBeam.GetNext(pos);
		addBeamToTree(pBeam);
	}

	// Get head position for imported accessories
	pos = m_splitClass->m_tplWarleyAcc.GetHeadPosition();

	while(pos)
	{
		pAcc = m_splitClass->m_tplWarleyAcc.GetNext(pos);
		addAccToTree(pAcc);
	}
}

void CDlgSplitter::OnExportwarley() 
{
	// TODO: Add your control notification handler code here
	CString	fileName;

	// Get the file name
	fileName = openCommonDlg(2);

	if(fileName.GetLength())
	{
		// Export the Warley d3 file
		if(exportFile(fileName, 2))
			m_exportedWarley=true;	
	}
}

void CDlgSplitter::OnIrvineRad() 
{
	// TODO: Add your control notification handler code here
	POSITION		pos;
	CImportD3Beam	*pBeam=NULL;
	CImportD3Acc	*pAcc=NULL;


	// Clear any tree entries
	m_tree.DeleteAllItems();

	// Clear any tree entries
	m_tree.DeleteAllItems();

	pos = m_splitClass->m_tplIrvineBeam.GetHeadPosition();

	while(pos)
	{
		pBeam = m_splitClass->m_tplIrvineBeam.GetNext(pos);
		addBeamToTree(pBeam);
	}
	
	// Get head position for imported accessories
	pos = m_splitClass->m_tplIrvineAcc.GetHeadPosition();

	while(pos)
	{
		pAcc = m_splitClass->m_tplIrvineAcc.GetNext(pos);
		addAccToTree(pAcc);
	}
}

void CDlgSplitter::OnExportirvine() 
{
	// TODO: Add your control notification handler code here
	CString	fileName;

	// Get the file name
	fileName = openCommonDlg(1);

	if(fileName.GetLength())
	{
		// Export the Irvine d3 file
		if(exportFile(fileName, 1))
			m_exportedIrvine=true;	
	}
	
}

// Print Warley and Irvine imported data
void CDlgSplitter::OnPrintexports() 
{
	// TODO: Add your control notification handler code here
	CPrintDialog	print(false);
	DOCINFO			docInfo;
	TEXTMETRIC		tMetric;
	int				height,width, yPos=0;
	int				xPosTitle = 50, xPosContents = 0;
	int				site;
	CDC				printerDC;
	HDC				dc;
	CFont			*oldFont, printFont;
	POSITION		pos;
	CImportD3Beam	*pBeam=NULL;
	CImportD3Acc	*pAcc=NULL;
	CString			szText, szHeader;
	

	// Open common print dialog
	if(print.DoModal()==IDOK)
	{
		// Reset the page number
		m_pageNum = 1;
		// Create the page header text
		szHeader = _T("Job Number: ") + m_pImport->GetJobNO() + " " + "Project: " + m_pImport->GetProject() +
			" " + "File name: " + m_pImport->GetFile();
		// Get the printer device
		dc = print.GetPrinterDC();
		
		// Attach printer DC to CDC object
		printerDC.Attach(dc);

		// Get device area
		height = printerDC.GetDeviceCaps(VERTRES);
		width = printerDC.GetDeviceCaps(HORZRES);

		// Set position
		xPosContents = width / 3;

		// Clean struct
		ZeroMemory(&docInfo, sizeof(DOCINFO));

		// Set up printing structure
		docInfo.cbSize=sizeof(DOCINFO);
		docInfo.lpszDocName = "Print D3 Details";
		docInfo.lpszOutput = NULL;
		docInfo.fwType = NULL;

		// Create the printing font
		printFont.CreatePointFont(800, _T("Times new roman"), NULL);

		// Set font to DC
		oldFont = printerDC.SelectObject(&printFont);

		// Get the size of the font
		printerDC.GetTextMetrics(&tMetric);

		// Start the print job
		printerDC.StartDoc(&docInfo);
		// Start the first page
		printerDC.StartPage();

		// Loop Warley then Irvine import beams
		for(site=0; site<2; site++)
		{
			if(site==0)
				// Get the head posistion of the selected site
				pos = m_splitClass->m_tplWarleyBeam.GetHeadPosition();
			else
				// Get the head posistion of the selected site
				pos = m_splitClass->m_tplIrvineBeam.GetHeadPosition();

			while(pos)
			{
				// Dont print off the bottom of the page
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				
				if(site==0)
					// Get the imported beam data
					pBeam = m_splitClass->m_tplWarleyBeam.GetNext(pos);
				else
					// Get the imported beam data
					pBeam = m_splitClass->m_tplIrvineBeam.GetNext(pos);

				// Print title
				printerDC.TextOut(0, yPos, _T("Beam"));
				// Move the y position
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				// Draw line
				printerDC.MoveTo(0, yPos);
				printerDC.LineTo(width-100, yPos);
				
				// Name of beam
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Name:"));
				printerDC.TextOut(xPosContents, yPos, pBeam->GetProductName());

				// Type of beam
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Type:"));
				printerDC.TextOut(xPosContents, yPos, pBeam->GetProductType());

				// Beam group
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Group:"));
				printerDC.TextOut(xPosContents, yPos, pBeam->GetProductGroup());

				// Beam mark
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Mark:"));
				printerDC.TextOut(xPosContents, yPos, pBeam->GetMark());

				// Length of beam
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Length:"));
				szText.Format("%i", pBeam->GetLength());
				printerDC.TextOut(xPosContents, yPos, szText);

				// Beam quantity
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Quantity:"));
				szText.Format("%i", pBeam->GetQty());
				printerDC.TextOut(xPosContents, yPos, szText);

				// How many extra holes
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Extra holes:"));
				szText.Format("%i", pBeam->m_tplHoleList.GetCount());
				printerDC.TextOut(xPosContents, yPos, szText);

				// Which production site
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Manufacturing site:"));

				if(site==0)
					szText = _T("Warley");
				else
					szText = _T("Irvine");

				printerDC.TextOut(xPosContents, yPos, szText);

				// Move the y position
				yPos += tMetric.tmHeight*2;
			}
		}

		// Print accessories here //
		// Loop Others, Warley and Irvine import accessories
		for(site=0; site<3; site++)
		{
			switch(site)
			{
			case 1:
				// Get the head posistion of the selected site
				pos = m_splitClass->m_tplWarleyAcc.GetHeadPosition();
				break;

			case 2:
				// Get the head posistion of the selected site
				pos = m_splitClass->m_tplIrvineAcc.GetHeadPosition();
				break;

			default:
				// Get the head posistion of the selected site
				pos = m_splitClass->m_tplOtherAcc.GetHeadPosition();
				break;
			}

			while(pos)
			{
				// Dont print off the bottom of the page
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				
				switch(site)
				{
				case 1:
					// Get the imported beam data
					pAcc = m_splitClass->m_tplWarleyAcc.GetNext(pos);
					break;
				case 2:
					// Get the imported beam data
					pAcc = m_splitClass->m_tplIrvineAcc.GetNext(pos);
					break;

				default:
					// Get the imported beam data
					pAcc = m_splitClass->m_tplOtherAcc.GetNext(pos);
					break;
				}

				// Print title
				printerDC.TextOut(0, yPos, _T("Accessory"));
				// Move the y position
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				// Draw line
				printerDC.MoveTo(0, yPos);
				printerDC.LineTo(width-100, yPos);

				// Name of accessory
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Name:"));
				printerDC.TextOut(xPosContents, yPos, pAcc->GetProductName());

				// Type of accessory
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Type:"));
				if(strlen(pAcc->GetProductType()))
					szText = pAcc->GetProductType();
				else
					szText = pAcc->GetType();

				printerDC.TextOut(xPosContents, yPos, szText);

				// Size of accessory
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Size:"));
				printerDC.TextOut(xPosContents, yPos, pAcc->GetSectionSize());

				// Accessory mark
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Mark:"));
				printerDC.TextOut(xPosContents, yPos, pAcc->GetMark());

				// Accessory quantity
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Quantity:"));
				szText.Format("%i", pAcc->GetQty());
				printerDC.TextOut(xPosContents, yPos, szText);

				// Which production site
				yPos += tMetric.tmHeight;
				testPageLimits(height, &yPos, &printerDC, tMetric.tmHeight, szHeader.GetBuffer(szHeader.GetLength()));
				printerDC.TextOut(xPosTitle, yPos, _T("Manufacturing site:"));

				switch(site)
				{
				case 1:
					szText = _T("Warley");
					break;

				case 2:
					szText = _T("Irvine");
					break;

				default:
					szText = _T("Daventry");
					break;
				}

				printerDC.TextOut(xPosContents, yPos, szText);

				// Move the y position
				yPos += tMetric.tmHeight*2;
			}
		}

		// End page
		printerDC.EndPage();
		// End the print job
		printerDC.EndDoc();

		// Release font object
		printerDC.SelectObject(oldFont);

	}

	// Set flag
	m_printed=true;
}

void CDlgSplitter::addBeamToTree(CImportD3Beam *beam)
{
	HTREEITEM		rootBeam, rootExtraHoles, rootHoles;
	CString			szText;
	POSITION		pos;
	CDet3BeamHole	*pHole=NULL;

	// Add a beam item to the tree
	rootBeam = m_tree.InsertItem("Beam", TVI_ROOT, TVI_LAST);
	// Set beam item data
	m_tree.InsertItem(_T("Product name: ") + (CString)beam->GetProductName(), rootBeam, TVI_LAST);
	m_tree.InsertItem(_T("Product type: ") + (CString)beam->GetProductType(), rootBeam, TVI_LAST);
	m_tree.InsertItem(_T("Product group: ") + (CString)beam->GetProductGroup(), rootBeam, TVI_LAST);
	m_tree.InsertItem(_T("Mark: ") + (CString)beam->GetMark(), rootBeam, TVI_LAST);
	
	// Add extra hole item into beam
	rootExtraHoles = m_tree.InsertItem(_T("Extra Holes"), rootBeam, TVI_LAST);

	// Get the head position
	pos = beam->m_tplHoleList.GetHeadPosition();

	while(pos)
	{
		// Get the hole pointer
		pHole = beam->m_tplHoleList.GetNext(pos);

		// Add extra hole root item
		rootHoles = m_tree.InsertItem(_T("Holes"), rootExtraHoles, TVI_LAST);
		// Set hole data
		m_tree.InsertItem(_T("Type: ") + (CString)pHole->GetHoleSetType(), rootHoles, TVI_LAST);
		szText.Format("%i", pHole->GetPosition());
		m_tree.InsertItem(_T("Pos: ") + szText, rootHoles, TVI_LAST);
		m_tree.InsertItem(_T("Comment: ") + (CString)pHole->GetComment(), rootHoles, TVI_LAST);
	}

	return;
}

void CDlgSplitter::addAccToTree(CImportD3Acc *acc)
{
	// Add accessories to the tree control
	HTREEITEM	rootAcc;
	CString		szText;

	// Add a beam item to the tree
	rootAcc = m_tree.InsertItem("Accessory", TVI_ROOT, TVI_LAST);
	// Set beam item data
	m_tree.InsertItem(_T("Product name: ") + (CString)acc->GetProductName(), rootAcc, TVI_LAST);

	if(strlen(acc->GetProductType()))
		szText = acc->GetProductType();
	else
		szText = acc->GetType();
	m_tree.InsertItem(_T("Product type: ") + szText, rootAcc, TVI_LAST);
	m_tree.InsertItem(_T("Section type: ") + (CString)acc->GetSectionType(), rootAcc, TVI_LAST);
	m_tree.InsertItem(_T("Section size: ") + (CString)acc->GetSectionSize(), rootAcc, TVI_LAST);
	m_tree.InsertItem(_T("Mark: ") + (CString)acc->GetMark(), rootAcc, TVI_LAST);
	

	return;
}

CString CDlgSplitter::openCommonDlg(int site)
{
	CString	path, fileEx, fileDes;
	DWORD	flags = OFN_FILEMUSTEXIST|
					OFN_HIDEREADONLY|
     				OFN_PATHMUSTEXIST|
					OFN_SHAREWARN|
					OFN_OVERWRITEPROMPT;

	// Set the export file details
	switch(site)
	{
	case 1:
		// Irvine
		fileEx = _T(".id3");
		fileDes = _T("Irvine d3 file (*.id3)|*.id3||");
		break;

	case 2:
		// Warley
		fileEx = _T(".wd3");
		fileDes = _T("Warley d3 file (*.wd3)|*.wd3||");
		break;
	}

	// Create common save file dialog
	CFileDialog dlgSave(false, fileEx, NULL, flags, fileDes,
							AfxGetApp()->m_pMainWnd);

	// Open the dialog
	if(dlgSave.DoModal()==IDOK)
		path = dlgSave.GetPathName();


	return(path);
}

bool CDlgSplitter::exportFile(CString fName, int site)
{
	POSITION		pos;
	CImportD3Beam	*pBeam=NULL;
	CImportD3Acc	*pAcc=NULL;
	int				index=0;
	CBigIni			ini(fName, 1); // Set to write and create mode

	// Write the d3 header
	if(m_pImport)
		m_pImport->WriteD3Header(ini);

	switch(site)
	{
	case 1:
		// Irvine

		// Get the head position for the Irvine beams
		pos = m_splitClass->m_tplIrvineBeam.GetHeadPosition();

		while(pos)
		{
			// Get the imported beam data
			pBeam = m_splitClass->m_tplIrvineBeam.GetNext(pos);
			// Write the beam to the d3 file
			pBeam->Write(ini, index++);
		}

		// Get the head position for the Irvine accessories
		pos = m_splitClass->m_tplIrvineAcc.GetHeadPosition();

		while(pos)
		{
			// Get the imported beam data
			pAcc = m_splitClass->m_tplIrvineAcc.GetNext(pos);
			// Write the accessory to the d3 file
			pAcc->Write(ini, index++);
		}
		break;

	case 2:
		// Warley

		// Get the head position for the Warley beams
		pos = m_splitClass->m_tplWarleyBeam.GetHeadPosition();

		while(pos)
		{
			// Get the imported beam data
			pBeam = m_splitClass->m_tplWarleyBeam.GetNext(pos);
			// Write the beam to the d3 file
			pBeam->Write(ini, index++);
		}

		// Get the head position for the Warley accessories
		pos = m_splitClass->m_tplWarleyAcc.GetHeadPosition();

		while(pos)
		{
			// Get the imported beam data
			pAcc = m_splitClass->m_tplWarleyAcc.GetNext(pos);
			// Write the accessory to the d3 file
			pAcc->Write(ini, index++);
		}
		break;
	}
	

	return(true);
}

void CDlgSplitter::testPageLimits(int height, int *yPos, CDC *dc, int textHeight, char *header)
{
	CString	szText;

	// Test current y co-ordinate
	if(*yPos==0)
	{
		dc->TextOut(0, *yPos, header);
		*yPos+=textHeight;
		// Format the page number
		szText.Format(_T("Page %i"), m_pageNum++);
		// Write the page number
		dc->TextOut(0, *yPos, szText.GetBuffer(szText.GetLength()));
		*yPos+=textHeight;
	}

	if(*yPos+textHeight >= height)
	{
		// Set to start of a new page
		*yPos=0;
		// End current page
		dc->EndPage();
		// Create new page
		dc->StartPage();

		// Write the next page header title
		dc->TextOut(0, *yPos, header);
		*yPos+=textHeight;

		// Format the page number
		szText.Format(_T("Page %i"), m_pageNum++);
		// Write the page number
		dc->TextOut(0, *yPos, szText.GetBuffer(szText.GetLength()));
		*yPos+=textHeight;
	}
}
