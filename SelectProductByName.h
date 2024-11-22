#if !defined(AFX_SELECTPRODUCTBYNAME_H__ECA02303_6A97_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SELECTPRODUCTBYNAME_H__ECA02303_6A97_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectProductByName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectProductByName DAO recordset

class CSelectProductByName : public CDaoRecordset
{
public:
	CSelectProductByName(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSelectProductByName)

// Field/Param Data
	//{{AFX_FIELD(CSelectProductByName, CDaoRecordset)
	CString	m_ProductCode;
	CString	m_Aviion_Prodcode;
	CString	m_Product_Type;
	CString	m_ProductName;
	CString	m_Section_ID;
	double	m_Gauge;
	double	m_Weight;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Aviion_Name;
	CString m_Customer_Filter;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectProductByName)
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

#endif // !defined(AFX_SELECTPRODUCTBYNAME_H__ECA02303_6A97_11D3_913F_00104BBA02E4__INCLUDED_)
