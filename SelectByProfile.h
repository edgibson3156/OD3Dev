#if !defined(AFX_SELECTBYPROFILE_H__ECA02305_6A97_11D3_913F_00104BBA02E4__INCLUDED_)
#define AFX_SELECTBYPROFILE_H__ECA02305_6A97_11D3_913F_00104BBA02E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectByProfile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectByProfile DAO recordset

class CSelectByProfile : public CDaoRecordset
{
public:
	CSelectByProfile(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSelectByProfile)

// Field/Param Data
	//{{AFX_FIELD(CSelectByProfile, CDaoRecordset)
	CString	m_ProductCode;
	CString	m_Aviion_Prodcode;
	CString	m_Section_ID;
	double	m_Gauge;
	double	m_Weight;
	CString	m_Aviion_Desc;
	CString	m_ProductName;
	CString	m_Product_Type;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_Profile_ID;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectByProfile)
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

#endif // !defined(AFX_SELECTBYPROFILE_H__ECA02305_6A97_11D3_913F_00104BBA02E4__INCLUDED_)
