// AssociationPage.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "AssociationPage.h"
#include "SelectByGroup.h"
#include "OD3Doc.h"
//#include "Context.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAssociationPage property page

IMPLEMENT_DYNCREATE(CAssociationPage, CPropertyPage)

CAssociationPage::CAssociationPage() : CPropertyPage(CAssociationPage::IDD)
{
	//{{AFX_DATA_INIT(CAssociationPage)
	m_comboProductionLine = _T("");
	m_comboProducts = _T("");
	//}}AFX_DATA_INIT

	m_pDB = 0;
	m_pProdLineSet = 0;

	m_pProdGroupSet = 0;
	m_pProductsGroup = 0;

	m_pSectionTypeSet = 0;
	m_pSectionSelectionSet = 0;
}

CAssociationPage::~CAssociationPage()
{
}

void CAssociationPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssociationPage)
	DDX_Control(pDX, IDC_REMOVE_BUTTON, m_buttonRemove);
	DDX_Control(pDX, IDC_ASSOCIATE_BUTTON, m_buttoAssociate);
	DDX_Control(pDX, IDC_ASSOCIATION_LIST, m_listAssociation);
	DDX_CBString(pDX, IDC_COMBO_PRODLINE, m_comboProductionLine);
	DDX_CBString(pDX, IDC_COMBO_PRODUCTS, m_comboProducts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssociationPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAssociationPage)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_ASSOCIATE_BUTTON, OnAssociateButton)
	ON_BN_CLICKED(IDC_RADIO_PRODUCT, OnRadioProduct)
	ON_BN_CLICKED(IDC_RADIO_PRODUCTGROUP, OnRadioProductgroup)
	ON_BN_CLICKED(IDC_RADIO_SECTION_TYPE, OnRadioSectionType)
	ON_NOTIFY(LVN_KEYDOWN, IDC_ASSOCIATION_LIST, OnKeydownAssociationList)
	ON_NOTIFY(NM_RCLICK, IDC_ASSOCIATION_LIST, OnRclickAssociationList)
	ON_COMMAND(IDM_SYS_SELALL, OnSysSelall)
	ON_COMMAND(IDM_SYS_DEL, OnSysDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssociationPage message handlers
/////////////////////////////////////////////////////////////////////////////
//
//
BOOL CAssociationPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Center Property Sheet
	CenterWindow();

	// Set up list control
	this->DefineListControl();
	
	// Initialise association option buttons
	this->SetRadio(true, false /*, false */);

	// Get Combobox controls
	CComboBox* pProductLineCombo;
	CComboBox* pSelectionCombo;

	pProductLineCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODLINE);
	pSelectionCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTS);

	// Check DB is open
	if (m_pDB != 0)
	{	
		// Initialise Line Selection combo box
		m_pProdLineSet = new CProductionLine(m_pDB);	
		
		// Open Database
		m_pProdLineSet->Open();

		// Display contents of database entity into combo box
		while (!m_pProdLineSet->IsEOF())
		{
			if (m_pProdLineSet->m_Auto) 
				pProductLineCombo->AddString(m_pProdLineSet->m_Line_ID);
			
			m_pProdLineSet->MoveNext();
		}

		// Close recordset and release memory
		m_pProdLineSet->Close();	
		delete(m_pProdLineSet);

		// Create Product Group Recordset
		// Initialise Product Selection Combo Box
		m_pProdGroupSet = new CSelectGroupSet(m_pDB);	
		
		// Open recordset
		m_pProdGroupSet->Open();

		// Insert recordset data
		while (!m_pProdGroupSet->IsEOF())
		{
			pSelectionCombo->AddString(m_pProdGroupSet->m_Product_group);
			
			m_pProdGroupSet->MoveNext();
		}
	
		// Close recordset and release memory
		m_pProdGroupSet->Close();	
		delete(m_pProdGroupSet);
	}

	this->InitAssociationList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::OnRemoveButton() 
{
	int			selCount, count, i;
	CString		sLine = _T("");
	CString		sRollSet = _T("");
	CSysConfig	*pProjectSettings = m_pDoc->GetProjectSettings();

	// Get selection count
	if( (selCount=m_listAssociation.GetSelectedCount()) >0 )
	{
		// Count number of item in the list ctrl
		count = m_listAssociation.GetItemCount();

		for(i=0; i<count; i++)
		{
			if(m_listAssociation.GetItemState(i, LVIS_SELECTED)==2)
			{
				// Get item text
				sLine = m_listAssociation.GetItemText(i, 0);
				// Get sublitem text
				sRollSet = m_listAssociation.GetItemText(i, 1);

				// Delete project line association
				if (pProjectSettings->DeleteAssociation(sRollSet, sLine))
				{
					// Remove item from list ctrl
					m_listAssociation.DeleteItem(i);

					// Perform recursive function call to remove any more selections
					OnRemoveButton();
				}
			}
		}
	}

	m_pDoc->SetModifiedFlag(true);
	return;
}

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::OnAssociateButton() 
{
	UpdateData(true);
	CSysConfig* pProjectSettings = m_pDoc->GetProjectSettings();

	// Association options
	int ProdGroup;
	int SectType;
//	int Products;

	// List View Item Attributes
	
	LVITEM ItemAttributes;				

	// Initialise list control item attributes
	ItemAttributes.mask = LVIF_TEXT;	// Text member is required
	ItemAttributes.iItem = 0;			// Initial index of insertion point
	ItemAttributes.iSubItem = 0;		// Main Item
			
	// Check associate selection type
	this->GetRadio(ProdGroup, SectType /*, Products */);

	if (ProdGroup)
	{
		// Associations are by product group so create Recordset based on suitable query
		m_pProductsGroup = new CSelectByGroup(m_pDB);
		
		// Open recordset
		m_pProductsGroup->Open();

		// Set up parameter
		m_pProductsGroup->m_Group_Ident = _T(m_comboProducts.GetBuffer(1));

		// Requery
		m_pProductsGroup->Requery();


		// Insert recordset data into list box
		while (!m_pProductsGroup->IsEOF())
		{
		//	Set association into system configuration member variables
			if (pProjectSettings->AddAssociation(m_pProductsGroup->m_RollSet_ID, m_comboProductionLine))
			{
			// Insert Production Line 
				ItemAttributes.iSubItem = 0;									// Main Item			
				ItemAttributes.pszText = m_comboProductionLine.GetBuffer(1);	// Set text
				m_listAssociation.InsertItem(&ItemAttributes);		// Insert into List Control
	
				// Insert Product
				ItemAttributes.iSubItem = 1;					// Set Sub Item (Row 0, Second Column)
				ItemAttributes.pszText = m_pProductsGroup->m_RollSet_ID.GetBuffer(1);	// Set text
				m_listAssociation.SetItem(&ItemAttributes);		// Use SetItem to Insert into List Control
			}
			
			// Next record
			m_pProductsGroup->MoveNext();

		}
	
		// Close recordset and release memory
		m_pProductsGroup->Close();	
		delete(m_pProductsGroup);
	}
	else if (SectType)
	{
		// Associations are by section type so create Recordset
		//  based on a suitable query
		m_pSectionSelectionSet = new CSelectBySection(m_pDB);	
		
		// Open recordset
		m_pSectionSelectionSet->Open();

		// Set up parameter
		m_pSectionSelectionSet->m_Section_Ident = _T(m_comboProducts.GetBuffer(1));

		// Requery
		m_pSectionSelectionSet->Requery();

		// Insert recordset data into list box
		while (!m_pSectionSelectionSet->IsEOF())
		{
		//	Set association into system configuration member variables
			if (pProjectSettings->AddAssociation(m_pSectionSelectionSet->m_RollSet_ID, m_comboProductionLine))
			{
				// Insert Production Line 
				ItemAttributes.iSubItem = 0;									// Main Item			
				ItemAttributes.pszText = m_comboProductionLine.GetBuffer(1);	// Set text
				m_listAssociation.InsertItem(&ItemAttributes);		// Insert into List Control
	
				// Insert Product
				ItemAttributes.iSubItem = 1;				// Set Sub Item (Row 0, Second Column)
				ItemAttributes.pszText = m_pSectionSelectionSet->m_RollSet_ID.GetBuffer(1);	// Set text	
				m_listAssociation.SetItem(&ItemAttributes);		// Use SetItem to Insert into List Control
			}
						
			// Next record
			m_pSectionSelectionSet->MoveNext();

		}
	
		// Close recordset and release memory
		m_pSectionSelectionSet->Close();	
		delete(m_pSectionSelectionSet);	
	}
/*	else
	{

		// Association by product - simply take the Production Line
		// and Product Combo values

		//	Set association into system configuration member variables
		if (pProjectSettings->AddAssociation(m_comboProducts, m_comboProductionLine))
		{
			ItemAttributes.pszText = m_comboProductionLine.GetBuffer(1);	// Set text
			m_listAssociation.InsertItem(&ItemAttributes);				// Insert into List Control

			ItemAttributes.iSubItem = 1;								// Set Sub Item (Row 0, Second Column)
			ItemAttributes.pszText = m_comboProducts.GetBuffer(1);		// Set text	
			m_listAssociation.SetItem(&ItemAttributes);					// Use SetItem to Insert into List Control
		}
	}
*/
	CPropertyPage::SetModified(true);
	m_pDoc->SetModifiedFlag(true);
	CPropertyPage::OnApply();
}

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::OnRadioProduct() 
{
/*	// Get Combobox control
	CComboBox* pSelectionCombo;
	pSelectionCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTS);

	// Toggle radio buttons
	this->SetRadio(false, false, true);	

	// Create Products Recordset
	m_pProductsListSet = new CSelectNameSet(m_pDB);	
		
	// Open recordset
	m_pProductsListSet->Open();

	// Empty combo box
	pSelectionCombo->ResetContent();

	// Insert recordset data
	while (!m_pProductsListSet->IsEOF())
	{
		pSelectionCombo->AddString(m_pProductsListSet->m_Description);
			
		m_pProductsListSet->MoveNext();
	}
	
	// Close recordset and release memory
	m_pProductsListSet->Close();	
	delete(m_pProductsListSet);	
*/
 }

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::OnRadioProductgroup() 
{
	// Get Combobox control
	CComboBox* pSelectionCombo;
	pSelectionCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTS);

	// Toggle radio buttons
	this->SetRadio(true, false /*, false */);

	// Create Product Group Recordset
	m_pProdGroupSet = new CSelectGroupSet(m_pDB);	
		
	// Open recordset
	m_pProdGroupSet->Open();

	// Empty combo box
	pSelectionCombo->ResetContent();

	// Insert recordset data
	while (!m_pProdGroupSet->IsEOF())
	{
		pSelectionCombo->AddString(m_pProdGroupSet->m_Product_group);
			
		m_pProdGroupSet->MoveNext();
	}
	
	// Close recordset and release memory
	m_pProdGroupSet->Close();	
	delete(m_pProdGroupSet);	
}

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::OnRadioSectionType() 
{
	// Get Combobox control
	CComboBox* pSelectionCombo;
	pSelectionCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTS);

	// Toggle radio buttons
	this->SetRadio(false, true /*, false */);	

	// Create Sections Recordset
	m_pSectionTypeSet= new CSelectSectionSet(m_pDB);	

	// Open recordset
	m_pSectionTypeSet->Open();

	// Empty combo box
	pSelectionCombo->ResetContent();

	// Insert recordset data
	while (!m_pSectionTypeSet->IsEOF())
	{
		pSelectionCombo->AddString(m_pSectionTypeSet->m_RollSet_ID);
			
		m_pSectionTypeSet->MoveNext();
	}
	
	// Close recordset and release memory
	m_pSectionTypeSet->Close();	
	delete(m_pSectionTypeSet);
}

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::SetRadio(bool ProdGroup, bool SectType /*, bool Products */ )
{
	CButton* pProdGroupRadio;
	CButton* pSectionTypeRadio;
//	CButton* pProductRadio;

	// Assigning dialog controls to pointers
	pProdGroupRadio = (CButton*)this->GetDlgItem(IDC_RADIO_PRODUCTGROUP);
	pSectionTypeRadio = (CButton*)this->GetDlgItem(IDC_RADIO_SECTION_TYPE);
//	pProductRadio = (CButton*)this->GetDlgItem(IDC_RADIO_PRODUCT);

	// Checking the sate of the radio controls
	pProdGroupRadio->SetCheck(ProdGroup);
	pSectionTypeRadio->SetCheck(SectType);
//	pProductRadio->SetCheck(Products);
}

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::GetRadio(int &ProdGroup, int &SectType /*, int &Products */)
{
	CButton* pProdGroupRadio;
	CButton* pSectionTypeRadio;
//	CButton* pProductRadio;

	// Assigning controls to pointers
	pProdGroupRadio = (CButton*)this->GetDlgItem(IDC_RADIO_PRODUCTGROUP);
	pSectionTypeRadio = (CButton*)this->GetDlgItem(IDC_RADIO_SECTION_TYPE);
//	pProductRadio = (CButton*)this->GetDlgItem(IDC_RADIO_PRODUCT);

	// Checking state of the radio controls
	ProdGroup = pProdGroupRadio->GetCheck();
	SectType = pSectionTypeRadio->GetCheck();
//	Products = pProductRadio->GetCheck();
}

/////////////////////////////////////////////////////////////////////////////
//
//
void CAssociationPage::DefineListControl()
{
	LVCOLUMN	ColumnAttributes;	// List View attributes structure
	CRect		rect, scRect;
	CScrollBar	*sBar=NULL;

	// Get the size of the list ctrl
	m_listAssociation.GetClientRect(&rect);

	if((sBar=m_listAssociation.GetScrollBarCtrl(SB_VERT)))
		sBar->GetWindowRect(&scRect);
	else
		scRect.SetRectEmpty();

	// Define List Control Column Attributes for Column 1
	ColumnAttributes.mask = LVCF_FMT				// Format member is valid (fmt)
						  | LVCF_SUBITEM			// SubItem member is valid (iSubItem)
						  | LVCF_TEXT				// Text member is valid (pszText)
						  | LVCF_WIDTH;				// Width member is valid (cx)

	ColumnAttributes.fmt = LVCFMT_LEFT;				// Left aligned text
	ColumnAttributes.pszText = "Production Line";	// Title for Column 1
	ColumnAttributes.iSubItem = 0;					// Main item
	ColumnAttributes.cx = 90;						// Column Width
	
	// Insert first column
	m_listAssociation.InsertColumn(0, &ColumnAttributes);

	// Change necessary attributes for column 2
	ColumnAttributes.pszText = "Roll Setting";		// Title for Column 2
	ColumnAttributes.iSubItem = 1;					// Sub Item
	ColumnAttributes.cx = rect.Width()-90;			// Column Width

	// Insert second column to right of first column
	m_listAssociation.InsertColumn(1, &ColumnAttributes);
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InitAssociationList() A function to retrieve the product and production line associations
//						from the association list - used to populate the property page list box.
void CAssociationPage::InitAssociationList()
{
	CAssociation* pAssociate;
	CString sRollSet = _T("");
	CString sLine = _T("");
	LVITEM ItemAttributes;				
	POSITION pos;

	
	// Initialise list control item attributes
	ItemAttributes.mask = LVIF_TEXT;	// Text member is required
	ItemAttributes.iItem = 0;			// Initial index of insertion point
	ItemAttributes.iSubItem = 0;		// Main Item

	CSysConfig* pProjectSettings = m_pDoc->GetProjectSettings();
		
	if(!pProjectSettings->m_tplAssociationList.IsEmpty())		// First check if ObList is empty...
	{								// ... it's not, so loop through list to find a match ...
		for (pos = pProjectSettings->m_tplAssociationList.GetHeadPosition();pos != NULL;)
		{
			pAssociate = pProjectSettings->m_tplAssociationList.GetNext(pos);
			pAssociate->GetAssociation(sRollSet, sLine);
			ItemAttributes.iSubItem = 0;				// Set Sub Item (Row 0, Second Column)
			ItemAttributes.pszText = sLine.GetBuffer(1);
			m_listAssociation.InsertItem(&ItemAttributes);		// Insert into List Control

			ItemAttributes.iSubItem = 1;				// Set Sub Item (Row 0, Second Column)
			ItemAttributes.pszText = sRollSet.GetBuffer(1);	// Set text	
			m_listAssociation.SetItem(&ItemAttributes);		// Use SetItem to Insert into List Control
			
			ItemAttributes.iItem += 1;
		}
	}

}


void CAssociationPage::OnKeydownAssociationList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	// Test the key press for delete
	switch(pLVKeyDow->wVKey)
	{
		case VK_DELETE:
			// Prompt user for response
			if(m_listAssociation.GetItemCount() > 0 &&
				m_listAssociation.GetSelectedCount() > 0 &&
				AfxMessageBox(IDS_DELASSO, MB_YESNO|MB_ICONQUESTION)==IDYES)
			{
				// Delete the selected items
				OnRemoveButton();
			}
			break;

		case 'a':
		case 'A':
			if(pLVKeyDow->flags & VK_CONTROL)
				OnSysSelall();
			break;
	}

	*pResult = 0;
}

void CAssociationPage::OnRclickAssociationList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu	menubar;
	CPoint	point;

	GetCursorPos(&point);

	if (menubar.LoadMenu(IDR_SYSASS_POP))
	{
		// debug menu is the first popup
		CMenu* pPopup = menubar.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, 
								this->GetParent());
	}

	*pResult = 0;
}


void CAssociationPage::OnSysSelall() 
{
	// TODO: Add your command handler code here
	int	i, count;

	// Loop through and select all
	if( (count=m_listAssociation.GetItemCount()) )
	{
		for(i=0; i<count; i++)
		{
			if(m_listAssociation.GetItemState(i, LVIS_SELECTED)!=LVIS_SELECTED)
				m_listAssociation.SetItemState(i, LVIS_SELECTED, LVSIL_STATE);
		}
	}
}

void CAssociationPage::OnSysDel() 
{
	// TODO: Add your command handler code here
	if(m_listAssociation.GetItemCount() > 0 && 
		m_listAssociation.GetSelectedCount() > 0 &&
		AfxMessageBox(IDS_DELASSO, MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		OnRemoveButton();
	}

}
