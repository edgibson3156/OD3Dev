#if !defined(AFX_PUNCHVALUE_H__F41039E5_315D_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_PUNCHVALUE_H__F41039E5_315D_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PunchValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPunchValue DAO recordset

class CPunchValue : public CDaoRecordset
{
public:
	CPunchValue(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPunchValue)

// Field/Param Data
	//{{AFX_FIELD(CPunchValue, CDaoRecordset)
	double	m_Value;
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
	long m_Script_Ident;
	CString m_Punch_Ident;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPunchValue)
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

#endif // !defined(AFX_PUNCHVALUE_H__F41039E5_315D_11D3_88B5_006008E6ADB9__INCLUDED_)
