// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__8BDEC0F1_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_LEFTVIEW_H__8BDEC0F1_1681_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Item.h"
#include "DlgItemList.h"

class COD3Doc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CImageList*	 m_pImgList;
	CTreeCtrl*	m_MainTree;
	CItem*	m_pItem;
	int	 m_iPrintStatus;
	bool m_Print;
	bool m_bDone;
	bool m_mode;

	CDaoDatabase*	m_pDB;

// Operations
private:
	bool GetItemPointer();
	bool GetAccItemPtr(HTREEITEM hItem);
	void PopTree();
	void DisplayElements();

public:
	COD3Doc* GetDocument();
	void PrintAllBeams(CDC* pDC, CPrintInfo* pInfo);
	void PrintItem(CDC* pDC, CPrintInfo* pInfo);
	void PrintItemDetails(CDC* pDC, CPrintInfo* pInfo);
	void PrintAccessoryDetails(CDC* pDC, CPrintInfo* pInfo);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	void printGo(CDC *pDC, CPrintInfo *pInfo);
	BOOL preparePrint(CPrintInfo *pInfo);
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	HTREEITEM m_pLastItem;
	void setParentState(void);
	int	 countSelection(void);
	bool testCheckBox(CItem *pItem, int iType);
	//{{AFX_MSG(CLeftView)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnProcessPrintAll();
	afx_msg void OnItemDelete();
	afx_msg void OnItemGenerate();
	afx_msg void OnItemPrint();
	afx_msg void OnItemTransfer();
	afx_msg void OnItemTransfer2();
	afx_msg void OnItemValidate();
	afx_msg void OnItemAddBeam();
	afx_msg void OnProcessPrintItem();
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateDumpSetreporttypeAllitems(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemPrint(CCmdUI* pCmdUI);
	afx_msg void OnDumpSetreporttypeAllitems();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdvancedMode();
	afx_msg void OnUpdateAdvancedMode(CCmdUI* pCmdUI);
	afx_msg void OnValSelection();
	afx_msg void OnUpdateValSelection(CCmdUI* pCmdUI);
	afx_msg void OnGenSelection();
	afx_msg void OnUpdateGenSelection(CCmdUI* pCmdUI);
	afx_msg void OnRepSelection();
	afx_msg void OnUpdateRepSelection(CCmdUI* pCmdUI);
	afx_msg void OnTranSelection();
	afx_msg void OnUpdateTranSelection(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void DefineImageList();

};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline COD3Doc* CLeftView::GetDocument()
   { return (COD3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__8BDEC0F1_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
