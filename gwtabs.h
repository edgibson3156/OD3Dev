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
// gwtabwnd.h : interface of the CGWTabView class
/////////////////////////////////////////////////////////////////////////////
#ifndef __GWTABS_H__
#define __GWTABS_H__


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
	#ifdef _GWTABDLLIMP
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


class GW_EXT_CLASS CGWSheetTab : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public: 
//GW_MEMBERS{{(CGWSheetTab,"Construction")
	CGWSheetTab()								//Default Constructor.
		{};
	CGWSheetTab(CString csCaption);				//Construct a Sheet tab and specify its caption.
//}}GW_MEMBERS	

// Attributes
protected:
//GW_MEMBERS{{(CGWSheetTab,"Data Members")
	CString m_csCaption;						//Sheet tab caption.
    CRect m_rectWindowTab;						//The coordinates of the tab within the grid window.
//}}GW_MEMBERS	

// Overrideables
public:
//GW_MEMBERS{{(CGWSheetTab,"Overrideables")
	virtual void OnDraw(CDC* pDC);
    virtual void OnDrawActive(CDC* pDC);
//}}GW_MEMBERS	

// Access methods
//GW_MEMBERS{{(CGWSheetTab,"Member Access Functions")
	inline CString GetCaption()							//Retrieve the caption for this tab.
		{
			return m_csCaption;
		}
	inline void SetCaption(CString csCaption)			//Set the caption for this tab.
		{
			m_csCaption = csCaption;
		}
	inline void GetWindowTabRect(LPRECT lpRect)			//Get the tab client coordinates.
		{
			*lpRect = m_rectWindowTab;
		}
	inline void SetWindowTabRect(CRect rect)			//Set the tab coordinates.
		{
			m_rectWindowTab = rect;
		}
//}}GW_MEMBERS	
};


class GW_EXT_CLASS CGWSheetTabHolder
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public: 
//GW_MEMBERS{{(CGWSheetTabHolder,"Construction")
	CGWSheetTabHolder();						//Default Constructor.
	virtual ~CGWSheetTabHolder();				//Default Destructor.
//}}GW_MEMBERS	

// Attributes
public:
//GW_MEMBERS{{(CGWSheetTabHolder,"Data Members")
	CWnd*		m_pWnd;							//The CWnd object holding this object.
	CGWGrid*	m_pGrid;						//The CGWGrid object that this tab holder object is attached too.
    CScrollBar* m_pHorizontalScrollBar;			//Pointer to the horizontal scroll bar attached to the grid window.
    CScrollBar* m_pVerticalScrollBar;			//Pointer to the vertical scroll bar attached to the grid window.
    CScrollBar* m_pSizeBox;						//Pointer to the sizebox scroll bar attached to the grid window.
    CScrollBar* m_pTabScrollBar;				//Pointer to the tab scroller scroll bar attached to the grid window.
    BOOL 	m_bVertical;						//Indicates if the vertical scrollbar is to be shown.
    BOOL    m_bHorizontal;						//Indicates if the horizontal scrollbar is to be shown.
    BOOL    m_bSizeBox;							//Indicates if the sizebox scrollbar is to be shown.
    BOOL    m_bTabScroll;						//Indicates if the tab scroller scrollbar is to be shown.
    BOOL    m_bTabEnabled;						//Indicates if a tab is to be enable or disabled.	
    int 	m_nHScrollBarLength;				//Length of the horizontal scrollbar attached to the grid window.
    int     m_nMinHScrollBarLength;				//The minimum allowable length of the horizontal scrollbar.
    int     m_nTabAreaLength;					//The length of the tab area under the grid.
    int     m_nTabOnlyLength;					//The length of visible tabs.
    int     m_nMinTabAreaLength;				//The minimum length of the tab area.
    int 	m_nTabScrollLength;					//The length of the tab scroller.
    int 	m_nTotalTabLength;					//The total length of all tabs.
	CFont  m_TabFont;							//Font to be used to draw the caption on the tab.
	CFont  m_ActiveTabFont;						//Font to be used to draw the active tabs caption.
    HCURSOR  m_hScrollSize;						//Cursor to be used to resize the scroll area.
    BOOL m_bSizingScrollBarNow;					//State variable indicating that sizing is ocurring.
    CObArray  m_arWindowTabs;					//Array of pointers to the CGWTab objects.
    int m_nActiveWindowTabIndex;				//The sheet index of the currently active tab.
	BOOL m_bShowTabs;							//Controls whether tabs are displayed.
//}}GW_MEMBERS	



//GW_MEMBERS{{(CGWSheetTabHolder,"Member Access Functions")
	void SetTabFont(LOGFONT* pLogFont);					//Set the tab font.
	CFont* GetTabFont()									//Get the tab font.
		{return &m_TabFont;} 
	void SetActiveTabFont(LOGFONT* pLogFont);			//Set the Active tab font.
	CFont* GetActiveTabFont()							//Get the Active tab font.
		{return &m_ActiveTabFont;} 
//}}GW_MEMBERS	

// Operations
public:
//GW_MEMBERS{{(CGWSheetTabHolder,"Operations")
	void GetClientRect(LPRECT lpRect);					//Get the client rect of the window and subtract out the tab area.
	void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);	//Show or hide one or more of the scrollbars.
	BOOL EnableScrollBar(int nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);	//Enable one or more of the scrollbars.
	void Invalidate(BOOL bErase = TRUE);				//Invalidate the grid window except for the tab area.
	void DestroyWindowTabs();							//Destroy the window tab objects.
	void GetTabAreaRect(LPRECT lpRect);					//Get the client coordinates of the tab area. 
	void GetSizingAreaRect(LPRECT lpRect);				//Get the area of the sizing region for the tab area.
	void UpdateVScroll(BOOL bRefresh = TRUE);			//Update the vertical scrollbar's position.
	void UpdateHScroll(BOOL bRefresh = TRUE);			//Update the horizontal scrollbar's position.
	void UpdateSizeBox(BOOL bRefresh = TRUE);			//Update the sizebox scrollbar's position.
	void TrackScrollBarSize(CPoint point);				//Track the size of the tab area.
	void RemoveWindowTab(int nIndex);					//Remove a particular window tab by its index.
	void RemoveWindowTab(CString csCaption);			//Remove a particular window tab by its name.
	void MoveWindowTab(int nIndex, int nCount);			//Move a window tab up or down nCount positions.
	BOOL ActivateWindowTab(int nIndex);					//Called to signal the window tab is being activated.
	int GetActiveWindowTabIndex();						//Get the index of the active window tab.
	CGWSheetTab* GetActiveWindowTab();					//Get the CGWSheetTab object for the active window tab.
	void UpdateWindowTabs();							//Recalculate all the window tabs.
	int WindowTabHitTest(CPoint point);					//Identify a window tab index based on a client coordinate point.
	void RefreshScrollTab();							//Refresh the the tab scrollers.
	void CreateScrollBars(BOOL bVertical, BOOL bHorizontal);		//Create all the required scrollbars for the grid.
	BOOL IsTabScrollVisible();							//Test to see if the tab scroller visible.
	BOOL IsSizeBoxVisible();							//Test to see if the size box is visible.
	BOOL IsVerticalScrollBarVisible();					//Test to see if the vertical scrollbar is visible.
	BOOL IsHorizontalScrollBarVisible();				//Test to see if the horizontal scrollbar is visible.
	void EnableWindow(BOOL bEnable)						//Enable or disable the window along with the tabs.
		{
			if (!m_pWnd->GetSafeHwnd())
				return;
			m_pWnd->CWnd::EnableWindow(bEnable);
			m_bTabEnabled = bEnable; 
			UpdateWindowTabs();
		}
	BOOL IsWindowEnabled(BOOL bEnable)					//Tests to see if the window is enabled.
		{
			return m_bTabEnabled;
		}
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWSheetTabHolder,"Operations")
	virtual void OnDraw(CDC* pDC);									//Overriden to draw tha tabs on this window.
	virtual CScrollBar* GetScrollBarCtrl( int nBar ) const;			//Get the address of a particular scrollbar control.
	virtual BOOL GetShowTabs()										//The the show tabs flag.
		{
			return m_bShowTabs;
		}
	virtual void SetShowTabs(BOOL bShowTabs)						//Set the show tabs floag.
		{
			m_bShowTabs = bShowTabs;
		}
//}}GW_MEMBERS	

public:
//GW_MEMBERS{{(CGWSheetTabHolder,"Message Handlers")
	afx_msg void OnSize(UINT nType, int cx, int cy);							//Handled to move scrollbars and recalculate the tab area.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);						//Handled to show the tab context menu.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);						//Handled to perform hit-testing and tab activation.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);						//Handled to perform tab area sizing.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);						//Handled to perform hit-testing and tab activation.
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Handled to scroll tabs.
//}}GW_MEMBERS	
};

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

                      
#endif   //__GWTABWND_H__                   
