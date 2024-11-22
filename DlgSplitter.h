#if !defined(AFX_DLGSPLITTER_H__B8D1F5DD_1ACC_4D6C_8B69_3C0AB71AFE4E__INCLUDED_)
#define AFX_DLGSPLITTER_H__B8D1F5DD_1ACC_4D6C_8B69_3C0AB71AFE4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSplitter.h : header file
//
#include "D3splitter.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitter dialog

class CDlgSplitter : public CDialog
{
// Construction
public:
	bool m_printed;
	bool m_exportedWarley;
	bool m_exportedIrvine;
	int	 m_pageNum;

	CDlgSplitter(CWnd* pParent = NULL);   // standard constructor

	CD3splitter	*m_splitClass;	// Set before modal call
	CImportDet3	*m_pImport;		// Set before modal call

// Dialog Data
	//{{AFX_DATA(CDlgSplitter)
	enum { IDD = IDD_SPLITD3 };
	CTreeCtrl	m_tree;
	CButton	m_exportWarley;
	CButton	m_exportIrvine;
	CButton	m_warleyRad;
	CButton	m_irvineRad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplitter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void testPageLimits(int height, int *yPos, CDC *dc, int textHeight, char *header);
	bool exportFile(CString fName, int site);
	CString openCommonDlg(int site);
	void addAccToTree(CImportD3Acc *acc);
	void addBeamToTree(CImportD3Beam *beam);

	// Generated message map functions
	//{{AFX_MSG(CDlgSplitter)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnWarleyRad();
	afx_msg void OnIrvineRad();
	afx_msg void OnExportwarley();
	afx_msg void OnExportirvine();
	afx_msg void OnPrintexports();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPLITTER_H__B8D1F5DD_1ACC_4D6C_8B69_3C0AB71AFE4E__INCLUDED_)
