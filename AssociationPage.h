#if !defined(AFX_ASSOCIATIONPAGE_H__7E9BD367_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_ASSOCIATIONPAGE_H__7E9BD367_1D10_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AssociationPage.h : header file
//

#include "OD3Doc.h"
#include "ProductionLine.h"
#include "SelectGroupSet.h"
#include "SelectSectionSet.h"
#include "SelectNameSet.h"
//#include "GroupSelection.h"
#include "SelectBySection.h"
#include "SelectByGroup.h"

/////////////////////////////////////////////////////////////////////////////
// CAssociationPage dialog

class CAssociationPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CAssociationPage)

// Construction
public:
	CAssociationPage();
	~CAssociationPage();

// Dialog Data
	//{{AFX_DATA(CAssociationPage)
	enum { IDD = IDD_ASSOCIATIONS_PAGE };
	CListCtrl	m_listAssociation;
	CButton	m_buttoAssociate;
	CButton	m_buttonRemove;
	CString	m_comboProductionLine;
	CString	m_comboProducts;
	//}}AFX_DATA


// Data Members
	COD3Doc*			m_pDoc;

	// Database members
	CDaoDatabase*		m_pDB;
	CProductionLine*	m_pProdLineSet;
	CSelectGroupSet*	m_pProdGroupSet;
	CSelectSectionSet*	m_pSectionTypeSet;
	CSelectNameSet*		m_pProductsListSet;
//	CGroupSelection*	m_pProductsGroup;
	CSelectBySection*	m_pSectionSelectionSet;
	CSelectByGroup*		m_pProductsGroup;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAssociationPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAssociationPage)
	afx_msg void OnRemoveButton();
	afx_msg void OnAssociateButton();
	afx_msg void OnRadioProduct();
	afx_msg void OnRadioProductgroup();
	afx_msg void OnRadioSectionType();
	virtual BOOL OnInitDialog();
	afx_msg void OnKeydownAssociationList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickAssociationList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSysSelall();
	afx_msg void OnSysDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetRadio(bool ProdGroup, bool SectType /*, bool Products */);
	void GetRadio(int &ProdGroup, int &SectType /*, int &Products */);
	void InitAssociationList();
	void DefineListControl();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSOCIATIONPAGE_H__7E9BD367_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
