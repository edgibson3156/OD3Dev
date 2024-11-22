#if !defined(AFX_DAOEAVESBYSLOPE_H__B6501E95_ACF3_41E6_BE33_35B02D5A96AB__INCLUDED_)
#define AFX_DAOEAVESBYSLOPE_H__B6501E95_ACF3_41E6_BE33_35B02D5A96AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoEavesBySlope.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoEavesBySlope DAO recordset

class CDaoEavesBySlope : public CDaoRecordset
{
public:
	CDaoEavesBySlope(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoEavesBySlope)

// Field/Param Data
	//{{AFX_FIELD(CDaoEavesBySlope, CDaoRecordset)
	CString	m_ProductCode;
	CString	m_ProductName;
	short	m_Angle;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	short m_iAngle;
	CString m_Prod_name;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoEavesBySlope)
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

#endif // !defined(AFX_DAOEAVESBYSLOPE_H__B6501E95_ACF3_41E6_BE33_35B02D5A96AB__INCLUDED_)
