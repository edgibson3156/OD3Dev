#if !defined(AFX_DLGNEWPROJECT_H__2F615FAC_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_DLGNEWPROJECT_H__2F615FAC_6C15_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewProject.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewProject dialog

class CDlgNewProject : public CDialog
{
// Construction
public:
	CDlgNewProject(CWnd* pParent = NULL);   // standard constructor
	int	m_nProjectType;

// Dialog Data
	//{{AFX_DATA(CDlgNewProject)
	enum { IDD = IDD_NEW_PROJECT };
	CEdit	m_ctrlProjName;
	CString	m_editProjectName;
	CString	m_editCustomerName;
	CString	m_editCustomerRef;
	CString	m_editDueDate;
	int		m_radioProjectType;
	CString	m_editJobDestination;
	CString	m_editComments;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewProject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewProject)
	afx_msg void OnSelectDuedateMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioProjtype1();
	afx_msg void OnRadioProjtype2();
	afx_msg void OnRadioProjtype3();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWPROJECT_H__2F615FAC_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
