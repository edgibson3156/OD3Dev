#if !defined(AFX_DAOACCOFFSET_H__8E7325F2_1C72_4979_924E_25DE2E92697F__INCLUDED_)
#define AFX_DAOACCOFFSET_H__8E7325F2_1C72_4979_924E_25DE2E92697F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoAccOffset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoAccOffset DAO recordset

class CDaoAccOffset : public CDaoRecordset
{
public:
	CDaoAccOffset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoAccOffset)

// Field/Param Data
	//{{AFX_FIELD(CDaoAccOffset, CDaoRecordset)
	CString	m_product_code;
	CString	m_aviion;
	CString	m_description;
	CString	m_section_id;
	double	m_weight;
	double	m_offset;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_prod_code;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoAccOffset)
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

#endif // !defined(AFX_DAOACCOFFSET_H__8E7325F2_1C72_4979_924E_25DE2E92697F__INCLUDED_)
