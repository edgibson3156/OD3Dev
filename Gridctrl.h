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
// gridctrl.h : header file
//
#ifndef __CGWGridCtrl
#define __CGWGridCtrl



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

/////////////////////////////////////////////////////////////////////////////
// CGWGridCtrl window
class GW_EXT_CLASS CGWGridCtrl : public CWnd, public CGWGrid
{
//GW_CLASS{{(CGWTabGridView)
/*
Implementing CGWGridCtrl and CGWTabGridCtrl derived classes is very similar to using any 
other CWnd child window. As described earlier in the section "Implementing a CGWGridCtrl", 
there are two ways to create a these objects. The first way is to use a dialog template which 
contains a custom control as a place holder. Specify the C++ class name for the Custom Controls
window class name. Then add the REGISTER_GW_CUSTOM_CONTROL macro with the class name. The macro
registers the C++ Class name as a registered window class. When the dialog gets created,
a instance of the custom control will be created automatically. See the "Getting Started"
section of the Online help for additional details. 

The other way is to simply call the create function passing in the parent address, resource id, 
and the CRect containing the coordinates for the CGWGridCtrl window.   

Grid Control objects behave identically to Grid View objects. The core difference is that 
a Grid Control has a GridOnInitialUpdate method instead of OnInitialUpdate. One other difference
is that Controls dont have a built-in print and print-preview feature. To print from a control,
you will need to use the GridWiz Wizard to generate a CGWReport object with a CGWGridItem. Then 
Attach the Grid Control the CGWGridRpt object in the GetGridReport function. See the 
Report sample app for additional details on reporting.
*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWGridCtrl)
public:
//The GridCell map allows you to easily format the grid. See GWIZGCO.H for cell types.
	DECLARE_GRIDCELL_MAP(CGWGridCtrl)
	DECLARE_GW_CUSTOM_CONTROL()
// Construction
public:
//GW_MEMBERS{{(CGWGridCtrl,"Construction")
	CGWGridCtrl();				//Constructor
	virtual ~CGWGridCtrl();		//Destructor
//}}GW_MEMBERS	


public:
//Data Members
//GW_MEMBERS{{(CGWGridCtrl,"Data Members")
	BOOL m_bCustomControl;					//Identifies whether this control was placed on the dialog template using the Custom Control tool.
    static CString m_strClass;				//The unique window class created for this control.
//}}GW_MEMBERS	
	
//GW_MEMBERS{{(CGWGridCtrl,"Operations")
   	virtual BOOL Create(CWnd* pParent, UINT nID, CRect Rect); //Call this function to create a new CGWGridCtrl window.
	static BOOL RegisterGridControl();			//This function is used to register a new Grid control. You must call it once from InitInstance.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridCtrl,"Overideables")
   	virtual void OnCreateCtrl()		//Called from the Create function before the window is displayed.
		{};
//}}GW_MEMBERS	

// Implementation
public:
//GW_MEMBERS{{(CGWGridCtrl, "Overriden Virtual Functions")
	virtual void Initialize();										//Overidden to provide specifc grid settings prior to showing the grid.
	virtual UINT OnGetDlgCode();									//This function is overriden to allow controls owned the grid to get messages.
	virtual void SizeGridToFit(BOOL bHorizontal, BOOL bVertical);	//Overidden to resize the grid's window to take away any excess space around the grid.
	virtual void SetIntegralHeight();								//Overidden to resize the grid's window so that an exact number of rows can be viewed.
	virtual void InitializeColWidths();								//Overidden to initialize certain column widths on startup.
    virtual void AttachDataSource(CGWDataSource* pGWDataSource);	//Overidden to supply additional processing when this grid is attached to a data source.
	void CheckSheetSettings(CGWDataSource* pGWDataSource);			//Overidden to supply additional processing when this grid is attached to a data source. Makes sure that all sheets have valid grid settings.
	virtual void CalcGridRect();									//Overidden to calculate the area required to display the grid and build the GCOs which will be in view.
	virtual void OnCellDeactivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);	//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLDEACTIVATE.
	virtual void OnCellActivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);		//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLACTIVATE.	
	virtual void OnCellClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);													//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLCLICK.
	virtual void OnCellDblClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);													//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLDBLCLK.		
	virtual void OnCellCreateHwnd(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);	//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLCREATEHWND.	
	virtual void OnCellDestroyHwnd(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);	//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLDESTROY.		
	virtual void OnCellChar(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags);			//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLCHAR.
	virtual void OnCellKeyDown(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags);		//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLKEYDOWN.
	virtual void OnCellKeyUp(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags);			//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLKEYUP.
	virtual CRect CalcControlSize(BOOL bRedraw = TRUE);            // Implements auto control sizing (OLE Control only).
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridCtrl, "Registered GridWiz Messages")
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

//GW_MEMBERS{{(CGWGridCtrl, "Message Handlers")
	afx_msg LONG OnSetFont(UINT,LONG);						//Handled to allow automatic setting of the default grid font.
	afx_msg void OnPaint();									//Handled to pass the control to the base class paint function.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	//Handled to pass the LButtonDown message to the Grid Cell Object.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	//Handled to pass the LButtonUp message to the Grid Cell Object.
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);	//Handled to pass the RButtonDown message to the Grid Cell Object.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);	//Handled to pass the RButtonUp message to the Grid Cell Object.
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Passes the scroll message on to the grid base class.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Passes the keydown message on to the cell and from the cell to the grid base class.
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);	//Passes the keyup message on to the cell and from the cell to the grid base class.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Passes the char message on to the cell and from the cell to the grid base class.
	afx_msg void OnTimer(UINT nIDEvent);					//Passes the timer message on to the base grid class.
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Passes the VScroll message on to the grid base class.
	afx_msg void OnEditClear();								//Calls the grid's implementation of EditClear.												
	afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);			//Implements EditClear CmdUI feature.
	afx_msg void OnEditCopy();								//Calls the grid's implementation of EditCopy.		
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);			//Implements EditCopy CmdUI feature.
	afx_msg void OnEditCut();								//Calls the grid's implementation of EditCut.		
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);			//Implements EditPaste CmdUI feature.
	afx_msg void OnEditPaste();								//Calls the grid's implementation of EditPaste.	
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);			//Implements EditCut CmdUI feature.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);		//Passes the mousemove message onto the grid cell object or to the base class grid.
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);	//Handled to pass the LButtonDblClk message to the Grid Cell Object.
	afx_msg void OnKillFocus(CWnd* pNewWnd);				//Handled to take care of remove hilite if necessary.
	afx_msg void OnSetFocus(CWnd* pOldWnd);					//Handled to take care of adding hilite if necessary.
	afx_msg void OnSize(UINT nType, int cx, int cy);		//Handled to recalculate the grid rectangle.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//Handled to provide the default back color to individual controls within cells.
	afx_msg void OnClose();									//Sets a flag telling the grid that it is being closed.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	//Attaches the internal data source and activates the first sheet of the grid.
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);	//Responds to this message with the cell or grid specific cursor.
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);					//Returns TRUE to prevent the default erasing of the window.
//}}GW_MEMBERS

protected:

	DECLARE_GRIDWIZ_CONTROL_NOTIFICATIONS()
	DECLARE_MESSAGE_MAP()

};



#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif // __CGWGridCtrl

/////////////////////////////////////////////////////////////////////////////
