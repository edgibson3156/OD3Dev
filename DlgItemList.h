#if !defined(AFX_DLGITEMLIST_H__1344DE22_3B71_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_DLGITEMLIST_H__1344DE22_3B71_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgItemList.h : header file
//

#include "OD3Doc.h"
#include "ProductData.h"
#include "SelectByProfile.h"
#include "DaoCustomerSet.h"
#include "ProfileList.h"
#include "SelectProductByName.h"
#include "Item.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgItemList dialog

class CDlgItemList : public CDialog
{
// Construction
public:
	CDlgItemList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgItemList)
	enum { IDD = IDD_ITEMS_LIST_DIALOG };
	CListCtrl	m_accList;
	CListCtrl	m_listItemDisplay;
	CString	m_comboCodes;
	CString	m_comboNames;
	CString	m_comboProfile;
	//}}AFX_DATA

//	DataMembers
	COD3Doc*				m_pDoc;
	CString					m_sFilter;			//	customer filter
	CString					m_sSectionID;
	CString					m_sType;
	CProductData*			m_pSelectProductSet;
	CDaoCustomerSet*		m_pSelectCodes;
	CProductData*			m_pGetProduct;
	CProfileList*			m_pSelectProfile;
	CSelectProductByName*	m_pGetCode;
	CSelectByProfile*		m_pGetName;
	int				m_nType;
	double			m_nWeight;
	bool			m_bIsModified;

private:
	CItem*			m_pItem;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgItemList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int getFreeItemNumber(bool isAccessory);

	// Generated message map functions
	//{{AFX_MSG(CDlgItemList)
	virtual BOOL OnInitDialog();
	afx_msg void OnApplyItemNo();
	afx_msg void OnEditchangeComboProducts();
	afx_msg void OnJrProducts();
	afx_msg void OnSbeProducts();
	afx_msg void OnStandardProducts();
	afx_msg void OnSelchangeComboProductcodes();
	afx_msg void OnSelchangeComboProductnames();
	afx_msg void OnSelchangeComboProfile();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	SetItemPointer(CItem* pItem){m_pItem = pItem;};
	CItem*	GetItemPointer(){return m_pItem;};
private:
	void DefineListControl();
	void InitDisplayList();
	void SetRadio(bool ProdStand, bool ProdJR, bool ProdSBE);
	void GetRadio(int &ProdStand, int &ProdJR, int &ProdSBE);
	void PopCombos(LPCTSTR szFilter);
	bool IsCodeAssigned(LPCTSTR sProductCode);
	void addAccessory(void);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITEMLIST_H__1344DE22_3B71_11D3_913F_00104BBA02E4__INCLUDED_)
