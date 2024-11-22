#if !defined(AFX_DAOCUSTOMERSET_H__2F615FA6_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_DAOCUSTOMERSET_H__2F615FA6_6C15_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoCustomerSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoCustomerSet DAO recordset

class CDaoCustomerSet : public CDaoRecordset
{
public:
	CDaoCustomerSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoCustomerSet)

// Field/Param Data
	//{{AFX_FIELD(CDaoCustomerSet, CDaoRecordset)
	CString	m_Aviion_Prodcode;
	CString	m_Product_Type;
	CString	m_ProductName;
	CString	m_Section_ID;
	double	m_Gauge;
	double	m_Weight;
	CString	m_Aviion_Desc;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Customer_Filter;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoCustomerSet)
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

#endif // !defined(AFX_DAOCUSTOMERSET_H__2F615FA6_6C15_11D3_913F_00104BBA02E4__INCLUDED_)
