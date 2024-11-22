// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__8BDEC0E9_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_MAINFRM_H__8BDEC0E9_1681_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:


// Operations
public:
	BOOL StatusBarMsgUpdate(LPCTSTR lpszText);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool m_suppress;
	CString			m_regPath;
	CString			m_standardTemplatePath;
	bool			m_standardTemplate;
	CProgressCtrl	m_progressBar;
	CStatusBar		m_wndStatusBar;
	bool			m_bProgCreated;

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	BOOL CreateStatusBar();

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;
	CWinThread	*m_pThread;			// Thread pointer

// Generated message map functions
protected:
	bool setTemplateRegistry(CString path);
	int  loadStandardTemplate(void);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStandardTemp();
	afx_msg void OnStandardTempLoad();
	afx_msg void OnUpdateStandardTemp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStandardTempLoad(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8BDEC0E9_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
