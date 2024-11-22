#if !defined(AFX_DLGPROJECTOPTIONS_H__2F615FA1_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_DLGPROJECTOPTIONS_H__2F615FA1_6C15_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProjectOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProjectOptions dialog

class CDlgProjectOptions : public CDialog
{
// Construction
public:
	CDlgProjectOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProjectOptions)
	enum { IDD = IDD_PROJECT_OPTIONS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	int m_nProjectSettings;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProjectOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProjectOptions)
	afx_msg void OnProjectSetupButton();
	virtual void OnCancel();
	afx_msg void OnFileImportProjectsettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROJECTOPTIONS_H__2F615FA1_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
