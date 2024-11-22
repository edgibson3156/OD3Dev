#if !defined(AFX_DLGLISTACC_H__C51EE8A7_4CDC_428C_9F7E_8DDBCBC6F499__INCLUDED_)
#define AFX_DLGLISTACC_H__C51EE8A7_4CDC_428C_9F7E_8DDBCBC6F499__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgListAcc.h : header file
//
#include "ListCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgListAcc dialog

class CDlgListAcc : public CDialog
{
// Construction
public:
	CDlgListAcc(CWnd* pParent = NULL);   // standard constructor
	int		m_index;
	bool	m_printed;

	CString	m_sJobDetails;
// Dialog Data
	//{{AFX_DATA(CDlgListAcc)
	enum { IDD = IDD_LISTACC };
	CListCtrlEx	m_accList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgListAcc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgListAcc)
	afx_msg void OnClickAccList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusAccList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintAcc();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLISTACC_H__C51EE8A7_4CDC_428C_9F7E_8DDBCBC6F499__INCLUDED_)
