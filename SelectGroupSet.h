#if !defined(AFX_SELECTGROUPSET_H__3A8E3DA7_6763_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SELECTGROUPSET_H__3A8E3DA7_6763_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectGroupSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectGroupSet DAO recordset

class CSelectGroupSet : public CDaoRecordset
{
public:
	CSelectGroupSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSelectGroupSet)

// Field/Param Data
	//{{AFX_FIELD(CSelectGroupSet, CDaoRecordset)
	CString	m_Product_group;
	BYTE	m_DisplayFlag;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectGroupSet)
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

#endif // !defined(AFX_SELECTGROUPSET_H__3A8E3DA7_6763_11D3_913F_00104BBA02E4__INCLUDED_)
