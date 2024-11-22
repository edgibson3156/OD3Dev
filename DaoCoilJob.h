#if !defined(AFX_DAOCOILJOB_H__6FCDE969_8609_47E8_8667_4AD173702816__INCLUDED_)
#define AFX_DAOCOILJOB_H__6FCDE969_8609_47E8_8667_4AD173702816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoCoilJob.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilJob DAO recordset

class CDaoCoilJob : public CDaoRecordset
{
public:
	CDaoCoilJob(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoCoilJob)

// Field/Param Data
	//{{AFX_FIELD(CDaoCoilJob, CDaoRecordset)
	CString	m_Job_Number;
	CString	m_Customer_name;
	COleDateTime	m_Due_date;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoCoilJob)
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

#endif // !defined(AFX_DAOCOILJOB_H__6FCDE969_8609_47E8_8667_4AD173702816__INCLUDED_)
