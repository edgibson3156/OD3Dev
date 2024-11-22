#if !defined(AFX_PROCESSINGPAGE_H__7E9BD36B_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_PROCESSINGPAGE_H__7E9BD36B_1D10_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessingPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcessingPage dialog

class CProcessingPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CProcessingPage)

// Construction
public:
	CProcessingPage();
	~CProcessingPage();

// Dialog Data
	//{{AFX_DATA(CProcessingPage)
	enum { IDD = IDD_PROCESSING_PAGE };
	int		m_radioProcessAll;
	int		m_radioProcessAuto;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProcessingPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProcessingPage)
	afx_msg void OnRadioProcessAll();
	afx_msg void OnRadioProcessAuto();
	afx_msg void OnRadioOptionsPrompt();
	afx_msg void OnRadioSelectFiles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSINGPAGE_H__7E9BD36B_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
