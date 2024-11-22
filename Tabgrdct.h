/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1999 McRae Software International, Inc.
//
//	Warning:  This computer program and source code  is  protected by copyright law and
//	international treaties and is the property of McRae Software International, Inc.
//  Unauthorized reproduction or distribution of this program
//	or source,  may result in severe civil and criminal penalties, and will be prosecuted 
//	to the maximum extent possible under law.
/////////////////////////////////////////////////////////////////////////////
// tabgrdct.h : header file
//
#ifndef __TABGRDCT_H__
#define __TABGRDCT_H__

#include "gwtabs.h"

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

/////////////////////////////////////////////////////////////////////////////
// CGWTabGridCtrl window
class GW_EXT_CLASS CGWTabGridCtrl : public CGWGridCtrl
{
//GW_CLASS{{(CGWTabGridCtrl)
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

public:
	DECLARE_DYNCREATE(CGWTabGridCtrl)
	DECLARE_GW_CUSTOM_CONTROL()


// Construction
public:
//GW_MEMBERS{{(CGWTabGridCtrl,"Construction")
	CGWTabGridCtrl();							//Default Constructor.
	virtual ~CGWTabGridCtrl();					//Default Destructor.
//}}GW_MEMBERS
	
//GW_MEMBERS{{(CGWTabGridCtrl,"Data Members")
	CGWSheetTabHolder m_SheetTabHolder;			//The container for the CGWSheetTab objects.
	BOOL m_bCustomControl;						//Indicated this control was create using the custom control on a dialog template.
    static CString m_strClass;					//The window class name for the custom control.
//}}GW_MEMBERS

// Operations
public:
//GW_MEMBERS{{(CGWTabGridCtrl,"Operations")
	void EnableWindow(BOOL bEnable)				//Enables or disables the grid control window.
		{
			m_SheetTabHolder.EnableWindow(bEnable);
			m_bEnabled = bEnable; 
			Refresh();
		}
	BOOL IsWindowEnabled(BOOL bEnable)			//Checks to see if grid control is enabled or disabled.
		{
			return m_bEnabled;
		}
   	virtual BOOL Create(CWnd* pParent, UINT nID, CRect Rect); //Call this function to create a new CGWTabGridCtrl window.
	void LoadTabs(CGWDataSource* pGWDataSource);			//Pull tab information from a CGWDataSource object and load it into the sheet tabs.
	void CheckSheetSettings(CGWDataSource* pGWDataSource);	//Check to make sure all sheets have proper grid settings object and create them if necessary.
	static BOOL RegisterGridControl();			//This function is used to register a new Grid control. You must call it once from InitInstance.
//}}GW_MEMBERS

	
// Implementation
public:

//GW_MEMBERS{{(CGWTabGridCtrl,"Overriden Virtual Functions")
	virtual CGWGridCellObject* GetControlCell()		//Retrieve the pointer to the cell which currently has edit focus.
		{
			return m_pControlCell;
		}
	virtual void OnAddSheet(CString csCaption);					//Overriden to add a CGWSheetTab object.
	virtual void OnRemoveSheet(int nSheet);						//Overriden to remove a CGWSheetTab object.
	virtual void OnInsertSheet(int nSheet, CString csCaption);	//Overriden to insert a CGWSheetTab object.
	virtual void OnChangeSheet(int nSheet, CString csCaption);	//Overriden to change a CGWSheetTab objects name.
	virtual void OnMoveSheet(int nSheet, int nCount);			//Overriden to move a CGWSheetTab object.
	virtual void OnActivateSheet(int nSheet = CURRENT_SHEET);	//Overriden to activate a CGWSheetTab object.
	void RearrangeSheetsDlg()									//Shows a dialog to re-arrange sheet tabs.
		{
			OnCommandArrangeTabs();
		}
	void InsertSheetDlg()										//Shows a dialog to insert a sheet tab.
		{
			OnCommandInsertTab();
		}
	void RenameSheetDlg()										//Shows a dialog to rename a sheet tab.
		{
			OnCommandRenameTab();
		}
	virtual void CalcGridRect();									//Calculates the grid region taking the tab area into consideration.
    virtual void AttachDataSource(CGWDataSource* pGWDataSource);	//Overriden to check sheet settings.
	virtual void GridShowScrollBar(UINT nSB, BOOL bShow)			//Hide or show scrollbars regardless of who owns them
		{
			m_SheetTabHolder.ShowScrollBar(nSB, bShow);
		}
	virtual void GWShowScrollBar(UINT nSB, BOOL bShow, BOOL bEnabled);   //Internal version of show scrollbar function. Overriden to take tab area into consideration.
	virtual CScrollBar* GetGridScrollBarCtrl(int nBar);				//Overriden to retrieve scrollbars taken over by tab area.
	virtual void GetGridWndClientRect(LPRECT rect)					//Get the client rectangle taking the tab area into consideration.
		{
			m_SheetTabHolder.GetClientRect(rect);
		}
//}}GW_MEMBERS

public: 
//GW_MEMBERS{{(CGWTabGridCtrl,"Overrideables")
   	virtual void OnCreateCtrl()										//Called just after the control has been created.
		{};
	virtual BOOL GetShowTabs()										//Called to determine if tabs should be shown.
		{
			return m_bShowTabs;
		}
	virtual void SetShowTabs(BOOL bShowTabs, BOOL bRefresh = TRUE);	//Called to set the show tabs flag.
	
//}}GW_MEMBERS

protected:
//GW_MEMBERS{{(CGWTabGridCtrl,"Message Handlers")
	afx_msg void OnPaint();														//Handled to paint the tabs as well as the grid.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Handled to process scroll messages for the tab scroller.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnSize(UINT nType, int cx, int cy);							//Handled to recalculate the tab area.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);						//Handled to turn off automatic scrollbars.
	afx_msg void OnCommandArrangeTabs();										//Launches dialog to re-arrange tabs.
	afx_msg void OnCommandInsertTab();											//Launches dialog to insert tabs.
	afx_msg void OnCommandDeleteTab();											//Handler to delete a tab.
	afx_msg void OnUpdateDeleteTab(CCmdUI* pCmdUI);								//CmdUI Handler for deleting a tab.
	afx_msg void OnCommandRenameTab();											//Launches a dialog to rename a tab.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()
};



#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif // __CGWTabGridCtrl

/////////////////////////////////////////////////////////////////////////////
