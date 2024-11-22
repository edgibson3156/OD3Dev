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
//GRIDDLGS.h     

#ifndef __GRIDDLGS_H__
#define __GRIDDLGS_H__ 


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

/////////////////////////////////////////////////////////////////////////////
// CGWBorderStatic 

class GW_EXT_CLASS CGWBorderStatic : public CStatic
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
	CGWBorderStatic() {};
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBorderStyleDlg dialog

class GW_EXT_CLASS CBorderStyleDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CBorderStyleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBorderStyleDlg)
	enum { IDD = IDD_GW_BORDER_STYLE };
	CGWBorderStatic m_BorderOutline;
	CGWBorderStatic m_BorderLeft;
	CGWBorderStatic m_BorderRight;
	CGWBorderStatic m_BorderTop;
	CGWBorderStatic m_BorderBottom;

	CGWBorderStatic m_BorderNone;
	CGWBorderStatic m_BorderDot;
	CGWBorderStatic m_BorderDash;
	CGWBorderStatic m_BorderSingle;
	CGWBorderStatic m_BorderDouble;
	CGWBorderStatic m_BorderTriple;
	CGWBorderStatic m_BorderDoubleLine;
	
	//}}AFX_DATA
	int	m_nBorderIdNdx;
	int m_nBorderStyleNdx;


	CRect m_rectBorder;
	COLORREF m_rgbBorderColor;
	CBrush m_brushBorderColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorderStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
// Implementation
	void OnSelchangeBorderId();
	void OnSelchangeBorderStyles();
protected:

	// Generated message map functions
	//{{AFX_MSG(CBorderStyleDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnColorDlg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class GW_EXT_CLASS CFillPatternDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CFillPatternDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFillPatternDlg)
	enum { IDD = IDD_GW_FILL_PATTERN };
	//}}AFX_DATA

	UINT     m_nPatternID;
	COLORREF m_rgbForecolor;
	COLORREF m_rgbBackcolor;
	CBrush m_brushPattern;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFillPatternDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    virtual void OnOK();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFillPatternDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnColorDlg();
	afx_msg void OnSelChangePatternID();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class GW_EXT_CLASS CNumberFormatDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CNumberFormatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNumberFormatDlg)
	enum { IDD = IDD_GW_TEXT_FORMAT };
	//}}AFX_DATA

	CString m_csFormatString;


	CStringArray m_csaNumericStrings;
	CStringArray m_csaCurrencyStrings;
	CStringArray m_csaPercentStrings;
	CStringArray m_csaDateStrings;
	CStringArray m_csaTimeStrings;
	CStringArray m_csaMiscStrings;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberFormatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    virtual void OnOK();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNumberFormatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFormatStrings();
	afx_msg void OnSelchangeCategory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class GW_EXT_CLASS CTextAlignmentDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CTextAlignmentDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextAlignmentDlg)
	enum { IDD = IDD_GW_TEXT_ALIGNMENT };
	CListBox m_lbHorizontal;
	CListBox m_lbVertical;
	//}}AFX_DATA
	UINT m_nHorzAlign;
	UINT m_nVertAlign;
	BOOL m_bWordWrap;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextAlignmentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextAlignmentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeVert();
	afx_msg void OnSelchangeHorz();
	afx_msg void OnClickWordWrap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// settings.h : interface of the CValidStringGrid class

class GW_EXT_CLASS CValidStringGrid : public CGWGridCtrl
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public: 
	CValidStringGrid();
	DECLARE_DYNCREATE(CValidStringGrid)
	DECLARE_GRIDCELL_MAP(CValidStringGrid)

// Attributes
public:

// Operations
public:
	void Initialize();
// Implementation
public:
	virtual ~CValidStringGrid();

protected:


// Generated message map functions
protected:
	//{{AFX_MSG(CValidStringGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


//BEGIN_VIRTUAL_FUNCTIONS(CValidStringGrid)
	virtual void GridOnInitialUpdate();
	virtual void OnGetFixedCellText(int nRowNdx, int nColNdx, CString& csCellText);
//END_VIRTUAL_FUNCTIONS
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CValidStringsDlg dialog
class GW_EXT_CLASS CValidStringsDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CValidStringsDlg(CGWValidStrings* pValidStringsObject, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CValidStringsDlg)
	enum { IDD = IDD_GW_VALID_STRINGS_DLG };
		// NOTE: the ClassWizard will add data members here
	int m_nTextStrings;
	CString m_csName;
	CString m_csConnect;
	CString m_csDatabaseName;
	CString m_csRecordSource;
	//}}AFX_DATA
	int m_nRecordSourceType;

	CValidStringGrid m_ValidStringGrid;
	CGWValidStrings	 m_ValidStringsObject;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValidStringsDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CValidStringsDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnGetDatabaseName();
	afx_msg void OnSelChangeConnect();
	afx_msg void OnGetRecordSource();
	afx_msg void OnRadioTextStrings();
	afx_msg void OnRadioExternalData();
	afx_msg void OnChangeDatabaseName();
	afx_msg void OnChangeRecordSource();
	afx_msg void OnChangeName();
	afx_msg void OnRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class GW_EXT_CLASS CContextMenuGrid : public CGWGridCtrl
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public: 
	CContextMenuGrid();
	DECLARE_DYNCREATE(CContextMenuGrid)
	DECLARE_GRIDCELL_MAP(CContextMenuGrid)

// Attributes
public:

// Operations
public:
	void Initialize();
// Implementation
public:
	virtual ~CContextMenuGrid();

protected:


// Generated message map functions
protected:
	//{{AFX_MSG(CContextMenuGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


//BEGIN_VIRTUAL_FUNCTIONS(CContextMenuGrid)
	virtual void GridOnInitialUpdate();
	virtual void OnGetFixedCellText(int nRowNdx, int nColNdx, CString& csCellText);
//END_VIRTUAL_FUNCTIONS
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CContextMenuDlg dialog
class GW_EXT_CLASS CContextMenuDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CContextMenuDlg(CGWContextMenu* pContextMenu, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CContextMenuDlg)
	enum { IDD = IDD_GW_CONTEXT_MENU };
		// NOTE: the ClassWizard will add data members here
	CString m_csName;
	//}}AFX_DATA

	CContextMenuGrid m_ContextMenuGrid;
	CGWContextMenu	 m_ContextMenu;
	CMapStringToPtr  m_mapNameToItem;


	virtual void OnOK();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContextMenuDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CContextMenuDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnChangeName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class GW_EXT_CLASS CDAODlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CDAODlg(CGWDataSource* pGWDataSource, 
			CGWDatabaseRequest* pDatabaseRequest,
			CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextAlignmentDlg)
	enum { IDD = IDD_GW_DAO_DLG };
	BOOL m_bReadOnly;    
	BOOL m_bAppendable;
	//}}AFX_DATA

	CGWDatabaseRequest m_GWDatabaseRequest;
	CGWDataSource* m_pGWDataSource;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextAlignmentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextAlignmentDlg)
	afx_msg void OnSql();
	afx_msg void OnQBE();
	virtual BOOL OnInitDialog();
	void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CODBCDlg dialog

class GW_EXT_CLASS CODBCDlg : public CDialog
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
// Construction
public:
	CODBCDlg(CGWDataSource* pGWDataSource, 
			 CGWDatabaseRequest* pDatabaseRequest,
			 CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CODBCDlg)
	enum { IDD = IDD_GW_ODBC_DLG };
		// NOTE: the ClassWizard will add data members here
	BOOL m_bReadOnly;    
	BOOL m_bAppendable;
	//}}AFX_DATA

	CDatabase m_Database;
	CGWDatabaseRequest m_GWDatabaseRequest;
	CGWDataSource* m_pGWDataSource;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CODBCDlg)
	afx_msg void OnSql();
	afx_msg void OnQBE();
	afx_msg void OnSelchangeTables();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif //__GRIDDLGS_H__
