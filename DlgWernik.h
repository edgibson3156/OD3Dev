#if !defined(AFX_DLGWERNIK_H__89E1DC85_53EF_4589_B4B9_919BECD163BA__INCLUDED_)
#define AFX_DLGWERNIK_H__89E1DC85_53EF_4589_B4B9_919BECD163BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWernik.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWernik dialog

class CDlgWernik : public CDialog
{
// Construction
public:
	CDlgWernik(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWernik)
	enum { IDD = IDD_WERNIK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWernik)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWernik)
	virtual BOOL OnInitDialog();
	afx_msg void OnIswernik();
	afx_msg void OnNotwernik();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWERNIK_H__89E1DC85_53EF_4589_B4B9_919BECD163BA__INCLUDED_)
