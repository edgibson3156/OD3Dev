// OD3View.h : interface of the COD3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OD3VIEW_H__8BDEC0EF_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_OD3VIEW_H__8BDEC0EF_1681_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListViewEx.h"
#include "Item.h"
#include "Element.h"


class COD3View : public CListViewEx
{
protected: // create from serialization only
	COD3View();
	DECLARE_DYNCREATE(COD3View)

// Attributes
public:
	COD3Doc* GetDocument();
	CListView	m_RecordList;
	CListCtrl	m_DisplayListCtrl;
	CImageList* m_pImgList;
	bool		m_bCut;
	bool		m_bCopy;
	
private:
//	int m_nItemID;
	CItem*		m_pItem;
	CElement*	m_pElement;

// Operations
public:
	void DisplayElements(CItem* pItem);
	void DisplayBeam(CBeamElement* pBeam, LVITEM &ItemAttributes);
	void DisplayAccessory(CElement *pAcc, LVITEM& ItemAttributes);

//	void SetItemID(int nItemID){m_nItemID = nItemID;};
//	int	 GetItemID(){return m_nItemID;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COD3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

private:
	void DefineListControl();
	void DefineImageList();
	bool GetElementPointer();
	bool GetElementPointer(int selIndex);

// view type helpers
public:
	BOOL	SetViewType(DWORD dwViewType);
	DWORD	GetViewType();
	bool	anySelected(void);

// Implementation
public:
	int isSelected(CString name);
	void RedrawListControls(void);
	void selectAllItems(void);
	virtual ~COD3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//	BOOL m_bStateIcons;

// Generated message map functions
protected:
	//{{AFX_MSG(COD3View)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewLargeicon();
	afx_msg void OnViewSmallicon();
	afx_msg void OnViewList();
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSmallicon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewLargeicon(CCmdUI* pCmdUI);
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnElementCopy();
	afx_msg void OnElementCut();
	afx_msg void OnElementDelete();
	afx_msg void OnElementEdit();
	afx_msg void OnElementPaste();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectallitems();
	afx_msg void OnUpdateElementDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateElementPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrintthiselement(CCmdUI* pCmdUI);
	afx_msg void OnPrintthiselement();
	afx_msg void OnUpdateSelectallitems(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OD3View.cpp
inline COD3Doc* COD3View::GetDocument()
   { return (COD3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OD3VIEW_H__8BDEC0EF_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
