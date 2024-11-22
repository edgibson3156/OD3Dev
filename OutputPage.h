#if !defined(AFX_OUTPUTPAGE_H__7E9BD36A_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_OUTPUTPAGE_H__7E9BD36A_1D10_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputPage.h : header file
//

// Embedded recordsets
#include "OD3Doc.h"
#include "ProductionLine.h"

/////////////////////////////////////////////////////////////////////////////
// COutputPage dialog

class COutputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COutputPage)

// Construction
public:
	COutputPage();
	~COutputPage();

// Dialog Data
	//{{AFX_DATA(COutputPage)
	enum { IDD = IDD_OUTPUTFILES_PAGE };
	CEdit	m_outputPath;
	CButton	m_buttonRemove;
	CButton	m_buttonAdd;
	CListCtrl	m_listOutput;
	CString	m_comboOutputLine;
	//}}AFX_DATA


// Data Members
	// Database members
	COD3Doc*			m_pDoc;
	CDaoDatabase*		m_pDB;
	CProductionLine*	m_pProdLineSet;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COutputPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COutputPage)
	afx_msg void OnOuputAddButton();
	afx_msg void OnOutputRemoveButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectOutpathButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void DefineListControl();
	void InitOutputList();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTPAGE_H__7E9BD36A_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
