#if !defined(AFX_DLGMESSAGE_H__2AEE7CCA_187A_475F_8EAB_4470642CC6D2__INCLUDED_)
#define AFX_DLGMESSAGE_H__2AEE7CCA_187A_475F_8EAB_4470642CC6D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMessage.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgMessage dialog

class CDlgMessage : public CDialog
{
// Construction
public:
	CDlgMessage(CWnd* pParent = NULL, CString sMessage = "");   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMessage)
	enum { IDD = IDD_MESSAGE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_sMessage;
	// Generated message map functions
	//{{AFX_MSG(CDlgMessage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMESSAGE_H__2AEE7CCA_187A_475F_8EAB_4470642CC6D2__INCLUDED_)
