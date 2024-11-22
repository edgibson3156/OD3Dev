// CeeSectFail.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "OD3Doc.h"
#include "CeeSectFail.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCeeSectFail dialog


CCeeSectFail::CCeeSectFail(CWnd* pParent /*=NULL*/)
	: CDialog(CCeeSectFail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCeeSectFail)
	//}}AFX_DATA_INIT
}


void CCeeSectFail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCeeSectFail)
	DDX_Control(pDX, IDC_LIST_FAULTS, m_faultText);
	DDX_Control(pDX, IDC_DEL_ITEM, m_delCheck);
	DDX_Control(pDX, IDC_FAILLIST, m_fList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCeeSectFail, CDialog)
	//{{AFX_MSG_MAP(CCeeSectFail)
	ON_NOTIFY(NM_DBLCLK, IDC_FAILLIST, OnDblclkFaillist)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CLICK, IDC_FAILLIST, OnClickFaillist)
	ON_NOTIFY(NM_KILLFOCUS, IDC_FAILLIST, OnKillfocusFaillist)
	ON_BN_CLICKED(IDC_DEL_ITEM, OnDelItem)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCeeSectFail message handlers
BOOL CCeeSectFail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect	rect;

	m_fList.GetClientRect(&rect);

	// Add headers to list control
	m_fList.InsertColumn(1, "Item Number", LVCFMT_LEFT, rect.Width()/4,-1);
	m_fList.InsertColumn(2, "Mark Number", LVCFMT_LEFT,rect.Width()/4,-1);
	// Warning
	m_fList.InsertColumn(3, "Punch", LVCFMT_LEFT, rect.Width()/4,-1);
	m_fList.InsertColumn(4, "Comment", LVCFMT_LEFT,(rect.Width()/4)+3,-1);

	// Selection index for painting
	m_index=-1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCeeSectFail::OnOK() 
{	
	// Clear list
	m_fList.DeleteAllItems();

	cleanMemory();

	CDialog::OnOK();
}

void CCeeSectFail::OnDblclkFaillist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CItem			*pItem;// = this->m_pItem;
	CBeamElement	*pBeam=NULL;
	int				index, delIndex;
	CString			sText, sMark;
	POSITION		pos;
	bool			notFound=true;
	CPoint			point;


	// Get the cursor pos
	GetCursorPos(&point);

	// Convert to object coordinates
	m_fList.ScreenToClient(&point);
	// Perform hit test
	index = m_fList.HitTest(point, NULL);

	// No item found
	if(index==-1)
	{
		// Set cursor pos to emulate psuedo double click on item
		point.x = 2;
		index = m_fList.HitTest(point, NULL);
	}

	// Get the item number
	if(index>-1)
	{
		// Get the mark number
		sMark = m_fList.GetItemText(index, 1);
		// Store list index
		delIndex = index;
		// Get the item number
		index=atoi(m_fList.GetItemText(index, 0));
		// Get the head pos of the list
		pos=m_pActiveDoc->m_tplItemList.GetHeadPosition();

		// Loop until found
		while(notFound)
		{
			pItem=m_pActiveDoc->m_tplItemList.GetAt(pos);
			if(pItem->GetItemID() == index)
			{
				notFound=false;
				// Get first element object
				pBeam=(CBeamElement *)pItem->m_tplElementList.GetHead();

				// Test document pointer
				ASSERT_VALID(m_pActiveDoc);

				// Create or ammend manual input dialog
				if (m_pActiveDoc->m_pBeamModeless != NULL)
				{
					m_pActiveDoc->m_pBeamModeless->DestroyWindow();
					m_pActiveDoc->m_pBeamModeless=NULL;
				}
				// Create manual input dialog
				m_pActiveDoc->CreateBeamDialog(pItem, pBeam, sMark);
			}
			else
			{
				// Move to next element
				m_pActiveDoc->m_tplItemList.GetNext(pos);
			}
		}
		// Remove from list
		if(m_delCheck.GetCheck())
			m_fList.DeleteItem(delIndex);

		// If no items are in the list control close the dialog
		if(m_fList.GetItemCount() == 0)
			ShowWindow(SW_HIDE);
	}


	*pResult = 0;
}

void CCeeSectFail::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	
	if(!bShow)
	{
		m_pActiveDoc=NULL;
		m_index=-1;

		cleanMemory();
	}
	else
	{
		if(setRegistry(false, true))
			m_delCheck.SetCheck(true);
		else
			m_delCheck.SetCheck(false);
	}
	
}

// Added to allow full row selection bar when main item not clicked
void CCeeSectFail::OnClickFaillist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint				point;
	CString				sText, sStr, sMark;
	int					iID, i, iCount=1;
	CCeeItemFaultDes	*pFault=NULL;

	// Get the cursor pos
	GetCursorPos(&point);

	// Convert to object coordinates
	m_fList.ScreenToClient(&point);
	// Perform hit test
	m_index = m_fList.HitTest(point, NULL);

	// No item found
	if(m_index==-1)
	{
		// Set cursor pos to emulate psuedo double click on item
		point.x = 2;
		m_index = m_fList.HitTest(point, NULL);
	}

	if(m_index>-1)
	{
		// Set the state
		m_fList.SetItemState(m_index,LVIS_SELECTED, LVSIL_STATE);

		// Get selected id number
		iID = atoi(m_fList.GetItemText(m_index, 0));
		sMark = m_fList.GetItemText(m_index, 1);

		// Format error string
		if((pFault = getErrorDesPtr(iID)))
		{
			for(i=0; i<pFault->m_ErrorText.GetSize(); i++)
			{
				if(!sMark.Compare(pFault->m_markText.GetAt(i)))
				{
					sStr.Format("%i) %s \r\n", iCount, pFault->m_ErrorText.GetAt(i));
					sText += sStr;
					iCount++;
				}
			}

			// Display error help
			m_faultText.SetWindowText(sText);
		}
	}
	else
	{
		// Clear
		m_faultText.SetWindowText("");
	}
	
	*pResult = 0;
}

LRESULT CCeeSectFail::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
		case WM_ACTIVATE:
			m_fList.SetFocus();
			break;
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CCeeSectFail::OnKillfocusFaillist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	// Remove selected item
	if(m_index>-1)
		m_fList.SetItemState(m_index,~LVIS_SELECTED, LVSIL_STATE);

	*pResult = 0;
}

void CCeeSectFail::OnDelItem() 
{
	// TODO: Add your control notification handler code here
	setRegistry(m_delCheck.GetCheck(), false);

	return;
}

int CCeeSectFail::setRegistry(int check, bool read)
{
	CMainFrame	*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	CRegKey		regKey;
	DWORD		dwVal=0;


	// Open the key
	if(regKey.Open(HKEY_CURRENT_USER, pMainFrm->m_regPath+"\\Cee", 
						KEY_ALL_ACCESS) != ERROR_SUCCESS)
	{
		
		
		// Create new key
		regKey.Create(HKEY_CURRENT_USER, pMainFrm->m_regPath+"\\Cee", 
								NULL, REG_OPTION_NON_VOLATILE);
	}

	// Set flag
	if(read)
		regKey.QueryValue(dwVal, "Remove");
	else
		regKey.SetValue(check, "Remove");
	

	// Close registry key
	regKey.Close();

	return(dwVal);
}

void CCeeSectFail::OnDestroy() 
{
	CDialog::OnDestroy();
	
	cleanMemory();
	
}


CCeeItemFaultDes* CCeeSectFail::getErrorDesPtr(int iID)
{
	CCeeItemFaultDes	*pResult=NULL;
	POSITION			pos = m_tplErrors.GetHeadPosition();

	while(pos)
	{
		// Get object
		pResult = m_tplErrors.GetNext(pos);

		// Test item number
		if(pResult->m_iItemID == iID)
			return pResult;
	}

	return(pResult);
}

void CCeeSectFail::cleanMemory()
{
	POSITION pos = m_tplErrors.GetHeadPosition();

	while(pos)
		delete m_tplErrors.GetNext(pos);

	m_tplErrors.RemoveAll();

	m_faultText.SetWindowText(_T(""));
}
