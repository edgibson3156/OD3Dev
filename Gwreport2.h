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
//Header file for CGWReport 

#ifndef __GWREPORT_H__
#define __GWREPORT_H__

#include <AFXPRIV.H> 

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


class CGWReportItem;
class GW_EXT_CLASS CGWReport : public CView   
{
//GW_CLASS{{(CGWReport)
/*

The CGWReport class is the main reporting class and derives from MFC's CView. The basic structure of MFC's printing 
architecture is left in tact including the ability to override the CView printing virtual functions. CGWReport overrides 
these functions as well, so make sure you call the base class implementations when appropriate. The CGWReport class 
maintains several lists of object pointers which point at Report Item objects and Page objects. The sections
of a page consist of the Header, Body and Footer. Reports are constructed by adding report items each of these sections.
The CGWReport class has other member data which define the page layout, the sizes of the three report sections 
(Header, Body , and Footer), and page orientation (Portrait and Landscape). The GridWiz Wizard will set the initial values 
for these items on the property page of a report. Once a report object is instantiated and created, it can be printed
by calling the PrintReport() function or previewed by calling the PrintPreview() function. 


See the article "Reports" for additional implementation details. There is also a sample application called: REPORT.

*/
//}}GW_CLASS	


	DECLARE_DYNCREATE(CGWReport)

//GW_ENUMERATIONS{{(CGWReport, "Report page orientation.")
	enum PageOrientation
	{
	 	Portrait = 1,
	 	Landscape = 2,
	} PageOrientations;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWReport, "Report section specifiers.")
	enum Section
	{
	 	HEADER,
		BODY,
	 	FOOTER,
	} Sections;
//}}GW_ENUMERATIONS

public: 
//GW_MEMBERS{{(CGWReport,"Construction")
	CGWReport(CView* pRequestWindow);			//Construct a CGWReport object from a CView	object.
	CGWReport();								//Default Constructor.
	virtual ~CGWReport();						//Default Destructor.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWReport,"Data Members")
	CView* m_pOldActiveView;			//Pointer to the view which is to recieve focus when the CGWReport object is destroyed.
	CWnd* m_pRequestWindow;				//After print preview is closed, focus goes to this window.
	CPrintInfo* m_pInfo;           		//Used to grab the number of the page which is to be printed
	CObArray  m_arrayHeaderItems;       //Array of pointers to report items which are part of the header.
	CObArray  m_arrayReportItems;       //Array of pointers to report items which make up the report body.
	CObArray  m_arrayFooterItems;       //Array of pointers to report items which are part of the footer.
	CRect m_rectHeader;       			//The area contained by the Header(in MM_LOENGLISH)
	CRect m_rectHeaderDP;   			//Contains the corresponding coordinates of m_rectReportBody in Device Points.
	CRect m_rectReportBody;       		//The portion of the page excluding margins, header and footer (in MM_LOENGLISH)
	CRect m_rectReportBodyDP;   		//Contains the corresponding coordinates of m_rectReportBody in Device Points.
	CRect m_rectFooter;       			//The area set aside for the footer (in MM_LOENGLISH)
	CRect m_rectFooterDP;   			//Contains the corresponding coordinates of m_rectReportBody in Device Points.
	CRect m_rectPage;              		//The layout of the page in MM_LOENGLISH units. 
	int m_nCurrentPage;            		//The number of the page which is to be printed
	int m_nCurrentItem;             	//The item which is currently being printed.
    int m_nTopMargin;                	//The top margin in MM_LOENGLISH units.
    int m_nBottomMargin;				//The bottom margin in MM_LOENGLISH units.
    int m_nRightMargin;					//The right margin in MM_LOENGLISH units.
    int m_nLeftMargin;					//The left margin in MM_LOENGLISH units.
	int m_nHeaderHeight;				//The height of the header section in MM_LOENGLISH units.
	int m_nFooterHeight;				//The height of the footer section in MM_LOENGLISH units.
	int m_nPageOrientation;				//The page orientation: Portrait = 1,Landscape = 2,
    int m_nHeaderToBody;				//The height of the gap between the header and body sections in MM_LOENGLISH units.
    int m_nBodyToFooter;				//The height of the gap between the body and footer sections in MM_LOENGLISH units.
//}}GW_MEMBERS	

public:
//GW_MEMBERS{{(CGWReport,"Working Data Members")
    CPoint m_ptCurrentPosition;			//The location of the next item to be added during pagination. In Device Points.
    BOOL   m_bNeedRepagination;			//Flag indicating that the report needs to be paginated.
    CObArray m_mapPageTable;			//Collection of CPage objects. One for each page.
	BOOL m_bPaginatingHeaderNow;		//Flag indicating that the header section is being paginated.
	BOOL m_bPaginatingReportBodyNow;	//Flag indicating that the report body section is being paginated.
	BOOL m_bPaginatingFooterNow;		//Flag indicating that the footer section is being paginated.
//}}GW_MEMBERS	


//Operations
public:
//GW_MEMBERS{{(CGWReport,"Operations")
	CPoint GetCurrentPosition()							//Set the position for the next item in the report.
		{
			return m_ptCurrentPosition;
		}
	BOOL   SetCurrentPosition(CPoint ptCurrentPosition) //Set the position for the next item in the report. Used during pagination to determine where the next item will be placed.
		{
			m_ptCurrentPosition = ptCurrentPosition;
			 return (m_ptCurrentPosition.y < m_rectReportBody.bottom) ? TRUE : FALSE;
		}
	void ClearReportItems();	//Remove and free all report items.
	void ClearPages();			//Remove and free all report pages.
	void PrintReport();			//Send the Print job to the printer.
	void PrintPreview();   		//Invoke the Print Preview function. 
//}}GW_MEMBERS	

//Overrideables
public:
//GW_MEMBERS{{(CGWReport,"Overrideables")
	virtual BOOL Create();											//Creates the the Frame/Doc/View.
	virtual void BuildPageLayout(CRect& rectPageSize, CDC* pDC);	//Create and add the report items to the header and footer sections.
	virtual void CalcReportBody(CRect& rectPageSize, CDC* pDC);		//Calculate the amount of space left over for the report body section.
	virtual void BuildReportLayout(CDC* pDC);						//Create and add the report items to the report body section.
	virtual void Paginate(CDC* pDC, CPrintInfo* pInfo);				//Create and add page object to the report.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);				//Overriden here to take over the creation of the print dialog.			
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);		//Builds and paginates the report.
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);		//Cleans up after printing.
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);				//Calls the reports OnDraw() function.
	virtual void OnDraw(CDC* pDC);									//Prints one page of the report.
	virtual void OnFilePrint();										//Kicks off the printing process.
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);	//Cleans up after print preview.
//}}GW_MEMBERS	

	
	
//Member access functions
//GW_MEMBERS{{(CGWReport,"Member Access Functions")
	inline int GetLeftMargin()							//Retrieve the reports left margin.		
		{return m_nLeftMargin;}
	inline int GetTopMargin()							//Retrieve the reports top margin.	
		{return m_nTopMargin;}
	inline int GetRightMargin()                			//Retrieve the reports right margin.
		{return m_nRightMargin;}
	inline int GetBottomMargin()               			//Retrieve the reports bottom margin.
		{return m_nBottomMargin;}
	inline int GetHeaderHeight()               			//Retrieve the reports header height.
		{return m_nHeaderHeight;}
	inline int GetFooterHeight()               			//Retrieve the reports footer height.
		{return m_nFooterHeight;}
	inline int GetPageOrientation()            			//Retrieve the reports page orientation.
		{return m_nPageOrientation;}
	inline int GetBodyToFooterGap()						//Retieve the body to footer height.
		{return m_nBodyToFooter;}
	inline int GetHeaderToBodyGap()						//Retrieve the header to body gap.
		{return m_nHeaderToBody;}
	inline void SetLeftMargin(int nLeftMargin)			//Set the left margin of the report in MM_LOENGLISH units.	
		{m_nLeftMargin = nLeftMargin;}
	inline void SetTopMargin(int nTopMargin)			//Set the top margin of the report in MM_LOENGLISH units.	
		{m_nTopMargin = nTopMargin;}
	inline void SetRightMargin(int nRightMargin)		//Set the right margin of the report in MM_LOENGLISH units.	
		{m_nRightMargin = nRightMargin;}
	inline void SetBottomMargin(int nBottomMargin)		//Set the bottom margin of the report in MM_LOENGLISH units.	
		{m_nBottomMargin = nBottomMargin;} 
	inline void AddHeaderItem(CGWReportItem* pReportItem)	//Add a report item to the header section.
		{m_arrayHeaderItems.Add((CObject*) pReportItem);}
	inline void AddReportItem(CGWReportItem* pReportItem)	//Add a report item to the report body section.
		{m_arrayReportItems.Add((CObject*) pReportItem);}
	inline void AddFooterItem(CGWReportItem* pReportItem)	//Add a report item to the report footer section.
		{m_arrayFooterItems.Add((CObject*) pReportItem);}
	inline void SetHeaderHeight(int nHeaderHeight)			//Set the header section height in MM_LOENGLISH units.
		{m_nHeaderHeight = nHeaderHeight;}
	inline void SetFooterHeight(int nFooterHeight)			//Set the footer section height in MM_LOENGLISH units.
		{m_nFooterHeight = nFooterHeight;}
	inline void SetPageOrientation(int nPageOrientation)	//Set the Page orientation flag.
		{m_nPageOrientation = nPageOrientation;}
	inline void SetBodyToFooterGap(int nBodyToFooter)		//Set the Body to Footer height in MM_LOENGLISH units.
		{m_nBodyToFooter = nBodyToFooter;}
	inline void SetHeaderToBodyGap(int nHeaderToBody)		//Set the Header to Body height in MM_LOENGLISH units.
		{m_nHeaderToBody = nHeaderToBody;}
//}}GW_MEMBERS	

//inline properties sets
protected:
//GW_MEMBERS{{(CGWReport,"Inline Properties Sets")
	inline void GW_LEFTMARGIN(int nLeftMargin) 				//Set the left margin of the report in MM_LOENGLISH units.				
		{SetLeftMargin(nLeftMargin);}
	inline void GW_TOPMARGIN(int nTopMargin)				//Set the top margin of the report in MM_LOENGLISH units.					
		{SetTopMargin(nTopMargin);}
	inline void GW_RIGHTMARGIN(int nRightMargin)			//Set the right margin of the report in MM_LOENGLISH units.				
		{SetRightMargin(nRightMargin);}
	inline void GW_BOTTOMMARGIN(int nBottomMargin)			//Set the bottom margin of the report in MM_LOENGLISH units.	 			
		{SetBottomMargin(nBottomMargin);}
	inline void GW_HEADERHEIGHT(int nHeaderHeight) 			//Set the header section height in MM_LOENGLISH units.		
		{SetHeaderHeight(nHeaderHeight);}
	inline void GW_FOOTERHEIGHT(int nFooterHeight) 			//Set the footer section height in MM_LOENGLISH units.		
		{SetFooterHeight(nFooterHeight);}
	inline void GW_PAGEORIENTATION(int nPageOrientation)	//Set the Page orientation flag.	
		{SetPageOrientation(nPageOrientation);}
	inline void GW_BODYTOFOOTER(int nBodyToFooter)			//Set the Body to Footer height in MM_LOENGLISH units.     
		{SetBodyToFooterGap(nBodyToFooter);}
	inline void GW_HEADERTOBODY(int nHeaderToBody)          //Set the Header to Body height in MM_LOENGLISH units.
		{SetHeaderToBodyGap(nHeaderToBody);}
//}}GW_MEMBERS	

// Generated message map functions
protected:
	//{{AFX_MSG(CGWReport)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnFilePrintPreview();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class GW_EXT_CLASS CExtraData : public CObject  // This object keeps track of extra data the Report Items
{												// Will use when the pages have been constructed during
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_DYNCREATE(CExtraData)				// pagination. The information is used to print each page.

public:								
//GW_MEMBERS{{(CExtraData,"Construction")
	CExtraData()									//Default constructor.
		{m_rectAbsolute = CRect(0,0,0,0);}
	CExtraData(CRect rectAbsolute)					//Constructs a CExtraData object and initializes the absolute position.
		{m_rectAbsolute = rectAbsolute;}
	virtual ~CExtraData()							//Default Destructor.
		{};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CExtraData,"Data Members")
	CRect m_rectAbsolute; 							//The absolute position of an item.
//}}GW_MEMBERS	
};

//Provides details for each page in the report after pagination has been performed.
class GW_EXT_CLASS CPage : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_DYNCREATE(CPage)
public:
//GW_MEMBERS{{(CPage,"Construction")
	CPage()										//Default Constructor.
		{};
 	CPage(int nPageNumber)						//Constructs a CPage object and sets its page number.
		{
			m_nPageNumber = nPageNumber;
		}
 	virtual ~CPage();							//Defualt Destructor.
//}}GW_MEMBERS	
	
//GW_MEMBERS{{(CPage,"Data Members")
 	int m_nPageNumber;							//The page number.
	CObArray  m_arrayReportItems;				//Collection of report items to be printed on this page.
 	CObArray  m_arrayExtraData;					//Hold extra data for a report item. i.e. offsets for items which span pages.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CPage,"Operations")
	void AddReportItem(CGWReportItem* pReportItem, CExtraData* pExtraData = NULL)		//Add a report item to a report page.
 		{
			m_arrayReportItems.Add((CObject*) pReportItem);
 			m_arrayExtraData.Add((CObject*) pExtraData);
		}
 	int GetNumItemsOnPage()									//Retrieve the number of items on a particular page.
		{
			return m_arrayReportItems.GetSize();
		} 
//}}GW_MEMBERS	
};

class GW_EXT_CLASS CGridExtraData : public CExtraData  //This object hold extra data for the grid item
{									
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_DYNCREATE(CGridExtraData)
public:								
//GW_MEMBERS{{(CGridExtraData,"Construction")
	CGridExtraData()									//Default Constructor.
		{};
	CGridExtraData(CGWGridRptPage* pPage)				//Creates a CGridExtraData object and sets its page member.
		{
			m_pPage = pPage;
		}
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGridExtraData,"Data Members")
	CGWGridRptPage* m_pPage;							//Page on which this CGridExtraData object is associated with.
//}}GW_MEMBERS	
};

class GW_EXT_CLASS CTextExtraData : public CExtraData  //This object hold extra data for the grid item
{									
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_DYNCREATE(CTextExtraData)
public:								
//GW_MEMBERS{{(CTextExtraData,"Constructors")
	CTextExtraData()									//Default Constructor.
		{};
	CTextExtraData(CRect rectAbsolute, int nStartLoc, int nBreakLoc)	//Constructs a CTextExtraData object and assigns the absolute position.
		{
			m_rectAbsolute = rectAbsolute; 
			m_nStartLoc = nStartLoc; 
			m_nBreakLoc = nBreakLoc;
		}
//}}GW_MEMBERS	

//GW_MEMBERS{{(CTextExtraData,"Data Members")
	int m_nStartLoc;									//Location with in text buffer to start page.	
	int m_nBreakLoc;									//End position in text buffeer to end page.
//}}GW_MEMBERS	
};

class GW_EXT_CLASS CGWReportPreview : public CPreviewView   
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_DYNCREATE(CGWReportPreview)
public: 
//GW_MEMBERS{{(CGWReportPreview,"Constructors")
	CGWReportPreview();									//Default Constructor.
	virtual ~CGWReportPreview();						//Default Destructor.
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWReportPreview,"Data Members")
	CGWReport* m_pGWReport;								//The report object.
	BOOL m_bPreviewPrint;								//Boolean indicating print preview.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWReportPreview,"Operations")
	void SwitchToOrigView();							//Switch focus to the originating view.
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);		//End the print preview process.
//}}GW_MEMBERS	


protected:
//GW_MEMBERS{{(CGWReportPreview,"Message Handlers")
	afx_msg void OnPreviewClose();						//Trigerred by closing the Print Preview view.
	afx_msg void OnPreviewPrint();						//Trigerred by clicking the print button from the Print Preview view.
	afx_msg void OnClose();								//Trigerred by the Print Preview view closing.
//}}GW_MEMBERS	

	DECLARE_MESSAGE_MAP()
};


class GW_EXT_CLASS CGWReportItem : public CObject
{
//GW_CLASS{{(CGWReportItem)
/*

 The CReportItem class is the base class for all report items. This class is a pure abstract class and cannot be used alone.  
 CReportItem has base class members which keep track of its size and relative position settings. It also has pointers back 
 to the page on which it belongs as well as CGWReport object.

*/
//}}GW_CLASS	
friend class CGWReport;
	DECLARE_DYNCREATE(CGWReportItem)

public:
//GW_ENUMERATIONS{{(CGWReportItem, "Automatic Item size specifiers.")
	enum ItemSize
	{
		PageWidth = -1,
		VariableLength = -1, 
		SectionHeight = -2
	} ItemSizes;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWReportItem, "Automatic Item position specifiers.")
	enum Position
	{
	 	Relative,
	 	Absolute,
	} Positions;
//}}GW_ENUMERATIONS
	
//GW_ENUMERATIONS{{(CGWReportItem, "Automatic Item minimum height specifiers.")
	enum MinimumHeight
	{
	 	AllorNextPage = -1,
	 	PrintRegardless = 0,
	} MinimumHeights;
//}}GW_ENUMERATIONS

public: 
//GW_MEMBERS{{(CGWReportItem,"Constructors")
	CRect 			m_rectItem;         	//The bounding rectangle for this item.
    BOOL 			m_bGoToNextPage;    	//Whether or not this item is allowed to span pages
    BOOL   			m_bPositionAbsolute;   	//Does m_rectItem specify an absolute location on the page.
	int				m_nMinSize;         	//The minimum size left on a page before this item skips to next page. (default 0 means it must fit completely).
	int             m_nMinSizeDP;			//The device point version of m_nMinSize.
	BOOL 			m_bVariableLength;      //Should the item itself define how long it should be.
	CGWReport* 		m_pGWReport;			//Report Object this item belongs to.
	CPage*          m_pPage;            	//Page object this item is on.
//}}GW_MEMBERS	
public:

//Operations
//GW_MEMBERS{{(CGWReportItem,"Operations")
	void SetItemRect(CRect rectItem, CDC* pDC, int nSection = CGWReport::BODY);   	//Sets the report items size and position in inches (MM_LONENGLISH)
//}}GW_MEMBERS	

//member access functions
public:
//GW_MEMBERS{{(CGWReportItem,"Member Access Functions")
    inline void SetPositionAbsolute(BOOL bPositionAbsolute)		//Set the position absolute flag.
		{
			m_bPositionAbsolute = bPositionAbsolute;
		}
	inline void SetPageCarryover(BOOL bPageCarryOver)			//Set the page carry over flag.
		{
			m_bGoToNextPage = bPageCarryOver;
		}
	inline void SetItemTop(int nTop)							//Set the rectItem.top member,
		{
			m_rectItem.bottom += nTop - m_rectItem.top;
			m_rectItem.top = nTop;
		}
	inline void SetItemLeft(int nLeft)							//Set the rectItem.left member,
		{
			m_rectItem.right += nLeft - m_rectItem.left;
			m_rectItem.left = nLeft;
		}
	inline void SetItemWidth(int nWidth)						//Set the rectItem width member,
		{
			m_rectItem.right = (nWidth == PageWidth) ? PageWidth : nWidth;
		}
	inline void SetItemHeight(int nHeight)						//Set the rectItem height member,	
		{	m_bVariableLength = (nHeight == VariableLength) ? TRUE : FALSE;
			m_rectItem.bottom = (nHeight == VariableLength) ? VariableLength : nHeight;
		}
	inline void SetItemMinHeight(int nMinHeight)				//Set the rectItem minimum height member,
		{
			m_nMinSize = nMinHeight;
		}
    inline BOOL GetPositionAbsolute() 							//Retrieve the position absolute flag.
		{
			return m_bPositionAbsolute;
		} 
	inline int  GetItemTop()									//Retrieve the rectItem.top member,							
		{
			return m_rectItem.top;
		}
	inline int  GetItemLeft()									//Retrieve the rectItem.left member, 			            
		{
			return m_rectItem.left;
		}
	inline int  GetItemRight()									//Retrieve the rectItem.right member,                    
		{
			return m_rectItem.right;
		}
	inline int  GetItemBottom()       							//Retrieve the rectItem.bottom member,         
		{
			return m_rectItem.bottom;
		}
	inline int  GetItemWidth()                    				//Retrieve the rectItem width member,
		{
			return m_rectItem.right - m_rectItem.left;
		}
	inline int  GetItemHeight()                  				//Retrieve the rectItem height member,
		{
			return m_rectItem.bottom - m_rectItem.top;
		}
	inline int  GetItemMinHeight()			            		//Retrieve the minimum rectItem height member,
		{
			return m_nMinSize;
		}
//}}GW_MEMBERS	

//Overrideables
//GW_MEMBERS{{(CGWReportItem,"Overrideables")
public:
    virtual BOOL CarriesOverToNextPage() 						//Specifes whether an item can carry over a page boundary.			
		{
			return m_bGoToNextPage;
		}
	virtual CExtraData*  GetExtraData(CRect m_rectAbsolute)		//Retrieves an extra data item for this report item.
		{
			return new CExtraData(m_rectAbsolute);
		}
	virtual CRect CalcRectItem(CDC* pDC);						//Calc the device unit coordinates for this item.
	virtual BOOL DrawItem(CDC* pDC, CExtraData* pExtraData)		//Draw the item.
		{
			return TRUE;
		}   //Implement this if you want to draw something.
	virtual void OnBeginPaginate()								//Signals the beginning of pagination for this item.
		{};
	virtual void OnUpdateCurrentPosition(CPoint point)			//Updates the current position for the overall report.
		{
			m_pGWReport->SetCurrentPosition(point);
		}
    virtual BOOL OnCreate(CDC* pDC, CRect rectItem)				//Called to provide design-time property settings.
		{
			return TRUE;
		}
//}}GW_MEMBERS	

//Inline properties sets
//GW_MEMBERS{{(CGWReportItem,"Inline Property Sets")
	inline void GW_PAGECARRYOVER(BOOL bPageCarryOver) 			//Sets the page carryover flag.
		{
			SetPageCarryover(bPageCarryOver);
		}
	inline void GW_POSITIONABSOLUTE(BOOL bPositionAbsolute) 	//Sets the position absolute flag.
		{
			SetPositionAbsolute(bPositionAbsolute);
		}
    inline void GW_ITEMTTOP(int nTop)							//Sets the item top in MM_LOENGLISH units.
		{
			SetItemTop(nTop);
		}
    inline void GW_ITEMLEFT(int nLeft)                          //Sets the item left in MM_LOENGLISH units.
		{
			SetItemLeft(nLeft);
		}
    inline void GW_ITEMWIDTH(int nWidth)                        //Sets the item width in MM_LOENGLISH units.
		{
			SetItemWidth(nWidth);
		}
    inline void GW_ITEMHEIGHT(int nHeight)                      //Sets the item height in MM_LOENGLISH units.
		{
			SetItemHeight(nHeight);
		}
    inline void GW_ITEMMINHEIGHT(int nMinHeight)                //Sets the item minimum height in MM_LOENGLISH units.
		{
			SetItemMinHeight(nMinHeight);
		}
//}}GW_MEMBERS	
};

class GW_EXT_CLASS CGWGridWizGridItem : public CGWReportItem
{
//GW_CLASS{{(CGWGridWizGridItem)
/*

The CGWGridWizGridItem is used to print a CGWGridRpt object. This CGWGridRpt object can be attached to a screen grid,
or a standalone CGWGridRpt object. We using a CGWGridRpt which is attached to a screen grid, the m_pDataGrid member 
of CGWGridRpt must be set to the address of the screen grid. Typically, you will override CGWGridWizGridItem:: GetGridRpt() 
and either create the stand-alone CGWGridRpt in this function or create the CGWGridRpt and attach to a screen grid as 
follows:

	CGWGridRpt* CReportGrid1::GetGridRpt(CDC* pDC)
	{
		//Either create a new generic CGWGridRpt or create one
		//which you used the Wizard on. In this case, since
		//we are going to print a screen grid, a generic one will do.
    		m_pGridRpt = new CGWGridRpt;

		//Need to have access to the screen grid which we want to print.
		//So created an embedded member in the CGWReport Object and passed
		//in the screen grids address to m_pGrid.
		CDBReport* pRpt = (CDBReport*) m_pGWReport;

		//Call the CGWGridRpt::Attach() method with a CGWGrid pointer to 
		//attach this CGWGridRpt object to a screen grid. It will basically
		//copy the innformation from the screen grid into the CGWGridRpt
		//Object. 
		m_pGridRpt->Attach(pDC, pRpt->m_pGrid);

   		 return m_pGridRpt;
	} 

The previous example used a CGWGridRpt which was attached to a screen grid. If we wanted to use a standalone CGWGridRpt 
which we created using the Wizard, we would have the following code segment:  

	CGWGridRpt* CReportGrid2::GetGridRpt(CDC* pDC)
	{
		//Either create a new generic CGWGridRpt or create one
		//which you used the Wizard on. In this case, we will use one we created
		//with the Wizard.
    		m_pGridRpt = (CGWGridRpt*) new CMyGridRpt;

		//Call the CGWGridRpt::GridOnIntialUpdate() method with a CDC* pointer.
		m_pGridRpt->GridOnInitialUpdate(pDC);

   		 return m_pGridRpt;
	} 

Implement CMyGridRpt as you would any other CGWGrid derived class.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWGridWizGridItem)
public:              
//GW_MEMBERS{{(CGWGridWizGridItem,"Construction")
	CGWGridWizGridItem();											//Default Constructor.
	~CGWGridWizGridItem();											//Default Destructor.
	CGWGridWizGridItem(CGWReport* pGWReport, CGWGridRpt* pGridRpt);	//Constructs a CGWGridWizGridItem from a report object and a CGWGridRpt object.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridWizGridItem,"Data Members")
	CGWGridRpt* m_pGridRpt;			//The grid used for drawing the report.
	BOOL m_bDefaultGrid;			//Indicates this object owns the default grid so it gets deleted it in the destructor;
	int m_nPaginatedPages;			//Used to keep track of the pages created during CGridRpt::Paginate.
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWGridWizGridItem,"Operations")
	void AttachScreenGrid(CGWGrid* pGrid);						//Attaches a screen grid to the default grid report.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridWizGridItem,"Operations")
	virtual BOOL DrawItem(CDC* pDC, CExtraData* pExtraData);	//Draws the grid into the report.
	virtual CGWGridRpt* GetGridRpt(CDC* pDC);					//Retrieves a pointer to the grid report.
    virtual BOOL OnCreate(CDC* pDC, CRect rectItem);			//Called when the CGWGridWizGridItem is created.
	virtual CExtraData*  GetExtraData(CRect rectAbsolute);		//Called to retrieve an CGridExtraData object.
	virtual CRect CalcRectItem(CDC* pDC);						//Calculates the size of the report item.
//}}GW_MEMBERS	
};                   


class GW_EXT_CLASS CGWTextItem : public CGWReportItem
{
//GW_CLASS{{(CGWTextItem)
/*

The CTextItem class derives from CReportItem and adds the ability to print variable length text. The text can be specified 
when the report is created by overriding a virtual function. Text is automatically paginated. CTextItems can be used in Headers 
for report titles and sub-titles. They can be used to display dates and other fields. The CTextItem class has several data 
members which keep track of the default font for the item. However, you can override the CTextItem::DrawItem() virtual function 
and change any aspect of the device context.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWTextItem)
public:
//GW_MEMBERS{{(CGWTextItem,"Construction")
    CGWTextItem();														//Default Constructor.
	CGWTextItem(CGWReport* pGWReport, CString csText, UINT nFormat);	//Constructs a CGWTextItem and assigns the text buffer and formating options.
//}}GW_MEMBERS	

public:              
//GW_MEMBERS{{(CGWTextItem,"Data Members")
	CString m_csText;						//The text buffer holding the text to print.
    UINT m_nFormat;							//The formating string to be applied to the output.
    LOGFONT m_LogFont;						//The logfont structure to be used to build the font.
    int m_nPointSize;						//The font point size to be used.
	COLORREF m_rgbTextColor;				//The text color.
	COLORREF m_rgbBackColor;				//The back color.
	int m_nStartLoc;						//The location within the text buffer to start printing.
	int m_nBreakLoc;						//The location within the text buffer to break to a new page.
//}}GW_MEMBERS	
    
//Implementation
protected:
//GW_MEMBERS{{(CGWTextItem,"Implementation")
	int FindBreakLoc(CDC* pDC, CRect& rectDraw, int nLimit);	//Find the word to break on, given the remaining space on the page.
	int SetTextBottom(CRect& rectDraw, CDC* pDC);				//Set the bottom coordinates of the draw rectangle.
	CString GetNextWord(CString& csText, int& nBreakLoc);		//Iterates through the text search for a break.
//}}GW_MEMBERS	

//Overrideables
protected:
//GW_MEMBERS{{(CGWTextItem,"Overrideables")
    virtual void OnGetTextItem(CString& csText)					//Called to retrieve the text to be printed. Called at pagination time.
		{
			m_csText = csText;
		}
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWTextItem,"Overriden Virtual Functions")
	virtual CExtraData*  GetExtraData(CRect rectAbsolute);		//Called to retrieve a CTextExtraData object.
	virtual CRect CalcRectItem(CDC* pDC);						//Called to calculate the device point coordinates for the report item.
	virtual BOOL DrawItem(CDC* pDC, CExtraData* pExtraData);	//Called to draw this item.
	virtual void OnBeginPaginate()								//Called to signal the beginning of the pagination phase.
		{
			m_nBreakLoc = m_nStartLoc = 0;
		}
//}}GW_MEMBERS	

//Member access functions
public:
//GW_MEMBERS{{(CGWTextItem,"Member Access Functions")
	void SetTextFont(LOGFONT* pLogFont)						//Set the LogFont for this item.
		{
			m_LogFont = *pLogFont;
		}
	inline COLORREF GetBackColor() 							//Get the back color for this item.
		{
			return m_rgbBackColor;
		}
	inline BOOL GetFontBold() 								//Get the Font Bold flag for this item.
		{
			return m_LogFont.lfWeight == FW_BOLD;
		}
	inline _TCHAR*  GetFontFaceName() 						//Get the Font Face name for this item.
		{
			return m_LogFont.lfFaceName;
		}
	inline BOOL GetFontItalic() 							//Get the Font Italic flag for this item.
		{
			return m_LogFont.lfItalic;
		}
	inline int GetFontPointSize() 							//Get the Font PointSize for this item.
		{
			return m_nPointSize;
		}
	inline COLORREF GetTextColor() 							//Get the text color for this item.
		{
			return m_rgbTextColor;
		}
	inline const _TCHAR* GetText()							//Get the text string for this item.,
		{
			return m_csText;
		}
	inline UINT GetFormat()									//Get the format string for this item.
		{
			return m_nFormat;
		}
	inline void SetBackColor(COLORREF clrf)                 //Set the back color for this item.
		{
			m_rgbBackColor = clrf;
		}
	inline void SetFontBold(BOOL bFontBold)                 //Set the font bold for this item.
		{
			m_LogFont.lfWeight = (bFontBold) ? FW_BOLD : FW_NORMAL;
		}	
	inline void SetFontFaceName(_TCHAR* lpszFaceName)       //Set the font face name for this item.
		{
			_tcsncpy(m_LogFont.lfFaceName, lpszFaceName,LF_FACESIZE - 1);
		}
	inline void SetFontItalic(BOOL bFontItalic)				//Set the font italic flag for this item.
		{
			m_LogFont.lfItalic = (unsigned char) bFontItalic;
		}
	inline void SetFontPointSize(int nFontPointSize)        //Set the font point size for this item.
		{
			m_LogFont.lfHeight = nFontPointSize;
			m_nPointSize = nFontPointSize;
		}
	inline void SetTextColor(COLORREF clrf)                 //Set the font text color for this item.
		{
			m_rgbTextColor = clrf;
		}
	inline void SetText(const _TCHAR* lpszText)             //Set the text value for this item.
		{
			m_csText = lpszText;
		}
	inline void SetFormat(UINT nFormat)                     //Set the output format for this item.
		{
			m_nFormat = nFormat;
		}
//}}GW_MEMBERS	

//inline properties sets
protected:
//GW_MEMBERS{{(CGWTextItem,"Inline Properties Sets")
	inline void GW_BACKCOLOR(COLORREF clrf) 				//Sets the backcolor for this item.
		{
			SetBackColor(clrf);
		}
	inline void GW_FONTBOLD(BOOL bFontBold)                 //Sets the font bold flag for this item.
		{
			SetFontBold(bFontBold);
		}
	inline void GW_FONTFACENAME(_TCHAR* lpszFaceName)      	//Sets the font facename for this item.
		{
			SetFontFaceName(lpszFaceName);
		}
	inline void GW_FONTITALIC(BOOL bFontItalic)             //Sets the font italic flag for this item.
		{
			SetFontItalic(bFontItalic);
		}
	inline void GW_FONTPOINTSIZE(int nFontPointSize)        //Sets the font pointsize for this item.
		{
			SetFontPointSize(nFontPointSize);
		}
	inline void GW_TEXTCOLOR(COLORREF clrf)                 //Sets the text color for this item.
		{
			SetTextColor(clrf);
		}
	inline void GW_ITEMTEXT(const _TCHAR* lpszText)         //Sets the text for this item.
		{
			SetText(lpszText);
		}  
	inline void GW_TEXTSTYLE(UINT nFormat)                  //Sets the text output style for this item.
		{
			SetFormat(nFormat);
		}
//}}GW_MEMBERS	

};


class GW_EXT_CLASS CGWBorderItem : public CGWReportItem
{
//GW_CLASS{{(CGWBorderItem)
/*

The CBorderItem class can be used to draw a rectangular border around a section or within a section. The most 
common use is to have a border for the report header and footer. The border can be filled and have a shadow. 
You will use the Wizard to create new CBorderItem classes and to select virtual functions and provide property 
settings. 

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWBorderItem)
public:              
//GW_MEMBERS{{(CGWBorderItem,"Construction")
	CGWBorderItem();							//Default Constructor.
	CGWBorderItem(CGWReport* pGWReport, LOGPEN* pLogPen, COLORREF rgBackground, CSize& sizeShadowBorder);       //Creates a CGWBorderItem object and specifies it data memebers.
//}}GW_MEMBERS	

//Attributes

//GW_MEMBERS{{(CGWBorderItem,"Data Members")
	COLORREF m_rgbBackground;					//The backgroud color for this item.
	COLORREF m_rgbShadowColor;					//The shadow color for this item.
	LOGPEN 	 m_LogPen;							//The LogPen structure used to build the pen.
	CSize    m_sizeShadowBorder;				//The size of the shadow border.
//}}GW_MEMBERS	

//Overrides
protected:
//GW_MEMBERS{{(CGWBorderItem,"Overriden Virtual Functions")
	virtual BOOL DrawItem(CDC* pDC, CExtraData* pExtraData);	//Overriden to take over the drawing of this item.
	virtual CRect CalcRectItem(CDC* pDC);						//Calculate the device coordinate size of this item.
	virtual void OnUpdateCurrentPosition(CPoint point)			//Updates the position to begin printing the next item.
		{};
//}}GW_MEMBERS	

//Member access functions
public:
//GW_MEMBERS{{(CGWBorderItem,"Overriden Virtual Functions")
	inline COLORREF GetBackColor() 							//Get the backcolor for this item.
		{return m_rgbBackground;}
	inline UINT GetPenStyle()                 				//Get logpen style for this item.
		{return m_LogPen.lopnStyle;}
	inline int GetPenWidth(int nWidth)                  	//Get the pen width for this item.
		{return m_LogPen.lopnWidth.x;}
	inline COLORREF GetPenColor(COLORREF clrf)              //Get the pen color for this item.
		{return m_LogPen.lopnColor;}
	inline int GetShadowHeight(int nHeight)              	//Get the shadow height for this item.
		{return m_sizeShadowBorder.cy;}
	inline int GetShadowWidth(int nWidth)                 	//Get the shadow width fot this item.
		{return m_sizeShadowBorder.cx;}
	inline COLORREF GetShadowColor(COLORREF clrf)           //Get the shadow color for this item.
		{return m_rgbShadowColor;}
	inline void SetBackColor(COLORREF clrf)                 //Set the backcolor for this item.
		{m_rgbBackground = clrf;}
	inline void SetPenStyle(UINT nPenStyle)                 //Set logpen style for this item.
		{m_LogPen.lopnStyle = nPenStyle;}
	inline void SetPenWidth(int nWidth)                  	//Set the pen width for this item.
		{m_LogPen.lopnWidth.x = nWidth;}
	inline void SetPenColor(COLORREF clrf)                  //Set the pen color for this item.
		{m_LogPen.lopnColor = clrf;}
	inline void SetShadowHeight(int nHeight)              	//Set the shadow height for this item.
		{m_sizeShadowBorder.cy = nHeight;}
	inline void SetShadowWidth(int nWidth)                 	//Set the shadow width for this item.
		{m_sizeShadowBorder.cx = nWidth;}
	inline void SetShadowColor(COLORREF clrf)               //Set the shadow color for this item.
		{m_rgbShadowColor = clrf;}
//}}GW_MEMBERS	

//inline properties sets
protected:
//GW_MEMBERS{{(CGWBorderItem,"Inline Properties Sets")
	inline void GW_BACKCOLOR(COLORREF clrf) 				//Set the backcolor for this item.
		{SetBackColor(clrf);}
	inline void GW_PENSTYLE(UINT nPenStyle)                 //Set logpen style for this item.
		{SetPenStyle(nPenStyle);}
	inline void GW_PENWIDTH(int nPenWidth)                  //Set the pen width for this item.
		{SetPenWidth(nPenWidth);}  
	inline void GW_PENCOLOR(COLORREF clrf)					//Set the pen color for this item.
		{SetPenColor(clrf);}
	inline void GW_SHADOWHEIGHT(int nShadowHeight)          //Set the shadow height for this item.
		{SetShadowHeight(nShadowHeight);}
	inline void GW_SHADOWWIDTH(int nShadowWidth)            //Set the shadow width for this item.
		{SetShadowWidth(nShadowWidth);}
	inline void GW_SHADOWCOLOR(COLORREF clrf)               //Set the shadow color for this item.
		{SetShadowColor(clrf);}
//}}GW_MEMBERS	
};

class CGWDIB;
class GW_EXT_CLASS CGWBitmapItem : public CGWReportItem
{
//GW_CLASS{{(CGWBitmapItem)
/*

The CBitmap item can be used to print GDI device dependent bitmaps or DIB device independent bitmaps. This report 
item works by sending bitmaps directly to the device in DIB format. There are two helper classes, CGWDIB and CGWDIBPal 
which are used in conjunction with CBitmapItem accomplish this. The CGWDIB and CGWDIBPal classes are implemented in 
GWDIB.CPP and are only required if you are using the CBitmapItem.  To use the CBitmapItem class, create a new 
CBitmapItem derived class using the Wizard and override the OnCreate() method. From there, call one of the overloaded 
SetBitmap() methods as follows:


	BOOL CPageBmp::OnCreate(CDC* pDC, CRect rectItem)
	{
		//In order to print a bitmap, you need to initialize the Bitmap items'
		//CGWDIB member by calling one of the six overridden SetBitmap functions
		
		//You can use a CBitmap object
		//CBitmap bmpDog;
		//bmpDog.LoadBitmap(IDB_DOG);
		//return SetBitmap(&bmpDog);

		//Or you can use a resource id to a bitmap;
		return SetBitmap(IDB_DOG);

		//Or you can use a device context which holds a bitmap;
		//CDC* pNewDC = new CDC;
		//pNewDC->CreateCompatibleDC(pDC);
		//CBitmap bmpDog;
		//bmpDog.LoadBitmap(IDB_DOG);
		//CBitmap* pOldBitmap = (CBitmap*) pNewDC->SelectObject(&bmpDog); 
		//BOOL bRC = SetBitmap(pNewDC);
		//pNewDC->SelectObject(pOldBitmap);
		//delete pNewDC;
		//return bRC;
		
		//Or you can send it an open CFile object
		//CFile bmpFile("dog.bmp", CFile::modeRead | CFile::shareDenyNone);
		//if (bmpFile.m_hFile == CFile::hFileNull)       
		//	return FALSE; 
		//return SetBitmap(&bmpFile);

		//Or you can send it the path to a file name
		//return SetBitmap("dog.bmp");
	}

*/
//}}GW_CLASS	


	DECLARE_DYNCREATE(CGWBitmapItem)
public:              
//GW_MEMBERS{{(CGWBitmapItem,"Construction")
	CGWBitmapItem();										//Defualt Constructor.
	CGWBitmapItem(CGWReport* pGWReport,CBitmap* pBitmap);	//Construct a CGWBitmapItem object and specify the MFC CBitmap object.
	virtual ~CGWBitmapItem();								//Defualt Destructor.
//}}GW_MEMBERS	
  
//Operations
public:
//GW_MEMBERS{{(CGWBitmapItem,"Operations")
	BOOL SetBitmap(CGWDIB* pGWDIB)							//Assigns the bitmap from a CGWDIB object.
		{m_pGWDIB = pGWDIB; return TRUE;}
	BOOL SetBitmap(CBitmap* pBitmap);						//Assigns the bitmap from a MFC CBitmap object.
	BOOL SetBitmap(CDC* pDC);								//Assigns the bitmap from a bitmap selected into a MFC CDC object.
	BOOL SetBitmap(CFile* pFile); 							//Assigns the bitmap from a MFC CFile object.
	BOOL SetBitmap(CString lpszFilePath);					//Assigns the bitmap from a file specified by its path.
	BOOL SetBitmap(UINT nID);								//Assigns the bitmap from a bitmap resource.
//}}GW_MEMBERS	

//Attributes
protected:
//GW_MEMBERS{{(CGWBitmapItem,"Data Members")
	CGWDIB* m_pGWDIB;										//The working CGWDIB object.
//}}GW_MEMBERS	

//Overrides
protected:
//GW_MEMBERS{{(CGWBitmapItem,"Overriden Virtual Functions")
	virtual CRect CalcRectItem(CDC* pDC);						//Calculates the device unit coordinates for the size and location of this object.
	virtual BOOL DrawItem(CDC* pDC, CExtraData* pExtraData);	//Overriden to take over the drawing of the item.
//}}GW_MEMBERS	
};


class GW_EXT_CLASS CGWPageNumber : public CGWTextItem
{
//GW_CLASS{{(CGWPageNumber)
/*

The CPageNumber report item is specialization of the CTextItem. Its purpose is print the current page number for the report. 
You can still override the GetText() method to specify the string or use the Wizard to set string to be used. The default 
is 'Page '.

*/
//}}GW_CLASS	
	DECLARE_DYNCREATE(CGWPageNumber)
public:
//GW_MEMBERS{{(CGWPageNumber,"Construction")
	CGWPageNumber(CGWReport* pGWReport, CString csText, UINT nFormat);  //Construct a CGWPageNumber object and specify the text for this item.    
	CGWPageNumber()														//Default Constructor.
		{
			m_bGoToNextPage = FALSE; 
		}
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWPageNumber,"Overriden Virtual Functions")
	virtual BOOL DrawItem(CDC* pDC, CExtraData* pExtraData);	//Overriden to take over the drawing of the item.
//}}GW_MEMBERS	
};


class GW_EXT_CLASS CGWPageBreakItem : public CGWReportItem
{
//GW_CLASS{{(CGWReportItem)
/*

The CPageBreakItem is a specialization of CReportItem. It does not override DrawItem() so it is not visible. Its sole 
purpose is to cause the paginate process to jump to the next page.

*/
//}}GW_CLASS	
	DECLARE_DYNCREATE(CGWPageBreakItem)
public:              
//GW_MEMBERS{{(CGWPageBreakItem,"Construction")
	CGWPageBreakItem()											//Default Constructor.
		{
			m_bGoToNextPage = FALSE; 
		}
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWPageBreakItem,"Overriden Virtual Functions")
	virtual CRect CalcRectItem(CDC* pDC)						//Calculates the device unit coordinates for the size and location of this object.
		{
			return CRect(0,0,0,0);
		}
//}}GW_MEMBERS	
};


//GW_MACROS{{(ADDHEADER,"Adds a report item to the header section of a report. This macro is only valid within the special comment block markers in the BuildPageLayout function of your CGWReport based class.")
#define ADDHEADER(ReportItemClass)										 				\
			pRuntimeClass  =   RUNTIME_CLASS(ReportItemClass);           				\
			pReportItem = (CGWReportItem*) pRuntimeClass->CreateObject();					\
			pReportItem->m_pGWReport = this;                                            \
			SectionTopLeft = CPoint(0,0);                                               \
			if (pReportItem->GetPositionAbsolute())                                     \
				SectionTopLeft  = m_rectHeader.TopLeft();                               \
			if (pReportItem->m_rectItem.right == CGWReportItem::PageWidth)                \
				pReportItem->m_rectItem.right = m_rectHeader.right;					\
			if (pReportItem->m_rectItem.bottom == CGWReportItem::SectionHeight)           \
				pReportItem->m_rectItem.bottom = m_rectHeader.Height();				    \
			rectItem.SetRect(SectionTopLeft.x + pReportItem->m_rectItem.left,           \
							 SectionTopLeft.y + pReportItem->m_rectItem.top,            \
							 pReportItem->m_rectItem.right,       					    \
	                         pReportItem->m_rectItem.bottom);                           \
	        pReportItem->SetItemRect(rectItem, pDC, HEADER);                             \
			if (pReportItem->OnCreate(pDC, pReportItem->m_rectItem))                    \
				AddHeaderItem(pReportItem);                                                 
//}}GW_MACROS

//GW_MACROS{{(ADDBODY,"Adds a report item to the body section of a report. This macro is only valid within the special comment block markers in the BuildReportLayout function of your CGWReport based class.")
#define ADDBODY(ReportItemClass)										 				\
			pRuntimeClass  =   RUNTIME_CLASS(ReportItemClass);           				\
			pReportItem = (CGWReportItem*) pRuntimeClass->CreateObject();					\
			pReportItem->m_pGWReport = this;                                            \
			SectionTopLeft = CPoint(0,0);                                               \
			if (pReportItem->GetPositionAbsolute())                                     \
				SectionTopLeft  = m_rectReportBody.TopLeft();	                        \
			if (pReportItem->m_rectItem.right == CGWReportItem::PageWidth)                \
				pReportItem->m_rectItem.right = m_rectReportBody.right;				\
			if (pReportItem->m_rectItem.bottom == CGWReportItem::SectionHeight)           \
				pReportItem->m_rectItem.bottom = m_rectReportBody.Height();				\
			rectItem.SetRect(SectionTopLeft.x + pReportItem->m_rectItem.left,           \
							 SectionTopLeft.y + pReportItem->m_rectItem.top,            \
							 pReportItem->m_rectItem.right,       					    \
	                         pReportItem->m_rectItem.bottom);                           \
	        pReportItem->SetItemRect(rectItem, pDC, BODY);                               \
			if (pReportItem->OnCreate(pDC, pReportItem->m_rectItem))                    \
				AddReportItem(pReportItem);    
//}}GW_MACROS

//GW_MACROS{{(ADDFOOTER,"Adds a report item to the footer section of a report. This macro is only valid within the special comment block markers in the BuildPageLayout function of your CGWReport based class.")
#define ADDFOOTER(ReportItemClass)										 				\
			pRuntimeClass  =   RUNTIME_CLASS(ReportItemClass);           				\
			pReportItem = (CGWReportItem*) pRuntimeClass->CreateObject();					\
			pReportItem->m_pGWReport = this;                                            \
			SectionTopLeft = CPoint(0,0);                                               \
			if (pReportItem->GetPositionAbsolute())                                     \
				SectionTopLeft  = m_rectFooter.TopLeft();	                        	\
			if (pReportItem->m_rectItem.right == CGWReportItem::PageWidth)                \
				pReportItem->m_rectItem.right = m_rectFooter.right;				    \
			if (pReportItem->m_rectItem.bottom == CGWReportItem::SectionHeight)           \
				pReportItem->m_rectItem.bottom = m_rectFooter.Height();				    \
			rectItem.SetRect(SectionTopLeft.x + pReportItem->m_rectItem.left,           \
							 SectionTopLeft.y + pReportItem->m_rectItem.top,            \
							 pReportItem->m_rectItem.right,       					    \
	                         pReportItem->m_rectItem.bottom);                           \
	        pReportItem->SetItemRect(rectItem, pDC, FOOTER);                             \
			if (pReportItem->OnCreate(pDC, pReportItem->m_rectItem))                    \
				AddFooterItem(pReportItem);    
//}}GW_MACROS


#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif  //__GWREPORT_H__   
