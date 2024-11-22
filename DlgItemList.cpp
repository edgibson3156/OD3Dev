// DlgItemList.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DlgItemList.h"
#include "Item.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgItemList dialog


CDlgItemList::CDlgItemList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgItemList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgItemList)
	m_comboCodes = _T("");
	m_comboNames = _T("");
	m_comboProfile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgItemList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgItemList)
	DDX_Control(pDX, IDC_ACC_LIST, m_accList);
	DDX_Control(pDX, IDC_ITEMS_LIST, m_listItemDisplay);
	DDX_CBString(pDX, IDC_COMBO_PRODUCTCODES, m_comboCodes);
	DDX_CBString(pDX, IDC_COMBO_PRODUCTNAMES, m_comboNames);
	DDX_CBString(pDX, IDC_COMBO_PROFILE, m_comboProfile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgItemList, CDialog)
	//{{AFX_MSG_MAP(CDlgItemList)
	ON_BN_CLICKED(IDC_APPLY_ITEM_NO, OnApplyItemNo)
	ON_CBN_EDITCHANGE(IDC_COMBO_PRODUCTS, OnEditchangeComboProducts)
	ON_BN_CLICKED(IDC_JR_PRODUCTS, OnJrProducts)
	ON_BN_CLICKED(IDC_SBE_PRODUCTS, OnSbeProducts)
	ON_BN_CLICKED(IDC_STANDARD_PRODUCTS, OnStandardProducts)
	ON_CBN_SELCHANGE(IDC_COMBO_PRODUCTCODES, OnSelchangeComboProductcodes)
	ON_CBN_SELCHANGE(IDC_COMBO_PRODUCTNAMES, OnSelchangeComboProductnames)
	ON_CBN_SELCHANGE(IDC_COMBO_PROFILE, OnSelchangeComboProfile)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgItemList message handlers

BOOL CDlgItemList::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CDaoDatabase* pDB = this->m_pDoc->m_pProjectSettings->m_pDB;
	POSITION Endpos;
	CItem*   pTest;
	int		 nItemTotal;
	
	if (!this->m_pDoc->m_tplItemList.IsEmpty())
	{
		Endpos = this->m_pDoc->m_tplItemList.GetTailPosition();

		pTest = this->m_pDoc->m_tplItemList.GetAt(Endpos);
		nItemTotal = pTest->GetItemID(); 
	}
	

	UpdateData(false);

	// Set up list control
	DefineListControl();

	if (m_sFilter == _T("GEN"))
	{
		this->SetRadio(true, false, false);
	}
	else if (m_sFilter == _T("JRS"))
	{
		this->SetRadio(false, true, false);
	}
	else if (m_sFilter == _T("SBE"))
	{
		this->SetRadio(false, false, true);
	}
	else
	{
		this->SetRadio(true, false, false);
		m_sFilter = _T("GEN");
	}

	this->PopCombos(m_sFilter);


	//	Initialise display list with currently listed items
	this->InitDisplayList();
	this->m_bIsModified = false;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// OnApplyItemNo() 
//
void CDlgItemList::OnApplyItemNo() 
{
	POSITION pos;
	CItem*	 pItem;
	CString	 sTemp = _T("");
	CString	 sProductName = _T("");
	CString	 sProductCode = _T("");
	CString	 sProfile = _T("");
	CString	 sType = _T("");
	CString	 szProductLabel = _T("");
	CString	 sItemID = _T("");
	CString	 szMsg = _T("");
	int		 nItemID;

	UpdateData(true);

	if (this->m_comboCodes == _T(""))
	{
		AfxMessageBox("You must select a product to be able to add it!");
		return;
	}

	sProductCode = this->m_sFilter;
	sProductCode += this->m_comboCodes;
	sType = this->m_pDoc->GetMemberTypeLabel(m_nType);

	// Dont add accessories here
	if(m_nType==0)
	{
		addAccessory();
		return;
	}

	//	check to see if product already assigned to item
	if(IsCodeAssigned(sProductCode))
	{
		nItemID = m_pItem->GetItemID();
		sItemID.Format("%d",nItemID);
		CString szMsg = "Item number ";
		szMsg += sItemID;
		szMsg += " has already been assigned to product code ";
		szMsg += sProductCode;
		szMsg += "\n\nDo you want to create another one?";

		if(AfxMessageBox(szMsg,MB_ICONQUESTION + MB_YESNO) == IDNO)
			return;

	}

	// Get the next free item number
	nItemID=getFreeItemNumber(false);

	
	bool bIsBeam = false;
	switch (this->m_nType)
	{
	case PURLIN:
	case STUD:
		bIsBeam = true;
		break;
	case RAIL:
		bIsBeam = true;
		break;
	case SWAGEBEAM:
		bIsBeam = true;
		break;
	case PRESSED:
		bIsBeam = true;
		break;
	case STOCK:
		bIsBeam = true;
		break;
	default:
		bIsBeam = false;
		break;
	}

	// Create the new item
	pItem = this->m_pDoc->CreateItem(nItemID);

	pItem->SetBeam(bIsBeam);
	pItem->SetType(this->m_nType);
	pItem->SetProductCode(sProductCode);
	pItem->SetProductName(this->m_comboNames);
	pItem->SetProfile(this->m_comboProfile);
	pItem->SetSectionID(this->m_sSectionID);
	pItem->SetProductWeight(this->m_nWeight);
			
	// Repaint display list in correct order

	// ... first invalidate current list
	m_listItemDisplay.DeleteAllItems();

	// ... now reconstruct list

	// ... start by initialising list control item attributes
	LVITEM ItemAttributes;				
	ItemAttributes.mask = LVIF_TEXT;	// Text member is required
	ItemAttributes.iItem = 0;			// Initial index of insertion point
	ItemAttributes.iSubItem = 0;		// Main Item
			
	//	Sort item list by itemID
	this->m_pDoc->SortByItemID(ISBEAM);

	// ... now get data to display from the item list	
	pos = this->m_pDoc->m_tplItemList.GetHeadPosition();
	while (pos)
	{
		pItem = this->m_pDoc->m_tplItemList.GetNext(pos);
		nItemID = pItem->GetItemID();
		sItemID.Format("%d",nItemID);
		int nType = pItem->GetType();

		ItemAttributes.iSubItem = 0;							// Set Sub Item (Row n, First Column)
		ItemAttributes.pszText = sItemID.GetBuffer(1);			// Set text
		this->m_listItemDisplay.InsertItem(&ItemAttributes);	// Insert into List Control

		ItemAttributes.iSubItem = 1;							// Set Sub Item (Row n, Second Column)
		sTemp = pItem->GetProductCode();
		sProductCode = sTemp.Right((sTemp.GetLength())-3);
		ItemAttributes.pszText = sProductCode.GetBuffer(1);		// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 2;							// Set Sub Item (Row n, Third Column)
		sProfile = pItem->GetProfile();
		ItemAttributes.pszText = sProfile.GetBuffer(1);			// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 3;							// Set Sub Item (Row n, Fourth Column)
		sProductName = pItem->GetProductName();
		ItemAttributes.pszText = sProductName.GetBuffer(1);		// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 4;							// Set Sub Item (Row n, Fifth Column)
		sType = this->m_pDoc->GetMemberTypeLabel(nType);
		ItemAttributes.pszText = sType.GetBuffer(1);			// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iItem += 1;
	}

	this->m_bIsModified = false;
	this->m_pDoc->UpdateAllViews(NULL);

	return;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  IsCodeAssigned()
//
bool CDlgItemList::IsCodeAssigned(LPCTSTR sProductCode)
{
	CString		sItemID;
	POSITION	pos;
	CItem		*pItem;
	bool		bResult=false;


	// Get the beam head position
	pos = this->m_pDoc->m_tplItemList.GetHeadPosition();

	while(pos)
	{
		pItem = this->m_pDoc->m_tplItemList.GetNext(pos);
		if (pItem->GetProductCode() == (CString)sProductCode)
		{
			// Set member pointer
			m_pItem = pItem;
			// Set result flag
			bResult=true;
			// Exit from loop
			break;
		}
	}

	
	if(!bResult)
	{
		// Get the accessories head position
		pos = m_pDoc->m_tplAccItemList.GetHeadPosition();

		// Loop accessories
		while(pos)
		{
			// Get the next item object
			pItem = this->m_pDoc->m_tplItemList.GetNext(pos);

			// Test 
			if (pItem->GetProductName() == (CString)sProductCode)
			{
				// Set member pointer
				m_pItem = pItem;
				// Set result flag
				bResult=true;
				// Exit from loop
				break;
			}
		}
	}


	return(bResult);
}


/////////////////////////////////////////////////////////////////////////////
//  DefineListControl()
//
void CDlgItemList::DefineListControl()
{
	DWORD	dwNewStyle;
	CRect	rect;
	int		increment=0;

	dwNewStyle = LVS_EX_FULLROWSELECT;

	// Get the size of the list control
	m_listItemDisplay.GetClientRect(&rect);

	m_listItemDisplay.SetExtendedStyle(dwNewStyle);
	m_accList.SetExtendedStyle(dwNewStyle);
	
	// List View attributes structure
	LVCOLUMN ColumnAttributes;	

	// Define List Control Column Attributes for Column 1
	ColumnAttributes.mask = LVCF_FMT					// Format member is valid (fmt)
						  | LVCF_SUBITEM				// SubItem member is valid (iSubItem)
						  | LVCF_TEXT					// Text member is valid (pszText)
						  | LVCF_WIDTH;					// Width member is valid (cx)

	ColumnAttributes.fmt = LVCFMT_LEFT;					// Left aligned text
	ColumnAttributes.pszText = "Item #";				// Title for Column 1
	ColumnAttributes.iSubItem = 0;						// Main item
	ColumnAttributes.cx = 45;							// Column Width
	increment+=ColumnAttributes.cx;
	
	// Insert first column
	m_listItemDisplay.InsertColumn(0, &ColumnAttributes);
	m_accList.InsertColumn(0, &ColumnAttributes);

	// Change necessary attributes for column 2
	ColumnAttributes.pszText = "Code";					// Title for Column 2
	ColumnAttributes.iSubItem = 1;						// Sub Item
	ColumnAttributes.cx = 75;							// Column Width
	increment+=ColumnAttributes.cx;

	// Insert second column to right of first column
	m_listItemDisplay.InsertColumn(1, &ColumnAttributes);
	m_accList.InsertColumn(1, &ColumnAttributes);
	
	// Change necessary attributes for column 3
	ColumnAttributes.pszText = "Profile";				// Title for Column 3
	ColumnAttributes.iSubItem = 2;						// Sub Item
	ColumnAttributes.cx = 120;							// Column Width
	increment+=ColumnAttributes.cx;

	// Insert third column to right of third column
	m_listItemDisplay.InsertColumn(2, &ColumnAttributes);
	m_accList.InsertColumn(2, &ColumnAttributes);

	// Change necessary attributes for column 4
	ColumnAttributes.pszText = "Product Name";			// Title for Column 4
	ColumnAttributes.iSubItem = 3;						// Sub Item
	ColumnAttributes.cx = (rect.Width()-increment)-80;	// Column Width


	// Insert fourth column to right of third column
	m_listItemDisplay.InsertColumn(3, &ColumnAttributes);
	m_accList.InsertColumn(3, &ColumnAttributes);

	// Change necessary attributes for column 5
	ColumnAttributes.pszText = "Type";					// Title for Column 5
	ColumnAttributes.iSubItem = 4;						// Sub Item
	ColumnAttributes.cx = 80;							// Column Width


	// Insert fifth column to right of second column
	m_listItemDisplay.InsertColumn(4, &ColumnAttributes);
	m_accList.InsertColumn(4, &ColumnAttributes);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InitDisplayList() A function to retrieve the product and item no. associations
//						from the item list - used to populate the import items dlg. list box.
//
void CDlgItemList::InitDisplayList()
{
	CItem*	 pItem;
	CString  sTemp = _T("");
	CString  sProduct = _T("");
	CString  sProfile = _T("");
	CString  sItemID = _T("");
	CString  sType = _T("");
	CString  sMemberType = _T("");
	CString  sProductCode = _T("");
	int		 cItem = 0;
	int		 nType = 0;
	POSITION pos;

	LVITEM ItemAttributes;				// List View Item Attributes

	// Initialise list control item attributes
	ItemAttributes.mask = LVIF_TEXT;	// Text member is required
	ItemAttributes.iItem = 0;			// Initial index of insertion point
	ItemAttributes.iSubItem = 0;		// Main Item

	pos = this->m_pDoc->m_tplItemList.GetHeadPosition();

	while(pos)
	{
		pItem = this->m_pDoc->m_tplItemList.GetNext(pos);
		cItem = pItem->GetItemID();
		sItemID.Format("%d",cItem);
		sProfile = pItem->GetProfile();
		nType = pItem->GetType();
		sType = this->m_pDoc->GetMemberTypeLabel(nType);
		sProduct = pItem->GetProductName();
		sTemp = pItem->GetProductCode();
		sProductCode = sTemp.Right((sTemp.GetLength())-3);

		ItemAttributes.iSubItem = 0;						// Set Sub Item (Row n, First Column)
		ItemAttributes.pszText = sItemID.GetBuffer(1);		// Set text	
		m_listItemDisplay.InsertItem(&ItemAttributes);		// Insert into List Control

		ItemAttributes.iSubItem = 1;						// Set Sub Item (Row n, Second Column)
		ItemAttributes.pszText = sProductCode.GetBuffer(1);	// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 2;						// Set Sub Item (Row n, Third Column)
		ItemAttributes.pszText = sProfile.GetBuffer(1);		// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 3;						// Set Sub Item (Row n, Fourth Column)
		ItemAttributes.pszText = sProduct.GetBuffer(1);		// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 4;						// Set Sub Item (Row n, Fifth Column)
		ItemAttributes.pszText = sType.GetBuffer(1);	// Set text	
		m_listItemDisplay.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iItem += 1;

	}

	// Get the head position for the accessories
	pos = this->m_pDoc->m_tplAccItemList.GetHeadPosition();
	ItemAttributes.iItem = 0;

	while(pos)
	{
		pItem = this->m_pDoc->m_tplAccItemList.GetNext(pos);
		cItem = pItem->GetItemID();
		sItemID.Format("%d",cItem);
		sProfile = pItem->GetProfile();
		nType = pItem->GetType();
		sType = this->m_pDoc->GetMemberTypeLabel(nType);
		sProduct = pItem->GetProductName();
		sTemp = pItem->GetProductCode();
		sProductCode = sTemp.Right((sTemp.GetLength())-3);

		ItemAttributes.iSubItem = 0;						// Set Sub Item (Row n, First Column)
		ItemAttributes.pszText = sItemID.GetBuffer(1);		// Set text	
		m_accList.InsertItem(&ItemAttributes);		// Insert into List Control

		ItemAttributes.iSubItem = 1;						// Set Sub Item (Row n, Second Column)
		ItemAttributes.pszText = sProductCode.GetBuffer(1);	// Set text	
		m_accList.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 2;						// Set Sub Item (Row n, Third Column)
		ItemAttributes.pszText = sProfile.GetBuffer(1);		// Set text	
		m_accList.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 3;						// Set Sub Item (Row n, Fourth Column)
		ItemAttributes.pszText = sProduct.GetBuffer(1);		// Set text	
		m_accList.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 4;						// Set Sub Item (Row n, Fifth Column)
		ItemAttributes.pszText = sType.GetBuffer(1);	// Set text	
		m_accList.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

		ItemAttributes.iItem += 1;

	}
}


void CDlgItemList::OnEditchangeComboProducts()
{
	m_bIsModified = true;
} 


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	OnJrProducts()	Setup combo box strings based on the JRS product code prefix
//
void CDlgItemList::OnJrProducts() 
{
	this->SetRadio(false, true, false);
	m_sFilter = _T("JRS");

	this->PopCombos(m_sFilter);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	OnSbeProducts()	Setup combo box strings based on the SBE product code prefix
//
void CDlgItemList::OnSbeProducts() 
{
	this->SetRadio(false, false, true);
	m_sFilter = _T("SBE");

	this->PopCombos(m_sFilter);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	OnStandardProducts()	Setup combo box strings based on the GEN product code prefix
//
void CDlgItemList::OnStandardProducts() 
{
	this->SetRadio(true, false, false);
	m_sFilter = _T("GEN");

	this->PopCombos(m_sFilter);
}

///////////////////////////////////////////////////////////////////////////////////////
//	OnSelchangeComboProductcodes()	Message handler to set current selection in combo boxes
//									to match selected product code
//
void CDlgItemList::OnSelchangeComboProductcodes() 
{
	CDaoDatabase* pDB = this->m_pDoc->m_pProjectSettings->m_pDB;

	// Get selected Product Code from combo box
	CString strItem = _T("");
	CString sType = _T("");

	CComboBox* pCodeBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTCODES);

	int nIndex = pCodeBox->GetCurSel();
	if (nIndex == CB_ERR)
		return;

	pCodeBox->GetLBText(nIndex, strItem);

	this->m_comboCodes = strItem;

	// Get "Profile" & "Product Names" from database based on selected "Product Code"

	CString szOD3Code = _T("");
	szOD3Code = this->m_sFilter;
	szOD3Code += this->m_comboCodes;

	m_pGetProduct = new CProductData(pDB);

	// Set code parameter
	m_pGetProduct->m_Product_Ident = szOD3Code;
		
	// Open recordset
	m_pGetProduct->Open();
	while (!m_pGetProduct->IsEOF())
	{
		this->m_comboProfile = m_pGetProduct->m_ProductName;
		this->m_comboNames = m_pGetProduct->m_Aviion_Desc;
		this->m_nWeight = m_pGetProduct->m_Weight;
		this->m_sSectionID = m_pGetProduct->m_Section_ID;

		// convert type string to int
		sType = m_pGetProduct->m_Product_Type;
		this->m_nType = this->m_pDoc->GetMemberTypeValue(sType);

		m_pGetProduct->MoveNext();
	}

	// Close recordset and release memory
	m_pGetProduct->Close();	
	delete(m_pGetProduct);

	// Find "Profile" in combo box and display in edit control
	int nStartAfter = -1;

	CComboBox* pProfileBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PROFILE);
	LPCTSTR lpszString = this->m_comboProfile.GetBuffer(1);
	nIndex = pProfileBox->SelectString(nStartAfter, lpszString);
	pProfileBox->SetCurSel(nIndex);

	// Find Product Name in combo box and display in edit control
	CComboBox* pNameBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTNAMES);
	lpszString = this->m_comboNames.GetBuffer(1);
	nIndex = pNameBox->SelectString(nStartAfter, lpszString);
	pNameBox->SetCurSel(nIndex);
	
}

///////////////////////////////////////////////////////////////////////////////////////
//	OnSelchangeComboProductnames()	Message handler to set current selection in combo boxes
//									to match selected product name
//
void CDlgItemList::OnSelchangeComboProductnames() 
{
	CDaoDatabase	*pDB = this->m_pDoc->m_pProjectSettings->m_pDB;
	CComboBox		*pCodeBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTCODES);
	CComboBox		*pProfileBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PROFILE);

	// Get selected Product Name from combo box
	CString strItem = _T("");
	CString sType = _T("");

	CComboBox* pNameBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTNAMES);

	int nIndex = pNameBox->GetCurSel();
	if (nIndex == CB_ERR)
		return;

	pNameBox->GetLBText(nIndex, strItem);

	this->m_comboNames = strItem;

	// Get "Profile" & "Product Code" from database based on selected "Product Name"

	m_pGetCode = new CSelectProductByName(pDB);

	// Set code parameter
	m_pGetCode->m_Customer_Filter = this->m_sFilter;
	m_pGetCode->m_Aviion_Name = this->m_comboNames;
		
	// Open recordset
	m_pGetCode->Open();
	

	while (!m_pGetCode->IsEOF())
	{
		this->m_comboProfile = m_pGetCode->m_ProductName;
		this->m_comboCodes = m_pGetCode->m_Aviion_Prodcode;
		this->m_nWeight = m_pGetCode->m_Weight;
		this->m_sSectionID = m_pGetCode->m_Section_ID;

		// convert type string to int
		sType = m_pGetCode->m_Product_Type;
		this->m_nType = this->m_pDoc->GetMemberTypeValue(sType);

		m_pGetCode->MoveNext();
	}

	// Close recordset and release memory
	m_pGetCode->Close();	
	delete(m_pGetCode);

	// Find "Profile" in combo box and display in edit control
	int nStartAfter = -1;

	LPCTSTR lpszString = this->m_comboProfile.GetBuffer(1);
	nIndex = pProfileBox->SelectString(nStartAfter, lpszString);
	pProfileBox->SetCurSel(nIndex);

	// Find Product Code in combo box and display in edit control
	lpszString = this->m_comboCodes.GetBuffer(1);
	nIndex = pCodeBox->SelectString(nStartAfter, lpszString);
	pCodeBox->SetCurSel(nIndex);
	
	
}

///////////////////////////////////////////////////////////////////////////////////////
//	OnSelchangeComboProfile()		Message handler to set current selection in combo boxes
//									to match selected profile
//
void CDlgItemList::OnSelchangeComboProfile() 
{
	CDaoDatabase* pDB = this->m_pDoc->m_pProjectSettings->m_pDB;

	// Get selected Profile from combo box
	CString strItem = _T("");
	CString sType = _T("");

	CComboBox* pProfileBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PROFILE);

	int nIndex = pProfileBox->GetCurSel();
	if (nIndex == CB_ERR)
		return;

	pProfileBox->GetLBText(nIndex, strItem);

	this->m_comboProfile = strItem;

	// Get "Product Codes" & "Product Names" from database based on selected "Profile"

	CString szOD3Code = _T("");
	szOD3Code = this->m_sFilter;
	szOD3Code += this->m_comboCodes;

	m_pGetName = new CSelectByProfile(pDB);

	// Set code parameter
	m_pGetName->m_Profile_ID = this->m_comboProfile;
		
	// Open recordset
	m_pGetName->Open();
	while (!m_pGetName->IsEOF())
	{
		this->m_comboCodes = m_pGetName->m_Aviion_Prodcode;
		this->m_comboNames = m_pGetName->m_Aviion_Desc;
		this->m_nWeight = m_pGetName->m_Weight;
		this->m_sSectionID = m_pGetName->m_Section_ID;

		// convert type string to int
		sType = m_pGetName->m_Product_Type;
		this->m_nType = this->m_pDoc->GetMemberTypeValue(sType);

		m_pGetName->MoveNext();
	}

	// Close recordset and release memory
	m_pGetName->Close();	
	delete(m_pGetName);

	// Find "ProductCode" in combo box and display in edit control
	int nStartAfter = -1;

	CComboBox* pCodeBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTCODES);
	LPCTSTR lpszString = this->m_comboCodes.GetBuffer(1);
	nIndex = pCodeBox->SelectString(nStartAfter, lpszString);
	pCodeBox->SetCurSel(nIndex);

	// Find Product Name in combo box and display in edit control
	CComboBox* pNameBox = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTNAMES);
	lpszString = this->m_comboNames.GetBuffer(1);
	nIndex = pNameBox->SelectString(nStartAfter, lpszString);
	pNameBox->SetCurSel(nIndex);
	
	AfxMessageBox("When selecting by Profile make sure you have got the correct PURLIN/RAIL type");
}

//////////////////////////////////////////////////////////////////////////////////////////
//	SetRadio()
//
void CDlgItemList::SetRadio(bool ProdGEN, bool ProdJRS, bool ProdSBE)
{
	CButton* pRadioGENprods;
	CButton* pRadioJRSprods;
	CButton* pRadioSBEprods;

	// Assigning dialog controls to pointers
	pRadioGENprods = (CButton*)this->GetDlgItem(IDC_STANDARD_PRODUCTS);
	pRadioJRSprods = (CButton*)this->GetDlgItem(IDC_JR_PRODUCTS);
	pRadioSBEprods = (CButton*)this->GetDlgItem(IDC_SBE_PRODUCTS);

	// Checking state of radio buttons
	pRadioGENprods->SetCheck(ProdGEN);
	pRadioJRSprods->SetCheck(ProdJRS);
	pRadioSBEprods->SetCheck(ProdSBE);
}

//////////////////////////////////////////////////////////////////////////////////////////
//	GetRadio()
//
void CDlgItemList::GetRadio(int &ProdGEN, int &ProdJRS, int &ProdSBE)
{	
	CButton* pRadioGENprods;
	CButton* pRadioJRSprods;
	CButton* pRadioSBEprods;

	// Assigning controls to pointers
	pRadioGENprods = (CButton*)this->GetDlgItem(IDC_STANDARD_PRODUCTS);
	pRadioJRSprods = (CButton*)this->GetDlgItem(IDC_JR_PRODUCTS);
	pRadioSBEprods = (CButton*)this->GetDlgItem(IDC_SBE_PRODUCTS);

	// Checking state of radio controls
	ProdGEN = pRadioGENprods->GetCheck();
	ProdJRS = pRadioJRSprods->GetCheck();
	ProdSBE = pRadioSBEprods->GetCheck();
}

//////////////////////////////////////////////////////////////////////////////////////////
//	PopCombos()		Get recordsets from database and use to populate the combo boxes
//
void CDlgItemList::PopCombos(LPCTSTR szFilter)
{
	CDaoDatabase* pDB = this->m_pDoc->m_pProjectSettings->m_pDB;

	CString  sComboCodeString = _T("");
	CString  sComboProfileString = _T("");
	CString  sComboNameString = _T("");

	// Initialise Combobox control & contents
	CComboBox* pCodeSelectionCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTCODES);
	CComboBox* pNameSelectionCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTNAMES);
	CComboBox* pcomboDetail = (CComboBox*)this->GetDlgItem(IDC_COMBO_PRODUCTNAMES);

	
	// Remove any selection
	pcomboDetail->SetCurSel(-1);

	// Create "Products" recordset from database
	m_pSelectCodes = new CDaoCustomerSet(pDB);
	
	//	Set 'filter' parameter
	m_pSelectCodes->m_Customer_Filter = m_sFilter;

	// Open recordset
	m_pSelectCodes->Open();


	// Empty combo box
	pCodeSelectionCombo->ResetContent();

	// Insert recordset data
	while (!m_pSelectCodes->IsEOF())
	{
		sComboCodeString = m_pSelectCodes->m_Aviion_Prodcode;	//	This is not OD3 specific and excludes GEN/JRS/SBE prefix to Aviion partcode.
		sComboNameString = m_pSelectCodes->m_Aviion_Desc;	

		if(pCodeSelectionCombo->FindStringExact(-1, sComboCodeString) == CB_ERR)
			pCodeSelectionCombo->AddString(sComboCodeString.GetBuffer(1));

		if(pNameSelectionCombo->FindStringExact(-1, sComboNameString) == CB_ERR)
			pNameSelectionCombo->AddString(sComboNameString.GetBuffer(1));
			
		m_pSelectCodes->MoveNext();
	}

	// Close recordset and release memory
	m_pSelectCodes->Close();	
	delete(m_pSelectCodes);	

	// Initialise Profile Combobox control & contents
	CComboBox* pProfileSelectionCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PROFILE);

	m_pSelectProfile = new CProfileList(pDB);

	//	Set 'filter' parameter
	m_pSelectProfile->m_Customer_Filter = m_sFilter;

	// Open recordset
	m_pSelectProfile->Open();

	// Empty combo box
	pProfileSelectionCombo->ResetContent();

	// Insert recordset data
	while (!m_pSelectProfile->IsEOF())
	{
		sComboProfileString = m_pSelectProfile->m_ProductName;		//	This is OD3 specific and includes GEN/JRS/SBE prefix to Aviion partcode, filtered as specified above.

		if(pProfileSelectionCombo->FindStringExact(-1, sComboProfileString) == CB_ERR)
			pProfileSelectionCombo->AddString(sComboProfileString.GetBuffer(1));
			
		m_pSelectProfile->MoveNext();
	}

	// Close recordset and release memory
	m_pSelectProfile->Close();	
	delete(m_pSelectProfile);	
}


void CDlgItemList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	UINT uFlags = 0;
	int nHitItem = m_listItemDisplay.HitTest(point, &uFlags);

	CRect rect;
	m_listItemDisplay.GetItemRect(nHitItem, rect, LVIR_BOUNDS);
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgItemList::addAccessory() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CItem*	 pItem;
	CString	 sTemp;
	CString	 sProductName;
	CString	 sProductCode;
	CString	 sProfile;
	CString	 sType;
	CString	 sItemID;
	int		 nItemID=1;


	sProductCode = m_sFilter;
	sProductCode += m_comboCodes;
	sType = this->m_pDoc->GetMemberTypeLabel(m_nType);


	//	check to see if product already assigned to item
	if(IsCodeAssigned(m_comboNames))
	{
		sTemp.Format("Item number %i has already been assigned to product code %s\n\nDo you want to create another one?",
							m_pItem->GetItemID(), m_comboNames);

		// Confirm create duplicate item
		if(AfxMessageBox(sTemp,MB_ICONQUESTION + MB_YESNO) == IDNO)
			return;

	}

	// Remove all the accessories from the list
	m_accList.DeleteAllItems();

	// Get the next free item number
	nItemID=getFreeItemNumber(true);

	// Create the accessory
	pItem = this->m_pDoc->CreateItem(nItemID, 0);

	pItem->SetBeam(false);
	pItem->SetType(this->m_nType);
	pItem->SetProductCode(sProductCode);
	pItem->SetProductName(this->m_comboNames);
	pItem->SetSectionID(this->m_sSectionID);
	pItem->SetProductWeight(this->m_nWeight);
	pItem->SetProdLine(D_BRACE);
	pItem->SetProdLineLabel(_T("Diagonal_Brace"));

	// Sort the list by item ID
	m_pDoc->SortByItemID(ISACCESSORY);

	// ... start by initialising list control item attributes
	LVITEM ItemAttributes;				
	ItemAttributes.mask = LVIF_TEXT;	// Text member is required
	ItemAttributes.iItem = 0;			// Initial index of insertion point
	ItemAttributes.iSubItem = 0;		// Main Item

	pos = this->m_pDoc->m_tplAccItemList.GetHeadPosition();
	while (pos)
	{
		pItem = this->m_pDoc->m_tplAccItemList.GetNext(pos);
		nItemID = pItem->GetItemID();
		sItemID.Format("%d",nItemID);
		int nType = pItem->GetType();

		ItemAttributes.iSubItem = 0;							// Set Sub Item (Row n, First Column)
		ItemAttributes.pszText = sItemID.GetBuffer(1);			// Set text
		m_accList.InsertItem(&ItemAttributes);	// Insert into List Control

		ItemAttributes.iSubItem = 1;							// Set Sub Item (Row n, Second Column)
		sTemp = pItem->GetProductCode();
		sProductCode = sTemp.Right((sTemp.GetLength())-3);
		ItemAttributes.pszText = sProductCode.GetBuffer(1);		// Set text	
		m_accList.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 2;							// Set Sub Item (Row n, Third Column)
		sProfile = pItem->GetProfile();
		ItemAttributes.pszText = sProfile.GetBuffer(1);			// Set text	
		m_accList.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 3;							// Set Sub Item (Row n, Fourth Column)
		sProductName = pItem->GetProductName();
		ItemAttributes.pszText = sProductName.GetBuffer(1);		// Set text	
		m_accList.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iSubItem = 4;							// Set Sub Item (Row n, Fifth Column)
		sType = this->m_pDoc->GetMemberTypeLabel(nType);
		ItemAttributes.pszText = sType.GetBuffer(1);			// Set text	
		m_accList.SetItem(&ItemAttributes);				// Use SetItem to Insert into List Control

		ItemAttributes.iItem += 1;
	}

	this->m_bIsModified = false;
	this->m_pDoc->UpdateAllViews(NULL);


}

int CDlgItemList::getFreeItemNumber(bool isAccessory)
{
	int			itemNum=1;
	POSITION	pos;
	CElement	*pElement=NULL;
	CItem		*pItem=NULL;

	// Get the head position for the items
	if(isAccessory)
		pos = m_pDoc->m_tplAccItemList.GetHeadPosition();
	else
		pos = m_pDoc->m_tplItemList.GetHeadPosition();


	while(pos)
	{
		// Get the next item object
		if(isAccessory)
			pItem = m_pDoc->m_tplAccItemList.GetNext(pos);
		else
			pItem = m_pDoc->m_tplItemList.GetNext(pos);

		// Is the item number free?
		if(itemNum != pItem->GetItemID())
			break;
		else
			itemNum++;

	}

	return(itemNum);
}
