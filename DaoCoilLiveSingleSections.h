#if !defined(AFX_DAOCOILLIVESINGLESECTIONS_H__886F6B8F_9BE5_49A3_B46C_75EAD8CE798B__INCLUDED_)
#define AFX_DAOCOILLIVESINGLESECTIONS_H__886F6B8F_9BE5_49A3_B46C_75EAD8CE798B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoCoilLiveSingleSections.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilLiveSingleSections DAO recordset

class CDaoCoilLiveSingleSections : public CDaoRecordset
{
public:
	CDaoCoilLiveSingleSections(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoCoilLiveSingleSections)

// Field/Param Data
	//{{AFX_FIELD(CDaoCoilLiveSingleSections, CDaoRecordset)
	CString	m_Section;
	CString	m_Job_Number;
	double	m_Tonnage;
	double	m_Metres;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoCoilLiveSingleSections)
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

#endif // !defined(AFX_DAOCOILLIVESINGLESECTIONS_H__886F6B8F_9BE5_49A3_B46C_75EAD8CE798B__INCLUDED_)
