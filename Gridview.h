/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1998 McRae Software International, Inc.
//
//	Warning:  This computer program and source code  is  protected by copyright law and
//	international treaties and is the property of McRae Software International, Inc.
//  Unauthorized reproduction or distribution of this program
//	or source,  may result in severe civil and criminal penalties, and will be prosecuted 
//	to the maximum extent possible under law.
/////////////////////////////////////////////////////////////////////////////
// gridview.h : header file
//
#ifndef __GRIDVIEW
#define __GRIDVIEW


#ifdef _MAC
#undef AFX_EXT_API
#undef AFX_EXT_CLASS
#define AFX_EXT_API
#define AFX_EXT_CLASS
#endif

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

#define GW_EXT_CLASS

#ifdef _WIN32
	#ifdef _GWDLLIMP
		#undef GW_EXT_CLASS
		#define GW_EXT_CLASS __declspec(dllimport)
	#else
		#ifdef _GWEXTDLL
			#undef GW_EXT_CLASS
			#define GW_EXT_CLASS AFX_EXT_CLASS
		#endif	
	#endif
#else //_WIN32
	#ifdef _GWEXTDLL
		#undef AFXAPP_DATA
		#define AFXAPP_DATA AFXAPI_DATA
	#endif //_WIN32
#endif

//*********************************************************************************************************************
// class CGWGridView : public CView, public CGWGrid

class CGWGridCellObject;
class GW_EXT_CLASS CGWGridView : public CView, public CGWGrid
{

//GW_CLASS{{(CGWGridView)
/*

Implementing CGWGridView and CGWTabGridView derived classes are very similar to using any other CView derived class. 
The easiest way to use a either of these classes is to replace the CView class in your applications document template 
with a class derived from CGWGridView or CGWTabGridView as shown below: 

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_EDITTYPE,
		RUNTIME_CLASS(CEditDoc),
		RUNTIME_CLASS(CEditSplitter),        // standard MDI child frame
		RUNTIME_CLASS(CMyGridView));    //The new CGWGridView derived class. 
	AddDocTemplate(pDocTemplate);

See the chapter on "Getting Started" for more information on how to use the GridWiz Wizard to build new GridWiz 
based classes. 

When using a CGWGridView derived class, the CGWGridView implementation of  OnInitialUpdate() does not call 
CGWGrid::OnInitialUpdate(). The primary reason for this is due to the potential for splitter windows. CGWGridView 
does support dynamic and static splitter windows (see the section on CGWGridView and Splitter Windows for details). 
CGWTabGridView or any other Grid based classes do not support splitters at this time.

There are several message handlers implemented in CGWGridView, mostly for mouse and keyboard messages. You may 
implement these same message handlers in your CGWGridView derived class. However, make sure that you call the base 
class implementation of these handlers or have good reason not to. Most of the CGWGrid virtual functions can be 
completely overridden except for OnSelectionChange. As a rule, you should always call the base class implementation 
of Grid virtual functions.

CGWGridView has an embedded pointer variable of type CGWGridRpt. This grid type is used for printing the CGWGridView. 
The basic flow of control when using the MFC view printing mechanism is for CGWGridView to store a copy of itself 
into a new CGWGridRpt object. This object can then re-scaled fonts and other measures to fit the printer rather than 
the display. The CGWGridRpt object has a member variable called m_pDataGrid which points back to the original 
CGWGridView object. All virtual functions called from CGWGridRpt go through the m_pDataGrid pointer. That way, all 
your data mappings will work correctly.  

*/
//}}GW_CLASS	


public:
	DECLARE_DYNCREATE(CGWGridView)
	DECLARE_GRIDCELL_MAP(CGWGridView)

//GW_MEMBERS{{(CGWGridView, "Construction")
	CGWGridView();				//Default Constructor.
	virtual ~CGWGridView();		//Default Destructor.
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWGridView, "Operations")
	 void operator=(const CGWGridView& otherGrid);	//Copy operator.
//}}GW_MEMBERS	

	 
//GW_MEMBERS{{(CGWGridView, "Operations")
	CGWGridRpt*   m_pGridRpt;	// A separate grid used for reporting so as to not interfere with current grid.
	CDocument* GetDocument();	// retrieves a ptr to the attached CDocument
	void CheckSheetSettings(CGWDataSource* pGWDataSource);	//Checks to make sure that all sheets have valid grid settings.
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);	// Set the mapping mode and selects the font and drawing tools
	void UpdateAllPanes(CGWGrid* pGV, BOOL bRedraw = TRUE);	// Updates view grid properties for any existing splitter panes.
	void SmartInvertAllPanes(CRect* pRect, UINT nRectNum);  // Calls the UpdateAllPanes for each pane in a splitter window.
	void ScrollAllPanes(UINT nBar, UINT nScrollCode, int nScrollPos);	//Calls the scroll message handlers for each open pane of a splitter window and update with the current panes scrolling.
	void CopySelRect(CGWGridView* pGV);						// Copies the selected rect from one Gridview to another.
	void SetCellAllPanes(int nRowNdx, int nColNdx,UINT bScrollToTop = 0, UINT bScrollToLeft = 0);	// Sets the currently selected cell for all panes. Data based indexes.
	void InvalidateCellAllPanes(int nRowNdx, int nColNdx);	// Invalidate a particular cell in all openned splitter panes.
	BOOL ResizeParentToGrid();								// Resize the frame  to match the size of the grid.
	void CopyView(CGWGridView* pGV, BOOL bRedraw = TRUE);   // Copies the attributes of one CGWGridView object to another.
	void SetExtents(CDC* pDC,BOOL bView = TRUE);			// Calculates extents and metrics used in drawing based on the currently selected font.
//}}GW_MEMBERS	

public:
//GW_MEMBERS{{(CGWGridView, "Overriden Virtual Functions")
    virtual void AttachDataSource(CGWDataSource* pGWDataSource);			// Overriden to check the sheet settings and then call the base class implementation.
	virtual void OnInitialUpdate();               							// Called as part of the document creation process and also when splitter panes are added.                          
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);	// Overriden to call the base class function GridOnUpdate.
	virtual	void OnDraw(CDC* pDC);											// Overriden to call the base class function GridOnDraw.
	virtual void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);	//Overriden to handle the switch between views in a splitter.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);						// Calls the CView implemenation of DoPreparePrinting.
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);				// Creates a CGWGridRpt object and copies the grids settings to it. The CGWGridRpt object is used to print.
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);				// Overriden to destroy the CGWGridRpt object.
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo);						// Paginates the CGWGridRpt and prints the pages, one page at a time.
	virtual void OnSelectionChange(int& nRowNdx, int& nColNdx, CRect* pRect, int nSelRectNdx);	// Overriden to invalidate other panes and then calls the base class implementation.
	virtual void OnHighlightCurrentCell(CDC* pDC, CRect* pRect, BOOL bSelected = TRUE);	//Overriden to allow only the active pane to hilight the current cell.
    virtual void Initialize();												// Called from the constructor to apply design time properties.
	virtual void CalcGridRect();											// Overriden to calculate the required space needed by the grid.											
//}}GW_MEMBERS	


protected:
//GW_MEMBERS{{(CGWGridView, "Message Handlers")
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Passes the scroll message on to the grid base class.
	afx_msg void OnSize(UINT nType, int cx, int cy);							//Handled to recalculate the grid rectangle.
	afx_msg void OnInitMenu(CMenu* pMenu);										//Handled to close any editing cell in response to the user activating a menu.
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Passes the VScroll message on to the grid base class.
	afx_msg void OnPaint();														//Handled to pass the control to the base class paint function.
	afx_msg void OnFilePrintPreview();											//Handled to begin the print preview process.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);						//Passes the mousemove message onto the grid cell object or to the base class grid.
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);			//Responds to this message with the cell or grid specific cursor.
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);					//Handled to pass the LButtonDblClk message to the Grid Cell Object.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);						//Handled to pass the LButtonDown message to the Grid Cell Object.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);						//Handled to pass the LButtonUp message to the Grid Cell Object.
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);						//Handled to pass the RButtonDown message to the Grid Cell Object.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);						//Handled to pass the RButtonUp message to the Grid Cell Object.
	afx_msg void OnTimer(UINT nIDEvent);										//Passes the timer message on to the base grid class.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);					//Passes the char message on to the cell and from the cell to the grid base class.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);				//Passes the keydown message on to the cell and from the cell to the grid base class.
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);				//Passes the keyup message on to the cell and from the cell to the grid base class.
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);										//Returns TRUE to prevent the default erasing of the window.
	afx_msg void OnEditClear();													//Calls the grid's implementation of EditClear.												
	afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);								//Implements EditClear CmdUI feature.
	afx_msg void OnEditCopy();													//Calls the grid's implementation of EditCopy.		
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);								//Implements EditCopy CmdUI feature.
	afx_msg void OnEditCut();													//Calls the grid's implementation of EditCut.		
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);								//Implements EditCut CmdUI feature.
	afx_msg void OnEditPaste();													//Calls the grid's implementation of EditPaste.	
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);								//Implements EditPaste CmdUI feature.
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);								//Calls the grid's implementation of EditUndo.	
	afx_msg void OnEditUndo();													//Implements EditUndo CmdUI feature.
	afx_msg void OnFilePrint();													//Handled to begin the printing process.
	afx_msg void OnKillFocus(CWnd* pNewWnd);									//Handled to take care of remove hilite if necessary.
	afx_msg void OnSetFocus(CWnd* pOldWnd);										//Handled to take care of adding hilite if necessary.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);			//Handled to provide the default back color to individual controls within cells.
	afx_msg void OnClose();														//Sets a flag telling the grid that it is being closed.
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWGridView, "Registered GridWiz Messages")
	long OnGCOLostFocus(WPARAM wParam, LPARAM lParam);		//Sent when a editing GCO loses focus. 			
	long OnGetControlCell(WPARAM wParam, LPARAM lParam);	//Sent by a GCO to retrieve the m_pControlCell data member.
	long OnCacheUpdate(WPARAM wParam, LPARAM lParam);		//Sent by a DataSource after a CacheHit has caused the cache to rebuilt.
	long OnSetColWidthMsg(WPARAM wParam, LPARAM lParam);	//Sent by a DataSource after a recordset has adjusted a grid column width.
	long OnGetColWidthMsg(WPARAM wParam, LPARAM lParam);	//Sent by a DataSource to retrieve the column width for a grid column.
	long OnRestoreGridSettingsMsg(WPARAM wParam, LPARAM lParam);	//Sent by a DataSource to signal the grid to restore the grid settings for the current sheet.
	long OnClearCachedDCs(WPARAM wParam, LPARAM lParam);	//Low priority message which cleans up the collection of DCs.
	long OnReturnGrid(WPARAM wParam, LPARAM lParam);		//Called by cells to get a pointer to the grid.
	long OnZapCell(WPARAM wParam, LPARAM lParam);					//Low priority message kills a cell so that it can be recreated.
//}}GW_MEMBERS	

	
	DECLARE_GRIDWIZ_CONTROL_NOTIFICATIONS()
	DECLARE_MESSAGE_MAP()


};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in grid3vw.cpp
inline CDocument* CGWGridView::GetDocument()
   { return (CDocument*)m_pDocument; }
#endif

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif

#undef GW_EXT_CLASS

#endif //#ifndef //__GRIDVIEW
