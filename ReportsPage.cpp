// ReportsPage.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "ReportsPage.h"
#include "ProductionLine.h"
#include "Reports.h"
#include "OD3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportsPage property page

IMPLEMENT_DYNCREATE(CReportsPage, CPropertyPage)

CReportsPage::CReportsPage() : CPropertyPage(CReportsPage::IDD)
{
	//{{AFX_DATA_INIT(CReportsPage)
	m_editAutoLines = _T("");
	m_editNonAutoLines = _T("");
	m_comboProdLine = _T("");
	//}}AFX_DATA_INIT

	m_pDB = 0;
	m_pProdLineSet = 0;
}

CReportsPage::~CReportsPage()
{
}

void CReportsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportsPage)
	DDX_Control(pDX, IDC_REPORT_LIST, m_listReportPaths);
	DDX_Control(pDX, IDC_REPORTS_ADD_BUTTON, m_buttonAddPath);
	DDX_Control(pDX, IDC_REPORTS_REMOVE_BUTTON, m_buttonRemovePath);
	DDX_Control(pDX, IDC_REPORTS_AUTO_BUTTON, m_buttonAutopath);
	DDX_Control(pDX, IDC_REPORTS_NONAUTO_BUTTON, m_buttonNonAutoPath);
	DDX_Text(pDX, IDC_EDIT_AUTOLINES, m_editAutoLines);
	DDX_Text(pDX, IDC_EDIT_NONAUTOLINES, m_editNonAutoLines);
	DDX_CBString(pDX, IDC_REPORT_PRODLINE, m_comboProdLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CReportsPage)
	ON_EN_UPDATE(IDC_EDIT_AUTOLINES, OnUpdateEditAutolines)
	ON_EN_UPDATE(IDC_EDIT_NONAUTOLINES, OnUpdateEditNonautolines)
	ON_BN_CLICKED(IDC_REPORTS_ADD_BUTTON, OnReportsAddButton)
	ON_BN_CLICKED(IDC_REPORTS_REMOVE_BUTTON, OnReportsRemoveButton)
	ON_BN_CLICKED(IDC_REPORTS_AUTO_BUTTON, OnReportsAutoButton)
	ON_BN_CLICKED(IDC_REPORTS_NONAUTO_BUTTON, OnReportsNonautoButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportsPage message handlers
/////////////////////////////////////////////////////////////////////////////
//
BOOL CReportsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Set up list control
	this->DefineListControl();

	// Get Combobox controls
	CComboBox* LineSelection;
	LineSelection = (CComboBox*) this->GetDlgItem(IDC_REPORT_PRODLINE);

	// Check DB is open
	if (m_pDB != 0)
	{
		// Initialise Line Selection combo box
		m_pProdLineSet = new CProductionLine(m_pDB);	
		
		m_pProdLineSet->Open();
	
		while (!m_pProdLineSet->IsEOF())
		{
			if (m_pProdLineSet->m_Auto) 
				LineSelection->AddString(m_pProdLineSet->m_Line_ID);		
				
				m_pProdLineSet->MoveNext();
		}
		
		// Close recordset and release memory
		m_pProdLineSet->Close();	
		delete(m_pProdLineSet);
	}
	
	this->InitReportList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::OnUpdateEditAutolines() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
	CPropertyPage::OnApply();
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::OnUpdateEditNonautolines() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
	CPropertyPage::OnApply();
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::OnReportsAddButton() 
{
	this->UpdateData(true);
	CSysConfig* pProjectSettings = m_pDoc->GetProjectSettings();

	LVITEM ItemAttributes;								// List View Item Attributes
	
	// Initialise list control item attributes
	ItemAttributes.mask = LVIF_TEXT;					// Text member is required
	ItemAttributes.iItem = 0;							// Initial index of insertion point
	ItemAttributes.iSubItem = 0;						// Main Item
			
	if (pProjectSettings->AddReportAss(m_comboProdLine, m_editAutoLines))
	{
		ItemAttributes.pszText = m_comboProdLine.GetBuffer(1);					// Set text
		m_listReportPaths.InsertItem(&ItemAttributes);			// Insert into List Control

		ItemAttributes.iSubItem = 1;						// Set Sub Item (Row 0, Second Column)
		ItemAttributes.pszText = m_editAutoLines.GetBuffer(1);	// Set text	
		m_listReportPaths.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control
	}

	CPropertyPage::SetModified(true);
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::OnReportsRemoveButton() 
{
	int nSelectionHolder;
	CString sLine;
	CString sPath;
	CSysConfig* pProjectSettings = m_pDoc->GetProjectSettings();

	nSelectionHolder = this->m_listReportPaths.GetSelectionMark();

	sLine = m_listReportPaths.GetItemText(nSelectionHolder,0);
	sPath = m_listReportPaths.GetItemText(nSelectionHolder,1);

	if (pProjectSettings->DeleteReport(sLine, sPath))
	{
		m_listReportPaths.DeleteItem(nSelectionHolder);
	}	
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::OnReportsAutoButton() 
{
	// TODO: Add your control notification handler code here
	
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::OnReportsNonautoButton() 
{
	// TODO: Add your control notification handler code here
	
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::DefineListControl()
{
	LVCOLUMN ColumnAttributes;	// List View attributes structure

	// Define List Control Column Attributes for Column 1
	ColumnAttributes.mask = LVCF_FMT			 // Format member is valid (fmt)
						  | LVCF_SUBITEM		 // SubItem member is valid (iSubItem)
						  | LVCF_TEXT			 // Text member is valid (pszText)
						  | LVCF_WIDTH;			 // Width member is valid (cx)

	ColumnAttributes.fmt = LVCFMT_LEFT;			 // Left aligned text
	ColumnAttributes.pszText = "Production Line";// Title for Column 1
	ColumnAttributes.iSubItem = 0;				 // Main item
	ColumnAttributes.cx = 100;					 // Column Width

	// Insert first column
	m_listReportPaths.InsertColumn(0, &ColumnAttributes);

	// Change necessary attributes for column 2
	ColumnAttributes.pszText = "Directory Path"; // Title for Column 1
	ColumnAttributes.iSubItem = 1;				 // Sub Item
	ColumnAttributes.cx = 316;					 // Column Width

	// Insert second column to right of first column
	m_listReportPaths.InsertColumn(1, &ColumnAttributes);
}

/////////////////////////////////////////////////////////////////////////////
//
void CReportsPage::InitReportList()
{
	CReports*	pAssociate;
	CString sPath = _T("");
	CString sPLine = _T("");
	POSITION pos;

	LVITEM ItemAttributes;	// List View Item Attributes

	// Initialise list control item attributes
	ItemAttributes.mask = LVIF_TEXT;
	ItemAttributes.iItem = 0;
	ItemAttributes.iSubItem = 0; 

	CSysConfig* pProjectSettings = m_pDoc->GetProjectSettings();

	if(!pProjectSettings->m_tplReportList.IsEmpty())
	{
		for (pos = pProjectSettings->m_tplReportList.GetHeadPosition();pos != NULL;)
		{
			pAssociate = (CReports*)pProjectSettings->m_tplReportList.GetNext(pos);
			pAssociate->GetOutput(sPLine,sPath);

			ItemAttributes.iSubItem = 0;
			ItemAttributes.pszText = sPLine.GetBuffer(1);
			m_listReportPaths.InsertItem(&ItemAttributes);

			ItemAttributes.iSubItem = 1;
			ItemAttributes.pszText = sPath.GetBuffer(1);
			m_listReportPaths.SetItem(&ItemAttributes);

			ItemAttributes.iItem += 1;
		}
	}
}

