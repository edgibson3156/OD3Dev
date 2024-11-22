// BeamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "BeamDlg.h"
#include "OD3Doc.h"
#include "Element.h"
#include "Item.h"
#include "od3gridctrl.h"
#include "BeamOps.h"
#include "ValidationMask.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DIM				1
#define PUNCH			2

/////////////////////////////////////////////////////////////////////////////
// CBeamDlg dialog


CBeamDlg::CBeamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBeamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBeamDlg)
	m_editProfile = _T("");
	m_editSPC = _T("");
	m_editBundleCount = 0;
	m_editEBSlope = 0;
	m_editLength = 0;
	m_editMarkNo = _T("");
	m_editOHang1 = 0;
	m_editOHang2 = 0;
	m_editQty = 0;
	m_editSpan1 = 0;
	m_editSpan2 = 0;
	m_editSpan3 = 0;
	m_sItemLabel = _T("");
	m_sBeamLabel = _T("");
	//}}AFX_DATA_INIT

	m_pParent = pParent;		//	pointer to parent window (NULL !!).
	m_nID = CBeamDlg::IDD;		//  identifier used in OnDestroy() for modeless dlg. 
	m_nMemberType = 0;			//	initialisation value only - change by selection

}


void CBeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBeamDlg)
	DDX_Control(pDX, IDC_ASFSERVICE, m_serviceHoles);
	DDX_Control(pDX, IDC_RADIO_MTYPE1, m_type1);
	DDX_Control(pDX, IDC_RADIO_MTYPE2, m_type2);
	DDX_Control(pDX, IDC_EDIT_SPAN3, m_ctrlSpan3);
	DDX_Control(pDX, IDC_EDIT_SPAN2, m_ctrlSpan2);
	DDX_Control(pDX, IDC_EDIT_SPAN1, m_ctrlSpan1);
	DDX_Control(pDX, IDC_EDIT_QTY, m_ctrlQty);
	DDX_Control(pDX, IDC_EDIT_OHANG2, m_ctrlOHang2);
	DDX_Control(pDX, IDC_EDIT_OHANG1, m_ctrlOHang1);
	DDX_Control(pDX, IDC_EDIT_LENGTH, m_ctrlLength);
	DDX_Control(pDX, IDC_EDIT_MARK, m_ctrlMark);
	DDX_Control(pDX, IDC_COMBO_SPC, m_comboSPC);
	DDX_Control(pDX, IDC_COMBO_PROFILE, m_comboProfile);
	DDX_CBString(pDX, IDC_COMBO_PROFILE, m_editProfile);
	DDV_MaxChars(pDX, m_editProfile, 20);
	DDX_CBString(pDX, IDC_COMBO_SPC, m_editSPC);
	DDV_MaxChars(pDX, m_editSPC, 10);
	DDX_Text(pDX, IDC_EDIT_BDL_COUNT, m_editBundleCount);
	DDV_MinMaxInt(pDX, m_editBundleCount, 0, 50);
	DDX_Text(pDX, IDC_EB_SLOPE, m_editEBSlope);
	DDV_MinMaxInt(pDX, m_editEBSlope, 0, 25);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_editLength);
	DDV_MinMaxInt(pDX, m_editLength, 0, 15900);
	DDX_Text(pDX, IDC_EDIT_MARK, m_editMarkNo);
	DDV_MaxChars(pDX, m_editMarkNo, 8);
	DDX_Text(pDX, IDC_EDIT_OHANG1, m_editOHang1);
	DDV_MinMaxInt(pDX, m_editOHang1, 0, 12000);
	DDX_Text(pDX, IDC_EDIT_OHANG2, m_editOHang2);
	DDV_MinMaxInt(pDX, m_editOHang2, 0, 12000);
	DDX_Text(pDX, IDC_EDIT_QTY, m_editQty);
	DDV_MinMaxInt(pDX, m_editQty, 0, 999);
	DDX_Text(pDX, IDC_EDIT_SPAN1, m_editSpan1);
	DDV_MinMaxInt(pDX, m_editSpan1, 0, 12000);
	DDX_Text(pDX, IDC_EDIT_SPAN2, m_editSpan2);
	DDV_MinMaxInt(pDX, m_editSpan2, 0, 12000);
	DDX_Text(pDX, IDC_EDIT_SPAN3, m_editSpan3);
	DDV_MinMaxInt(pDX, m_editSpan3, 0, 12000);
	DDX_Text(pDX, IDC_ITEM_LABEL, m_sItemLabel);
	DDX_Text(pDX, IDC_BEAM_REF, m_sBeamLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBeamDlg, CDialog)
	//{{AFX_MSG_MAP(CBeamDlg)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnSaveButton)
	ON_BN_CLICKED(IDC_PREVIOUS__BUTTON, OnPreviousButton)
	ON_BN_CLICKED(IDC_NEXT_BUTTON, OnNextButton)
	ON_BN_CLICKED(IDC_RADIO_MTYPE1, OnRadioMtype1)
	ON_BN_CLICKED(IDC_RADIO_MTYPE2, OnRadioMtype2)
	ON_BN_CLICKED(IDC_ADDITEM_BUTTON, OnAdditemButton)
	ON_BN_CLICKED(IDC_ADD_EXTRA_BEAM, OnAddExtraBeam)
	ON_CBN_EDITCHANGE(IDC_COMBO_PROFILE, OnChangeData)
	ON_BN_CLICKED(IDC_DELETE_BEAM, OnDeleteBeam)
	ON_CBN_EDITCHANGE(IDC_COMBO_SPC, OnChangeData)
	ON_EN_CHANGE(IDC_EB_SLOPE, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_BDL_COUNT, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_LENGTH, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_MARK, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_OHANG1, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_OHANG2, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_QTY, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_SPAN1, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_SPAN2, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_SPAN3, OnChangeData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeamDlg message handlers
/////////////////////////////////////////////////////////////////////////////
BOOL CBeamDlg::Create() 
{
	return CDialog::Create(m_nID, m_pParent);
}

/////////////////////////////////////////////////////////////////////////////
void CBeamDlg::OnCancel() 
{
	if (this->m_bIsModified != false)		// we've got some unsaved modified data
	{
		if(!PromptToSave()){return;}		// user cancelled the operation
	}
	if (this->m_editMarkNo == _T(""))		// we've got an unmodified blank input record
	{										// just make sure it is before deleting...
		if(m_pBeam && m_pBeam->GetLength() <= 0)		// ... if length < 0 the variable wasn't initialised
		{			
			delete this->m_pBeam;			// destroy the beam object created before dialog was refreshed
		}
	}
	m_pDoc->BoxDone();						// destroy pointer to this dialog;
	DestroyWindow();						// destroy the modeless dialog.
}

/////////////////////////////////////////////////////////////////////////////
void CBeamDlg::PostNcDestroy() 
{
	delete this;
}

/////////////////////////////////////////////////////////////////////////////
//
BOOL CBeamDlg::OnInitDialog() 
{
	CMainFrame		*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	WINDOWPLACEMENT	place;
	HKEY			openKey;
	DWORD			result;
	DWORD			dwType = REG_BINARY; 
	DWORD			dwSize;
	

	// Get default window pos
	GetWindowPlacement(&place);

	// Open or create registry key
	RegCreateKeyEx(HKEY_CURRENT_USER,pMainFrm->m_regPath+"\\manual",0,
					NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
					NULL, &openKey, &result);

	// Load the registry value
	if(result==REG_OPENED_EXISTING_KEY)
	{
		RegQueryValueEx(openKey,"POS",0, &dwType, (BYTE *)&place, &dwSize);
	}

	// Set new window pos
	SetWindowPlacement(&place);
		




	// Release registry key
	RegCloseKey(openKey);


	m_pDB = m_pDoc->GetProjectSettings()->m_pDB;
	m_sBeamLabel = BeamLabel(m_cBeamCounter);


// Get combobox controls
	CComboBox* pProfileCombo;
	CComboBox* pSPCCombo;

	pProfileCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_PROFILE);
	pSPCCombo = (CComboBox*)this->GetDlgItem(IDC_COMBO_SPC);

// Check DB is open
	if (m_pDB != 0)
	{
		// Initialise the Profile combo box
		m_pProduct = new CProfileList(m_pDB);

		//	Set 'filter' parameter
		CString szFilter = this->m_pItem->GetProductCode();
		m_pProduct->m_Customer_Filter = szFilter.Left(3);

		// Open recordset
		m_pProduct->Open();

		// Empty combo box
		pProfileCombo->ResetContent();

		// Insert recordset data
		while (!m_pProduct->IsEOF())
		{
			pProfileCombo->AddString(m_pProduct->m_ProductName.GetBuffer(1));
			
			m_pProduct->MoveNext();
		}

		// Close recordset and release memory
		m_pProduct->Close();	
		delete(m_pProduct);	

		// Initialise the SPC combo box
		m_pSPC = new CPartCodes(m_pDB);
		m_pSPC->Open();
		while (!m_pSPC->IsEOF())
		{
			pSPCCombo->AddString(m_pSPC->m_PartCodeID);
			m_pSPC->MoveNext();
		}
		// Close recordset and release memory
		m_pSPC->Close();
		delete (m_pSPC);
	
	}
	
	if(this->m_cBeamCounter%1000 <= this->m_pItem->m_tplElementList.GetCount())
//	if(!this->m_pItem->m_tplElementList.IsEmpty())
	{
		this->OnRefreshBeam();
	}
	else
	{
		this->OnNewBeam();	
	}
	
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
//
BOOL CBeamDlg::OnInitGridCtrl() 
{
	// get pointer to grid
	COD3GridCtrl* pGrid = (COD3GridCtrl*)this->GetDlgItem(IDC_EXTRA_HOLE_GRID);
	pGrid->RefreshGrid();

	// populate grid with existing data
	POSITION pos;
	CBeamOps* pOperation;
	CString	sOpType = _T("");		//	type of operation (Generic|Dimension|Punch)
	CString	sOperation = _T("");		//	operation text as specified in OD3 database operation scripts or by user input
	CString	sComment = _T("");		//	comment attached to an additional hole in 'd3' beam
	bool	bAbsolute;		//	absolute|relative dimension indicator
	bool	bPositive;		//	positive|negative dimension indicator
	bool	bMultiplied;	//	multiply(true)|divide(false) dimension modification indicator
	int		nMultiplier;	//	value used a dimension modifier base on value of m_Multiplied

	CItem	*pItem = (CItem*)m_pBeam->m_pItem;
	CString	 sPosX = _T("");
	CString	 sPunch = _T("");
	CString	 sPunchGroup = _T("");
	int		 nOpType;
	LPSTR    lpszPosX;
	LPSTR    lpszPunch;

	pos = this->m_pBeam->m_tplAddList.GetHeadPosition();

	int nRowNdx = 1;
	int	nColNdx = 1;
	int nSheetNdx = CURRENT_SHEET;
	int nSeqID	= 0;
	while(pos)
	{
		pOperation = this->m_pBeam->m_tplAddList.GetNext(pos);

		sOpType = pOperation->GetOpType();
		if (sOpType == _T("Dim")){nOpType = DIM;} else {nOpType = PUNCH;}

		sOperation = pOperation->GetOperation();
		sComment = pOperation->GetComment();
		bAbsolute = pOperation->GetAbsolute();
		bPositive = pOperation->GetPositive();
		bMultiplied = pOperation->GetMultiplied();
		nMultiplier = pOperation->GetMultiplier();

		switch (nOpType)
		{
		case DIM:
			lpszPosX = sOperation.GetBuffer(1);
			pGrid->SetCellText(nRowNdx, nColNdx, lpszPosX, nSheetNdx);
			pOperation->SetXtraHoleHit(nRowNdx);
			pOperation->SetOpSeqID(++nSeqID);
			++nColNdx;
			break;
		case PUNCH:
			lpszPunch = sOperation.GetBuffer(1);
			pGrid->SetCellText(nRowNdx, nColNdx, lpszPunch, nSheetNdx);
			pOperation->SetXtraHoleHit(nRowNdx);

			if(pItem)
			{
				// Set the comment text if SBE C section only
				if(sComment.GetLength() && pItem->GetProfile().Find("SBEC", 0) == 0)
				{
					pGrid->SetCellText(nRowNdx, 6, sComment.GetBuffer(sComment.GetLength()), nSheetNdx);
				}
			}

			pOperation->SetOpSeqID(++nSeqID);
			++nRowNdx;
			nColNdx = 1;
			break;
		}
	}

	nRowNdx = 1;
	nColNdx = 1;
	int nFlags = 0;
	UINT bScrollToTop = 1;
	UINT bScrollToLeft = 0;
	pGrid->SetCurCell(nRowNdx,nColNdx,nFlags, bScrollToTop, bScrollToLeft);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
//
void CBeamDlg::OnAddExtraBeam() 
{
	int nLastBeam;

	this->m_pBeam = new CBeamElement();
	nLastBeam = m_pDoc->GetElementCount(m_nItemID);
	m_cBeamCounter = (m_nItemID * 1000)+ nLastBeam + 1;
	m_pBeam->m_pItem = m_pItem;
	m_pBeam->m_pDoc = m_pDoc;
	OnNewBeam();
}


/////////////////////////////////////////////////////////////////////////////
void CBeamDlg::OnSaveButton() 
{

	UpdateData(true);

	if (!this->ValidateInput()){return;}

	// now update CElement object with data
	CElement* pElement = (CElement*)m_pBeam;
	pElement->SetElementID(m_cBeamCounter);

	// Remove any underscores present in the mark number
	m_editMarkNo.Replace(_T("_"), _T("#"));
 	pElement->SetMark(m_editMarkNo);
	pElement->SetQty(m_editQty);

	m_pBeam->SetLength(m_editLength);
	m_pBeam->SetBundle(m_editBundleCount);
	m_pBeam->SetEBSlope(m_editEBSlope);
	m_pBeam->SetSPCode(m_editSPC);
	m_pBeam->SetMemberType(m_nMemberType);
	m_pBeam->SetSpan1(m_editSpan1);
	m_pBeam->SetSpan2(m_editSpan2);
	m_pBeam->SetSpan3(m_editSpan3);
	m_pBeam->SetOHang1(m_editOHang1);
	m_pBeam->SetOHang2(m_editOHang2);

	// Test if the section is ASF
	if(m_pItem->GetType() == 9)
	{
		// Use the comment field to store service holes
		if(m_serviceHoles.GetCheck())
			m_pBeam->SetComment("Service Holes");
		else
			m_pBeam->SetComment("No Service Holes");
	}

	m_pBeam->ProcessGridInput(this);
	
	m_pDoc->SetModifiedFlag(true);
	m_pDoc->SetTitle(NULL);
	m_pDoc->UpdateDoc(m_nMemberType);


	// on return from doc refresh display
	if (this->m_cBeamCounter != FALSE)
	{
		this->OnRefreshBeam();			// update to display next beam in list
	}
	else	
	{
		this->OnAddExtraBeam();			// no more beams in list so create a new one
	}
}

/////////////////////////////////////////////////////////////////////////////
void CBeamDlg::OnNewBeam() 
{
	COD3GridCtrl* pGrid = (COD3GridCtrl*)this->GetDlgItem(IDC_EXTRA_HOLE_GRID);
	pGrid->RefreshGrid();

	this->InitialUpdate();
	m_editSPC = _T(" ");
	m_editBundleCount = 0;
	m_editLength = 0;
	m_editMarkNo = _T("");
	m_editOHang1 = 0;
	m_editOHang2 = 0;
	m_editQty = 0;
	m_editSpan1 = 0;
	m_editSpan2 = 0;
	m_editSpan3 = 0;
	m_editEBSlope = 0;
	m_nMemberType = 1;

	if(m_pItem->GetType()==1 || m_pItem->GetType()==7 ||
		m_pItem->GetType()==8 || m_pItem->GetType()==9)
	{
		m_nMemberType = 1;
		m_type1.SetCheck(true);
		m_type2.SetCheck(false);
	}
	else
	{
		m_nMemberType = 2;
		m_type2.SetCheck(true);
		m_type1.SetCheck(false);
	}

	// Test if the section is ASF
	if(m_pItem->GetType() == 9)
	{
		// Show the check box
		m_serviceHoles.ShowWindow(SW_SHOW);
		m_serviceHoles.SetCheck(false);
	}

	UpdateData(false);
	this->OnInitGridCtrl(); 
	m_ctrlMark.SetFocus();
	UpdateData(false);
	this->m_bIsModified = false;
}

/////////////////////////////////////////////////////////////////////////////
void CBeamDlg::OnRefreshBeam() 
{
	COD3GridCtrl* pGrid = (COD3GridCtrl*)this->GetDlgItem(IDC_EXTRA_HOLE_GRID);
	pGrid->RefreshGrid();

	this->InitialUpdate();

	CElement* pElement = (CElement*)m_pBeam;
	this->m_editMarkNo		= pElement->GetMark();
	this->m_editQty			= pElement->GetQty();

	this->m_editLength		= m_pBeam->GetLength();
	this->m_editBundleCount = m_pBeam->GetBundle();
	this->m_editEBSlope		= m_pBeam->GetEBSlope();
	this->m_editSPC			= m_pBeam->GetSPCode();
	this->m_nMemberType		= m_pBeam->GetMemberType();
	this->m_editSpan1		= m_pBeam->GetSpan1();
	this->m_editSpan2		= m_pBeam->GetSpan2();
	this->m_editSpan3		= m_pBeam->GetSpan3();
	this->m_editOHang1		= m_pBeam->GetOHang1();
	this->m_editOHang2		= m_pBeam->GetOHang2();

	// Set the document and item pointers
	if(!pElement->m_pDoc)
		pElement->m_pDoc = m_pDoc;

	if(!pElement->m_pItem)
		pElement->m_pItem = m_pItem;

	// Set the member type
	if(m_nMemberType==1)
	{
		m_type1.SetCheck(true);
		m_type2.SetCheck(false);
	}
	else
	{
		m_type1.SetCheck(false);
		m_type2.SetCheck(true);
	}

	// Test if the section is ASF
	if(m_pItem->GetType() == 9)
	{
		// Show the check box
		m_serviceHoles.ShowWindow(SW_SHOW);
	
		// Use the comment field to store service holes
		if(!m_pBeam->GetComment().Compare(_T("Service Holes")))
			m_serviceHoles.SetCheck(true);
		else if(!m_pBeam->GetComment().Compare(_T("No Service Holes")))
			m_serviceHoles.SetCheck(false);
		else
			m_serviceHoles.SetCheck(false);

	}
	else
	{
		// Hide the check box
		m_serviceHoles.ShowWindow(SW_HIDE);
	}

//////////////////////////////////////////////////

/*	this->m_pBeam->GetBeam(this,
							m_cBeamCounter,
							m_editQty,
							m_editMarkNo,
							m_editSPC,
							m_sComment,
							m_editBundleCount,
							m_editLength,
							m_editSpan1,
							m_editSpan2,
							m_editSpan3,
							m_editOHang1,
							m_editOHang2,
							m_editEBSlope,
							m_nMemberType);
*/
	if (m_editMarkNo != _T(""))
	{
		m_sBeamLabel = BeamLabel(m_cBeamCounter);
		UpdateData(false);
		this->OnInitGridCtrl(); 
		this->m_ctrlMark.SetFocus();
		UpdateData(false);
		this->m_bIsModified = false;
	}
	else
	{
		OnNewBeam();
	}
}


/////////////////////////////////////////////////////////////////////////////
//
void CBeamDlg::OnPreviousButton() 
{
	if(this->m_bIsModified != false)
	{
		if(!this->PromptToSave()){return;}
	}
	else if (this->m_editMarkNo == _T(""))		// we've got an unmodified blank dialog
	{
		delete this->m_pBeam;				// so delete the new object created before dialog refreshed.
	}
	m_pDoc->OnPreviousBeam(m_pDlg);	
	this->OnRefreshBeam();
}

/////////////////////////////////////////////////////////////////////////////
void CBeamDlg::OnNextButton() 
{
	if(	m_editMarkNo != _T(""))	// we are not already at the last record
	{
		if(this->m_bIsModified != false)
		{
			if(!this->PromptToSave()){return;}
		}
		else
		{
			m_pDoc->OnNextBeam(m_pDlg);	
			this->OnRefreshBeam();
		}
	}
	else
	{
		AfxMessageBox("No more records to display for this Item");
	}
}

/////////////////////////////////////////////////////////////////////////////
void CBeamDlg::OnAdditemButton() 
{
	if(	m_editMarkNo != _T(""))	// we're not already at an empty record
	{
		if(this->m_bIsModified != false)
		{
			if(!this->PromptToSave()){return;}
		}
	}
	else						// we are at an unmodified empty record
	{
		delete this->m_pBeam;
	}
	m_pDoc->OnNextItem();
	this->m_ctrlMark.SetFocus();
	UpdateData(false);
}

/////////////////////////////////////////////////////////////////////////////
//
void CBeamDlg::OnRadioMtype1() 
{
	m_nMemberType = 1;	
	this->m_bIsModified = true;
}

/////////////////////////////////////////////////////////////////////////////
//
void CBeamDlg::OnRadioMtype2() 
{
	m_nMemberType = 2;
	this->m_bIsModified = true;
}

/////////////////////////////////////////////////////////////
//
void CBeamDlg::OnChangeData() 
{
	this->m_bIsModified = true;
}

///////////////////////////////////////////////////////////////////////
// CBeamDialog commands
/////////////////////////////////////////////////////////////////////////////
//  InitialUpdate()	create labels and populate 'constant' item variables
//
void CBeamDlg::InitialUpdate()
{
	this->m_nItemID = m_pItem->GetItemID();
	this->m_sItemLabel = this->ItemLabel(m_pItem);
	this->m_sBeamLabel = BeamLabel(m_cBeamCounter);
	this->m_nMemberType = this->m_pBeam->GetMemberType();

	this->m_editProfile = this->m_pItem->GetProfile();
	UpdateData(false);
	this->m_bIsModified = false;

}

/////////////////////////////////////////////////////////////
// BeamLabel() A function to format the beam counter and convert
// to CString for display manual input dialog.
//
CString CBeamDlg::BeamLabel(int nItem)
{
	CString Label = _T("");
	CString sBeam = _T("");

	sBeam.Format("%d", nItem);
	Label = _T("[ Beam Ref: ") + sBeam + _T(" ]");
	return Label;
}

/////////////////////////////////////////////////////////////
// ItemLabel() A function to concatenate the project name and item number for display
// in manual input dialog.
//
CString CBeamDlg::ItemLabel(CItem* pItem)
{
	CString sJobName = _T("");
	CString sProduct = _T("");
	CString sLabel = _T("");
	CString sItem = _T("");

	sJobName = this->m_pDoc->m_pProjectHeader->m_sProjectName;
	sProduct = pItem->GetProductName();

	int nItem = pItem->GetItemID();
	sItem.Format("%d", nItem);
	
	sLabel = _T("[ Job No.");
	sLabel += sJobName;
	sLabel += _T(": Item No. ");
	sLabel += sItem;
	sLabel += _T(" - ");
	sLabel += sProduct;
	sLabel += _T(" ]");

	return sLabel;
}
/////////////////////////////////////////////////////////////////////////////
//
bool CBeamDlg::PromptToSave()
{
	int nResponse;

	nResponse = AfxMessageBox("Save current beam ?",MB_ICONQUESTION|MB_YESNOCANCEL);

	switch(nResponse)
	{
	case IDYES:
		this->OnSaveButton();
		return true;
	case IDNO:					// a new beam object was created before dialog refreshed
		delete this->m_pBeam;	// so delete it if user doesn't want it 
		this->m_pBeam=NULL;
		return true;
	default:	/*IDCANCEL*/
		return false;
	}

}

/////////////////////////////////////////////////////////////////////////////////
// ValidateInput()	Initial validation to make sure we've got the data we need
//
bool CBeamDlg::ValidateInput()
{
	CString csMsg = _T("");
	POSITION posItem;
	POSITION posBeam;
	CItem* pItem;
	CElement* pElement;

	posItem = this->m_pDoc->m_tplItemList.GetHeadPosition();
	while (posItem)
	{
		pItem = this->m_pDoc->m_tplItemList.GetNext(posItem);
		posBeam = pItem->m_tplElementList.GetHeadPosition();
		while (posBeam)
		{
			pElement = pItem->m_tplElementList.GetNext(posBeam);
			if(pElement->GetMark() == this->m_editMarkNo && pElement != (CElement*)this->m_pBeam)
			{
				csMsg = _T("Mark ");
				csMsg += this->m_editMarkNo;
				csMsg += _T(" has already been used in Item ");
				CString sItemID;
				int nItemID = pItem->GetItemID();
				sItemID.Format("%d",nItemID);
				csMsg += sItemID;

				AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
				this->m_ctrlMark.SetFocus();
				UpdateData(false);
				return false;
			}
		}
	}

	
	if (this->m_editMarkNo == _T(""))
	{
		csMsg = _T("Cannot save record without a mark no.");
		AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
		this->m_ctrlMark.SetFocus();
		UpdateData(false);
		return false;
	}
	else if (this->m_editQty <= 0)
	{
		csMsg = _T("Cannot save record with a zero quantity.");
		AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
		this->m_ctrlQty.SetFocus();
		UpdateData(false);
		return false;
	}
	else if (this->m_editLength <= 0)
	{
		csMsg  = _T("Cannot save record with a zero length.");
		AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
		this->m_ctrlLength.SetFocus();
		UpdateData(false);
		return false;
	}
	else if (this->m_editSPC == _T(""))
	{
		csMsg  = _T("Cannot save record without an SPC.");
		AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
		this->m_comboSPC.SetFocus();
		UpdateData(false);
		return false;
	}
	// not done yet - examine supplied SPC code and make sure we have the relevant data
	else 
	{
		if(this->GetMask())
		{
			if(this->m_bOhang1 != false && this->m_editOHang1 == 0)
			{
				csMsg  = _T("This SPC requires an Overhang Dimension.");
				AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
				this->m_ctrlOHang1.SetFocus();
				UpdateData(false);
				return false;
			}
			else if (this->m_bOhang2 != false && this->m_editOHang2 == 0)
			{
				csMsg  = _T("This SPC requires a 2nd Overhang Dimension.");
				AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
				this->m_ctrlOHang2.SetFocus();
				UpdateData(false);
				return false;
			}
			else if (this->m_bSpan1 != false && this->m_editSpan1 ==0)
			{
				csMsg  = _T("This SPC requires an entry for Span 1.");
				AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
				this->m_ctrlSpan1.SetFocus();
				UpdateData(false);
				return false;
			}
			else if (this->m_bSpan2 != false && this->m_editSpan2 ==0)
			{
				csMsg  = _T("This SPC requires an entry for Span 2.");
				AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
				this->m_ctrlSpan2.SetFocus();
				UpdateData(false);
				return false;
			}
			else if (this->m_bSpan3 != false && this->m_editSpan3 ==0)
			{
				csMsg  = _T("This SPC requires an entry for Span 3.");
				AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);
				this->m_ctrlSpan3.SetFocus();
				UpdateData(false);
				return false;
			}
		}
		else		// GetMask() returned false
		{
			csMsg  = _T("There's a problem with the data source connection"); 
			csMsg += _T("/n/nClose this dialog without saving this record,");
			csMsg += _T("/nthen save your work to disk and close the file");
			csMsg += _T("/n/nReopen the file and make sure you are connected to the correct datasource");
			AfxMessageBox(csMsg, MB_ICONSTOP|MB_OK);
			return false;
		}
		// now check consistency of data
		int nCalcLength;
		switch (m_SpanSummingMask)
		{
		case 1:
			nCalcLength = this->m_editSpan1;
			if (m_bOhang1)
			{
				nCalcLength += this->m_editOHang1;
			}
			if (m_bOhang2)
			{
				nCalcLength += this->m_editOHang2;
			}
//			Need a futher validation step here to check that the overlength of an overlap purlin
//			matches the input span.
			nCalcLength += this->m_lAdjustmentDim;
			break;
		case 2:
			nCalcLength = this->m_editSpan2;
			if (m_bOhang1)
			{
				nCalcLength += this->m_editOHang1;
			}
			if (m_bOhang2)
			{
				nCalcLength += this->m_editOHang2;
			}
//			Need a futher validation step here to check that the overlength of an overlap purlin
//			matches the input span.
			nCalcLength += this->m_lAdjustmentDim;
			break;
		case 3:
			nCalcLength = (this->m_editSpan1) + (this->m_editSpan2); 
			if (m_bOhang1)
			{
				nCalcLength += this->m_editOHang1;
			}
			if (m_bOhang2)
			{
				nCalcLength += this->m_editOHang2;
			}
			nCalcLength += this->m_lAdjustmentDim;
			break;
		default:
			break;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetMask()	A function to create a new dynaset from the ValidationMaskbySPC Query in the OD3 Database
//
bool CBeamDlg::GetMask()
{
	m_pDB = m_pDoc->GetProjectSettings()->m_pDB;
	
	// Check DB is open
	if (m_pDB != 0)
	{
		CValidationMask* pRequiredData = new CValidationMask(m_pDB);

		pRequiredData->m_SPC_Ident = this->m_editSPC;

		pRequiredData->Open();
		this->m_lValidation_ID = pRequiredData->m_Validation_ID;
		this->m_bOhang1 = pRequiredData->m_Ohang1;
		this->m_bOhang2 = pRequiredData->m_Ohang2;
		this->m_bSpan1 = pRequiredData->m_Span1;
		this->m_bSpan2 = pRequiredData->m_Span2;
		this->m_bSpan3 = pRequiredData->m_Span3;
		this->m_lAdjustmentDim = pRequiredData->m_AdjustmentDim;
		this->m_SpanSummingMask = pRequiredData->m_SpanSummingMask;

		// Close recordset and release memory
		pRequiredData->Close();
		delete pRequiredData;
		return true;
	}
	AfxMessageBox(_T("Data Source not connected"));
	// VHF TODO: is it legal to simply re-establish the connection or are there other implications if we end up here?
	// can't do it anyway - OnOpenSysConfig is protected
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
//	OnDeleteBeam()
//
void CBeamDlg::OnDeleteBeam() 
{
	bool bFirstBeam;
	bool bLastBeam;

	// TODO: Add your control notification handler code here
	if (this->m_cBeamCounter % 1000 > 1)
	{
		bFirstBeam = false;
	}
	else
	{
		bFirstBeam = true;
	}
	if (this->m_cBeamCounter % 1000 == m_pItem->m_tplElementList.GetCount())
	{
		bLastBeam = true;
	}
	else
	{
		bLastBeam = false;
	}

	CString  szMsg = _T("");
	CString  szMark = _T("");
	
	szMark = m_pBeam->GetMark();
	szMsg  = _T("Are you sure you want to delete ");
	szMsg += szMark;
	szMsg += _T(" ?");

	
	AfxMessageBox(szMsg,MB_YESNO + MB_ICONQUESTION);
	if(IDYES)
	{
		this->m_pItem->DeleteBeam(m_pBeam);
	
		if (bLastBeam == false)
		{
			--m_cBeamCounter;
			this->OnNextButton();
		}
		else if (bFirstBeam == false)
		{
			this->OnPreviousButton();
		}
		else 
		{
			this->OnCancel();
		}
	}
	else
	{
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////// Trap incoming messages and deal with them before dialog takes control ///////
//
BOOL CBeamDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		COD3GridCtrl* pGrid = (COD3GridCtrl*)this->GetDlgItem(IDC_EXTRA_HOLE_GRID);

		// If the key pressed is enter convert to a tab key press if focus is with the grid
		if(pMsg->wParam == VK_RETURN && GetFocus() == pGrid)
		{
			pMsg->wParam = VK_TAB;
		}
	}
	if(pMsg->message == WM_KEYUP)
	{
		COD3GridCtrl* pGrid = (COD3GridCtrl*)this->GetDlgItem(IDC_EXTRA_HOLE_GRID);

		// If the key pressed is enter convert to a tab key press if focus is with the grid
		if(pMsg->wParam == VK_RETURN && GetFocus() == pGrid)
		{
			pMsg->wParam = VK_TAB;
		}
	}

	// Allow keypress to continue as normal.
	return CDialog::PreTranslateMessage(pMsg);
}
///////////////////////////////////////////////////////////////////////////////////////////////

BOOL CBeamDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame		*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	WINDOWPLACEMENT	place;
	HKEY			openKey;
	DWORD			result;
	

	// Open or create registry key
	RegCreateKeyEx(HKEY_CURRENT_USER,pMainFrm->m_regPath+"\\manual",0,
					NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
					NULL, &openKey, &result);


	// Get new window pos
	this->GetWindowPlacement(&place);
	// Store values in registry
	RegSetValueEx(openKey,"POS",0,REG_BINARY, 
					(unsigned char *)&place, sizeof(WINDOWPLACEMENT));

	// Release registry key
	RegCloseKey(openKey);


	return CDialog::DestroyWindow();
}
