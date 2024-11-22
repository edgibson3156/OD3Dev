#if !defined(AFX_DLGACCESSORIES_H__2F615FA9_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_DLGACCESSORIES_H__2F615FA9_6C15_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAccessories.h : header file
//
#include "Item.h"
#include "Element.h"

class CItem;
class CElement;
class CAccessoryElement;

/////////////////////////////////////////////////////////////////////////////
// CDlgAccessories dialog

class CDlgAccessories : public CDialog
{
// Construction
public:
	CDlgAccessories(COD3Doc *pDoc, CItem *pItem, CAccessoryElement *pElement, CWnd* pParent = NULL);   // Constructor

	void	*m_pView;	// Pointer from the list control or tree control views
	bool	m_bTree;	// Is the view a tree or list type

// Dialog Data
	//{{AFX_DATA(CDlgAccessories)
	enum { IDD = IDD_ACC_DIALOG };
	CEdit	m_quantity;
	CEdit	m_bundle;
	CEdit	m_comment;
	CEdit	m_length;
	CEdit	m_mark;
	CEdit	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAccessories)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	POSITION			m_elementPos;	// Stores position in current list
	COD3Doc				*m_pDoc;		// Pointer to current document
	CItem				*m_pItem;		// Pointer to item
	CAccessoryElement	*m_pElement;	// Pointer to the element to be edited

	int		m_iQuantity;
	int		m_iLength;
	int		m_iBundle;
	CString	m_sMark;
	CString m_sComment;

	bool dataPresent(void);
	void setElement(CAccessoryElement *pAcc);
	void cleanEdits(void);
	bool createAccessory(void);
	bool hasChanged(int iType);
	bool testAccMark(CString sMark);

	// Generated message map functions
	//{{AFX_MSG(CDlgAccessories)
	virtual BOOL OnInitDialog();
	afx_msg void OnAccPrev();
	afx_msg BOOL OnAccNext();
	afx_msg void OnAccSave();
	afx_msg void OnAccNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACCESSORIES_H__2F615FA9_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
