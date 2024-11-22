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
// gridview.h : header file
//
#ifndef __GRIDRPT_H__
#define __GRIDRPT_H__


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

class GW_EXT_CLASS CGWGridRptPage : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS


public:
//GW_MEMBERS{{(CGWGridRptPage, "Construction")
	CGWGridRptPage(int nVScrollPos, int nHScrollPos, int nPageNumber); //Constructs a page which describes the grid contents.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridRptPage, "Data Members")
	int m_nVScrollPos;	//Starting vertical row index.
	int m_nHScrollPos;	//Starting horizontal column index.
	int m_nVPageSize;	//Number of rows on the page.
	int m_nHPageSize;	//Number of columns on the page.
	int m_nPageNumber;	//The page number.
	CRect m_GridRect;	//The deveice coordinate extents of the page.
//}}GW_MEMBERS	
};

class GW_EXT_CLASS CGWGridRpt :  public CObject, public CGWGrid
{
//GW_CLASS{{(CGWGridRpt)
/*

The CGWGridRpt is mostly used with the reporting classes, but is also used when printing a CGWGridView 
object. The CGWGridView derived class overrides the MFC print virtual functions and instead of printing 
directly from the CGWGridView class, makes a copy and stores it in a CGWGridRpt object. This CGWGridRpt 
object is 'attached' to the CGWGridView by an embedded CGWGridRpt pointer called m_pDataGrid. All virtual 
functions are called through the m_pDataGrid pointer. If the CGWGridRpt object is  not attached to another 
CGWGrid object, the m_pDataGrid member should be set to itself. 

*/
//}}GW_CLASS	
friend class CGWGridView;
friend class CGWGridCtrl;
friend class CGWGridPopup;
//Attributes
public: 
	DECLARE_DYNCREATE(CGWGridRpt)
	DECLARE_GRIDCELL_MAP(CGWGridRpt)
//GW_MEMBERS{{(CGWGridRpt, "Construction")
	CGWGridRpt();			//Default constructor.
	virtual ~CGWGridRpt();	//Default destructor.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridRpt, "Data Members")
	CGWGrid*     m_pDataGrid;		//The grid which controls access to the data.
	CDocument* m_pDocument;			//The document which the data grid is attached to.
	CObArray   m_GridRptPages;		//Collection of CGWGridRptPage objects.
	float  m_fXScale;				//Multiplier to convert screen coordinates to printer coordinates.
	float  m_fYScale;				//Multiplier to convert screen coordinates to printer coordinates.
	int m_nOrigMaxRows;				//Original max rows before docked rows are added.
	int m_nOrigMaxColumns;			//Original max columns before docked columns are added.
//}}GW_MEMBERS	

public:
//GW_MEMBERS{{(CGWGridRpt, "Operations")
	BOOL Attach(CDC* pDC, CGWGrid* pGrid);	//Use this function to attach this CGWGridRpt to a screen grid.
    virtual	void CopyAndScaleGridExtents(CDC* pPrinterDC);		//Called to update a particular field with a CRecordset object.
 	virtual void PrintPage(CDC* pDC, CGWGridRptPage* pPage);	//Called to print a particular page.
	virtual void Paginate(CDC* pDC, CRect rectDraw, CPoint ptStart = CPoint(0,0) );	//Builds the CGWGridRptPage objects and adds then to m_GridRptPages collection.
    virtual void RestoreGridExtents();	//Returns extents to screen coordinates.
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWGridRpt, "Overriden Virtual Functions")
	virtual void OnGetCellText(int nRowNdx, int nColNdx, CString& csCellText);	//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual void OnGetCellLong(int nRowNdx, int nColNdx, long& nCellLong);		//Overriden to defer to the data grid pointed to by m_pDataGrid.	
	virtual void OnGetCellObject(int nRowNdx, int nColNdx, CObject*& pObject);	//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual void OnGetCellFloat(int nRowNdx, int nColNdx, double& nCellFloat);	//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual CBitmap* OnGetCellBitmap(int nRowNdx, int nColNdx, BOOL& bStretch, int& nJustify);	//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual void OnGetCellVariant(int nRowNdx, int nColNdx, VARIANT& vt, UINT vID);		//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual void OnGetFixedCellText(int nRowNdx, int nColNdx, CString& csCellText);		//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual void CopyGrid(CGWGrid* pGrid);	//Overriden to copy and scale specific extents from the screen grid.
	virtual void GridOnDrawPrint(CDC* pDC);	//Overriden to print pages from the m_GridRptPages collection.
	virtual CRect CalcTextRect(CRect rectCell, CDC* pDC) //Overriden to apply the scaling factor to the areas around the cell. 
				{
				    CRect rectDrawRect = CalcDrawRect(rectCell, pDC);
					CRect rectTextRect(rectDrawRect.left + (int) (2 * m_fXScale), 
					       		       rectDrawRect.top +  (int) (2 * m_fYScale),
									   rectDrawRect.right - (int) (3 * m_fXScale),
									   rectDrawRect.bottom - (int) (1 * m_fYScale));
					return rectTextRect; 
				}
	virtual void CalcGridRect()	//Overriden to disable recalculation of the grid rect and grid cell objects.
				{};
	virtual void GridOnInitialUpdate(CDC* pDC);	//Overriden to apply design-time properies to the grid. 
	virtual void CalcPageSize(CRect* pGridRect = NULL);	//This function determines how many rows and columns can potentially fit into the area of m_GridRect.
 	virtual void RecalcGridLayout(UINT nOperation, int nHint = 0);	//Overriden to rebuild the grid cell object cache.
	virtual void InitializeColWidths() //Disable the default in case this is a ODBC app.
				{};
	virtual CScrollBar* GetGridScrollBarCtrl(int nBar) //Overriden to disable scrollbars.
				{return NULL;}
//}}GW_MEMBERS	
	
	
	//Member access functions for CGWGridRpt
public:
//GW_MEMBERS{{(CGWGridRpt, "Member Access Functions")
	inline CGCOCache* GetGCOCache()			//Returns a pointer to the grid cell object cache.
		{return &m_listGridCellObjects;}  
	inline LOGFONT* GetLogFont()			//Returns a pointer to the grid's default log font.
		{return &m_LogFont;}
	inline void SetGridRect(CRect GridRect, BOOL bRefresh = FALSE);		//Sets the rectangle into which the grid page will be drawn.
    inline void SetVScrollPos(int nVScrollPos, BOOL bRefresh = FALSE);	//Sets the vertical scroll postion of the grid.
    inline void SetHScrollPos(int nHScrollPos, BOOL bRefresh = FALSE);	//Sets the horizontal scroll position of the grid.
//}}GW_MEMBERS	
};               

inline void CGWGridRpt::SetGridRect(CRect GridRect, BOOL bRefresh)
{
	m_GridRect = GridRect;
	if (bRefresh)
		Refresh();
}    

inline void CGWGridRpt::SetVScrollPos(int  nVScrollPos, BOOL bRefresh)
{
	m_nVScrollPos = nVScrollPos;
	if (bRefresh)
		Refresh();
}    

inline void CGWGridRpt::SetHScrollPos(int  nHScrollPos, BOOL bRefresh)
{
	m_nHScrollPos = nHScrollPos;
	if (bRefresh)
		Refresh();
}    


#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif //__GRIDRPT_H__

