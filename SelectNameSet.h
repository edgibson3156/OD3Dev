#if !defined(AFX_SELECTNAMESET_H__8F9CA841_678B_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SELECTNAMESET_H__8F9CA841_678B_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectNameSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectNameSet DAO recordset

class CSelectNameSet : public CDaoRecordset
{
public:
	CSelectNameSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSelectNameSet)

// Field/Param Data
	//{{AFX_FIELD(CSelectNameSet, CDaoRecordset)
	CString	m_Description;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectNameSet)
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

#endif // !defined(AFX_SELECTNAMESET_H__8F9CA841_678B_11D3_913F_00104BBA02E4__INCLUDED_)
