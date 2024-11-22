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
// tabgrdvw.h : header file
//
#ifndef __TABGRDVW_H__
#define __TABGRDVW_H__

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



//*********************************************************************************************************************
// class CGWTabGridView : public CGWTabView, public CGWGrid
// This is the class that actually implements the grid and all of its 
// base functionality. You should always derive your view from this class. 
// It is not recommended that you use this class alone. In order for this
// view to function properly, make certain that any virtual functions that 
// you override call this base classes implementation where appropriate 
// (which should be most of the time). 

CGWGridCellObject;
class GW_EXT_CLASS CGWTabGridView : public CGWGridView
{

//GW_CLASS{{(CGWTabGridView)
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
	DECLARE_DYNCREATE(CGWTabGridView)
	

//GW_MEMBERS{{(CGWTabGridView,"Construction")
	CGWTabGridView();					//Default Constructor.
	virtual ~CGWTabGridView();          //Default Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWTabGridView,"Data Members")
	CGWSheetTabHolder m_SheetTabHolder;		//The container for the CGWSheetTab objects.
	static UINT m_nReturnControlGCOLocal;	//Registered User Window Message.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWTabGridView,"Operations")
	void EnableWindow(BOOL bEnable)						//Enables or disables the grid control window.
		{
			m_SheetTabHolder.EnableWindow(bEnable);
			m_bEnabled = bEnable; 
			Refresh();
		}
	BOOL IsWindowEnabled(BOOL bEnable)					//Checks to see if grid control is enabled or disabled.
		{
			return m_bEnabled;
		}
	void LoadTabs(CGWDataSource* pGWDataSource);			//Pull tab information from a CGWDataSource object and load it into the sheet tabs.
	void CheckSheetSettings(CGWDataSource* pGWDataSource);	//Check to make sure all sheets have proper grid settings object and create them if necessary.
	void RearrangeSheetsDlg()								//Calls a command handler to show the re-arrange sheet tab dialog.
		{
			OnCommandArrangeTabs();
		}
	void InsertSheetDlg()									//Calls a command handler to show the insert sheet tab dialog.
		{
			OnCommandInsertTab();
		}
	void RenameSheetDlg()									//Calls a command handler to show the Rename sheet tab dialog.
		{
			OnCommandRenameTab();
		}
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWTabGridView,"Overriden Virtual Functions")
	virtual void OnInitialUpdate();		//Called as part of the document creation process and also when splitter panes are added. 
	virtual	void OnDraw(CDC* pDC);		//Overriden to pass control to tab handler for drawing.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo);
	virtual void GridShowScrollBar(UINT nSB, BOOL bShow)				//Hide or show scrollbars regardless of who owns them
		{
			m_SheetTabHolder.ShowScrollBar(nSB, bShow);
		}
	virtual void GWShowScrollBar(UINT nSB, BOOL bShow, BOOL bEnabled);  //Internal version of show scrollbar function. Overriden to take tab area into consideration.
	virtual CScrollBar* GetGridScrollBarCtrl(int nBar);					//Overriden to retrieve scrollbars taken over by tab area.
	virtual void GetGridWndClientRect(LPRECT rect)						//Get the client rectangle taking the tab area into consideration.
		{
			m_SheetTabHolder.GetClientRect(rect);
		}	
	virtual void OnAddSheet(CString csCaption);							//Overriden to add a CGWSheetTab object.
	virtual void OnRemoveSheet(int nSheet);								//Overriden to remove a CGWSheetTab object.
	virtual void OnInsertSheet(int nSheet, CString csCaption);			//Overriden to insert a CGWSheetTab object.
	virtual void OnChangeSheet(int nSheet, CString csCaption);			//Overriden to change a CGWSheetTab objects name.
	virtual void OnMoveSheet(int nSheet, int nCount);					//Overriden to move a CGWSheetTab object.
	virtual void OnActivateSheet(int nSheet = CURRENT_SHEET);			//Overriden to activate a CGWSheetTab object.
    virtual void AttachDataSource(CGWDataSource* pGWDataSource);		//Overriden to check sheet settings.
	virtual void CalcGridRect();										//Calculates the grid region taking the tab area into consideration.
//}}GW_MEMBERS


public:
//Overridables
//GW_MEMBERS{{(CGWTabGridView,"Overridables")
	virtual BOOL GetShowTabs()											//Called to determine if tabs should be shown.
		{
			return CGWGrid::GetShowTabs();
		}
	virtual void SetShowTabs(BOOL bShowTabs, BOOL bRefresh = TRUE);		//Called to set the show tabs flag.
//}}GW_MEMBERS


protected:
	//{{AFX_MSG(CGWTabGridView)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Handled to process scroll messages for the tab scroller.
	afx_msg void OnInitMenu(CMenu* pMenu);										//Handled to kill cell editing when a menu is invoked.
	afx_msg void OnSize(UINT nType, int cx, int cy);							//Handled to recalculate the tab area.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);						//Handled to do additional hit-testing for tabs.
	afx_msg void OnCommandArrangeTabs();										//Launches dialog to re-arrange tabs.
	afx_msg void OnCommandInsertTab();											//Launches dialog to insert tabs.
	afx_msg void OnCommandDeleteTab();											//Handler to delete a tab.
	afx_msg void OnUpdateDeleteTab(CCmdUI* pCmdUI);								//CmdUI Handler for deleting a tab.
	afx_msg void OnCommandRenameTab();											//Launches a dialog to rename a tab.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);						//Handled to turn off automatic scrollbars.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

/////////////////////////////////////////////////////////////////////////////

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif

#undef GW_EXT_CLASS

#endif //#ifndef //__GRIDVIEW
