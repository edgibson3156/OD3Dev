#if !defined(AFX_INPUTPAGE_H__7E9BD368_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_INPUTPAGE_H__7E9BD368_1D10_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputPage dialog

class CInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CInputPage)

// Construction
public:
	CInputPage();
	~CInputPage();

// Dialog Data
	//{{AFX_DATA(CInputPage)
	enum { IDD = IDD_INPUTFILES_PAGE };
	CString	m_editAutoInputPath;
	CString	m_editProjectPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInputPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInputPage)
	afx_msg void OnUpdateAutoinput();
	afx_msg void OnUpdateProjectdir();
	afx_msg void OnAutopathButton();
	afx_msg void OnProjpathButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTPAGE_H__7E9BD368_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
