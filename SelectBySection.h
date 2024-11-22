#if !defined(AFX_SELECTBYSECTION_H__7EEB4CE3_69C5_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SELECTBYSECTION_H__7EEB4CE3_69C5_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectBySection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectBySection DAO recordset

class CSelectBySection : public CDaoRecordset
{
public:
	CSelectBySection(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSelectBySection)

// Field/Param Data
	//{{AFX_FIELD(CSelectBySection, CDaoRecordset)
	CString	m_RollSet_ID;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Section_Ident;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectBySection)
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

#endif // !defined(AFX_SELECTBYSECTION_H__7EEB4CE3_69C5_11D3_913F_00104BBA02E4__INCLUDED_)
