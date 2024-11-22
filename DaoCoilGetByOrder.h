#if !defined(AFX_DAOCOILGETBYORDER_H__0BB0478E_2D15_4DB2_9933_706BBFEEC6A3__INCLUDED_)
#define AFX_DAOCOILGETBYORDER_H__0BB0478E_2D15_4DB2_9933_706BBFEEC6A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaoCoilGetByOrder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoCoilGetByOrder DAO recordset

class CDaoCoilGetByOrder : public CDaoRecordset
{
public:
	CDaoCoilGetByOrder(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoCoilGetByOrder)

// Field/Param Data
	//{{AFX_FIELD(CDaoCoilGetByOrder, CDaoRecordset)
	CString	m_ID;
	CString	m_Job_Number;
	CString	m_Section;
	double	m_Metres;
	double	m_Tonnage;
	CString	m_Coil_Code;
	BOOL	m_Complete;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_SearchOrder;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoCoilGetByOrder)
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

#endif // !defined(AFX_DAOCOILGETBYORDER_H__0BB0478E_2D15_4DB2_9933_706BBFEEC6A3__INCLUDED_)
