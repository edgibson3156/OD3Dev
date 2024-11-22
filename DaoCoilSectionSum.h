#if !defined(AFX_DAOCOILSECTIONSUM_H__6246CDAD_C5C8_4439_81D3_EE5A0F95EF1F__INCLUDED_)
#define AFX_DAOCOILSECTIONSUM_H__6246CDAD_C5C8_4439_81D3_EE5A0F95EF1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoCoilSectionSum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilSectionSum DAO recordset

class CDaoCoilSectionSum : public CDaoRecordset
{
public:
	CDaoCoilSectionSum(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoCoilSectionSum)

// Field/Param Data
	//{{AFX_FIELD(CDaoCoilSectionSum, CDaoRecordset)
	CString	m_Section;
	double	m_SumOfMetres;
	double	m_SumOfTonnage;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoCoilSectionSum)
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

#endif // !defined(AFX_DAOCOILSECTIONSUM_H__6246CDAD_C5C8_4439_81D3_EE5A0F95EF1F__INCLUDED_)
