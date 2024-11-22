#if !defined(AFX_VALIDATIONMASK_H__98F5BE81_48EC_11D3_81CC_0050048C8638__INCLUDED_)
#define AFX_VALIDATIONMASK_H__98F5BE81_48EC_11D3_81CC_0050048C8638__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ValidationMask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CValidationMask DAO recordset

class CValidationMask : public CDaoRecordset
{
public:
	CValidationMask(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CValidationMask)

// Field/Param Data
	//{{AFX_FIELD(CValidationMask, CDaoRecordset)
	long	m_Validation_ID;
	BOOL	m_Ohang1;
	BOOL	m_Ohang2;
	BOOL	m_Span1;
	BOOL	m_Span2;
	BOOL	m_Span3;
	long	m_AdjustmentDim;
	BYTE	m_SpanSummingMask;
	//}}AFX_FIELD
	// This data source is a query which contains parameters.  Note
	//  that these lines are placed outside of the ClassWizard comments,
	//  since ClassWizard can not currently browse or edit query parameters.
	//  You will have to modify these fields by hand if the parameters in your
	//  data source change.
	// You must set the recordset's parameter member variables to values before
	//  the recordset is opened.
	CString m_SPC_Ident;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValidationMask)
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

#endif // !defined(AFX_VALIDATIONMASK_H__98F5BE81_48EC_11D3_81CC_0050048C8638__INCLUDED_)