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
// odbcmap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGWODBCDataSource Collection class
#ifndef __ODBCMAP_H__
#define __ODBCMAP_H__
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
	#ifdef _GWEXTDLL
		#undef GW_EXT_CLASS
		#define GW_EXT_CLASS AFX_EXT_CLASS
	#endif	
#else //_WIN32
	#ifdef _GWEXTDLL
		#undef AFXAPP_DATA
		#define AFXAPP_DATA AFXAPI_DATA
	#endif //_WIN32
#endif


#ifndef _WIN32
#define AFX_RFX_TIMESTAMP_PSEUDO_NULL 99

void RFX_Date(CFieldExchange* pFX, const char *szName,
    TIMESTAMP_STRUCT& value);
#endif    

class CGWRecordset;
class GW_EXT_CLASS CGWODBCDataSource : public CCellDataMap
{
//GW_CLASS{{(CGWODBCDataSource)
/*
The CGWODBCDataSource class is a specialization of the CCellDataMap class which allows individual sheets to be
bound to ODBC recordsets. The recordset to be bound can be specified as the address of a existing MFC based
CRecordset object by setting the SheetExtraData pointer. This can be accessed through the SetSheetExtraData() 
method. When set to a valid reocrdset, the data source will open it, create the columns for each field and 
access the recordset for data as the CGWGrid based grid requests it. The other way to bind to a ODBC recordset is 
to use an instance of the GWDatabaseRequest class. This class defines the Connection string and SQL statement
to be bound. The CGWODBCDataSource class takes care of building the recordset and managing the connection to the 
mdb file. The main consideration on which approach you use depends on whether you want the grid to manage the
database. If you want to have other recordsets off of a single database object, it is better to use the first 
approach. If your grid will be the only accessor of the database, its better to use the second approach.

See the CGWDatabaseRequest class for additional details on setting up a connection to an access database. The
are two samples which deal specifically with ODBC: ODBCDEMO and ODBCTEST.

*/
//}}GW_CLASS	

	DECLARE_SERIAL(CGWODBCDataSource)
// Construction
public:
//GW_MEMBERS{{(CGWODBCDataSource,"Construction")
	CGWODBCDataSource();			//Default Constructor.
	virtual ~CGWODBCDataSource();	//Default Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWODBCDataSource,"Data Members")
	static CMapStringToPtr		m_mapDatabases;				//Collection of MFC CDatabase objects.
	static CPtrArray			m_Recordsets;				//Collection of MFC Recordset objects.
	static CStringArray			m_csaOpenDatabaseNames;		//Collection of open database names.
	static int					m_nRefCount;				//Reference count on ODBC connection.
//}}GW_MEMBERS



// Operations
public:
	
//GW_MEMBERS{{(CGWODBCDataSource,"Operations")
	CDatabase*  OpenDatabase(CString csConnect, BOOL bReadOnly);												//Opens a ODBC database for shared access by all sheets.
	CRecordset* OpenRecordset(CDatabase* pDB, CString csRecordSource, int nRecordsetType, CRecordset* pOldRS);	//Opens a ODBC recordset for shared access by all sheets.
	void operator=(CGWODBCDataSource& otherODBCDataSource);														//Copies one CGWODBCDataSource object to another.
	void GetRecordsetText(int nFieldNdx, CRecordset* pSet, CString& csCellText);								//Retrieves the contents of a particular field in the odbc recordset.
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWODBCDataSource,"Overriden Virtual Functions")
	virtual void Serialize(CArchive& ar);				//Stores and loads a CGWODBCDataSource object to and from a CArchive object.
	virtual void ActivateSheet(int nSheet);				//Overriden to evaluate the ODBC query for a particular sheet.
    virtual void DestroySheets();						//Overriden to free odbc objects.
	virtual void RefreshSheet(int nSheet = 0);			//Overriden to initialize column objects.
	virtual CString GetDefaultConnectType()				//Overriden to return the ODBC; connect string.
		{
			CString csConnect(_T("ODBC;")); 
			return csConnect;
		}
	virtual CGWDatabaseRequest* GetDatabaseRequest(int nSheet);										//Returns the database request for a particular sheet.
	virtual void SetDatabaseRequest(CGWDatabaseRequest* pDatabaseRequest, int nSheet);				//Specify a database request for a particular sheet.
	virtual void RequestTables(CGWDatabaseRequest* pGWDatabaseRequest);								//Retrieve the names of the tables available on this data source.
	virtual void RequestColumns(CGWDatabaseRequest* pGWDatabaseRequest);							//Retrieve the names of the columns available for a particular table on this data source.
	virtual void RefreshValidStringObjects();														//Rebuilds those valid string objects that are based on a database request.
	virtual int GetMaxRow(int nSheet);																//Get the largest data row index for a sheet.
	virtual int GetMaxCol(int nSheet);																//Get the largest data column index for a sheet.
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);		//Overriden to redirect the update the text field on the ODBC recordset.
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);		//Overriden to redirect the request the text field from the ODBC recordset.
	virtual void SetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0);			//Overriden to redirect the update the long integer field on the ODBC recordset.
	virtual void GetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0);			//Overriden to redirect the request the long integert field from the ODBC recordset.
	virtual void SetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0);		//Overriden to redirect the update the floating point field on the ODBC recordset.
	virtual void GetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0);		//Overriden to redirect the request the floating point field from the ODBC recordset.
	virtual void SetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0);	//Overriden to redirect update the date/time field on the ODBC recordset.
	virtual void GetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0);	//Overriden to redirect the request the date/time field from the ODBC recordset.
	virtual void DeleteRow(UINT nRowNdx, UINT nCount, int nSheet = 0);								//Overriden to delete the row on the ODBC result set.
	virtual void BindColumn(UINT nColNdx, UINT nFieldNdx, CObject* pObject, int nSheet = 0);		//Binds a column to a field of a ODBC result set.
	virtual BOOL ScrollToBottom(int nSheet);														//Force the result set to scroll to the end.
	virtual int FillCache(int nBegRow, int nSheet);			//Called from framework when a cache hit 
	virtual void UpdateCacheRow(int nRowNdx, int nSheet);	//Update a particular record in the cache
//}}GW_MEMBERS

// Attributes
public:	 
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;
};

/////////////////////////////////////////////////////////////////////////////
// CGWRecordset recordset
void AFXAPI RFX_GWLongBinary(CFieldExchange* pFX, LPCTSTR szName, CLongBinary& value);

class GW_EXT_CLASS CGWRecordset : public CRecordset
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
	enum nVarType
	{
		GW_RFX_BOOL,
		GW_RFX_DOUBLE,
		GW_RFX_LONG,
		GW_RFX_SINGLE,
		GW_RFX_INT,
		GW_RFX_DATE,
		GW_RFX_BYTE,
		GW_RFX_BINARY,
		GW_RFX_LONGBINARY,
		GW_RFX_TEXT,
		GW_RFX_VARCHAR,
		GW_RFX_LONGVARCHAR,
	} nVarTypes;

public:
	DECLARE_DYNAMIC(CGWRecordset)

//GW_MEMBERS{{(CGWRecordset,"Construction")
	CGWRecordset(CDatabase* pDatabase = NULL);		//Constructs a CGWRecordset object and assigns a MFC CDatabase object.
	~CGWRecordset();								//Default Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWRecordset,"Data Memebers")
	CString m_csSQL;								//SQL Statement to run.
	int     m_nType;								//Recordset type.
	CUIntArray m_uTypes;							//Array of field types.
	CPtrArray m_VarPtrs;							//Array of field addresses.
	CStringArray m_csaNames;						//Array of field names.
//}}GW_MEMBERS

	
//GW_MEMBERS{{(CGWRecordset,"Operations")
	void DestroyFieldData();						//Destroy the array of fields.
    void BuildFieldArray(CString& csSQL);			//Build an array of fields.
    void BuildFieldArrayFromTable(CString& csTableName);	//Build an array of fields from a table schema.
//}}GW_MEMBERS

public:
//GW_MEMBERS{{(CGWRecordset,"Overriden Virtual Functions")
	virtual CString GetDefaultConnect();					//Retrieve the default connection string
	virtual CString GetDefaultSQL();						//Retrieve the default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);		//Exchange data with the recordset and the array of field values.
	virtual BOOL Open(UINT nOpenType = snapshot, LPCTSTR lpszSql = NULL, DWORD dwOptions = none);	//Open the recordset.
	virtual BOOL Requery();									//Requery the recordset.
	virtual void Move(long lRows);							//Move the current position with in the recordset cursor.
	virtual void Close();									//Close the recordset.
	virtual void OnWaitForDataSource(BOOL bStillExecuting);	//Check to see if the recordsource is busy.
	virtual void OnSetOptions(HSTMT hstmt);					//Called to set recordset options.
//}}GW_MEMBERS

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//---------------------------------------------------------------------
// CColumns - results from SQLColumns()

class GW_EXT_CLASS CColumns : public CRecordset
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS

public:
//GW_MEMBERS{{(CColumns,"Construction")
	CColumns(CDatabase* pDatabase);			//Constructs a CColumns object and assigns an MFC CDatabase object.
//}}GW_MEMBERS

//GW_MEMBERS{{(CColumns,"Operations")
	BOOL			Open(LPCTSTR pszTableQualifier = NULL, LPCTSTR pszTableOwner = NULL, LPCTSTR pszTableName = NULL, LPCTSTR pszColumnName = NULL);	//Opens and runs the query.
//}}GW_MEMBERS

//GW_MEMBERS{{(CColumns,"Data Members")
	CString			m_strTableQualifier;		//Table qualifier.
	CString			m_strTableOwner;			//Table owner name.
	CString			m_strTableName;				//Table name.
	CString			m_strColumnName;			//Column Name.
	int				m_nDataType;				//Data Type.
	CString			m_strTypeName;				//Data Type name.
	long			m_nPrecision;				//Digits of precision.
	long			m_nLength;					//Length of field.
	int				m_nScale;					//Field scale.
	int				m_nRadix;					//Field Radix.
	int				m_fNullable;				//Flag indicating if field accepts NULL values.
	CString			m_strRemarks;				//Field remarks.
//}}GW_MEMBERS

//GW_MEMBERS{{(CColumns,"Overriden Virtual Functions")
	virtual CString GetDefaultConnect()			//Overriden to return a empty string.
		{ 
			return ""; 
		}
	virtual CString GetDefaultSQL()				//Overriden to return a empty string.
		{ 
			return ""; 
		}
	virtual void	DoFieldExchange(CFieldExchange*);	//Exchange field values with recordset and class data members.
//}}GW_MEMBERS
};
//---------------------------------------------------------------------
// CTables - results from SQLTables

class GW_EXT_CLASS CTables : public CRecordset
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CTables,"Operations")
	CTables(CDatabase* pDatabase);		//Construct a CTables object and assign a MFC CDatabase object.
//}}GW_MEMBERS

//GW_MEMBERS{{(CTables,"Operations")
	BOOL Open(LPCTSTR pszTableQualifier = NULL,LPCTSTR pszTableOwner = NULL,LPCTSTR pszTableName = NULL, LPCTSTR pszTableType = NULL);
//}}GW_MEMBERS

//GW_MEMBERS{{(CTables,"Data Members")
	CString			m_strTableQualifier;	//Table qualifier.
	CString			m_strTableOwner;		//Table owner name.
	CString			m_strTableName;			//Table name.
	CString			m_strTableType;			//Table type.
	CString			m_strRemarks;			//Table remarks.
//}}GW_MEMBERS

//GW_MEMBERS{{(CTables,"Overriden Virtual Functions")
	virtual CString GetDefaultConnect()					//Overriden to return a empty string.
		{ 
			return ""; 
		}
	virtual CString GetDefaultSQL()						//Overriden to return a empty string.
		{ 
			return ""; 
		}
	virtual void	DoFieldExchange(CFieldExchange*);	//Exchange field values with recordset and class data members.
//}}GW_MEMBERS
};

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif  //__ODBCMAP_H__
