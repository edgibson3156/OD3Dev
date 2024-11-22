#if !defined(AFX_DAOCOILLIVEDUPLICATESECTIONS_H__7DB101D7_A157_4030_B004_3B88A0B36EC8__INCLUDED_)
#define AFX_DAOCOILLIVEDUPLICATESECTIONS_H__7DB101D7_A157_4030_B004_3B88A0B36EC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoCoilLiveDuplicateSections.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilLiveDuplicateSections DAO recordset

class CDaoCoilLiveDuplicateSections : public CDaoRecordset
{
public:
	CDaoCoilLiveDuplicateSections(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoCoilLiveDuplicateSections)

// Field/Param Data
	//{{AFX_FIELD(CDaoCoilLiveDuplicateSections, CDaoRecordset)
	CString	m_Section;
	CString	m_Job_Number;
	double	m_Tonnage;
	double	m_Metres;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoCoilLiveDuplicateSections)
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

#endif // !defined(AFX_DAOCOILLIVEDUPLICATESECTIONS_H__7DB101D7_A157_4030_B004_3B88A0B36EC8__INCLUDED_)
