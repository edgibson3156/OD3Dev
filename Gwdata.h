/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1999 McRae Software International, Inc.
//
//	Warning:  This computer program and source code  is  protected by copyright law and
//	international treaties and is the property of McRae Software International, Inc.
//  Unauthorized reproduction or distribution of this program
//	or source,  may result in severe civil and criminal penalties, and will be prosecuted 
//	to the maximum extent possible under law.
/////////////////////////////////////////////////////////////////////////////
// gwdata.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGWDataSource Collection class
#ifndef __GWDATA_H__
#define __GWDATA_H__

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
#else
	#ifdef _GWEXTDLL
		#undef AFXAPP_DATA
		#define AFXAPP_DATA AFXAPI_DATA
	#endif //_WIN32
#endif
#ifndef INT_MAX
#define INT_MAX 32765
#endif

#if _MFC_VER > 0x0420

#include "GWDataLink.tlh"

#else
typedef IDispatch IDataLink;
#endif

#ifdef _GW_ADO15
#include "msado15.tlh"
using namespace ado15;
#else
typedef void* _RecordsetPtr;
#endif


#if _MFC_VER < 0x0600
typedef void IRowset;
#endif



#ifndef __AFXDB_H__
typedef struct tagTIMESTAMP_STRUCT
{
	WORD year;
	WORD month;
 	WORD day;
 	WORD hour;
 	WORD minute;
	WORD second;
	DWORD fraction; 
	
} TIMESTAMP_STRUCT; 
#endif //TIMESTAMP_STRUCT


//This is a non-persistant object which keeps trak of valid values. This object is
//usually assigned to a range of cells which have either a drop down combo or list 
//type gco.
class GW_EXT_CLASS CGWDateTime : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
protected:
	DECLARE_SERIAL(CGWDateTime)

public:
//GW_MEMBERS{{(CGWDateTime, "Construction")
	CGWDateTime();								//Default Constructor.
	CGWDateTime(TIMESTAMP_STRUCT* pDateTime)	//Constructs a CGWDateTime from a TIMESTAMP_STRUCT.
				{m_DateTime = *pDateTime;}
	virtual ~CGWDateTime()						//Default Destructor.
				{};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWDateTime, "Data Members")
	TIMESTAMP_STRUCT m_DateTime;				//Contains the date information for this object.
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWDateTime, "Operations")
	void InitializeTime()						//Initializes the m_DateTime structure to all zeroes.
		{memset(&m_DateTime, 0, sizeof(TIMESTAMP_STRUCT));}
	virtual void Serialize(CArchive& ar)		//Stores and retrieves the object from a CArchive object.
		{
		 	if (ar.IsStoring())
			{
			 	ar.Write(&m_DateTime, sizeof(TIMESTAMP_STRUCT));
			}
			else
			{
			 	ar.Read(&m_DateTime, sizeof(TIMESTAMP_STRUCT));
			}
		
		}
	void SetDateTime(CGWDateTime& tm)			//Sets this objectsa value from another CGWDateTime object.
			{m_DateTime = tm.m_DateTime;}
	BOOL ValidDate(BOOL bCTimeCompatible = TRUE);	//Detects whether this date time object contains valid data.
	void operator=(CGWDateTime& otherDateTime)		//Copies one CGWDateTime object to another.
			{m_DateTime =  otherDateTime.m_DateTime;}
	BOOL operator==(CGWDateTime& otherDateTime)		//Checks for equality between two CGWDateTime objects.
			{
				return (m_DateTime.year == otherDateTime.m_DateTime.year &&
					m_DateTime.month == otherDateTime.m_DateTime.month &&
					m_DateTime.day == otherDateTime.m_DateTime.day &&
					m_DateTime.hour == otherDateTime.m_DateTime.hour &&
					m_DateTime.minute == otherDateTime.m_DateTime.minute &&
					m_DateTime.second == otherDateTime.m_DateTime.second)
					  ? TRUE : FALSE;
			}
	BOOL operator!=(CGWDateTime& otherDateTime)		//Checks for inequality between two CGWDateTime objects.
			{
				return (m_DateTime.year == otherDateTime.m_DateTime.year &&
					m_DateTime.month == otherDateTime.m_DateTime.month &&
					m_DateTime.day == otherDateTime.m_DateTime.day &&
					m_DateTime.hour == otherDateTime.m_DateTime.hour &&
					m_DateTime.minute == otherDateTime.m_DateTime.minute &&
					m_DateTime.second == otherDateTime.m_DateTime.second)
					 ? FALSE : TRUE;
			}
	void operator=(TIMESTAMP_STRUCT& otherDateTime) //Assigns a value to this object from a TIMESTAMP_STRUCT.
			{
				m_DateTime.year = otherDateTime.year;
				m_DateTime.month = otherDateTime.month;
				m_DateTime.day = otherDateTime.day;
				m_DateTime.hour = otherDateTime.hour;
				m_DateTime.minute = otherDateTime.minute;
				m_DateTime.second = otherDateTime.second; 
			}
	void SetDateTime(CTime ctime)	//Sets the value of this object from a CTime object.
			{
					m_DateTime.year = (unsigned short) ctime.GetYear();
					m_DateTime.month = (unsigned short) ctime.GetMonth();
					m_DateTime.day = (unsigned short) ctime.GetDay();
					m_DateTime.hour = (unsigned short) ctime.GetHour();
					m_DateTime.minute = (unsigned short) ctime.GetMinute();
					m_DateTime.second = (unsigned short) ctime.GetSecond();
			}
	void SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond)		//Sets the value of this object from individual date values.
			{
				m_DateTime.year = (unsigned short) nYear;
				m_DateTime.month = (unsigned short) nMonth;
				m_DateTime.day = (unsigned short) nDay;
				m_DateTime.hour = (unsigned short) nHour;
				m_DateTime.minute = (unsigned short) nMinute;
				m_DateTime.second = (unsigned short) nSecond;
			}

	CTime GetCTime()	//Builds and returns a CTime object based of the date stored in this object.
			{
				CTime tm(m_DateTime.year,
				m_DateTime.month,
				m_DateTime.day,
				m_DateTime.hour,
				m_DateTime.minute,
				m_DateTime.second);
				return tm; 
			}
	int GetYear()		//Returns the year.
			{return  m_DateTime.year;}
	int GetMonth()		//Returns the month.
			{return  m_DateTime.month;}
	int GetDay()		//Returns the day.
			{return  m_DateTime.day;}
	int GetHour()		//Returns the hour.
			{return  m_DateTime.hour;}
	int GetMinute()		//Returns the minute.
			{return  m_DateTime.minute;}
	int GetSecond()		//Returns the second.
			{return  m_DateTime.second;}
	void SetYear(int nYear) 								//Sets the year value.
			{m_DateTime.year = (unsigned short) nYear;}
	void SetMonth(int nMonth) 								//Sets the month value.
			{m_DateTime.month = (unsigned short) nMonth;}
	void SetDay(int nDay) 									//Sets the day value.
			{m_DateTime.day = (unsigned short) nDay;}
	void SetHour(int nHour) 								//Sets the hour value.
			{m_DateTime.hour = (unsigned short) nHour;}
	void SetMinute(int nMinute) 							//Sets the minute value.
			{m_DateTime.minute = (unsigned short) nMinute;}
	void SetSecond(int nSecond) 							//Sets the second value.
			{m_DateTime.second = (unsigned short) nSecond;}
	BOOL ParseDateTime(CString csDateTime, CString csDateFormat);	//Builds a date value from a string.
	CString Format(CString csFormat);								//Format a string date from this object.
//}}GW_MEMBERS	

	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

};

class GW_EXT_CLASS CGWParamInfo : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	friend class CCellDataMap;
	DECLARE_SERIAL(CGWParamInfo)
// Construction
public:		
//GW_MEMBERS{{(CGWParamInfo, "Construction")
	CGWParamInfo()				//Default Constructor.
		{m_nParamType = 10;}
	virtual ~CGWParamInfo()		//Default Destructor.
		{};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWParamInfo, "Construction")
	virtual	CGWParamInfo* Duplicate()					//Duplicates this object and returns a new instance.
	{
		CGWParamInfo* pParamInfo = new CGWParamInfo;
		pParamInfo->m_csParamName = m_csParamName;
		pParamInfo->m_nParamType = m_nParamType;
		pParamInfo->m_csInitValue = m_csInitValue;
		return pParamInfo;
	}; 
	virtual void Copy(CGWParamInfo* pParam)				//Copies one CGWParamInfo to another.
			{
				m_csParamName = pParam->m_csParamName;
				m_nParamType = pParam->m_nParamType;
				m_csInitValue = pParam->m_csInitValue;
			}
	virtual CString GetStringValue()					//Returns the string value of this parameter.
			{
				CString csValue; 
				return csValue;
			}
	virtual void SetValue(CString csValue)				//Sets the string value of this parameter.
			{
				m_csInitValue = csValue;
			}
//}}GW_MEMBERS	

	
//Data members
//GW_MEMBERS{{(CGWParamInfo, "Data Members")
	CString m_csParamName;			//The parameter name.
	short   m_nParamType;			//The parameter type.
	CString m_csInitValue;			//The initial string value for this parameter.
//}}GW_MEMBERS	

};


class CCachePage
{
public:
//GW_MEMBERS{{(CCachePage, "Constructor")
	CCachePage(int nBegRow, int nRowCount)		//Constructs a cache page from the begin row and ending row for the page.
	{
		m_nBegRow = nBegRow;
		m_nRowCount = nRowCount;
		m_bDiscarded = FALSE;
	}
//}}GW_MEMBERS	

//GW_MEMBERS{{(CCachePage, "Operations")
	BOOL IsDiscarded()							//Returns the flag indicating whether this page has been discarded.
		{return m_bDiscarded;}
	void DiscardPage();							//Discards this page from the cache.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CCachePage, "Data Members")
	int m_nBegRow;								//Begining row index for this page.
	int m_nRowCount;							//Begining volumn index for this page.
	BOOL m_bDiscarded;							//Flag indicating whether this cachepage has been released.
//}}GW_MEMBERS	
};

class CGWDataContext
{	
//GW_MEMBERS{{(CGWDataContext, "Construction")
	CGWDataContext(LPCTSTR szFieldDelim, LPCTSTR szLineDelim)	//Constructs a CGWDataContext from the field and line delimeters.
	{
		_tcsncpy(m_szFieldDelim, szFieldDelim, 10);
		_tcsncpy(m_szLineDelim, szLineDelim, 10);
	}
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWDataContext, "Data Members")
	TCHAR m_szFieldDelim[10];	//The field delimeter to be used for import and export.
	TCHAR m_szLineDelim[10];	//The line delimeter to be used for import and export.
//}}GW_MEMBERS	
};

class CGWDatabaseRequest;
class CGWGridSettings;
class CGWCellSettings;
class CGWGCOMappings;
class CGWRowSettings;
class CGWColumnSettings;
class CGWImportExportObject;
class CGWSeek;
class CGWReplace;
/////////////////////////////////////////////////////////////////////////////
class GW_EXT_CLASS CGWDataSource : public CObject
{ 

//GW_CLASS{{(CGWDataSource)
/*

CGWDataSource is an abstract base class and cannot be instantiated. The CCellDataMap, class which derives from 
CGWDataSource, is the most frequently used storage class for GridWiz grids and can be "Attached" to the grid with 
a single function call. Attaching a data source to a grid means that the underlying grid virtual functions like 
OnGetCellText and OnSetCellText will automatically flow through to the attached data source and provide persistance 
for the cell data. Without an attached data source, the cell data is not persisted unless you override OnGetCellText 
and OnSetCellText in the CGWGrid derived class. NOTE: Grid classes generated by the GridWiz Wizard automatically 
attach to a CCellDataMap object through a call to AttachInternalDataSource() which is placed in the grid's 
OnInitialUpdate override. The following code sample illustrates a typical grid module created by the GridWiz Wizard.


	void CTestGrid::GridOnInitialUpdate()
	{
		//There are three choices when hooking the grid to data. You will use only one of these
		//mechanisms. 
		//(1) Use the internal data structure possibly coupled with a initialization file. If you
		//use this method, the grid will automatically store changes. You may need to load and 
		//unload the grid using functions like OnSetCellText() and OnGetCellText().

		AttachInternalDataSource(); // (Default)

		//(2) Attach to a CGWDataSource object which is stored eleswhere. This GWDataSource can
		//be based on an ODBC recordset, a DAO recordset or a simple CCellDatamap. You can still
		//use a initialization file. Using this method, you can also serialize the data source 
		//to a file if you want.
		//AttachDataSource(&GetDocument()->m_MyDataSource); //You create the datasource and attach 
		//it to the grid using this function. 
 
		//(3) Don't attach to any data source at all. This will place the grid in "virtual" mode.
		//You will need to Override functions like OnGetCellText() and OnSetCellText() and 
		//store and retrieve the data yourself. 

		//Calling the base class implementation. This is necessary to realize all
		//default property settings like fonts, colors, scrollbars, etc.

		CGWTabGridCtrl::GridOnInitialUpdate(); 

		////////////////////////////////////////////////////////////////////////////////
		//For performance reasons, place your initial sheet/row/col/range/cell property
		//settings here. By placing your property setting function calls here, you can 
		//avoid refreshing the grid needlessly!
		//Start property settings
		//Place property setting function calls here, if any.


		//End property settings
		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////
		//Finally, activate the sheet. This will cause the initial grid to be rendered
		//and any predefined SQL or database requests to be processed. This should be 
		//the last thing done in this function.

		ActivateSheet(0);

	}

Please note that the comments here indicate that the very first task in this function is to attach to a GridWiz Data source. 
This implementation attaches to the internal data source, but you could attach to a data source which might be stored on your 
document object. Storing the Data source on the document object is a easy way to persist your Gridwiz data with the rest of 
your document data. Also note that the last task in this function is to call ActivateSheet(). Do not remove the call to ActivateSheet. 

Once the data source is attached to the grid, it is accessible via the m_pGWDataSource pointer member. Loading or unloading the data 
source can be accomplished by accessing the m_pGWDataSource object directly by calling functions such as CGWDataSource::SetCellText(), etc.
Data sources can also be loaded from persisted data source objects using the LoadData() functions. SaveData() can be used to stored a
data source to a file. You can also simply serialize a CGWDataSource object into an existing MFC CArchive object. This is the approach
taken to serialize documents in the MFC class CDocument. Import and Export are also available and will handle most kins of delimitted 
data. See the "CGWImportExportObject" class and the article "Importing and Exorting Data" for additional details. There is also
a sample application called: ImportExport.


*/
//}}GW_CLASS	

	
	DECLARE_SERIAL(CGWDataSource)
public:
//GW_MEMBERS{{(CGWDataSource, "Construction")
	CGWDataSource()								//Default Constructor.
			{
				m_bInitialized = FALSE;
				m_bDesignMode = FALSE;
			}
	virtual ~CGWDataSource()					//Defualt Destructor.
			{};
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWDataSource, "Data Members")
	CDocument* m_pArchiveDocument;				//The CDocument* used during the archive process.
	CGWGridSettings m_GridGlobalSettings;		//The grid global settings for this data source.
	CStringArray    m_csaAddRow;        		//A CString Array representing the AddRow. This buffer is used when doing row based appending.
	int 			m_nDataEntryMode;			//Controls default data entry behavior
	int 			m_nDataEntryModeState;		//Differnt states within a data entry mode.
	int				m_nAddIndex;            	//The row index for the database row being added.
	CWnd*           m_pGridCWnd;                //A pointer back to the Window to which this data source is attached.
	CGWGrid*		m_pGrid;					//A pointer back to the Grid to which this data source is attached.
	BOOL			m_bFreeDatabaseResources;   //Determines whether to release DB resource like AfxDAOTerm.
	BOOL 			m_bDataSourceError;         //Indicates an error condition within the data source.
	CPoint          m_ptErrorCell;              //The Cell which contains the error;
	int             m_nErrorCode;               //The Error code associated with the error condition
	CString         m_csErrorString;            //The Error description.
	BOOL			m_bDisplayed;				//Did the entity which created the error or exception already display a dialog box.
	BOOL            m_bShowTabs;                //ShowTabs for a multi-sheet workbook
	BOOL            m_bDesignMode;              //Are designing or running.
	int				m_nMaxAutoColWidth;			//Default maximum column width applied when a external database result set is openned.
	DWORD			m_dwQueryTimeOutSeconds;    //Time out value for querys
	BOOL			m_bUseLocalCursor;			//Use ODBC Cursor Lib
	BOOL			m_bInitialized;				//Flag indicating whether this data source has been loaded from a file or other source.
//}}GW_MEMBERS	

	

//GW_MEMBERS{{(CGWDataSource, "Property Access Functions")
	BOOL GetDesignMode()						//Retrieves the m_bDesignMode flag.
			{
				return m_bDesignMode;
			}
	void SetDesignMode(BOOL bDesignMode)		//Sets the m_bDesignMode flag.
			{
				m_bDesignMode = bDesignMode;
			}
	BOOL IsInitialized()						//Retrieves the m_bInitialized flag.
			{
				return m_bInitialized;
			}
	BOOL GetShowTabs()							//Retrieves the m_bShowTabs member.
			{
				return m_bShowTabs;
			}
	void SetShowTabs(BOOL bShowTabs)			//Sets the m_bShowTabs member.
			{
				m_bShowTabs = bShowTabs;
			}
	virtual void SetRowCacheIncrement(int nIncrement, int nSheetNdx)	//Sets the RowCacheIncrement value. This is the number or rows in a cache page.
			{};
	virtual int GetRowCacheIncrement(int nSheetNdx)		//Gets the RowCacheIncrement value. This is the number or rows in a cache page.			
			{
				return 0;
			}
	virtual void SetGridGlobalSettings(CGWGridSettings* pGridGlobalSettings)	//Assigns grid global settings to this data source.
			{};
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWDataSource, "Operations")
	void ClearError()							//Reset any error condition with the data source.
			{
				m_bDataSourceError = FALSE;
				m_ptErrorCell = CPoint(-1,-1);
				m_nErrorCode = 0;
				m_csErrorString.Empty();
				m_bDisplayed = FALSE;
			}
	void RaiseError(CPoint ptErrorCell, int nErrorCode, CString csErrorString, BOOL bDisplayed = FALSE)		//Set the error condition with the data source.
			{	
				m_bDataSourceError = TRUE;
				m_ptErrorCell = ptErrorCell;
				m_nErrorCode = nErrorCode;
				m_csErrorString = csErrorString;
				m_bDisplayed = bDisplayed;
			}
	virtual void LoadSettings(CString csSettingsFile)		//Load this data source with grid settings from a file or custom resource.
			{};
	virtual void RecalcSheets()								//RecalcSheets causes external data sources to be re-evaluated.
			{};
	virtual void Serialize(CArchive& ar)					//Store or load this data source to or from a CArchive object.
			{}; 
	virtual BOOL GetDataSourceError(CPoint& ptErrorCell, int& nErrorCode, CString& csErrorString, BOOL& bDisplayed)  //Retrieve the error status from this data source.
			{return FALSE;}
	virtual void ImportData(CGWImportExportObject* pGWImportExportObject, int nSheet)	//Import data into this sheet according to the criteria in CGWImportExportObject object.
			{};
	virtual void SetDataEntryMode(int m_nDataEntryMode = 0, int m_nDataEntryModeState = 0) //Change the entry mode. Either Add or Edit.
		{};
	virtual void GetDataEntryMode(int& m_nDataEntryMode, int& m_nDataEntryModeState)		//Get the data entry mode.
		{};
	virtual void SetAddRowIndex(int nAddIndex)				//Set the current row index which is assigned to the appending row.
		{};
	virtual BOOL ScrollToBottom(int nSheet)					//Cause the data source to scroll to the end of an external database connection.
		{return FALSE;}
//}}GW_MEMBERS	
	

	
//Overrideables
//GW_MEMBERS{{(CGWDataSource,"Data Access")
	virtual void GetCell(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0)			//Retrieve the CCellDataObject based on row and column coordinates.
		{};		
	virtual void SetCell(UINT nRowNdx, UINT nColNdx, CObject* pObject, int nSheet = 0)			//Assign a CCellDataObject to a row and column.
		{};		
	virtual void SetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0)	//Associate a CObject* with this cell.
		{};		
	virtual void GetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0)	//Retrieve the CObject* associated with this cell.
		{};		
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0)	//Set the text value of a cell.
		{};		
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0)	//Retrieve the text value for a cell.
		{};		
	virtual void SetCellTag(UINT nRowNdx, UINT nColNdx, CString& csTag, int nSheet = 0)	//Set the tag value of a cell.
		{};		
	virtual void GetCellTag(UINT nRowNdx, UINT nColNdx, CString& csTag, int nSheet = 0)	//Retrieve the tag value for a cell.
		{};		
	virtual void SetCellVariant(UINT nRowNdx, UINT nColNdx, _variant_t& pObject, int nSheet = 0) //Overidden to retrieve the associated Variant with the contents of a cell.
		{};
	virtual void GetCellVariant(UINT nRowNdx, UINT nColNdx, _variant_t& pObject, int nSheet = 0)	//Overidden to associate a Variant with the contents of a cell.
		{};
	virtual void GetDefaultCellText(UINT nRowNdx, UINT nColNdx, CString& csDefaultCellText, int nSheet = 0) //Return the default text value during an Append Row operation.
		{};		
	virtual void SetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0)		//Set the long integer value of a cell.
		{};		
	virtual void GetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0)		//Retrieve the long integer value for a cell.
		{};		
	virtual void SetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0)	//Set the floating point double value for a cell.
		{};		
	virtual void GetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0)	//Retrieve the floating point double value for a cell. 
		{};		
	virtual void SetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0)	//Set the date value for a cell.
		{};		
	virtual void GetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0)	//Retriece the date value for a cell.
		{};		
	virtual CObject* GetSheetExtraData(int nSheet)					//Get the sheet extra data object. Usually a MFC recordset object.
		{return NULL;}   
	virtual void SetSheetExtraData(CObject* pObject, int nSheet)	//Set the sheet extra data object. Usually a MFC recordset object.
		{}; 
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWDataSource, "Data Manipulation")
	virtual void DeleteRow(UINT nRowNdx, UINT nCount, int nSheet = 0)							//Delete one or more rows of data and display settings.
		{};
	virtual void InsertRow(UINT nRowNdx, UINT nCount, int nSheet = 0)							//Insert one or more rows of data and shift display settings.
		{};
	virtual void AddRow(UINT nCount, int nSheet = 0)												//Append one or more rows of data and shift display settings.										
		{};
	virtual void DeleteColumn(UINT nColNdx, UINT nCount, int nSheet = 0)							//Delete one or more columns of data and display settings.
		{};
	virtual void InsertColumn(UINT nColNdx, UINT nCount, int nSheet = 0)							//Insert one or more columns of data and shift display settings.
		{};
	virtual void AddColumn(UINT nCount, int nSheet = 0)											//Append one or more columns of data and shift display settings.
		{};
	virtual void MoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = 0)	//Move one or more rows of data and shift display settings.
		{};
	virtual void MoveColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int nSheet = 0) //Move one or more columns of data and shift display settings.
		{};
	virtual void CopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = 0)	//Copy one or more rows of data and shift display settings.	
		{};
	virtual void CopyColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int nSheet = 0) //Copy one or more columns of data and shift display settings.
		{};
	virtual void BindAllColumns(int nFieldCount, int nFixedColumns)								//Associate each column with a field index in an external data source or to simply allow for column redirecting.
		{};
	virtual void BindColumn(UINT nColNdx, UINT nFieldNdx, CObject* pObject, int nSheet = 0) 		//Associate a particular column with a field index in an external data source or to simply allow for column redirecting.
		{};
	virtual int  GetBoundField(int nColNdx, CObject* pObject, int nSheet = 0)	//Retrieve the field index which has been bound to a particular column.
		{return nColNdx;};
	virtual void Sort(int nMajorCol, BOOL bAscending = TRUE, BOOL bNumeric = FALSE, int nMinorCol1 = -1, BOOL bAscending1 = TRUE, BOOL bNumeric1 = FALSE, int nMinorCol2 = -1, BOOL bAscending2 = TRUE, BOOL bNumeric2 = FALSE, int nMinorCol3 = -1, BOOL bAscending3 = TRUE, BOOL bNumeric3 = FALSE, BOOL bCallBackForData = FALSE, BOOL bIncludeBlankLines = TRUE, int nSheet = 0)   //Sort the data source according to specific criteria.
		{};
	virtual BOOL Seek(CGWSeek* pSeek, BOOL bNext, int nSheet = 0)  //Search the values of this data source according to criteria contained in the CGWSeek object.
		{return FALSE;};
	virtual long Replace(CGWReplace* pReplace, BOOL bNext, int nSheet = 0)  //Replace values in this data source according to the criteria contained in the CGWReplace object.
		{return 0;};
	virtual int GetRowOrderIndex(int nRowNdx, int nSheet = 0)  //Retrieve the sort order index of a particular row index.
		{return -1;};
	virtual void ResetDataSource()       //Removes all sheets and add one back
		{};
	virtual void ClearSheetData(int nSheet)  //Removes just sheet data
		{};
	virtual void ClearSheetAll(int nSheet)  //Removes sheet data and settings
		{};
	virtual void ResetSheet(int nSheet)  //Resets sheet field bindings 
		{};
	virtual void ResetSheetDBSettings(int nSheet) //Resets sheet database bindings
		{};
//}}GW_MEMBERS	


//ValidStringObjects are used to populate listboxes in drop down cells,
//check boxes and radio button.
//GW_MEMBERS{{(CGWDataSource, "Valid String Objects")
	virtual BOOL RegisterValidStringObject(CGWValidStrings* pGWValidStrings)						//Register a valid string object with this data source. This allows for object clean up when the data source is destroyed.
			{return FALSE;}
	virtual BOOL LookupValidStringObject(CString m_csName, CGWValidStrings*& pValidStringObject)	//Retrieve a valid string object based on its name.
			{return FALSE;}
	virtual POSITION GetFirstValidStringObject()													//Get the first valid string object in the collection.
			{return NULL;}
	virtual void GetNextValidStringObject(POSITION& pos, CString& csName, CGWValidStrings*& pValidStringObject)		//Get the next valid string object in the collection.
			{};
	virtual void RefreshValidStringObjects()														//Reload the valid string objects which are based on external data sources.
			{};
	virtual void RemoveValidStringObject(CGWValidStrings* pGWValidStrings)							//Remove the valid string object from the collection.
			{};
//}}GW_MEMBERS	

//Context Menu Objects are used to provide unique context menus for
//various parts of the grid.
//GW_MEMBERS{{(CGWDataSource, "Valid String Objects")
	virtual BOOL RegisterContextMenu(CGWContextMenu* pGWContextMenu)								//Register the context menu with this data source.
			{return FALSE;}
	virtual BOOL LookupContextMenu(CString m_csName, CGWContextMenu*& pContextMenu)					//Look up a context menu by its name.
			{return FALSE;}
	virtual POSITION GetFirstContextMenu()															//Get the first Context Menu in the collection.
			{return NULL;}
	virtual void GetNextContextMenu(POSITION& pos, CString& csName, CGWContextMenu*& pContextMenu)	//Get the next Context Menu from the collection.
			{};
	virtual void RemoveContextMenu(CGWContextMenu* pContextMenu)									//Remove the Context Menu from the collection.
			{};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWDataSource, "Database Request")
	virtual CGWDatabaseRequest* GetDatabaseRequest(int nSheet)							//Get the database request object for a particular sheet.
			{return NULL;}
	virtual void SetDatabaseRequest(CGWDatabaseRequest* pDatabaseRequest, int nSheet)	//Assign the database request object to a particular sheet. 
			{};
	virtual void EditDatabaseRequest(CGWDatabaseRequest* pDatabaseRequest)				//Display a dialog box to edit a database request object.
			{};
	virtual void ExecuteQBE(CGWDatabaseRequest* pGWDatabaseRequest)						//Create a query builder dialog to edit a database request object.
			{};
	virtual void RequestTables(CGWDatabaseRequest* pGWDatabaseRequest)					//Populates a CStringArray with the names of tables available from the connection described by the database request object.
			{};
	virtual void RequestColumns(CGWDatabaseRequest* pGWDatabaseRequest)					//Populates a CStringArray with the names of columns available from the connection described by the database request object.
			{};
	virtual CString GetDefaultConnectType()												//Retrieve the default connection string associated with this data source.
			{CString csConnect; return csConnect;}
	virtual void SetRecordSourceType(int nRecordSourceType, int nSheet = 0)	//Set the RecordSource Type member of the data source object associated with a sheet in this data source.
			{};
	virtual void SetDatabaseConnect(CString csConnect, int nSheet = 0)		//Set the Database connection string member of the data source object associated with a sheet in this data source.		
			{};
	virtual void SetDatabasePath(CString csDatabasePath, int nSheet = 0)	//Set the Database file path member of the data source object associated with a sheet in this data source.
			{};
	virtual void SetDatabaseName(CString csDatabaseName, int nSheet = 0)	//Set the Database file member of the data source object associated with a sheet in this data source.
			{};
	virtual void SetRecordSource(CString csRecordSource, int nSheet = 0)	//Set the RecordSource member of the data source object associated with a sheet in this data source.
			{};
	virtual void SetRecordsetType(int nRecordsetType, int nSheet = 0)		//Set the RecordSet Type member of the data source object associated with a sheet in this data source.
			{};
	virtual void SetDatabaseReadOnly(BOOL bReadOnly, int nSheet = 0)		//Set the Read Only member of the data source object associated with a sheet in this data source.
			{};
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWDataSource, "Sheet Manipulation")
	virtual int GetNumSheets()								//Retrieve the number of sheets contained in this data source.
		{return 0;}
	virtual void ActivateSheet(int nSheet)					//Activate the sheet causing any external data source connection to be evaluated.
		{};
	virtual CString GetSheetName(int nSheet)				//Retrieve the sheet name for a particular sheet within this data source.
		{return "";}
	virtual void SetSheetName(int nSheet, CString csSheetName)	//Set the sheet name for a particular sheet within this data source.
		{};	
	virtual int FindSheet(CString csSheetName)				//Retrieve the sheet index based on the sheet name.
		{return 0;}
	virtual int GetMaxRow(int nSheet)						//Get the maximum data row index within a sheet of this data source.
		{return 0;}
	virtual int GetMaxCol(int nSheet)						//Get the maximum data column index within a sheet of this data source.
		{return 0;}
	virtual void SetNumRows(int nNumRows, int nSheet = 0)	//Set the number of rows for for a sheet within this data source.
		{};
	virtual void SetNumColumns(int nNumRows, int nSheet = 0) //Set the number of rows for for a sheet within this data source.
		{};
	virtual void InsertNewSheet(int nInsertBefore, CString csSheetName, CObject* pSheetExtraData = NULL)	//Insert a new sheet into this data source.
		{};
	virtual void RemoveSheet(int nSheetIndex)									//Remove a sheet from this data source based on its index.
		{};	
	virtual void RemoveSheet(CString csSheetName)								//Remove a sheet from this data source based on its name.
		{};
	virtual void MoveSheet(int nSheetIndex, int nCount)							//Move a sheet to a new location within this data source.
		{};
	virtual int AddSheet(CString csSheetName, CObject* pSheetExtraData = NULL)	//Append a new sheet to this data source.
		{return 0;}
	virtual void CopySheet(int nSourceSheetNdx, int nDestSheetNdx)				//Copy a sheet and add it into the data source.
		{};
	virtual void RefreshSheet(int nSheet = 0)									//Refresh the sheet by removing any binding or column width settings made by an external database connection.
		{};
	virtual void RefreshSheet(CString csSheet)									//Refresh the sheet by removing any binding or column width settings made by an external database connection.
		{};
    virtual void DestroySheets()												//Destroy all the sheets within this data source.
		{};
	virtual long GetBookmarkRow(_variant_t& varBookmark, long nStart, long nEnd, int nSheet = 0)	//Retrieve the row index for a particular bookmark in a bound sheet.
		{return -1;}
	virtual long AppendBookmarkRow(_variant_t& varBookmark, int nSheet = 0)	//Append a new row to the end of the sheet. New rows comes from asynchronous inserts.
		{return -1;}
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWDataSource, "Grid Propery Settings")
	virtual CGWGridSettings* GetGridSettings(int nSheet = 0)												//Get the grid settings which define a particular sheet.
		{return NULL;}
	virtual CGWCellSettings* GetCellSettings(UINT nRowNdx, UINT nColNdx, int nSheet = 0)					//Get the cell settings which define a particular cell.
		{return NULL;}
	virtual CGWGCOMappings* GetGCOMappings(int nSheet = 0)													//Get GCO mappings for a particular sheet.
		{return NULL;}
	virtual CGWRowSettings* GetRowSettings(int nRowNdx, int nSheet = 0)										//Get cell settings for a row within a particular sheet.
		{return NULL;};
	virtual CGWColumnSettings* GetColumnSettings(int nColNdx, int nSheet = 0)								//Get cell settings for a column within a particular sheet.
		{return NULL;};
	virtual void SetGridSettings(CGWGridSettings*& pSetting, int nSheet = 0)								//Set the grid settings which define a particular sheet.
		{};
	virtual void SetCellSettings(UINT nRowNdx, UINT nColNdx, CGWCellSettings*& pSetting, int nSheet = 0)	//Set the cell settings which define a particular cell.
		{};
	virtual void SetGCOMappings(CGWGCOMappings*& pSetting, int nSheet = 0)									//Set GCO mappings for a particular sheet.
		{};
	virtual void SetRowSettings(int nRowNdx, CGWRowSettings*& pSetting, int nSheet = 0)						//Set cell settings for a row within a particular sheet.
		{};
	virtual void SetColumnSettings(int nColNdx, CGWColumnSettings*& pSetting, int nSheet = 0)				//Set cell settings for a column within a particular sheet.
		{};
//}}GW_MEMBERS	


//Caching
//GW_MEMBERS{{(CGWDataSource, "Caching")
	virtual void SetCachePageSize(int nNumRows, int nSheet)	//Sets the number of rows in each cache page
		{};
	virtual void SetCachePages(int nNumPages, int nSheet) 	//Sets the number of cache pages to keep
		{};
	virtual void SetCachingOn(int nSheet) 					//Turns caching on.
		{};
	virtual void FreeAllCachePages(int nSheet) 				//Frees all the pages in the cached
		{};
	virtual int LoadData(CGWDataContext gwdc, int nSheet, CFile* pFile)	//Loads data from a file into the data source.
		{return 0;}				
	virtual int LoadData(CGWDataContext gwdc, int nSheet, LPCSTR lpszBuffer) //Loads data from a buffer into the data source.
		{return 0;}		
	virtual int FastLoad(CGWDataContext gwdc, int nSheet, CFile* pFile)	//Loads data from a file into a special area which will be used by the caching code.
		{return 0;}
	virtual int FastLoad(CGWDataContext gwdc, int nSheet, LPCSTR lpszBuffer) //Loads data from a buffer into a special area which will be used by the caching code.
		{return 0;}
	virtual int SaveData(CGWDataContext gwdc, int nSheet, CFile* pFile) //Saves the data source data to a file.
		{return 0;}				
	virtual int SaveData(CGWDataContext gwdc, int nSheet, LPCSTR lpszBuffer) //Saves the data source data to a buffer.
		{return 0;}		
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


class GW_EXT_CLASS CGWFileIdentifier : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	friend class CCellDataMap;
	DECLARE_SERIAL(CGWFileIdentifier)

		
public:
//GW_MEMBERS{{(CGWFileIdentifier, "Construction")
	CGWFileIdentifier()									//Default Constructor.
		{m_nTryFirst = 0;}
	CGWFileIdentifier(CGWFileIdentifier& otherFileId);	//Copy Constructor. 
	CGWFileIdentifier(CString& csFileName, CString& csAbsPath, CString& csRelPath, CString& csURL, CString& csExtension, int nTryFirst)		//Construct a file identifier by its individual parts.
			{
				m_csFileName = csFileName;
				m_csAbsolutePath = csAbsPath;
				m_csRelativePath = csRelPath;
				m_csURL = csURL;
				m_nTryFirst = 0;
				m_csExtension = csExtension;
			}
	virtual ~CGWFileIdentifier()						//Default Destructor.
			{};
//}}GW_MEMBERS	


//Operations
public:
//GW_MEMBERS{{(CGWFileIdentifier, "Operations")
	virtual void Serialize(CArchive& ar);						//Store and load this object to and from a CArchive object.
	void operator=(CGWFileIdentifier& otherFileIdentifier);		//Copies one CGWFileIdentifier object to another.
	BOOL VerifyExists(CString csPath, int nType);				//Verifies that the file pointed to by this object exists.
	CString GetFilePath();										//Retrieves the file path in string form.
//}}GW_MEMBERS	

//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

//GW_MEMBERS{{(CGWFileIdentifier, "Operations")
	CString m_csFileName;			//The file name.
	CString m_csAbsolutePath;		//The absolute path.
	CString m_csRelativePath;		//The relative path.
	CString m_csURL;				//The URL path.
	CString m_csExtension;			//The file extension.
	int m_nTryFirst;				//Flag indicating which path to try first when openning or verifying the file.
//}}GW_MEMBERS	
};


class CGWRowset;
struct IDataSource;
class CGWRowsetNotify;
class CGWRowPositionChange;
class GW_EXT_CLASS CGWDatabaseRequest : public CObject
{

//GW_CLASS{{(CGWDatabaseRequest)
/*

The CGWDatabaseRequest class unifies most of the differences in binding to OLEDB, ADO, ODBC and DAO data sources. It is 
intended to be a database independent way to provide a connection or describe a connection to a backend data source. 
There can be one CGWDatabaseRequest object associated with each sheet in the grid. The resultset for the connection 
is built when the sheet is activated. Changes in the database request object are reflected in the sheet after the 
RefreshSheet() method of the data source is called. 

Connections to OLEDB are handled by assignment of a pointer to a CGWRowset object. This object should have already 
been instantiated and openned. Similarly, ADO connections a handled by an assignment of a pointer to a _RecordsetPtr
object, which is the COM compiler support built ADO Recordset pointer. See the MFC documentation for specifics 
on COM compiler support. GridWiz ships with a set of header files for ADO support which were built using the 
#import facility. See the TESTADO and OLEDBTEST sample applications for details.

The other database binding options, DAO and ODBC, can be built by specifying elements of the database request object
including connection string, SQL, tabledef or querydef. See the DAODEMO and ODBCDEMO sample applications for details.

Additional information on binding to databases can be found in the article: "Binding to External Databases".

*/
//}}GW_CLASS	
	
	
	
	friend class CCellDataMap;
	DECLARE_SERIAL(CGWDatabaseRequest)

		
//GW_ENUMERATIONS{{(CGWDatabaseRequest, "Recordset type specifiers.")
	enum nRecordsetType
	{
		TABLE = 1,
		DYNASET = 2,
		SNAPSHOT = 3,
	} nRecordsetTypes;	
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWDatabaseRequest, "Record Source type specifiers.")
	enum nRecordSourceType
	{
		UNDEFINED = 0,
		TABLEDEF = 1,
		QUERYDEF = 2,
		SQL = 3,
	} nRecordSourceTypes;	
//}}GW_ENUMERATIONS

// Construction
public:
//GW_MEMBERS{{(CGWDatabaseRequest, "Construction")
	CGWDatabaseRequest();						//Default Constructor.
	virtual ~CGWDatabaseRequest();				//Default Destructor.
//}}GW_MEMBERS	
	

//GW_MEMBERS{{(CGWDatabaseRequest, "Operations")
	void ResetDatabaseRequest()
		{
			CGWDatabaseRequest dbrq;
			*this = dbrq;
		}
	virtual void Serialize(CArchive& ar);
	void operator=(CGWDatabaseRequest& otherDatabaseRequest);
	void BindOleDB(CGWGrid* pGrid, IDataSource* pDataSource, LPCTSTR lpszDataMember);		//Called to initialize and bind to a Rowset.   
	void ReBindOleDB(CGWGrid* pGrid, IDataSource* pDataSource, LPCTSTR lpszDataMember);		//Called to initialize and bind to a different Rowset.   
	void BindOleDB(CGWGrid* pGrid, IRowset* pRowset);		//Called to initialize and bind to a Rowset.   
	void ReBindOleDB(CGWGrid* pGrid, IRowset* pRowset);		//Called to initialize and bind to a different Rowset.   
	BOOL IsBound()												//Checks to see if this object is bound to a Rowset.
	{
		if (m_pGWRowset) 
			return TRUE;
		return FALSE;
	}
	CGWRowset* GetOledbBinding()								//This function returns a pointer to the CGWRowset object if this database request is bound to an OLE DB data source.
	{
		return m_pGWRowset;
	}
//}}GW_MEMBERS	


#ifdef _GW_ADO15
	_RecordsetPtr m_pAdoRecordset;		//Makes the normal unbound grid able to access and ADO Recordset. Not valid for CGWDAODataSource,or CGWODBCDataSource. Also, this member is not persistent.
	CGWRowsetNotify * m_pGWRowsetNotify;
	CGWRowPositionChange * m_pGWRowPositionChange;
#else
	void* m_pAdoRecordset;
	void* m_pGWRowsetNotify;
	void* m_pGWRowPositionChange;
#endif

// Attributes
public:	 
//GW_MEMBERS{{(CGWDatabaseRequest, "Data Members")
	IDataLink* m_pDataLink;			//Makes the normal unbound grid able to read external data. Not valid for CGWDAODataSource,or CGWODBCDataSource. Also, this member is not persistent.
	CGWRowset* m_pGWRowset;			//Address of the rowset used to make a connection to OLEDB databinding.
	CString m_csConnect;			//Either Access or ODBC connect string
	CGWFileIdentifier m_GWFileId;	//Name and location of database file (Database file name)
	CString m_csRecordSource;		//Name of Tabledef/Querydef (access) or TableName (ODBC)
	int     m_nRecordsetType;		//Table, Dynaset, Snapshot
	BOOL    m_bReadOnly;			//Open record source as updateable.
	BOOL    m_bAppendable;			//Open record source as appendable.		
	int     m_nRecordSourceType;	//TableDef, QueryDef, SQL Language Request
	BOOL    m_bDBRequestIsDirty;	//Flag indicating that the database request should be requeried.
	CString m_csSQL;				//SQL to be executed against access or odbc
	CObArray m_ParamInfo;			//Param info used for parameterized Dao QueryDefs.
	CString m_csFilter;				//Filter applied to recordset when its openned.
	CString m_csSort;				//Sort fields used to sort result set.
	CStringArray m_csaSelectedTables;	//Table names available from this record source.
	CStringArray m_csaSelectedFields;	//Field names available from this record source.
	CStringArray m_csaFieldCriteria;	//Criteria used to build the where clause.
	CStringArray m_csaGroupBy;			//Fields used to build the Group By clause.
	CStringArray m_csaOrderBy;			//Fields used to build the Order By clause.
	CStringArray m_csaTables;			//Temporary holding area for table names.
	CUIntArray   m_uaTableType;			//Temporary holding area for table and view types.
	CStringArray m_csaColumns;			//Temporary holding area for column names.
	CUIntArray   m_uaColumnTypes;		//Temporary holding area for column types.
//}}GW_MEMBERS	


//Attributes
//This version table helps track changes in this object. When changes are made to the 
//schema of this object, insert version Identifier just before Current_Version_Number so that
//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;



//GW_MEMBERS{{(CGWDatabaseRequest, "Data Access Members")
	inline void SetDatabaseConnect(CString csConnect)	//Sets the connection string.
		{m_csConnect	= csConnect;DBRequestDirty();}
	inline void SetFilter(CString csFilter)				//Sets the filter member.
		{m_csFilter	= csFilter;DBRequestDirty();}
	inline void SetSort(CString csSort)					//Sets the sort string member.
		{m_csSort	= csSort;DBRequestDirty();}
	inline void SetDatabaseFileId(CGWFileIdentifier& GWFileId)	//Sets the dirty flag.
		{m_GWFileId	= GWFileId;DBRequestDirty();}
	inline void SetRecordSource(CString csRecordSource)			//Sets the record source field.
		{m_csRecordSource	= csRecordSource;DBRequestDirty();}
	inline CString GetRecordSource()			//Sets the record source field.
		{return m_csRecordSource;}
	inline void SetSQL(CString csSQL)					//Sets the SQL statement.
		{m_csSQL	= csSQL;DBRequestDirty();}
	inline void SetRecordsetType(int nRecordsetType)	//Sets the recordset type member.
		{m_nRecordsetType	= nRecordsetType;DBRequestDirty();}	
	inline void SetDatabaseReadOnly(BOOL bReadOnly)		//Sets the read only member.
		{m_bReadOnly	= bReadOnly;DBRequestDirty();}
	inline void SetRecordSourceType(int nRecordSourceType)	//Sets the RecordSourceType member.
		{m_nRecordSourceType	= nRecordSourceType;DBRequestDirty();}
	void SetAdoRecordset(_RecordsetPtr pAdoRecordset);	//Sets the Ado Recordset member. Ado Recordset should be open.
	BOOL DBRequestIsDirty()									//Checks the dirty flag.
		{return m_bDBRequestIsDirty;}
	void DBRequestCleaned()									//Turns off the dirty flag.
		{m_bDBRequestIsDirty = FALSE;}
	void DBRequestDirty()									//Turns on the dirty flag.
		{m_bDBRequestIsDirty = TRUE;}
//}}GW_MEMBERS	


//DAO QueryDef Parameters
//GW_MEMBERS{{(CGWDatabaseRequest, "Parameters")
	void ClearParams();													//Clears and deletes all parameters.
	short GetParameterCount()											//Retrieves the number of parameters.
		{return (short) m_ParamInfo.GetSize();}
	void SetParamValue(int nIndex, CGWParamInfo* pGWParamInfo);			//Sets a parameter value based on its index.
	void SetParamValue(LPCTSTR lpszName, CGWParamInfo* pGWParamInfo);	//Sets a parameter value based on its name.
	void SetParam(int nIndex, CGWParamInfo* pParam);					//Assign a CGWParamInfo object by its index.
	void SetParam(LPCTSTR lpszName, CGWParamInfo* pParam);				//Assign a CGWParamInfo object by its name.
	CGWParamInfo* GetParamValue(int nIndex);							//Gets a parameter value by its index.
	CGWParamInfo* GetParamValue(LPCTSTR lpszName);						//Gets a parameter value by its name.
	void GetParameterInfo(int nIndex, CGWParamInfo& pGWParamInfo);		//Gets a parameter info object by its index.
	void SetParameterInfo(int nIndex, CGWParamInfo& pGWParamInfo);		//Sets a parameter info object by its index.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWDatabaseRequest, "Operations")
	virtual void RequestTables(CGWDataSource* pGWDataSource)			//Retrieve the names of the tables available with this data source.
		{
			if (pGWDataSource)
				pGWDataSource->RequestTables(this);
		}
	virtual void RequestColumns(CGWDataSource* pGWDataSource)			//Retrieve the names of the columns available with this data source.
		{
			if (pGWDataSource)
				pGWDataSource->RequestColumns(this);
		};
//}}GW_MEMBERS	
};


class GW_EXT_CLASS CGWValidStrings : public CObject
{ 
//GW_CLASS{{(CGWValidStrings)
/*

The CGWValidStrings class  maintains a list of strings which can be displayed in the drop list portion of a cell or 
in a multi-radio button or checkbox cell. called CGWValidStrings. To use the CGWValidStrings class, you first create 
an instance of this class on the heap. Add string data to it and then assign it to a range of cells in the grid. 
The following code illustrates how to build a CGWValidStrings object and assign it to a column of cells. See the 
GWDemo1 sample for the complete code.

	CGWValidStrings* pValidStrings = new CGWValidStrings;
	pValidStrings->SetValidString("Valid String 1");
	pValidStrings->SetValidString("Valid String 2");
	pValidStrings->SetValidString("Valid String 3");
	pValidStrings->SetValidString("Valid String 4");
	pValidStrings->SetValidString("Valid String 5");
	pValidStrings->SetValidString("Valid String 6");
	pValidStrings->SetValidString("Valid String 7");
	pValidStrings->SetValidString("Valid String 8");
	m_pGWDataSource->RegisterValidStringObject(pValidStrings);
	SetColValidStrings(1,1,pValidStrings);
 

Alternatively, you can identify a database connection to fill the CGWValidStrings object from the resultset of a query. 
The following code sample illustrates this. See the the CGWDatabaseRequest object for additional details on building 
this connection. See the VSOTest sample for the complete code.

	//Setup a Valid String object
	CGWValidStrings* pVSO = new CGWValidStrings(&m_MyDataSource); 
	pVSO->SetName("Employees");
	//Link VSO to a dbrq
	CGWDatabaseRequest dbrq; 
	dbrq.m_GWFileId.m_csFileName = csInstallDir + "Samples\\GWSample.mdb";
	dbrq.SetDatabaseConnect("Access");
	dbrq.SetRecordsetType(CGWDatabaseRequest::SNAPSHOT); 
	dbrq.SetRecordSourceType(CGWDatabaseRequest::SQL); 
	dbrq.SetSQL("Select Employees.[Last Name], Employees.[Employee ID] from Employees");
	pVSO->SetDatabaseRequest(&dbrq); 
	//Assign VSO to some cells. 
	SetColValidStrings(14,14, pVSO); 
	//Force the query to be run
	OnRefreshValidStringObjects();
 
The above Valid String objects are managed completely by the grid framework. Once they are created on the heap and registered 
with the grid, the grid framework will destroy them when the grid is destroyed. When using the Grid Workshop application, you 
are building ValidString objects and storing them in the settings file. In many cases, this can be a valuable time-saver and 
cut down on un-needed coding

*/
//}}GW_CLASS	

	friend class CSheet;
	DECLARE_SERIAL(CGWValidStrings)
public:

//GW_MEMBERS{{(CGWValidStrings, "Construction")
	CGWValidStrings(CGWDataSource* pGWDataSource)		//Constructs a CGWValidStrings object from another one.
		{
			m_bTextStrings = TRUE;
			m_pGWDataSource = pGWDataSource;
		}
	CGWValidStrings()									//Default Constructor.
		{
			m_bTextStrings = TRUE;
			m_pGWDataSource = NULL;
		}
	virtual ~CGWValidStrings()							//Default Destructor,
		{};
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWValidStrings, "Operations")
	virtual void Serialize(CArchive& ar);							//Stores and load an instance of this object to and from a CArchive object.
	void operator=(CGWValidStrings& otherValidStrings)				//Copies one valid string object to another. 
		{
			m_csName = otherValidStrings.m_csName;
			m_pGWDataSource = otherValidStrings.m_pGWDataSource;
			m_bTextStrings = otherValidStrings.m_bTextStrings; 
			m_GWDatabaseRequest = otherValidStrings.m_GWDatabaseRequest;
			m_csaValidStrings.RemoveAll();
			m_csaValidStrings.InsertAt(0,&otherValidStrings.m_csaValidStrings); 
			m_csaItemDataStrings.RemoveAll(); 
			m_csaItemDataStrings.InsertAt(0,&otherValidStrings.m_csaItemDataStrings); 
			m_cpaItemDataPtrs.RemoveAll();
			m_cpaItemDataPtrs.InsertAt(0,&otherValidStrings.m_cpaItemDataPtrs);
		}
	BOOL GetValidString(CString& csValidString, int nStringIndex);	//Retrieve a valid string by its index.
	BOOL GetItemDataPtr(void*& pItemDataPtr, int nStringIndex);		//Retrieve a user data pointer by its index.
	BOOL GetItemDataString(CString& csItemDataString, int nStringIndex);	//Retrieve a user data string by its index.
	void SetName(LPCTSTR csName)									//Set the name of the valid string object.
		{m_csName = csName;}	
	CString GetName()												//Get the name of the valid string object.
		{return m_csName;}
	void SetTextStrings(BOOL bTextStrings)							//Set the flag controling whether strings will be manually loaded or loaded from an external data source. 
		{m_bTextStrings = bTextStrings;}
	BOOL GetTextStrings()											//Get the flag controling whether strings will be manually loaded or loaded from an external data source. 
		{return m_bTextStrings;}
	void SetDatabaseRequest(CGWDatabaseRequest* pGWDatabaseRequest)	//Assign a database request object to be used as a source of the valid strings.
		{
			m_GWDatabaseRequest = *pGWDatabaseRequest;
			m_bTextStrings = FALSE;
		}
	int SetValidString(CString csValidString);								//Assign a valid string.
	void SetItemDataString(CString csItemDataString, int nStringIndex);		//Assign a user data string.
	void SetItemDataPtr(void* pItemDataPtr, int nStringIndex);				//Assign a user data pointer.
	void ClearContents()													//Destroy all strings and user data.
		{
			m_csaValidStrings.RemoveAll();
			m_csaItemDataStrings.RemoveAll();
			m_cpaItemDataPtrs.RemoveAll();
		}
//}}GW_MEMBERS	
	
//GW_MEMBERS{{(CGWValidStrings, "Data Members")
	CString        m_csName;				//The name of the Valid String Object.
	CGWDataSource* m_pGWDataSource;			//A pointer back to the data source to which this objects is attached.
	BOOL m_bTextStrings;					//Determines whether to use the data structures or Database  Request Object.
	CGWDatabaseRequest m_GWDatabaseRequest;	//Holds instructions for performing a query to use for Valid Strings.
	CStringArray m_csaValidStrings;			//The collection of valid strings.
	CStringArray m_csaItemDataStrings;		//Use if you want this object to assume control over destoying string
	CPtrArray    m_cpaItemDataPtrs;			//Collection of user data pointers.
//}}GW_MEMBERS	


//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

};

////////////////////////////////////////////////
// CGWContextMenu
class GW_EXT_CLASS CGWContextMenu : public CMenu
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	friend class CSheet;
	DECLARE_SERIAL(CGWContextMenu)
public:
//GW_MEMBERS{{(CGWContextMenu,"Construction")
	CGWContextMenu(CString csName, CGWDataSource* pGWDataSource)		//Constructs a CGWContextMenu assigning its name and associated GridWiz Data Source.
				{
					m_csName = csName;
					m_pGWDataSource = pGWDataSource;
				    m_nMenuResourceID = 0;
					CreatePopupMenu();
				}
	CGWContextMenu()													//Default Constructor.
				{
					m_pGWDataSource = NULL;
					m_nMenuResourceID = 0;
					CreatePopupMenu();
				}
	virtual ~CGWContextMenu()											//Default Destructor.
				{};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWContextMenu,"Operations")
	virtual void Serialize(CArchive& ar);				//Stores and loads and instance of this object to and from a CArchive object.
	void operator=(CGWContextMenu& otherContextMenu);	//Copies one CGWContextMenu object to another.
	BOOL LoadMenu(UINT nIDResource)						//Loads the menu from resources.
		{
			m_nMenuResourceID = nIDResource;
			return CMenu::LoadMenu(nIDResource);
		}
	void SetName(CString csName)						//Sets the name member.
		{m_csName = csName;}
	CString GetName()									//Gets the name member.
		{return m_csName;}
//}}GW_MEMBERS	
	
//GW_MEMBERS{{(CGWContextMenu,"Data Members")
	CString        m_csName;				//Name given to this context menu.
	CGWDataSource* m_pGWDataSource;			//A pointer back to the data source to which this objects is attached.
	UINT  m_nMenuResourceID;				//The resource id assigned to this menu.
//}}GW_MEMBERS	


//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				PRE_RELEASE, 
				Current_Version_Number,
			  } Version_Table;

};

////////////////////////////////////////////////
// CGWSort
class GW_EXT_CLASS CGWSort : public CObject
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	friend class CSheet;
	//DECLARE_SERIAL(CGWSort)
public:
//Construction
//GW_MEMBERS{{(CGWSort,"Construction")
	CGWSort(CGWGrid* pGrid, BOOL bCallBackForData = FALSE, BOOL bIncludeBlankLines = TRUE);  //Constructs a CGWSort object.
	CGWSort();												 //Default constructor.
	virtual ~CGWSort()										 //Destructor.
	{};
//}}GW_MEMBERS

	
//Implementation
	virtual void Serialize(CArchive& ar) {};
	void operator=(CGWSort& otherSort) {};

//Operations
//GW_MEMBERS{{(CGWSort,"Operations")
	void SetMajorSortColumn(int nColNdx, BOOL bAscending = TRUE, BOOL bNumeric = FALSE);	//Specify the primary sort column.
	void SetMinorSortColumn(int nMinorKeyNdx, int nColNdx, BOOL bAscending = TRUE, BOOL bNumeric = FALSE); //Specify up to 3 minor sort columns
	BOOL Execute();						//Execute the sort on the current sheet.
//}}GW_MEMBERS

//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;
//Data Members
//GW_MEMBERS{{(CGWSort,"Data Memebers")
	CGWGrid* m_pGrid;			//a Pointer back to the grid to which this objects is attached.
	BOOL m_bCallBackForData;	//Call grid virtual functions to access cell data.
	BOOL m_bIncludeBlankLines;	//Determines whether rows which have no data are included in the sort. Default is TRUE.
	int m_nMajorSortCol;		//Major column index to sort on
	int m_nMinorSortCol1;		//First minor sort column index.
	int m_nMinorSortCol2;		//Second minor sort column index.
	int m_nMinorSortCol3;		//Third minor sort column index.
	BOOL m_bMajorAscending;		//Sort major column Ascending.
	BOOL m_bMinorAscending1;	//Sort Minor1 column Ascending.
	BOOL m_bMinorAscending2;	//Sort Minor2 column Ascending.
	BOOL m_bMinorAscending3;	//Sort Minor3 column Ascending.
	BOOL m_bMajorNumeric;		//Sort major column Ascending.
	BOOL m_bMinorNumeric1;	//Sort Minor1 column Ascending.
	BOOL m_bMinorNumeric2;	//Sort Minor2 column Ascending.
	BOOL m_bMinorNumeric3;	//Sort Minor3 column Ascending.
//}}GW_MEMBERS
};


////////////////////////////////////////////////
// CGWSort
class GW_EXT_CLASS CGWSeek
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	enum CONDITION
	{
		EQ = 0,
		LT = 1,
		LE = 2,
		GT = 3,
		GE = 4,
	} nConditions;	
	friend class CSheet;
public:
//Construction
//GW_MEMBERS{{(CGWSeek,"Construction")
	CGWSeek(CGWGrid* pGrid, BOOL bCallBackForData = FALSE)   //Construct a CGWSeek Object
	{
		m_pGrid = pGrid;
		m_bCallBackForData = bCallBackForData;
		m_bSearchEntireGrid =TRUE;
		m_bSearchEntireSheet =TRUE;
		m_bSearchSelection = FALSE;
		m_ptStartAt = CPoint(0,0);
		m_bMatchCase = FALSE;
		m_bSearchDown = TRUE;
		m_bMatchWholeCell = TRUE;
		m_bStopAtTopAndBottom = TRUE;
		m_nSearchCondition = EQ;   
		m_bPositionGrid = TRUE;
		m_nSheetNdx = -1;
	}
	CGWSeek()					//Defualt constructor
	{
		m_pGrid = NULL;
		m_bCallBackForData = FALSE;
		m_bSearchEntireGrid =TRUE;
		m_bSearchEntireGrid =TRUE;
		m_bSearchSelection = FALSE;
		m_ptStartAt = CPoint(0,0);
		m_bMatchCase = FALSE;
		m_bSearchDown = TRUE;
		m_bMatchWholeCell = TRUE;
		m_bStopAtTopAndBottom = TRUE;
		m_nSearchCondition = EQ;   
		m_bPositionGrid = TRUE;
		m_nSheetNdx = -1;
	}
	virtual ~CGWSeek()			//Destructs the CGWSeek object
	{
		for (int x = 0; x < m_arrayRanges.GetSize(); x++)
		{
			CRect* pRect = (CRect*) m_arrayRanges[x];
			delete pRect;
		}
	};
//}}GW_MEMBERS

	void operator=(CGWSeek& otherSeek) {};

//Methods
//GW_MEMBERS{{(CGWSeek,"Methods")
	void SearchEntireGrid(BOOL bSearchEntireGrid = TRUE)  //Instructs the seek object to search all sheets within the grid.
	{
		m_bSearchEntireGrid = bSearchEntireGrid;
		if (bSearchEntireGrid)
			m_bSearchSelection = FALSE;
	}
	void SearchEntireSheet(BOOL bSearchEntireSheet = TRUE) //Instructs the seek object to search every cell in the sheet.
	{
		m_bSearchEntireSheet = bSearchEntireSheet;
		if (bSearchEntireSheet)
			m_bSearchSelection = FALSE;
	}
	void SheetNdx(short nSheetNdx = -1)   //Set the sheet index where the seek object will begin its search.
	{
		m_nSheetNdx = nSheetNdx;
	}
	void SearchSelection(BOOL bSearchSelection = TRUE)  //Instruct the seek object to search the current selection.
	{
		m_bSearchSelection = bSearchSelection;
		if (bSearchSelection)
			m_bSearchEntireGrid = FALSE;
	}
	void StartAt(int nRowNdx, int nColNdx)   //Instruct the seek object to begin its search at a particular row and column.
	{
		m_ptStartAt = CPoint(nColNdx, nRowNdx);
	}
	void SearchFor(CString& csSearchFor)		//Identifies the string to search for.
	{
		m_csSearchString = csSearchFor;		
	}
	void MatchCase(BOOL bMatchCase = TRUE)	//Instruct the seek object to match the case of the search string with that of the cell data.
	{
		m_bMatchCase = bMatchCase;			
	}
	void SearchDown(BOOL bSearchDown = TRUE)		//Instruct the seek object to search downward from the top left to bottom right.
	{
		m_bSearchDown = bSearchDown;	
	}
	void MatchWholeCell(BOOL bMatchWholeCell = TRUE)		//Instruct the seek object to match the search string against the entire contents of the cell.
	{
		m_bMatchWholeCell = bMatchWholeCell;
		if (!m_bMatchWholeCell)
			m_nSearchCondition = EQ;
	}
	void StopAtTopAndBottom(BOOL bStop = TRUE)			//Instruct the seek object to stop and the top or bottom if no match is found.
	{
		m_bStopAtTopAndBottom = bStop;
	}
	void SearchCondition(int nCondition = EQ)			//Identifies the search condition (=, <, <=, >, >=).
	{
		m_nSearchCondition = nCondition;
	}
	void PositionGrid(BOOL bPositionGrid = TRUE)		//Instructs the seek object to select successfully matched cells.
	{
		m_bPositionGrid = bPositionGrid;
	}
	void SearchRange(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx) //Identifies a range of cells to be searched.
	{
		CRect* pRect = new CRect(nBegColNdx, nBegRowNdx, nEndColNdx, nEndRowNdx);
		m_arrayRanges.Add(pRect);
		m_bSearchEntireGrid = FALSE;
	}
	void SearchRows(int nBegRowNdx, int nEndRowNdx)  //Identifies a range of rows to be searched.
	{
		CRect* pRect = new CRect(0, nBegRowNdx, INT_MAX, nEndRowNdx);
		pRect->right--;
		m_arrayRanges.Add(pRect);
		m_bSearchEntireGrid = FALSE;
		m_bSearchSelection = FALSE;
	}
	void SearchColumns(int nBegColNdx, int nEndColNdx)	//Identifies a range of columns to be searched.
	{
		CRect* pRect = new CRect(nBegColNdx, 0, nEndColNdx, INT_MAX);
		pRect->bottom--;
		m_arrayRanges.Add(pRect);
		m_bSearchEntireGrid = FALSE;
		m_bSearchSelection = FALSE;
	}
	void ResetSeek()	//Reset the seek object's values to their defaults.
	{
		for (int x = 0; x < m_arrayRanges.GetSize(); x++)
		{
			CRect* pRect = (CRect*) m_arrayRanges[x];
			delete pRect;
		}
		m_bSearchEntireGrid =TRUE;
		m_bSearchSelection = FALSE;
		m_ptStartAt = CPoint(0,0);
		m_bMatchCase = FALSE;
		m_bSearchDown = TRUE;
		m_bMatchWholeCell = TRUE;
		m_bStopAtTopAndBottom = TRUE;
		m_nSearchCondition = EQ;   
		m_bPositionGrid = TRUE;
	}
	BOOL Execute();	//Execute the seek operation.
	BOOL SeekNext(); //Repeat the last seek operation.
//}}GW_MEMBERS

//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

//Data Members
//GW_MEMBERS{{(CGWSeek,"Data Members")
	CGWGrid*	m_pGrid;					//Pointer back to the grid to which this objects is attached.
	BOOL		m_bSearchEntireGrid;		//Indicates all sheets will be searched.
	BOOL		m_bSearchEntireSheet;		//Indicates all cells in sheet will be searched.
	BOOL		m_bSearchSelection;			//Indicates the currently selected cells will be searched.
	BOOL		m_bCallBackForData;			//Indicates whether virtual functions on the grid are called to access cell data.
	CPoint		m_ptStartAt;				//Identifies the starting row and column location for the search.
	CString		m_csSearchString;			//Identifies the string to search for.
	BOOL		m_bMatchCase;				//Match the case of the search string and the cell contents.
	BOOL		m_bSearchDown;				//Search in a top-down, left-to-right order.
	BOOL		m_bMatchWholeCell;			//Entire contents of cell must match search string.
	BOOL		m_bStopAtTopAndBottom;		//Pause at bottom or top before proceeding with search.
	int			m_nSearchCondition;			//Search criteria (>, >=, <, <=, =);
	BOOL        m_bPositionGrid;			//Select the cell which matches the criteria.
	short		m_nSheetNdx;				//Identifies the starting sheet index for the search.
	CPtrArray   m_arrayRanges;				//Array of cell ranges to be searched.
//}}GW_MEMBERS
};


////////////////////////////////////////////////
// CGWReplace
class GW_EXT_CLASS CGWReplace
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	friend class CSheet;
public:
//Construction
//GW_MEMBERS{{(CGWReplace,"Construction")
	CGWReplace(CGWSeek* pGWSeek, BOOL bCallBackForData = FALSE)	//Construct a CGWReplace object from a CGWSeek object
	  {
			m_pGWSeek = pGWSeek;
			m_bCallBackForData = bCallBackForData;
			m_bReplaceAll = FALSE;
	  }
	CGWReplace()												//Default constructor.
	{};
	virtual ~CGWReplace()										//Destructor. You are responsible for m_pGWSeek.
	{};
//}}GW_MEMBERS
	void operator=(CGWReplace& otherReplace) {};

//Methods
//GW_MEMBERS{{(CGWReplace,"Methods")
	void ReplaceWith(LPCTSTR lpReplacement)    //Set the replacement string.
	{
		m_csReplaceString = lpReplacement;
	}
	void ReplaceAll(BOOL bReplaceAll)			//Set the flag indicating whether to replace all occurences.
	{
		m_bReplaceAll = bReplaceAll;
	}
	int Execute();								//Execute the replacement.
	int ReplaceNext();							//Repeat the last replacement.
//}}GW_MEMBERS

//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

//GW_MEMBERS{{(CGWReplace,"Data Members")
	CGWSeek* m_pGWSeek;			//The CGWSeek object used for the replacement operation.
	CString m_csReplaceString;	//The replacement string.
	BOOL m_bReplaceAll;			//Indicates whether or not to replace all occureneces within seek range.
	BOOL m_bCallBackForData;    //Call grid virtual functions to access data. 
//}}GW_MEMBERS

};

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif

#undef GW_EXT_CLASS

#endif  //__GWDATA_H__
