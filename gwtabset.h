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
// gwtabset.h : header file
//

#ifndef __GWTABSET_H__
#define __GWTABSET_H__


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
// CRenameTabDlg dialog

class GW_EXT_CLASS CRenameTabDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
//GW_MEMBERS{{(CRenameTabDlg,"Construction")
	CRenameTabDlg(CWnd* pParent = NULL);	// standard constructor
//}}GW_MEMBERS	

// Dialog Data
	//{{AFX_DATA(CRenameTabDlg)
	enum { IDD = IDD_GW_RENAME_TAB };
	//}}AFX_DATA

//GW_MEMBERS{{(CRenameTabDlg,"Data Members")
	CEdit	m_editTabName;							//Edit control containing the tab caption.
	CString	m_csTabName;							//The string buffer containing the tab name.
//}}GW_MEMBERS	

// Overrides
public:
//GW_MEMBERS{{(CRenameTabDlg,"Data Members")
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();						//Initialize the dialog before it is displayed.
//}}GW_MEMBERS	

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRenameTabDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CInsertTabDlg dialog

class GW_EXT_CLASS CInsertTabDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
//GW_MEMBERS{{(CInsertTabDlg,"Construction")
	CInsertTabDlg(CWnd* pParent = NULL);	// standard constructor
//}}GW_MEMBERS	

// Dialog Data
	//{{AFX_DATA(CInsertTabDlg)
	enum { IDD = IDD_GW_RENAME_TAB };
	//}}AFX_DATA

//GW_MEMBERS{{(CInsertTabDlg,"Data Members")
	CEdit	m_editTabName;							//Edit control containing the tab caption.
	CString	m_csTabName;							//The string buffer containing the tab name.
//}}GW_MEMBERS	


// Overrides
public:
//GW_MEMBERS{{(CInsertTabDlg,"Overrideables")
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();						//Initialize the dialog before it is displayed.
//}}GW_MEMBERS	

// Implementation
protected:

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CArrangeTabsDlg dialog

class GW_EXT_CLASS CArrangeTabsDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
//GW_MEMBERS{{(CArrangeTabsDlg,"Construction")
	CArrangeTabsDlg(CWnd* pParent = NULL);	// standard constructor
//}}GW_MEMBERS	

// Dialog Data
	//{{AFX_DATA(CArrangeTabsDlg)
	enum { IDD = IDD_GW_ARRANGE_TAB };
	//}}AFX_DATA

//GW_MEMBERS{{(CArrangeTabsDlg,"Data Members")
	CButton	m_btnMoveUp;						//Button for moving selected items up.
	CButton	m_btnMoveDown;						//Button for moving selected items down.
	CListBox	m_lbTabList;					//Listbox containing the captions for all the tabs.
    CObArray m_arWindowTabs;					//Copy of the array holding the CGWWindowTab objects.
    int m_nInitialSel;							//Index of the initial selection.
//}}GW_MEMBERS	

// Overrides
public:
//GW_MEMBERS{{(CInsertTabDlg,"Overrideables")
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    virtual void OnOK();								//Called when the user clicks the OK button.
	virtual BOOL OnInitDialog();						//Called to initialize the dialog before it is displayed.
//}}GW_MEMBERS	

	
// Implementation
protected:

//GW_MEMBERS{{(CInsertTabDlg,"Message Handlers")
	afx_msg void OnMovedown();							//Called when a Tab caption is moved down.
	afx_msg void OnMoveup();							//Called when a Tab caption is moved up.
	afx_msg void OnSelchangeTabList();					//Called when a new Tab caption is selected.
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


#endif //__GWTABSET_H__