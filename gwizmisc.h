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
//gwizmisc.h     Header file for Gridwiz miscellaneous classes
#ifndef __GWIZMISC_H__
#define __GWIZMISC_H__ 

//#include <afxtempl.h>

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
//UINT HashKey(unsigned long lVal);

class GW_EXT_CLASS CGWMapIntToPtr : public CMapPtrToPtr
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWMapIntToPtr,"Construction")
	CGWMapIntToPtr()					//Default Constructor
		{};
	CGWMapIntToPtr(int nBlockSize)		//Construct a CGWMapIntToPtr with a specific block size.
		: CMapPtrToPtr(nBlockSize) {};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWMapIntToPtr,"Operations")
	BOOL Lookup(int key, void*& Value) const;							//Lookup ptr value with an int key.
    void SetAt(int key, void* newValue);								//Associate a ptr value with an int key.
    BOOL RemoveKey(int key);											//Remove a key/value pair.
    void GetNextAssoc(POSITION& pos, int& key, void*& nValue) const;	//Get the next key/value pair.
//}}GW_MEMBERS
};

class GW_EXT_CLASS CGWMapULongToPtr : public CMapPtrToPtr
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWMapULongToPtr,"Construction")
	CGWMapULongToPtr()								//Default Constructor
		{};
	CGWMapULongToPtr(int nBlockSize)				//Construct a CGWMapULongToPtr with a specific block size.
		: CMapPtrToPtr(nBlockSize) {};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWMapULongToPtr,"Operations")
	BOOL Lookup(unsigned long key, void*& Value) const;					//Lookup ptr value with an UINT key.
    void SetAt(unsigned long key, void* newValue);						//Associate a ptr value with an UINT key.
    BOOL RemoveKey(unsigned long key);									//Remove a key/value pair.
    void GetNextAssoc(POSITION& pos, unsigned long& key, void*& nValue) const;	//Get the next key/value pair.
//}}GW_MEMBERS
};

class GW_EXT_CLASS CGWMapIntToPos : public CMapPtrToPtr
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWMapIntToPos,"Construction")
	CGWMapIntToPos()								//Default Constructor
		{};
	CGWMapIntToPos(int nBlockSize)					//Construct a CGWMapIntToPos with a specific block size.
		: CMapPtrToPtr(nBlockSize) {};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWMapIntToPos,"Operations")
	BOOL Lookup(int key, POSITION& nValue) const;							//Lookup pos value with an UINT key.
    void SetAt(int key, POSITION newValue);									//Associate a pos value with an UINT key.
    BOOL RemoveKey(int key);												//Remove a key/value pair.
    void GetNextAssoc(POSITION& pos, int& key, POSITION& nValue) const;		//Get the next key/value pair.
//}}GW_MEMBERS
};


class CGWGrid;
class GW_EXT_CLASS CMatrix : public CObList
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
//GW_MEMBERS{{(CMatrix,"Construction")
	CMatrix();										//Default Constructor.
	CMatrix(int nBlockSize);						//Construct a CGWMapIntToPos with a specific block size.
	virtual ~CMatrix();								//Default Destructor.
//}}GW_MEMBERS

// Attributes
public:                        

//GW_MEMBERS{{(CMatrix,"Data Members")
	BOOL m_bLocked;									//Temporary variable which prevents changes to the GCO Cache.
	CGWGrid* m_pGrid;								//Pointer to the grid which is using this GCO Cache.
	UINT m_nVPageSize;								//The number of rows in this collection.
	UINT m_nHPageSize;								//The number of columns in this collection.
	UINT m_nVScrollPos;								//The vertical scroll position.
	UINT m_nHScrollPos;								//The horizontal scroll position.
	CPtrArray m_aRowHeadPosition;					//Array holding the positions of the first GCO in each row.
	CPtrArray m_aRowTailPosition;					//Array holding the positions of the last GCO in each row.
	int	m_nDockableRows;							//The number of docked rows in this collection.
	int	m_nDockableColumns;							//The number of docked columns in this collection.
	CGWMapULongToPtr m_mapDockedRowsNCols;			//A collection of GCOs which are located in the docked rows and columns.
//}}GW_MEMBERS

	
// Operations
public:
	static unsigned long GW_KEY(UINT nRowNdx, UINT nColNdx);

//GW_MEMBERS{{(CMatrix,"Operations")
	UINT AddRow(int nRowNdx);						//Add a new row of GCOs.
	UINT AddDockedRow();							//Add a new row of Docked GCOs.
	UINT AddCol(int nColNdx);						//Add a new column of GCOs.
	void Refresh();									//Destroy and rebuild all the GCOs in the cache.
	UINT InsertRow(UINT nRow);						//Insert a row of GCOs into the cache.
	UINT InsertCol(UINT nCol);						//Insert a column of GCOs into the cache.
	BOOL RemoveRow(UINT nRow);						//Remove a row of GCOs from the cache.
	BOOL RemoveCol(UINT nCol);						//Remove a column of GCOs from the cache.
	UINT InsertLine(UINT nRow);						//Insert a line of GCOs into the cache.
	void ClearAll();								//Clear the GCO cache without rebuilding.
	void ReplaceElement(UINT nRow, UINT nCol, CObject* pNewObject);	//Replace an individual GCO within the cache.
	CObject* GetElement(UINT nRow, UINT nCol);		//Retrieve a individual GCO from the cache. 
	POSITION GetRowHeadPosition(UINT nRow);			//Get the first GCO in a specific row.
//}}GW_MEMBERS

// Implementation
public:
//GW_MEMBERS{{(CMatrix,"Overrideables")
	virtual CObject* GetObject(int nRow, int nCol)=0;		//Create and initialize a new GCO.
	virtual CObject* GetDockableObject(int nRow, int nCol)	//Create and initialize a new Docked GCO.
		{return NULL;}
//}}GW_MEMBERS
};

class GW_EXT_CLASS CGWMapIntToInt : public CMapPtrToPtr
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWMapIntToInt,"Construction")
	CGWMapIntToInt()								//Default Constructor.
		{};
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWMapIntToInt,"Operations")
	void operator=(const CGWMapIntToInt& otherMap);					//Copy one CGWMapIntToInt object to another.
	BOOL Lookup(int key, int& nValue) const;						//Lookup a int value using an int key.
    void SetAt(int key, int newValue);								//Associate an int value with an int key.
    BOOL RemoveKey(int key);										//Remove an int key/value pair.
    void GetNextAssoc(POSITION& pos, int& key, int& nValue) const;	//Get the next int key/value pair.
	virtual void Serialize(CArchive& ar);							//Store and load a CGWMapIntToInt to and from a CArchive object.
//}}GW_MEMBERS
};

class GW_EXT_CLASS CGWOleSwitch
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWOleSwitch,"Overrideables")
	virtual void DestroyOleObjects()					//Destroy any cached ole data sources.
		{};
	virtual void RegisterDropTarget()					//Register a window as a drop target.
		{};
	virtual BOOL DoDragDrop(CPoint point)				//Initiate a drag and drop operation.
		{return FALSE;}
//}}GW_MEMBERS
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class CGCOCache : public CMatrix
// 
//


class CGWGrid;
class GW_EXT_CLASS CGCOCache : public CMatrix
{ 
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:	
//GW_MEMBERS{{(CGCOCache,"Construction")
	CGCOCache()									//Default Constructor.
		{m_pGrid = NULL;}
	CGCOCache(int nBlockSize)					//Construct a CGCOCache object with a specific block size.
		: CMatrix(nBlockSize) {m_pGrid = NULL;}
//}}GW_MEMBERS


//GW_MEMBERS{{(CGCOCache,"Data Members")
	CPtrArray m_arrayCellTops;					//Array containing the client coordinates of the tops of cells in the GCO Cache.
	CPtrArray m_arrayCellLefts;					//Array containing the client coordinates of the lefts of cells in the GCO Cache.
	CPtrArray m_arrayDockableCellTops;			//Array containing the client coordinates of the tops of docked cells in the GCO Cache.
	CPtrArray m_arrayDockableCellLefts;			//Array containing the client coordinates of the lefts of docked cells in the GCO Cache.
//}}GW_MEMBERS


//GW_MEMBERS{{(CGCOCache,"Operations")
	void ZapCell(int nRowNdx, int nColNdx);		//Force an individual cell to be destroyed and re-created.
//}}GW_MEMBERS


//GW_MEMBERS{{(CGCOCache,"Overrideables")
	virtual CObject* GetObject(int nRow, int nCol);			//Create and initialize a new GCO.
	virtual CObject* GetDockableObject(int nRow, int nCol);	//Create and initialize a new dockable GCO.
//}}GW_MEMBERS
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class CCellContext : public CObject
// 
// This class encapsulates the essence of a cell on the grid. Objects of 
// this type are created only when they are needed. There is not a 
// CCellContext for each cell in the grid. They are created when the user
// interacts with the grid and then are destroyed when the operation
// is completed. There is, however, an object of this type that is a 
// member of CGWGrid. This is because we will need to maintain a 
// CCellContent for the span of several message handlers. For example,
// OnLButtonDown too OnMouseMove too OnLButtonUp.
//
class CRecordset;
class CDBException;
class GW_EXT_CLASS CCellContext : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:

// Contructors
//GW_MEMBERS{{(CCellContext,"Construction")
	CCellContext();															//Default Constructor.
	CCellContext(UINT nType, int nRowNdx,int nColNdx, CRect& CellRect);		//Construct a CCellContext from it individual members.
//}}GW_MEMBERS

//GW_MEMBERS{{(CCellContext,"Operations")
	void operator=(const CCellContext& otherCCellContext);					//Copy one CCellContext object to another.
	void SetCC(UINT nType, int nRowNdx,int nColNdx, CRect&  CellRect);		//Sets the members of a CCellContext Object.
//}}GW_MEMBERS

//GW_MEMBERS{{(CCellContext,"Operations")
	UINT m_nType;           //The Cursor type associated with this Context.
	int m_nRowNdx;			//The row index into the document data strucuture.
	int m_nColNdx;			//The column index into the docs data structure.
	CRect m_CellRect;       //The CRect for the cell in logical points.
//}}GW_MEMBERS
};
#ifdef __AFXDB_H__
/////////////////////////////////////////////////////////////////////////////
// CDBExceptionDlg dialog

class GW_EXT_CLASS CDBExceptionDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
//GW_MEMBERS{{(CDBExceptionDlg,"Construction")
	CDBExceptionDlg(CDBException* pDBExcp, CWnd* pParent = NULL);	// Constructs CDBExceptionDlg object.
//}}GW_MEMBERS

// Dialog Data
	enum { IDD = IDD_GW_DBEXCEPTION };

//GW_MEMBERS{{(CDBExceptionDlg,"Data Members")
	CString	m_csNativeOrigin;			//Native Origin member of the CDBException structure.
	CString	m_csError;					//Native Error string member of the CDBException structure.
	CString	m_csReturnCode;				//Native Return Code member of the CDBException structure.
	CDBException* m_pDBExcp;			//Address of the CDBException object.
//}}GW_MEMBERS

// Implementation
protected:
//GW_MEMBERS{{(CDBExceptionDlg,"Implementation")
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void OnPrintError();								//Allow for printing the dialog.
//}}GW_MEMBERS

	DECLARE_MESSAGE_MAP()
};               
#endif //__AFXDB_H__


/////////////////////////////////////////////////////////////////////////////
// CGWTabStop Class;

class GW_EXT_CLASS CGWTabStop : public CObject
{              
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWTabStop,"Construction")
	CGWTabStop()									//Default Constructor
		{};
	CGWTabStop( const CGWTabStop &other );          //Copy Constructor
 	CGWTabStop(int nColNdx, int nCellItem = 1);		//Overloaded Constructor
//}}GW_MEMBERS
	
//GW_MEMBERS{{(CGWTabStop,"Data Members")
 	UINT m_nColNdx;									//The column index of the cell containing this CGWTabStop object.
 	UINT m_nCellItem;								//The tab stop within the cell containing this CGWTabStop object.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWTabStop,"Operations")
 	virtual BOOL IsEqual(CGWTabStop* tabStop);		//Compare two CGWTabStop objects.
 	void operator=(const CGWTabStop& tabStop);		//Copy one CGWTabStop to another.
 	BOOL operator==(const CGWTabStop tabStop);		//Compare two CGWTabStop objects.
//}}GW_MEMBERS
};

/////////////////////////////////////////////////////////////////////////////
// CTab command target

class GW_EXT_CLASS CGWTab : public CObject
{   
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWTab,"Construction")
	CGWTab();							//Default Constructor.
	virtual ~CGWTab();					//Default Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWTab,"Data Members")
    CObArray 	m_arrayTabStops;		//Array of tab stops
    CUIntArray  m_arrayTabOrder;		//Order of tab stops
    CGWGrid* 		m_pGrid;			//Grid to which tab stops apply.
//}}GW_MEMBERS

// Operations
public:                         
//GW_MEMBERS{{(CGWTab,"Operations")
	UINT AddTabStop(CGWTabStop* pTabStop);						//Add a tabstop object to the collection.
	UINT ChangeTabStop(UINT nNewOrdinal, CGWTabStop& TabStop);	//Change an existing tab stop.
	UINT RemoveTabStop(UINT nOrdinal);							//Remove a tabstop object from the collection.
	void ClearTabStops();										//Remove all tabstops from the collection.
 	CGWTabStop* GetTabStop(UINT nOrdinal);						//Get a specific tabstop.
	UINT GetTabStopOrdinal(CGWTabStop& TabStop);				//Get an ordinal from a tabstop.
	UINT GetNextTabStopOrdinal(UINT nOrdinal);					//Get the next tabstop based on ordinal.
	CGWTabStop* GetNextTabStop(CGWTabStop& TabStop);			//Get the next tabstop based on tabstop address.
	UINT GetPrevTabStopOrdinal(UINT nOrdinal);					//Get the previous tabstop based on ordinal.
	CGWTabStop* GetPrevTabStop(CGWTabStop& TabStop);			//Get the previous tabstop based on tabstop address.
	UINT GetMaxTabOrdinal()										//Get the maximum tabstop ordinal.
		{
			return (UINT)m_arrayTabOrder.GetSize(); 
		} 
	int FindTabStop(CGWTabStop& TabStop);						//Find a tabstop based on its ordinal.
	UINT FindTabStopOrdinal(UINT nTabStopNdx);					//Find a tabstop ordinal based on its address.
//}}GW_MEMBERS

	
//Overrideables
//GW_MEMBERS{{(CGWTab,"Overrideable")
	virtual void RegisterTabStops()								//Registers tabstops with the grid.
		{};
//}}GW_MEMBERS

};


#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS


#endif  //__GWIZMISC_H__
