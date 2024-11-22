#if !defined(AFX_DLGUPDATEJOBSTATUS_H__E3641D36_3CF9_475D_8994_3DE61AD9C29D__INCLUDED_)
#define AFX_DLGUPDATEJOBSTATUS_H__E3641D36_3CF9_475D_8994_3DE61AD9C29D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUpdateJobStatus.h : header file
//
#include "OD3Doc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgUpdateJobStatus dialog

class CDlgUpdateJobStatus : public CDialog
{
// Construction
public:
	CDlgUpdateJobStatus(CWnd* pParent = NULL, COD3Doc *pDoc = NULL);   // standard constructor

private:
	COD3Doc	*m_pDoc;
// Dialog Data
	//{{AFX_DATA(CDlgUpdateJobStatus)
	enum { IDD = IDD_UPDATECOILSTATUS };
	CStatic	m_orderNumLab;
	CEdit	m_jobNum;
	CListCtrl	m_jobList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUpdateJobStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUpdateJobStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnCoilJobserach();
	virtual void OnOK();
	afx_msg void OnKeydownCoilJoblist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPDATEJOBSTATUS_H__E3641D36_3CF9_475D_8994_3DE61AD9C29D__INCLUDED_)
