// DlgAccessories.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DlgAccessories.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LENGTH 1
#define MARK 2
/////////////////////////////////////////////////////////////////////////////
// CDlgAccessories dialog


CDlgAccessories::CDlgAccessories(COD3Doc *pDoc, CItem *pItem, CAccessoryElement *pElement, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAccessories::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAccessories)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	// Set the member pointers
	m_pDoc = pDoc;
	m_pItem = pItem;
	m_pElement = pElement;
}


void CDlgAccessories::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAccessories)
	DDX_Control(pDX, IDC_ACC_QTY, m_quantity);
	DDX_Control(pDX, IDC_ACC_BUNDLE, m_bundle);
	DDX_Control(pDX, IDC_ACC_COMMENT, m_comment);
	DDX_Control(pDX, IDC_ACC_LEN, m_length);
	DDX_Control(pDX, IDC_ACC_MARK, m_mark);
	DDX_Control(pDX, IDC_ACC_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAccessories, CDialog)
	//{{AFX_MSG_MAP(CDlgAccessories)
	ON_BN_CLICKED(IDC_ACC_PREV, OnAccPrev)
	ON_BN_CLICKED(IDC_ACC_NEXT, OnAccNext)
	ON_BN_CLICKED(IDC_ACC_SAVE, OnAccSave)
	ON_BN_CLICKED(IDC_ACC_NEW, OnAccNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAccessories message handlers


BOOL CDlgAccessories::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// Set the item product name
	m_name.SetWindowText(m_pItem->GetProductName());

	// Get the element position in the list
	m_elementPos = m_pItem->m_tplElementList.Find(m_pElement);

	if(m_pElement)
	{
		// Set the element data in the fields
		setElement(m_pElement);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAccessories::setElement(CAccessoryElement *pAcc)
{
	CElement	*pElement = pAcc;
	CString		sText;

	// Quantity
	sText.Format("%i", pElement->GetQty());
	m_quantity.SetWindowText(sText);

	// Length
	sText.Format("%i", pAcc->GetLength());
	m_length.SetWindowText(sText);

	// Bundle count
	sText.Format("%i", pAcc->GetBundle());
	m_bundle.SetWindowText(sText);

	// Mark
	m_mark.SetWindowText(pAcc->GetMark());

	// Comment
	m_comment.SetWindowText(pAcc->GetComment());
}

void CDlgAccessories::OnAccPrev() 
{
	// TODO: Add your control notification handler code here
	POSITION			store=m_elementPos;
	CAccessoryElement	*pAcc=NULL;

	if(m_pItem->m_tplElementList.GetCount())
	{
		if(!m_elementPos)
		{
			// Set to the head position
			store=m_elementPos = m_pItem->m_tplElementList.GetHeadPosition();
		}

		// Get the accessory element
		m_pItem->m_tplElementList.GetPrev(m_elementPos);

		// First element in the list
		if(!m_elementPos)
		{
			m_elementPos = store;
		}
		
		// Get the accessory object
		pAcc = (CAccessoryElement *) m_pItem->m_tplElementList.GetAt(m_elementPos);
		// Display the element data
		setElement(pAcc);
		// Set the member pointer
		m_pElement = pAcc;
	}
	
}

BOOL CDlgAccessories::OnAccNext() 
{
	// TODO: Add your control notification handler code here
	POSITION			store=m_elementPos;
	CAccessoryElement	*pAcc=NULL;
	bool				bRes=false;

	if(m_pItem->m_tplElementList.GetCount())
	{
		if(!m_elementPos)
		{
			// Set to the head position
			store=m_elementPos = m_pItem->m_tplElementList.GetTailPosition();
		}

		// Get the next position
		m_pItem->m_tplElementList.GetNext(m_elementPos);

		// Last element in the list
		if(!m_elementPos)
		{
			m_elementPos = store;
			// CSet result flag
			bRes=true;
		}
		
		// Get the accessory object
		pAcc = (CAccessoryElement *) m_pItem->m_tplElementList.GetAt(m_elementPos);
		// Display the element data
		setElement(pAcc);
		// Set the member pointer
		m_pElement = pAcc;
	}

	return(bRes);
}


bool CDlgAccessories::dataPresent()
{
	bool	bResult=true;
	CString	sText;

	// Quantity
	if(m_quantity.GetWindowTextLength())
	{
		// Set the quantity member value
		m_quantity.GetWindowText(sText);
		m_iQuantity = atoi(sText);

		// Length
		if(m_length.GetWindowTextLength())
		{
			// Set the length member value
			m_length.GetWindowText(sText);
			m_iLength = atoi(sText);

			// Bundle count
			if(m_bundle.GetWindowTextLength())
			{
				// Set the length member value
				m_bundle.GetWindowText(sText);
				m_iBundle = atoi(sText);

				// Mark
				if(m_mark.GetWindowTextLength())
				{
					m_mark.GetWindowText(m_sMark);
				}
				else
				{
					// No mark added
					AfxMessageBox(IDS_NOMARK, MB_OK|MB_ICONINFORMATION);
					bResult=false;
					m_mark.SetFocus();
				}
			}
			else
			{
				// No bundle added
				AfxMessageBox(IDS_NOBUNDLE, MB_OK|MB_ICONINFORMATION);
				bResult=false;
				m_bundle.SetFocus();
			}
		}
		else
		{
			// No length added
			AfxMessageBox(IDS_NOLENGTH, MB_OK|MB_ICONINFORMATION);
			bResult=false;
			m_length.SetFocus();
		}
	}
	else
	{
		// No quantity added
		AfxMessageBox(IDS_NOQUANTITY, MB_OK|MB_ICONINFORMATION);
		bResult=false;
		m_quantity.SetFocus();
	}

	// Set the comment member value
	m_comment.GetWindowText(m_sComment);


	return(bResult);
}


bool CDlgAccessories::hasChanged(int iType) 
{
	// TODO: Add your control notification handler code here
	bool bResult=false;

#if 0
	if(m_pElement->GetComment() != m_sComment)
		bResult=true;
	else if(m_pElement->GetBundle() != m_iBundle)
		bResult=true;
	else if(m_pElement->GetLength() != m_iLength)
		bResult=true;
	else if(m_pElement->GetQty() != m_iQuantity)
		bResult=true;
#endif

	if(iType==MARK && m_pElement->GetMark() != m_sMark)
		bResult=true;

	if(iType==LENGTH && m_pElement->GetLength() != m_iLength)
		bResult=true;
		
	
	return(bResult);
}


void CDlgAccessories::OnAccSave() 
{
	// TODO: Add your control notification handler code here
	createAccessory();
}

bool CDlgAccessories::createAccessory()
{
	COD3View			*pView=NULL;
	bool				bResult=false, bCreate=true;
	CAccessoryElement	*pNewAcc=NULL;
	CBeamElement		*pBeam=NULL;
	
	// Extract the data
	if(dataPresent())
	{
		// If editing current element
		if(m_pElement)
		{
			// Has the mark changed
			if(hasChanged(MARK))
			{
				// Replace underscore if present
				m_sMark.Replace(_T("_"), _T("#"));

				// If the mark is found but the user cancels
				if(testAccMark(m_sMark))
					return(bResult);
			}

			// Has the length changed
			if(hasChanged(LENGTH))
			{	
				POSITION pos = m_pItem->m_tplElementList.Find(m_pElement);

				if(pos)
				{
					// Delete the object
					delete m_pElement;
					m_pElement=NULL;
					// Clear from pointer list
					m_pItem->m_tplElementList.RemoveAt(pos);
				}
			}
			else
			{
				// Set the accessory data
				CBeamElement *pB = (CBeamElement*)m_pElement;
				m_pElement->SetComment(m_sComment);
				m_pElement->SetBundle(m_iBundle);
				m_pElement->SetLength(m_iLength);
				pB->SetLength(m_iLength);
				m_pElement->SetQty(m_iQuantity);
				m_pElement->SetMark(m_sMark);				

				// Set flag
				bCreate = false;
			}
		}

		// Create a new element
		if(bCreate)
		{
			// Replace underscore if present
			m_sMark.Replace(_T("_"), _T("#"));

			// If the mark is found but the user cancels
			if(testAccMark(m_sMark))
				return(bResult);
			
			// Create the new accessory element
			pNewAcc = new CAccessoryElement;
			// Cast pointer
			pBeam = (CBeamElement*)pNewAcc;

			// Set the accessory data
			pNewAcc->SetComment(m_sComment);
			pNewAcc->SetBundle(m_iBundle);
			pNewAcc->SetLength(m_iLength);
			pBeam->SetLength(m_iLength);
			pNewAcc->SetQty(m_iQuantity);			
			pNewAcc->SetMark(m_sMark);			
			
			// Set the item pointer
			pNewAcc->m_pItem = m_pItem;

			// Set the member element pointer
			m_pElement = pNewAcc;
		}

		// Set the view pointer
		if(m_bTree)
		{
			CLeftView *pLeftView = (CLeftView *)m_pView;
			CWnd *pWnd = pLeftView->GetNextWindow(GW_HWNDNEXT);

			pView = (COD3View *)pWnd;
		}
		else
		{
			pView = (COD3View *)m_pView;
		}

		if(bCreate)
		{
			// Add Accessory to the list and sort the accessory list
			m_pItem->CreateOrderedBeamList(pBeam);

			// Set the member position pointer
			m_elementPos = m_pItem->m_tplElementList.Find(pNewAcc);
		}

		// Redraw the screens
		pView->RedrawListControls();

		// Set the document to modified
		m_pDoc->SetModifiedFlag(true);
		m_pDoc->SetTitle(m_pDoc->GetTitle());

		if(OnAccNext())
		{
			// Clear the text
			cleanEdits();
		}
	}
	
	return(bResult);
}

void CDlgAccessories::cleanEdits()
{
	// Empty any text in the editboxes
	m_quantity.SetWindowText(_T(""));
	m_length.SetWindowText(_T(""));
	m_bundle.SetWindowText(_T(""));
	m_mark.SetWindowText(_T(""));
	m_comment.SetWindowText(_T(""));

	// Clean the pointer
	m_pElement = NULL;

	// Set focus to quantity field
	m_quantity.SetFocus();

}

void CDlgAccessories::OnAccNew() 
{
	// TODO: Add your control notification handler code here
	cleanEdits();
}

bool CDlgAccessories::testAccMark(CString sMark)
{
	CAccessoryElement	*pAcc=NULL;
	CString				newMark;
	int					iOffset=1;
	bool				bResult=false;

	// Test if the mark is present
	if(m_pItem->getAccessory(sMark))
	{
		// Inform the user the mark is present and ask if amend or ignore
		if(AfxMessageBox(IDS_ACC_MARK_EXIST, MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			// Create the new mark number
			newMark.Format("%s#%i", sMark, iOffset++);

			// Modify mark name
			while(m_pItem->getAccessory(newMark))
			{
				// Create the new mark number
				newMark.Format("%s#%i", sMark, iOffset++);
			}

			// Set the new mark value
			m_sMark = newMark;	
		}
		else
		{
			// Set result flag
			bResult=true;
		}
	}

	return(bResult);
}
