#if !defined(AFX_SPCSCRIPT_H__69089F45_3086_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SPCSCRIPT_H__69089F45_3086_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpcScript.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpcScript DAO recordset

class CSpcScript : public CDaoRecordset
{
public:
	CSpcScript(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSpcScript)

// Field/Param Data
	//{{AFX_FIELD(CSpcScript, CDaoRecordset)
	long	m_Op_Script_ID;
	long	m_Operation_Sequence_No;
	CString	m_Operation;
	CString	m_Operation_Code;
	CString	m_Operation_Type;
	BOOL	m_Absolute;
	BOOL	m_Positive;
	BOOL	m_Multiplied;
	short	m_MultiplierValue;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpcScript)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCSCRIPT_H__69089F45_3086_11D3_913F_00104BBA02E4__INCLUDED_)
