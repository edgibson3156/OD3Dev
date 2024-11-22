#if !defined(AFX_MANUALINPUTPAGE_H__7E9BD369_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_MANUALINPUTPAGE_H__7E9BD369_1D10_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManualInputPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManualInputPage dialog

class CManualInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CManualInputPage)

// Construction
public:
	CManualInputPage();
	~CManualInputPage();

// Dialog Data
	//{{AFX_DATA(CManualInputPage)
	enum { IDD = IDD_MANUALINPUT_PAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CManualInputPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CManualInputPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALINPUTPAGE_H__7E9BD369_1D10_11D3_88B5_006008E6ADB9__INCLUDED_)
