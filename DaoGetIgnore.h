#if !defined(AFX_DAOGETIGNORE_H__B00330DE_AEAA_400F_8076_F58ED6F5D1E7__INCLUDED_)
#define AFX_DAOGETIGNORE_H__B00330DE_AEAA_400F_8076_F58ED6F5D1E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoGetIgnore.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoGetIgnore DAO recordset

class CDaoGetIgnore : public CDaoRecordset
{
public:
	CDaoGetIgnore(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoGetIgnore)

// Field/Param Data
	//{{AFX_FIELD(CDaoGetIgnore, CDaoRecordset)
	CString	m_Product_Name;
	CString	m_Product_Type;
	CString	m_Description;
	double	m_Gauge;
	double	m_Weight;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Sel_Name;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoGetIgnore)
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

#endif // !defined(AFX_DAOGETIGNORE_H__B00330DE_AEAA_400F_8076_F58ED6F5D1E7__INCLUDED_)
