#if !defined(AFX_PARTCODES_H__15428664_0E20_11D3_88B4_006008E6ADB9__INCLUDED_)
#define AFX_PARTCODES_H__15428664_0E20_11D3_88B4_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PartCodes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPartCodes DAO recordset

class CPartCodes : public CDaoRecordset
{
public:
	CPartCodes(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPartCodes)

// Field/Param Data
	//{{AFX_FIELD(CPartCodes, CDaoRecordset)
	CString	m_Description;
	CString	m_PartCodeID;
	long	m_ValidationID;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPartCodes)
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

#endif // !defined(AFX_PARTCODES_H__15428664_0E20_11D3_88B4_006008E6ADB9__INCLUDED_)
