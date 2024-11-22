#if !defined(AFX_SELECTSECTIONSET_H__3A8E3DA8_6763_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SELECTSECTIONSET_H__3A8E3DA8_6763_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectSectionSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectSectionSet DAO recordset

class CSelectSectionSet : public CDaoRecordset
{
public:
	CSelectSectionSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSelectSectionSet)

// Field/Param Data
	//{{AFX_FIELD(CSelectSectionSet, CDaoRecordset)
	CString	m_RollSet_ID;
	CString	m_Product_group;
	long	m_Depth;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectSectionSet)
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

#endif // !defined(AFX_SELECTSECTIONSET_H__3A8E3DA8_6763_11D3_913F_00104BBA02E4__INCLUDED_)
