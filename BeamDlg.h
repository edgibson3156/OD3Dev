#if !defined(AFX_BEAMDLG_H__0C967666_1731_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_BEAMDLG_H__0C967666_1731_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BeamDlg.h : header file
//

#include "ProfileList.h"
#include "PartCodes.h"
#include "Element.h"
#include "Item.h"

class CItem;
class COD3Doc;
class CBeamElement;
class CValidationMask;

/////////////////////////////////////////////////////////////////////////////
// CBeamDlg dialog

class CBeamDlg : public CDialog
{
// Construction
public:
	CBeamDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL Create();
	void OnNewBeam();
	void OnRefreshBeam();
	void DeleteBeam();

// Dialog Data
	//{{AFX_DATA(CBeamDlg)
	enum { IDD = IDD_MANUAL_BEAM_INPUT };
	CButton	m_serviceHoles;
	CButton	m_type1;
	CButton	m_type2;
	CEdit	m_ctrlSpan3;
	CEdit	m_ctrlSpan2;
	CEdit	m_ctrlSpan1;
	CEdit	m_ctrlQty;
	CEdit	m_ctrlOHang2;
	CEdit	m_ctrlOHang1;
	CEdit	m_ctrlLength;
	CEdit	m_ctrlMark;
	CComboBox	m_comboSPC;
	CComboBox	m_comboProfile;
	CString	m_editProfile;
	CString	m_editSPC;
	int		m_editBundleCount;
	int		m_editEBSlope;
	int		m_editLength;
	CString	m_editMarkNo;
	int		m_editOHang1;
	int		m_editOHang2;
	int		m_editQty;
	int		m_editSpan1;
	int		m_editSpan2;
	int		m_editSpan3;
	CString	m_sItemLabel;
	CString	m_sBeamLabel;
	//}}AFX_DATA

	int				m_cBeamCounter;
	int				m_nItemID;
	int				m_nMemberType;
	CString			m_sSection;
	CString			m_sGauge;
	CString			m_sComment;
	CBeamDlg*		m_pDlg;
	CDaoDatabase*	m_pDB;
	CProfileList*	m_pProduct;
	CPartCodes*		m_pSPC;
	COD3Doc*		m_pDoc;
	CItem*			m_pItem;
	CBeamElement*	m_pBeam;
	bool			m_bIsModified;
	bool			m_bUpdate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeamDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd*		m_pParent;
	int			m_nID;

	// Generated message map functions
	//{{AFX_MSG(CBeamDlg)
	afx_msg void OnSaveButton();
	afx_msg void OnPreviousButton();
	afx_msg void OnNextButton();
	afx_msg void OnRadioMtype1();
	afx_msg void OnRadioMtype2();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdditemButton();
	afx_msg void OnAddExtraBeam();
	afx_msg void OnChangeData();
	afx_msg void OnDeleteBeam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitGridCtrl(); 
	void RefreshGrid();

private:
	long	m_lValidation_ID;
	BOOL	m_bOhang1;
	BOOL	m_bOhang2;
	BOOL	m_bSpan1;
	BOOL	m_bSpan2;
	BOOL	m_bSpan3;
	long	m_lAdjustmentDim;
	BYTE	m_SpanSummingMask;

private:
	void	InitialUpdate();
	bool	PromptToSave();
	bool	ValidateInput();
	bool	GetMask();
	CString	BeamLabel(int);
	CString	ItemLabel(CItem* pItem);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAMDLG_H__0C967666_1731_11D3_88B5_006008E6ADB9__INCLUDED_)
