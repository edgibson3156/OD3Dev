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
// popup.h : header file
//
#ifndef __GRIDPOP_H__
#define __GRIDPOP_H__


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
// CPopup window

class GW_EXT_CLASS CPopup : public CWnd
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_DYNCREATE(CPopup)
// Construction
public:

//GW_MEMBERS{{(CPopup,"Construction")
	CPopup();			//Default Constructor.
	virtual ~CPopup();	//Default Destructor.
//}}GW_MEMBERS	

// Attributes
public:
	static void RegisterPopup();
	static CString m_strClass;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);	

// Implementation
public:
//GW_MEMBERS{{(CPopup,"Message Handlers")
	virtual void PostNcDestroy();				//Handled to control destruction of the class.
	afx_msg void OnDestroy();					//Handled to control destruction of the class.
	afx_msg void OnKillFocus(CWnd* pNewWnd);	//Handled to control destruction of the class.
	afx_msg void OnNcDestroy();					//Handled to control destruction of the class.
//}}GW_MEMBERS	

protected:
	long OnUserMessageHandler(UINT nMsg, long l);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class GW_EXT_CLASS CGWGridPopup : public CPopup, public CGWGrid
{
//GW_CLASS{{(CGWGridPopup)
/*

Implementing a CGWGridPopup derived class is similar to CGWGridCtrl, except that you do not need to create an 
embedded member variable for your CGWGridPopup class. Typically, popup windows are displayed in response to a 
mouse event like a single left or right button click. Popup windows, like popup menus usually track mouse 
clicks after the window has been displayed and destroy themselves when the user clicks somewhere outside of 
its border. This is how the CGWGridPopup class behaves. Creating a CGWGridPopup object is a two step process. 
First, create the C++ object for the CGWGridPopup derived class. Usually this is done by allocating an instance 
of this object on the heap using the ‘new’ function. Next, create the actual window for the CGWGridPopup object 
by calling CGWGridPopup::Create(). The following example illustrates how a CGWGridPopup object can be created:

CEditPopup* pEditPopup = new CEditPopup(); 

ClientToScreen(&point); 

pEditPopup->m_pDoc = GetDocument();

pEditPopup->Create(CRect(point, CSize(300,150))); 

Please note, the coordinates sent to the Create function are screen coordinates, meaning that 0,0 is the top 
left corner of the screen. The CGWGrid base class has a member variable called m_pDoc which can be used to 
store a CDocument pointer. This helps provide consistency across all of the grid types. The CGWGridPopup window 
is destroyed when the user clicks the mouse button outside the border of the popup window or DestroyWindow() is 
called in response to some other event. The CGWGridPopup implementation of OnDestroy deletes the C++ object 
from the heap automatically.

See the Edit Sample for additional details.
*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWGridPopup)
public:
//The GridCell map allows you to easily format the grid. See GWIZGCO.H for cell types.
	DECLARE_GRIDCELL_MAP(CGWGridPopup)

		
public:
//GW_MEMBERS{{(CGWGridPopup,"Construction")
	CGWGridPopup();			//Default Constructor.
//}}GW_MEMBERS	

	static UINT CGWGridPopup::nPopupLostFocus;

public:

//GW_MEMBERS{{(CGWGridPopup,"Implementation")
	virtual void Initialize();				//Overidden to provide specifc grid settings prior to showing the grid.
   	virtual void OnCreateCtrl()				//Virtual function which allows derived classes to set properties before its displayed.
					{};
	virtual UINT OnGetDlgCode();			//This function is overriden to allow controls owned the grid to get messages.
   	virtual BOOL Create(CRect rectPopup);  	//Call this function to create a new CGridPopup window.
   	BOOL ResizeWindowToGrid();				//Shrink or grow the popup window to fit the number of rows and columns in the grid.
	virtual void CalcGridRect();			//Calculate the space required to display the grid.
	virtual CRect CalcControlSize(BOOL bRedraw = TRUE);         // Implements auto control sizing (OLE Control only).
//}}GW_MEMBERS	

protected:
//GW_MEMBERS{{(CGWGridPopup,"Message Handlers")
	afx_msg void OnPaint();														//Handled to pass the control to the base class paint function.		
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);						//Handled to pass the LButtonDown message to the Grid Cell Object.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);						//Handled to pass the LButtonUp message to the Grid Cell Object.
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);						//Handled to pass the RButtonDown message to the Grid Cell Object.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);						//Handled to pass the RButtonUp message to the Grid Cell Object.
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Passes the scroll message on to the grid base class.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);				//Passes the keydown message on to the cell and from the cell to the grid base class.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);					//Passes the char message on to the cell and from the cell to the grid base class.
	afx_msg void OnTimer(UINT nIDEvent);										//Passes the timer message on to the base grid class.
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Passes the VScroll message on to the grid base class.
	afx_msg void OnEditClear();													//Calls the grid's implementation of EditClear.			
	afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);								//Implements EditClear CmdUI feature.
	afx_msg void OnEditCopy();													//Calls the grid's implementation of EditCopy.	
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);								//Implements EditCopy CmdUI feature.
	afx_msg void OnEditCut();													//Calls the grid's implementation of EditCut.	
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);								//Implements EditCut CmdUI feature.
	afx_msg void OnEditPaste();													//Calls the grid's implementation of EditPaste.	
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);								//Implements EditCut CmdUI feature.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);						//Passes the mousemove message onto the grid cell object or to the base class grid.
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);					//Handled to pass the LButtonDblClk message to the Grid Cell Object.
	afx_msg void OnKillFocus(CWnd* pNewWnd);									//Handled to take care of remove hilite if necessary.
	afx_msg void OnSetFocus(CWnd* pOldWnd);										//Handled to take care of adding hilite if necessary.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);			//Handled to provide the default back color to individual controls within cells.
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);										//Returns TRUE to prevent the default erasing of the window.
	afx_msg void OnDestroy();													//Handled to process the destruction of the grid.
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWGridCtrl, "Registered GridWiz Messages")
	long OnGCOLostFocus(WPARAM wParam, LPARAM lParam);		//Sent when a editing GCO loses focus. 			
	long OnGetControlCell(WPARAM wParam, LPARAM lParam);	//Sent by a GCO to retrieve the m_pControlCell data member.
	long OnUserMessageHandler(UINT nMsg, long l);			//Sent by popup when the popup loses focuses. Triggers destruction of the grid.
	long OnClearCachedDCs(WPARAM wParam, LPARAM lParam);	//Low priority message which cleans up the collection of DCs.
	long OnZapCell(WPARAM wParam, LPARAM lParam);					//Low priority message kills a cell so that it can be recreated.
//}}GW_MEMBERS	

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

#endif // __GRIDPOP_H__
