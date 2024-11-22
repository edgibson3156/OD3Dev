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
// gwrowset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGWRowset class definition

#ifndef __GWROWSET_H__
#define __GWROWSET_H__

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


#include <msdatsrc.h>	// IDataSource and IDataSourceListener
//#include "acw\adbctl.h"
//#include "acw\util.h"
//#include "tchar.h"
#include <oledberr.h>
//IMalloc Wrappers
#define SAFE_ALLOC(pv, type, cb)		{ pv = (type*)CoTaskMemAlloc((cb)*sizeof(type)); CHECK_MEMORY(pv);			}
#define SAFE_REALLOC(pv, type, cb)		{ pv = (type*)CoTaskMemRealloc(pv, (cb)*sizeof(type)); CHECK_MEMORY(pv);	}
#define SAFE_SYSALLOC(pv, bstr)			{ pv = SysAllocString(bstr); CHECK_MEMORY(pv);												}		

#define SAFE_FREE(pv)					{ CoTaskMemFree(pv); pv = NULL;						}
#define SAFE_SYSFREE(bstr)				{ SysFreeString(bstr); bstr = NULL;					}
#define CHECK_MEMORY(pv)				if(!pv) { AfxMessageBox(_T("Out of memory")); goto CLEANUP; }
#define MAX_COL_SIZE		    5000


///////////////////////////////////////////////////////////////////
// Accessor / Binding 
//
///////////////////////////////////////////////////////////////////
//STATUS helpers, for locating obStatus offsets in the bindings
#define STATUS_IS_BOUND(Binding)    ( (Binding).dwPart & DBPART_STATUS )
#define BINDING_STATUS(Binding, pv) (*(ULONG*)((BYTE*)(pv) + (Binding).obStatus))

//LENGTH helpers, for locating obLength offsets in the bindings
#define LENGTH_IS_BOUND(Binding)    ( (Binding).dwPart & DBPART_LENGTH )
#define BINDING_LENGTH(Binding, pv) (*(ULONG*)((BYTE*)(pv) + (Binding).obLength))

//VALUE helpers, for locating obValue offsets in the bindings
#define VALUE_IS_BOUND(Binding)     ( (Binding).dwPart & DBPART_VALUE )
#define BINDING_VALUE(Binding, pv)  (*(ULONG*)((BYTE*)(pv) + (Binding).obValue ))
//ROUNDUP on all platforms pointers must be aligned properly
#define ROUNDUP_AMOUNT	8
#define ROUNDUP_(size,amount)		(((ULONG)(size)+((amount)-1))&~((amount)-1))
#define ROUNDUP(size)				ROUNDUP_(size, ROUNDUP_AMOUNT)
//Error Checking
#define TESTC(hr)						{ if(FAILED(hr)) goto CLEANUP;				}
#define TESTC_(hr, hrExpected)			{ if((hr) != (hrExpected)) goto CLEANUP;	}
#define IS_SAME_GUIDS(riid1, riid2) (((riid1).Data1 == (riid2).Data1) && ((riid1) == (riid2)))
//Helper macros
#ifndef RETURN_ON_FAILURE
#define RETURN_ON_FAILURE(hr) if (FAILED(hr)) return hr
#endif
#ifndef RETURN_ON_NULLALLOC
#define RETURN_ON_NULLALLOC(ptr) if (!(ptr)) return E_OUTOFMEMORY
#endif
#ifndef RELEASE_OBJECT
#define RELEASE_OBJECT(ptr)    if (ptr) { IUnknown *pUnk = (ptr); (ptr) = NULL; pUnk->Release(); }
#endif
#ifndef QUICK_RELEASE
#define QUICK_RELEASE(ptr)     if (ptr) ((IUnknown *)ptr)->Release();
#endif
#ifndef ADDREF_OBJECT
#define ADDREF_OBJECT(ptr)     if (ptr) (ptr)->AddRef()
#endif
#ifndef CHECK_POINTER
#define CHECK_POINTER(val) if (!(val) || IsBadReadPtr((void *)(val), sizeof(void *))) return E_POINTER
#endif
#ifndef CHECK_POINTER_SIZE
#define CHECK_POINTER_SIZE(val,sz) if (!(val) || IsBadReadPtr((void *)(val), sz)) return E_POINTER
#endif
#define SAFE_RELEASE(pv)				if(pv) { (pv)->Release(); (pv) = NULL;				}  

/////////////////////////////////////////////////////////////////////////////
// Data Types
//

// Columns structure extending DBCOLUMNINFO
// to contain addtional metadata
//
struct COLUMNINFO : public DBCOLUMNINFO
{
public:
	COLUMNINFO();
	~COLUMNINFO();

	void Clear(BOOL fZeroMemory = TRUE);

// Additional metadata
public:
	VARIANT	varDefault;		// Default value for a column

// Operators
public:
	COLUMNINFO& operator=(const COLUMNINFO& other);
	COLUMNINFO& operator=(const DBCOLUMNINFO& other);
};

// This structure contains the most pertinent
// properties for a Rowset that a consumer 
// may be interested in
//
struct ROWSETPROPERTIES
{
	// Value properties
	//
	struct
	{
		long	MaxOpenRows;	// Maximum rows consumers are allowed to hold
		long	Updatability;	// IRowsetChange methods supported
	}	value;

	// Boolean properties
	//
	struct
	{
		UINT	StrongId		:1;	// Newly inserted HROWs can be compared
		UINT	LiteralId		:1;	// HROWs can be literally compared
		UINT	HasBookmarks	:1;	// Rows have self-bookmark columns
									//	IRowsetLocate is implemented
		UINT	CanHoldRows		:1;	// HROWs can be held inbetween GetRows
		UINT	CanScrollBack	:1;	// GetRows can scroll backwards
									//	IRowsetScroll is implemented
		UINT	CanFetchBack	:1;	// GetRows can fetch backwards
		UINT	CanChange		:1;	// IRowsetChange is implemented
		UINT	CanUpdate		:1;	// IRowsetUpdate is implemented

		UINT	IRowsetScroll	:1;		// IRowsetScroll is implemented
	}	flag;
};




enum CONV_FLAGS
{
	CONV_NONE			= 0x00000000,
	CONV_VARBOOL		= 0x00000001,
	CONV_ALPHABOOL		= 0x00000002,
	CONV_HEX			= 0x00000004,
	CONV_OCTAL			= 0x00000008,
	CONV_DECIMAL		= 0x00000010,
	CONV_BINARY			= 0x00000020,
};
#define EOL		 '\0'
#define wEOL	L'\0'


// Cursor standard bookmarks
// not to be used with OLE DB
//
#define BMK_SIZE        sizeof(BYTE)
extern const BYTE BMK_INVALID;
extern const BYTE BMK_CURRENT;
extern const BYTE BMK_BEGINNING;
extern const BYTE BMK_END;

// OLE DB standard bookmarks
// not to be used with Cursors
//
extern const BYTE DBBMK_FIRSTROW;
extern const BYTE DBBMK_LASTROW;


#define UNUSED_OFFSET	((ULONG)-1L)
// Intializes a DBBINDING structure for accessing rows
//
void InitBinding(DBBINDING& dbBinding, ULONG iOrdinal, 
 DBTYPE wType, ULONG cbMaxLen, ULONG obValue, 
 ULONG obLength = UNUSED_OFFSET, ULONG obStatus = UNUSED_OFFSET, 
 BYTE bPercision = 0, BYTE bScale = 0);



HRESULT DisplayErrorRecords();
HRESULT GetErrorRecords(ULONG* pcRecords, IErrorRecords** ppIErrorRecords);
HRESULT GetSqlErrorInfo(ULONG iRecord, IErrorRecords* pIErrorRecords, BSTR* pBstr, LONG* plNativeError);


// This macros generates a temporary ANSI multibyte string
// from a WIDE string
//
#define MAKE_MULTIBYTESTRING(name,arg) \
	MULTIBYTESTRING _Temp_Obj_##name(arg); \
	const char* name = _Temp_Obj_##name

void ClearID(DBID& dbid);
void CopyID(DBID& dbidDst, const DBID& dbidSrc);


// String APIs
//
int lstrncmp(const char *sz1, const char *sz2, int cChars);
int lstrncmpi(const char *sz1, const char *sz2, int cChars);

int bstrlen(const BSTR bstr);
int bstrcmp(const BSTR bstr1, const BSTR bstr2);
int bstrncmp(const BSTR bstr1, const BSTR bstr2, int cChars);
int bstrcmpi(const BSTR bstr1, const BSTR bstr2);
int bstrncmpi(const BSTR bstr1, const BSTR bstr2, int cChars);

BSTR bstrcpy(BSTR& bstrDst, const BSTR bstrSrc);
BSTR bstrncpy(BSTR& bstrDst, const BSTR bstrSrc, int cChars);

int wstrlen(const WCHAR *wsz);
int wstrcmp(const WCHAR *wsz1, const WCHAR *wsz2);
int wstrncmp(const WCHAR *wsz1, const WCHAR *wsz2, int cChars);
int wstrcmpi(const WCHAR *wsz1, const WCHAR *wsz2);
int wstrncmpi(const WCHAR *wsz1, const WCHAR *wsz2, int cChars);

WCHAR *wstrcpy(WCHAR *wszDst, const WCHAR *wszSrc);
WCHAR *wstrncpy(WCHAR *wszDst, const WCHAR *wszSrc, int cChars);

char *stralloc(const char *sz);
char *stralloc(const BSTR bstr);
char *stralloc(const WCHAR *wsz);
WCHAR *wstralloc(const WCHAR *wsz);
WCHAR *wstralloc(const BSTR bstr);
WCHAR *wstralloc(const WCHAR *wsz);
BSTR bstralloc(const BSTR bstr);
BSTR bstralloc(const char *sz);
BSTR bstralloc(const WCHAR *wsz);

int LoadWideString(HINSTANCE hInstance, UINT uID, WCHAR *pwcBuf, int cbBufMax);

/////////////////////////////////////////////////////////////////////////////
// MULTIBYTESTRING
//
struct MULTIBYTESTRING
{
	MULTIBYTESTRING(const BSTR bstr);
	MULTIBYTESTRING(const WCHAR *wsz);
	~MULTIBYTESTRING();

	char *sz;

	operator const char*() {return (const char*)sz;}
};

/////////////////////////////////////////////////////////////////
// CGWListener 
//
/////////////////////////////////////////////////////////////////
class CGWListener : public IUnknown
{
public:
	CGWListener(REFIID riid);
	virtual ~CGWListener();
	
	virtual HRESULT Advise(IConnectionPoint* pIConnectionPoint);
	virtual HRESULT Unadvise(IConnectionPoint* pIConnectionPoint);

	virtual HRESULT Advise(IUnknown* pIUnknown);
	virtual HRESULT Unadvise(IUnknown* pIUnknown);

	virtual HRESULT SetReturnValue(HRESULT hrReturn);
	virtual HRESULT GetReturnValue();

	STDMETHODIMP_(ULONG)	AddRef(void);
	STDMETHODIMP_(ULONG)	Release(void);
	STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);

protected:
	//Data
	DWORD		m_dwCookie;		// The cookie that UnAdvise needs
	ULONG		m_cRef;			// reference count
	HRESULT		m_hrReturn;
	REFIID		m_riid;
};


/////////////////////////////////////////////////////////////////
// CGWRowsetNotify 
//
/////////////////////////////////////////////////////////////////
class CGWRowsetNotify : public IRowsetNotify, public CGWListener
{
public:
	CGWRowsetNotify(CGWDatabaseRequest* pDBRQ, CGWGrid* pGrid, int nSheetNdx);
	virtual ~CGWRowsetNotify();
	
	STDMETHODIMP_(ULONG)	AddRef(void);
	STDMETHODIMP_(ULONG)	Release(void);
	STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
	
    virtual HRESULT STDMETHODCALLTYPE OnFieldChange( 
            /* [in] */ IRowset __RPC_FAR *pIRowset,
            /* [in] */ HROW hRow,
            /* [in] */ ULONG cColumns,
            /* [size_is][in] */ ULONG __RPC_FAR rgColumns[  ],
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny);
        
    virtual HRESULT STDMETHODCALLTYPE OnRowChange( 
            /* [in] */ IRowset __RPC_FAR *pIRowset,
            /* [in] */ ULONG cRows,
            /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny);
        
   virtual HRESULT STDMETHODCALLTYPE OnRowsetChange( 
            /* [in] */ IRowset __RPC_FAR *pIRowset,
            /* [in] */ DBREASON eReason,
            /* [in] */ DBEVENTPHASE ePhase,
            /* [in] */ BOOL fCantDeny);

protected:
	//Data
	CGWGrid*	m_pGrid;
	int			m_nSheetNdx;
	CGWDatabaseRequest* m_pDBRQ;
};

/////////////////////////////////////////////////////////////////
// CGWRowsetNotify 
//
/////////////////////////////////////////////////////////////////
class CGWRowPositionChange : public IRowPositionChange, public CGWListener
{
public:
	CGWRowPositionChange(CGWDatabaseRequest* pDBRQ, CGWGrid* pGrid, int nSheetNdx);
	virtual ~CGWRowPositionChange();
	
	STDMETHODIMP_(ULONG)	AddRef(void);
	STDMETHODIMP_(ULONG)	Release(void);
	STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
	
	STDMETHOD(OnRowPositionChange)(DBREASON eReason, DBEVENTPHASE ePhase, BOOL fCantDeny);

protected:
	//Data
	CGWGrid*	m_pGrid;
	int			m_nSheetNdx;
	CGWDatabaseRequest* m_pDBRQ;

};

/////////////////////////////////////////////////////////////////
// CGWRowsetNotify 
//
/////////////////////////////////////////////////////////////////
class CGWDataSourceListener : public IDataSourceListener
{
public:
	CGWDataSourceListener(CGWGrid* pGrid);
	virtual ~CGWDataSourceListener();
	
	STDMETHODIMP_(ULONG)	AddRef(void);
	STDMETHODIMP_(ULONG)	Release(void);
	STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
	
	STDMETHOD(dataMemberChanged)(THIS_ DataMember bstrDM);
	STDMETHOD(dataMemberAdded)(THIS_ DataMember bstrDM);
	STDMETHOD(dataMemberRemoved)(THIS_ DataMember bstrDM);

protected:
	//Data
	CGWGrid*	m_pGrid;
	ULONG		m_cRef;			// reference count
};


/////////////////////////////////////////////////////////////////////////////
// CGWBookmark
//
class CGWBookmark : public BLOB
{
public:
	CGWBookmark();
	CGWBookmark(const CGWBookmark& other);
	CGWBookmark(ULONG ulSize, const BYTE *pBlob);
	CGWBookmark(const BLOB& blob);
	~CGWBookmark();

public:
	BOOL IsInvalid(void) const {return 0 == cbSize || (BMK_SIZE == cbSize && BMK_INVALID == BmkByte());}
	
	// For OLE DB
	//
	BOOL IsFirstRow(void) const {return BMK_SIZE == cbSize && DBBMK_FIRSTROW == BmkByte();}
	BOOL IsLastRow(void) const {return BMK_SIZE == cbSize && DBBMK_LASTROW == BmkByte();}

	void Clear(void);
	HRESULT Set(ULONG ulSize, const BYTE *pBlob);
	HRESULT Set(const VARIANT& var);
	HRESULT Get(VARIANT& var) const;

public:
	operator BLOB&() {return *((BLOB *)this);}
	operator const BLOB&() const {return *((BLOB *)this);}
	operator ULONG() const {return cbSize;}
	operator void*() {return (cbSize > sizeof pBlobData) ? pBlobData : (void*)&pBlobData;}
	operator const void*() const {return (cbSize > sizeof pBlobData) ? pBlobData : (void*)&pBlobData;}
	operator const BYTE*() const {return (const BYTE*)(const void*)*this;}
	operator BYTE*() {return (BYTE*)(void*)*this;}

	BOOL operator==(const CGWBookmark& other) const;
	BOOL operator==(const VARIANT& var) const;
	CGWBookmark& operator=(const CGWBookmark& other);

	static BOOL IsBookmark(const VARIANT& var) {return (VT_ARRAY|VT_UI1|VT_R8) == V_VT(&var) && 1 == SafeArrayGetDim(V_ARRAY(&var));}

protected:
	BYTE BmkByte(void) const {return *((BYTE *)&pBlobData);}
	ULONG BmkULong(void) const {return *((ULONG *)&pBlobData);}
};





class GW_EXT_CLASS CGWRowset
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWRowset, "Construction")
	CGWRowset();					//Constructs and initializes an CGWRowset object.
	CGWRowset(CGWGrid* pGrid, IDataSource* pDataSource, LPCTSTR lpszDataMember);	//Constructs and initializes an CGWRowset object.
	CGWRowset(CGWGrid* pGrid, IRowset* pRowset);									//Constructs and initializes an CGWRowset object.
	~CGWRowset();					//Destructs and frees an CGWRowset object.
//}}GW_MEMBERS	

public:	 
//GW_MEMBERS{{(CGWRowset, "Cached interface pointers")
	IRowset*					m_pRowset;				// Address of the IRowset interface used to extract the data.
	IRowPosition*				m_pRowPosition;			// Address of the IRowPosition interface used to drive this object.
	IRowsetLocate*				m_pRowsetLocate;
	IRowsetScroll*				m_pRowsetScroll;
	IRowsetFind*				m_pRowsetFind;
	IRowsetInfo*				m_pRowsetInfo;
	IRowsetIdentity*			m_pRowsetIdentity;
	IRowsetChange*				m_pRowsetChange;
	IRowsetUpdate*				m_pRowsetUpdate;
	IAccessor*					m_pAccessor;
	IConvertType*				m_pConvertType;
	IColumnsInfo*				m_pColumnsInfo;
	IDataSource*				m_pDataSource;			// Address of the IDataSource interface used to drive this object.
	IConnectionPointContainer*	m_pIConnectionPointContainer;
	IConnectionPoint*			m_pIConnectionPoint;
	IUnknown*					m_pIUnknown;
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWRowset, "Data Members")
	CString				m_csDataMember;			// String containing connection information for this object.
	COLUMNINFO*			m_pColumns;				// COLUMNINFO array.
	ULONG				m_nColumns;				// Number of elements in m_pColumns.
	HACCESSOR			m_hRowAccessor;			// Accessor for the rows to be retrieved through the IRowset interface.
	DBBINDING*			m_pBindings;			// Array of DBBINDING structures used to create the Accessor.
	void*				m_pData;				// Buffer used to hold row data.
	CGWBookmark			m_CurrentBmk;			// Bookmark of current row.
	CGWRowsetNotify*	m_pGWRowsetNotify;
	CGWRowPositionChange*	m_pGWRowPositionChange;
	CGWGrid*			m_pGrid;
	HROW				m_hRow;					// The HROW of the row to update.
	ROWSETPROPERTIES	m_properties;
	BSTR				m_bstrDM;
	CUIntArray			m_DirtyFields;			//	Keep track of dirty fields.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWRowset, "Operations")
	HRESULT Bind();								// Attaches to the Rowset.
	HRESULT InitRowPosition(void);				// This method is called to initialize the member variable m_pRowPosition.
	HRESULT InitRowset(void);					// This method is called to initialize the class member variable m_pRowset.
	HRESULT AttachRowset(IUnknown *pUnk);		// This function attempts to attach this object to the IRowset interface.
	HRESULT InitColumns(void);					// This function frees any columns and attempts to retrieve column information through IRowset interface.
	HRESULT DeleteColumns(void);				// This function frees any columns information.
	HRESULT InitRowAccessor();					// This function attempts to create an Accessor using the binding information obtained from the columns.
	HRESULT FreeRowAccessor();					// This function frees the accessor.
	CString GetDataMember()						// This function returns the data member attribute in a CString.
	{
		return m_csDataMember;
	}
	HRESULT SetupBindings(ULONG* pcBindings, DBBINDING** prgBindings, ULONG* pcRowSize, BOOL* pbOutofLine);
	virtual HRESULT SetColumnData(DBBINDING* pBinding, void* pData, DBSTATUS dwStatus, CHAR* pszValue);
	HRESULT GetColumnData(DBBINDING* pBinding, void* pData, DBSTATUS* pdwStatus, ULONG* pdwLength, DBTYPE* pwSubType, CHAR* pszValue, ULONG ulMaxSize, DWORD dwFlags, DBTYPE wBaseType);
	HRESULT VariantToString(VARIANT* pVariant, CHAR* psz, ULONG ulMaxSize, DWORD dwFlags);
	HRESULT ConvertToMBCS(WCHAR* pwsz, CHAR* psz, ULONG cbStrLen);
	BOOL FreeBindings(ULONG* pcBindings, DBBINDING** prgBindings);
	BOOL FreeBindingData(ULONG cBindings, DBBINDING* rgBindings, void* pData);
	HRESULT InitVariants(ULONG cVariants, VARIANT* rgVariants);
	HRESULT FreeVariants(ULONG cVariants, VARIANT* rgVariants);
	HRESULT ConvertToWCHAR(CHAR* psz, WCHAR* pwsz, ULONG cbStrLen);
	virtual HRESULT AdviseListeners();
	virtual HRESULT UnadviseListeners();
	virtual HRESULT Attach(IUnknown *punk, LPCTSTR lpszDataMember = NULL);		// Attach to a DataSource or an IRowset or IRowPosition
	HRESULT CreateAccessor(const DBBINDING *pBindings, ULONG cBindings, HACCESSOR& haccessor, DBBINDSTATUS *pStatus = NULL);
	HRESULT ReleaseAccessor(HACCESSOR haccessor);
	HRESULT GetColumns(COLUMNINFO*& pCols, ULONG& cCols);
	HRESULT GetCurrentRow(HROW& hrow, DBPOSITIONFLAGS *pdwPositionFlags = NULL);
	HRESULT RestartPosition(void);
	HRESULT GetNextRows(long lOffset, long cRowsRequested, HROW*& phRows, ULONG& cRows);
	HRESULT FreeRows(const HROW *pRows, ULONG cRows);
	HRESULT ReleaseRows(const HROW *pRows, ULONG cRows);
	HRESULT AddRefRows(const HROW *pRows, ULONG cRows);
	HRESULT GetData(HROW hrow, HACCESSOR haccessor, void *pBuffer);
	HRESULT SetData(HROW hrow, HACCESSOR haccessor, void *pBuffer);
	HRESULT DeleteRows(const HROW *phRows, ULONG cRows, DBROWSTATUS *pRowsStatus);
	HRESULT InsertRow(HACCESSOR haccessor, void *pData, HROW& hrow);
	HRESULT GetOriginalData(HROW hrow, HACCESSOR haccessor, void *pData);
	HRESULT GetPendingRows(DBPENDINGSTATUS dwStatus, HROW*& phRows, ULONG& cRows, DBPENDINGSTATUS **ppStatus);
	HRESULT GetRowStatus(const HROW *phRows, ULONG cRows, DBPENDINGSTATUS *pStatus);
	HRESULT Undo(const HROW *phRows, ULONG cRows, ULONG *pcRows, HROW **pphRows, DBROWSTATUS **ppStatus);
	HRESULT Update(const HROW *phRows, ULONG cRows, ULONG *pcRows, HROW **pphRows, DBROWSTATUS **ppStatus);
	HRESULT GetSelfBookmark(HROW hrow, CGWBookmark& bmk);
	HRESULT GetRows(const CGWBookmark& bmk, long lOffset, long cRowsRequested, HROW*& phRows, ULONG& cRows);
	HRESULT GetRows(const CGWBookmark *pBookmarks, ULONG cBookmarks, HROW* phRows, DBROWSTATUS *pRowStatus = NULL);
	IRowset* GetRowset(void);
	IAccessor* GetAccessor(void);
	IRowPosition* GetRowPosition(void);
	IDataSource* GetDataSource(void);
	virtual const ROWSETPROPERTIES& GetProperties(void);
	HRESULT GetRowsetProperties(IUnknown *pRowset, const DBPROPID *pPropIDs, VARIANT *pValues, ULONG cPropIDs);
	HRESULT InitRowsetLocate(void);
	HRESULT InitRowsetScroll(void);
	HRESULT InitRowsetFind(void);
	HRESULT InitRowsetInfo(void);
	HRESULT InitRowsetIdentity(void);
	HRESULT InitRowsetChange(void);
	HRESULT InitRowsetUpdate(void);
	HRESULT InitAccessor(void);
	HRESULT InitConvertType(void);
	HRESULT InitColumnsInfo(void);
	HRESULT InitColumnsMetadata(COLUMNINFO*& pColumns, ULONG cColumns);
	HRESULT GetColumnOrdinals(ULONG *pOrdinals, const DBID* pdbColIDs, ULONG cColIDs);
//}}GW_MEMBERS	


	HRESULT DisplayErrorRecords();
	BOOL FieldDirty(UINT nField);
	void ClearDirtyFields() 
	{	m_DirtyFields.RemoveAll(); }
	void MarkFieldDirty(UINT nField)
	{	
		//nField is 0 based. If the first column is a bookmark, add 1.
		if (m_properties.flag.HasBookmarks)
			nField++;
		m_DirtyFields.Add(nField);	
	}


//GW_MEMBERS{{(CGWRowset, "Data Access Operations")
	int SetAbsolutePosition(int nRowNdx);
    HRESULT GetFieldText (CGWBookmark& bmk, long nField, CString& csFieldText);
    HRESULT SetFieldText (long nRow, long nField, CHAR* pszValue, BOOL* pbSucceeded);
    HRESULT GetFieldName (long nField, BSTR*  csFieldName);
    HRESULT GetFieldSize (long nField, long*  lFieldSize);
    HRESULT GetFieldType (long nField, short* pType);
    HRESULT GetFieldRequired (long nField, BOOL* pbRequired);
    HRESULT GetFieldAllowZeroLengthString (long nField, BOOL* pbAllowZeroLengthString);
    HRESULT GetFieldDefaultText (long nField, BSTR* pbstrDefaultText);
    HRESULT Edit();
    HRESULT Add();
    HRESULT Delete();
    HRESULT Update(BOOL* pbSucceeded);
    HRESULT IsEOF(BOOL* pbIsEOF);
    HRESULT IsBOF(BOOL* pbIsBOF);
    HRESULT MoveNext(long* plCurrentRow);
    HRESULT MoveFirst();
    HRESULT MoveLast(long* plCurrentRow);
    HRESULT MovePrev(long* plCurrentRow);
    HRESULT Move(long lMoveRows, long * plCurrentRow );
    HRESULT PositionAbsolute(long nRow, long * plCurrentRow);
    HRESULT IsOpen(BOOL* pbIsOpen);
    HRESULT IsReadOnly(BOOL* pbIsReadOnly);
    HRESULT GetFieldCount(long * plFieldCount);
    HRESULT CanBookMark (BOOL* pbCanBookMark);
    HRESULT GetBookMark(VARIANT * lpvBookMark);
    HRESULT SetBookMark(CGWBookmark* lpvBookMark);
//}}GW_MEMBERS	


};



#endif
