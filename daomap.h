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
// daomap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCellMap Collection class
#ifndef __DAOMAP_H__
#define __DAOMAP_H__


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


class GW_EXT_CLASS CGWDAOParamInfo : public CGWParamInfo
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS	
	friend class CCellDataMap;
	DECLARE_SERIAL(CGWDAOParamInfo)

// Construction
public:		
//GW_MEMBERS{{(CGWDAOParamInfo,"Construction")
	CGWDAOParamInfo(CString csParamName, short nParamType, COleVariant& pvarValue);  //Constructs a CGWDAOParamInfo Object
	CGWDAOParamInfo();			//Default Constructor.
	virtual ~CGWDAOParamInfo();	//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWDAOParamInfo,"Operations")
	void operator=(CGWDAOParamInfo& otherGWParamInfo);  //Copies a CGWDAOParamInfo Object
	virtual void Serialize(CArchive& ar);				//Serializes a CGWDAOParamInfo Object
	virtual void Copy(CGWParamInfo* pParam)				//Copies a CGWParamInfo or a CGWDAOParamInfo Object
											{
												CGWParamInfo::Copy(pParam); 
												m_varValue = ((CGWDAOParamInfo*) pParam)->m_varValue;
											}
	virtual	CGWParamInfo* Duplicate();					// Duplicates this object 
	virtual CString GetStringValue();					//Gets the text representation of the parameter value.
	virtual void SetValue(CString csParamVal);			//Sets the text representation of the parameter value.
//}}GW_MEMBERS

//Data members
//GW_MEMBERS{{(CGWDAOParamInfo,"Data Members")
	COleVariant  m_varValue;							//Actual parameter variable which is passed to recordset.
//}}GW_MEMBERS
public:
//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;
};


class GW_EXT_CLASS CGWDAODataSource : public CCellDataMap
{
//GW_CLASS{{(CGWDAODataSource)
/*
The CGWDAODataSource class is a specialization of the CCellDataMap class which allows individual sheets to be
bound to DAO recordsets. The recordset to be bound can be specified as the address of a existing MFC based
CDAORecordset object by setting the SheetExtraData pointer. This can be accessed through the SetSheetExtraData() 
method. When set to a valid reocrdset, the data source will open it, create the columns for each field and 
access the recordset for data as the CGWGrid based grid requests it. The other way to bind to a DAO recordset is 
to use an instance of the GWDatabaseRequest class. This class defines the querydef, tabledef or SQL statement
to be bound. The CGWDataSource class takes care of building the recordset and managing the connection to the 
mdb file. The main consideration on which approach you use depends on whether you want the grid to manage the
database. If you want to have other recordsets off of a single database object, it is better to use the first 
approach. If your grid will be the only accessor of the database, its better to use the second approach.

See the CGWDatabaseRequest class for additional details on setting up a connection to an access database. The
are two samples which deal specifically with DAO: DAODEMO and DAOTEST2.

*/
//}}GW_CLASS	
	DECLARE_SERIAL(CGWDAODataSource)
public:
// Construction
//GW_MEMBERS{{(CGWDAODataSource,"Construction")
	CGWDAODataSource();	//Default Constructor.
	virtual ~CGWDAODataSource();
//}}GW_MEMBERS

	
//GW_MEMBERS{{(CGWDAODataSource,"Data Members")
	static CStringArray m_csaOpenDatabaseNames;		//Array of database names so that files are only openned once.
	static CMapStringToPtr   m_mapDatabases;		//Pointers to internally created database objects.
	static CPtrArray    m_TableDefs;				//Pointers to internally created tabledefs.
	static CPtrArray	m_QueryDefs;				//Pointers to internally created querydefs.
	static CPtrArray    m_Recordsets;				//Pointers to internally created recordsets.
	static int			m_nRefCount;				//Reference count of Data Source.
//}}GW_MEMBERS
	static CString		m_csTempFile;

// Attributes
public:	 
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

	// Operations
public:

//GW_MEMBERS{{(CGWDAODataSource,"Operations")
	void SetParamValue(CDaoQueryDef* pDaoQD, CGWDatabaseRequest* pDbReq);		//Set the value of a parameter for the querydef
	void EditParameters(CDaoQueryDef* pDaoQD, CGWDatabaseRequest* pDbReq);      //Show a dialog box which edits the parameters for this querydef.
	virtual CDaoDatabase*  OpenDaoDatabase(CString csDatabase, BOOL bReadOnly, CString csConnect);  //Open or retrieve an already open CDaoDatabase object.
	virtual CDaoDatabase*  OpenDaoDatabase();														//Open a CDaoDatabase object.
	virtual CDaoTableDef*  OpenDaoTableDef(CDaoDatabase* pDaoDatabase, CString csRecordSource);		//Open or retrieve an already open CDaoTableDef object.
	virtual CDaoQueryDef*  OpenDaoQueryDef(CDaoDatabase* pDaoDatabase, CString csRecordSource);		//Open or retrieve an already open CDaoQueryDef object based on a tabledef.
	virtual CDaoRecordset* OpenDaoRecordset(CDaoTableDef* pTableDef, int nRecordsetType);			//Open or retrieve an already open CDaoRecordset object based on a querydef.
	virtual CDaoRecordset* OpenDaoRecordset(CDaoQueryDef* pDaoQueryDef, int nRecordsetType);		//Open or retrieve an already open CDaoRecordset object based on an SQL statement.
	virtual CDaoRecordset* OpenDaoRecordset(CDaoDatabase* pDatabase, CString csSQL, int nRecordsetType);	//Open or retrieve an already open CDaoRecordset object.
	virtual CDaoTableDef*  OpenDaoTableDef(CDaoDatabase* pDaoDatabase, CString csRecordSource,CString csConnection);	//Open or retrieve an already open CDaoTableDef object.
	int SetAbsolutePosition(CDaoRecordset* pSet, int nRowNdx);					//Set the absolute record position of a  dao recordset.
	void operator=(CGWDAODataSource& otherDAODataSource);						//Make a copy of this data source.
//}}GW_MEMBERS


public:
//Overridden virtual functions
//GW_MEMBERS{{(CGWDAODataSource, "Overriden Virtual Functions")
	virtual void Serialize(CArchive& ar);										//Overidden to serialize additional data members.
	virtual CString GetDefaultConnectType()										//Overidden to identify "Access" as the connection string.
		{CString csConnect(_T("Access")); return csConnect;}					
	virtual void RequestTables(CGWDatabaseRequest* pGWDatabaseRequest);			//Overidden to build a list of tables and queries from the data source.
	virtual void RequestColumns(CGWDatabaseRequest* pGWDatabaseRequest);		//Overidden to build a list of columns from the resordset.
	virtual void ActivateSheet(int nSheet);										//Overidden to activate and initialize an external database link.
	virtual void RefreshValidStringObjects();									//Overidden to reload any valid string objects which are based on external database links. 
    virtual void DestroySheets();												//Overidden to destroy the CSheet object held by this data source.
	virtual void ClearSheetData(int nSheet);									//Overidden to clear the contents of a sheet.
	virtual void SetRecordSourceType(int nRecordSourceType, int nSheet = 0);	//Overidden to set the recordsource type for an external database link.
	virtual void SetDatabaseConnect(CString csConnect, int nSheet = 0);			//Overidden to set the database connect string for an external database link.
	virtual void SetDatabasePath(CString csDatabasePath, int nSheet = 0);		//Overidden to set the path to the database for an external database link.
	virtual void SetDatabaseName(CString csDatabaseName, int nSheet = 0);		//Overidden to set the name of the database for an external database link.
	virtual void SetRecordSource(CString csRecordSource, int nSheet = 0);		//Overidden to identify the recordsource for an external database link.
	virtual void SetRecordsetType(int nRecordsetType, int nSheet = 0);			//Overidden to identify the recordset type for an external database link.
	virtual void SetDatabaseReadOnly(BOOL bReadOnly, int nSheet = 0);			//Overidden to specify the read-only flag for an external database link.
	virtual void RefreshSheet(int nSheet = 0);									//Overidden to cause a particular sheet object to recalculate and check any external database links.
	virtual void Requery(int nSheet = 0,int nType = dbOpenSnapshot, int nOptions = 0);	//Overidden to rerun a query associated with an external database link.
	virtual int GetMaxRow(int nSheet);											//Overidden to retrieve the largest row index associated with actual data.
	virtual int GetMaxCol(int nSheet);											//Overidden to retrieve the largest column index associated with actual data.
	virtual BOOL ScrollToBottom(int nSheet);									//Overidden to force the caching algorithm to search for the bottom of the data and then set the grid's scroll range.
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);	//Overidden to direct the text for a cell to the external database link.
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);	//Overidden to direct the text for a cell to the external database link.
	virtual void SetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0);		//Overidden to direct the request for a cell's value to the external database link.
	virtual void GetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0);		//Overidden to direct the request for a cell's value to the external database link.
	virtual void GetDefaultCellText(UINT nRowNdx, UINT nColNdx, CString& csDefaultCellText, int nSheet = 0); //Overidden to direct the request for default values to the external database link.
	virtual void SetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0);	//Overidden to direct the request for a cell's value to the external database link.
	virtual void GetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0);	//Overidden to direct the request for a cell's value to the external database link.
	virtual void SetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0);	//Overidden to direct the request for a cell's value to the external database link.
	virtual void GetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0);	//Overidden to direct the request for a cell's value to the external database link.
	virtual void DeleteRow(UINT nRowNdx, UINT nCount, int nSheet = 0);							//Overidden to direct the delete row request to the external database link.
	virtual void DeleteColumn(UINT nColNdx, UINT nCount, int nSheet = 0);						//Overidden to direct the delete column request  to the external database link.
	virtual void InsertRow(UINT nRowNdx, UINT nCount, int nSheet = 0);							//Overidden to direct the insert row request to the external database link.
	virtual void MoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = 0);	//Overidden to direct the insert column request to the external database link.
	virtual void BindColumn(UINT nColNdx, UINT nFieldNdx, CObject* pObject, int nSheet = 0);	//Overidden to bind a column to a field in the external database link.
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

#endif  //__DAOMAP_H__
