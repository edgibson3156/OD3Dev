#if !defined(AFX_DAOCOILJOBDETAILS_H__E398A22C_B188_4CAD_9631_2D97E2658D83__INCLUDED_)
#define AFX_DAOCOILJOBDETAILS_H__E398A22C_B188_4CAD_9631_2D97E2658D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoCoilJobDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilJobDetails DAO recordset

class CDaoCoilJobDetails : public CDaoRecordset
{
public:
	CDaoCoilJobDetails(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoCoilJobDetails)

// Field/Param Data
	//{{AFX_FIELD(CDaoCoilJobDetails, CDaoRecordset)
	CString	m_ID;
	CString	m_Job_Number;
	CString	m_Section;
	double	m_Metres;
	double	m_Tonnage;
	CString	m_Coil_Code;
	BOOL	m_Complete;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoCoilJobDetails)
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

#endif // !defined(AFX_DAOCOILJOBDETAILS_H__E398A22C_B188_4CAD_9631_2D97E2658D83__INCLUDED_)
