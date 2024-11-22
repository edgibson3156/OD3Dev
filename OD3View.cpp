// OD3View.cpp : implementation of the COD3View class
//

#include "stdafx.h"
#include "OD3.h"

#include "OD3Doc.h"
#include "OD3View.h"
#include "MainFrm.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COD3View

IMPLEMENT_DYNCREATE(COD3View, CListView)

BEGIN_MESSAGE_MAP(COD3View, CListView)
	//{{AFX_MSG_MAP(COD3View)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_VIEW_LARGEICON, OnViewLargeicon)
	ON_COMMAND(ID_VIEW_SMALLICON, OnViewSmallicon)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALLICON, OnUpdateViewSmallicon)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGEICON, OnUpdateViewLargeicon)
	ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, OnUpdateViewDetails)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ELEMENT_COPY, OnElementCopy)
	ON_COMMAND(ID_ELEMENT_CUT, OnElementCut)
	ON_COMMAND(ID_ELEMENT_DELETE, OnElementDelete)
	ON_COMMAND(ID_ELEMENT_EDIT, OnElementEdit)
	ON_COMMAND(ID_ELEMENT_PASTE, OnElementPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_COMMAND(IDM_SELECTALLITEMS, OnSelectallitems)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_DELETE, OnUpdateElementDelete)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_EDIT, OnUpdateElementEdit)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CUT, OnUpdateElementCut)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_COPY, OnUpdateElementCopy)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_PASTE, OnUpdateElementPaste)
	ON_UPDATE_COMMAND_UI(IDM_PRINTTHISELEMENT, OnUpdatePrintthiselement)
	ON_COMMAND(IDM_PRINTTHISELEMENT, OnPrintthiselement)
	ON_UPDATE_COMMAND_UI(IDM_SELECTALLITEMS, OnUpdateSelectallitems)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COD3View construction/destruction

COD3View::COD3View()
{
//	m_bStateIcons = TRUE;
	m_bFullRowSel = FALSE;
	m_bClientWidthSel = TRUE;
	m_pItem = NULL;	
	m_bCut	= false;	// set to true by COD3View Context menu
	m_bCopy	= false;	// set to true by COD3View Context menu
	m_pImgList = NULL;
}

COD3View::~COD3View()
{
	if(m_pImgList)
		delete m_pImgList;
}

BOOL COD3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= LVS_SHOWSELALWAYS | LVS_REPORT;

	return CListViewEx::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COD3View drawing

void COD3View::OnDraw(CDC* pDC)
{
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
//
//
void COD3View::OnInitialUpdate()
{
	CListViewEx::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().

	// define list control
	this->DefineImageList();
	this->DefineListControl();

}

///////////////////////////////////////////////////////////////////////////////////////////
//
//
void COD3View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (m_pItem)
	{
		this->DisplayElements(m_pItem);
	}
}

/////////////////////////////////////////////////////////////////////////////
// COD3View printing

BOOL COD3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	//DoPreparePrinting(pInfo);
	CLeftView *pView=(CLeftView *)GetNextWindow(GW_HWNDPREV);

	if(pView)
		return(pView->preparePrint(pInfo));
	else
		return(false);

}


void COD3View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CLeftView *pView=(CLeftView *)GetNextWindow(GW_HWNDPREV);
	
	if(pView)
		pView->printGo(pDC, pInfo);

	CListView::OnPrint(pDC, pInfo);
}

////////////////////////////////////////////////////////////////////////////////////
// COD3View controls
////////////////////////////////////////////////////////////////////////////////////
//	DefineListControl()		Define the list coloumn structure and format
//
void COD3View::DefineListControl()
{
//	DWORD dwNewStyle;
//	dwNewStyle	= LVS_REPORT
//				| LVS_EX_FULLROWSELECT
//				& !LVS_EX_GRIDLINES;
	
	LVCOLUMN ColumnAttributes;	// List View attributes structure
	CListCtrl&	m_DisplayListCtrl = GetListCtrl();
	CRect		rect, lRect;
	CLeftView	*pLView = (CLeftView *)GetNextWindow(GW_HWNDPREV);
	int			totSize;
//	m_DisplayListCtrl.SetExtendedStyle(dwNewStyle);

	m_DisplayListCtrl.SetImageList(m_pImgList, TVSIL_NORMAL);

	// Get the size of the drawing area
	GetClientRect(&rect);
	pLView->GetClientRect(&lRect);

	// Define List Control Column Attributes for Column 1
	ColumnAttributes.mask = LVCF_FMT			 // Format member is valid (fmt)
						  | LVCF_SUBITEM		 // SubItem member is valid (iSubItem)
						  | LVCF_TEXT			 // Text member is valid (pszText)
					/*	  | LVCF_IMAGE			 // Image member is valid (iImage)	*/
						  | LVCF_WIDTH;			 // Width member is valid (cx)

	ColumnAttributes.fmt = LVCFMT_LEFT;			 // Left aligned text
	ColumnAttributes.pszText = "Mark No";		 // Title for Column 1
	ColumnAttributes.iSubItem = 0;				 // Main item
//	ColumnAttributes.iImage = 0;				 // Item image
	ColumnAttributes.cx = 100;					 // Column Width

	totSize = ColumnAttributes.cx;
	
	// Insert first column
	m_DisplayListCtrl.InsertColumn(0, &ColumnAttributes);

	// Change necessary attributes for column 2
	ColumnAttributes.pszText = "No.Off";		 // Title for Column 2
	ColumnAttributes.iSubItem = 1;				 // Sub Item
	ColumnAttributes.cx = 50;					 // Column Width
	totSize += ColumnAttributes.cx;

	// Insert second column to right of first column
	m_DisplayListCtrl.InsertColumn(1, &ColumnAttributes);

	// Change necessary attributes for column 3
	ColumnAttributes.pszText = "Length";		 // Title for Column 3
	ColumnAttributes.iSubItem = 2;				 // Sub Item
	ColumnAttributes.cx = 100;					 // Column Width
	totSize += ColumnAttributes.cx;

	// Insert third column to right of second column
	m_DisplayListCtrl.InsertColumn(2, &ColumnAttributes);

	// Change necessary attributes for column 4
	ColumnAttributes.pszText = "SPC";			 // Title for Column 4
	ColumnAttributes.iSubItem = 3;				 // Sub Item
	ColumnAttributes.cx = 50;					 // Column Width
	totSize += ColumnAttributes.cx;

	// Insert fourth column to right of third column
	m_DisplayListCtrl.InsertColumn(3, &ColumnAttributes);

	// Change necessary attributes for column 5
	ColumnAttributes.pszText = "Type";			 // Title for Column 5
	ColumnAttributes.iSubItem = 4;				 // Sub Item
	ColumnAttributes.cx = 50;					 // Column Width
	totSize += ColumnAttributes.cx;

	// Insert fifth column to right of fourth column
	m_DisplayListCtrl.InsertColumn(4, &ColumnAttributes);

	// Change necessary attributes for column 6
	ColumnAttributes.pszText = "Comment";		 // Title for Column 6
	ColumnAttributes.iSubItem = 5;				 // Sub Item
	ColumnAttributes.cx = rect.Width()+lRect.Width()-totSize-2;	 // Column Width (remainder of window)

	// Insert sixth column to right of fifth column
	m_DisplayListCtrl.InsertColumn(5, &ColumnAttributes);
}

/////////////////////////////////////////////////////////////////////////////
// COD3View diagnostics

#ifdef _DEBUG
void COD3View::AssertValid() const
{
	CListViewEx::AssertValid();
}

void COD3View::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}

COD3Doc* COD3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COD3Doc)));
	return (COD3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COD3View helpers

BOOL COD3View::SetViewType(DWORD dwViewType)
{
	return(ModifyStyle(LVS_TYPEMASK,dwViewType & LVS_TYPEMASK));
}

DWORD COD3View::GetViewType()
{
	return(GetStyle() & LVS_TYPEMASK);
}

/////////////////////////////////////////////////////////////////////////////
// COD3View message handlers
void COD3View::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

///////////////////////////////////////////////////////////////////////////////////////////
//	OnRButtonDown()  Message handler function to display context menu
//
void COD3View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menubar;

	// Select item before creating the popup menu
#ifdef RIGHT_BUTTON_CTRL
	CListViewEx::OnRButtonDown(nFlags, point);
#else
	CListViewEx::OnLButtonDown(nFlags, point);
#endif

	// Load menu resource
	if (menubar.LoadMenu(IDR_POPUPMENUS))
	{
		CMenu* pPopup = menubar.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		ClientToScreen(&point); // not used in retail build

		// route commands through mainframe for command ui events
		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y,
			AfxGetApp()->GetMainWnd());
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//	OnDblclk()		Message handler function to open the beam dialog with focus to selected element
//
void COD3View::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	COD3Doc	*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CItem			*pItem = this->m_pItem;
	CBeamElement	*pBeam=NULL;
	int				index=0;
	CListCtrl&		listCtrl = GetListCtrl();
	CPoint			point;

	// Get mouse coords
	GetCursorPos(&point);
	// Convert to object coords
	ScreenToClient(&point);

	// Test for item hit
	if((index = listCtrl.HitTest(point, NULL)) > -1)
	{
		if(this->GetElementPointer(index))
		{
			if(this->m_pItem->IsBeam())
			{
				pBeam = (CBeamElement*)(this->m_pElement);
				int cElementCounter = pBeam->GetElementID();
				if (pDoc->m_pBeamModeless != NULL)
				{
					pDoc->RefreshBeamDialog(pItem, pBeam, cElementCounter);
				}
				else		
				{
					// Dialog not shown, create it
					pDoc->CreateBeamDialog(pItem, pBeam, cElementCounter);
				}

			}
			else
			{
				// Create object and set pointers
				CDlgAccessories dlgAcc(pDoc, m_pItem, (CAccessoryElement *)m_pElement);

				// Set the view pointer
				dlgAcc.m_pView = this;
				dlgAcc.m_bTree = false;

				dlgAcc.DoModal();
			}
		}
	}


	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// COD3View message handlers

void COD3View::OnViewSmallicon()
{
	if (GetViewType() != LVS_SMALLICON)
		SetViewType(LVS_SMALLICON);
}

void COD3View::OnViewLargeicon()
{
	if (GetViewType() != LVS_ICON)
		SetViewType(LVS_ICON);
}

void COD3View::OnViewList()
{
	if (GetViewType() != LVS_LIST)
		SetViewType(LVS_LIST);
}

void COD3View::OnViewDetails()
{
	if ((GetViewType() != LVS_REPORT) || GetFullRowSel())
	{
		SetFullRowSel(TRUE);
		if (GetViewType() != LVS_REPORT)
			SetViewType(LVS_REPORT);
	}
}


void COD3View::OnUpdateViewSmallicon(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetViewType() == LVS_SMALLICON);
}

void COD3View::OnUpdateViewLargeicon(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetViewType() == LVS_ICON);
}

void COD3View::OnUpdateViewList(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetViewType() == LVS_LIST);
}

void COD3View::OnUpdateViewDetails(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((GetViewType() == LVS_REPORT) && !GetFullRowSel());
}


////////////////////////////////////////////////////////////////////////////////////////
//	OnLButtonDown()		message handler - sample code imported from 'rowlist'
//
void COD3View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags = 0;
	int nHitItem = GetListCtrl().HitTest(point, &uFlags);

	CRect rect;
	GetListCtrl().GetItemRect(nHitItem, rect, LVIR_BOUNDS);

	CListViewEx::OnLButtonDown(nFlags, point);
}

////////////////////////////////////////////////////////////////////////////////////////
//
void COD3View::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CListCtrl&	listCtrl = GetListCtrl();

	// Any to copy?
	if(listCtrl.GetSelectedCount())
		this->OnElementCopy();

	return;
}

////////////////////////////////////////////////////////////////////////////////////////
//	OnElementCopy()		Message handler 
//						 
//
void COD3View::OnElementCopy() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int				listCount=0, i;
	CItem			*pItem = this->m_pItem;
	CBeamElement	*pBeam=NULL;
	CListCtrl&		listCtrl = GetListCtrl();


	// Get Selection count
	listCount = listCtrl.GetItemCount();

	// Loop through all selected items
	for(i=0; i<listCount; i++)
	{
		// Test for selected item
		if(listCtrl.GetItemState(i, LVIS_SELECTED))
		{
			if(this->GetElementPointer(i))
			{
				if(this->m_pItem->IsBeam())
				{
					pBeam = (CBeamElement*)(this->m_pElement);
					pItem->m_pDoc = pDoc;
					this->m_bCopy = true;
					pItem->CopyBeam(pBeam, this);
				}
				else
				{
					// Set document pointer
					pItem->m_pDoc = pDoc;
					// Set the copy flag
					m_bCopy = true;
					// Copy the accessory element
					pItem->copyAccessory((CAccessoryElement *)m_pElement);
				}
			}
		}
	}

#ifndef ALLVIEW
		RedrawListControls();		
#else
	// update view
	pDoc->UpdateAllViews( (CView *)this->GetNextWindow(GW_HWNDNEXT), NULL, NULL);
#endif

	return;
}

////////////////////////////////////////////////////////////////////////////////////////
//
void COD3View::OnEditCut() 
{
	// TODO: Add your command handler code here
	CListCtrl&	listCtrl = GetListCtrl();

	// Any to cut?
	if(listCtrl.GetSelectedCount())
		this->OnElementCut();

	return;
}

////////////////////////////////////////////////////////////////////////////////////////
//	OnElementCut()		Message handler 
//						 
//
void COD3View::OnElementCut() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int				listCount=0, i;
	CItem			*pItem = this->m_pItem;
	CBeamElement	*pBeam=NULL;
	CListCtrl&		listCtrl = GetListCtrl();
	bool			update=false;


	// Get Selection count
	listCount = listCtrl.GetItemCount();

	// Loop through all selected items
	for(i=0; i<listCount; i++)
	{
		// Test for selected item
		if(listCtrl.GetItemState(i, LVIS_SELECTED))
		{
			if(GetElementPointer(i))
			{
				// Set flag for updating element IDs
				update=true;
				// Set the document pointer
				pItem->m_pDoc = pDoc;
				// Set the cut flag
				m_bCut = true;
	
				pBeam = (CBeamElement*)(this->m_pElement);
				// Set the item pointer
				pBeam->m_pItem = m_pItem;
				// Cut the beam element
				pItem->CutBeam(pBeam, this);
			}
		}
	}
	
	if(update)
		pItem->ResetBeamCounter();


#ifndef ALLVIEW
	RedrawListControls();		
#else
	// update view
	pDoc->UpdateAllViews( (CView *)this->GetNextWindow(GW_HWNDNEXT), NULL, NULL);
#endif

}

////////////////////////////////////////////////////////////////////////////////////////////
//	OnElementDelete()		message handler
//
void COD3View::OnElementDelete() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int				listCount=0, selCount=0, i;
	CItem			*pItem = this->m_pItem;
	CBeamElement	*pBeam=NULL;
	CListCtrl&		listCtrl = GetListCtrl();
	CString			warn;


	// Any selected
	if(selCount = listCtrl.GetSelectedCount())
	{
		// Count total elements
		listCount = listCtrl.GetItemCount();

		// Load warning message
		if(selCount == 1)
			warn.Format(IDS_DEL_ONE_ELEMENT);	
		else
			warn.Format(IDS_DEL_ELEMENTS, selCount);

		if(AfxMessageBox(warn, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			// Loop through all selected items
			for(i=0; i<listCount; i++)
			{
				// Test for selected item
				if(listCtrl.GetItemState(i, LVIS_SELECTED))
				{
					if(this->GetElementPointer(i))
					{
						if(this->m_pItem->IsBeam())
						{
							pBeam = (CBeamElement*)(this->m_pElement);
							m_pItem->DeleteBeam(pBeam);
						}
						else
						{
							// Delete the accessory item
							m_pItem->deleteAccessoy((CAccessoryElement *)m_pElement);
						}
					}
				}
			}

			// update view
#ifndef ALLVIEW
			RedrawListControls();		
#else
			// Global redraw
			pDoc->UpdateAllViews(NULL,NULL,NULL);
#endif
			// Changes been made to project file
			pDoc->SetModifiedFlag();
			pDoc->SetTitle(NULL);
		}
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////
//	OnElementEdit()		Message handler to open dialog with focus set to selected element 
//						 
//
void COD3View::OnElementEdit() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CItem* pItem = this->m_pItem;
	CBeamElement* pBeam;

	if(this->GetElementPointer())
	{
		if(this->m_pItem->IsBeam())
		{
			pBeam = (CBeamElement*)(this->m_pElement);
			int cElementCounter = pBeam->GetElementID();
			if (pDoc->m_pBeamModeless != NULL)
			{
				pDoc->RefreshBeamDialog(pItem, pBeam, cElementCounter);
			}
			else		// dialog not up - so create it 'new'
			{
				pDoc->CreateBeamDialog(pItem, pBeam, cElementCounter);
			}

		}
		else
		{
			// Create object ans set pointers
			CDlgAccessories dlgAcc(pDoc, m_pItem, (CAccessoryElement *)m_pElement);

			// Set the view pointer
			dlgAcc.m_pView = this;
			dlgAcc.m_bTree = false;

			dlgAcc.DoModal();
		}
	}
	else
	{
		return;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//
void COD3View::OnEditPaste() 
{
	// TODO: Add your command handler code here
	COD3Doc	*pDoc = GetDocument();

	// Test for paste buffer
	if(!pDoc->m_tplCutList.IsEmpty() || !pDoc->m_tplCopyList.IsEmpty())
		this->OnElementPaste();	

	return;
}

////////////////////////////////////////////////////////////////////////////////////////
//	OnElementPaste()		Message handler to add elements from either the documents
//							'cut list' or 'copy list' to the selected item's element list 						 
//
void COD3View::OnElementPaste() 
{
	// TODO: Add your command handler code here
	
	COD3Doc		*pDoc = GetDocument();
	CElement	*pElement=NULL;
	CItem		*pItem = m_pItem;

	ASSERT_VALID(pDoc);


	// Get the element pointer
	if(m_bCopy)
	{
		pElement = pDoc->m_tplCopyList.GetHead();
	}
	else if(m_bCut)
	{
		pElement = pDoc->m_tplCutList.GetHead();
	}

	// Beams or accessories to paste
	if(pElement->m_pItem->IsBeam())
	{
		// Items to be pasted are type beams
		if(m_pItem->IsBeam())
		{
			// Set the document pointer
			pItem->m_pDoc = pDoc;
			pItem->PasteBeam(this);
		}
		else
		{
			// Inform user
			AfxMessageBox(IDS_BEAMPASTE, MB_ICONINFORMATION);
		}
	}
	else
	{
		// Items to be pasted are type accessories
		if(!m_pItem->IsBeam())
		{
			// Set the document pointer
			pItem->m_pDoc = pDoc;
			pItem->PasteBeam(this);
		}
		else
		{
			// Inform user
			AfxMessageBox(IDS_ACCESSORYPASTE, MB_ICONINFORMATION);
		}
	}

	return;
}

///////////////////////////////////////////////////////////////////////////////
// COD3View commands
///////////////////////////////////////////////////////////////////////////////
// DisplayItems()	List the contents of the item selected from the LH Tree View
//
void COD3View::DisplayElements(CItem* pItem)
{
	this->m_pItem = pItem;

	if (GetViewType() != LVS_REPORT)
		SetViewType(LVS_REPORT);
	SetFullRowSel(TRUE);

	// Get pointer to the document
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Get reference to list control
	CListCtrl& m_DisplayListCtrl = GetListCtrl();
	m_DisplayListCtrl.SetImageList(m_pImgList, TVSIL_NORMAL);

	LVITEM			ItemAttributes;				
	CString*		pszText;
	int				iImage;
	POSITION		pos;
	CElement*		pElement;
	CBeamElement*	pBeam;

	m_DisplayListCtrl.DeleteAllItems();

	if(m_pItem)
	{
		// Test for a valid CItem *leftview pointer
		if(anySelected())
		{
			// Initialise list control item attributes
			ItemAttributes.mask = LVIF_TEXT|LVIF_IMAGE;	// Text member & icon is required
			ItemAttributes.iItem = 0;					// Initial index of insertion point
			CString sTemp;

			if(pItem->m_bIsBeam)
				iImage = 0;
			else
				iImage = 2;

			pos = pItem->m_tplElementList.GetHeadPosition();

			while (pos)
			{
				if(pItem->m_tplElementList.GetCount() <= 0){return;}

				pElement = pItem->m_tplElementList.GetNext(pos);

				// Insert Row 0 Column 1 
				ItemAttributes.iSubItem = 0;						// Main Item
				pszText = &(pElement->GetMark());					// Get text
				ItemAttributes.pszText = pszText->GetBuffer(1);		// Set text
				ItemAttributes.iImage = iImage;						// Set image
				m_DisplayListCtrl.InsertItem(&ItemAttributes);		// Insert into List Control
			
				// Insert Row 0 Column 2
				ItemAttributes.iSubItem = 1;						// Set Sub Item (Row 0, Second Column)
				int nQty = pElement->GetQty();						
				sTemp.Format("%d",nQty);
				pszText = &sTemp;									// Get text
				ItemAttributes.pszText = pszText->GetBuffer(1);		// Set text
				m_DisplayListCtrl.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

				if(pItem->m_bIsBeam)
				{
					pBeam = (CBeamElement*)pElement;
					this->DisplayBeam(pBeam, ItemAttributes);
				}
				else
				{
					CAccessoryElement *pAcc = (CAccessoryElement*)pElement;
					DisplayAccessory(pAcc, ItemAttributes);
				//	AfxMessageBox("Processing of Accessories not yet implemented");
				}

				++ItemAttributes.iItem;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//	DisplayBeam()		command function to add specific CBeamElement data to List
//
void COD3View::DisplayBeam(CBeamElement* pBeam, LVITEM& ItemAttributes)
{
	CListCtrl& m_DisplayListCtrl = GetListCtrl();

//	LVITEM		ItemAttributes;				
	CString*	pszText;
	CString		sTemp;

	// Insert Column 3
	ItemAttributes.iSubItem = 2;						// Set Sub Item (Row 0, Third Column)
	int nLength = pBeam->GetLength();						
	sTemp.Format("%d",nLength);
	pszText = &sTemp;									// Get text
	ItemAttributes.pszText = pszText->GetBuffer(1);		// Set text
	GetListCtrl().SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

	// Insert Column 4
	ItemAttributes.iSubItem = 3;						// Set Sub Item (Row 0, Fourth Column)
	pszText = &(pBeam->GetSPCode());					// Get text
	ItemAttributes.pszText = pszText->GetBuffer(1);		// Set text
	m_DisplayListCtrl.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

	// Insert Column 5
	ItemAttributes.iSubItem = 4;						// Set Sub Item (Row 0, Fifth Column)
	int nType = pBeam->GetMemberType();						
	sTemp.Format("%d",nType);
	pszText = &sTemp;									// Get text
	ItemAttributes.pszText = pszText->GetBuffer(1);		// Set text
	m_DisplayListCtrl.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control

	// Insert Column 6
	ItemAttributes.iSubItem = 5;						// Set Sub Item (Row 0, Sixth Column)
	pszText = &(pBeam->GetComment());					// Get address of text
	ItemAttributes.pszText = pszText->GetBuffer(1);		// Set text
	m_DisplayListCtrl.SetItem(&ItemAttributes);			// Use SetItem to Insert into List Control
}

void COD3View::DisplayAccessory(CElement *pElement, LVITEM& ItemAttributes)
{
	CListCtrl& m_DisplayListCtrl = GetListCtrl();
			
	CString				*pszText;
	CString				sTemp;
	CAccessoryElement	*pAcc = (CAccessoryElement *)pElement;

	// Insert Column 3
	ItemAttributes.iSubItem = 2;						
	int nLength = pAcc->GetLength();						
	sTemp.Format("%d",nLength);
	pszText = &sTemp;									
	ItemAttributes.pszText = pszText->GetBuffer(1);		
	GetListCtrl().SetItem(&ItemAttributes);			

	// Insert Column 4 (SPC)
	ItemAttributes.iSubItem = 3;						
	ItemAttributes.pszText = _T("None");
	m_DisplayListCtrl.SetItem(&ItemAttributes);			

	// Insert Column 5 (Type)
	ItemAttributes.iSubItem = 4;															
	ItemAttributes.pszText = _T("0");	
	m_DisplayListCtrl.SetItem(&ItemAttributes);			

	// Insert Column 6
	ItemAttributes.iSubItem = 5;						
	pszText = &(pAcc->GetComment());					
	ItemAttributes.pszText = pszText->GetBuffer(1);		
	m_DisplayListCtrl.SetItem(&ItemAttributes);			
}

///////////////////////////////////////////////////////////////////////////////////
// DefineImageList()	Setup image list for right pane list
//
void COD3View::DefineImageList()
{
	CBitmap		Bitmap;

	m_pImgList = new CImageList();
	m_pImgList->Create(16, 16, TRUE/*bMask*/, 4, 0);

	// Number 0
	Bitmap.LoadBitmap(IDB_SMALLBEAM);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 1
	Bitmap.LoadBitmap(IDB_SMALLBEAM);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 2
	Bitmap.LoadBitmap(IDB_SMALLBEAM);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 3
	Bitmap.LoadBitmap(IDB_SMALLBEAM);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);	
	Bitmap.DeleteObject();
}


//////////////////////////////////////////////////////////////////////////////////////////////
//	GetElementPointer()	Helper function to return a CItem pointer based on tree view selection
//
bool COD3View::GetElementPointer()
{
	int nIndex;
	CString szMark;

	nIndex = GetListCtrl().GetSelectionMark();
	szMark = GetListCtrl().GetItemText(nIndex,0);

	CItem*	pItem = this->m_pItem;
	CElement* pElement;

	// Search ElementList to get pointer to matching CElement object
	POSITION pos;

	pos = m_pItem->m_tplElementList.GetHeadPosition();

	while(pos)
	{
		pElement = m_pItem->m_tplElementList.GetNext(pos);
		if(szMark == pElement->GetMark())
		{
			this->m_pElement = pElement;
			return true; 
		}
	}
	return false;
}

bool COD3View::GetElementPointer(int selIndex)
{
	CItem		*pItem = this->m_pItem;
	CElement	*pElement=NULL;
	POSITION	pos;
	CString		szMark;
	bool		bRes=false;

	// Get selected itme text
	szMark = GetListCtrl().GetItemText(selIndex,0);

	pos = m_pItem->m_tplElementList.GetHeadPosition();

	// Search ElementList to get pointer to matching CElement object
	while(pos)
	{
		pElement = m_pItem->m_tplElementList.GetNext(pos);
		if(szMark == pElement->GetMark())
		{
			this->m_pElement = pElement;
			bRes = true;
			break;
		}
	}


	return(bRes);
}


void COD3View::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	// TODO: Add your control notification handler code here
	
	if(pLVKeyDow->flags & VK_CONTROL && 
		(pLVKeyDow->wVKey == 'a' || pLVKeyDow->wVKey == 'A'))
	{
		selectAllItems();
	}
	else if(pLVKeyDow->flags & VK_CONTROL && pLVKeyDow->wVKey == VK_DELETE)
	{
		// Delete selected elements
		OnElementDelete();
	}

	*pResult = 0;
}

void COD3View::selectAllItems()
{
	CListCtrl&	listCtrl = GetListCtrl();
	int			listCount=0, i;

	// Get item count
	if(listCount = listCtrl.GetItemCount())
	{
		// Loop through all items
		for(i=0; i<listCount; i++)
		{
			// Set to active state
			listCtrl.SetItemState(i, LVIS_SELECTED, LVSIL_STATE);
		}
	}

	return;
}

// Select all items via the menu popup
void COD3View::OnSelectallitems() 
{
	// TODO: Add your command handler code here
	selectAllItems();
	
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////
////////////////////// Context sensitive popup menu events ////////////////////////////////
//
void COD3View::OnUpdateElementDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl&	listCtrl = GetListCtrl();

	if(!listCtrl.GetSelectedCount())
		pCmdUI->Enable(false);

	return;
}

void COD3View::OnUpdateElementEdit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl&	listCtrl = GetListCtrl();
	int			count=0;

	if(!(count = listCtrl.GetSelectedCount()) || count > 1)
		pCmdUI->Enable(false);

	return;
}

void COD3View::OnUpdateElementCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl&	listCtrl = GetListCtrl();

	if(!listCtrl.GetSelectedCount())
		pCmdUI->Enable(false);

	return;
}

void COD3View::OnUpdateElementCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl&	listCtrl = GetListCtrl();

	if(!listCtrl.GetSelectedCount())
		pCmdUI->Enable(false);
	
	return;
}

void COD3View::OnUpdateElementPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	COD3Doc	*pDoc = GetDocument();

	if(pDoc->m_tplCutList.IsEmpty() && pDoc->m_tplCopyList.IsEmpty())
		pCmdUI->Enable(false);

	return;
}
///////////////////////////////////////////////////////////////////////////////////////////

void COD3View::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	COD3Doc		*pDoc = GetDocument();
	CMainFrame	*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	CString		dPath;
	CDC			*draw=NULL;
	UINT		nID, nStyle;
	int			cxWidth=200;
	CSize		txtSize;


	dPath.Empty();
	// Get the statusbar panel defaults
	pMainFrm->m_wndStatusBar.GetPaneInfo(1, nID, nStyle, cxWidth);
	// Set to default size
	cxWidth = 200;

	// If activating
	if(bActivate)
	{
		if(pDoc->m_pProjectSettings->m_ODDB_Open)
		{
			// Get the statusbar's DC
			draw=pMainFrm->m_wndStatusBar.GetDC();
			// Set text output
			dPath = pDoc->m_pProjectSettings->m_sDataSource;
			// Get the text size
			txtSize = draw->GetTextExtent(dPath);
			// Modify the width
			cxWidth = txtSize.cx - 20;
		}
	}
	
	// Set the width
	pMainFrm->m_wndStatusBar.SetPaneInfo(1, nID, nStyle, cxWidth);
	// Set the text
	pMainFrm->m_wndStatusBar.SetPaneText(1, dPath, true);

	CListView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void COD3View::OnUpdatePrintthiselement(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl&	listCtrl = GetListCtrl();


	if(listCtrl.GetSelectedCount() == 0)
		pCmdUI->Enable(false);
	
	return;	
}

void COD3View::OnPrintthiselement() 
{
	// TODO: Add your command handler code here
	int			count, i, pos;
	COD3Doc		*pDoc = GetDocument();
	CListCtrl&	listView = GetListCtrl();
	char		buffer[50];


	// Get the amount of items in the list
	count = listView.GetItemCount();

	for(i=0; i<count; i++)
	{
		if(listView.GetItemState(i, LVIS_SELECTED))
		{
			// Get selected item text
			listView.GetItemText(i, 0, buffer, sizeof(buffer)-1);

			if((pos=isSelected(buffer)) != -1)
			{
				pDoc->m_printSelArr.RemoveAt(pos);
			}
			else
			{
				pDoc->m_printSelArr.Add(buffer);
			}
		}
	}
	
	// Redraw list control
	if(count)
		listView.Invalidate(true);
		

	return;
}

void COD3View::OnUpdateSelectallitems(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CListCtrl&	listCtrl = GetListCtrl();

	if(listCtrl.GetItemCount() == 0)
		pCmdUI->Enable(false);

	return;
}

// If there is none selected the m_pItem member may be wrong
// Only used in standard mode
bool COD3View::anySelected(void)
{
	bool		sel=false;
	CLeftView	*pLeft=DYNAMIC_DOWNCAST(CLeftView, GetNextWindow(GW_HWNDFIRST));
	CTreeCtrl&	treeCtrl=pLeft->GetTreeCtrl();

	// Perform mode test
	if(!pLeft->m_mode)
	{
		// Got valid selction
		if(treeCtrl.GetSelectedItem())
			sel=true;
	}
	else
		sel=true;
	
	
	return(sel);
}

void COD3View::RedrawListControls()
{
	CLeftView		*view = (CLeftView *)GetNextWindow(GW_HWNDPREV);
	CTreeCtrl&		treeCtrl = view->GetTreeCtrl();
	HTREEITEM		child, sel, parent;
	CString			sBuffer;
	int				nQty = 0;
	int				nPieces = 0;
	double			nLength = 0.0;
	double			nRunLength = 0.0;
	double			nWeight = 0.0;
	double			nTonnes = 0.0;
	POSITION		posElement;
	CElement		*pElement=NULL;
	CBeamElement	*pBeam=NULL;


	
	// Get the selected item
	sel = treeCtrl.GetSelectedItem();

	// Ensure parent item selected
	if(!treeCtrl.ItemHasChildren(sel))
	{
		// Test for type of parent
		parent = treeCtrl.GetNextItem(sel, TVGN_PARENT);

		if(treeCtrl.GetRootItem() != parent)
			sel = parent;
	}

	// Get the first child item
	child = treeCtrl.GetChildItem(sel);

	// Loop until children removed
	while(child)
	{
		// Delete child
		treeCtrl.DeleteItem(child);
		// Get next child
		child = treeCtrl.GetChildItem(sel);
	}
	
	// Re-insert the tree items
	if (!m_pItem->m_tplElementList.IsEmpty())
	{
		// Get the head position
		posElement = m_pItem->m_tplElementList.GetHeadPosition();
		// Get the weight
		nWeight = m_pItem->GetProductWeight();

		// Loop all elements
		while(posElement)
		{
			// Get the pointer
			pElement = m_pItem->m_tplElementList.GetNext(posElement);
			nQty = pElement->GetQty();
			// Increment the total number of peices
			nPieces += nQty;
			pBeam = (CBeamElement*)pElement;
			nLength = pBeam->GetLength();
			// Increment the length
			nRunLength += (nLength / 1000) * nQty;
			// Increment the weight
			nTonnes = (nRunLength * nWeight) / 1000;
		}


		// Product code
		sBuffer.Format("Product Code: %s", m_pItem->GetProductCode());
		treeCtrl.InsertItem(sBuffer, 6, 6, sel, TVI_LAST);	

		// Quantity
		sBuffer.Format("Total Pieces: %i", nPieces);
		treeCtrl.InsertItem(sBuffer, 6, 6, sel, TVI_LAST);

		// Run length
		sBuffer.Format("Total Run Length: %.3f", nRunLength);
		treeCtrl.InsertItem(sBuffer, 6, 6, sel, TVI_LAST);

		// Weight
		sBuffer.Format("Total Weight: %.3f", nTonnes);
		treeCtrl.InsertItem(sBuffer, 6, 6, sel, TVI_LAST);
	}

	// Used as a psuedo mouse click, redraws list view
	// Select no tree items
	treeCtrl.SelectItem(NULL);
	// Reselect tree item
	treeCtrl.SelectItem(sel);


	return;
}

int COD3View::isSelected(CString name)
{
	int	result=-1, i;
	COD3Doc	*pDoc = GetDocument();
	int count = pDoc->m_printSelArr.GetSize();


	// Loop selected items
	for(i=0; i<count; i++)
	{
		if(!pDoc->m_printSelArr.GetAt(i).Compare(name))
		{
			// Name found
			result=i;
			break;
		}
	}

	return(result);
}
