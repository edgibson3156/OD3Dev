// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "OD3.h"

#include "OD3Doc.h"
#include "LeftView.h"
#include "OD3View.h"
#include "Line1.h"
#include "Line2.h"
#include "Line3.h"
#include "mainfrm.h"
#include "DlgAccessories.h"
#include "DaoAccOffset.h"

extern CLine1 Line1;
extern CLine2 Line2;
extern CLine3 Line3;

#include "ProductMods.h"
extern CProductMods prodMods;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_COMMAND(ID_PROCESS_PRINT_ALL, OnProcessPrintAll)
	ON_COMMAND(ID_ITEM_DELETE, OnItemDelete)
	ON_COMMAND(ID_ITEM_GENERATE, OnItemGenerate)
	ON_COMMAND(ID_ITEM_PRINT, OnItemPrint)
	ON_COMMAND(ID_ITEM_TRANSFER, OnItemTransfer)
	ON_COMMAND(ID_ITEM_TRANSFER2, OnItemTransfer2)
	ON_COMMAND(ID_ITEM_VALIDATE, OnItemValidate)
	ON_COMMAND(ID_ITEM_ADD_BEAM, OnItemAddBeam)
	ON_COMMAND(ID_PROCESS_PRINT_ITEM, OnProcessPrintItem)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_UPDATE_COMMAND_UI(ID_DUMP_SETREPORTTYPE_ALLITEMS, OnUpdateDumpSetreporttypeAllitems)
	ON_UPDATE_COMMAND_UI(ID_ITEM_PRINT, OnUpdateItemPrint)
	ON_COMMAND(ID_DUMP_SETREPORTTYPE_ALLITEMS, OnDumpSetreporttypeAllitems)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_COMMAND(IDM_ADVANCED_MODE, OnAdvancedMode)
	ON_UPDATE_COMMAND_UI(IDM_ADVANCED_MODE, OnUpdateAdvancedMode)
	ON_COMMAND(IDM_VAL_SELECTION, OnValSelection)
	ON_UPDATE_COMMAND_UI(IDM_VAL_SELECTION, OnUpdateValSelection)
	ON_COMMAND(IDM_GEN_SELECTION, OnGenSelection)
	ON_UPDATE_COMMAND_UI(IDM_GEN_SELECTION, OnUpdateGenSelection)
	ON_COMMAND(IDM_REP_SELECTION, OnRepSelection)
	ON_UPDATE_COMMAND_UI(IDM_REP_SELECTION, OnUpdateRepSelection)
	ON_COMMAND(IDM_TRAN_SELECTION, OnTranSelection)
	ON_UPDATE_COMMAND_UI(IDM_TRAN_SELECTION, OnUpdateTranSelection)
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	m_iPrintStatus = 2;
	m_mode = false;
	m_pImgList = NULL;
	m_pLastItem = NULL;
}

CLeftView::~CLeftView()
{
	if(m_pImgList)
		delete m_pImgList;
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing
BOOL CLeftView::preparePrint(CPrintInfo *pInfo)
{
	return(OnPreparePrinting(pInfo));
}

void CLeftView::printGo(CDC *pDC, CPrintInfo *pInfo)
{
	OnPrint(pDC, pInfo);
}

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	this->m_bDone = false;
	pInfo->m_nNumPreviewPages = 1;
	pInfo->SetMaxPage(1);
	
	return(DoPreparePrinting(pInfo));
}

//////////////////////////////////////////////////////////////////////////////////////////////
//	OnPrepareDC()	message handler override to cope with unknown number of pages
//
void CLeftView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bDone)
	{
		pInfo->m_bContinuePrinting = FALSE;
	}
	else
	{
		pInfo->m_bContinuePrinting = TRUE;
	}
	CTreeView::OnPrepareDC(pDC, pInfo);
}

////////////////////////////////////////////////////////////////////////////
//	OnPrint()		message handler to switch between report types
//
void CLeftView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// set headers and footers from this function
	bool	revert=false;
	CString	txt;
	CBrush	*oldBru, bru;
	COD3Doc	*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	short int state = HIWORD(GetKeyState(VK_CONTROL));


	// Are we previewing? we can preview one at the moment
	if(pInfo->m_bPreview && state == 0)
	{
		bru.CreateSolidBrush(RGB(255,0,0));
		pDC->LineTo(pInfo->m_rectDraw.right, pInfo->m_rectDraw.bottom);
		pDC->MoveTo(pInfo->m_rectDraw.right, pInfo->m_rectDraw.top);
		pDC->LineTo(pInfo->m_rectDraw.left, pInfo->m_rectDraw.bottom);


		oldBru = (CBrush *)pDC->SelectObject(&bru);
		pDC->Rectangle((pInfo->m_rectDraw.right/2)-250,
						(pInfo->m_rectDraw.bottom/2)-250,
						(pInfo->m_rectDraw.right/2)+250,
						(pInfo->m_rectDraw.bottom/2)+250);

		pDC->SelectObject(oldBru);
		bru.DeleteObject();

		txt = _T("Ayrshire Metal Products");
		pDC->TextOut((pInfo->m_rectDraw.right/2)-600, 200, txt.GetBuffer(txt.GetLength()));
		txt = _T("I Sanders");
		pDC->TextOut((pInfo->m_rectDraw.right/2)-300, 500, txt.GetBuffer(txt.GetLength()));

		CTreeView::OnPrint(pDC, pInfo);
		return;
	}

	if(pDoc->m_printSelArr.GetSize())
	{
		m_iPrintStatus=1;
		revert=true;
	}

	if(m_iPrintStatus == 2)
	{
		this->PrintAllBeams(pDC, pInfo);
	}
	else if(m_iPrintStatus == 0)
	{
		this->PrintAccessoryDetails(pDC,pInfo);
	}
	else if(m_iPrintStatus == 1)
	{
		this->PrintItemDetails(pDC,pInfo);
	}

	// Restore previous settings
	if(revert)
	{
		// Clear single print selection
		pDoc->m_printSelArr.RemoveAll();
		// Get the current list view
		COD3View *pView = DYNAMIC_DOWNCAST(COD3View, this->GetNextWindow(GW_HWNDNEXT));
		// Get the list control
		CListCtrl& listCtrl = pView->GetListCtrl();
		// Update list control
		listCtrl.Invalidate(true);
	}

	if(m_iPrintStatus==1)
	{
		// Change the selected image back to normal
		TVITEM		item;
		CTreeCtrl&	tree=GetTreeCtrl();


		// Set the item structure
		item.mask = TVIF_SELECTEDIMAGE|TVIF_IMAGE;
		item.hItem = tree.GetSelectedItem();

		// Get the item
		tree.GetItem(&item);

		// Only change the image if a beam or accessory
		if(item.iImage==2 || item.iImage==4)
		{
			// Change to printer image
			item.iSelectedImage = item.iImage;
			tree.SetItem(&item);
		}
	}

	// Restore to print all items
	m_iPrintStatus = 2;

	CTreeView::OnPrint(pDC, pInfo);
}

// No real requirement for these
#if 0
////////////////////////////////////////////////////////////////////////////
void CLeftView::OnPrintAccessory() 
{
	m_iPrintStatus = 0;	
}

////////////////////////////////////////////////////////////////////////////
void CLeftView::OnPrintBeam()  
{
	m_iPrintStatus = 2;

}
#endif
////////////////////////////////////////////////////////////////////////////
//	OnProcessPrintAll())		message handler for 'Process' menu item
//								to set print status flag to print all beams
//
void CLeftView::OnProcessPrintAll() 
{
	m_iPrintStatus = 2;
	
}

//////////////////////////////////////////////////////////////////////////////////////////////
//	OnProcessPrintItem()		message handler for 'Process' menu item
//								to get item number to print from dialog
//
void CLeftView::OnProcessPrintItem()
{
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// Call the items list dialog to set up item to print
	CDlgItemList SelectItemDlg;
	SelectItemDlg.m_pDoc = pDoc;
	SelectItemDlg.DoModal();

	m_pItem = SelectItemDlg.GetItemPointer();

	m_iPrintStatus = 1;
	
}

////////////////////////////////////////////////////////////////////////////
//	OnItemPrint()		message handler for context menu
//
void CLeftView::OnItemPrint()
{
	// TODO: Add your command handler code here
	TVITEM		item;
	CTreeCtrl&	tree=GetTreeCtrl();


	this->GetItemPointer();		//	sets CItem* to member variable
	
	m_iPrintStatus = 1;
	
	// Set the item structure
	item.mask = TVIF_SELECTEDIMAGE|TVIF_IMAGE;
	item.hItem = tree.GetSelectedItem();

	// Get the item
	tree.GetItem(&item);

	// Only change the image if a beam or accessory
	if(item.iImage==2 || item.iImage==4)
	{
		// Change to printer image
		item.iSelectedImage = 8;
		tree.SetItem(&item);
	}

}



/////////////////////////////////////////////////////////////////////////////
// CLeftView TreeView Display
//
void CLeftView::OnInitialUpdate()
{

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	
	this->DefineImageList();

	CTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

COD3Doc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COD3Doc)));
	return (COD3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers
/////////////////////////////////////////////////////////////////////////////
//
void CLeftView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
#ifdef NOT_REQUIRED
	CMenu menubar;

	// Load context menu
	menubar.LoadMenu(IDR_POPUPMENUS);

	unsigned int	uFlags = 0;
	HTREEITEM		hitTest=NULL;
	CTreeCtrl&		refMainTree = GetTreeCtrl();
	CPoint			point;
	CItem			*pItem=NULL;

	// Get mouse pointer pos
	GetCursorPos(&point);
	// Convert to view coords
	this->ScreenToClient(&point);

	// Perform pos hit test with flags
	hitTest = refMainTree.HitTest(point, &uFlags);

	// Get and display item if on lable and an item has been hit
	if(hitTest && uFlags & TVHT_ONITEM)
	{
		// Return item pointer
		if (this->GetItemPointer(hitTest))
		{
			// Send message to panel2 and update the display
			pItem = this->m_pItem;
			CWnd* pWnd = this->GetNextWindow();
			COD3View* pView = DYNAMIC_DOWNCAST(COD3View, pWnd);
			// Display elements in listview control
			pView->DisplayElements(pItem);
		}
	}
#endif

	*pResult = 0;
}


//////////////////////////////////////////////////////////////////////////////////////
//	OnUpdate()
//
void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

	// Populate the TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

	DWORD dwRemove=0;
	UINT  nFlags=0;
	DWORD dwAdd;

	CTreeCtrl& refMainTree = GetTreeCtrl();

	if(m_mode)
	{
		// Set to advanced colour
		refMainTree.SetBkColor(RGB(195,192,205));

		// Set flags
		dwAdd =	TVS_CHECKBOXES |
				TVS_HASLINES |
				TVS_LINESATROOT |
				TVS_HASBUTTONS |
				TVS_DISABLEDRAGDROP |
				TVS_NOTOOLTIPS |
				TVS_TRACKSELECT;
	}
	else
	{
		// Set to standard colour
		refMainTree.SetBkColor(RGB(255,255,255));

		// Set flags
		dwAdd =	TVS_HASLINES |
				TVS_LINESATROOT |
				TVS_HASBUTTONS |
				TVS_DISABLEDRAGDROP |
				TVS_NOTOOLTIPS |
				TVS_TRACKSELECT;

		// Remove checkboxes
		dwRemove = TVS_CHECKBOXES;

	}

	refMainTree.ModifyStyle(dwRemove, dwAdd, nFlags);

	refMainTree.DeleteAllItems();
	
	this->PopTree();
}

//////////////////////////////////////////////////////////////////////////////////////////////
//	OnItemDelete()		message handler 
//
void CLeftView::OnItemDelete() 
{
	// TODO: Add your command handler code here
	COD3Doc		*pDoc = GetDocument();
	COD3View	*pView=DYNAMIC_DOWNCAST(COD3View, GetNextWindow(GW_HWNDNEXT));
	CTreeCtrl&	treeCtrl = GetTreeCtrl();
	CListCtrl&	listCtrl = pView->GetListCtrl();
	HTREEITEM	hTreeItem;
	CItem		*pItem=NULL;
	int			nItemID, strPos, selCount, i;
	CString		szMsg, product;
	TVITEM		item;
	CPtrArray	cItemPtr;


	// Test mode
	if(!m_mode)
	{
		if(m_pItem)
		{
			pItem = this->m_pItem;
			nItemID = pItem->GetItemID();

			szMsg.Format(IDS_DEL_ITEM, nItemID);
			if(AfxMessageBox(szMsg, MB_ICONQUESTION|MB_YESNO) == IDYES)
			{
				// Delete selected item
				pDoc->DeleteItem(pItem);
				// Clean member pointer
				m_pItem=NULL;
			}
		}
	}
	else
	{
		// Multiple deletion using check boxes
		if((selCount=countSelection()) > 0)
		{
			// Test count and load warning
			if(selCount > 1)
				szMsg.Format(IDS_DEL_MANY, selCount);
			else
				szMsg.LoadString(IDS_DEL_ONE);

			// Ask for removal confirmation
			if(AfxMessageBox(szMsg,MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				// Get root item
				hTreeItem = treeCtrl.GetNextItem(NULL, TVGN_ROOT);
				// Get the next child item
				hTreeItem = treeCtrl.GetNextItem(hTreeItem, TVGN_CHILD);

				while(hTreeItem)
				{
					// Test if the item is selected for removal
					if(treeCtrl.GetCheck(hTreeItem))
					{
						// Set the item structure
						item.mask = TVIF_PARAM;
						item.hItem = hTreeItem;
						// Get the item
						treeCtrl.GetItem(&item);

						// Get the item text
						product = treeCtrl.GetItemText(hTreeItem);

						// Break up the string
						strPos = product.Find(":");
						product = product.Mid(4, (strPos-4));

						// Get item number
						nItemID = atoi(product);
				
						// Get the item and add it to a pointer list
						if((pItem = pDoc->GetItemPointer(nItemID, item.lParam)))
							cItemPtr.Add(pItem);
					}

					// Get the next item
					hTreeItem = treeCtrl.GetNextItem(hTreeItem, TVGN_NEXT);
				}

				// Delete the list of items
				for(i=0; i<cItemPtr.GetSize(); i++)
					pDoc->DeleteItem((CItem *)cItemPtr.GetAt(i));

				// Clean pointer list
				cItemPtr.RemoveAll();

				// Save when exit flag
				pDoc->SetModifiedFlag();
				// Set title prompt
				pDoc->SetTitle(NULL);

				// Remove items in the list control
				listCtrl.DeleteAllItems();
			}
		}
	}


	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//	OnItemValidate()		Message handler calls COD3Doc functions
//
void CLeftView::OnItemValidate() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	CItem* pItem;
	CString sItemID;
	int nItemID;
	
	if(this->GetItemPointer())
	{
		// Beam or accessory
		if(m_pItem->IsBeam())
		{
			pItem = this->m_pItem;
			nItemID = pItem->GetItemID();
			sItemID.Format("%d",nItemID);

			pDoc->ValidateItem(pItem);
		}
		else
		{
			pDoc->ValidateAccItem(m_pItem);
		}
	}
	else
	{
		return;
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////////
//	OnItemGenerate()		Message handler calls COD3Doc functions
//
void CLeftView::OnItemGenerate() 
{
	COD3Doc		*pDoc = GetDocument();
	CMainFrame	*pMainFrm=DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	CItem		*pItem;
	CString		sItemID;
	int			nItemID;
	bool		bResult=true;

	// TODO: Add your command handler code here
	
	BeginWaitCursor(); // display the hourglass cursor

	if(this->GetItemPointer())
	{
		pItem = this->m_pItem;
		nItemID = pItem->GetItemID();
		sItemID.Format("%d",nItemID);
	}
	else
	{
		// Clear waring flag
		prodMods.warn = true;
		return;
	}

	if(pItem->IsBeam())
	{
		if (pDoc->ValidateItem(pItem))
		{}
		else
		{
			CString szMsg;
			szMsg = "Validation has failed!";
			szMsg += "\n\nYou must associate all products in this project";
			szMsg += "\nwith appropriate production lines to complete the validation";
			AfxMessageBox(szMsg);
			// Clear waring flag
			prodMods.warn = true;
			return;
		}

		// if item fails to generate because of non-standard requirement or
		// NULL punch value exit the loop to reach the CmdTarget break so
		// the modeless dialog will be displayed for updating

		if(!pDoc->GenerateItem(pItem))
		{
			// Clear waring flag
			prodMods.warn = true;
			return;
		}
	}
	else
	{	
		// Generate the accessory item
		bResult = pDoc->GenerateAccItem(pItem);
	}

	// Remove progress bar
	if(pMainFrm->m_bProgCreated)
	{
		pMainFrm->m_bProgCreated = false;
		pMainFrm->m_progressBar.DestroyWindow();
	}


	if(bResult)
	{
		CString		sText;

		// Format message
		sText.Format("Output Generated for Item %s", sItemID);
		// Create message dialog
		CDlgMessage msg(NULL, sText);

		// Display message
		msg.DoModal();

		pDoc->m_bIsGenerated = true;
	}

	LPCTSTR lpszText = _T("Ready");
	pDoc->UpdateStatusBar(lpszText);


	EndWaitCursor(); 

	
	// Clear waring flag
	prodMods.warn = true;
	
	return;
}

/////////////////////////////////////////////////////////////////////////////
//	OnItemAddBeam() 
//
void CLeftView::OnItemAddBeam() 
{
	// TODO: Add your command handler code here
	COD3Doc		*pDoc = GetDocument();
	CItem		*pItem;
	TVITEM		item;
	CTreeCtrl&	tree=GetTreeCtrl();
	HTREEITEM	hItem=tree.GetSelectedItem();


	// Set the item structure
	item.mask = TVIF_PARAM;
	item.hItem = hItem;
	// Get the item
	tree.GetItem(&item);

	// Beam or accessory picked
	if(item.lParam==ISBEAM)
	{
		if(GetItemPointer())
		{
			// Set the pointer
			pItem = this->m_pItem;
			pDoc->AddBeam(pItem);
		}
	}
	else if(item.lParam==ISACCESSORY)
	{
		// Get the accessory item pointer
		GetAccItemPtr(hItem);
		// Create object ans set pointers
		CDlgAccessories dlgAcc(pDoc, m_pItem, NULL);

		// Set the view pointer
		dlgAcc.m_pView = this;
		dlgAcc.m_bTree = true;

		// Open the dialog
		dlgAcc.DoModal();
	}
	
}

/////////////////////////////////////////////////////////////////////////////
//	void CLeftView::OnItemTransfer() 
//
void CLeftView::OnItemTransfer() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	CItem* pItem;
	CString sItemID, sText;
	int nItemID;
	
	if(this->GetItemPointer())
	{
		pItem = this->m_pItem;
		nItemID = pItem->GetItemID();
		sItemID.Format("%d",nItemID);

		if(pDoc->TransferItem(pItem))
		{
			// Create the ink jet file
			if(pDoc->writeInkJetFile(pItem))
			{
				// Create user information string
				sItemID.Format("_%i", pItem->GetItemID());
				sText.Format("Transfer complete for item %i\nInkjet file created and saved to A:\\%s.ink",
								pItem->m_nItemID, pDoc->m_pProjectHeader->m_sProjectName+sItemID);
			}
			else
	


			{
				// Create user information string
				sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
			}

			// Inform user
			AfxMessageBox(sText, MB_ICONINFORMATION);
		}
		
	}
	
}

//// test
void CLeftView::OnItemTransfer2() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	CItem* pItem;
	CString sItemID, sText;
	int nItemID;
	
	if(this->GetItemPointer())
	{
		pItem = this->m_pItem;
		nItemID = pItem->GetItemID();
		sItemID.Format("%d",nItemID);

		if(pDoc->TransferItemb(pItem))
		{
			// Create the ink jet file
			if(pDoc->writeInkJetFile2(pItem))
			{
				// Create user information string
				sItemID.Format("_%i", pItem->GetItemID());
				sText.Format("Transfer complete for item %i\nInkjet file created and saved to E:\\%s.ink",
								pItem->m_nItemID, pDoc->m_pProjectHeader->m_sProjectName+sItemID);
			}
			else
	


			{
				// Create user information string
				sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
			}

			// Inform user
			AfxMessageBox(sText, MB_ICONINFORMATION);
		}
		
	}
	
}





/////////////////////////////////////////////////////////////////////////////
// CLeftView Commands
/////////////////////////////////////////////////////////////////////
// DefineImageList()		Setup image list for tree control
//
void CLeftView::DefineImageList()
{
	// Setup image list for tree control
	CBitmap		Bitmap;

	m_pImgList = new CImageList();
	m_pImgList->Create(20, 14, TRUE/*bMask*/, 7, 0);

	// Number 0
	Bitmap.LoadBitmap(IDB_FILE_CLOSED);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 1
	Bitmap.LoadBitmap(IDB_FILE_OPEN);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 2
	Bitmap.LoadBitmap(IDB_BEAM);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 3
	Bitmap.LoadBitmap(IDB_BEAM_SELECTED);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 4
	Bitmap.LoadBitmap(IDB_ACC);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 5
	Bitmap.LoadBitmap(IDB_ACC_SELECTED);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);	
	Bitmap.DeleteObject();

	// Number 6
	Bitmap.LoadBitmap(IDB_CHILD);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);
	Bitmap.DeleteObject();

	// Number 7
	Bitmap.LoadBitmap(IDB_CHILD);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);	
	Bitmap.DeleteObject();

	// Number 8
	Bitmap.LoadBitmap(IDB_PRINT_SEL);
	m_pImgList->Add(&Bitmap, (COLORREF)0xFFFFFF);	
	Bitmap.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// PopTree()		A function to add items to the tree control
//
void CLeftView::PopTree() 
{

	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CTreeCtrl& refMainTree = GetTreeCtrl();

	refMainTree.SetImageList(m_pImgList, TVSIL_NORMAL);

	// TODO: Add your command handler code here
	// Define tree structure - top level is a list of projects (files)...
	HTREEITEM hFile;
		
	// Each file consists of a list of items ..
	HTREEITEM hItem;
	
	// An Item also contains a summary of information relating to the elements it contains....
	HTREEITEM hProdCode,hPieces,hMetres,hTonnes;
	
	CString				sProjectName,sItemLabel,sItemID,sProdCode;
	CString				sNoOff,sMetres,sTonnes,sTemp;
	POSITION			posItem,posElement;
	CItem				*pItem=NULL;
	CElement			*pElement=NULL;
	CBeamElement		*pBeam=NULL;
	CAccessoryElement	*pAcc=NULL;
	int					nQty, nPieces, nItemID;
	double				nLength, nRunLength, nWeight, nTonnes;
	TVITEM				item;

	// Insert the project name at root of tree and add the nodes for items and elements...
	sProjectName = pDoc->m_pProjectHeader->m_sProjectName;

	// Project 1 (only one in this implementation)
	hFile = refMainTree.InsertItem(sProjectName, 0, 1,TVI_ROOT,TVI_LAST);

	//     Project 1, Items #1 .... #n
	// First check that at least one item exists ...
	if(!pDoc->m_tplItemList.IsEmpty() || !pDoc->m_tplAccItemList.IsEmpty())
	{
		posItem = pDoc->m_tplItemList.GetHeadPosition();
	
		// ... loop through list to find all the items
		while(posItem)
		{
			pItem = pDoc->m_tplItemList.GetNext(posItem);
			nItemID = pItem->GetItemID();
			sItemID.Format("%d",nItemID);
			sItemLabel = "Item ";
			sItemLabel += sItemID;
			sItemLabel += ": ";
			sItemLabel += pItem->GetProductName();

			// Add the item to the tree
			hItem = refMainTree.InsertItem(sItemLabel, 2, 3, hFile, TVI_LAST);

			// Set item data
			item.mask = TVIF_PARAM;
			item.hItem = hItem;
			item.lParam = ISBEAM;

			refMainTree.SetItem(&item);


			// initialize local variables
			nQty=nPieces = 0;
			nLength=nRunLength=nWeight=nTonnes = 0.0;

			sProdCode = "Product Code: ";
			sProdCode += pItem->GetProductCode();

			//  now loop through the element list to summarise the quantities
			// ... first make sure at least one element exists

			if (!pItem->m_tplElementList.IsEmpty())
			{
				posElement = pItem->m_tplElementList.GetHeadPosition();
				nWeight = pItem->GetProductWeight();

				while(posElement)
				{	

					pElement = pItem->m_tplElementList.GetNext(posElement);

					nQty = pElement->GetQty();
					nPieces += nQty;

					pBeam = (CBeamElement*)pElement;
					nLength = pBeam->GetLength();
			
					nRunLength += (nLength / 1000) * nQty;
					nTonnes = (nRunLength * nWeight) / 1000;
				}

				sTemp.Format("%d",nPieces);
				sNoOff = "Total Pieces: ";
				sNoOff += sTemp;

				sTemp.Format("%.3lf",nRunLength);
				sMetres = "Total Run Length: ";
				sMetres += sTemp;
				sMetres += " Metres.";

				sTemp.Format("%.3lf", nTonnes);
				sTonnes = "Total Weight: ";
				sTonnes += sTemp;
				sTonnes += "Tonnes";

				hProdCode = refMainTree.InsertItem(sProdCode, 6,6, hItem, TVI_LAST);	
				hPieces = refMainTree.InsertItem(sNoOff, 6,6, hItem, TVI_LAST);	
				hMetres = refMainTree.InsertItem(sMetres, 6,6, hItem, TVI_LAST);	
				hTonnes = refMainTree.InsertItem(sTonnes, 6,6, hItem, TVI_LAST);	
			}
		}

		// Get the accessories head position
		posItem = pDoc->m_tplAccItemList.GetHeadPosition();

		while(posItem)
		{
			pItem = pDoc->m_tplAccItemList.GetNext(posItem);
			nItemID = pItem->GetItemID();
			sItemID.Format("%d",nItemID);
			sItemLabel = "Item ";
			sItemLabel += sItemID;
			sItemLabel += ": ";
			sItemLabel += pItem->GetProductName();

		
			hItem = refMainTree.InsertItem(sItemLabel, 4,5, hFile, TVI_LAST);
			
			// Set item data
			item.mask = TVIF_PARAM;
			item.hItem = hItem;
			item.lParam = ISACCESSORY;

			refMainTree.SetItem(&item);

			// initialize local variables
			nQty=nPieces = 0;
			nLength=nRunLength=nWeight=nTonnes = 0.0;

			sProdCode = "Product Code: ";
			sProdCode += pItem->GetProductCode();


			if (!pItem->m_tplElementList.IsEmpty())
			{
				posElement = pItem->m_tplElementList.GetHeadPosition();
				nWeight = pItem->GetProductWeight();

				while(posElement)
				{
					pAcc = (CAccessoryElement *)pItem->m_tplElementList.GetNext(posElement);	
					pElement = (CElement *)pAcc;

					nQty = pElement->GetQty();
					nPieces += nQty;

					nLength = pAcc->GetLength();

					nRunLength += (nLength / 1000) * nQty;
					nTonnes = (nRunLength * nWeight) / 1000;
				}

				sTemp.Format("%d",nPieces);
				sNoOff = "Total Pieces: ";
				sNoOff += sTemp;

				sTemp.Format("%.3lf",nRunLength);
				sMetres = "Total Run Length: ";
				sMetres += sTemp;
				sMetres += " Metres.";

				sTemp.Format("%.3lf", nTonnes);
				sTonnes = "Total Weight: ";
				sTonnes += sTemp;
				sTonnes += "Tonnes";

				hProdCode = refMainTree.InsertItem(sProdCode, 6,6, hItem, TVI_LAST);	
				hPieces = refMainTree.InsertItem(sNoOff, 6,6, hItem, TVI_LAST);	
				hMetres = refMainTree.InsertItem(sMetres, 6,6, hItem, TVI_LAST);	
				hTonnes = refMainTree.InsertItem(sTonnes, 6,6, hItem, TVI_LAST);	
			}
		}
	}

	// Expand root item after update
	refMainTree.Expand(hFile, TVE_EXPAND);

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////
// DisplayElements()		command function to display the item's element list
//							 in the right hand pane
//
void CLeftView::DisplayElements()
{
	CItem* pItem;

	if (this->GetItemPointer())
	{
		// Send message to right pane to update its display
		pItem = this->m_pItem;
		CWnd* pWnd = this->GetNextWindow();
		COD3View* pView = DYNAMIC_DOWNCAST(COD3View, pWnd);

		pView->DisplayElements(pItem);
	}
	else
	{
		return;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////
//	GetItemPointer()	Helper function to return a CItem pointer based on tree view selection
//
bool CLeftView::GetItemPointer()
{
	CTreeCtrl& refMainTree = GetTreeCtrl();

	CItem*	pItem=NULL;
	COD3Doc* pDoc = GetDocument();

	HTREEITEM	hItem;
	CString		sItemID;
	CString		sPath;
	CString		sTemp;
	int			cChar;
	int			nItemID;
	TVITEM		item;

	// Get currently selected item in the tree
	hItem = refMainTree.GetSelectedItem();

	// Set the item structure
	item.mask = TVIF_PARAM;
	item.hItem = hItem;
	// Get the item
	refMainTree.GetItem(&item);

	// Set the selected item text to string variable
	sPath = refMainTree.GetItemText(hItem);

	// Manipulate item text to get nItemID
	sTemp = sPath.Right(sPath.GetLength()-5);
	cChar = sTemp.Find(":",0);
	sItemID = sTemp.Left(cChar);
	nItemID = atoi(sItemID);

	// Search ItemList to get pointer to matching CItem object
	POSITION pos;

	if(item.lParam == ISBEAM)
	{
		pos = pDoc->m_tplItemList.GetHeadPosition();

		while(pos)
		{
			pItem = pDoc->m_tplItemList.GetNext(pos);
			if(nItemID == pItem->GetItemID())
			{
				this->m_pItem = pItem;
				return TRUE; 
			}
		}
	}
	else if(item.lParam == ISACCESSORY)
	{
		// Get the head position for the accessories
		pos = pDoc->m_tplAccItemList.GetHeadPosition();

		while(pos)
		{
			// Get the next element object
			pItem = pDoc->m_tplAccItemList.GetNext(pos);

			// Test the id number
			if(nItemID == pItem->GetItemID())
			{
				// Set the member pointer
				this->m_pItem = pItem;
				return(true); 
			}
		}
	}


	return(false);
}
///////////////////////////////////////////////////////////////////////////////////////////
//	Printer command functions
//
///////////////////////////////////////////////////////////////////////////////////////////
// PrintAllBeams()		command function called by OnPrint depending on m_iPrintStatus flag
//						loops through the document's item list and calls PrintItem for each item
//
void CLeftView::PrintAllBeams(CDC* pDC, CPrintInfo* pInfo)
{
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->m_bIsGenerated != true)
	{
		AfxMessageBox("You must generate the output file before printing the schedule");
		return;
	}

	POSITION posItem;

	//	Get start of item list
	posItem = pDoc->m_tplItemList.GetHeadPosition();

	this->m_bDone = false;
	
	while (posItem)
	{
		m_pItem = pDoc->m_tplItemList.GetNext(posItem); 
		this->PrintItem(pDC, pInfo);
	}

	//	Get start of accessories list
	posItem = pDoc->m_tplAccItemList.GetHeadPosition();
	while (posItem)
	{
		m_pItem = pDoc->m_tplAccItemList.GetNext(posItem); 
		this->PrintItem(pDC, pInfo);
	}
	this->m_bDone = true;
}

////////////////////////////////////////////////////////////////////////////
// PrintItemDetails()	command function called by OnPrint depending on m_iPrintStatus flag
//						calls PrintItem for item referenced by the m_pItem member variable
//
void CLeftView::PrintItemDetails(CDC* pDC, CPrintInfo* pInfo)
{
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->m_bIsGenerated != true)
	{
		AfxMessageBox("You must generate the output file before printing the schedule");
		return;
	}

	this->m_bDone = false;

	this->PrintItem(pDC, pInfo);

	this->m_bDone = true;

}
////////////////////////////////////////////////////////////////////////////
// PrintItem	command function to print details 
//
void CLeftView::PrintItem(CDC* pDC, CPrintInfo* pInfo)
{
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CElement*		pElement;
	CBeamElement*	pBeam;
	CHole*			pOperation;

	int iPartIndex;
	int iHitCounter;
	int nPageCounter;
	double nRunLength = 0.0;
	double nRunWeight = 0.0;
	double nItemLength = 0.0;
	double nItemWeight = 0.0;

	CString szText;
	CString szDocTitle;
	CString sItemID, date;
	char szBuffer[256];
	int  singlePrint, iAccOffset;

	short iLeftMargin = 150;
	short iTopMargin = 100;
	short iBottomMargin = 150;
	short iCenterTabMargin	= pDC->GetDeviceCaps(HORZRES)/2;
	short iTabMarginOne		= pDC->GetDeviceCaps(HORZRES)/4;
	short iTabMarginTwo		= pDC->GetDeviceCaps(HORZRES)/2;
	short iPageLength		= pDC->GetDeviceCaps(VERTRES);

	long iYPosition = iTopMargin;
	long iYLineIncrement;
	short iMaxPrintPosition = iPageLength - iTopMargin - iBottomMargin;

	TEXTMETRIC ThisTextMetrics;
	pDC->GetTextMetrics( &ThisTextMetrics);

	iYLineIncrement = ThisTextMetrics.tmHeight; 

	POSITION			posElement;
	POSITION			posHit;
	int					nHitCount, i, count;
	// Get app for version number
	COD3App				*app = (COD3App*)AfxGetApp();
	SYSTEMTIME			sysTime;
	CDaoAccOffset		daoOffset(pDoc->m_pProjectSettings->m_pDB);

	// Get time and date
	GetSystemTime(&sysTime);

	// Set string for footer
	date.Format("%i/%i/%i", sysTime.wDay, sysTime.wMonth, sysTime.wYear);
	
	// Create header for new item
	iYPosition = iTopMargin;
	nPageCounter = 1;
	CString csLine = m_pItem->GetProdLineLabel();

	wsprintf((LPSTR) szBuffer, "----------------------- %s Production Schedule -----------------------",csLine);
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);

	// Increment line position by two
	iYPosition += iYLineIncrement;	
	iYPosition += iYLineIncrement;

	posElement = m_pItem->m_tplElementList.GetHeadPosition();

	iPartIndex = 0;
			
	while (posElement)
	{
		// Set the element pointer
		pElement = m_pItem->m_tplElementList.GetNext(posElement);

		// Clear single print flag
		singlePrint=-1;

		// Are we printing one element
		if(!(count = pDoc->m_printSelArr.GetSize()))
		{
			singlePrint=0;
		}
		else
		{
			for(i=0; i<count; i++)
			{
				if((singlePrint = pDoc->m_printSelArr.GetAt(i).CompareNoCase(pElement->GetMark()))==0)
					break;
			}
		}

		if(singlePrint==0)
		{
			pBeam = (CBeamElement*)pElement;

			if(m_pItem->IsBeam())
				nHitCount = pBeam->m_tplPrintHitList.GetCount();
			else
				nHitCount = 0;

			++iPartIndex;

			// will details fit on this page ?
			int	 nMinSpace = (nHitCount + 14)*iYLineIncrement;
			//nrc 
			if(iYPosition > iMaxPrintPosition - nMinSpace)
			{
			//	 Add software version and date to print output
			//	 force new page
			 szText.Format(IDS_PRINTFOOT, app->m_sAppVer, sItemID, nPageCounter, date);
				pDC->TextOut((iTabMarginOne + iTabMarginTwo)/4,(iMaxPrintPosition - iYLineIncrement),szText.GetBuffer(szText.GetLength()));

				int nRetValue = pDC->EndPage();
				if (nRetValue < 0)
				{
					CString csMsg;
					switch (nRetValue)
					{
						case SP_ERROR:
							csMsg = "General Error";
							break;
						case SP_APPABORT:
							csMsg = "Job was ended because the application’s abort function returned 0.";
							break;
						case SP_USERABORT:
							csMsg = "User ended the job through Print Manager.";
							break;
					case SP_OUTOFDISK:
							csMsg = "Not enough disk space is currently available for spooling, and no more space will become available.";
							break;
						case SP_OUTOFMEMORY:
							csMsg = "Not enough memory is available for spooling. ";
						break;
					}
					AfxMessageBox(csMsg);
				}
				
				pDC->StartPage();
				nPageCounter++;
				iYPosition = iTopMargin;
					
			//	 Create new page header 
				wsprintf((LPSTR) szBuffer, "-------------------- %s Production Schedule (cont'd) -------------------", csLine);
				szText = szBuffer;
				pDC->TextOut(iLeftMargin,iYPosition,szText);

				iYPosition += iYLineIncrement; 
				iYPosition += iYLineIncrement;
			}

			// Display Project Filename	and Item No.	
			CString sProjectName;
			sProjectName = pDoc->m_pProjectHeader->m_sProjectName;
			sProjectName += ".od3";

			wsprintf((LPSTR) szBuffer,"Project File: %s",sProjectName); 
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			int nItemID = m_pItem->m_nItemID;
			sItemID.Format("%d",nItemID);
			if (nItemID < 10){sItemID = "0" + sItemID;}
			wsprintf((LPSTR) szBuffer,"Item No.: %s",sItemID); 
			szText = szBuffer;
			pDC->TextOut(iCenterTabMargin, iYPosition, szText);

			iYPosition += iYLineIncrement; 

			// Display Filename 
			CString szPartFileName;
			if(!lstrcmpi(csLine, "Line_1"))
			{
				Line1.GetPartFileName( &szPartFileName, sItemID );
			}
			else
			{
				sItemID.Format("%d",nItemID);
				if (nItemID > 9 && nItemID < 100)
				{
					sItemID = "0" + sItemID;
				}
				if (nItemID < 10)
				{
					sItemID = "00" + sItemID;
				}

				if(!lstrcmpi(csLine, "Line_2"))
				{
					Line2.GetPartFileName( &szPartFileName, sItemID, iPartIndex );
				}
				else if(!lstrcmpi(csLine, "Line_3"))
				{
					Line3.GetPartFileName( &szPartFileName, sItemID );
				}
				else if(!csLine.CompareNoCase(_T("Diagonal_Brace")))
				{
					// Get the file name
					int iPos;

					// Get the path and file name
					szPartFileName = pDoc->createAccFileName(m_pItem->GetItemID());

					// Extract the file name
					iPos = szPartFileName.ReverseFind('\\');
					szPartFileName = szPartFileName.Mid(iPos+1);
				}
			}

			wsprintf((LPSTR) szBuffer,"Filename: %s",szPartFileName); 
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			iYPosition += iYLineIncrement; 

			// Display Order Number & part sequence number
			wsprintf((LPSTR) szBuffer, "Order Number: %s", pDoc->m_pProjectHeader->m_sProjectName);
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			wsprintf((LPSTR) szBuffer, "Part: %d",iPartIndex);
			szText = szBuffer;
			pDC->TextOut(iCenterTabMargin, iYPosition, szText);

			iYPosition += iYLineIncrement; 

			// Display Section Size and Mark No.
			CString szTempSection = m_pItem->GetProfile();

			wsprintf((LPSTR) szBuffer, "Section Size: %s", szTempSection );
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);			

			wsprintf((LPSTR) szBuffer, "Mark Number: %s",pElement->GetMark());
			szText = szBuffer;
			pDC->TextOut(iCenterTabMargin, iYPosition, szText);
				
			iYPosition += iYLineIncrement; 

			// Display Quantity and bundle count
			wsprintf((LPSTR) szBuffer, "Quantity Required: %d", pElement->GetQty());
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			wsprintf((LPSTR) szBuffer, "Bundle Count: %d", pBeam->GetBundle());
			szText = szBuffer;
			pDC->TextOut(iCenterTabMargin, iYPosition, szText);

			iYPosition += iYLineIncrement;

			// Display SPC and member type
			wsprintf((LPSTR) szBuffer, "SPC: %s",pBeam->GetSPCode()); 
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			wsprintf((LPSTR) szBuffer, "Type: %d", pBeam->GetMemberType());
			szText = szBuffer;
			pDC->TextOut(iCenterTabMargin, iYPosition, szText);

			// Increment line position by two	
			iYPosition += iYLineIncrement;	
			iYPosition += iYLineIncrement;

			if (pBeam->m_tplPrintHitList.IsEmpty() || !m_pItem->IsBeam())
			{
				int iOffset=0;

				// Determine text to print
				if(!m_pItem->IsBeam())
				{
					iOffset=iTabMarginOne-iLeftMargin;
					szText.Format("Product type: %s",m_pItem->GetProductName());
				}
				else
				{
					// Standard beam text
					szText = "Unpunched Length";
				}

				pDC->TextOut(iTabMarginOne-iOffset, iYPosition, szText);
				iYPosition += iYLineIncrement;
				iYPosition += iYLineIncrement;
			}
			else 
			{
				szText = "Operation1:";
				pDC->TextOut(iLeftMargin, iYPosition, szText);

				szText = "Position:";
				pDC->TextOut(iTabMarginOne, iYPosition, szText);

				szText = "Punch:";
				pDC->TextOut(iTabMarginTwo, iYPosition, szText);

				iYPosition += iYLineIncrement;
				iYPosition += iYLineIncrement;

				posHit = pBeam->m_tplPrintHitList.GetHeadPosition();
				iHitCounter = 0;

				while(posHit)
				{
			

					pOperation =(CHole*)pBeam->m_tplPrintHitList.GetNext(posHit);
					++iHitCounter;
					
					//NRC Test
					if(iHitCounter==51||iHitCounter==101||iHitCounter==151||iHitCounter==201||iHitCounter==251||iHitCounter==301)
  					{
						wsprintf((LPSTR) szBuffer,"-------------------------------------------------------------------");
						szText = szBuffer;
						pDC->TextOut(iLeftMargin, iYPosition, szText);

						iYPosition += iYLineIncrement;
						iYPosition += iYLineIncrement;
					
					//	wsprintf((LPSTR) szBuffer, app->m_sAppVer, sItemID, nPageCounter, date);
					//	szText = szBuffer;
					//	pDC->TextOut(iLeftMargin, iYPosition, szText);
						szText.Format(IDS_PRINTFOOT, app->m_sAppVer, sItemID, nPageCounter, date);
						pDC->TextOut((iTabMarginOne + iTabMarginTwo)/4,(iMaxPrintPosition - iYLineIncrement),szText.GetBuffer(szText.GetLength()));
						
						int nRetValue = pDC->EndPage();
					
						nPageCounter++;
						iYPosition = iTopMargin;
					
						// Create new page header 
						wsprintf((LPSTR) szBuffer, "-------------------- %s Production Schedule (cont'd) -------------------", csLine);
						szText = szBuffer;
						pDC->TextOut(iLeftMargin,iYPosition,szText);
	
						iYPosition += iYLineIncrement; 
						iYPosition += iYLineIncrement;
					}	
			
					
					//end of NRC test

	

					wsprintf((LPSTR) szBuffer,"%i", iHitCounter);
					szText = szBuffer;
					pDC->TextOut(iLeftMargin, iYPosition, szText);

					wsprintf((LPSTR) szBuffer,"%i", pOperation->GetPosX());
					szText = szBuffer;
					pDC->TextOut(iTabMarginOne, iYPosition, szText);
		
					wsprintf((LPSTR) szBuffer,"%i", pOperation->GetPunch());
					szText = szBuffer;
					pDC->TextOut(iTabMarginTwo, iYPosition, szText);
					
					iYPosition += iYLineIncrement;			
				}
					
				iYPosition += iYLineIncrement;
				iYPosition += iYLineIncrement;
			}
			

			if(m_pItem->IsBeam())
			{
				nRunLength = ((double)pBeam->GetLength())/1000 * pElement->GetQty();
			}
			else
			{
				CAccessoryElement *pAcc=NULL;
				
				// Set search criteria
				daoOffset.m_prod_code = m_pItem->GetProductCode();

				// Open the recordset
				daoOffset.Open();

				if(daoOffset.GetRecordCount() > 0)
				{
					// Set offset
					iAccOffset = (int)daoOffset.m_offset;
					// Close recordaset
					daoOffset.Close();
				}
				else
				{
					iAccOffset = 0;
				}

				pAcc=(CAccessoryElement *)pBeam;
				nRunLength = ((double)(pAcc->GetLength()+iAccOffset))/1000 * pElement->GetQty();
			}

			nItemLength += nRunLength;

			nRunWeight = (nRunLength * m_pItem->GetProductWeight()) / 1000; // Tonnage
			nItemWeight += nRunWeight;

			sprintf( szBuffer,"Part Run Length: %.3lf (Metres) --> %.3lf (Tonnes)",
				(double)nRunLength,
				(double)nRunWeight);
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			iYPosition += iYLineIncrement;

			sprintf( szBuffer,"Cumulative Run Length for this Item: %.3lf (Metres) --> %.3lf (Tonnes)",
				(double)nItemLength,
				(double)nItemWeight);
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			iYPosition += iYLineIncrement;
			iYPosition += iYLineIncrement;

			// Creating separator for next Part
			wsprintf((LPSTR) szBuffer,"-------------------------------------------------------------------");
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			iYPosition += iYLineIncrement;
			iYPosition += iYLineIncrement;
		}

	}
	//  Print page number on last page of item listing
	szText.Format(IDS_PRINTFOOT, app->m_sAppVer, sItemID, nPageCounter, date);
	pDC->TextOut((iTabMarginOne + iTabMarginTwo)/4,(iMaxPrintPosition - iYLineIncrement),szText.GetBuffer(szText.GetLength()));

	// End Page at end of item
	
		int nRetValue = pDC->EndPage();
		if (nRetValue <= 0)
		{
			CString csMsg;
			switch (nRetValue)
			{
			case SP_ERROR:
			csMsg = "General Error";
				break;
			case SP_APPABORT:
				csMsg = "Job was ended because the application’s abort function returned 0.";
				break;
			case SP_USERABORT:
				csMsg = "User ended the job through Print Manager.";
				break;
		case SP_OUTOFDISK:
			csMsg = "Not enough disk space is currently available for spooling, and no more space will become available.";
				break;
		case SP_OUTOFMEMORY:
				csMsg = "Not enough memory is available for spooling. ";
				break;
		}
		AfxMessageBox(csMsg);
	}
	
	
	if(pInfo->m_strPageDesc.Compare("Selection Print") != 0)
	pDC->StartPage();


return;
}


////////////////////////////////////////////////////////////////////////////
// Print Accessory Details
//
void CLeftView::PrintAccessoryDetails(CDC* pDC, CPrintInfo* pInfo)
{
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CItem*			pItem;

	int m_ElementCount;
	int m_Counter;
	int iHitCounter;
	int m_PageCounter;
	int m_DisplayCounter;
	CString szText;
	CString szDocTitle;
	char szBuffer[256];
	short iLeftMargin = 150;
	short iTopMargin = 100;
	short iBottomMargin = 150;
	short iCenterTabMargin = pDC->GetDeviceCaps(HORZRES)/2;
	short iTabMarginOne = 500;
	short iTabMarginTwo = 1100;
	short iTabMarginThree = 1600;
	short iTabMarginFour = 3150;
	short iPageLength = pDC->GetDeviceCaps(VERTRES);
	long iYPosition = iTopMargin;
	short iMaxPrintPosition = iPageLength - iTopMargin - iBottomMargin;
	long iYLineIncrement;
	TEXTMETRIC ThisTextMetrics;
	pDC->GetTextMetrics( &ThisTextMetrics);
	iYLineIncrement = ThisTextMetrics.tmHeight; 
	POSITION posElement;
	POSITION posItem;
	 
	// Creating header for Part
	wsprintf((LPSTR) szBuffer, "-------------------------------------------------------------------");
	szText = szBuffer;			
	pDC->TextOut(iLeftMargin, iYPosition, szText);	

	iYPosition += iYLineIncrement;	

	wsprintf((LPSTR) szBuffer, "                             Job Sheet                             ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);	

	iYPosition += iYLineIncrement;

	wsprintf((LPSTR) szBuffer, "                  Ayrshire Metal Products Daventry                 ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);	

	iYPosition += iYLineIncrement;	

	wsprintf((LPSTR) szBuffer, "-------------------------------------------------------------------");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);	

	iYPosition += iYLineIncrement;	

	// Display SPC on the screen with its data
	wsprintf((LPSTR) szBuffer, "Date: ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);

	// Display SPC on the screen with its data
	wsprintf((LPSTR) szBuffer, "Page: ");
	szText = szBuffer;
	pDC->TextOut(3400, iYPosition, szText);

	iYPosition += iYLineIncrement;
	iYPosition += iYLineIncrement;

	// Display Filename and its data on the screen	
	wsprintf((LPSTR) szBuffer, "Filename: ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);

	posItem = pDoc->m_tplItemList.GetHeadPosition();
		
	m_PageCounter = 2;
	m_DisplayCounter = 0;

	pItem = pDoc->m_tplItemList.GetNext(posItem); 
	posElement = pItem->m_tplElementList.GetHeadPosition();

	m_Counter = 1;
	m_ElementCount = pItem->m_tplElementList.GetCount();
			
	// Only 2 parts should appear on one page
/*	if(m_DisplayCounter == m_PageCounter)
	{
		pDC->EndPage();
		pDC->StartPage();	

		m_PageCounter = m_PageCounter + 2;

		iYPosition = iTopMargin;
	}
*/
//	pElement = pItem->m_tplElementList.GetNext(posElement);
			
	// Increment line position by one
	iYPosition += iYLineIncrement; 

	// Display Section Size on the screen with its data
	wsprintf((LPSTR) szBuffer, "Job Number: ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);			
	
	// Increment line position by one
	iYPosition += iYLineIncrement; 

	// Display Section Size on the screen with its data
	wsprintf((LPSTR) szBuffer, "Customer Order: ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);	

	// Display Mark Number on the screen with its data
	wsprintf((LPSTR) szBuffer, "Copy: ");//,m_Counter);
	szText = szBuffer;
	pDC->TextOut(3075, iYPosition, szText);
		
	wsprintf((LPSTR) szBuffer, "of ");//,m_ElementCount);
	szText = szBuffer;
	pDC->TextOut(3550, iYPosition, szText);

	// Increment line position by two
	iYPosition += iYLineIncrement; 
	iYPosition += iYLineIncrement; 

	// Display Mark Number on the screen with its data
	wsprintf((LPSTR) szBuffer, "Order Date: ");
	szText = szBuffer;
	pDC->TextOut(iCenterTabMargin, iYPosition, szText);

	iYPosition += iYLineIncrement; 

	// Display Mark Number on the screen with its data
	wsprintf((LPSTR) szBuffer, "Completed Date: ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);

	// Display Mark Number on the screen with its data
	wsprintf((LPSTR) szBuffer, "Customer Code: ");
	szText = szBuffer;
	pDC->TextOut(iCenterTabMargin, iYPosition, szText);

	iYPosition += iYLineIncrement; 

	// Display Mark Number on the screen with its data
	wsprintf((LPSTR) szBuffer, "Customer Name: ");
	szText = szBuffer;
	pDC->TextOut(iCenterTabMargin, iYPosition, szText);

	// Increment line position by one
	iYPosition += iYLineIncrement; 
	iYPosition += iYLineIncrement; 

	// Display Order Number on the screen and its data
	wsprintf((LPSTR) szBuffer, "Product: ");// pDoc->m_pProjectHeader->m_sCustomerRef);
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);

	wsprintf((LPSTR) szBuffer, "Item: ");//,m_Counter);
	szText = szBuffer;
	pDC->TextOut(3400, iYPosition, szText);

//	wsprintf((LPSTR) szBuffer, "of %d",m_ElementCount);
//	szText = szBuffer;
//	pDC->TextOut(3900, iYPosition, szText);


	// Increment line position by two	
	iYPosition += iYLineIncrement;	
	iYPosition += iYLineIncrement;

//	if (pBeam->m_tplHitList.IsEmpty())
//	{}
//	else
//	{
		wsprintf((LPSTR) szBuffer,"-------------------------------------------------------------------");
		szText = szBuffer;
		pDC->TextOut(iLeftMargin, iYPosition, szText);

		// Increment line position by one
		iYPosition += iYLineIncrement;

		szText = "Mark";
		pDC->TextOut(iLeftMargin, iYPosition, szText);

		szText = "Quantity";
		pDC->TextOut(iTabMarginOne, iYPosition, szText);

		szText = "Length";
		pDC->TextOut(iTabMarginTwo, iYPosition, szText);

		szText = "Remarks";
		pDC->TextOut(iTabMarginThree, iYPosition, szText);

		szText = "Cum Length (M)";
		pDC->TextOut(iTabMarginFour, iYPosition, szText);

		// Increment line position by one
		iYPosition += iYLineIncrement;

		iHitCounter = 1;

		wsprintf((LPSTR) szBuffer,"-------------------------------------------------------------------");
		szText = szBuffer;
		pDC->TextOut(iLeftMargin, iYPosition, szText);

		iYPosition += iYLineIncrement;
/*
		while(posHit)
		{
			pOperation =(CHole*)pBeam->m_tplHitList.GetNext(posHit);

			wsprintf((LPSTR) szBuffer,"%i", iHitCounter);
			szText = szBuffer;
			pDC->TextOut(iLeftMargin, iYPosition, szText);

			wsprintf((LPSTR) szBuffer,"%i", pOperation->GetPosX());
			szText = szBuffer;
			pDC->TextOut(iTabMarginOne, iYPosition, szText);
	
			wsprintf((LPSTR) szBuffer,"%i", pOperation->GetPunch());
			szText = szBuffer;
			pDC->TextOut(iTabMarginTwo, iYPosition, szText);
				
			iHitCounter = iHitCounter + 1;

			iYPosition += iYLineIncrement;
		}
*/				
//		wsprintf((LPSTR) szBuffer,"--------------------------------------------");
//		szText = szBuffer;
//		pDC->TextOut(iLeftMargin, iYPosition, szText);

//		iYPosition += iYLineIncrement;
		iYPosition += iYLineIncrement;
//	}

	wsprintf((LPSTR) szBuffer,"Total Length (Metres): ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);
	
	iYPosition += iYLineIncrement;

	wsprintf((LPSTR) szBuffer,"Total Weight (Kilos): ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);
			
	iYPosition += iYLineIncrement;
	iYPosition += iYLineIncrement;

	wsprintf((LPSTR) szBuffer,"Bundle Number: ");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);
	
	iYPosition += iYLineIncrement;

	wsprintf((LPSTR) szBuffer,"-------------------------------------------------------------------");
	szText = szBuffer;
	pDC->TextOut(iLeftMargin, iYPosition, szText);

	m_Counter = m_Counter + 1;
	m_DisplayCounter = m_DisplayCounter + 1;
}


void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM		hItem=NULL;
	CTreeCtrl&		mainTree = GetTreeCtrl();
	CItem			*pItem=NULL;
	TVITEM			item;

	// Get the selected tree item
	if(hItem=mainTree.GetSelectedItem())
	{
		CWnd* pWnd = this->GetNextWindow();
		COD3View* pView = DYNAMIC_DOWNCAST(COD3View, pWnd);

		if(m_pLastItem)
		{
			item.mask = TVIF_PARAM|TVIF_SELECTEDIMAGE;
			item.hItem = m_pLastItem;

			// Get the item
			mainTree.GetItem(&item);

			if(item.lParam==ISBEAM)
			{
				item.iSelectedImage = 3;
			}
			else if(item.lParam==ISACCESSORY)
			{
				item.iSelectedImage = 5;
			}

			mainTree.SetItem(&item);
		}

		// Set the item structure
		item.mask = TVIF_PARAM|TVIF_SELECTEDIMAGE;
		m_pLastItem=item.hItem = hItem;
		// Get the item
		mainTree.GetItem(&item);

		// Beam or accessory picked
		if(item.lParam==ISBEAM)
		{
			// Get the beam item
			if(GetItemPointer())
			{
				// Set pointer value for displaying
				pItem = this->m_pItem;
			}
			else
			{
				// Clear pointer
				m_pItem = NULL;
			}
		}
		else if(item.lParam==ISACCESSORY)
		{
			// Get the accessory item
			if(GetAccItemPtr(hItem))
			{
				// Set pointer value for displaying
				pItem = this->m_pItem;
			}
			else
			{
				// Clear pointer
				m_pItem = NULL;
			}
		}
		else
		{
			// Clear pointer
			m_pItem = NULL;
		}

		// Change the selected image
		if(m_pItem && this->m_iPrintStatus==1)
		{
			// Set image number
			item.iSelectedImage = 8;
			mainTree.SetItem(&item);
		}
		// Display elements in listview control
		pView->DisplayElements(m_pItem);
	}
	
	*pResult = 0;
}

void CLeftView::OnUpdateDumpSetreporttypeAllitems(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);

	if(m_iPrintStatus == 2)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);

	return;
}

void CLeftView::OnUpdateItemPrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_iPrintStatus == 1)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);

	return;
}

void CLeftView::OnDumpSetreporttypeAllitems() 
{
	// TODO: Add your command handler code here
	TVITEM		item;
	CTreeCtrl&	tree=GetTreeCtrl();

	m_iPrintStatus = 2;

	// Set the item structure
	item.mask = TVIF_SELECTEDIMAGE|TVIF_IMAGE;
	item.hItem = tree.GetSelectedItem();

	// Get the item
	tree.GetItem(&item);

	// Only change the image if a beam or accessory
	if(item.iImage==2 || item.iImage==4)
	{
		// Change to standard image
		item.iSelectedImage = item.iImage;
		tree.SetItem(&item);
	}

	return;
}

void CLeftView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(pTVKeyDown->flags & VK_CONTROL && pTVKeyDown->wVKey == VK_DELETE)
	{
		// Delete selected elements
		OnItemDelete();
	}

	*pResult = 0;
}

void CLeftView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	COD3Doc		*pDoc = GetDocument();
	CMainFrame	*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	CString		dPath;
	CDC			*draw=NULL;
	UINT		nID, nStyle;
	int			cxWidth;
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

	CTreeView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CLeftView::OnAdvancedMode() 
{
	// TODO: Add your command handler code here

	// Toggle flag
	m_mode = !m_mode;

	// Redraw window
	OnUpdate(this, 0, NULL);
	
}

void CLeftView::OnUpdateAdvancedMode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_mode)
		pCmdUI->SetCheck(true);
}

void CLeftView::OnValSelection() 
{
	// TODO: Add your command handler code here
	COD3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CItem		*pItem=NULL;
	POSITION	pos;
	
	// Get head position
	pos = pDoc->m_tplItemList.GetHeadPosition();

	while(pos)
	{
		// Get item from the list
		pItem = pDoc->m_tplItemList.GetNext(pos);

		// Test item against treeview checkbox status
		if(testCheckBox(pItem, ISBEAM))
			pDoc->ValidateItem(pItem);
	}

	// Get head position for the accessories
	pos = pDoc->m_tplAccItemList.GetHeadPosition();

	while(pos)
	{
		// Get item from the list
		pItem = pDoc->m_tplAccItemList.GetNext(pos);

		// Test item against treeview checkbox status
		if(testCheckBox(pItem, ISACCESSORY))
			pDoc->ValidateAccItem(pItem);
	}
}

void CLeftView::OnUpdateValSelection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_mode)
		pCmdUI->Enable(false);
	
}

void CLeftView::OnGenSelection() 
{
	// TODO: Add your command handler code here
	CMainFrame	*pMainFrm=DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	COD3Doc		*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CItem		*pItem=NULL;
	POSITION	pos;
	bool		generated=true;
	
	// Get head position
	pos = pDoc->m_tplItemList.GetHeadPosition();

	while(pos)
	{
		// Get item from the list
		pItem = pDoc->m_tplItemList.GetNext(pos);

		// Test item against treeview checkbox status
		if(testCheckBox(pItem, ISBEAM))
		{
			// Validate before generatng
			if(pDoc->ValidateItem(pItem))
			{
				// Generate selected item
				if(!pDoc->GenerateItem(pItem))
					generated=false;
			}
		}
	}

	// Loop the accessories
	// Get head position
	pos = pDoc->m_tplAccItemList.GetHeadPosition();

	while(pos)
	{
		// Get item from the list
		pItem = pDoc->m_tplAccItemList.GetNext(pos);

		// Test item against treeview checkbox status
		if(testCheckBox(pItem, ISACCESSORY))
		{			
			// Generate accessory
			if(!pDoc->GenerateAccItem(pItem))
			{
				// Set flag
				generated = false;	
			}
		}
	}

	// Remove progress bar
	if(pMainFrm->m_bProgCreated)
	{
		pMainFrm->m_bProgCreated = false;
		pMainFrm->m_progressBar.DestroyWindow();
	}

	if(generated)
	{
		pDoc->m_bIsGenerated = true;
		CDlgMessage msg(NULL, "Output Generated");

		msg.DoModal();
	}
}

void CLeftView::OnUpdateGenSelection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_mode)
		pCmdUI->Enable(false);
	
}

void CLeftView::OnRepSelection() 
{
	// TODO: Add your command handler code here
	COD3Doc		*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CItem		*pItem=NULL;
	POSITION	pos;
	CPrintDialog	print(false);
	DOCINFO			docInfo;



	if(countSelection() > 0)
	{
		// Open common print dialog
		if(print.DoModal()==IDOK)
		{
			// Get the printer device
			CDC	pDC;
			CPrintInfo	printInfo;
			HDC dc = print.GetPrinterDC();

			pDC.Attach(dc);
			// Clean struct
			ZeroMemory(&docInfo, sizeof(DOCINFO));

			// Set up printing structure
			docInfo.cbSize=sizeof(DOCINFO);
			docInfo.lpszDocName = "Selection Print";
			docInfo.lpszOutput = NULL;
			docInfo.fwType = NULL;

			printInfo.m_strPageDesc = "Selection Print";
			printInfo.m_bPreview = 0;
			printInfo.m_nNumPreviewPages = 1;

			// Get head position
			pos = pDoc->m_tplItemList.GetHeadPosition();

			while(pos)
			{
				// Get item from the list
				pItem = pDoc->m_tplItemList.GetNext(pos);

				// Test item against treeview checkbox status
				if(testCheckBox(pItem, ISBEAM))
				{
					// Start the document
					StartDoc(dc, &docInfo);

					// Set member pointer for printing
					m_pItem = pItem;

					// Print item
					PrintItem(&pDC, &printInfo);

					// End print job
					EndDoc(dc);	
				}
			}

			// Get head position for the accessories
			pos = pDoc->m_tplAccItemList.GetHeadPosition();

			while(pos)
			{
				// Get item from the list
				pItem = pDoc->m_tplAccItemList.GetNext(pos);

				// Test item against treeview checkbox status
				if(testCheckBox(pItem, ISACCESSORY))
				{
					// Start the document
					StartDoc(dc, &docInfo);

					// Set member pointer for printing
					m_pItem = pItem;

					// Print item
					PrintItem(&pDC, &printInfo);

					// End print job
					EndDoc(dc);	
				}
			}
			// Release DC
			pDC.Detach();
		}
	}

	return;
}

void CLeftView::OnUpdateRepSelection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_mode)
		pCmdUI->Enable(false);
	
}

void CLeftView::OnTranSelection() 
{
	// TODO: Add your command handler code here
	COD3Doc		*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CItem		*pItem=NULL;
	POSITION	pos;
	CString		sText, sID;

	// Get head position
	pos = pDoc->m_tplItemList.GetHeadPosition();

	while(pos)
	{
		// Get item from the list
		pItem = pDoc->m_tplItemList.GetNext(pos);

		// Test item against treeview checkbox status
		if(testCheckBox(pItem, ISBEAM))
		{
			// Transfer data to disk
			if(pDoc->TransferItem(pItem))
			{
				// Create the ink jet file
				if(pDoc->writeInkJetFile(pItem))
				{
					// Create user information string
					sID.Format("_%i", pItem->GetItemID());
					sText.Format("Transfer complete for item %i\nInkjet file created and saved to A:\\%s.ink",
									pItem->m_nItemID, pDoc->m_pProjectHeader->m_sProjectName+sID);
				}
				else
				{
					// Create user information string
					sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
				}

				// Inform user
				AfxMessageBox(sText, MB_ICONINFORMATION);
			}
		}
	}

	// Get head position for the ccessories
	pos = pDoc->m_tplAccItemList.GetHeadPosition();

	while(pos)
	{
		// Get item from the list
		pItem = pDoc->m_tplAccItemList.GetNext(pos);

		// Test item against treeview checkbox status
		if(testCheckBox(pItem, ISACCESSORY))
		{
			// Transfer data to disk
			if(pDoc->TransferItem(pItem))
			{
				// Create the ink jet file
				if(pDoc->writeInkJetFile(pItem))
				{
					// Create user information string
					sID.Format("_%i", pItem->GetItemID());
					sText.Format("Transfer complete for item %i\nInkjet file created and saved to A:\\%s.ink",
									pItem->m_nItemID, pDoc->m_pProjectHeader->m_sProjectName+sID);
				}
				else
				{
					// Create user information string
					sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
				}

				// Inform user
				AfxMessageBox(sText, MB_ICONINFORMATION);
			}
		}
	}

}

void CLeftView::OnUpdateTranSelection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_mode)
		pCmdUI->Enable(false);
	
}

bool CLeftView::testCheckBox(CItem *pItem, int iType)
{
	COD3Doc		*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	bool		result=false;
	HTREEITEM	hTreeItem;
	CTreeCtrl&	treeCtrl=GetTreeCtrl();
	CString		product;
	int			strPos, nItemID;
	POSITION	pos;
	TVITEM		item;


	// Get root item
	hTreeItem = treeCtrl.GetNextItem(NULL, TVGN_ROOT);
	// Get the next child item
	hTreeItem = treeCtrl.GetNextItem(hTreeItem, TVGN_CHILD);

	while(hTreeItem && !result)
	{
		// Test if the item is selected
		if(treeCtrl.GetCheck(hTreeItem))
		{
			// Set the item structure
			item.mask = TVIF_PARAM;
			item.hItem = hTreeItem;
			// Get the item
			treeCtrl.GetItem(&item);

			// Get the item text
			product = treeCtrl.GetItemText(hTreeItem);

			// Break up the string
			strPos = product.Find(":");
			product = product.Mid(4, (strPos-4));

			// Get item number
			nItemID = atoi(product);

			// Find beam item pointer
			pos = pDoc->m_tplItemList.GetHeadPosition();
							

			// Test pointer ID number against removal ID
			if(nItemID == pItem->GetItemID() && item.lParam == iType)
			{
				result=true;
				break;
			}
		}
		// Get the next item
		hTreeItem = treeCtrl.GetNextItem(hTreeItem, TVGN_NEXT);
	}


	return(result);
}


int CLeftView::countSelection()
{
	HTREEITEM	hTreeItem;
	int			selCount=0;
	CTreeCtrl&	treeCtrl=GetTreeCtrl();


	// Get root item
	hTreeItem = treeCtrl.GetNextItem(NULL, TVGN_ROOT);
	// Get the next child item
	hTreeItem = treeCtrl.GetNextItem(hTreeItem, TVGN_CHILD);

	// Perfrom a quick loop to test selection count
	while(hTreeItem)
	{
		// Test if the item is selected for removal
		if(treeCtrl.GetCheck(hTreeItem))
			selCount++;

		// Get the next item
		hTreeItem = treeCtrl.GetNextItem(hTreeItem, TVGN_NEXT);
	}

	return(selCount);
}

void CLeftView::setParentState()
{
	unsigned int	uFlags = 0;
	HTREEITEM		hitTest=NULL, parent=NULL, child=NULL;
	CTreeCtrl&		refMainTree = GetTreeCtrl();
	CPoint			point;
	bool			state=false;

	// If advanced
	if(m_mode)
	{
		// Get mouse pointer pos
		GetCursorPos(&point);
		// Convert to view coords
		ScreenToClient(&point);

		// Perform pos hit test with flags
		if(hitTest = refMainTree.HitTest(point, &uFlags))
		{
			if(!refMainTree.ItemHasChildren(hitTest) && 
				hitTest != refMainTree.GetRootItem() )
			{
				// Get the parent and set the state
				parent = refMainTree.GetParentItem(hitTest);

				// Get first child item
				child = refMainTree.GetChildItem(parent);

				// Loop all children testing states
				while(child)
				{
					// Test the state of the checkbox
					if(refMainTree.GetCheck(child))
					{
						// Set state flag
						state = true;
						// Dont need to test any more
						break;
					}
					// Get the next child
					child = refMainTree.GetNextSiblingItem(child);
				}

				// Set the state of the parent
				refMainTree.SetCheck(parent, state);
			}
		}
	}


	return;
}

void CLeftView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	// Click a child, activate the parent
	setParentState();
	
	CTreeView::OnLButtonUp(nFlags, point);
}

bool CLeftView::GetAccItemPtr(HTREEITEM hItem)
{
	
	CTreeCtrl& refMainTree = GetTreeCtrl();

	CItem		*pItem=NULL;
	COD3Doc		*pDoc = GetDocument();
	bool		bResult=false;
	CString		sItemID;
	CString		sText;
	CString		sTemp;
	int			cChar;
	int			nItemID;

	// Set the selected item text to string variable
	sText = refMainTree.GetItemText(hItem);

	// Manipulate item text to get nItemID
	sTemp = sText.Right(sText.GetLength()-5);
	cChar = sTemp.Find(":",0);
	sItemID = sTemp.Left(cChar);
	nItemID = atoi(sItemID);

	// Search ItemList to get pointer to matching CItem object
	POSITION pos;

	// Get the head position of the accessory item
	pos = pDoc->m_tplAccItemList.GetHeadPosition();

	while(pos)
	{
		// Get the next item object
		pItem = pDoc->m_tplItemList.GetNext(pos);

		// Test the ID number
		if(nItemID == pItem->GetItemID())
		{
			// Set the member variable
			m_pItem = pItem;
			// Set flag
			bResult=true;
			// Exit loop
			break;
		}
	}


	return(bResult);
}


void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu			menubar;
	CPoint			point;
	CTreeCtrl&		tree=GetTreeCtrl();
	unsigned int	uFlags=0;
	HTREEITEM		hitTest;

	// Get the cursor position
	GetCursorPos(&point);

	// Convert the coords
	ScreenToClient(&point);

	// Perform pos hit test with flags
	hitTest = tree.HitTest(point, &uFlags);

	// Get and display item if on label and an item has been hit
	if(hitTest && uFlags & TVHT_ONITEM)
	{
		// Select the item under the mouse pointer
		tree.SelectItem(hitTest);
	}

	if (menubar.LoadMenu(IDR_LEFTPOPUP))
	{
		// debug menu is the first popup
		CMenu* pPopup = menubar.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		ClientToScreen(&point); // not used in retail build

		// route commands through the mainframe for command ui events
		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, 
									AfxGetApp()->GetMainWnd());
	}

	*pResult = 0;
}


