#if !defined(AFX_CEESECTFAIL_H__FA7E1C40_975B_4CA6_9F47_1C073BECD51E__INCLUDED_)
#define AFX_CEESECTFAIL_H__FA7E1C40_975B_4CA6_9F47_1C073BECD51E__INCLUDED_

#include "OD3Doc.h"	// Added by ClassView
#include "ListCtrlEx.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CeeSectFail.h : header file
//
//class COD3Doc;
/////////////////////////////////////////////////////////////////////////////
// CCeeSectFail dialog
class CCeeItemFaultDes : public CObject
{
public:
	CCeeItemFaultDes(){m_iItemID = 0;};
	virtual ~CCeeItemFaultDes(){m_ErrorText.RemoveAll();
								m_markText.RemoveAll();};

	int				m_iItemID;
	CStringArray	m_ErrorText;
	CStringArray	m_markText;

};

class CCeeSectFail : public CDialog
{
// Construction
public:
	CCeeItemFaultDes* getErrorDesPtr(int iID);
	CCeeSectFail(CWnd* pParent = NULL);   // standard constructor
	void setActiveDoc(COD3Doc *pDoc){m_pActiveDoc=pDoc;}

	CTypedPtrList<CObList, CCeeItemFaultDes*> m_tplErrors;
// Dialog Data
	//{{AFX_DATA(CCeeSectFail)
	enum { IDD = IDD_CEE_SECTION };
	CEdit	m_faultText;
	CButton	m_delCheck;
	CListCtrlEx	m_fList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCeeSectFail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void cleanMemory(void);
	int setRegistry(int check, bool read);

	int m_index;
	COD3Doc *m_pActiveDoc;

	//CDocument *m_pDocument;
	// Generated message map functions
	//{{AFX_MSG(CCeeSectFail)
	virtual void OnOK();
	afx_msg void OnDblclkFaillist(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClickFaillist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusFaillist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelItem();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEESECTFAIL_H__FA7E1C40_975B_4CA6_9F47_1C073BECD51E__INCLUDED_)
