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
// GWOleControl.h : Declaration of the CGWOleControl OLE control class.
#ifndef __CGWOLECONTROL_H__
#define __CGWOLECONTROL_H__

#if _MFC_VER < 0x0600
typedef void CGWDataSourceListener;
#endif


#define GW_EXT_CLASS

#define	 gwReadOnlyCell					0
#define	 gwEditCell						1
#define	 gwComboBoxCell					2
#define	 gwDropListCell					3
#define	 gwDropGridCell					4
#define	 gwCheckBoxCell					5
#define	 gwRadioBtnCell					6
#define	 gwHeaderCell					7
#define	 gwLetteredHeaderCell			8
#define	 gwNumberedHeaderCell			9
#define	 gwIntegerCell					10
#define	 gwFlotingPointCell				11
#define	 gwDateTimeCell					12
#define	 gwOutlineCell					13
#define	 gwDialogPromptCell				14
#define	 gwButtonCell					15
#define	 gwSpinButtonCell				16
#define	 gwProgressMeterCell			17
#define	 gwTrackBarCell					18
#define	 gwActiveXCell					19


typedef enum {
    gwOLEDragManual = 0,
    gwOLEDragAutomatic = 1
} OLEDragConstants;

typedef enum {
    gwOLEDropNone = 0,
    gwOLEDropManual = 1,
    gwOLEDropAutomatic = 2
} OLEDropConstants;

typedef enum {
    gwEnter = 0,
    gwLeave = 1,
    gwOver = 2
} DragOverConstants;

typedef enum {
    gwCFText = 1,
    gwCFBitmap = 2,
    gwCFMetafile = 3,
    gwCFDIB = 8,
    gwCFPalette = 9,
    gwCFEMetafile = 14,
    gwCFFiles = 15,
    gwCFRTF = -16639
} ClipBoardConstants;

typedef enum {
    gwOLEDropEffectNone = 0,
    gwOLEDropEffectCopy = 1,
    gwOLEDropEffectMove = 2,
    gwOLEDropEffectScroll = -2147483648
} OLEDropEffectConstants;

class CGWOleControl;

/////////////////////////////////////////////////////////////////////////////
// CGWDataObject command target

class CGWDataObject : public CCmdTarget
{
public:
	DECLARE_DYNCREATE(CGWDataObject)


// Attributes
	CGWDataObject();           // protected constructor used by dynamic creation
	virtual ~CGWDataObject();


	COleDataSource* m_pOleDataSource;
	COleDataObject* m_pOleDataObject;

	long m_lAllowedEffects;
	BOOL m_bOriginatedInGrid;
	CGWOleControl* m_pGrid;
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWDataObject)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGWDataObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGWDataObject)
	afx_msg void Clear();
	afx_msg VARIANT GetData(short sFormat);
	afx_msg BOOL GetFormat(short sFormat);
	afx_msg void SetData(VARIANT FAR& vValue, VARIANT FAR& vFormat);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CGWOleControl : See GWOleControl.cpp for implementation.

class CGWCachedDataPathProp : public CCachedDataPathProperty
{
public:
	virtual void OnDataAvailable(DWORD dwSize, DWORD grfBSCF);

};
class GW_EXT_CLASS CGWOleControl : public COleControl, public CGWGrid
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	friend class CGWDataObject;

	DECLARE_DYNCREATE(CGWOleControl)
// Constructor
public:
	
//GW_MEMBERS{{(CGWOleControl,"Construction")
	CGWOleControl();		//Default Constructor.
	~CGWOleControl();		//Destructor
//}}GW_MEMBERS	

	DECLARE_GRIDCELL_MAP(CGWOleControl)

//CGWGrid attributes
//GW_MEMBERS{{(CGWOleControl,"Data Members")
	HGLOBAL m_hGridSettings;			//Glabal memory handle to Grid Settings.
	CGWSheetTabHolder m_SheetTabHolder; //Holds sheet tab information for the grid.
	CCellDataMap* m_pDataSource;		//Pointer to the GridWiz Data Source object.
	CRect m_rectDesignModRect;			//Temp Hack because of VC++ won't create the window is design mode.
	CGWCachedDataPathProp m_CachedGridSettings;  //DataPathProp object used for asynchrously downloading GridWiz settings.
	short m_nMousePointer;				//Mouse pointer exposed to users of the grid.
	CString m_csBlankString;			//Dummy CString
	CBitmap m_tempBitmap;				//Temporary GDI bitmap holder.
	CPictureHolder m_tempPicHolder;		//Temporary OLE Picture holder.
	CGWGridRpt* m_pGridRpt;				//Pointer to the optional grid report.
	IDataSource* m_pOledbDataSource;	//Pointer to the grids default oledb data source.
	CGWDataSourceListener*	m_pGWDataSourceListener; //Pointer to a listener object which will receive notifications when datamembers of the attached data source change.
	short m_nOleDragMode;				//Manual or automatic drag mode for this drag source.
	short m_nOleDropMode;				//Manual or automatic drop mode for this drop target.
	CGWDataObject* m_pGWDataObject;		//Address of Data object used for OLE Drag and Drop.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWOleControl,"Implementation")
	virtual CGWDataSource* CreateDataSource();						//Called to create the GridWiz data source.
	virtual void ExchangeGridGlobalSettings(CPropExchange* pPX);	//Exchange grid settings. Called from DoPropExchange.
	void GetClientRect(LPRECT lpRect);								//Copies the client coordinates of the CWnd client area into the structure pointed to by lpRect.
	void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);				//Shows or hides a scroll bar. 
	BOOL EnableScrollBar(int nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);		//Enables or disables one or both arrows of a scroll bar.
	void Invalidate(BOOL bErase = TRUE);							//Invalidates the entire client area of CWnd.
	void EnableWindow(BOOL bEnable)									//Enables or disables mouse and keyboard input.
			{
				CWnd::EnableWindow(bEnable);
				m_SheetTabHolder.m_bTabEnabled = bEnable; 
				m_SheetTabHolder.UpdateWindowTabs();
			}
	BOOL IsWindowEnabled(BOOL bEnable)								//Specifies whether CWnd is enabled for mouse and keyboard input.						
			{
				return m_SheetTabHolder.m_bTabEnabled;
			}
	void LoadTabs(CGWDataSource* pGWDataSource);					//Pull tab information from a CGWDataSource object and load it into the sheet tabs.
	void RearrangeSheetsDlg()										//Calls a command handler to show the re-arrange sheet tab dialog. 
			{
				OnCommandArrangeTabs();
			}
	void InsertSheetDlg()											//Calls a command handler to show the insert sheet tab dialog. 
			{
				OnCommandInsertTab();
			}
	void LoadBlobSettings();										//Routine loads a GridWiz data source from a global memory handle
	void StoreBlobSettings();										//Routine stores a GridWiz data source from into global memory handle
	CString FormatSelectionMode(UINT nGridStyle);					//Builds a string list of valid Grid Style and Selection Modes.
	void OLEDrag();
	void BindToDataMember();										//Generic routine to handle bind to a ADO recordset
//}}GW_MEMBERS	

//Implementation (TabWnd)
//GW_MEMBERS{{(CGWOleControl,"CWnd Virtual Function Overrides")
	virtual CScrollBar* GetScrollBarCtrl( int nBar ) const;			//Get the address of a particular scrollbar control.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);					//Overriden to apply special create styles.
	virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);	 //Overriden to handle specific windows messages.
	virtual BOOL PreTranslateMessage(LPMSG lpmsg);						//Overriden to capture certain keystrokes.
//}}GW_MEMBERS	

public:	

// Overrides (CGWGrid)
//GW_MEMBERS{{(CGWOleControl,"GridWiz Virtual Function Overrides")
	virtual void GetGridWndClientRect(LPRECT rect);					//Get the client rectangle taking the tab area into consideration.
	virtual void AttachDataSource(CGWDataSource* pGWDataSource);	//Overriden to check sheet settings.
	virtual void CheckSheetSettings(CGWDataSource* pGWDataSource);	//Check to make sure all sheets have proper grid settings object and create them if necessary.
	virtual void OnAddSheet(CString csCaption);						//Overriden to add a CGWSheetTab object.
	virtual void OnRemoveSheet(int nSheet);							//Overriden to remove a CGWSheetTab object.
	virtual void OnInsertSheet(int nSheet, CString csCaption);		//Overriden to insert a CGWSheetTab object.
	virtual void OnChangeSheet(int nSheet, CString csCaption);		//Overriden to change a CGWSheetTab objects name.
	virtual void OnMoveSheet(int nSheet, int nCount);				//Overriden to move a CGWSheetTab object.
	virtual void OnActivateSheet(int nSheet = CURRENT_SHEET);		//Overriden to activate a CGWSheetTab object.
	virtual void DoSetCursor(UINT nFlags, CPoint& point);			//Called to allow the grid to set the cursor shape during a WM_MOUSEMOVE message.
	virtual void CalcGridRect(void);								//Calculates the grid region taking the tab area into consideration.
	virtual void OnGetCellText(int nRowNdx, int nColNdx, CString& csCellText);	//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual void OnSetCellText(int nRowNdx, int nColNdx, CString& csCellText);	//This function can be called by GCOs and various grid operations to store text data for a cell.
	virtual BOOL OnCellValidateData(int m_nRowNdx, int m_nColNdx, CString& csFormatedText);	//This function can be called by GCOs and various grid operations to store text data for a cell.
	virtual void OnChangeColWidth(int nColNdx, float& nNewWidth, int nUnits = DEFAULT_UNITS);		//Called when a Column was resized. Passes the Column the index.
	virtual void OnChangeRowHeight(int nRowNdx, float& nNewHeight, int nUnits = DEFAULT_UNITS);     //Called when a Row was resized. Passes the Row index.
	virtual void OnPostSelectionChange(int nRowNdx, int nColNdx);	//Called after a selection has been made. It cannot be changed at this point. See also: OnSelectionChange().
	virtual void OnCellSelChange(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, int nItemCount, CString* pSelection, void* pExtraData, int* pItems, BOOL& bSendExtraData);	//Called from a GCO with a drop down list to notify the grid that the user has made a selection in the list.
	virtual BOOL OnGetCellValidString(int nRowNdx, int nColNdx, CString& csValidString, void*& pItemDataPtr, int nStringIndex);	//Called from GCOs to retrieve valid strings for drop down list type cells.
	virtual void GWShowScrollBar(UINT nSB, BOOL bShow, BOOL bEnabled);   //Internal version of show scrollbar function. Overriden to take tab area into consideration.
	virtual void InitializeColWidths();					//Called from OnInitialUpdate to pre-set the widths any columns
	virtual BOOL IsPageBreakColumn(int nColNdx);		//Is the column a page break column?
	virtual BOOL IsPageBreakRow(int nRowNdx);			//Is the row a page break row?
	virtual void OnAddColumn(int nCount, int nSheet = CURRENT_SHEET);	//Called in response to the AddColumn function.
	virtual void OnAddRow(int nCount, int nSheet = CURRENT_SHEET);		//Called in response to the AddRow function.
	virtual void OnCellDeactivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);	//This virtual function is fired from a GCO to notify the grid that the editing control is about to be removed from a cell and destroyed.
	virtual void OnCellActivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);		//This virtual function is fired from a GCO to notify the grid that the editing control is about to displayed and activated.
	virtual void OnCellClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);	//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLCLICK. 
	virtual void OnCellDblClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);	//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLDBLCLK.
	virtual void OnCellCreateHwnd(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);	//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLCREATEHWND.
	virtual void OnCellDestroyHwnd(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);	//Overidden to intercept this event and format a special WM_NOTIFY message to be sent to grid's parent. Notify code: GWN_CELLDESTROY.
	virtual void OnCellError(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);	//Called when a cell detects an error through a validation routine.
	virtual void OnCellNotify(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT nNotification);	//Generic mechanism for GCOs to pass custom notifications to the grid.
	virtual void OnClearSheetData(int nSheet = CURRENT_SHEET);						//Calls a function on CGWDataSource to clear the data on a sheet.
	virtual void OnCopyColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Called in response to the CopyColumn function or a drag and drop operation.nSheet = CURRENT_SHEET);
	virtual void OnCopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);		//Called in response to the CopyRow function or a drag and drop operation.
	virtual void OnDeleteColumn(int nColNdx, int nCount, int nSheet = CURRENT_SHEET);	//Called in response to the DeleteColumn function or the user deleteing a row via the keyboard.
	virtual void OnDeleteRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);		//Called in response to the DeleteRow function or the user deleteing a row via the keyboard. 
	virtual void OnGetDefaultCellText(int nRowNdx, int nColNdx, CString& csDefaultVal);	//This fucntion is called during the "AddRow" processing to obtain default values for each cell in the new row.
	virtual void OnInsertColumn(int nColNdx, int nCount, int nSheet = CURRENT_SHEET);	//Called in response to the InsertColumn function. 
	virtual void OnInsertRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);		//Called in response to the InsertRow function.
	virtual void OnMoveColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Called in response to the MoveColumn function or a drag and drop operation.nSheet = CURRENT_SHEET);
	virtual void OnMoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);		//Called in response to the MoveRow function or a drag and drop operation.
	virtual CBitmap* OnGetCellBitmap(int nRowNdx, int nColNdx, BOOL& bStretch, int& nJustify);	//Called to retrieve a CBitmap pointer for a cell.
	virtual void OnCellChar(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags);	//This virtual function is fired from a GCO to notify the grid that the cell just received a WM_CHAR message.
	virtual void OnCellKeyDown(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags);	//This virtual function is fired from a GCO to notify the grid that the cell just received a WM_KEYDOWN message.
	virtual void OnCellKeyUp(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags);		//This virtual function is fired from a GCO to notify the grid that the cell just received a WM_KEYUP message.
	virtual BOOL CalcControlSize();            // Implements auto control sizing (OLE Control only).
	virtual void SetDesignMode(BOOL bDesignMode);	//Sets the m_bDesignMode flag.
	virtual BOOL GetDesignMode();					//Retrieves the m_bDesignMode flag.
	virtual COleDataSource* CreateOleDataSource();					//Called when drag and drop is initiated to constructs an COleDataSource object.
	virtual void DestroyOleDataSource(COleDataSource* pDataSource);  ////Called when drag and drop is terminates to destroy the COleDataSource object.
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point, BOOL* pbCancelDefaultAction);	//Called by the frameword when the mouse is dragged over the target window.		
	virtual void OnDragLeave(CWnd* pWnd, BOOL* pbCancelDefaultAction);																		//Called by the frameword when the mouse leaves the target window.		
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point, BOOL* pbCancelDefaultAction);		//Called by the frameword when the mouse moves over the target window.		
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point, BOOL* pbCancelDefaultAction);			//Called by the frameword when the user drops onto the target window.		
	virtual void OnDragComplete(COleDataSource* pDataSource, DROPEFFECT dropEffect);			//Called by the framework to notify the source of the completed operation.		
	virtual SCODE GiveFeedback(DROPEFFECT dropEffect, BOOL* pbCancelDefaultAction);				//Called by the framework so you can provide the visual feedback to the user.		
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWOleControl,"COleControl Virtual Function Overrides")
	BOOL OnGetDisplayString(DISPID dispid, CString& strValue);			//Called by the framework to obtain a string that represents the current value of the property identified by dispid.
	BOOL OnGetPredefinedStrings(DISPID dispid,CStringArray* pStringArray, CDWordArray* pCookieArray);	//Called by the framework to obtain a set of predefined strings representing the possible values for a property.
	BOOL OnGetPredefinedValue(DISPID dispid, DWORD dwCookie,VARIANT FAR* lpvarOut);	//Called by the framework to obtain the value corresponding to one of the predefined strings previously returned by an override of COleControl::OnGetPredefinedStrings.
	virtual void OnBackColorChanged();	//Called by the framework when the stock BackColor property value has changed.
	virtual void OnFontChanged();		//Called by the framework when the stock Font property value has changed.
	virtual void OnForeColorChanged();	//Called by the framework when the stock ForeColor property value has changed.
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);	//Called by the framework to draw the OLE control in the specified bounding rectangle using the specified device context.
	virtual void OnAmbientPropertyChange(DISPID dispID);	//Called by the framework when an ambient property of the container has changed value.
	virtual void OnResetState();							//Called by the framework when the control's properties should be set to their default values.
	virtual void OnClose(DWORD dwSaveOption);				//Called by the framework when the container has called the control's IOleControl::Close function.
	virtual void OnBorderStyleChanged();					//Called by the framework when the stock BorderStyle property value has changed. 
//}}GW_MEMBERS	
	virtual unsigned long GetMiscStatus()
		{return 0l;};
	virtual unsigned int GetUserTypeNameID() 
		{return 0;};
	virtual long GetClassID(struct _GUID *) 
		{return 0l;}

protected:


//GW_MEMBERS{{(CGWOleControl,"CWnd Message Handlers")
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);		//The framework calls this member function when an application requests that the Windows window be created by calling the Create or CreateEx member function.
	afx_msg void OnPaint();										//The framework calls this member function when Windows or an application makes a request to repaint a portion of an application's window.
	afx_msg void OnSize(UINT nType, int cx, int cy);			//The framework calls this member function after the window's size has changed.
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//The framework calls this member function when the user clicks the window's vertical scroll bar.
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//The framework calls this member function when the user clicks a window's horizontal scroll bar. 
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);		//The framework calls this member function when the user presses the left mouse button.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);		//The framework calls this member function when the user releases the left mouse button.
	afx_msg void OnKillFocus(CWnd* pNewWnd);					//The framework calls this member function immediately before losing the input focus.
	afx_msg void OnSetFocus(CWnd* pOldWnd);						//The framework calls this member function after gaining the input focus. To display a caret, CWnd should call the appropriate caret functions at this point.
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);	//The framework calls this member function when the user double-clicks the left mouse button.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);		//The framework calls this member function when the mouse cursor moves.
	afx_msg void OnTimer(UINT nIDEvent);						//The framework calls this member function after each interval specified in the SetTimer member function used to install a timer. 
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);	//The framework calls this member function when a keystroke translates to a nonsystem character.
	afx_msg UINT OnGetDlgCode();	//Normally, Windows handles all arrow-key and TAB-key input to a CWnd control. By overriding OnGetDlgCode, a CWnd control can choose a particular type of input to process itself. 
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//The framework calls this member function when a nonsystem key is pressed.
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);	//The framework calls this member function when a nonsystem key is released.
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);			//This member function is called by the framework to allow your application to handle a Windows message.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);			//The framework calls this member function when the user releases the right mouse button.
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWOleControl,"GridWiz Message Handlers")
	afx_msg void OnCommandArrangeTabs();							//Launches dialog to re-arrange tabs.
	afx_msg void OnCommandInsertTab();								//Launches dialog to insert tabs.
	afx_msg void OnCommandDeleteTab();								//Handler to delete a tab.
	afx_msg void OnUpdateDeleteTab(CCmdUI* pCmdUI);					//CmdUI Handler for deleting a tab.
	afx_msg void OnCommandRenameTab();								//Launches a dialog to rename a tab.
	long OnUserMessageHandler(UINT nMsg, long l);					//Sent by popup when the popup loses focuses. Triggers destruction of the grid. 
	long OnGetControlCell(WPARAM wParam, LPARAM lParam);			//Sent by a GCO to retrieve the m_pControlCell data member.
	long OnCacheUpdate(WPARAM wParam, LPARAM lParam);				//Sent by a DataSource after a CacheHit has caused the cache to rebuilt.
	long OnSetColWidthMsg(WPARAM wParam, LPARAM lParam);			//Sent by a DataSource after a recordset has adjusted a grid column width.
	long OnGetColWidthMsg(WPARAM wParam, LPARAM lParam);			//Sent by a DataSource to retrieve the column width for a grid column.
	long OnRestoreGridSettingsMsg(WPARAM wParam, LPARAM lParam);	//Sent by a DataSource to signal the grid to restore the grid settings for the current sheet.
	long OnClearCachedDCs(WPARAM wParam, LPARAM lParam);			//Low priority message which cleans up the collection of DCs.
	long OnFillDataCache(WPARAM wParam, LPARAM lParam);				//Message fired from data source when a cache hit has taken place. 
	long OnZapCell(WPARAM wParam, LPARAM lParam);					//Low priority message kills a cell so that it can be recreated.
	long RefreshDesignTimeSheet(WPARAM wParam, LPARAM lParam);		//Sent to refresh the sheet during design-time processing
//}}GW_MEMBERS	

	DECLARE_GRIDWIZ_CONTROL_NOTIFICATIONS()
	DECLARE_MESSAGE_MAP()

	DECLARE_EVENTSINK_MAP()
//GW_MEMBERS{{(CGWOleControl,"Embedded OCX Message Handlers")
	afx_msg BOOL OnMouseDownOCX(UINT nID, short Button, short Shift, long x, long y);	//Event handler for a mouse down inside an embedded OCX
	afx_msg BOOL OnMouseMoveOCX(UINT nID, short Button, short Shift, long x, long y);	//Event handler for a mouse move inside an embedded OCX
	afx_msg BOOL OnMouseUpOCX(UINT nID, short Button, short Shift, long x, long y);		//Event handler for a mouse up inside an embedded OCX
	afx_msg BOOL OnClickOCX(UINT nID);			//Event handler for a click event inside an embedded OCX
	afx_msg BOOL OnDblClickOCX(UINT nID);		//Event handler for a double click event inside an embedded OCX
	afx_msg BOOL OnKeyDownOCX(UINT nID, short KeyCode, short Shift);		//Event handler for a key down event inside an embedded OCX
	afx_msg BOOL OnKeyPressOCX(UINT nID, short FAR* KeyAscii);				//Event handler for a key press event inside an embedded OCX
	afx_msg BOOL OnKeyUpOCX(UINT nID, short KeyCode, short Shift);			//Event handler for a key up event inside an embedded OCX
	BOOL OnEvent(UINT idCtrl, AFX_EVENT* pEvent,AFX_CMDHANDLERINFO* pHandlerInfo);	//Generic event handler for an embedded OCX
	afx_msg LPDISPATCH GetCellDispatch(long nRowNdx, long nColNdx);			//Funtion to retrieve the IDispatch pointer of an embedded OCX
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);		//Event handler for a SetCursor event inside an embedded OCX
//}}GW_MEMBERS	

	
// Dispatch maps
	//{{AFX_DISPATCH(CGWOleControl)
//GW_MEMBERS{{(CGWOleControl,"Disaptch Implementation")
	afx_msg BOOL GetGridLines();					//This property controls whether gridlines are displayed			
	afx_msg void SetGridLines(BOOL bNewValue);		//This property controls whether gridlines are displayed			
	afx_msg long GetRows();							//This property indicates and controls the number of rows on the current sheet as well as the default sheet.
	afx_msg void SetRows(long nNewValue);			//This property indicates and controls the number of rows on the current sheet as well as the default sheet.
	afx_msg long GetColumns();						//This property indicates and controls the number of columns on the current sheet as well as the default sheet.
	afx_msg void SetColumns(long nNewValue);		//This property indicates and controls the number of columns on the current sheet as well as the default sheet.
	afx_msg BOOL GetColSelect();					//This property controls the user's ability to select columns using the mouse.
	afx_msg void SetColSelect(BOOL bNewValue);		//This property controls the user's ability to select columns using the mouse.
	afx_msg BOOL GetColResize();					//This property controls the user's ability to resize columns using the mouse.
	afx_msg void SetColResize(BOOL bNewValue);		//This property controls the user's ability to resize columns using the mouse.
	afx_msg BOOL GetRowSelect();					//This property controls the user's ability to select rows using the mouse.
	afx_msg void SetRowSelect(BOOL bNewValue);		//This property controls the user's ability to select rows using the mouse.
	afx_msg BOOL GetRowResize();					//This property controls the user's ability to resize rows using the mouse.
	afx_msg void SetRowResize(BOOL bNewValue);		//This property controls the user's ability to resize rows using the mouse.
	afx_msg OLE_COLOR GetGridLineColor();				//This property controls the color of the grid lines.
	afx_msg void SetGridLineColor(OLE_COLOR nNewValue);	//This property controls the color of the grid lines.
	afx_msg short GetSelectionMode();					//This property controls whether multiple selections are possible and how those selection can be accomplished.
	afx_msg void SetSelectionMode(short nNewValue);		//This property controls whether multiple selections are possible and how those selection can be accomplished.
	afx_msg short GetScrollBars();						//This property controls whether scrollbars will be displayed as part of the grid.
	afx_msg void SetScrollBars(short nNewValue);		//This property controls whether scrollbars will be displayed as part of the grid.
	afx_msg short GetDisableNoScroll();					//This property controls the appearance of scrollbars on the sheet or grid level.
	afx_msg void SetDisableNoScroll(short nNewValue);	//This property controls the appearance of scrollbars on the sheet or grid level.
	afx_msg BOOL GetAutoSizeColumns();					//This property controls whether all the columns in the grid will be forced to fit inside the current grid window.
	afx_msg void SetAutoSizeColumns(BOOL bNewValue);	//This property controls whether all the columns in the grid will be forced to fit inside the current grid window.
	afx_msg long GetDefaultColumnWidth();				//This property controls the default width of columns.
	afx_msg void SetDefaultColumnWidth(long nNewValue);	//This property controls the default width of columns.
	afx_msg BOOL GetOLEDragAndDrop();					//This property can be used to toggle the users ability to use OLE Drag and Drop in the grid.
	afx_msg void SetOLEDragAndDrop(BOOL bNewValue);		//This property can be used to toggle the users ability to use OLE Drag and Drop in the grid.
	afx_msg long GetDefaultRowHeight();					//This property controls the default height of rows.
	afx_msg void SetDefaultRowHeight(long nNewValue);	//This property controls the default height of rows.
	afx_msg short GetSizingRegionWidth();				//This property controls the height and width of the hit-testing region between row and columns which is used for sizing with the mouse.
	afx_msg void SetSizingRegionWidth(short nNewValue);	//This property controls the height and width of the hit-testing region between row and columns which is used for sizing with the mouse.
	afx_msg BOOL GetThumbScroll();						//This property controls whether the SB_THUMBTRACK scroll command updates the scroll position.
	afx_msg void SetThumbScroll(BOOL bNewValue);		//This property controls whether the SB_THUMBTRACK scroll command updates the scroll position.
	afx_msg short GetRowColUnits();						//This property controls the default unit of measure applied to the Row Height and Column width properties.
	afx_msg void SetRowColUnits(short nNewValue);		//This property controls the default unit of measure applied to the Row Height and Column width properties.
	afx_msg VARIANT GetGridSettings();					//Do not use this function through the automation interface
	afx_msg void SetGridSettings(const VARIANT FAR& newValue);		//Do not use this function through the automation interface
	afx_msg BOOL GetShowTabs();							//This property controls whether the grid displays sheet tabs along the bottom of the grid.
	afx_msg void SetShowTabs(BOOL bNewValue);			//This property controls whether the grid displays sheet tabs along the bottom of the grid.
	afx_msg short GetNumSheets();						//This property controls the number of visible sheets in the grid.
	afx_msg void SetNumSheets(short nNewValue);			//This property controls the number of visible sheets in the grid.
	afx_msg BOOL GetListboxMode();						//This property controls whether the Grid will operate in Listbox Mode.
	afx_msg void SetListboxMode(BOOL bNewValue);		//This property controls whether the Grid will operate in Listbox Mode.
	afx_msg OLE_COLOR GetHeaderCellColor();					//The HeaderCellColor property controls the back ground color of the cells in the fixed rows and columns.
	afx_msg void SetHeaderCellColor(OLE_COLOR nNewValue);	//The HeaderCellColor property controls the back ground color of the cells in the fixed rows and columns.
	afx_msg BOOL GetAddRow();							//Provides the additional row at the bottom of the grid for adding new rows.
	afx_msg void SetAddRow(BOOL bNewValue);				//Provides the additional row at the bottom of the grid for adding new rows.
	afx_msg BSTR GetDefaultCellType();							//This property identifies the defualt type of the cells for a entire grid including all sheets.	
	afx_msg void SetDefaultCellType(LPCTSTR lpszNewValue);		//This property identifies the defualt type of the cells for a entire grid including all sheets.
	afx_msg LPDISPATCH Sheet(short nSheetNdx);					//This function creates and returns a new Sheet object corresponding to the nSheetNdx argument.
	afx_msg void InsertNewSheet(short nInsertAt, LPCTSTR csSheetName);	//Call this function to insert a new un-initialized sheet into the grid.
	afx_msg LPDISPATCH ActiveSheet();							//This function returns a sheet object which can be manipulated through OLE Automation.
	afx_msg short ActivateSheet(short nSheetNdx);				//Causes a sheet to become the currently active and displayed sheet.
	afx_msg void RegisterValidStringObject(LPCTSTR Name, LPDISPATCH ValidStringObject);	//Call this function to register a new ValidStrings Object with the grid.
	afx_msg void RefreshValidStringObjects();					//This method will force any valid string objects which were based on a DatabaseRequest Object to be re-evaluated.
	CString m_szPropertyFile;									//Internal string used to hold the file path to a Grid Workshop settings file.
	afx_msg void OnPropertyFileChanged();						//Change notification that the settings file property has been altered.
	BOOL m_bWantOnGetCellText;									//Internal boolean which holds hold a value which determines whether the OnGetCellText event gets fired.
	afx_msg void OnWantOnGetCellTextChanged();					//Change notification that the WantOnGetCellText property has been altered.
	BOOL m_bWantOnSetCellText;									//Internal boolean which holds hold a value which determines whether the OnSetCellText event gets fired.
	afx_msg void OnWantOnSetCellTextChanged();					//Change notification that the WantOnSetCellText property has been altered.
	afx_msg BOOL GetSizeColumnTopToBottom();					//This property controls the size of the region used to resize columns with the mouse.
	afx_msg void SetSizeColumnTopToBottom(BOOL bNewValue);		//This property controls the size of the region used to resize columns with the mouse.
	afx_msg BOOL GetSizeRowLeftToRight();						//This property controls the size of the region used to resize rows with the mouse.
	afx_msg void SetSizeRowLeftToRight(BOOL bNewValue);			//This property controls the size of the region used to resize rows with the mouse.
	afx_msg short GetDockedRows();								//GridWiz also supports docking rows and columns along the right and bottom side of the grid.
	afx_msg void SetDockedRows(short nNewValue);				//GridWiz also supports docking rows and columns along the right and bottom side of the grid.
	afx_msg short GetDockedColumns();							//GridWiz also supports docking rows and columns along the right and bottom side of the grid.
	afx_msg void SetDockedColumns(short nNewValue);				//GridWiz also supports docking rows and columns along the right and bottom side of the grid.
	afx_msg short GetColumnDragStyle();							//The ColumnDragStyle property allows you to specify flags to control or force specific drag options.
	afx_msg void SetColumnDragStyle(short nNewValue);			//The ColumnDragStyle property allows you to specify flags to control or force specific drag options.
	afx_msg short GetRowDragStyle();							//The RowDragStyle property allows you to specify flags to control or force specific drag options.
	afx_msg void SetRowDragStyle(short nNewValue);				//The RowDragStyle property allows you to specify flags to control or force specific drag options.
	afx_msg short GetRangeDragStyle();							//The RangeDragStyle property allows you to specify flags to control or force specific drag options.
	afx_msg void SetRangeDragStyle(short nNewValue);			//The RangeDragStyle property allows you to specify flags to control or force specific drag options.
	afx_msg OLE_COLOR GetHwndBackColor();						//This property controls the back ground color unused portions of the grid window.
	afx_msg void SetHwndBackColor(OLE_COLOR nNewValue);			//This property controls the back ground color unused portions of the grid window.
	afx_msg short GetTabControlStyle();							//This property controls the handling of the tab key within the grid.
	afx_msg void SetTabControlStyle(short nNewValue);			//This property controls the handling of the tab key within the grid.
	afx_msg BOOL GetHiliteNoFocus();							//The HiliteNoFocus property controls the visual appearance of selected cells when the grid loses focus. In other words, "What happens when the user clicks on another control on the form"?
	afx_msg void SetHiliteNoFocus(BOOL bNewValue);				//The HiliteNoFocus property controls the visual appearance of selected cells when the grid loses focus. In other words, "What happens when the user clicks on another control on the form"?
	afx_msg BOOL GetClipHeadings();								//The ClipHeadings property determines whether data from the headings (fixed rows and columns) will be included in any clipboard operations.
	afx_msg void SetClipHeadings(BOOL bNewValue);				//The ClipHeadings property determines whether data from the headings (fixed rows and columns) will be included in any clipboard operations.
	afx_msg BOOL GetShowEditIndicators();						//This property controls whether the edit indicators appear in the first row header when the grid is being used in edit mode.
	afx_msg void SetShowEditIndicators(BOOL bNewValue);			//This property controls whether the edit indicators appear in the first row header when the grid is being used in edit mode.
	afx_msg short GetMousePointer();							//The MousePointer property controls the default mouse pointer used by the grid.
	afx_msg void SetMousePointer(short nNewValue);				//The MousePointer property controls the default mouse pointer used by the grid.
	afx_msg void GetCurrentCell(long FAR* nRowNdx, long FAR* nColNdx);		//Retrieve a CPoint which contains the coordinates of the current cell.
	afx_msg void SetCurrentCell(long nRowNdx, long nColNdx, BOOL bScroll);	//This function sets the row and column coordinates for the current cell.
	afx_msg void SetCellText(long nRowNdx, long nColNdx, short nSheet, LPCTSTR CellText);	//This method will assign a tab-delimitted string to a block of cells.
	afx_msg void SetRangeText(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, long nEndColNdx, short nSheetNdx, LPCTSTR RangeText, LPCTSTR CellDelim, LPCTSTR LineDelim);	//This function will bulk copy a delimitted text buffer into a range of the specified sheet.
	afx_msg BSTR GetCellText(long nRowNdx, long nColNdx, short nSheetNdx);		//This function will retrieve a tab-delimitted string containing the contents of a block of cells.
	afx_msg BSTR GetRangeText(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, long nEndColNdx, short nSheetNdx, LPCTSTR CellDelim, LPCTSTR LineDelim);	//This function will retrieve a tab-delimitted string containing the contents of a block of cells.
	afx_msg void Sort(long nMajor, BOOL Ascending, long nMinor1, BOOL Ascending1, long nMinor2, BOOL Ascending2, long nMinor3, BOOL Ascending3, BOOL bCallBackForData);	//This method can be used to sort a single column in ascending or descending order.
	afx_msg BOOL Seek(LPCTSTR SeekText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL CallBackForData);	//The Seek Method will search a particular column on the currently active sheet for text matching the supplied search text according to the search criteria.
	afx_msg long Replace(LPCTSTR SeekText, LPCTSTR ReplacementText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL bReplaceAll, BOOL CallBackForData);	//The Replace Method will search a particular column on the currently active sheet for text matching the supplied search text according to the search criteria.
	afx_msg BOOL SeekNext();		//Repeat the last seek operation.
	afx_msg BOOL ReplaceNext();		//Repeat the last replacement operation.
	afx_msg void ReSort();			//Repeat the last sort operation.
	afx_msg void SaveGridSettings(BOOL bIncludeData, LPCTSTR strFilePath);	//Saves the entire grids current settings to a file.
	afx_msg void LoadGridSettings(LPCTSTR strFilePath);						//Loads the entire grids settings from a file.
	afx_msg void SetAutoSizeControlHeight(BOOL bAutoSize);					//Determines whether to control sizes itself to fit all the rows.
	afx_msg void SetAutoSizeControlWidth(BOOL bAutoSize);					//Determines whether to control sizes itself to fit all the columns.
	afx_msg void SetEnableCellTips(BOOL bEnableCellTips);					//Enables or disables cell tips.
	afx_msg long GetDefaultCellID();										//Gets the default cell types ID.
	afx_msg void SetDefaultCellID(long nNewValue);							//Sets the default cell type by its ID.
	afx_msg long GetVScrollPos();											//Gets the vertical scroll position. This is the row index of the first visible non-fixed row.
	afx_msg long GetHScrollPos();											//Gets the horizontal scroll position. This is the column index of the first visible non-fixed column.
	afx_msg void SetVScrollPos(long Pos);									//Sets the vertical scroll position. This is the row index of the first visible non-fixed row.
	afx_msg void SetHScrollPos(long Pos);									//Sets the vertical scroll position. This is the row index of the first visible non-fixed row.
	afx_msg void ClearSheet(short SheetNdx, BOOL ClearHeadings, BOOL ClearSettings);	//Clear the sheets data and or settings
	afx_msg LPUNKNOWN GetDataSource();										//Gets the grids default oledb data source.
	afx_msg void SetDataSource(LPUNKNOWN newValue);							//Sets the grids default oledb data source.
	afx_msg BSTR GetDataMember();											//Gets the oledb data source data member for the current sheet.
	afx_msg void SetDataMember(LPCTSTR lpszNewValue);						//Sets the oledb data source data member for the current sheet.
	afx_msg BSTR GetCurrentSheet();											//Gets the name of the active sheet
	afx_msg void SetCurrentSheet(LPCTSTR lpszNewValue);						//Sets the active sheet by name
	afx_msg void RemoveSheet(short SheetNdx);								//Remove and destroy an individual sheet.
	afx_msg void MoveSheet(short SheetNdx, short InsertBeforeSheetNdx);		//Arranges sheet tabs.
	afx_msg void CopySheet(short SheetNdx, short InsertBeforeSheetNdx);		//Make a copy of an existing sheet.
	afx_msg void AutoSizeTabArea();											//Recalculates the area required to display the sheet tabs.
	afx_msg int GetOLEDragMode();					//This property controls whether the grid uses manual or automatic OLEDragMode	
	afx_msg void SetOLEDragMode(int NewValue);		//This property controls whether the grid uses manual or automatic OLEDragMode				
	afx_msg int GetOLEDropMode();					//This property controls whether the grid uses manual or automatic OLEDropMode				
	afx_msg void SetOLEDropMode(int NewValue);		//This property controls whether the grid uses manual or automatic OLEDropMode				
//}}GW_MEMBERS	
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()


// Event maps
	//{{AFX_EVENT(CGWOleControl)
	void FireOnGetCellText(long nRowNdx, long nColNdx, short nSheetNdx, BSTR FAR* csCellText, BOOL FAR* CancelDefaultAction)
		{FireEvent(eventidOnGetCellText,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I2  VTS_PBSTR VTS_PBOOL), nRowNdx, nColNdx, nSheetNdx, csCellText, CancelDefaultAction);}
	void FireOnSetCellText(long nRowNdx, long nColNdx, short nSheetNdx, LPCTSTR csCellText, BOOL FAR* CancelDefaultAction)
		{FireEvent(eventidOnSetCellText,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I2  VTS_BSTR VTS_PBOOL), nRowNdx, nColNdx, nSheetNdx, csCellText, CancelDefaultAction);}
	void FireSelChange(long FAR* nRowNdx, long FAR* nColNdx, short nSelNdx)
		{FireEvent(eventidSelChange,EVENT_PARAM(VTS_PI4  VTS_PI4  VTS_I2), nRowNdx, nColNdx, nSelNdx);}
	void FireOnActivateSheet(short nSheetNdx, BOOL FAR* CancelActivate)
		{FireEvent(eventidOnActivateSheet,EVENT_PARAM(VTS_I2  VTS_PBOOL), nSheetNdx, CancelActivate);}
	void FireOnValidateCell(long nRowNdx, long nColNdx, short nSheetNdx, LPCTSTR CellText, BOOL FAR* IsValid)
		{FireEvent(eventidOnValidateCell,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I2  VTS_BSTR  VTS_PBOOL), nRowNdx, nColNdx, nSheetNdx, CellText, IsValid);}
	void FireOnCellSelChange(long nRowNdx, long nColNdx, short nSheetNdx, LPCTSTR ValidString, LPCTSTR ExtraData, short StringNdx)
		{FireEvent(eventidOnCellSelChange,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I2  VTS_BSTR  VTS_BSTR  VTS_I2), nRowNdx, nColNdx, nSheetNdx, ValidString, ExtraData, StringNdx);}
	void FireOnGetCellValidString(long nRowNdx, long nColNdx, short nSheetNdx, BSTR FAR* ValidString, VARIANT FAR* ExtraData, short StringNdx, BOOL FAR* MoreStrings, BOOL FAR* CancelDefaultAction)
		{FireEvent(eventidOnGetCellValidString,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I2  VTS_PBSTR  VTS_PVARIANT  VTS_I2  VTS_PBOOL  VTS_PBOOL), nRowNdx, nColNdx, nSheetNdx, ValidString, ExtraData, StringNdx, MoreStrings, CancelDefaultAction);}
	void FireOnChangeRowHeight(long nRowNdx, float FAR* NewHeight, short Units)
		{FireEvent(eventidOnChangeRowHeight,EVENT_PARAM(VTS_I4  VTS_PR4  VTS_I2), nRowNdx, NewHeight, Units);}
	void FireOnChangeColWidth(long nRowNdx, float FAR* NewWidth, short Units)
		{FireEvent(eventidOnChangeColWidth,EVENT_PARAM(VTS_I4  VTS_PR4  VTS_I2), nRowNdx, NewWidth, Units);}
	void FireOnCellError(long nRowNdx, long nColNdx)
		{FireEvent(eventidOnCellError,EVENT_PARAM(VTS_I4  VTS_I4), nRowNdx, nColNdx);}
	void FireOnCellClick(short Button, short Shift, long nRowNdx, long nColNdx)
		{FireEvent(eventidOnCellClick,EVENT_PARAM(VTS_I2 VTS_I2 VTS_I4  VTS_I4), Button, Shift, nRowNdx, nColNdx);}
	void FireOnCellDblClick(short Button, short Shift, long nRowNdx, long nColNdx)
		{FireEvent(eventidOnCellDblClick,EVENT_PARAM(VTS_I2 VTS_I2 VTS_I4  VTS_I4), Button, Shift, nRowNdx, nColNdx);}
	void FireOnCellNotify(long nRowNdx, long nColNdx, long nNotification)
		{FireEvent(eventidOnCellNotify,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4), nRowNdx, nColNdx, nNotification);}
	void FireOnGetDefaultCellText(long nRowNdx, long nColNdx, BSTR FAR* DefaultText)
		{FireEvent(eventidOnGetDefaultCellText,EVENT_PARAM(VTS_I4  VTS_I4  VTS_PBSTR), nRowNdx, nColNdx, DefaultText);}
	void FireOnClearAllData()
		{FireEvent(eventidOnClearAllData,EVENT_PARAM(VTS_NONE));}
	void FireOnAddRow(short Count)
		{FireEvent(eventidOnAddRow,EVENT_PARAM(VTS_I2), Count);}
	void FireOnAddColumn(short Count)
		{FireEvent(eventidOnAddColumn,EVENT_PARAM(VTS_I2), Count);}
	void FireOnDeleteRow(long nRowNdx, short Count)
		{FireEvent(eventidOnDeleteRow,EVENT_PARAM(VTS_I4  VTS_I2), nRowNdx, Count);}
	void FireOnDeleteColumn(long nColNdx, short Count)
		{FireEvent(eventidOnDeleteColumn,EVENT_PARAM(VTS_I4  VTS_I2), nColNdx, Count);}
	void FireOnInsertRow(long nRowNdx, short Count)
		{FireEvent(eventidOnInsertRow,EVENT_PARAM(VTS_I4  VTS_I2), nRowNdx, Count);}
	void FireOnInsertColumn(long nColNdx, short Count)
		{FireEvent(eventidOnInsertColumn,EVENT_PARAM(VTS_I4  VTS_I2), nColNdx, Count);}
	void FireOnCopyRow(long BeginRow, long EndRow, long InsertBeforeRow)
		{FireEvent(eventidOnCopyRow,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4), BeginRow, EndRow, InsertBeforeRow);}
	void FireOnCopyColumn(long BeginColumn, long EndColumn, long InsertBeforeColumn)
		{FireEvent(eventidOnCopyColumn,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4), BeginColumn, EndColumn, InsertBeforeColumn);}
	void FireOnMoveRow(long BeginRow, long EndRow, long InsertBeforeRow)
		{FireEvent(eventidOnMoveRow,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4), BeginRow, EndRow, InsertBeforeRow);}
	void FireOnMoveColumn(long BeginColumn, long EndColumn, long InsertBeforeColumn)
		{FireEvent(eventidOnMoveColumn,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4), BeginColumn, EndColumn, InsertBeforeColumn);}
	void FireIsPageBreakRow(long nRowNdx, BOOL FAR* RetVal)
		{FireEvent(eventidIsPageBreakRow,EVENT_PARAM(VTS_I4  VTS_PBOOL), nRowNdx, RetVal);}
	void FireIsPageBreakColumn(long nColNdx, BOOL FAR* RetVal)
		{FireEvent(eventidIsPageBreakColumn,EVENT_PARAM(VTS_I4  VTS_PBOOL), nColNdx, RetVal);}
	void FireOnFillCache(long nHighWaterMark, long nCacheIncrement, long FAR* nRowsAdded, short nSheetNdx)
		{FireEvent(eventidOnFillCache,EVENT_PARAM(VTS_I4  VTS_I4  VTS_PI4  VTS_I2), nHighWaterMark, nCacheIncrement, nRowsAdded, nSheetNdx);}
	void FireOnCellActivate(long nRowNdx, long nColNdx, OLE_HANDLE Hwnd, LPDISPATCH IDispatch)
		{FireEvent(eventidOnCellActivate,EVENT_PARAM(VTS_I4  VTS_I4  VTS_HANDLE  VTS_DISPATCH), nRowNdx, nColNdx, Hwnd, IDispatch);}
	void FireOnCellDeactivate(long nRowNdx, long nColNdx, OLE_HANDLE Hwnd, LPDISPATCH IDispatch)
		{FireEvent(eventidOnCellDeactivate,EVENT_PARAM(VTS_I4  VTS_I4  VTS_HANDLE  VTS_DISPATCH), nRowNdx, nColNdx, Hwnd, IDispatch);}
	void FireOnCellCreateHwnd(long nRowNdx, long nColNdx, OLE_HANDLE Hwnd, LPDISPATCH IDispatch)
		{FireEvent(eventidOnCellCreateHwnd,EVENT_PARAM(VTS_I4  VTS_I4  VTS_HANDLE  VTS_DISPATCH), nRowNdx, nColNdx, Hwnd, IDispatch);}
	void FireOnCellDestroyHwnd(long nRowNdx, long nColNdx, OLE_HANDLE Hwnd, LPDISPATCH IDispatch)
		{FireEvent(eventidOnCellDestroyHwnd,EVENT_PARAM(VTS_I4  VTS_I4  VTS_HANDLE  VTS_DISPATCH), nRowNdx, nColNdx, Hwnd, IDispatch);}
	void FireOnGetCellBitmap(long nRowNdx, long nColNdx, LPDISPATCH FAR* lpBitmap, BOOL FAR* Stretch, short FAR* Justify)
		{FireEvent(eventidOnGetCellBitmap,EVENT_PARAM(VTS_I4  VTS_I4  VTS_PDISPATCH  VTS_PBOOL  VTS_PI2), nRowNdx, nColNdx, lpBitmap, Stretch, Justify);}
	void FireOCXCellMouseDown(short Button, short Shift, long x, long y, LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellMouseDown,EVENT_PARAM(VTS_I2  VTS_I2  VTS_I4  VTS_I4  VTS_DISPATCH), Button, Shift, x, y, IDispatch);}
	void FireOCXCellMouseMove(short Button, short Shift, long x, long y, LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellMouseMove,EVENT_PARAM(VTS_I2  VTS_I2  VTS_I4  VTS_I4  VTS_DISPATCH), Button, Shift, x, y, IDispatch);}
	void FireOCXCellMouseUp(short Button, short Shift, long x, long y, LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellMouseUp,EVENT_PARAM(VTS_I2  VTS_I2  VTS_I4  VTS_I4  VTS_DISPATCH), Button, Shift, x, y, IDispatch);}
	void FireOCXCellClick(LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellClick,EVENT_PARAM(VTS_DISPATCH), IDispatch);}
	void FireOCXCellDblClick(LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellDblClick,EVENT_PARAM(VTS_DISPATCH), IDispatch);}
	void FireOCXCellKeyUp(short KeyCode, short Shift, LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellKeyUp,EVENT_PARAM(VTS_I2  VTS_I2  VTS_DISPATCH), KeyCode, Shift, IDispatch);}
	void FireOCXCellKeyDown(short KeyCode, short Shift, LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellKeyDown,EVENT_PARAM(VTS_I2  VTS_I2  VTS_DISPATCH), KeyCode, Shift, IDispatch);}
	void FireOCXCellKeyPress(short FAR* KeyAscii, LPDISPATCH IDispatch)
		{FireEvent(eventidOCXCellKeyPress,EVENT_PARAM(VTS_PI2  VTS_DISPATCH), KeyAscii, IDispatch);}
	void FireOnHScroll(long pos)
		{FireEvent(eventidOnHScroll,EVENT_PARAM(VTS_I4), pos);}
	void FireOnVScroll(long pos)
		{FireEvent(eventidOnVScroll,EVENT_PARAM(VTS_I4), pos);}
	void FireOnGridError(long nRowNdx, long nColNdx, long nErrorCode, LPCTSTR strDescription)
		{FireEvent(eventidOnGridError,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4  VTS_BSTR), nRowNdx, nColNdx, nErrorCode, strDescription);}
	void FireOLEStartDrag(LPDISPATCH FAR*  Data, long FAR* AllowedEffects)
		{FireEvent(eventidOLEStartDrag,EVENT_PARAM(VTS_PDISPATCH  VTS_PI4), Data, AllowedEffects);}
	void FireOLEGiveFeedback(long FAR* Effect, BOOL FAR* DefaultCursors)
		{FireEvent(eventidOLEGiveFeedback,EVENT_PARAM(VTS_PI4  VTS_PBOOL), Effect, DefaultCursors);}
	void FireOLESetData(LPDISPATCH FAR*  Data, short FAR* DataFormat)
		{FireEvent(eventidOLESetData,EVENT_PARAM(VTS_PDISPATCH  VTS_PI2), Data, DataFormat);}
	void FireOLECompleteDrag(long FAR* Effect)
		{FireEvent(eventidOLECompleteDrag,EVENT_PARAM(VTS_PI4), Effect);}
	void FireOLEDragOver(LPDISPATCH FAR*  Data, long FAR* Effect, short FAR* Button, short FAR* Shift, float FAR* x, float FAR* y, short FAR* State)
		{FireEvent(eventidOLEDragOver,EVENT_PARAM(VTS_PDISPATCH  VTS_PI4  VTS_PI2  VTS_PI2  VTS_PR4  VTS_PR4  VTS_PI2), Data, Effect, Button, Shift, x, y, State);}
	void FireOLEDragDrop(LPDISPATCH FAR*  Data, long FAR* Effect, short FAR* Button, short FAR* Shift, float FAR* x, float FAR* y)
		{FireEvent(eventidOLEDragDrop,EVENT_PARAM(VTS_PDISPATCH  VTS_PI4  VTS_PI2  VTS_PI2  VTS_PR4  VTS_PR4), Data, Effect, Button, Shift, x, y);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGWOleControl)
	//}}AFX_DISP_ID
	dispidGridLines = 0x10001L,
	dispidRows = 0x10002L,
	dispidColumns = 0x10003L,
	dispidColSelect = 0x10004L,
	dispidColResize = 0x10005L,
	dispidRowSelect = 0x10006L,
	dispidRowResize = 0x10007L,
	dispidGridLineColor = 0x10008L,
	dispidSelectionMode = 0x10009L,
	dispidScrollBars = 0x1000AL,
	dispidDisableNoScroll = 0x1000BL,
	dispidAutoSizeColumns = 0x1000CL,
	dispidDefaultColumnWidth = 0x1000DL,
	dispidOLEDragAndDrop = 0x1000EL,
	dispidDefaultRowHeight = 0x1000FL,
	dispidSizingRegionWidth = 0x10010L,
	dispidThumbScroll = 0x10011L,
	dispidRowColUnits = 0x10012L,
	dispidGridSettings = 0x10013L,
	dispidShowTabs = 0x10014L,
	dispidNumSheets = 0x10015L,
	dispidListboxMode = 0x10016L,
	dispidHeaderCellColor = 0x10017L,
	dispidAddRow = 0x10018L,
	dispidDefaultCellType = 0x10019L,
	dispidSheet = 0x1001AL,
	dispidInsertNewSheet = 0x1001BL,
	dispidActiveSheet = 0x1001CL,
	dispidActivateSheet = 0x1001DL,
	dispidRegisterValidStringObject = 0x1001EL,
	dispidRefreshValidStringObjects = 0x1001FL,
	dispidPropertyFile = 0x10020L,
	dispidWantOnGetCellText = 0x10021L,
	dispidWantOnSetCellText = 0x10022L,
	dispidSizeColumnTopToBottom = 0x10023L,
	dispidSizeRowLeftToRight = 0x10024L,
	dispidDockedRows = 0x10025L,
	dispidDockedColumns = 0x10026L,
	dispidColumnDragStyle = 0x10027L,
	dispidRowDragStyle = 0x10028L,
	dispidRangeDragStyle = 0x10029L,
	dispidHwndBackColor = 0x1002AL,
	dispidTabControlStyle = 0x1002BL,
	dispidHiliteNoFocus = 0x1002CL,
	dispidClipHeadings = 0x1002DL,
	dispidShowEditIndicators = 0x1002EL,
	dispidMousePointer = 0x1002FL,
	dispidGetCurrentCell = 0x10030L,
	dispidSetCurrentCell = 0x10031L,
	dispidSetCellText = 0x10032L,
	dispidSetRangeText = 0x10033L,
	dispidGetCellText = 0x10034L,
	dispidGetRangeText = 0x10035L,
	dispidSort = 0x10036L,
	dispidSeek = 0x10037L,
	dispidSeekNext = 0x10038L,
	dispidReplace = 0x10039L,
	dispidReplaceNext = 0x1003AL,
	dispidReSort = 0x1003BL,
	dispidSaveGridSettings = 0x1003CL,
	dispidLoadGridSettings = 0x1003DL,
	dispidSetAutoSizeControlHeight = 0x1003EL,
	dispidSetAutoSizeControlWidth = 0x1003FL,
	dispidDefaultCellID = 0x10041L,
	dispidCurrentSheet = 0x10047L,
	eventidOnGetCellText = 1001L,
	eventidOnSetCellText = 1002L,
	eventidSelChange = 1003L,
	eventidOnActivateSheet = 1004L,
	eventidOnValidateCell = 1005L,
	eventidOnCellSelChange = 1006L,
	eventidOnGetCellValidString = 1007L,
	eventidOnChangeRowHeight = 1008L,
	eventidOnChangeColWidth = 1009L,
	eventidOnCellError = 1010L,
	eventidOnCellClick = 1011L,
	eventidOnCellDblClick = 1012L,
	eventidOnCellNotify = 1013L,
	eventidOnGetDefaultCellText = 1014L,
	eventidOnClearAllData = 1015L,
	eventidOnAddRow = 1016L,
	eventidOnAddColumn = 1017L,
	eventidOnDeleteRow = 1018L,
	eventidOnDeleteColumn = 1019L,
	eventidOnInsertRow = 1020L,
	eventidOnInsertColumn = 1021L,
	eventidOnCopyRow = 1022L,
	eventidOnCopyColumn = 1023L,
	eventidOnMoveRow = 1024L,
	eventidOnMoveColumn = 1025L,
	eventidIsPageBreakRow = 1026L,
	eventidIsPageBreakColumn = 1027L,
	eventidOnFillCache = 1028L,
	eventidOnCellActivate = 1029L,
	eventidOnCellDeactivate = 1030L,
	eventidOnCellCreateHwnd = 1031L,
	eventidOnCellDestroyHwnd = 1032L,
	eventidOnGetCellBitmap = 1033L,
	eventidOCXCellMouseDown = 1034L,
	eventidOCXCellMouseMove = 1035L,
	eventidOCXCellMouseUp = 1036L,
	eventidOCXCellClick = 1037L,
	eventidOCXCellDblClick = 1038L,
	eventidOCXCellKeyUp = 1039L,
	eventidOCXCellKeyDown = 1040L,
	eventidOCXCellKeyPress = 1041L,
	eventidOnHScroll = 1042L,
	eventidOnVScroll = 1043L,
	eventidOnGridError = 1044L,
	eventidOLEStartDrag = 1045L,
	eventidOLEGiveFeedback = 1046L,
	eventidOLESetData = 1047L,
	eventidOLECompleteDrag = 1048L,
	eventidOLEDragOver = 1049L,
	eventidOLEDragDrop = 1050L,
	};
};
#endif
