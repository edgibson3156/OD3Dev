// OutputPage.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "OutputPage.h"
#include "ProductionLine.h"
#include "OD3Doc.h"
#include "FolderBrowse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputPage property page

IMPLEMENT_DYNCREATE(COutputPage, CPropertyPage)

COutputPage::COutputPage() : CPropertyPage(COutputPage::IDD)
{
	//{{AFX_DATA_INIT(COutputPage)
	m_comboOutputLine = _T("");
	//}}AFX_DATA_INIT

	m_pDB = 0;
	m_pProdLineSet = 0;
}

COutputPage::~COutputPage()
{
}

void COutputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputPage)
	DDX_Control(pDX, IDC_EDIT_OUTPUT_PATH, m_outputPath);
	DDX_Control(pDX, IDC_OUTPUT_REMOVE_BUTTON, m_buttonRemove);
	DDX_Control(pDX, IDC_OUPUT_ADD_BUTTON, m_buttonAdd);
	DDX_Control(pDX, IDC_OUTPUT_LIST, m_listOutput);
	DDX_CBString(pDX, IDC__COMBO_OUTPUT_LINE, m_comboOutputLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutputPage, CPropertyPage)
	//{{AFX_MSG_MAP(COutputPage)
	ON_BN_CLICKED(IDC_OUPUT_ADD_BUTTON, OnOuputAddButton)
	ON_BN_CLICKED(IDC_OUTPUT_REMOVE_BUTTON, OnOutputRemoveButton)
	ON_BN_CLICKED(IDC_SELECT_OUTPATH_BUTTON, OnSelectOutpathButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputPage message handlers
/////////////////////////////////////////////////////////////////////////////
//
//
BOOL COutputPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Center Property Sheet
	CenterWindow();

	// Set up list control
	this->DefineListControl();

	// Get Combobox controls
	CComboBox* LineSelection;
	LineSelection = (CComboBox*) this->GetDlgItem(IDC__COMBO_OUTPUT_LINE);

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
	
	this->InitOutputList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
//
//
void COutputPage::OnOutputRemoveButton() 
{
	int nSelectionHolder;
	CString sLine;
	CString sPath;
	CSysConfig* pProjectSettings = m_pDoc->GetProjectSettings();

	nSelectionHolder = this->m_listOutput.GetSelectionMark();

	sLine = m_listOutput.GetItemText(nSelectionHolder,0);
	sPath = m_listOutput.GetItemText(nSelectionHolder,1);

	if (pProjectSettings->DeleteOutput(sLine, sPath))
	{
		m_listOutput.DeleteItem(nSelectionHolder);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Add to list control
//
void COutputPage::OnOuputAddButton() 
{
	int	iInsert = 0;
	this->UpdateData(true);
	CSysConfig	*pProjectSettings = m_pDoc->GetProjectSettings();
	CString		path;
	LVITEM		ItemAttributes;								// List View Item Attributes
	
	// Initialise list control item attributes
	ItemAttributes.mask = LVIF_TEXT;					// Text member is required
	ItemAttributes.iItem = iInsert;							// Initial index of insertion point
	ItemAttributes.iSubItem = 0;						// Main Item
			
	m_outputPath.GetWindowText(path);

	if (pProjectSettings->AddOutputAss(m_comboOutputLine, path))
	{
		ItemAttributes.pszText = m_comboOutputLine.GetBuffer(m_comboOutputLine.GetLength());
		// Insert into List Control
		iInsert = m_listOutput.InsertItem(&ItemAttributes);			

		// Set insertion position
		ItemAttributes.iItem = iInsert;	

		ItemAttributes.iSubItem = 1;						// Set Sub Item (Row 0, Second Column)
		ItemAttributes.pszText = path.GetBuffer(path.GetLength());//m_editOutputPath.GetBuffer(1);	// Set text	
		m_listOutput.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control
	}

	CPropertyPage::SetModified(true);
	m_pDoc->SetModifiedFlag(true);
	CPropertyPage::OnApply();
}

/////////////////////////////////////////////////////////////////////////////
//
//
void COutputPage::DefineListControl()
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
	ColumnAttributes.cx = 90;					 // Column Width

	// Insert first column
	m_listOutput.InsertColumn(0, &ColumnAttributes);

	// Change necessary attributes for column 2
	ColumnAttributes.pszText = "Path Details";		 // Title for Column 1
	ColumnAttributes.iSubItem = 1;				 // Sub Item
	ColumnAttributes.cx = 343;					 // Column Width

	// Insert second column to right of first column
	m_listOutput.InsertColumn(1, &ColumnAttributes);
}

/////////////////////////////////////////////////////////////////////////////
// INIT OUTPUT LIST
void COutputPage::InitOutputList()
{
	COutputList* pAssociate;
	CString sPath = _T("");
	CString sPLine = _T("");
	POSITION pos;
	int		iInsert = 0;

	LVITEM ItemAttributes;	// List View Item Attributes

	// Initialise list control item attributes
	ItemAttributes.mask = LVIF_TEXT;
	ItemAttributes.iItem = iInsert;
	ItemAttributes.iSubItem = 0; 

	CSysConfig* pProjectSettings = m_pDoc->GetProjectSettings();

	if(!pProjectSettings->m_tplOutputList.IsEmpty())
	{
		for (pos = pProjectSettings->m_tplOutputList.GetHeadPosition();pos != NULL;)
		{
			pAssociate = (COutputList*)pProjectSettings->m_tplOutputList.GetNext(pos);
			pAssociate->GetOutput(sPLine,sPath);

			ItemAttributes.iSubItem = 0;
			ItemAttributes.pszText = sPLine.GetBuffer(sPLine.GetLength());
			iInsert = m_listOutput.InsertItem(&ItemAttributes);

			// Set insertion point
			ItemAttributes.iItem = iInsert;

			ItemAttributes.iSubItem = 1;
			ItemAttributes.pszText = sPath.GetBuffer(sPath.GetLength());
			m_listOutput.SetItem(&ItemAttributes);
		}
	}
}

void COutputPage::OnSelectOutpathButton() 
{
	// TODO: Add your control notification handler code here
	CFolderBrowse	folder;
	CString			path;
	
	path=folder.getFolder();
	m_outputPath.SetWindowText(path);
}
