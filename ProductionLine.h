#if !defined(AFX_PRODUCTIONLINE_H__F1B4D612_1688_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_PRODUCTIONLINE_H__F1B4D612_1688_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProductionLine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProductionLine DAO recordset

class CProductionLine : public CDaoRecordset
{
public:
	CProductionLine(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProductionLine)

// Field/Param Data
	//{{AFX_FIELD(CProductionLine, CDaoRecordset)
	CString	m_Line_ID;
	BYTE	m_Line_Type;
	BYTE	m_Auto;
	CString	m_Description;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProductionLine)
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

#endif // !defined(AFX_PRODUCTIONLINE_H__F1B4D612_1688_11D3_88B5_006008E6ADB9__INCLUDED_)
