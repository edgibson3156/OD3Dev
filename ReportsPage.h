#if !defined(AFX_REPORTSPAGE_H__7E9BD36C_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_REPORTSPAGE_H__7E9BD36C_1D10_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportsPage.h : header file
//

#include "ProductionLine.h"

/////////////////////////////////////////////////////////////////////////////
// CReportsPage dialog

class CReportsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CReportsPage)

// Construction
public:
	CReportsPage();
	~CReportsPage();

// Dialog Data
	//{{AFX_DATA(CReportsPage)
	enum { IDD = IDD_REPORTS_PAGE };
	CListCtrl	m_listReportPaths;
	CButton	m_buttonAddPath;
	CButton	m_buttonRemovePath;
	CButton	m_buttonAutopath;
	CButton	m_buttonNonAutoPath;
	CString	m_editAutoLines;
	CString	m_editNonAutoLines;
	CString	m_comboProdLine;
	//}}AFX_DATA

	// Database members
	COD3Doc*			m_pDoc;
	CDaoDatabase*		m_pDB;
	CProductionLine*	m_pProdLineSet;	

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReportsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CReportsPage)
	afx_msg void OnUpdateEditAutolines();
	afx_msg void OnUpdateEditNonautolines();
	virtual BOOL OnInitDialog();
	afx_msg void OnReportsAddButton();
	afx_msg void OnReportsRemoveButton();
	afx_msg void OnReportsAutoButton();
	afx_msg void OnReportsNonautoButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void DefineListControl();
	void InitReportList();
	void BitmapButtons();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTSPAGE_H__7E9BD36C_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
