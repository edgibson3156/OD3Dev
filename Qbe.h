/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1998 McRae Software International, Inc.
//
//	Warning:  This computer program and source code  is  protected by copyright law and
//	international treaties and is the property of McRae Software International, Inc.
//  Unauthorized reproduction or distribution of this program
//	or source,  may result in severe civil and criminal penalties, and will be prosecuted 
//	to the maximum extent possible under law.
/////////////////////////////////////////////////////////////////////////////
// qbe.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CQBE form view
#ifndef __QBE_H__
#define __QBE_H__

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif  

#ifdef _MAC
#undef AFX_EXT_API
#undef AFX_EXT_CLASS
#define AFX_EXT_API
#define AFX_EXT_CLASS
#endif

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

#define GW_EXT_CLASS

#ifdef _WIN32
	#ifdef _GWDLLIMP
		#undef GW_EXT_CLASS
		#define GW_EXT_CLASS __declspec(dllimport)
	#else
		#ifdef _GWEXTDLL
			#undef GW_EXT_CLASS
			#define GW_EXT_CLASS AFX_EXT_CLASS
		#endif	
	#endif
#else //_WIN32
	#ifdef _GWEXTDLL
		#undef AFXAPP_DATA
		#define AFXAPP_DATA AFXAPI_DATA
	#endif //_WIN32
#endif


class CLB;
class GW_EXT_CLASS CQBE : public CDialog
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
{
public:
//GW_MEMBERS{{(CQBE,"Overriden Virtual Functions")
	CQBE(CGWDataSource* pGWDataSource, CGWDatabaseRequest* pGWDatabaseRequest, CWnd* pParent = NULL);	//Construct a CQBE recordset.
	virtual ~CQBE();						//Default Destructor.
//}}GW_MEMBERS

// Form Data
public:
	//{{AFX_DATA(CQBE)
	enum { IDD = IDD_GW_QBE };
	//}}AFX_DATA
//GW_MEMBERS{{(CQBE,"Data Members")
	CString	m_csCriteria;						//Data Member for the Criteria edit box.
	CString	m_csFieldCriteria;					//Data Member for the Field Criteria edit box.
	CString	m_csGroupBy;						//Data Member for the GroupBy edit box.
	CString	m_csOperator;						//Data Memeber for the Operator listbox.
	CString	m_csOrderBy;						//Data Member for the OrderBy listbox.
	CString	m_csSelectedFields;					//Data Member for the Selected fields listbox.
	CString	m_csTables;							//Data Member for the Tables listbox.
	CString	m_csValue;							//Data Member for the Value edit box.
	CString	m_csAndOr;							//Data Member for the AndOr listbox.
	CPoint m_mouseLoc;							//Temporary variable for holding the cursor loc during a drag operation.
	CGWDatabaseRequest m_GWDatabaseRequest;		//The database request object being edited.
	CGWDataSource* m_pGWDataSource;				//Pointer to a GridWiz Data Source.
	CLB m_LBGroupBy;							//Drag and drop enabled listbox.
	CLB m_LBOrderBy;							//Drag and drop enabled listbox.
	CLB m_LBFields;								//Drag and drop enabled listbox.
	CLB m_LBSelectedFields;						//Drag and drop enabled listbox.
//}}GW_MEMBERS

public:
//GW_MEMBERS{{(CQBE,"Data Members")
	int FindField(CString& csText);							//Finds the index of a field name with in the fields listbox.
	BOOL AddCriteria();										//Adds a new entry to the criteria collection.
	BOOL UpdateCriteria();									//Updates an existing criteria entry.
	void RefreshOrderBy();									//Repaints the OrderBy listbox.
	void GetOrderBy();										//Builds the OrderBy listbox.
	void RefreshGroupBy();									//Repaints the GroupBy listbox.
	void GetGroupBy();										//Builds the GroupBy listbox.
	CString GetCriteriaString(CString& csCriteria);			//Extract the criteria strings from the SQL query.
	void UpdateAll();										//Rebuild all the fields in the QBE form.
	void MakeSQL();											//Extract the contents of the QBE form and construct an SQL statement.
	void coaFCToCString(CString& cstr );					//Convert the contents of a CObarray to its string representation.
	void csaToCString(CStringArray* csa, CString& cstr);	//Convert the contrnts of a CStringArray to its string representation.
//}}GW_MEMBERS

//GW_MEMBERS{{(CQBE,"Overriden Virtual Functions")
	virtual void OnOK();									//Called when the clicks the OK button.
	virtual void DoDataExchange(CDataExchange* pDX);		//DDX/DDV support
//}}GW_MEMBERS

// Implementation
public:
//GW_MEMBERS{{(CQBE,"Message Handlers")
	afx_msg void OnSelchangeCriteria();				//Called when the user changes selection in the Criteria listbox.
	afx_msg void OnSelchangeTables();				//Called when the user changes selection in the Tables listbox.
	afx_msg void OnDropdownValue();					//Called when the Value combobox is dropped down.
	afx_msg void OnSelchangeFieldCriteria();		//Called when the user changes selection in the Field Criteria listbox.
	afx_msg void OnClickedUseJoin();				//Called when the Use Join button is checked or unchecked.
	afx_msg void OnClickedUseValues();				//Called when the Use Values button is checked or unchecked.
	afx_msg void OnSelchangeSelectedFields();		//Called when the user changes selection in the Selected Fields listbox.
	afx_msg void OnDropdownFieldCriteria();			//Called when the field criteria combobox is dropped.
	afx_msg void OnClickedShowQuery();				//Called when the show query button is clicked.
	afx_msg void OnClickedUpdate();					//Called when the Update button is clicked.
	afx_msg void OnClickedAdd();					//Called when the Add button is clicked.
	afx_msg void OnClickedDelete();					//Called when the delete button is clicked.
	afx_msg void OnSelchangeGroupBy();				//Called when the user changes selection in the Group By listbox.
	afx_msg void OnSelchangeOrderBy();				//Called when the user changes selection in the Order By listbox.
	afx_msg void OnDblclkSelectedFields();			//Called a selected field is double clicked.
	virtual BOOL OnInitDialog();					//Called when the dialog is loaded but before it is displayed.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
 
class CDragDropTarget : public CObject
{
public:
//GW_MEMBERS{{(CDragDropTarget,"Construction")
	CDragDropTarget();									//Default Constructor.
	CDragDropTarget(CLB* pSource, CLB* pDestination);	//Construct a CDragDropTarget object and initialize its source and destination pointers.
//}}GW_MEMBERS

//GW_MEMBERS{{(CQBE,"Data Members")
	CLB* m_Source;						//A possible source listbox.
	CLB* m_Destination;					//A possible destination listbox.
//}}GW_MEMBERS
};
 
/////////////////////////////////////////////////////////////////////////////
#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS


#endif  //QBE
