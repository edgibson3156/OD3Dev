#if !defined(AFX_SELECTBYGROUP_H__978FED41_69B7_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SELECTBYGROUP_H__978FED41_69B7_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectByGroup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectByGroup DAO recordset

class CSelectByGroup : public CDaoRecordset
{
public:
	CSelectByGroup(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSelectByGroup)

// Field/Param Data
	//{{AFX_FIELD(CSelectByGroup, CDaoRecordset)
	CString	m_RollSet_ID;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Group_Ident;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectByGroup)
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

#endif // !defined(AFX_SELECTBYGROUP_H__978FED41_69B7_11D3_913F_00104BBA02E4__INCLUDED_)
