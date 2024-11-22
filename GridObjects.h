// GridObjects.h : header file
//
//These are the objects which are manipulated through Dispatch 
//interfaces. These objects then interact with the Grid OCX;

/////////////////////////////////////////////////////////////////////////////
// CGWSheet command target
#ifndef __GRIDOBJECTS_H__
#define __GRIDOBJECTS_H__

class CGWSheet : public CCmdTarget
{
	friend class CGWRange;
	friend class CGWRow;
	friend class CGWColumn;
	friend class CGWCell;

	DECLARE_DYNCREATE(CGWSheet)

	CGWSheet();           // protected constructor used by dynamic creation
	CGWSheet(CGWGrid* pGrid, short nSheetNdx);
// Attributes
public:
   CGWGrid* m_pGrid;
   short m_nSheetNdx;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWSheet)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGWSheet();

	// Generated message map functions
	//{{AFX_MSG(CGWSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGWSheet)
	afx_msg long GetCellType();
	afx_msg void SetCellType(long lNewValue);
	afx_msg OLE_COLOR GetTextColor();
	afx_msg void SetTextColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetBackColor();
	afx_msg void SetBackColor(OLE_COLOR nNewValue);
	afx_msg BSTR GetFontName();
	afx_msg void SetFontName(LPCTSTR lpszNewValue);
	afx_msg BOOL GetFontBold();
	afx_msg void SetFontBold(BOOL bNewValue);
	afx_msg BOOL GetFontItalic();
	afx_msg void SetFontItalic(BOOL bNewValue);
	afx_msg short GetFontSize();
	afx_msg void SetFontSize(short nNewValue);
	afx_msg BOOL GetFontStrikeThru();
	afx_msg void SetFontStrikeThru(BOOL bNewValue);
	afx_msg BOOL GetFontTransparent();
	afx_msg void SetFontTransparent(BOOL bNewValue);
	afx_msg BOOL GetFontUnderLine();
	afx_msg void SetFontUnderLine(BOOL bNewValue);
	afx_msg BSTR GetSheetName();
	afx_msg void SetSheetName(LPCTSTR lpszNewValue);
	afx_msg short GetSheetIndex();
	afx_msg BSTR GetName();
	afx_msg void SetName(LPCTSTR lpszNewValue);
	afx_msg short GetVisibleRows();
	afx_msg short GetVisibleColumns();
	afx_msg short GetRowColUnits();
	afx_msg void SetRowColUnits(short nNewValue);
	afx_msg BOOL GetListBoxMode();
	afx_msg void SetListBoxMode(BOOL bNewValue);
	afx_msg short GetSelectionMode();
	afx_msg void SetSelectionMode(short nNewValue);
	afx_msg BOOL GetGridLines();
	afx_msg void SetGridLines(BOOL bNewValue);
	afx_msg long GetNumRows();
	afx_msg void SetNumRows(long nNewValue);
	afx_msg long GetNumColumns();
	afx_msg void SetNumColumns(long nNewValue);
	afx_msg BOOL GetColSelect();
	afx_msg void SetColSelect(BOOL bNewValue);
	afx_msg BOOL GetColResize();
	afx_msg void SetColResize(BOOL bNewValue);
	afx_msg BOOL GetRowSelect();
	afx_msg void SetRowSelect(BOOL bNewValue);
	afx_msg BOOL GetRowResize();
	afx_msg void SetRowResize(BOOL bNewValue);
	afx_msg OLE_COLOR GetGridLineColor();
	afx_msg void SetGridLineColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetFixedCellColor();
	afx_msg void SetFixedCellColor(OLE_COLOR nNewValue);
	afx_msg short GetDisableNoScroll();
	afx_msg void SetDisableNoScroll(short nNewValue);
	afx_msg float GetDefaultColumnWidth();
	afx_msg void SetDefaultColumnWidth(float newValue);
	afx_msg BOOL GetOleDragAndDrop();
	afx_msg void SetOleDragAndDrop(BOOL bNewValue);
	afx_msg float GetDefaultRowHeight();
	afx_msg void SetDefaultRowHeight(float newValue);
	afx_msg short GetSizingRegionWidth();
	afx_msg void SetSizingRegionWidth(short nNewValue);
	afx_msg short GetThumbScroll();
	afx_msg void SetThumbScroll(short nNewValue);
	afx_msg short GetScrollBars();
	afx_msg void SetScrollBars(short nNewValue);
	afx_msg short GetFixedColumns();
	afx_msg void SetFixedColumns(short nNewValue);
	afx_msg short GetFixedRows();
	afx_msg void SetFixedRows(short nNewValue);
	afx_msg BOOL GetShowAddRow();
	afx_msg void SetShowAddRow(BOOL bNewValue);
	afx_msg BOOL GetAutoSizeColumns();
	afx_msg void SetAutoSizeColumns(BOOL bNewValue);
	afx_msg BSTR GetDefaultCellType();
	afx_msg void SetDefaultCellType(LPCTSTR lpszNewValue);
	afx_msg long GetRowCacheIncrement();
	afx_msg void SetRowCacheIncrement(long nNewValue);
	afx_msg LPDISPATCH Rows(long nBegRowNdx, long nEndRowNdx);
	afx_msg LPDISPATCH Row(long nRowNdx);
	afx_msg LPDISPATCH Column(long nColNdx);
	afx_msg LPDISPATCH Columns(long nBegColNdx, long nEndColNdx);
	afx_msg LPDISPATCH Range(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, long nEndColNdx);
	afx_msg LPDISPATCH Cell(long nRowNdx, long nColNdx);
	afx_msg void ShowRow(long nRowNdx, BOOL bShow);
	afx_msg void ShowColumn(long nColNdx, BOOL bShow);
	afx_msg BOOL IsRowHidden(long nRowNdx);
	afx_msg BOOL IsRowVisible(long nRowNdx);
	afx_msg BOOL IsColumnHidden(long nColNdx);
	afx_msg BOOL IsColumnVisible(long nColNdx);
	afx_msg BOOL IsRowSelected(long nRowNdx);
	afx_msg BOOL IsColumnSelected(long nColNdx);
	afx_msg BOOL IsCellSelected(long nRowNdx, long nColNdx);
	afx_msg short SelectCell(long nRowNdx, long nColNdx, BOOL bExclusive);
	afx_msg short SelectRange(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, long nEndColNdx, BOOL bExclusive);
	afx_msg short SelectRow(long nRowNdx, BOOL bExclusive);
	afx_msg short SelectColumn(long nColNdx, BOOL bExclusive);
	afx_msg BOOL GetSelection(long FAR* nBegRowNdx, long FAR* nBegColNdx, long FAR* nEndRowNdx, long FAR* nEndColNdx, short nSelNdx);
	afx_msg long GetRowNdx(short nRow);
	afx_msg long GetColNdx(short nCol);
	afx_msg short GetGridRow(long nRowNdx);
	afx_msg short GetGridCol(long nColNdx);
	afx_msg float GetRowHeight(long nRowNdx, short nUnits);
	afx_msg float GetColWidth(long nColNdx, short nUnits);
	afx_msg void SetRowHeight(long nRowNdx, float fRowHeight, short nUnits);
	afx_msg void SetColWidth(long nColNdx, float fColWidth, short nUnits);
	afx_msg BOOL LockRow(long nRowNdx, BOOL bLock);
	afx_msg BOOL LockColumn(long nColNdx, BOOL bLock);
	afx_msg BOOL IsRowLocked(long nRowNdx);
	afx_msg BOOL IsColumnLocked(long nColNdx);
	afx_msg void ProtectRow(long nRowNdx, BOOL bProtected);
	afx_msg void ProtectColumn(long nColNdx, BOOL bProtected);
	afx_msg void ProtectCell(long nRowNdx, long nColNdx, BOOL bProtected);
	afx_msg void ProtectRange(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, long nEndColNdx, BOOL bProtected);
	afx_msg BOOL IsRowProtected(long nRowNdx);
	afx_msg BOOL IsColumnProtected(long nColNdx);
	afx_msg BOOL IsCellProtected(long nRowNdx, long nColNdx);
	afx_msg void DeleteRow(long nRowNdx, long nCount);
	afx_msg void DeleteColumn(long nColNdx, long nCount);
	afx_msg long InsertColumn(long nInsertBefore, long nCount, long lCellType);
	afx_msg long InsertRow(long nInsertBefore, long nCount, long lCellType);
	afx_msg long AddRow(long nCount, long lCellType);
	afx_msg long AddColumn(long nCount, long lCellType);
	afx_msg long MoveColumn(long nColNdx, long nInsertBefore);
	afx_msg long MoveRow(long nRowNdx, long nInsertBefore);
	afx_msg LPDISPATCH GetCurrentCell();
	afx_msg void CopyColumn(long nColNdx, long nInsertBefore);
	afx_msg void CopyRow(long nRowNdx, long nInsertBefore);
	afx_msg void BindColumn(long nColNdx, short nFieldNdx);
	afx_msg LPDISPATCH Report();
	afx_msg void RefreshRow(long BeginRow, long EndRow);
	afx_msg void RefreshColumn(long BeginColumn, long EndColumn);
	afx_msg void RefreshRange(long BeginRow, long BeginColumn, long EndRow, long EndColumn);
	afx_msg void RefreshCell(long Row, long Col);
	afx_msg LPDISPATCH GetDatabaseRequest();
	afx_msg BSTR GetCellText(BOOL bIncludeHeadings);
	afx_msg void SetCellText(LPCTSTR CellText, BOOL bIncludeHeadings);
	afx_msg void GroupCells(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, long nEndColNdx);
	afx_msg void UnGroupCells(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, long nEndColNdx);
	afx_msg void SetEditEvent(long nBegRowNdx, long nBegColNdx, long nEndRowNdx, short nEndColNdx, short nEditFlag);
	afx_msg void ResetExternalData();
	afx_msg void RefreshExternalData();
	afx_msg long Export(LPCTSTR FilePath, LPCTSTR FieldDelim, LPCTSTR LineDelim, BOOL DataHasRowHeaders, BOOL DataHasColumnHeaders, BOOL IncludeRowHeaders, BOOL IncludeColumnHeaders, BOOL CallBackForData);
	afx_msg long Import(LPCTSTR FilePath, LPCTSTR FieldDelim, LPCTSTR LineDelim, BOOL DataHasRowHeaders, BOOL DataHasColumnHeaders, BOOL IncludeRowHeaders, BOOL IncludeColumnHeaders, BOOL OverlayExistingData, BOOL ClearExistingData, BOOL CallBackForData);
	afx_msg void Sort(long nMajor, BOOL Ascending, long nMinor1, BOOL Ascending1, long nMinor2, BOOL Ascending2, long nMinor3, BOOL Ascending3, BOOL bCallBackForData);
	afx_msg BOOL Seek(LPCTSTR SeekText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL CallBackForData);
	afx_msg long Replace(LPCTSTR SeekText, LPCTSTR ReplacementText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL bReplaceAll, BOOL CallBackForData);
	afx_msg void SetAutoSizeRowHeight(BOOL bAutoSize);
	afx_msg void SetAutoSizeColumnWidth(BOOL bAutoSize);
	afx_msg void SetAutoSizeVisibleOnly(BOOL bAutoSizeVisible);
	afx_msg void SetControlStyles(long dwPrimaryControlStyle, long dwSecondaryControlStyle);
	afx_msg void SetExtendedControlStyle(long dwExtendedControlStyle);
	afx_msg void CopyToClipboard();
	afx_msg BOOL GetAutoSizeRowHeight();
	afx_msg BOOL GetAutoSizeColumnWidth();
	afx_msg BOOL GetAutoSizeVisibleOnly();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGWRow command target

class CGWRow : public CCmdTarget
{
	DECLARE_DYNCREATE(CGWRow)

	CGWRow();           // protected constructor used by dynamic creation
	CGWRow(CGWSheet* pSheet, long nBegRowNdx, long nEndRowNdx);       

// Attributes
public:
   CGWSheet* m_pSheet;
   long  m_nBegRowNdx;
   long  m_nEndRowNdx;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWRow)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGWRow();

	// Generated message map functions
	//{{AFX_MSG(CGWRow)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGWRow)
	afx_msg long GetRowNdx();
	afx_msg void SetRowNdx(long nNewValue);
	afx_msg short GetGridRow();
	afx_msg void SetGridRow(short nNewValue);
	afx_msg long GetCellType();
	afx_msg void SetCellType(long lNewValue);
	afx_msg BOOL GetProtected();
	afx_msg void SetProtected(BOOL bNewValue);
	afx_msg BOOL GetFontBold();
	afx_msg void SetFontBold(BOOL bNewValue);
	afx_msg BOOL GetFontItalic();
	afx_msg void SetFontItalic(BOOL bNewValue);
	afx_msg BSTR GetFontName();
	afx_msg void SetFontName(LPCTSTR lpszNewValue);
	afx_msg short GetFontSize();
	afx_msg void SetFontSize(short nNewValue);
	afx_msg BOOL GetFontStrikeThru();
	afx_msg void SetFontStrikeThru(BOOL bNewValue);
	afx_msg BOOL GetFontTransparent();
	afx_msg void SetFontTransparent(BOOL bNewValue);
	afx_msg BOOL GetFontUnderline();
	afx_msg void SetFontUnderline(BOOL bNewValue);
	afx_msg OLE_COLOR GetBackColor();
	afx_msg void SetBackColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetTextColor();
	afx_msg void SetTextColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetBorderColor();
	afx_msg void SetBorderColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetForeColor();
	afx_msg void SetForeColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetAutoBackColor();
	afx_msg void SetAutoBackColor(BOOL bNewValue);
	afx_msg BOOL GetAutoTextColor();
	afx_msg void SetAutoTextColor(BOOL bNewValue);
	afx_msg BOOL GetAutoFont();
	afx_msg void SetAutoFont(BOOL bNewValue);
	afx_msg BSTR GetFormat();
	afx_msg void SetFormat(LPCTSTR lpszNewValue);
	afx_msg short GetEditEvent();
	afx_msg void SetEditEvent(short nNewValue);
	afx_msg BSTR GetOCXClassName();
	afx_msg void SetOCXClassName(LPCTSTR lpszOCXClassName);
	afx_msg double GetMinValue();
	afx_msg void SetMinValue(double dMinValue);
	afx_msg double GetMaxValue();
	afx_msg void SetMaxValue(double dMaxValue);
	afx_msg long GetMaxTextLength();
	afx_msg void SetMaxTextLength(long lMaxTextLength);
	afx_msg void Show(BOOL bShow);
	afx_msg BOOL IsHidden();
	afx_msg BOOL IsVisible();
	afx_msg BOOL IsSelected();
	afx_msg short Select(BOOL bExclusive);
	afx_msg void SetHeight(float fHeight, short nUnits);
	afx_msg float GetHeight(short nUnits);
	afx_msg BOOL Lock(BOOL bLock);
	afx_msg BOOL IsLocked();
	afx_msg void Delete();
	afx_msg long Move(long nInsertBefore);
	afx_msg void Copy(long nInsertBefore);
	afx_msg void SetCellBorder(short LeftBorder, short TopBorder, short RightBorder, short BottomBorder, short LeftOutline, short TopOutline, short RightOutline, short BottomOutline);
	afx_msg void SetAlignment(short nVertAlign, short nHorzAlign, BOOL bWordWrap);
	afx_msg void SetFillPattern(short nPatternID, OLE_COLOR rgbForecolor);
	afx_msg void SetValidStringObject(LPDISPATCH ValidStringObject);
	afx_msg BSTR GetCellText(BOOL bIncludeHeadings);
	afx_msg void SetCellText(LPCTSTR CellText, BOOL bIncludeHeadings);
	afx_msg void GroupCells();
	afx_msg void UnGroupCells();
	afx_msg BOOL Seek(LPCTSTR SeekText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL CallBackForData);
	afx_msg long Replace(LPCTSTR SeekText, LPCTSTR ReplacementText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL bReplaceAll, BOOL CallBackForData);
	afx_msg void SetAutoSizeRowHeight(BOOL bAutoSize);
	afx_msg void SetAutoSizeColumnWidth(BOOL bAutoSize);
	afx_msg void SetAutoSizeVisibleOnly(BOOL bAutoSizeVisible);
	afx_msg void SetControlStyles(long dwPrimaryControlStyle, long dwSecondaryControlStyle);
	afx_msg void SetExtendedControlStyle(long dwExtendedControlStyle);
	afx_msg void CopyToClipboard();
	afx_msg void SetInputMask(LPCTSTR strInputMask);
	afx_msg void GetAlignment(short FAR* VertAlign, short FAR* HorzAlign, BOOL FAR* WordWrap);
	afx_msg void GetCellBorder(short FAR* LeftBorder, short FAR* TopBorder, short FAR* RightBorder, short FAR* BottomBorder, short FAR* LeftOutline, short FAR* TopOutline, short FAR* RightOutline, short FAR* BottomOutline);
	afx_msg void GetFillPattern(short FAR* PatternID, OLE_COLOR* ForeColor);
	afx_msg LPDISPATCH GetValidStringObject();
	afx_msg void GetControlStyles(long FAR* PrimaryControlStyle, long FAR* SecondaryControlStyle);
	afx_msg void GetExtendedControlStyle(long FAR* ExtendedControlStyle);
	afx_msg void GetInputMask(BSTR FAR* InputMask);
	afx_msg void GetCellGroup(long FAR* BegRowNdx, long FAR* BegColNdx, long FAR* EndRowNdx, long FAR* EndColNdx);
	afx_msg OLE_XPOS_PIXELS GetXPos();
	afx_msg OLE_YPOS_PIXELS GetYPos();
	afx_msg LPDISPATCH GetCellSettings();
	afx_msg void SetCellSettings(LPDISPATCH newValue);
	afx_msg BOOL GetAutoSizeRowHeight();
	afx_msg BOOL GetAutoSizeColumnWidth();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CGWColumn command target

class CGWColumn : public CCmdTarget
{
	DECLARE_DYNCREATE(CGWColumn)

	CGWColumn();           // protected constructor used by dynamic creation
	CGWColumn(CGWSheet* pSheet, long nBegColNdx, long nEndColNdx); 
// Attributes
public:
   CGWSheet* m_pSheet;
   long  m_nBegColNdx;
   long  m_nEndColNdx;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWColumn)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGWColumn();

	// Generated message map functions
	//{{AFX_MSG(CGWColumn)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGWColumn)
	afx_msg long GetColNdx();
	afx_msg void SetColNdx(long nNewValue);
	afx_msg short GetGridCol();
	afx_msg void SetGridCol(short nNewValue);
	afx_msg long GetCellType();
	afx_msg void SetCellType(long lNewValue);
	afx_msg BOOL GetProtected();
	afx_msg void SetProtected(BOOL bNewValue);
	afx_msg BOOL GetFontBold();
	afx_msg void SetFontBold(BOOL bNewValue);
	afx_msg BOOL GetFontItalic();
	afx_msg void SetFontItalic(BOOL bNewValue);
	afx_msg BSTR GetFontName();
	afx_msg void SetFontName(LPCTSTR lpszNewValue);
	afx_msg short GetFontSize();
	afx_msg void SetFontSize(short nNewValue);
	afx_msg BOOL GetFontStrikeThru();
	afx_msg void SetFontStrikeThru(BOOL bNewValue);
	afx_msg BOOL GetFontTransparent();
	afx_msg void SetFontTransparent(BOOL bNewValue);
	afx_msg BOOL GetFontUnderline();
	afx_msg void SetFontUnderline(BOOL bNewValue);
	afx_msg OLE_COLOR GetBackColor();
	afx_msg void SetBackColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetTextColor();
	afx_msg void SetTextColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetBorderColor();
	afx_msg void SetBorderColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetForeColor();
	afx_msg void SetForeColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetAutoBackColor();
	afx_msg void SetAutoBackColor(BOOL bNewValue);
	afx_msg BOOL GetAutoTextColor();
	afx_msg void SetAutoTextColor(BOOL bNewValue);
	afx_msg BOOL GetAutoFont();
	afx_msg void SetAutoFont(BOOL bNewValue);
	afx_msg BSTR GetFormat();
	afx_msg void SetFormat(LPCTSTR lpszNewValue);
	afx_msg short GetEditEvent();
	afx_msg void SetEditEvent(short nNewValue);
	afx_msg BSTR GetOCXClassName();
	afx_msg void SetOCXClassName(LPCTSTR lpszOCXClassName);
	afx_msg double GetMinValue();
	afx_msg void SetMinValue(double dMinValue);
	afx_msg double GetMaxValue();
	afx_msg void SetMaxValue(double dMaxValue);
	afx_msg long GetMaxTextLength();
	afx_msg void SetMaxTextLength(long lMaxTextLength);
	afx_msg void Show(BOOL bShow);
	afx_msg BOOL IsHidden();
	afx_msg BOOL IsVisible();
	afx_msg BOOL IsSelected();
	afx_msg short Select(BOOL bExclusive);
	afx_msg float GetWidth(short nUnits);
	afx_msg void SetWidth(float fWidth, short nUnits);
	afx_msg BOOL Lock(BOOL bLock);
	afx_msg BOOL IsLocked();
	afx_msg void Delete();
	afx_msg long Move(long nInsertBefore);
	afx_msg void Copy(long nInsertBefore);
	afx_msg void SetCellBorder(short LeftBorder, short TopBorder, short RightBorder, short BottomBorder, short LeftOutline, short TopOutline, short RightOutline, short BottomOutline);
	afx_msg void SetAlignment(short nVertAlign, short nHorzAlign, BOOL bWordWrap);
	afx_msg void SetFillPattern(short nPatternID, OLE_COLOR rgbForeColor);
	afx_msg void SetValidStringObject(LPDISPATCH ValidStringObject);
	afx_msg void SetCellText(LPCTSTR CellText, BOOL bIncludeHeadings);
	afx_msg BSTR GetCellText(BOOL bIncludeHeadings);
	afx_msg void GroupCells();
	afx_msg void UnGroupCells();
	afx_msg void Sort(BOOL Ascending, BOOL Ascending1, BOOL Ascending2, BOOL Ascending3, BOOL bCallBackForData);
	afx_msg BOOL Seek(LPCTSTR SeekText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL CallBackForData);
	afx_msg long Replace(LPCTSTR SeekText, LPCTSTR ReplacementText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL bReplaceAll, BOOL CallBackForData);
	afx_msg void SetAutoSizeRowHeight(BOOL bAutoSize);
	afx_msg void SetAutoSizeColumnWidth(BOOL bAutoSize);
	afx_msg void SetAutoSizeVisibleOnly(BOOL bAutoSizeVisible);
	afx_msg void SetControlStyles(long dwPrimaryControlStyle, long dwSecondaryControlStyle);
	afx_msg void SetExtendedControlStyle(long dwExtendedControlStyle);
	afx_msg void CopyToClipboard();
	afx_msg void SetInputMask(LPCTSTR strInputMask);
	afx_msg void GetAlignment(short FAR* VertAlign, short FAR* HorzAlign, BOOL FAR* WordWrap);
	afx_msg void GetCellBorder(short FAR* LeftBorder, short FAR* TopBorder, short FAR* RightBorder, short FAR* BottomBorder, short FAR* LeftOutline, short FAR* TopOutline, short FAR* RightOutline, short FAR* BottomOutline);
	afx_msg void GetFillPattern(short FAR* PatternID, OLE_COLOR* ForeColor);
	afx_msg LPDISPATCH GetValidStringObject();
	afx_msg void GetControlStyles(long FAR* PrimaryControlStyle, long FAR* SecondaryControlStyle);
	afx_msg void GetExtendedControlStyle(long FAR* ExtendedControlStyle);
	afx_msg void GetInputMask(BSTR FAR* InputMask);
	afx_msg void GetCellGroup(long FAR* BegRowNdx, long FAR* BegColNdx, long FAR* EndRowNdx, long FAR* EndColNdx);
	afx_msg OLE_XPOS_PIXELS GetXPos();
	afx_msg OLE_YPOS_PIXELS GetYPos();
	afx_msg LPDISPATCH GetCellSettings();
	afx_msg void SetCellSettings(LPDISPATCH newValue);
	afx_msg BOOL GetAutoSizeRowHeight();
	afx_msg BOOL GetAutoSizeColumnWidth();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CGWRange command target

class CGWRange : public CCmdTarget
{
	DECLARE_DYNCREATE(CGWRange)

	CGWRange();           // protected constructor used by dynamic creation
	CGWRange(CGWSheet* pSheet, long nBegRowNdx, 
			 long nBegColNdx, long nEndRowNdx, 
			 long nEndColNdx);
// Attributes
public:
   CGWSheet* m_pSheet;
   long  m_nBegRowNdx;
   long  m_nEndRowNdx;
   long  m_nBegColNdx;
   long  m_nEndColNdx;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWRange)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGWRange();

	// Generated message map functions
	//{{AFX_MSG(CGWRange)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGWRange)
	afx_msg long GetCellType();
	afx_msg void SetCellType(long lNewValue);
	afx_msg BOOL GetProtected();
	afx_msg void SetProtected(BOOL bNewValue);
	afx_msg BOOL GetFontBold();
	afx_msg void SetFontBold(BOOL bNewValue);
	afx_msg BOOL GetFontItalic();
	afx_msg void SetFontItalic(BOOL bNewValue);
	afx_msg BSTR GetFontName();
	afx_msg void SetFontName(LPCTSTR lpszNewValue);
	afx_msg short GetFontSize();
	afx_msg void SetFontSize(short nNewValue);
	afx_msg BOOL GetFontStrikeThru();
	afx_msg void SetFontStrikeThru(BOOL bNewValue);
	afx_msg BOOL GetFontTransparent();
	afx_msg void SetFontTransparent(BOOL bNewValue);
	afx_msg BOOL GetFontUnderline();
	afx_msg void SetFontUnderline(BOOL bNewValue);
	afx_msg OLE_COLOR GetBackColor();
	afx_msg void SetBackColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetTextColor();
	afx_msg void SetTextColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetBorderColor();
	afx_msg void SetBorderColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetForeColor();
	afx_msg void SetForeColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetAutoBackColor();
	afx_msg void SetAutoBackColor(BOOL bNewValue);
	afx_msg BOOL GetAutoTextColor();
	afx_msg void SetAutoTextColor(BOOL bNewValue);
	afx_msg BOOL GetAutoFont();
	afx_msg void SetAutoFont(BOOL bNewValue);
	afx_msg BSTR GetFormat();
	afx_msg void SetFormat(LPCTSTR lpszNewValue);
	afx_msg short GetEditEvent();
	afx_msg void SetEditEvent(short nNewValue);
	afx_msg BSTR GetOCXClassName();
	afx_msg void SetOCXClassName(LPCTSTR lpszOCXClassName);
	afx_msg double GetMinValue();
	afx_msg void SetMinValue(double dMinValue);
	afx_msg double GetMaxValue();
	afx_msg void SetMaxValue(double dMaxValue);
	afx_msg long GetMaxTextLength();
	afx_msg void SetMaxTextLength(long lMaxTextLength);
	afx_msg short Select(BOOL bExclusive);
	afx_msg void SetCellBorder(short LeftBorder, short TopBorder, short RightBorder, short BottomBorder, short LeftOutline, short TopOutline, short RightOutline, short BottomOutline);
	afx_msg void SetAlignment(short nVertAlign, short nHorzAlign, BOOL bWordWrap);
	afx_msg void SetFillPattern(short nPatternID, OLE_COLOR rgbForecolor);
	afx_msg void SetValidStringObject(LPDISPATCH ValidStringObject);
	afx_msg BSTR GetCellText(BOOL bIncludeHeadings);
	afx_msg void SetCellText(LPCTSTR CellText, BOOL bIncludeHeadings);
	afx_msg void GroupCells();
	afx_msg void UnGroupCells();
	afx_msg long Export(LPCTSTR FilePath, LPCTSTR FieldDelim, LPCTSTR LineDelim, BOOL DataHasRowHeaders, BOOL DataHasColumnHeaders, BOOL IncludeRowHeaders, BOOL IncludeColumnHeaders, BOOL CallBackForData);
	afx_msg long Import(LPCTSTR FilePath, LPCTSTR FieldDelim, LPCTSTR LineDelim, BOOL DataHasRowHeaders, BOOL DataHasColumnHeaders, BOOL IncludeRowHeaders, BOOL IncludeColumnHeaders, BOOL OverlayExistingData, BOOL ClearExistingData, BOOL CallBackForData);
	afx_msg BOOL Seek(LPCTSTR SeekText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL CallBackForData);
	afx_msg long Replace(LPCTSTR SeekText, LPCTSTR ReplacementText, long FAR* StartRow, long FAR* StartCol, BOOL Forward, BOOL MatchCase, BOOL MatchWholeCell, short SearchCondition, BOOL SetFocus, BOOL bReplaceAll, BOOL CallBackForData);
	afx_msg void SetControlStyles(long dwPrimaryControlStyle, long dwSecondaryControlStyle);
	afx_msg void SetExtendedControlStyle(long dwExtendedControlStyle);
	afx_msg void CopyToClipboard();
	afx_msg void SetInputMask(LPCTSTR strInputMask);
	afx_msg void GetAlignment(short FAR* VertAlign, short FAR* HorzAlign, BOOL FAR* WordWrap);
	afx_msg void GetCellBorder(short FAR* LeftBorder, short FAR* TopBorder, short FAR* RightBorder, short FAR* BottomBorder, short FAR* LeftOutline, short FAR* TopOutline, short FAR* RightOutline, short FAR* BottomOutline);
	afx_msg void GetFillPattern(short FAR* PatternID, OLE_COLOR* ForeColor);
	afx_msg LPDISPATCH GetValidStringObject();
	afx_msg void GetControlStyles(long FAR* PrimaryControlStyle, long FAR* SecondaryControlStyle);
	afx_msg void GetExtendedControlStyle(long FAR* ExtendedControlStyle);
	afx_msg void GetInputMask(BSTR FAR* InputMask);
	afx_msg void GetCellGroup(long FAR* BegRowNdx, long FAR* BegColNdx, long FAR* EndRowNdx, long FAR* EndColNdx);
	afx_msg OLE_XPOS_PIXELS GetXPos();
	afx_msg OLE_YPOS_PIXELS GetYPos();
	afx_msg LPDISPATCH GetCellSettings();
	afx_msg void SetCellSettings(LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CGWCell command target

class CGWCell : public CCmdTarget
{
	DECLARE_DYNCREATE(CGWCell)

	CGWCell();           // protected constructor used by dynamic creation
	CGWCell(CGWSheet* pSheet, long nRowNdx, long nColNdx); 

// Attributes
public:
   CGWSheet* m_pSheet;
   long  m_nRowNdx;
   long  m_nColNdx;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGWCell)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGWCell();

	// Generated message map functions
	//{{AFX_MSG(CGWCell)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGWCell)
	afx_msg BSTR GetText();
	afx_msg void SetText(LPCTSTR lpszNewValue);
	afx_msg short GetGridRow();
	afx_msg void SetGridRow(short nNewValue);
	afx_msg short GetGridCol();
	afx_msg void SetGridCol(short nNewValue);
	afx_msg long GetRowNdx();
	afx_msg void SetRowNdx(long nNewValue);
	afx_msg long GetColNdx();
	afx_msg void SetColNdx(long nNewValue);
	afx_msg long GetCellType();
	afx_msg void SetCellType(long lNewValue);
	afx_msg BOOL GetProtected();
	afx_msg void SetProtected(BOOL bNewValue);
	afx_msg BSTR GetFontName();
	afx_msg void SetFontName(LPCTSTR lpszNewValue);
	afx_msg BOOL GetFontItalic();
	afx_msg void SetFontItalic(BOOL bNewValue);
	afx_msg BOOL GetFontBold();
	afx_msg void SetFontBold(BOOL bNewValue);
	afx_msg short GetFontSize();
	afx_msg void SetFontSize(short nNewValue);
	afx_msg BOOL GetFontTransparent();
	afx_msg void SetFontTransparent(BOOL bNewValue);
	afx_msg BOOL GetFontUnderline();
	afx_msg void SetFontUnderline(BOOL bNewValue);
	afx_msg BOOL GetFontStrikeThru();
	afx_msg void SetFontStrikeThru(BOOL bNewValue);
	afx_msg OLE_COLOR GetBackColor();
	afx_msg void SetBackColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetTextColor();
	afx_msg void SetTextColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetBorderColor();
	afx_msg void SetBorderColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetForeColor();
	afx_msg void SetForeColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetAutoBackColor();
	afx_msg void SetAutoBackColor(BOOL bNewValue);
	afx_msg BOOL GetAutoTextColor();
	afx_msg void SetAutoTextColor(BOOL bNewValue);
	afx_msg BOOL GetAutoFont();
	afx_msg void SetAutoFont(BOOL bNewValue);
	afx_msg BSTR GetFormat();
	afx_msg void SetFormat(LPCTSTR lpszNewValue);
	afx_msg BSTR GetCellText();
	afx_msg void SetCellText(LPCTSTR lpszNewValue);
	afx_msg short GetEditEvent();
	afx_msg void SetEditEvent(short nNewValue);
	afx_msg BSTR GetOCXClassName();
	afx_msg void SetOCXClassName(LPCTSTR lpszOCXClassName);
	afx_msg double GetMinValue();
	afx_msg void SetMinValue(double dMinValue);
	afx_msg double GetMaxValue();
	afx_msg void SetMaxValue(double dMaxValue);
	afx_msg long GetMaxTextLength();
	afx_msg void SetMaxTextLength(long lMaxTextLength);
	afx_msg BOOL IsSelected();
	afx_msg short Select(BOOL bExclusive);
	afx_msg float GetHeight(short nUnits);
	afx_msg float GetWidth(short nUnits);
	afx_msg void SetCellBorder(short LeftBorder, short TopBorder, short RightBorder, short BottomBorder);
	afx_msg void SetAlignment(short nVertAlign, short nHorzAlign, BOOL bWordWrap);
	afx_msg void SetFillPattern(short nPatternID, OLE_COLOR rgbForeColor);
	afx_msg void SetValidStringObject(LPDISPATCH ValidStringObject);
	afx_msg void SetControlStyles(long dwPrimaryControlStyle, long dwSecondaryControlStyle);
	afx_msg void SetExtendedControlStyle(long dwExtendedControlStyle);
	afx_msg void CopyToClipboard();
	afx_msg void SetInputMask(LPCTSTR strInputMask);
	afx_msg void GetAlignment(short FAR* VertAlign, short FAR* HorzAlign, BOOL FAR* WordWrap);
	afx_msg void GetCellBorder(short FAR* LeftBorder, short FAR* TopBorder, short FAR* RightBorder, short FAR* BottomBorder, short FAR* LeftOutline, short FAR* TopOutline, short FAR* RightOutline, short FAR* BottomOutline);
	afx_msg void GetFillPattern(short FAR* PatternID, OLE_COLOR* ForeColor);
	afx_msg LPDISPATCH GetValidStringObject();
	afx_msg void GetControlStyles(long FAR* PrimaryControlStyle, long FAR* SecondaryControlStyle);
	afx_msg void GetExtendedControlStyle(long FAR* ExtendedControlStyle);
	afx_msg void GetInputMask(BSTR FAR* InputMask);
	afx_msg void GetCellGroup(long FAR* BegRowNdx, long FAR* BegColNdx, long FAR* EndRowNdx, long FAR* EndColNdx);
	afx_msg OLE_XPOS_PIXELS GetXPos();
	afx_msg OLE_YPOS_PIXELS GetYPos();
	afx_msg LPDISPATCH GetCellSettings();
	afx_msg void SetCellSettings(LPDISPATCH newValue);
	afx_msg LPPICTUREDISP GetBitmap();
	afx_msg void SetBitmap(LPPICTUREDISP newValue);
	afx_msg long GetBitmapAlignment();
	afx_msg void SetBitmapAlignment(long nNewValue);
	afx_msg BSTR GetTag();
	afx_msg void SetTag(LPCTSTR newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// COCXValidStrings command target

class COCXValidStrings : public CCmdTarget
{
	DECLARE_DYNCREATE(COCXValidStrings)
	COCXValidStrings();           // protected constructor used by dynamic creation

// Attributes
public:
	CGWValidStrings* m_pValidStringObject;
	BOOL bDestroyWhenFinished;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCXValidStrings)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COCXValidStrings();

	// Generated message map functions
	//{{AFX_MSG(COCXValidStrings)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(COCXValidStrings)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COCXValidStrings)
	afx_msg BSTR GetValidString(short ValidStringIndex);
	afx_msg void SetDatabaseRequest(LPDISPATCH DatabaseRequest);
	afx_msg void SetItemDataString(short ValidStringIndex, LPCTSTR ItemDataString);
	afx_msg void ClearContents();
	afx_msg BSTR GetItemDataString(short ValidStringIndex);
	afx_msg short SetValidString(LPCTSTR ValidString);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// COCXDatabaseRequest command target

class COCXDatabaseRequest : public CCmdTarget
{
	DECLARE_DYNCREATE(COCXDatabaseRequest)

	COCXDatabaseRequest();           // protected constructor used by dynamic creation
	COCXDatabaseRequest(CGWSheet* pSheet);
// Attributes
public:
	CGWDatabaseRequest* m_pDatabaseRequest;
	BOOL bDestroyWhenFinished;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCXDatabaseRequest)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COCXDatabaseRequest();

	// Generated message map functions
	//{{AFX_MSG(COCXDatabaseRequest)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(COCXDatabaseRequest)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COCXDatabaseRequest)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg LPDISPATCH GetAdoRecordset();
	afx_msg void SetAdoRecordset(LPDISPATCH newValue);
	afx_msg BSTR GetDatabaseConnect();
	afx_msg void SetDatabaseConnect(LPCTSTR lpszNewValue);
	afx_msg BSTR GetRecordSource();
	afx_msg void SetRecordSource(LPCTSTR lpszNewValue);
	afx_msg short GetRecordsetType();
	afx_msg void SetRecordsetType(short nNewValue);
	afx_msg BOOL GetReadOnly();
	afx_msg void SetReadOnly(BOOL bNewValue);
	afx_msg short GetRecordSourceType();
	afx_msg void SetRecordSourceType(short nNewValue);
	afx_msg BSTR GetSQL();
	afx_msg void SetSQL(LPCTSTR lpszNewValue);
	afx_msg short GetParameterCount();
	afx_msg void ClearParams();
	afx_msg void SetParamValue(LPCTSTR Name, LPCTSTR Value);
	afx_msg BSTR GetParamValue(LPCTSTR Name);
	afx_msg void SetDatabaseFile(LPCTSTR FileName, LPCTSTR AbsolutePath, LPCTSTR RelativePath, LPCTSTR URLPath, short PrimaryPath);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COCXCellSettings command target

class COCXCellSettings : public CCmdTarget
{
public:
	DECLARE_DYNCREATE(COCXCellSettings)


// Attributes
	COCXCellSettings();           // protected constructor used by dynamic creation
	virtual ~COCXCellSettings();
	HGLOBAL m_hCellSettings;

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCXCellSettings)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COCXCellSettings)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COCXCellSettings)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif// GridObjects.cpp : implementation file
