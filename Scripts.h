#if !defined(AFX_SCRIPTS_H__F41039E4_315D_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_SCRIPTS_H__F41039E4_315D_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Scripts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScripts DAO recordset

class CScripts : public CDaoRecordset
{
public:
	CScripts(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CScripts)

// Field/Param Data
	//{{AFX_FIELD(CScripts, CDaoRecordset)
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
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Line_Ident;
	CString m_Section_Ident;
	CString m_SPC_Ident;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScripts)
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

#endif // !defined(AFX_SCRIPTS_H__F41039E4_315D_11D3_88B5_006008E6ADB9__INCLUDED_)
