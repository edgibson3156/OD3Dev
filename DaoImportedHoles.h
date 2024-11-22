#if !defined(AFX_DAOIMPORTEDHOLES_H__2F615FAB_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_DAOIMPORTEDHOLES_H__2F615FAB_6C15_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoImportedHoles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoImportedHoles DAO recordset

class CDaoImportedHoles : public CDaoRecordset
{
public:
	CDaoImportedHoles(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoImportedHoles)

// Field/Param Data
	//{{AFX_FIELD(CDaoImportedHoles, CDaoRecordset)
	long	m_Additional_Hole_ID;
	CString	m_Section_ID;
	CString	m_Punch_Code;
	CString	m_Description;
	CString	m_Dim_ID;
	BOOL	m_On_Line;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Section_Ident;
	CString m_D3_HoleName;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoImportedHoles)
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

#endif // !defined(AFX_DAOIMPORTEDHOLES_H__2F615FAB_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
