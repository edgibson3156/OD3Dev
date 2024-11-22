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
// cellmap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCellMap Collection class
#ifndef __CELLMAP_H__
#define __CELLMAP_H__


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



class GW_EXT_CLASS CCellDataObject : public CObject
{ 
//GW_INTERNAL_CLASS{{(CCellDataObject)
/*
This class is responsible for providing persistence to cell data and properties. The
cell's value is contained in a string and its properties stored in a class structure 
called CGWCellSettings. This structure is allocated on the heap and its address stored
in this class. It is quite likely that there is not a CCellDataObject object for each 
cell in your grid. These objects are onlu constructed for cells which have data 
or properties associated with them. Otherwise, cell properties can be obtained from 
global sheet settings, or row and column settings. The class handles serializing itself
to an from an archive through the Serialize() function. Additional pieces of information
can be associated with a cell including a VARIANT, a CObject* and a TAG value. The VARIANT 
is internally for Bookmark, while the CObject* is intended to provide the ability to associate 
objects with a cell. The TAB value is simply an additional text value that can be associated 
with the cell.

This class is marked INTERNAL. The reason for this is that it is rarely necessary to manipulate
objects of this class. It is equally unlikely that you will ever derive from this class because
CSheet and CCellDataMap are not built to handle different kinds of cells. Access to objects
of this class are handled by the CSheet object.
*/
//}}GW_CLASS	

	friend class CSheet;
	DECLARE_SERIAL(CCellDataObject)
public:
//Construction
//GW_INTERNAL_MEMBERS{{(CCellDataObject,"Construction")
	CCellDataObject();					//Constructs a CCellDataObject.
	virtual ~CCellDataObject();			//Destructor.
//}}GW_MEMBERS	


//GW_INTERNAL_MEMBERS{{(CCellDataObject,"Data Members")
	UINT m_nRowNdx;						//The Row coordinate for this data object.
	UINT m_nColNdx;						//The Column coordinate for this data object.
	CString m_csCellText;				//The text value for this cell.
    CObject* m_pObject;					//A variable which can be used to associate a CObject* derived object with this cell.
	_variant_t	m_var;					//A variant which can be associated with each cell.
	CString m_csTag;					//Optional tag value associated with each cell.
	CGWCellSettings* m_pGWCellSettings; //Cell properties such as Color, Font, etc.
//}}GW_MEMBERS	

//Overrideables
//GW_INTERNAL_MEMBERS{{(CCellDataObject,"Overrideables")
	virtual void SetText(CString csCellText)	//Assigns a text value to the object.
												{m_csCellText = csCellText;}
	virtual CString GetText() 					//Returns the text value for this object.
												{return m_csCellText;}
	virtual void SetObject(CObject* pObject);	//Associates a CObject based object with this cell.
	virtual CObject* GetObject() 				//Returns the address of the CObject based object for this cell.
												{return m_pObject;}
	virtual void operator=(CCellDataObject& otherDataObject); //Copies a CCellDataObject.
	virtual void Serialize(CArchive& ar);	//Serializes a CCellDataObject to and from a stream.
//}}GW_MEMBERS
public:
//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				GRIDWIZ_352,
				GRIDWIZ_355,
				Current_Version_Number,
			  } Version_Table;

};


class GW_EXT_CLASS CCellInt : public CCellDataObject
{ 
//GW_INTERNAL_CLASS{{(CCellInt)
/*
This class derives from CCellDataObject which provides basic persistence for cell data and property
settings. This class is a specialization of CCellDataObject intended for managing integer numeric 
type data. This class overrides functions to provide the translation for string to integer and vice versa.

This class is marked INTERNAL. The reason for this is that it is rarely necessary to manipulate
objects of this class. It is equally unlikely that you will ever derive from this class because
CSheet and CCellDataMap are not built to handle different kinds of cells. Access to objects
of this class are handled by the CSheet object.
*/
//}}GW_CLASS	
	DECLARE_SERIAL(CCellInt)
public:
//Construction
//GW_INTERNAL_MEMBERS{{(CCellInt,"Construction")
	CCellInt();				//Default Constructor
	virtual ~CCellInt();	//Destructor
//}}GW_MEMBERS

//Overrideables
//GW_INTERNAL_MEMBERS{{(CCellInt, "Overriden Virtual Functions")
	virtual void SetText(CString csCellText);	//Overidden to handler numeric conversions.
	virtual CString GetText();					//Overidden to handler numeric conversions.
	virtual void Serialize(CArchive& ar);		//Overriden to serialize additional data memebers.
//}}GW_MEMBERS

public:
//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

//GW_INTERNAL_MEMBERS{{(CCellInt,"Data Members")
	long m_nCellLong;					// Long Integer value for this cell.
//}}GW_MEMBERS

};



class GW_EXT_CLASS CCellTime : public CCellDataObject
{ 

//GW_INTERNAL_CLASS{{(CCellTime)
/*
This class derives from CCellDataObject which provides basic persistence for cell data and property
settings. This class is a specialization of CCellDataObject intended for managing date and time data. 
This class overrides functions to provide the translation for string to date and vice versa.

This class is marked INTERNAL. The reason for this is that it is rarely necessary to manipulate
objects of this class. It is equally unlikely that you will ever derive from this class because
CSheet and CCellDataMap are not built to handle different kinds of cells. Access to objects
of this class are handled by the CSheet object.
*/
//}}GW_CLASS	

	
	DECLARE_SERIAL(CCellTime)
public:
//Construction
//GW_INTERNAL_MEMBERS{{(CCellTime,"Construction")
	CCellTime();				//Default Constructor.
	virtual ~CCellTime();		//Destructor.
//}}GW_MEMBERS

//Overrideables
//GW_INTERNAL_MEMBERS{{(CCellTime, "Overriden Virtual Functions")
	virtual void SetText(CString csCellText);		//Overidden to handler date conversions.
	virtual CString GetText();						//Overidden to handler date conversions.
	virtual void Serialize(CArchive& ar);			//Overriden to serialize additional data memebers.
//}}GW_MEMBERS

public:
//Attributes								
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

//GW_INTERNAL_MEMBERS{{(CCellTime,"Data Members")
	CGWDateTime m_CellTime;					//Date value for this cell.
//}}GW_MEMBERS

};


class GW_EXT_CLASS CCellFloat : public CCellDataObject
{ 

//GW_INTERNAL_CLASS{{(CCellFloat)
/*
This class derives from CCellDataObject which provides basic persistence for cell data and property
settings. This class is a specialization of CCellDataObject intended for managing floating point numeric data. 
This class overrides functions to provide the translation for string to float and vice versa.

This class is marked INTERNAL. The reason for this is that it is rarely necessary to manipulate
objects of this class. It is equally unlikely that you will ever derive from this class because
CSheet and CCellDataMap are not built to handle different kinds of cells. Access to objects
of this class are handled by the CSheet object.
*/
//}}GW_CLASS	

	DECLARE_SERIAL(CCellFloat)
public:
//Construction
//GW_INTERNAL_MEMBERS{{(CCellTime,"Construction")
	CCellFloat();				//Default Constructor.
	virtual ~CCellFloat();		//Destructor.	
//}}GW_MEMBERS

//Overrideables
//GW_INTERNAL_MEMBERS{{(CCellTime, "Overriden Virtual Functions")
	virtual void SetText(CString csCellText);		//Overidden to handle numeric conversions.
	virtual CString GetText();						//Overidden to handle numeric conversions.
	virtual void Serialize(CArchive& ar);			//Overriden to serialize additional data memebers.
//}}GW_MEMBERS

public:
//Attributes
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;

//GW_INTERNAL_MEMBERS{{(CCellFloat,"Data Members")
	double m_fCellFloat;				// Float value for this cell.
//}}GW_MEMBERS
};


class CGWImportExportObject;
class GW_EXT_CLASS CSheet : public CObject
{

//GW_INTERNAL_CLASS{{(CSheet)
/*
This class derives from CObject for its capability to provide persistence through serialization. 
The main purpose of this class is to provide a repository for cell objects including data and property 
settings and to provide the necessary routines for manipulating rows and columns of cells. The CSheet 
object uses several MFC map derivatives for keep track of cell objects and their row/column coordinates. The 
m_ColMap is actually a collection of cells within a particular column. Each column is actually a MFC map 
derivative which associates cells with their respective row coordinate. These maps hold entries of type 
CCellDataObject or one of its derivatives. The CCellDataObject provides persistence for both cell data and 
individual cell properties. Two other maps on the sheet keep track of Cell settings for entire rows or columns.
The sheet itself then contains an object of type CGWGridSettings which provides the grid level settings for 
this particular sheet. 

Many operations can be performed on the sheet including sorting, seeking and replacing. Deleting, inserting and 
appending rows and columns. While sheets can be databound, this is handled in the sheets container, CCellDataMap. 
Sheets can be saved and retored from an archive using the serialize() method, however, you will usually rely on the
CCellDataMap object to take of this for all your sheets. Certain instances required sheets to be refreshed, including
upon loading. In most cases, refreshing is used to calculate the high water mark for rows and columns. 
Refreshing bound sheets usually involve re-running the query and rebinding to columns.

This class is marked INTERNAL. The reason for this is that it is rarely necessary to manipulate
objects of this class. It is equally unlikely that you will ever derive from this class because
CCellDataMap is not built to handle different kinds of sheets. Access to objects
of this class are handled by the CCellDataObject class.
*/
//}}GW_CLASS	

	friend class CCellDataMap;
	friend class CDatabaseWorkBook;
	DECLARE_SERIAL(CSheet)

// Construction
public:
//Construction
//GW_INTERNAL_MEMBERS{{(CSheet,"Construction")
	CSheet();				//Defualt constructor.
	virtual ~CSheet();		//Destructor.
	void DestroyColMap();		//Deletes the data for this sheet.
	void DestroyColSettings();	//Deletes the cell settings for columns.
	void DestroyRowSettings();	//Deletes the cell settings for rows.
//}}GW_MEMBERS

// Attributes
public:	 
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;



//Data Memebers	
//GW_INTERNAL_MEMBERS{{(CSheet,"Data Members")
	CGWMapIntToPtr m_ColMap;				//Keeps track of CGWMapInToPos for keeping track of rows.
	CGWMapIntToPtr m_RowSettings;			//Map of Row Settings Objects
	CGWMapIntToPtr m_ColumnSettings;		//Map of Col Settings Objects
	CObject* m_pSheetExtraData;				//Register any extra sheet data using this member. //Used by ODBCMap and DAOMap to hold the recordset*.
	CGWDatabaseRequest m_DatabaseRequest;	//Used to store database info for the this sheet.
	CGWDataSource* m_pGWDataSource;			//Pointer to data source owning this sheet.
	int m_nCacheRows;						//How many rows to cache. Default is 100;
	BOOL m_bCacheHitEOF;					//Recordset hit EOF?
	long m_nCacheHighWater;					//High water mark or highest row within cache page
	BOOL m_bCachingEnabled;					//Invoke Caching code?
	int m_nCachePages;						//Maximum number of pages to keep current in the cache
	CPtrArray m_arrayCachedPages;			//Array of CCachePage  objects
	CUIntArray      m_RowOrderArray;		//These arrays offer indirection when
	CGWMapIntToInt	m_MapColumnToField;	    //sorting or ordering is needed without
//}}GW_MEMBERS

protected:
//GW_INTERNAL_MEMBERS{{(CSheet,"Protected Data Members")
	int m_nMaxDataRows;						//The maximum data row index existing in this sheet.
	int m_nMaxDataCols;						//The maximum data column index existing in the sheet.
	int m_nMajorSortCol;					//Primary sort column.
	int m_nMinorSortCol1;					//Secondary sort column.
	int m_nMinorSortCol2;					//Third order sort column.
	int m_nMinorSortCol3;					//Fourth order sort column.
	BOOL m_bAscending;						//Sort order indicator on primary sort column.
	BOOL m_bAscending1;						//Sort order indicator on secondary sort column.
	BOOL m_bAscending2;						//Sort order indicator on third sort column.
	BOOL m_bAscending3;						//Sort order indicator on fourth sort column.
	BOOL m_bNumeric;						//Sort numerics on primary sort column.
	BOOL m_bNumeric1;						//Sort numerics on secondary sort column.
	BOOL m_bNumeric2;						//Sort numerics on third sort column.
	BOOL m_bNumeric3;						//Sort numerics on fourth sort column.
	CString m_csSheetName;					//The name given to this sheet.
	CGWGridSettings* 	m_pGWGridSettings;	//The grid settings used to display this sheet.
	CGWGCOMappings* 	m_pGWGCOMappings;	//The cell mappings for this sheet.
//}}GW_MEMBERS

// Operations
public:
//GW_INTERNAL_MEMBERS{{(CSheet,"Operations")
	virtual void operator=(CSheet& otherSheet);		//Copies one sheet to another.
	virtual int GetMaxRow();						//Returns the highest row index for this sheet.
	virtual int GetMaxCol();						//Return the highest column index for this sheet.
	virtual CObject* GetSheetExtraData()			//Returns a CObject* which has been associated with this sheet. Typically used with the database classes.
													{return m_pSheetExtraData;}   
	virtual void SetSheetExtraData(CObject* pObject); //Associates a CObject* with this sheet. Typically used with the database classes to hold a CRecordset address.
													
	virtual CGWDatabaseRequest* GetDatabaseRequest() //Returns a pointer to the CGWDatabaseRequest Object for this sheet.
													{return &m_DatabaseRequest;}
	virtual void SetDatabaseRequest(CGWDatabaseRequest* pDatabaseRequest) //Sets the CGWDatabaseRequest Object for this sheet.
													{m_DatabaseRequest = *pDatabaseRequest;}
	virtual CString GetSheetName()					//Retrieve the sheet name.
													{return m_csSheetName;}
	virtual void SetSheetName(CString csSheetName)	//Assign the sheet name.
													{m_csSheetName = csSheetName;}
	virtual void ImportData(CGWImportExportObject* pGWImportExportObject);	//Import data from a external data source.
													
	virtual void FixupGroups(CGWMapIntToPtr* pMap);	//Realign cell groups after data has been moved.
	virtual void RefreshSheet(CGWMapIntToPtr* pMap, BOOL bFixupGroups = TRUE); //Walk the sheet fixing row and column indexes. Run queries for database sheets.
	virtual void RefreshSheetIDataLink(); //Walk the sheet fixing row and column indexes. Run queries for database sheets.
	virtual void RefreshSheetAdoRecordset(); //Walk the sheet fixing row and column indexes. Run queries for database sheets.
	virtual void RefreshSheetOledbRowset(); //Walk the sheet fixing row and column indexes. Run queries for database sheets.
	virtual long GetBookmarkRow(_variant_t& varBookmark, long nStart, long nEnd);	//Retrieve the row index for a particular bookmark in a bound sheet.
	virtual long AppendBookmarkRow(_variant_t& varBookmark);	//Append a new row to the end of the sheet. New rows comes from asynchronous inserts.
	virtual void Serialize(CArchive& ar);			//Save or load this sheet to a CArchive object.
//}}GW_MEMBERS

	
//GW_INTERNAL_MEMBERS{{(CSheet,"Column Binding")
	virtual void BindAllColumns(int nFieldCount, int nFixedColumns);  //Assign a one-to-one column to field binding.
	virtual void BindColumn(UINT nColNdx, UINT nFieldNdx, CObject* pObject); //Bind a particular column to a specific field.
	virtual int  GetBoundFieldIndex(UINT nColNdx);  //Retrieve the field index for a particular column.
	virtual BOOL BoundFields();	//Returns TRUE if fields have been bound.
	virtual void UnBindAllColumns(); //Removes all column to field binding.
//}}GW_MEMBERS
	
//GW_INTERNAL_MEMBERS{{(CSheet,"Sort, Seek and Replace")
	virtual void Sort(int nMajorCol, BOOL bAscending, BOOL bNumeric, int nMinorCol1, BOOL bAscending1, BOOL bNumeric1, int nMinorCol2, BOOL bAscending2, BOOL bNumeric2, int nMinorCol3, BOOL bAscending3, BOOL bNumeric3, BOOL bCallBackForData, BOOL bIncludeBlankLines); //Sorts the data source.
	BOOL CompareAndSwap(int nRow, CStringArray& arraySortKeyMajor, CStringArray& arraySortMinor1, CStringArray& arraySortMinor2, CStringArray& arraySortMinor3, BOOL bIncludeBlankLines);	//Routine which is responsible for sorting.
	virtual int GetRowOrderIndex(int nRowNdx);
	virtual BOOL Seek(CGWSeek* pSeek, BOOL bNext);
	BOOL IsMatch(int nRowNdx, int nColNdx, CString csSearchString, CGWSeek* pSeek);
	BOOL IncludedInSearch(CGWSeek* pSeek);
	virtual long Replace(CGWReplace* pReplace, BOOL bNext);
//}}GW_MEMBERS
	

//GW_INTERNAL_MEMBERS{{(CSheet,"Data Access")
	virtual CObject* GetCell(UINT nRowNdx, UINT nColNdx);						//Retrieve the CCellDataObject based on row and column coordinates.
	virtual void SetCell(UINT nRowNdx, UINT nColNdx, CObject* pObject);			//Assign a CCellDataObject to a row and column.
	virtual void GetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject);  //Retrieve the CObject* associated with this cell.
	virtual void GetCellVariant(UINT nRowNdx, UINT nColNdx, _variant_t& var);  //Retrieve the Variant associated with this cell.
	virtual void SetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject);	//Associate a CObject* with this cell.
	virtual void SetCellVariant(UINT nRowNdx, UINT nColNdx, _variant_t& var);	//Associate a variant with this cell.
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Set the text value of a cell.
	virtual void SetCellTextIDataLink(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Set the text value of a cell if the sheet is attached to a IDatalink object.
	virtual void SetCellTextAdoRecordset(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Set the text value of a cell if the sheet is attached to a Ado Recordset.
	virtual void SetCellTextOledbRowset(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Set the text value of a cell if the sheet is attached to a Ole DB Data Source.
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Retrieve the text value for a cell.
	virtual void GetCellTextIDataLink(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Retrieve the text value for a cell if the sheet is attached to a IDatalink object.
	virtual void GetCellTextAdoRecordset(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Retrieve the text value for a cell if the sheet is attached to a Ado Recordset.
	virtual void GetCellTextOledbRowset(UINT nRowNdx, UINT nColNdx, CString& csCellText);	//Retrieve the text value for a cell if the sheet is attached to a OleDB Rowset.
	virtual void SetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong);		//Set the long integer value of a cell.
	virtual void GetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong);		//Retrieve the long integer value for a cell.
	virtual void SetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat);	//Set the floating point double value for a cell.
	virtual void GetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat);	//Retrieve the floating point double value for a cell. 
	virtual void SetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime);	//Set the date value for a cell.
	virtual void GetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime);	//Retriece the date value for a cell.
	virtual BOOL GetCellValidString(UINT nRowNdx, UINT nColNdx, CString& csCellText, void*& pItemDataPtr, int nStringID)  //Get a valid string assoicated with this cell.
														{return FALSE;}
	virtual void GetDefaultCellText(UINT nRowNdx, UINT nColNdx, CString& csDefaultCellText, int nSheet); //Return the default text value during an Append Row operation.
	virtual void SetCellTag(UINT nRowNdx, UINT nColNdx, CString& csTag);	//Set the tag value of a cell.
	virtual void GetCellTag(UINT nRowNdx, UINT nColNdx, CString& csTag);	//Retrieve the tag value for a cell.
//}}GW_MEMBERS


//GW_INTERNAL_MEMBERS{{(CSheet,"Grid Property Settings")
	virtual CGWGridSettings* GetGridSettings()										//Retrieve the sheet's display properties object.
														{return m_pGWGridSettings;}
	virtual void SetGridSettings(CGWGridSettings* pGridSettings)					//Set the sheet's display properties object.
														{m_pGWGridSettings = pGridSettings;}
	virtual CGWGCOMappings* GetGCOMappings()										//Retrieve the sheet's GCO mapping structure.
														{return m_pGWGCOMappings;}
	virtual void SetGCOMappings(CGWGCOMappings* pGWGCOMappings)						//Set the sheet's GCO mapping structure.
														{m_pGWGCOMappings = pGWGCOMappings;}
	virtual CGWCellSettings* GetCellSettings(UINT nRowNdx, UINT nColNdx);			//Get the cell display settings.
	virtual CGWRowSettings*  GetRowSettings(UINT nRowNdx);							//Get the row's display settings.
	virtual CGWColumnSettings* GetColumnSettings(UINT nColNdx);						//Get the column's display settings.
	virtual void SetRowSettings(UINT nRowNdx, CGWRowSettings* pNewSettings);		//Set the row's display settings.
	virtual void SetColumnSettings(UINT nColNdx, CGWColumnSettings* pNewSettings);	//Set the column's display settings.
//}}GW_MEMBERS


//GW_INTERNAL_MEMBERS{{(CSheet,"Data Manipulation")
	virtual void DeleteRow(UINT nRowNdx, UINT nCount);								//Delete one or more rows of data and display settings.
	virtual void InsertRow(UINT nRowNdx, UINT nCount);								//Insert one or more rows of data and shift display settings.
	virtual void DeleteColumn(UINT nColNdx, UINT nCount, BOOL bFixupGroups = TRUE);	//Delete one or more columns of data and display settings.
	virtual void InsertColumn(UINT nColNdx, UINT nCount, BOOL bFixupGroups = TRUE);	//Insert one or more columns of data and shift display settings.
	virtual void MoveColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore);	//Move one or more columns of data and shift display settings.
	virtual void MoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore);		//Move one or more rows of data and shift display settings.
	virtual void CopyColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore);	//Copy one or more columns of data and shift display settings.
	virtual void CopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore);		//Copy one or more rows of data and shift display settings.
	virtual void ClearSheetData();					//Clear the sheet's data only.			
	virtual void ClearSheetAll();					//Clear the sheet's data and display settings.
//}}GW_MEMBERS

//Caching
//GW_INTERNAL_MEMBERS{{(CSheet,"Caching")
	void SetCachePageSize(int nNumRows);	//Sets the number of rows in each cache page
	void SetCachePages(int nNumPages);		//Sets the number of cache pages to keep
	void SetCachingOn();					//Turns caching on.
	void FreeAllCachePages();				//Frees all the pages in the cached
	CCachePage* PageInCache(int nRowNdx);	//Determines whether there is a particular page existing in the cache.
	void UpdateCachePage(int nBegRowNdx, int nRowCount); //Forces the cached to refresh the rows starting at nBegRowNdx for nRowCount rows.
	BOOL RecordInCache(int nRowNdx);		//Determines whether a particular record is in the cache.
	int OnCacheFault(long nRowCount)		//Called when a record is requested which does not exist in the cache.
														{return -1;}
//}}GW_MEMBERS

};




class GW_EXT_CLASS CCellDataMap : public CGWDataSource
{

//GW_CLASS{{(CCellDataMap)
/*
This class derives from pure abstract class, CGWDataSource. This is the primary implementation of the GridWiz Data Source.
The main purpose of this class is to provide a repository for sheet objects and provide an interface for accessing 
data by row index, column index and sheet index. The user interface side of the GridWiz Class Library has 
built-in support for browsing GridWiz DataSources such as CCellDataMap. This object maintains collections of CSheet objects 
as well as sheet names, ValidStringObjects and context menus. Many of the operations implemented in this object
deal with providing persistance, load and saving data,  and manipulating sheets. The functions which are designed to 
provide access to cell data are typically passed through to the targeted sheet where CSheet functions take over.

This class is designed to be used as a base class, but is very rarely used that way. In most cases, you will 
use this class directly and will not need to derive to add functionality. Objects of this class are designed 
to work seamlessly with any GridWiz grid and therefore any attempt to derive new functionality should be undertaken 
with great care. In most cases. you can accomplish what you need by overriding CGWGrid virtual functions in combination
with using this class. It is much simpler to create new functionality at the grid level by using the GridWiz Wizard to 
derive from some of the many virtual CGWGrid functions.

*/
//}}GW_CLASS	


	DECLARE_SERIAL(CCellDataMap)
// Construction
public:
//Construction
//GW_MEMBERS{{(CSheet,"Construction")
	CCellDataMap();				//Default Constructor.
	virtual ~CCellDataMap();	//Destructor.
//}}GW_MEMBERS

// Attributes
public:	 
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				GRIDWIZ_3_5_0,
				GRIDWIZ_352,
				Current_Version_Number,
			  } Version_Table;
	
	
//GW_INTERNAL_MEMBERS{{(CCellDataMap,"Data Members")
	CObArray m_Sheets;  						//Keeps track of grid sheets.
	CStringArray m_SheetNames;					//Keeps track of grid sheet names.
	CMapStringToOb m_mapValidStringObjects;		//Used to track the valid string objects associated with a worksheet.
	CMapStringToOb m_mapContextMenus;			//Used to track the Context Menu objects associated with cells on a worksheet.
	BOOL m_bFreeDiscardedPages;					//Determines whether newly discarded pages are automatically freed.
//}}GW_MEMBERS

protected:

// Operations
public:

//GW_MEMBERS{{(CCellDataMap,"Operations")
	void operator=(CCellDataMap& otherCellDataMap);  //Copies a CCellDataMap Object.
//}}GW_MEMBERS
    
	

//Caching
//GW_INTERNAL_MEMBERS{{(CCellDataMap,"Caching")
	virtual void FreeAllCachePages(int nSheet);				//Frees all the pages in the cached
	virtual int FillCache(int nBegRow, int nSheet);			//Called from framework when a cache hit occurs. Returns the number of rows added.
	virtual void UpdateCacheRow(int nRowNdx, int nSheet);	//Update a particular record in the cache
	BOOL ScrollToBottom(int nSheet);						//Force the caching algorithm to search for the bottom of the data and then set the grid's scroll range.
//}}GW_MEMBERS


//GW_MEMBERS{{(CCellDataMap, "Overriden Virtual Functions")
	virtual void Serialize(CArchive& ar);					//Overidden to serialize additional data members.
	virtual void SetCachePageSize(int nNumRows, int nSheet);//Overidden to set the number of rows in each cache page
	virtual void SetCachePages(int nNumPages, int nSheet);	//Overidden to set the number of cache pages to keep
	virtual void SetCachingOn(int nSheet);					//Overidden to turn caching on.
	virtual void SetRowCacheIncrement(int nIncrement, int nSheetNdx); //Overidden to adjust the number of rows per cache page.
	virtual int GetRowCacheIncrement(int nSheetNdx);		//Overidden to return the number of rows per cache page.
	virtual void SetDataEntryMode(int m_nDataEntryMode = 0, int m_nDataEntryModeState = 0);	//Overidden to put the data source into either Edit(Normal) or Add Mode(Special).
	virtual void GetDataEntryMode(int& m_nDataEntryMode, int& m_nDataEntryModeState);		//Overidden to retrieve the current editing mode of the data source.
	virtual void SetAddRowIndex(int nAddIndex);				//Overidden to set to identify the row index which is used for the "AddRow" feature.
    virtual void DestroySheets();							//Overidden to destroy the CSheet object held by this data source.
	virtual void ResetSheetDBSettings(int nSheet);			//Overidden to reset the sheet in conjunction with a link to a external data source.
	virtual void ResetDataSource();							//Overidden to remove all sheets and add one back.
	virtual void RefreshSheet(int nSheet = 0);				//Overidden to cause a particular sheet object to recalculate and check any external database links.
	virtual long GetBookmarkRow(_variant_t& varBookmark, long nStart, long nEnd, int nSheet = 0);	//Retrieve the row index for a particular bookmark in a bound sheet.
	virtual long AppendBookmarkRow(_variant_t& varBookmark, int nSheet = 0);	//Append a new row to the end of the sheet. New rows comes from asynchronous inserts.
	virtual void RefreshSheet(CString csSheet);				//Overidden to cause a particular sheet object to recalculate and check any external database links.
	virtual void RecalcSheets();							//Overidden to casue a particular sheet to recalculate its max data row and column indexes.
	virtual void ActivateSheet(int nSheet);					//Overidden to cause a sheet to become the active sheet and check any external data links.
	virtual CGWDatabaseRequest* GetDatabaseRequest(int nSheet);	//Overidden to return a Database request object for a particular sheet.
	virtual void SetDatabaseRequest(CGWDatabaseRequest* pDatabaseRequest, int nSheet);	//Overidden to set a database request object.
	virtual void SetGridGlobalSettings(CGWGridSettings* pGridGlobalSettings);			//Overidden to store the grid global settings.
	virtual BOOL GetDataSourceError(CPoint& ptErrorCell, int& nErrorCode, CString& csErrorString, BOOL& bDisplayed);	//Overidden to retrieve the error state of the data source.
	virtual void LoadSettings(CString csSettingsFile);		//Overidden to load a property stream from a file or application resource.
	virtual int GetNumSheets()								//Overidden to calculate and return the number of sheets contained in the data source.
		{return m_SheetNames.GetSize();}
	virtual CString GetSheetName(int nSheet);				//Overidden to get the name of a particular sheet.
	virtual void SetSheetName(int nSheet, CString csSheetName);	//Overidden to set the name of a particular sheet.
	virtual int GetMaxRow(int nSheet);						//Overidden to retrieve the largest row index associated with actual data.
	virtual int GetMaxCol(int nSheet);						//Overidden to retrieve the largest column index associated with actual data.
	virtual void SetNumRows(int nNumRows, int nSheet = 0);	//Overidden to set the largest row index associated with actual data.
	virtual void SetNumColumns(int nNumColumns, int nSheet = 0);	//Overidden to set the largest column index associated with actual data.
	virtual int FindSheet(CString csSheetName);				//Overidden to return a sheet index based on a sheet name.
	virtual CSheet* GetSheet(CString csSheetName);			//Overidden to return a CSheet* based on a sheet name.
	virtual void InsertNewSheet(int nInsertBefore, CString csSheetName, CObject* pSheetExtraData = NULL);	//Overidden to insert a new sheet in the collection of sheets.
	virtual void RemoveSheet(int nSheetIndex);				//Overidden to remove and destroy a sheet from the collection of sheet objects.
	virtual void MoveSheet(int nSheetIndex, int nCount);	//Overidden to change the order of sheets.
	virtual int  AddSheet(CString csSheetName, CObject* pSheetExtraData = NULL);	//Overidden to append a new sheet to the collection.
	virtual void CopySheet(int nSourceSheetNdx, int nDestSheetNdx);					//Overidden to copy a sheet's contents to another sheet.
	virtual CObject* GetSheetExtraData(int nSheet);			//Overidden to retrieve the extra data pointer associated with a sheet.
	virtual void SetSheetExtraData(CObject* pObject, int nSheet); //Overidden to set the extra data pointer associated with a sheet.
	virtual void GetCell(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0);	//Overidden to retrieve the address of the object used to represent a cell.
	virtual void SetCell(UINT nRowNdx, UINT nColNdx, CObject* pObject, int nSheet = 0);		//Overidden to set the address of the object used to represent a cell.
	virtual void SetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0);	//Overidden to retrieve the associated CObject* with the contents of a cell.
	virtual void GetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0);	//Overidden to associate a CObject* with the contents of a cell.
	virtual void SetCellVariant(UINT nRowNdx, UINT nColNdx, _variant_t& pObject, int nSheet = 0);	//Overidden to retrieve the associated Variant with the contents of a cell.
	virtual void GetCellVariant(UINT nRowNdx, UINT nColNdx, _variant_t& pObject, int nSheet = 0);	//Overidden to associate a Variant with the contents of a cell.
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);	//Overidden to set the text contents of a cell.
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);	//Overidden to retrieve the text contents of a cell.
	virtual void SetCellTag(UINT nRowNdx, UINT nColNdx, CString& csTag, int nSheet = 0);	//Set the tag value of a cell.
	virtual void GetCellTag(UINT nRowNdx, UINT nColNdx, CString& csTag, int nSheet = 0);	//Retrieve the tag value for a cell.
	virtual BOOL GetCellValidString(UINT nRowNdx, UINT nColNdx, CString& csCellText, void*& pItemDataPtr, int nStringID, int nSheet = 0) //Overidden to retrieve a valid string associated with a cell.
		{return FALSE;}
	virtual void SetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0);			//Overidden to set a numeric value of a cell.
	virtual void GetCellLong(UINT nRowNdx, UINT nColNdx, long& nCellLong, int nSheet = 0);			//Overidden to get a numeric representation of the value of a cell.
	virtual void SetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0);		//Overidden to set a floting point value of a cell.
	virtual void GetCellFloat(UINT nRowNdx, UINT nColNdx, double& fCellFloat, int nSheet = 0);		//Overidden to get a floating representation of the value of a cell.
	virtual void SetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0);	//Overidden to set a date/time value of a cell.
	virtual void GetCellTime(UINT nRowNdx, UINT nColNdx, CGWDateTime& CellTime, int nSheet = 0);	//Overidden to get a date/time representation of the value of a cell.
	virtual void DeleteRow(UINT nRowNdx, UINT nCount, int nSheet = 0);								//Overidden to delete a row from a sheet.
	virtual void InsertRow(UINT nRowNdx, UINT nCount, int nSheet = 0);								//Overidden to insert a row into a sheet.
	virtual void DeleteColumn(UINT nColNdx, UINT nCount, int nSheet = 0);							//Overidden to delete a column from a sheet.
	virtual void InsertColumn(UINT nColNdx, UINT nCount, int nSheet = 0);							//Overidden to insert a column into a sheet.
	virtual void MoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = 0);		//Overidden to move a row within a sheet.
	virtual void MoveColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int nSheet = 0);	//Overidden to move a column within a sheet.
	virtual void CopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = 0);		//Overidden to copy a row within a sheet.
	virtual void CopyColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int nSheet = 0);	//Overidden to copy a column within a sheet.
	virtual void ClearSheetData(int nSheet);														//Overidden to clear the contents of a sheet.
	virtual void ClearSheetAll(int nSheet);															//Overidden to clear the contents and any property settings of a sheet.
	virtual void ImportData(CGWImportExportObject* pGWImportExportObject, int nSheet);				//Overidden to import data from an external delimitted file.
	virtual void BindColumn(UINT nColNdx, UINT nFieldNdx, CObject* pObject, int nSheet = 0);		//Overidden to associate a grid column with an arbitrary field index.
	virtual int  GetBoundField(int nColNdx, CObject* pObject, int nSheet = 0);						//Overidden to return the field index associated with a column index.
	virtual void Sort(int nMajorCol, BOOL bAscending = TRUE, BOOL bNumeric = FALSE, int nMinorCol1 = -1, BOOL bAscending1 = TRUE, BOOL bNumeric1 = FALSE, int nMinorCol2 = -1, BOOL bAscending2 = TRUE, BOOL bNumeric2 = FALSE, int nMinorCol3 = -1, BOOL bAscending3 = TRUE, BOOL bNumeric3 = FALSE, BOOL bCallBackForData = FALSE, BOOL bIncludeBlankLines = TRUE, int nSheet = 0);	//Overidden to sort the rows of a sheet.
	virtual int GetRowOrderIndex(int nRowNdx, int nSheet = 0);										//Overidden to retrieve the actual row index for a row in a sorted grid.
	virtual BOOL Seek(CGWSeek* pSeek, BOOL bNext, int nSheet = 0);									//Overidden to seek the contents of the data source for specific values.
	virtual long Replace(CGWReplace* pReplace, BOOL bNext, int nSheet = 0);							//Overidden to replace specific values in the data source based on seek criteria.
	virtual CGWGridSettings* GetGridSettings(int nSheet = 0);										//Overidden to retrieve the Grid settings structure associated with a sheet in the data source.
	virtual CGWCellSettings* GetCellSettings(UINT nRowNdx, UINT nColNdx, int nSheet = 0);			//Overidden to retrieve the cell settings structure for a cell with in a sheet.
	virtual CGWGCOMappings* GetGCOMappings(int nSheet = 0);											//Overidden to retrieve the GCO mappings structure for a sheet in the data source.
	virtual CGWRowSettings* GetRowSettings(int nRowNdx, int nSheet = 0);							//Overidden to retrieve the row settings structure for a row in the grid.
	virtual CGWColumnSettings* GetColumnSettings(int nColNdx, int nSheet = 0);						//Overidden to retrieve the column settings structure for a column in the grid.
	virtual void SetGridSettings(CGWGridSettings*& pSetting, int nSheet = 0);						//Overidden to set the Grid settings structure associated with a sheet in the data source.
	virtual void SetCellSettings(UINT nRowNdx, UINT nColNdx, CGWCellSettings*& pSetting, int nSheet = 0);	//Overidden to set the cell settings structure for a cell with in a sheet.
	virtual void SetGCOMappings(CGWGCOMappings*& pSetting, int nSheet = 0);							//Overidden to set the GCO mappings structure for a sheet in the data source.
	virtual void SetRowSettings(int nRowNdx, CGWRowSettings*& pSetting, int nSheet = 0);			//Overidden to set the row settings structure for a row in the grid.
	virtual void SetColumnSettings(int nColNdx, CGWColumnSettings*& pSetting, int nSheet = 0);		//Overidden to set the column settings structure for a column in the grid.
	virtual BOOL RegisterValidStringObject(CGWValidStrings* pGWValidStrings);						//Overidden to register a valid strings object with the data source.
	virtual BOOL LookupValidStringObject(CString m_csName, CGWValidStrings*& pValidStringObject);	//Overidden to retrieve a valid strings object using its name.
	virtual POSITION GetFirstValidStringObject();													//Overidden to retrieve the first valid string object in the collection of registered valid strings objects.
	virtual void GetNextValidStringObject(POSITION& pos, CString& csName, CGWValidStrings*& pValidStringObject);	//Overidden to retrieve the next valid string object in the collection of registered valid strings objects.
	virtual void RefreshValidStringObjects();														//Overidden to reload any valid string objects which are based on external database links.
	virtual void RemoveValidStringObject(CGWValidStrings* pGWValidStrings);							//Overidden to remove a valid string object from the collection of valid string objects.
	virtual BOOL RegisterContextMenu(CGWContextMenu* pGWContextMenu);								//Overidden to register a context menu with the data source.
	virtual BOOL LookupContextMenu(CString m_csName, CGWContextMenu*& pContextMenu);				//Overidden to retrieve a context menu based on its name.
	virtual POSITION GetFirstContextMenu();															//Overidden to retrieve the first context menu from the collection of registered context menus.
	virtual void GetNextContextMenu(POSITION& pos, CString& csName, CGWContextMenu*& pContextMenu);	//Overidden to retrieve the next context menu from the collection of registered context menus.
	virtual void RemoveContextMenu(CGWContextMenu* pGWContextMenu);									//Overidden to remove a context menu from the collection of registered context menus.
	virtual int LoadData(CGWDataContext gwdc, int nSheet, CFile* pFile);					//Overidden to load data from an external source.
	virtual int LoadData(CGWDataContext gwdc, int nSheet, LPCSTR lpszBuffer);				//Overidden to load data from an external source.
	virtual int FastLoad(CGWDataContext gwdc, int nSheet, CFile* pFile);					//Overidden to fast load data from an external source.
	virtual int FastLoad(CGWDataContext gwdc, int nSheet, LPCSTR lpszBuffer);				//Overidden to fast load data from an external source.
	virtual int SaveData(CGWDataContext gwdc, int nSheet, CFile* pFile);					//Overidden to save data to an external data source.
	virtual int SaveData(CGWDataContext gwdc, int nSheet, LPCSTR lpszBuffer);				//Overidden to save data to an external data source.
//}}GW_MEMBERS

};

/////////////////////////////////////////////////////////////////////////////
// CSQLDlg dialog

class GW_EXT_CLASS CSQLDlg : public CDialog
{

//GW_INTERNAL_CLASS{{(CSQLDlg)
/*
This class represents a Dialog for gathering an SQL statement or launching another dialog
to graphically build a SQL statement. This dialog is rarley used and does not support ADO 
or OLE DB. This is included for compatibility with older versions of GridWiz.

This class is marked INTERNAL. The reason for this is no longer used and included for backward
compatibility only.
*/
//}}GW_CLASS	

	
// Construction
public:
//GW_INTERNAL_MEMBERS{{(CSQLDlg,"Construction")
	CSQLDlg(CGWDataSource* pGWDataSource, CGWDatabaseRequest& GWDatabaseRequest, CWnd* pParent = NULL);  //Constructs a CSQLDlg object.
//}}GW_MEMBERS

// Dialog Data
	//{{AFX_DATA(CSQLDlg)
	enum { IDD = IDD_GW_SQL };
	//}}AFX_DATA

//GW_INTERNAL_MEMBERS{{(CSQLDlg,"Data Members")
	CString	m_csSQL;							//The SQL String to be displayed and editted.
	CGWDataSource* m_pGWDataSource;				//The data source owning the database request object.
	CGWDatabaseRequest m_GWDatabaseRequest;		//The database request object owning the SQL statement.
	BOOL m_bProtected;							//Make the SQL statement read-only.
//}}GW_MEMBERS

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSQLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnQbe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CGWFileDlg dialog

class GW_EXT_CLASS CGWFileDlg : public CDialog
{

//GW_INTERNAL_CLASS{{(CGWFileDlg)
/*
This class represents a special file open dialog. This dialog is rarley used. This is included for 
compatibility with older versions of GridWiz.

This class is marked INTERNAL. The reason for this is no longer used and included for backward
compatibility only.
*/
//}}GW_CLASS	
	
	
// Construction
public:

//GW_INTERNAL_MEMBERS{{(CGWFileDlg,"Construction")
	CGWFileDlg(CGWFileIdentifier m_GWFileId, CWnd* pParent = NULL);   //Constructs a CGWFileDlg object.
//}}GW_MEMBERS

// Dialog Data
	//{{AFX_DATA(CGWFileDlg)
	enum { IDD = IDD_GW_GWFILE };
	//}}AFX_DATA

//GW_INTERNAL_MEMBERS{{(CGWFileDlg,"Data Members")
	CGWFileIdentifier m_GWFileId;			//The CGWFileID Object to be displayed and edited.
	CString m_csRelativeTo;					//Path to use as a absolute base for a relative path.
	CString m_csCaption;					//The caption to display on the dialog.
	DWORD m_dwFlags;						//FileOpen dialog flags.
//}}GW_MEMBERS

#if _MFC_VER >= 0x0400
	LPOFNHOOKPROC m_lpfnHook;
#endif

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGWFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGWParamDlg dialog

class GW_EXT_CLASS CGWParamDlg : public CDialog
{

//GW_INTERNAL_CLASS{{(CGWParamDlg)
/*
This class represents a Dialog for gathering parameters for prepared SQL statements. This dialog is rarley 
used and does not support ADO or OLE DB. This is included for compatibility with older versions of GridWiz.

This class is marked INTERNAL. The reason for this is no longer used and included for backward
compatibility only.
*/
//}}GW_CLASS	

	
// Construction
public:
//GW_INTERNAL_MEMBERS{{(CGWParamDlg,"Construction")
	CGWParamDlg(CGWDatabaseRequest& GWDatabaseRequest, CWnd* pParent = NULL);   // Constructs a CGWParamDlg object.
//}}GW_MEMBERS

// Dialog Data
	//{{AFX_DATA(CGWParamDlg)
	enum { IDD = IDD_GW_PARAMETERS };
	//}}AFX_DATA

//GW_INTERNAL_MEMBERS{{(CGWParamDlg,"Data Members")
	CGWDatabaseRequest m_GWDatabaseRequest;   //The database request object which owns the paramters being displayed and edited.
//}}GW_MEMBERS

//GW_INTERNAL_MEMBERS{{(CGWParamDlg,"Operations")
	void UpdateList();
//}}GW_MEMBERS
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGWParamDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeParamList();
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};





class GW_EXT_CLASS CGWImportExportObject
{

//GW_CLASS{{(CGWImportExportObject)
/*

This class is used to describe an import or export operation. The data members hold all of the information 
required to perform an import or export operation on a data within a single sheet. Use the data member access
functions to identify row and column locations, delimiters, and other identifiers to control the operation. 
There are several operations which can be performed depending on the location of the source data and its 
final destination.

This class is intended to be used as-is. The CGWGrid and CCellDatamap classes are designed to work with
this class.

*/
//}}GW_CLASS	

	
	friend class CGWHierarchySheet;
public:
//Construction
//GW_MEMBERS{{(CGWImportExportObject,"Construction")
	CGWImportExportObject();
	CGWImportExportObject(CGWGrid* pGrid, BOOL bCallBackForData);			//Constructs a CGWImportExportObject object.
	CGWImportExportObject(CCellDataMap* pDataSource, int nSheetNdx);		//Constructs a CGWImportExportObject object.
	~CGWImportExportObject();
//}}GW_MEMBERS

//Attributes	
//GW_INTERNAL_MEMBERS{{(CGWImportExportObject,"Data Members")
	CString	m_csFilePath;				//Name and Path to file to either import or export.
	CCellDataMap* m_pExternalDataSource; //External data source to import/export from/to
	int		m_nExternalSheet;			//External Sheet Index to import/export from/to
	CCellDataMap* m_pTargetDataSource;	//Target data source
	int		m_nSheetNdx;				//Target sheet within target data source
	BOOL	m_bDelimited;				//Specifies whether data is delimited or fixed length.
	CString	m_csFieldDelimiter;			//Delimiter used between fields on same record.
	CString	m_csLineDelimiter;			//Delimiter used between lines.
	BOOL	m_bDataHasRowHeadings;		//Specifies whether the data contains row headings.
	BOOL	m_bDataHasColHeadings;		//Specifies whether the data contains columns headings.
	BOOL	m_bIncludeRowHeadings;		//Specifies whether to include row headings in import or export.
	BOOL	m_bIncludeColHeadings;		//Specifies whether to include column headings in import or export.
	long	m_nStartRowNdx;				//Row index at which to start import or export.
	long    m_nStartColNdx;				//Column index at which to start import or export,
	long	m_nEndRowNdx;				//Row index at which to end import or export.
	long    m_nEndColNdx;				//Column index at which to end import or export,
	BOOL    m_bOverlayExistingData;		//Specifies whether existing data will be overlayed.
	BOOL	m_bClearExistingData;		//Specifies whether existing data will cleared.
	CFile*  m_pExportFile;				//CFile used to export.
	CGWGrid*	m_pGrid;				//Grid pointer used for virtual grid importing and exporting.
	BOOL    m_bCallBackForData;			//Specifies whether to call CGWGrid virtual functions to get or set data.
	BOOL	m_bUseTempStorage;			//Specifies that an intermediate storage location will be used.
	CCellDataMap* m_pDataSource;		//Data Source used as an intermediate storage location for import.
//}}GW_MEMBERS

//Setup
//GW_MEMBERS{{(CGWImportExportObject,"Public Operations")
	void FilePath(LPCTSTR csFilePath)	//Set the file and path for either import or export.
	{
		m_csFilePath = csFilePath;
	}
	void Delimited(BOOL bDelimited)		//Does the file contain delimited data
	{
		m_bDelimited = bDelimited;
	}
	void FieldDelimiter(LPCTSTR& csFieldDelimiter)		//Character used to delimit fields.
	{
		m_csFieldDelimiter = csFieldDelimiter;
	}
	void LineDelimiter(LPCTSTR& csLineDelimiter)		//Character used to delimit lines.
	{
		m_csLineDelimiter = csLineDelimiter;
	}
	void DataHasRowHeadings(BOOL bDataHasRowHeadings)	//Raw data contains row headings
	{
		m_bDataHasRowHeadings = bDataHasRowHeadings;
	}
	void DataHasColHeadings(BOOL bDataHasColHeadings)   //Raw Data contains column headings
	{
		m_bDataHasColHeadings = bDataHasColHeadings;
	}
	void IncludeRowHeadings(BOOL bIncludeRowHeadings)   //Include row headings in operation
	{
		m_bIncludeRowHeadings = bIncludeRowHeadings;
	}
	void IncludeColHeadings(BOOL bIncludeColHeadings)   //Include column headings in operation
	{
		m_bIncludeColHeadings = bIncludeColHeadings;
	}
	void StartRowNdx(long nStartRowNdx)   //Row index at which to start import or export.
	{
		m_nStartRowNdx = nStartRowNdx;
	}
	void StartColNdx(long nStartColNdx)   //Row index at which to start import or export.
	{
		m_nStartColNdx = nStartColNdx;
	}
	void EndRowNdx(long nEndRowNdx)   //Row index at which to start import or export.
	{
		m_nEndRowNdx = nEndRowNdx;
	}
	void EndColNdx(long nEndColNdx)   //Row index at which to start import or export.
	{
		m_nEndColNdx = nEndColNdx;
	}
	void OverlayExistingData(BOOL bOverlayExistingData)   //Specifies whether existing data will be overlayed on import.
	{
		m_bOverlayExistingData = bOverlayExistingData;
	}
	void ClearExistingData(BOOL bClearExistingData)   //Specifies whether existing data will be overlayed on import.
	{
		m_bClearExistingData = bClearExistingData;
	}
	void ExternalDataSource(CCellDataMap* pExternalDataSource, int nExternalSheet)   //Specifies the external data source to be used as a source or target
	{
		m_pExternalDataSource = pExternalDataSource;
		m_nExternalSheet = nExternalSheet;
	}
	void UseTempStorage(BOOL bUseTempStorage)   //Row index at which to start import or export.
	{
		m_bUseTempStorage = bUseTempStorage;
	}
	virtual long ImportData();			//Import data according to the details contained in the objects data members.
	virtual long ExportData();			//Export data according to the details contained in the objects data members.
	virtual long ImportFromDataSource();	//Import data from a CCellDataMap object according to the details contained in the objects data members.
	virtual long ExportToDataSource();		//Export data to a CCellDataMap object according to the details contained in the objects data members.
//}}GW_MEMBERS


public:
//Operations
//GW_INTERNAL_MEMBERS{{(CGWImportExportObject,"Private Operations")
	virtual BOOL OpenForExport(CString csFileName);  //Open m_pExportFile for exporting data.
	virtual BOOL OpenForImport(CString csFileName);  //Open m_pExportFile for importing data.
	virtual void CloseExportFile();						//Close m_pExportFile;
	int GetImportedRows();								//Determine how many rows exist in imported data.
	int GetImportedColumns();							//Determine how many columns exist in imported data.
	void GetImportedField(int nRowNdx, int nColNdx, CString& csField);  //Get the value for a particular field from the imported data.
	virtual CCellDataMap* CreateDataSource()							//Create a temporary data source to contain the imported data.
												{return new CCellDataMap;}
	virtual int ParseRow(int nRowNdx, int nColNdx, CString csNewLine);  //Parse a delimited row of text from a import file.
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


#endif  //__CELLMAP_H__
