#if !defined(AFX_DLGWHATSNEW_H__8B5CCAB4_E926_42E9_A541_954A1C20F3AD__INCLUDED_)
#define AFX_DLGWHATSNEW_H__8B5CCAB4_E926_42E9_A541_954A1C20F3AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWhatsNew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWhatsNew dialog

class CDlgWhatsNew : public CDialog
{
// Construction
public:
	CDlgWhatsNew(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWhatsNew)
	enum { IDD = IDD_WHATSNEW };
	CEdit	m_display;
	CButton	m_dontShow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWhatsNew)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWhatsNew)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWHATSNEW_H__8B5CCAB4_E926_42E9_A541_954A1C20F3AD__INCLUDED_)
