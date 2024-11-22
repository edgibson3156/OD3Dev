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
// grid.h : header file
//
#ifndef __GRID_H__
#define __GRID_H__

#ifdef _WIN32
#if !defined( _BASETYPS_H_ )
#include <BaseTyps.h>
#endif
#include <oleauto.h>
#endif


#ifndef _WIN32
#ifndef _VARIANT_H_ 
#define _VARIANT_H_   

enum VARENUM
{
    VT_EMPTY           = 0,   /* [V]   [P]  nothing                     */
    VT_NULL            = 1,   /* [V]        SQL style Null              */
    VT_I2              = 2,   /* [V][T][P]  2 byte signed int           */
    VT_I4              = 3,   /* [V][T][P]  4 byte signed int           */
    VT_R4              = 4,   /* [V][T][P]  4 byte real                 */
    VT_R8              = 5,   /* [V][T][P]  8 byte real                 */
    VT_CY              = 6,   /* [V][T][P]  currency                    */
    VT_DATE            = 7,   /* [V][T][P]  date                        */
    VT_BSTR            = 8,   /* [V][T][P]  binary string               */
    VT_DISPATCH        = 9,   /* [V][T]     IDispatch FAR*              */
    VT_ERROR           = 10,  /* [V][T]     SCODE                       */
    VT_BOOL            = 11,  /* [V][T][P]  True=-1, False=0            */
    VT_VARIANT         = 12,  /* [V][T][P]  VARIANT FAR*                */
    VT_UNKNOWN         = 13,  /* [V][T]     IUnknown FAR*               */

    VT_I1              = 16,  /*    [T]     signed char                 */
    VT_UI1             = 17,  /*    [T]     unsigned char               */
    VT_UI2             = 18,  /*    [T]     unsigned short              */
    VT_UI4             = 19,  /*    [T]     unsigned short              */
    VT_I8              = 20,  /*    [T][P]  signed 64-bit int           */
    VT_UI8             = 21,  /*    [T]     unsigned 64-bit int         */
    VT_INT             = 22,  /*    [T]     signed machine int          */
    VT_UINT            = 23,  /*    [T]     unsigned machine int        */
    VT_VOID            = 24,  /*    [T]     C style void                */
    VT_HRESULT         = 25,  /*    [T]                                 */
    VT_PTR             = 26,  /*    [T]     pointer type                */
    VT_SAFEARRAY       = 27,  /*    [T]     (use VT_ARRAY in VARIANT)   */
    VT_CARRAY          = 28,  /*    [T]     C style array               */
    VT_USERDEFINED     = 29,  /*    [T]     user defined type	        */
    VT_LPSTR           = 30,  /*    [T][P]  null terminated string      */
    VT_LPWSTR          = 31,  /*    [T][P]  wide null terminated string */

    VT_FILETIME        = 64,  /*       [P]  FILETIME                    */
    VT_BLOB            = 65,  /*       [P]  Length prefixed bytes       */
    VT_STREAM          = 66,  /*       [P]  Name of the stream follows  */
    VT_STORAGE         = 67,  /*       [P]  Name of the storage follows */
    VT_STREAMED_OBJECT = 68,  /*       [P]  Stream contains an object   */
    VT_STORED_OBJECT   = 69,  /*       [P]  Storage contains an object  */
    VT_BLOB_OBJECT     = 70,  /*       [P]  Blob contains an object     */
    VT_CF              = 71,  /*       [P]  Clipboard format            */
    VT_CLSID           = 72   /*       [P]  A Class ID                  */
};


typedef unsigned short VARTYPE;
struct tagVARIANT{
    VARTYPE vt;
    unsigned short wReserved1;
    unsigned short wReserved2;
    unsigned short wReserved3;
    union {
      short	   iVal;             /* VT_I2                */
      long	   lVal;             /* VT_I4                */
      float	   fltVal;           /* VT_R4                */
      double	   dblVal;           /* VT_R8                */
      BOOL     bool;                 /* VT_BOOL              */
      void	   FAR* byref;	     /* Generic ByRef        */
    }; 
    };
typedef struct tagVARIANT VARIANT;
#endif
#endif

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

#ifndef INT_MAX
#define INT_MAX  32767
#endif 
#define SB_NONE			    4


//GW_CONSTANTS{{("SetCurrentCell")
#define SCC_NO_SCROLL 0		//If the specified cell is currently displayed in the view, it will be selected without changing scroll position of the view. If it is not in the view, it will be scrolled into view.
#define SCC_SCROLL 1		//Always scroll the specifies Cell to the top of the view.
#define SCC_NEVER_SCROLL 2	//Never change the scroll position of the view.
//}}GW_CONSTANTS

#ifndef DOCKEDROW
//GW_CONSTANTS{{("Docked Rows and Columns")
#define DOCKEDROW  (INT_MAX - 1)		//Set to maximum integer -1 one. This would represent the last docked row. The previous one, if any, would be INT_MAX -2.
#define DOCKEDCOLUMN  (INT_MAX - 1)		//Set to maximum integer -1 one. This would represent the last docked column. The previous one, if any, would be INT_MAX -2.
//}}GW_CONSTANTS
#endif

//GW_CONSTANTS{{("RecalcGridLayout hints")
#define RGL_FULL       		0	//Full recalculate destroys and recreates all visible GCOs
#define RGL_VSCROLL 		1	//Removes one line of GCOs from top or bottom and adds a new one on top or bottom.
#define RGL_HSCROLL 		2	//Removes one column of GCOs from left or right and adds a new one on left or right.
#define RGL_ADDLINE 		3	//Adds a new row of GCOs to the end.
#define RGL_INSERTLINE      4	//Inserts a row of GCOs into the middle.
#define RGL_CALCONLY		5	//Calculates but does not destroy any GCOs.
//}}GW_CONSTANTS

//GW_CONSTANTS{{("Text and bitmap alignment constants")
#define GW_JUSTIFY_LEFT     0x0001
#define GW_JUSTIFY_CENTER   0x0002
#define GW_JUSTIFY_RIGHT    0x0004
#define GW_JUSTIFY_TOP      0x0008
#define GW_JUSTIFY_VCENTER  0x0010
#define GW_JUSTIFY_BOTTOM   0x0020
#define GW_STRETCH			0x0040
//}}GW_CONSTANTS

//GW_CONSTANTS{{("Tab key handling style constants")
#define GW_DISABLE_TAB		0x0000	//Tab between cells is disabled.
#define GW_WANT_TAB			0x0001	//Grid will capture tab.
#define GW_TAB_WRAP			0x0003	//Tab will wrap from end of line to new line.
#define GW_TAB_OUT			0x0005	//Tab will goto next control in tab order after tabbing out of last cell.
//}}GW_CONSTANTS


//GW_CONSTANTS{{("Mouse Button identifiers")
#define gwLeftButton 1		//Left mouse button is down
#define gwRightButton 2		//Right mouse button is down
#define gwMiddleButton 4	//Middle mouse buttom is down
//}}GW_CONSTANTS

//GW_CONSTANTS{{("Keyboard masks for Mouse events")
#define gwShiftMask 1		//Left mouse button is down
#define gwCtrlMask 2		//Right mouse button is down
#define gwAltMask 4			//Middle mouse buttom is down
//}}GW_CONSTANTS

class CGWGridCellObject;
class CGWGridRpt;  
class CGWGridPopup;
class CGWDropTarget;
class COleDataSource;


//WM_NOTIFY strutures
#ifdef _WIN32
//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent to notify of a WM_KEYDOWN, WM_KEYUP and WM_CHAR messages.")
typedef struct tagGW_CELLCHAR {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected row.
	int nColNdx;						//Col index of affected column.
    CGWGridCellObject* pGCO;			//Address of GCO
	UINT nChar;							//The character that was entered.
	UINT nRepCnt;						//Repeat count.
	UINT nFlags;						//Keyboard flags.
} GW_CELLCHAR;
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that a particular cell was clicked. This message is sent from the CGWGridCtrl implementation OnCellClick.")
typedef struct tagGW_CELLCLICK {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected row.
	int nColNdx;						//Col index of affected column.
    CGWGridCellObject* pGCO;			//Address of GCO
} GW_CELLCLICK;	
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that a particular cell was double clicked. This message is sent from the CGWGridCtrl implementation OnCellDblClick.")
typedef struct tagGW_CELLDBLCLK {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected row.
	int nColNdx;						//Col index of affected column.
    CGWGridCellObject* pGCO;			//Address of GCO.
} GW_CELLDBLCLK;
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that a GCO has created an embedded control. This message is sent from the CGWGridCtrl implementation OnCellCreateHwnd.")
typedef struct tagGW_CELLCREATEHWND {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected row.
	int nColNdx;						//Col index of affected column.
    CGWGridCellObject* pGCO;			//Address of GCO.
	CWnd* pFloatingCtrl;				//Address of embedded CWnd control.
	LPDISPATCH pIDispatch;				//Address of IDispatch interface if embedded control is an OCX.
} GW_CELLCREATEHWND;
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that a GCO is destroying the embedded control. This message is sent from the CGWGridCtrl implementation OnCellDestroyHwnd.")
typedef struct tagGW_CELLDESTROYHWND {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected row.
	int nColNdx;						//Col index of affected column.
    CGWGridCellObject* pGCO;			//Address of GCO.
	CWnd* pFloatingCtrl;				//Address of embedded CWnd control.
	LPDISPATCH pIDispatch;				//Address of IDispatch interface if embedded control is an OCX.
} GW_CELLDESTROYHWND;
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that a GCO is deactivating and hiding the embedded control. This message is sent from the CGWGridCtrl implementation OnCellDestroyHwnd.")
typedef struct tagGW_CELLDEACTIVATE {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected column.
	int nColNdx;						//Col index of affected column.
    CGWGridCellObject* pGCO;			//Address of GCO.
	CWnd* pFloatingCtrl;				//Address of embedded CWnd control.
	LPDISPATCH pIDispatch;				//Address of IDispatch interface if embedded control is an OCX.
} GW_CELLDEACTIVATE;
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that a GCO is activating and showing the embedded control. This message is sent from the CGWGridCtrl implementation OnCellDestroyHwnd.")
typedef struct tagGW_CELLACTIVATE {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected row.
	int nColNdx;						//Col index of affected column.
    CGWGridCellObject* pGCO;			//Address of GCO.
	CWnd* pFloatingCtrl;				//Address of embedded CWnd control.
	LPDISPATCH pIDispatch;				//Address of IDispatch interface if embedded control is an OCX.
} GW_CELLACTIVATE;
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that a Grid sheet is being activated.")
typedef struct tagGM_ACTIVATESHEET {
    NMHDR hdr;							//Notify Message Header structure.
	int nSheetNdx;						//Index of sheet being activated.
} GM_ACTIVATESHEET;
//}}GW_STRUCTURES

//GW_STRUCTURES{{("Structure sent with WM_NOTIFY message to grid's parent indicating that the grid's selection has changed.")
typedef struct tagGM_SELCHANGE {
    NMHDR hdr;							//Notify Message Header structure.
	int nRowNdx;						//Row index of affected row.
	int nColNdx;						//Col index of affected column.
} GM_SELCHANGE;
//}}GW_STRUCTURES
#endif  
  
class CGWImportExportObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class CGWGrid
// This is the class that actually implements the grid and all of its 
// base functionality. You should always derive your view from this class. 
// It is not recommended that you use this class alone. In order for this
// view to function properly, make certain that any virtual functions that 
// you override calls this base classes implementation where appropriate 
// (which should be most of the time). 
class GW_EXT_CLASS CGWGrid 
{

//GW_CLASS{{(CGWGrid)
/*
The main class in the GridWiz Library is the CGWGrid abstract class. This class contains the infrastructure of the grid. The 
CGWGrid class is used as a base class along with another MFC or GridWiz class to form usable objects. The other grid 
classes, CGWGridView, CGWTabGridView, CGWGridCtrl, CGWTabGridCtrl, CGWGridPopup and CGWGridRpt derive from CGWGrid 
for grid services and MFC to provide the CWnd or CObject functionality. CGWGrid and its derivatives are virtual grids 
by design. What we mean by that is, the application data is not stored in CGWGrid or any of the other grid classes, 
it's stored elsewhere, possibly in a GridWiz Attachable Data Source or in your own data structure. CGWGrid keeps track 
of what cells are visible in the window, and requests data from the data source only when it needs to be drawn. This 
way, there's no duplication of data like in VBX controls. In addition, it provides tremendous flexibility as to what 
you want to draw into a cell.  By overriding a few virtual functions, you can assume as much control over the grid 
as you want.

CGWGrid keeps track of Grid Cell Objects (GCOs) in a embedded collection class called CGCOCache. Only visible cells 
in the grid have a GCO associated with it. Embedded array and maps keep track of the registered GCO types and where 
they are mapped. A CGWGridCellObject is a class which is used to represent a single cell. Using the GCOMap, you can 
map ranges, rows and columns to specific CGWGridCellObject types. This architecture allows you to separate the Cell 
user interface from the grid-to-data mapping. This allows you to reuse user-interface features of your cells in other 
grids. GridWiz supplies several built in CGWGridCellObject types which can be extended (see the section on Grid Cell 
Objects for details).

the CGWGrid base class methods typically manipulate Sheets, Rows, Columns, Ranges and Cells. These items are not class 
types however, they are just a means to categorize or abstract portions of the CGWGrid's overall interface. These 
categories plus several others are used to describe CGWGrid's public interface. For example, there are a group of 
CGWGrid properties which are applicable to rows of cells in the grid. There are events  which are applicable to a 
particular sheet. Since there are no intermediate objects representing Rows etc., how do you identify a row from 
a cell from a sheet. Generally speaking, all of the properties are implemented through member access functions 
(Get... / Set...). The function name along with arguments at the beginning or the argument list will help identify 
the category and the target item or group of items.

For example:

void SetRowBackColor(int nBegRowNdx, int nEndRowNdx, COLORREF rgbBackColor, int nSheet = CURRENT_SHEET);

From the function name, you can tell that this function has something to do with the Row category. The first two arguments 
identify the beginning row and the ending row. From that you can correctly assume that this function will work on a 
collection or Rows.  Finally, many member access functions have one or more default arguments. In this case, nSheet 
identifies the Sheet (zero based index) on which the Rows exist. Since properties can apply to more than one category 
(Sheets, Rows, Columns, etc..), the documentation for each property will specify which categories the property applies to.

One of the major additions in GridWiz 3.5 is persistent properties.  This feature enables you to set the value of properties 
down to the cell level from anywhere in your code where you have a pointer to your grid object. Prior to this version, 
the only way to accomplish this was to derive new classes and implement interfaces on those properties yourself. Consequently, 
with the addition of so many new functions, the GridWiz interface has become a little daunting to say the least. Therefore, 
we have grouped the interface into Core and  Internal functionality.  Again, this is only an attempt to make the classes 
and its documentation easier to use. There are no switches or additional modules required to use Internal features.  Most 
applications will only need to use the Core functionality so why confuse people with exotic functionality that they 
probably won't use.

*/

//}}GW_CLASS	

friend class CGCOCache;
friend class CMatrix;
friend class CGWGridEdit;    							// The Grid floating edit control class.
friend class CGWGridCellObject;
friend class CGWHeaderCell;
friend class CGWGridDC;
friend class CGWReport;  
friend class CGWGridWizGridItem; 
friend class CGWDropTarget;
friend class CGWOleActive;
friend class CGWCellTip;
friend class CGWTabGridView;
friend class CGWTabGridCtrl;

public:
	DECLARE_GRIDCELL_MAP(CGWGrid)

public:                 

//class constants
//GW_ENUMERATIONS{{(CGWGrid, "Automatic sheet index specifiers.")
    enum SheetIndexes					
    {
    	CURRENT_SHEET = -1,
    	FIRST_SHEET = 0,
    } SheetIndex;
//}}GW_ENUMERATIONS

    	
//GW_ENUMERATIONS{{(CGWGrid, "Current Row Settings used in DeselectRow function.")
    enum CurrentRowSettings			
    {
    	NOT_CURRENT_ROW,
    	SET_ROW_AS_CURRENT
    } CurrentRowSetting;
//}}GW_ENUMERATIONS
    	
//GW_ENUMERATIONS{{(CGWGrid, "Vertical Scroll Commands issued from selection routines.")
    enum VerticalScrollCommands			
    {
    	SCROLL_VERTICAL_NONE,
    	SCROLL_LINE_UP,
    	SCROLL_LINE_DOWN
    } VerticalScrollCommand;
//}}GW_ENUMERATIONS
    	
//GW_ENUMERATIONS{{(CGWGrid, "Horizontal Scroll Commands issued from selection routines.")
    enum HorizontalScrollCommands		
    {
    	SCROLL_HORIZONTAL_NONE,
    	SCROLL_LINE_LEFT,
    	SCROLL_LINE_RIGHT
    } HorizontalScrollCommand;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGrid, "Redraw Flags used in SelectRow and DeselectRow functions.")
    enum RedrawFlags				
    {
    	DO_NOT_REDRAW,
    	REDRAW_NOW
    } RedrawFlag;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGrid, "Grid styles and Selection modes used in SetGridStyle() function.")
    enum GridStyles					
    {
		GS_NORMAL = 1,            //Standard spreadsheet cell selection.
		GS_LISTBOX = 2,           //Grid behaves as a listbox. Click on a cell selects entire row.
		GS_MULTIPLE = 4,          //Mutiple selection style selects additional cells or rows just by clicking. 
		GS_EXTENDED = 8      	  //Extended selecting and Deselecting by clicking and holding down Control and Shift keys.
    } GridStyle;   
//}}GW_ENUMERATIONS
    
//GW_ENUMERATIONS{{(CGWGrid, "Automatic row and column extents.")
    enum RowColWidths					
    {
     	DEFAULT_TO_FONT = 0,
    } RowColWidth;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGrid, "OnUpdate() function hints.")
	enum UpdateHint						
	{
		RESTORE_GRID_SETTINGS = 8, 
		RESTORE_GCO_MAPPINGS = 9, 
		RESTORE_ALL_SETTINGS = 10,
	} UpdateHints;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGrid, "Row and column extent units used in calls to SetRowHeight(), GetColWidth(), etc.")
	enum RowColUnits					
	{
		DEFAULT_UNITS = -1,
		PIXELS = 0,
		CHARS = 1,
	} nRowColUnits;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGrid, "Grid operation modes.")
	enum DataEntryMode					
	{
	 	DEM_EDIT = 0,			//Grid is mostly in this mode. Allows for simple cell by cell editting.
	 	DEM_RECORD_ADD = 1,		//Grid enters this mode when there is data entry in the AddRow. 
	} DataEntryModes;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGrid, "Grid Data entry modes")
	enum DataEntryModeState			
	{
		DEMS_NEUTRAL = 0,				//Grid is not editing or adding.
	 	DEMS_EDIT_NEW_ROW = 1,        	//In the process of editing row data. Defaults have been obtained.
		DEMS_ADDNEW = 2,				//Call AddNew if data source is recordset based
	 	DEMS_TRANSFER_BUFFER = 3,    	//Buffer is being transfered into fields.
	 	DEMS_COMMIT_ADD = 4,    		//Database Update or commit is performed.
	} DataEntryModeStates;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGrid, "OLE Drag and Drop styles used in calls to SetRowDragStyle, etc.")
    enum DragStyles				
    {
		DRAG_DISABLED   = 0x0000,				//No draging allowed
		DRAG_OVERLAY	= 0x0001,				//Allowable operation        
		DRAG_INSERT		= 0x0002,				//Allowable operation         
		DRAG_COPY		= 0x0004,				//Allowable operation         
		DRAG_MOVE		= 0x0008,				//Allowable operation         
		DRAG_ALWAYS_OVERLAY		= 0x0010,		//Overrules Shift Key         
		DRAG_ALWAYS_INSERT		= 0x0020,		//Overrules Shift Key         
		DRAG_ALWAYS_COPY		= 0x0040,		//Overrules Control Key         
		DRAG_ALWAYS_MOVE		= 0x0080,		//Overrules Control Key                 
		DRAG_STANDARD   = 0x000F,				//Default drag styles
    } nDragStyle;   
//}}GW_ENUMERATIONS


protected:
//Protected Data Members
//GW_MEMBERS{{(CGWGrid,"Protected Data Members")
	int 			m_nAddRow;                      // Allow on additional row for adding new row. Automatically incremented.
 	BOOL 			m_bAutoSizeColumns;             // Force all columns to fit exactly in the grid.
	COLORREF 		m_BackgroundColor; 				// RGB the background color for each cell.
	BOOL 			m_bBorder;       				// Draw a rectangle around the grid.
	int				m_nMaxColumns;					// Top of ScrollRange (Set this!)
	int				m_nMaxRows;             		// This one too.
    BOOL 			m_bResizeRows;   				// Determines whether the user can resize via fixed rows
    BOOL 			m_bResizeCols;  		 		// and Columns. Default TRUE;
    BOOL 			m_bRowSelect;   				// Determines whether the user can select rows by clicking on a fixed header
    BOOL 			m_bColSelect;  		  			// Determines whether the user can select columns by clicking on a fixed header
	BOOL			m_bSizeColumnsTopToBottom;      // Determines whether sizing colums can be done from top to bottom rather than only in column headers. 
	BOOL			m_bSizeRowsLeftToRight;			// Determines whether sizing rows can be done from left to right rather than only in row headers. 
	BOOL			m_bShowTreeLines;				// Determines whether tree lines are shown.
	int             m_nRowColUnits;                 // Chars or Pixels
    UINT 			m_nDisableNoScroll;				// Determines whether scrollbars are removed or just diabled.
    BOOL 			m_bDragAndDrop;            		// Enable drag and drop
	COLORREF 		m_FixedCellColor;      			// Fixed cell color. Defaults to COLOR_BTNFACE
	int				m_nFixedColumns;  	 			// Determines the number of fixed columns. 
	int 			m_nFixedRows;      				// Determines the number of fixed rows.
	int				m_nLockedColumns;  	 			// Determines the number of fixed columns. 
	int 			m_nLockedRows;      			// Determines the number of fixed rows.
	LOGFONT 		m_LogFont;              		// The LogFont structure for the current Font
	int 	 		m_nPointSize;          			// The point size of the font to be used.
	COLORREF 		m_GridLineColor;      		 	// RGB value of the gridlines.
	BOOL			m_bGridLines;      				// Toggles whether there are visible gridlines.
	BOOL 			m_bInvertSelection;   			// Determines whether the selecting process will use Inverse Video to highlight.
	UINT 			m_nGridStyle;			        // Determines the grid style including the ability to select multiple regions
	CPoint 			m_PenWidth;          			// The width of the pen in logical points.
    CString 		m_csPrintCaption;               // Caption used for the default grid printing.
    BOOL 			m_bRecordsetEnable;				// Is this grid used to go after a CRecordset Object
	BOOL			m_bShowFocusRect;  				// Controls whether the focus rect thing is drawn around current selection. Default is FALSE;
    BOOL 			m_vBar;                         // Determines whether the vertical scroll bar is visible.
	BOOL 			m_hBar;							// Determines whether the horizontal scroll bar is visible.
	BOOL 			m_bShowCurrentCell;   			// Determines whether the current cell has a selection box.
	BOOL            m_bGridHasFocus;				// Identifies whether the grid or a child window currently has the input focus.
	BOOL            m_bHiliteNoFocus;               // This fixes the grid displaying hilight when not in focus issue,
	UINT 			m_nSizingRegionWidth;          	// The size of the area used to resize rows and columns with the mouse. 
	BOOL 			m_bSynchronizePanes;    		// Controls whether one pane can drive another.
	COLORREF 		m_TextColor;           			// RGB value of the Cell Text. Defaults to COLOR_WINDOW.
	BOOL			m_bThumbScroll;   				// Enables or disables the thumbscroll.
	COLORREF 		m_HighlightColor;     			// Hightlight color. Not being used.
	int				m_nMinColumn;           		// Defaults to 1. Don't set < 1.
	int				m_nMinRow;              		// Ditto. Must be > 0.
	int 			m_MapMode;              		// Defaults to MM_HIMETRIC. Don't change
	BOOL            m_bEnabled;						// Sets the enabled state of the grid.
	BOOL 			m_bRowBasedDrawing;				// Allows you to mark rows as dirty. They're reset during GridOnDraw.
	BOOL			m_bWantDropNotify;              // Allows you to handle the ole drop mechanism and not allow the AddRow functionality to take over.
	BOOL			m_bWantDrawNotify;				// Controls whether call backs are made as each cell is drawn.
	CGWContextMenu* m_pContextMenu;					// Default context menu for the sheet.	
	CGWContextMenu* m_pTabMenu;						// Default context menu for the tab area.	
	int				m_nDockedColumns;				// Number of docked columns (Fixed along right side).
	int				m_nDockedRows;					// Number of docked rows (Fixed along bottom).
	BOOL			m_bAutoScroll;					// Controls whether the grid automatically scrolls cells into view on LButtonUp
	CString			m_CellDelim;					// Delimiter used between fields when building blocks of data.
	CString			m_LineDelim;					// Delimiter used between lines when building blocks of data.
	UINT 		  	m_nCurrentCursor;  				// The ResourceID of the current cursor.
	HCURSOR		  	m_hUserDefinedCursor;			// A cursor handle which can be specified to take over the entire grid.
    int 			m_nHScrollPos;        			// Horizontal scroll position.
    int 			m_nVScrollPos;       			// Vertical scroll position.
    CWnd* 			m_pGridCWnd;           			// The CWnd derived class which inherits from this class.
	CBitmap*		m_pGridBitmap;					// The bitmap used for offscreen rendering.
	BOOL            m_bDrawOffScreen;				// Tells the grid to use offscreen bitmaps when possible.
	CSize			m_sizeWnd;						// The last size of the window. Used to optimize calls to OnSize.
    CRect 			m_GridRect;           			// The Crect in Device points corresponding to the visible grid. 
	CGWGridCellObject* m_pCellCapture; 				// The cell which has captured the input focus. 
	CString 		m_csSettingsFile;				// CString containing the settings file which will initialize the CGWDataSource object.
	CString 		m_csSettingsFilePath;			// CString the path to the InitializationFile
	int				m_nStringCount;                 // Controls the number of strings shown in a drop down or combobox type cell.
	UINT			m_nTabControl;					// Controls how the grid reacts to the tab key.
	CRect			m_DockableRowRect;				// Client based coordinates of the area made up of any docked rows.
	CRect			m_DockableColumnRect;			// Client based coordinates of the area made up of any docked rows.
	int				m_nCellSettingsRank;			// Rank given to cell settings. (1, 2, or 3)
	int				m_nRowSettingsRank;				// Rank given to row settings. (1, 2, or 3)
	int				m_nColSettingsRank;				// Rank given to column settings. (1, 2, or 3)
	BOOL 			m_bSizingRowNow;				// These members are used for row and column 
	BOOL 			m_bSizingColumnNow;   			// sizing. The BOOLs control whether the 
	BOOL			m_bSelectingNow;	   			// Indicates whether the selection rect is being modified.
	UINT 			m_nTimerScroll;       			// tells the timer msg handler how to scroll
	BOOL 			m_bCellSelected;     			// What type of selection was made.
	BOOL 			m_bRowSelected;                 // What type of selection was made.
	BOOL 			m_bColumnSelected;              // What type of selection was made.
	BOOL 			m_bActivePane;        			// Set to true if this pane is active in a 
	BOOL 			m_bInitialColWidth;   			// Has the column Widths been initialized for this grid?
	int 			m_nVPageSize;         			// The number of rows currently visible
	int 			m_nHPageSize;         			// The number of columns currently visible
	BOOL 			m_bTextBand;  					// True when printing the text band
	BOOL 			m_bGraphicsBand; 				// TRUE when printing the Graphics band
	CPoint 			m_DirtyCell;  					// The cell which has just been updated through the floating edit control.
	BOOL 			m_bGridDirty;                   // Set whenever a visual aspect of the grid has been changed.
	int 			m_nRowNotCompletelyVisible; 	// Indicates whether the last row of the grid is completely visible.
	int 			m_nColNotCompletelyVisible; 	// Indicates whether the last column of the grid is completely visible.
	BOOL 			m_bGridError;                   // Is the cell which was editted in error?
	BOOL 			m_bTabSetMode;     				// Puts the entire grid into tab setting mode. 
    CPoint   		m_CurrentCell;   				// The cell with focus 
    int 	   		m_nCurrentSheet;   				// The current sheet in a multi-sheet workbook. 
    CGWGridCellObject* m_pGCOFocus;                 // Pointer to the cell (must be visible) with focus.
    CCellContext  	m_CurrentCC;      				// CCellContext used for current cell
    int 	 		m_nCurrentCellState;        	// The current cell or selected row can be one of the following:
    CRect 			m_rectCurrentCell;              // The CRect coordinates of the current cell.
	BOOL 			m_bSplitterRow;					// These two variables control how the splitter
	BOOL 			m_bSplitterCol;    				// Handles fixed rows and columns.		
    BOOL 			m_bFocusRectDirty;              // Does the focus rect need to be updated.
	BOOL 			m_bLButtonDownInGrid;           // Need to know when closing a splitter window.
	CGWGridCellObject* m_pControlCell;              // The address of the GCO which has a activated control in it.
	UINT*			m_arrayRowPoints;				// Array which keeps track of where rows start and end.
	UINT*			m_arrayColPoints;				// Array which keeps track of where columns start and end.
	CGWMapIntToInt 	m_mwpHiddenRows;    			// Keeps track of any hidden rows.
	CGWMapIntToInt 	m_mwpHiddenColumns; 			// Keeps track of any hidden rows.
	CGWMapIntToInt 	m_mwtpColumnInfo;   			// Stores column width in pixels.
	CGWMapIntToInt 	m_mwtpColumnWidth;   			// Stores column width in 1/100th of Ave. char width.
	CGWMapIntToInt 	m_mwtpRowInfo;      			// Stores row height in pixels.
	CGWMapIntToInt 	m_mwtpRowHeight;      			// Stores row height in points.
	CGWMapIntToInt  m_mwtpMinColSize;               // Stores the minimum columns sizes.
	CGWMapIntToInt 	m_mwtpColumnInfoSave;  			// Copies column sizes before scaling for printing.
	CGWMapIntToInt 	m_mwtpRowInfoSave;      		// Copies row sizes before scaling for printing.
    CGWMapIntToPos 	m_mapFixedRowToGCO;   			// Sparse array of GridCellObject to fixed rows.
    CGWMapIntToPos 	m_mapRowToGCO;        			// Sparse array of GridCellObject to rows.
    CGWMapIntToPos 	m_mapFixedColToGCO;   			// Sparse array of GridCellObject to fixed columns.
    CGWMapIntToPos 	m_mapColToGCO;        			// Sparse array of GridCellObject to columns.
    CPtrArray 		m_arrayRanges;   				// Ptr to a CRect for each defined range mapped to aCGWGridCellObject class.
    CPtrArray 		m_arrayGCOPos;   				// Ptr to a CRect for each defined range mapped to aCGWGridCellObject class.
    CGCOCache 		m_listGridCellObjects;			// Collection class which holds that GCO pointer for visible cells.
    CRuntimeClass* 	m_runtimeGCODefault;			// Pointer to the RUNTIME_CLASS object of the default GCO.
	CPtrArray     	m_paSelectionRects; 			// Holds the currently selected regions stored as CRect*. The members of the each CRect are Grid Row and Column indexes.  
	CPtrList 		m_listSelectionRectsCopy; 		// Holds  a copy of m_paSelectionRects. For use with Extended Listbox  
	CGWTab 			m_TabKeeper;       				// Object which manages Tabstops.
	CPtrArray    	m_paSelectedCells;  			// Holds the individual cell corrdinates of the selection region. Call function SelectionCells to refresh.
	CPoint 			m_FromPt;		  				// Original point during a row or column size.
	CPoint 			m_ToPt;            				// Destination point during a row or column size.
	CPoint 			m_LastPt;           			// Original point during a row or column size.
	CPoint 			m_FirstPt;		   				// Destination point during a row or column size.
    CRect 			m_GridLessFixedColRect;  		// Client coordinates of the area of the grid less any fixed columns.
    CRect 			m_GridLessFixedRowRect;  		// Client coordinates of the area of the grid less any fixed rows
	CRect 			m_GridLessFixedRowsNCols; 		// Client coordinates of the area of the grid less any fixed rows and columns.
    CRect 			m_GridLessLockedColRect;  		// Client coordinates of the area of the grid less any locked columns.
    CRect 			m_GridLessLockedRowRect;  		// Client coordinates of the area of the grid less any locked rows
	CRect 			m_GridLessLockedRowsNCols; 		// Client coordinates of the area of the grid less any locked rows and columns.
	CBitmap 		m_bmpSpinBtn;    				// Bitmap for the CSpinBtnCell GCO
	CString 		m_csTRUE;     					// CStrings loaded from resources for displaying
	CString 		m_csFALSE;    					// Boolean values for ODBC datatype conversion,
	CString 		m_csDefaultString; 				// CString loaded from resources to determine the 
    int 			m_nSaveHScrollPos;    			// Copy of original scrollpos saved while printing.
    int 			m_nSaveVScrollPos;				// Copy of original scrollpos saved while printing.
	BOOL 			m_bSaveShowCurrentCell;  		// Saved during the SetTabMode session
	BOOL 			m_bSaveInvertSelection;         // Saved during the SetTabMode session
    int 			m_nRowHeight;          			// The default extents of a grid cell in pixels.             
    int 			m_nColWidth;           			// The default extents of a grid cell in pixels.             
    float 			m_nRowHeightPoints;          	// The default extents of a grid cell based on the current font.
    float 			m_nColWidthChars;           	// The default extents of a grid cell based on the current font.
	int 			m_nRowHeightSave;      			// Copy of the extents of a grid cell in pixels.             
	int 			m_nColWidthSave;       			// Copy of the extents of a grid cell in pixels.             
	UINT 			m_nCurrentTabSet;               // The next tab stop index to get focus;
	int     		m_nYOrg;           			 	// The sign of the y-axis. (+1 for MM_TEXT otherwise -1 )    
    int	 			m_nAnchorRow;               	// Row used for shift selecting in the GS_EXTENDED style
	CFont   		m_CurrentFont;	                // Default GDI objects 
	CPen    		m_GridLinePen;					// Default GDI objects 
	CBrush  		m_BackgroundBrush;				// Default GDI objects 
	CGWMapULongToPtr   m_mapCachedBrushes;			// A cache of brushes used in drawing.
	CMapStringToPtr   m_mapCachedFonts;				// A cache of fonts used in drawing.
	CMapPtrToPtr	m_mapCachedDCs;					// A cache of Client DCs
	BOOL			m_bCacheDCs;					// Determines whether to Cache DCs.
	CBrush  		m_CTLBrush;						// Default GDI objects 
	CBrush  		m_FixedCellBrush;				// Default GDI objects 
	CEdit* 			m_pSecretCWnd;                  // A hidden CEdit control used for MFC RFX macros.
	long            m_dGridOrgY;					// The device point origin of the first non-fixed row
	long            m_dGridOrgX;					// The device point origin of the first non-fixed column
	BOOL			m_bShowTabs;					// Determines whether tabs are displayed on grids that can have a tabbed interface.
	CRgn			m_rgnSelectedRgn;				// Region which covers the selected cells.
	CRgn			m_rgnCurrentCellRgn;			// Region which covers the current cell.
	int				m_nTipTimerDelay;				// Delay in millesecconds between WM_MOUSEMOVE events which controls when a cell is allowed to show its tooltip.
	CString			m_csCellTipWindowClass;			// The window class name of the cell tip window. This member should be empty unless cell tip windows cannot be created.
	BOOL			m_bNotifyParent;				// Controls whether notification command messages are sent to the grid's parent. Defaults to FALSE for CViews and TRUE for grids.
	BOOL			m_bDroppedInGrid;				// Determines whether the drag drop operation resulted in a drop in this grid.
	BOOL			m_bDragSource;					// Determines whether the drag drop operation originated in this grid.
//}}GW_MEMBERS

	BOOL 			m_bCalledFromSetScrollPos;
	long			m_nTempScrollPos;
	BOOL			m_bAllowDragSelecting;

public:
//Special Bitmaps
//GW_MEMBERS{{(CGWGrid,"Stock Bitmaps")
	CBitmap			m_bmCheckBoxOn;					// CheckBox which is enabled and checked.
	CBitmap			m_bmCheckBoxOnDisable;			// CheckBox which is disabled and checked.
	CBitmap			m_bmCheckBoxOff;				// CheckBox which is enabled and not checked.
	CBitmap			m_bmCheckBoxOffDisable;			// CheckBox which is disabled and not checked.
	CBitmap			m_bmRadioOn;					// Radio button which is enabled and checked.
	CBitmap			m_bmRadioOnDisable;				// Radio button which is disabled and checked.
	CBitmap			m_bmRadioOff;					// Radio button which is enabled and not checked.
	CBitmap			m_bmRadioOffDisable;			// Radio button which is disabled and not checked.
	CBitmap         m_bmFolderOpen;					// Open Folder.
	CBitmap         m_bmFolderClosed;				// Closed Folder.
	CBitmap         m_bmDocument;					// Document.
	CBitmap         m_bmDocumentNew;				// New Document
//}}GW_MEMBERS

public:
//Public Data Members
//GW_MEMBERS{{(CGWGrid,"Public Data Members")
	CGWGridSettings m_GridGlobalSettings;			// Grid settings which are built upon initialization and applied to any new sheets.
	CDocument*      m_pDoc;							// A CDocument pointer. 
    CGWDataSource*  m_pGWDataSource;                // Address of a CGWDataSource object used for default of data and settings;
    CGWDataSource*  m_pGridInternalDataSource;		// Address of a CGWDataSource. Same as m_pGWDataSource if AttachInternalDataSource was called.
	CGWOleSwitch*   m_pGWOleSwitch;                 // Pointer to the object which implements the OLE Drag and Drop for the grid.
    CGWDropTarget*  m_pGWDropTarget;                // The drop target used for all grids.
    CSize   		m_sizeDragOffset;               // Offset from the drag rect to the point.
    UINT 			m_nGCOLostFocusToAnotherWindow; // Registered windows message indicating that a control in a GCO lost focus to a window which is not the grid or a child of the grid.
	static  UINT    m_nReturnControlGCO;			// Registered windows message which returns the address of a GCO which is currently in edit mode.
	static  UINT    m_nReturnGrid;					// Registered windows message which returns a CGWGrid pointer.
	static  UINT    m_CacheUpdate;					// Registered windows message which signals the grid to update the scroll range.
	static  UINT    m_FillDataCache;				// Registered windows message which signals the grid to request additional data for the data cache.
	static  UINT 	m_SetColWidth;					// Registered windows message which signals the grid to adjust the width of a particular column.
	static  UINT 	m_GetColWidth;					// Registered windows message which signals the grid to lookup and return the width of a particlar column.
	static  UINT    m_RestoreGridSettings;			// Registered windows message which signals the grid to restore grid settings from the data source.
	static  UINT	m_nClearCachedDCs;              // Registered windows message which signals the grid to destroy any cached DCs which have accumulated.
	static  UINT	m_nZapCell;						// Registered windows message which signals the grid to destroy a cell so that it can be recreated.
	static  UINT    m_nGetNode;						// Registered windows message which retrieves the node id of a row.
	int				m_LOGPIXELSY;					// Cached logical pixels per vertical inch.
	float			m_LOGPIXELSYdiv72;				// Cached logical pixels per vertical inch divided by 72.
	int				m_LOGPIXELSX;					// Cached logical pixels per horizontal inch.
	int				m_HORZRES;						// Cached horizontal resolution.
	int				m_VERTRES;						// Cached vertical resolution.
	CString 		m_csAlphabet;    				// CString loaded from resources for lettered grid.
	BOOL 			m_bOKtoRefresh;					// Signals that the grid has gotten beyond OnInitialUpdate and its ok to refresh the window.
	BOOL			m_Closing;						// The window is in the process of being closed.
	BOOL			m_bActivatingSheet;				// Indicates that the grid is in the process of activating a sheet.
	CGWSort*        m_pGWSort;						// Keeps track of the last sort operation.
	CGWSeek*        m_pGWSeek;						// Keeps track of the last seek operation.
	CGWReplace*		m_pGWReplace;					// Keeps track of the last replace operation.
	BOOL			m_bEditingNow;	   			    // Indicates whether the current cell has an active control in it
	int 			m_nDataEntryMode;				// Controls default data entry behavior
	int 			m_nDataEntryModeState;			// Differnt states within a data entry mode.
	int				m_nAddIndex;            		// The row index for the database row being added.
	CPoint 			m_cellError;                    // The cell which cause the current error condition.
	CMapWordToPtr 	m_mapPageMap;       			// Keeps track of starting row for each page
    CWordArray      m_RowDirtyArray;                // An array which is initialized each time OnDraw is called Can be used by GCOs to row painting. i.e. set the flag so that a row is only draw once. GCO is responsible for this.
	BOOL 			m_bGCOCacheIsDirty;             // Set this to force the GCO cache to be recalculated next time thru RecalcGridLayout.
	static  HCURSOR 	  	m_hcursor;         		// Used to store the CWnds previous  HCURSOR.
	BOOL			m_bVirtualDataMode;             // Determines whether certain data releated functions call the OnSet/OnGet virtuals. Default is FALSE.	//BF0045
	BOOL			m_bClipHeadings;                // Determines whether to include headings in clipboard operations.  //BF0045
	BOOL            m_bShowEditIndicators;          // Show edit indicators in row header. //BF0057
	BOOL 			m_bCellDirty;  					// Is set to true whenever the floting edit control is updated.
	UINT			m_nColumnDragStyle;             // Controls how drag and drop capability for columns.	
	UINT			m_nRowDragStyle;                // Controls how drag and drop capability for Rows.	
	UINT			m_nRangeDragStyle;              // Controls how drag and drop capability for Ranges.	
	COLORREF		m_clrfOutOfBounds;				// The color of the non-grid portion of the window.
	int				m_nEditFlag;					// The sheet level edit event setting.
	int				m_nVertAlign;					// The sheet level vertical alignment setting.	
	int				m_nHorzAlign;					// The sheet level horizontal alignment setting.
	BOOL			m_bWordWrap;					// The sheet level word wrap setting.
	CRect			m_rectBorder;					// The sheet level border setting.
	int				m_nPatternID;					// The sheet level background pattern setting.
	COLORREF		m_rgbForecolor;					// The sheet level forecolor setting.
	CString			m_csFormat;						// The sheet level text format setting.
	CString			m_csInputMask;					// The sheet level input mask setting.
	static CPtrList m_listRegisteredGCO;      		// List containing CRuntimeClass* to registered CGWGridCellObject derived classes.
	static CMapStringToPtr m_mapNameToGCO;			// Map containing names of classes and their associated RUNTIME_CLASS structures.
	BOOL m_bAutoSizeRowHeight;						//Automatically size height to fit wrapped text for all cells on the sheet.
	BOOL m_bAutoSizeColumnWidth;					//Automatically size Width to fit single line text for all cells on the sheet.
	BOOL m_bAutoSizeControlHeight;					//Automatically size height of grid window to fit all rows.
	BOOL m_bAutoSizeControlWidth;					//Automatically size Width of grid window to fit all columns.
	BOOL m_bAutoSizeVisibleOnly;					//Restrict autosize routine to access only cells that would be visible and all rows and columns.
	DWORD m_dwPrimaryControlStyle;		// Window control style to be applied to primary child control in cell.
	DWORD m_dwSecondaryControlStyle;	// Window control style to be applied to secondary child control in cell.
	DWORD m_dwExtendedCellStyle;		// Additional cell styles particular to specialized GCOs.
	BOOL m_bHandleSetFont;				// Controls whether the grid control handles the WM_SETFONT message. This will override the default grid font.	
	BOOL m_bSendCommandsToParent;		// Controls whether the grid owned popup menus send WM_COMMAND messages to the parent rather than the grid.
	BOOL m_bEnableCellTips;				// Controls whether cell tips are displayed.
//}}GW_MEMBERS
	

protected: 
//Protected Housekeeping Functions
//GW_MEMBERS{{(CGWGrid,"Protected Housekeeping Functions")
	void SetMaxRows(int nRowNdx, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);     // Sets the number of rows and updates the scroll range.
	void SetMaxColumns(int nColNdx, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	// Sets the number of columns and updates the scroll range.
	void SetMinRow(int nRowNdx);														// Sets the minimum row index. Based on the number of fixed rows.
	void SetMinColumn(int nColNdx);														// Sets the minimum column index. Based on the number of fixed columns.
 	void ClearGCOCache();										// Delete and reset all the GCOs in the GCO Cache.
 	void DumpGCOCache();										// Dump information about the GCOs from the GCO Cache.
	void CompactGCO(int nVPageSize, int nHPageSize);            // Free any uneeded GCOs after resizing the grid.
	void ShiftRowAttributes(int nStartAt, int nCount, int nSheet = CURRENT_SHEET);		// Shift row attributes up or down.
	void ShiftColumnAttributes(int nStartAt, int nCount, int nSheet = CURRENT_SHEET);	// Shift column attributes left or right.
	void ShiftRowGCOMap(int nStartAt, int nCount, int nSheet = CURRENT_SHEET);			// Shift the GCO row map up or down.
	void ShiftColumnGCOMap(int nStartAt, int nCount, int nSheet = CURRENT_SHEET);		// Shift the GCO column map left or right.
	void SmartInvertSelection(CRect* pRect, UINT nRectNum);					// Invert and minimize flicker (Obsolete)
	virtual void SmartInvertAllPanes(CRect* pRect, UINT nRectNum) 			// Invert in all panes (Obsolete)
			{};
	CRect GetSelectedRect(CDC* pDC, UINT nRectNum, BOOL bConcat = FALSE);	// This function retrieves a CRect containing the logical point coordinates of the region of the view representing the currently selected cell(s). nRectNum controls which selected rect if there are multiple regions.
	void ClearSelectedRects();												// Clears the array of currenly selected regions of the grid.
	void SortSelectedRects(BOOL bAscending = TRUE);							// Sorts the array of currently selected cells of the grid.
	void ClearSelectedCells();												// Clears the array of currenly selected cells of the grid.
	void CopySelectionRects();												// Copies the selected rects to a special member. For use with Extended listbox style.
	virtual void CopySelRect(CGWGrid* pGV)									// Copies the selected rect from one Gridview to another.
			{};
	virtual void InvalidateCellAllPanes(int nRowNdx, int nColNdx)			// Invalidate a particular cell in all openned splitter panes.
			{};
	void GridOnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);				// Set the mapping mode and selects the font and drawing tools
	virtual void CalcGridRect() = 0;										// This function is overridden in CGWGridCtrl and CGWGridView and CGWGridPopup to determine m_GridRect.
	virtual void CalcPageSize(CRect* pGridRect = NULL);						// This function determines how many rows and columns can potentially fit into the area of m_GridRect.
	void SetExtents(CDC* pDC,BOOL bView = TRUE);							// Calculates extents and metrics used in drawing based on the currently selected font.
	virtual void GWShowScrollBar(UINT nSB, BOOL bShow, BOOL bEnabled);		// Hide or show scrollbars regardless of who owns them
	virtual void CopyView(CGWGrid* pGV, BOOL bRedraw = TRUE)				// Copies the attributes of one CGWGrid object to another.
			{};
	void DoExtendedListboxSelect(int nRowNdx,UINT nFlags, UINT nScrollToTop);	// Implements selecting with mouse and keyboard.
	void DoExtendedListboxSelectControl(int nRowNdx);							// Implements selecting with mouse and keyboard.
	void DoExtendedListboxSelectShift(int nRowNdx);								// Implements selecting with mouse and keyboard.
	void DoExtendedListboxSelectCS(int nRowNdx);								// Implements selecting with mouse and keyboard.
	void DoExtendedListboxDragSelect(UINT nFlags, CPoint& point);				// Implements selecting with mouse and keyboard.
	void DoMultipleListboxSelect(int nRowNdx, UINT nScrollToTop);				// Implements selecting with mouse and keyboard.
	void DoMultipleListboxDragSelect(UINT nFlags, CPoint& point);				// Implements selecting with mouse and keyboard.
	void DoSingleListboxSelect(int nRowNdx, UINT nScrollToTop);					// Implements selecting with mouse and keyboard.
	void DoSingleListboxDragSelect(UINT nFlags, CPoint& point);					// Implements selecting with mouse and keyboard.
	void DoExtendedGridSelect(int nRowNdx, int nColNdx, UINT nFlags, UINT nScrollToTop, UINT nScrollToLeft);	// Implements selecting with mouse and keyboard.
	void DoExtendedGridDragSelect(UINT nFlags, CPoint& point);													// Implements selecting with mouse and keyboard.
	void DoMultipleGridSelect(int nRowNdx, int nColNdx, UINT nFlags, UINT nScrollToTop, UINT nScrollToLeft);	// Implements selecting with mouse and keyboard.
	void DoSingleGridSelect(int nRowNdx, int nColNdx, UINT nFlags, UINT nScrollToTop, UINT nScrollToLeft);		// Implements selecting with mouse and keyboard.
	void DoSingleGridDragSelect(UINT nFlags, CPoint& point);							// Implements selecting with mouse and keyboard.
	void DeselectRow(int nRowNdx,  BOOL bRedraw = TRUE, BOOL bSetCurrentRow = TRUE);	// Implements selecting with mouse and keyboard.
	void DoSizeRow(CPoint& point);									// Implements sizing with mouse.
	void DoSizeColumn(CPoint& point);								// Implements sizing with mouse.	
	void DoSelecting(UINT nFlags, CPoint& point);					// Implements selecting with mouse and keyboard.
	void DoProcessScrollCommand(DWORD dwScrollCommand);				// Implements selecting with mouse and keyboard.
	void DeselectRangeRows(int nStartRow, int nEndRow);				// Implements selecting with mouse and keyboard.
	void DeselectRangeRowsExclude(int nStartRow, int nEndRow);		// Implements selecting with mouse and keyboard.
	void CalcTopAndBottom(int& Top, int& Bottom, CRect* pRect, CDC* pDC);	// Used during drag selecting to determine the new selected region and whether or not to start scrolling.
	void CalcLeftAndRight(int& Left, int& Right, CRect* pRect, CDC* pDC);	// Used during drag selecting to determine the new selected region and whether or not to start scrolling.
	DWORD GetScrollCmd(CPoint& point,int& nRowNdx,int& nColNdx);			// Used during drag selecting to determine the new selected region and whether or not to start scrolling.
	void ToggleSelectionAll(CDC* pDC);								// Called from Grid OnPaint to highlight the selected regions.
	BOOL InSelectionRectsCopy(int nRowNdx);							// Test to see if a row is already selected. Used for extended listbox style.
	virtual void CopyAndScaleGridExtents(CDC* pPrinterDC);			// Scale all the measures and extents to the resolution of the Printer. 
	virtual void RestoreGridExtents();								// Reset measures and extents to the resolution after printing.
	void SetMargins(float left, float top, float bottom, float right, CDC* pPrinterDC, CPrintInfo* pInfo); 	//Set print margins.
	void SetProportionalColWidths(CRect& lpGridRect);				// Forces all column widths to be adjusted so that all columns fit exactly within the grid.
	int  GetMinColWidth(int nColNdx);								// Retrieves the minimum Width of a column
	int SetGridScrollRange(UINT nSB, CScrollBar* pScrollBar, BOOL bRedraw = TRUE);	// Set the scroll range for a particular scroll determined by the min and max rows or columns.
	void GetGridScrollRange(UINT nSB, CScrollBar* pScrollBar, int& nMin, int& nMax); // Get the scroll range for a particular scroll determined by the min and max rows or columns.
	virtual void UpdateAllPanes(CGWGrid* pGV, BOOL bRedraw = TRUE)				// Updates view grid properties for any existing splitter panes.
			{};
	virtual void ScrollAllPanes(UINT nBar, UINT nScrollCode, int nScrollPos)	//Call the scroll message handlers for each open pane of a splitter window
			{};
	void GridToPrinter(CPoint& point, CDC* pPrinterDC);							// Convert a point based on the screen grid into a printer coordinate.
	void GridShowScrollBar(UINT nSB, BOOL bShow, BOOL bUpdate = TRUE);			//Call this function to hide or show the scrollbars
	void CleanUpCachedDCs();				// Called to remove cached DCs.
	BOOL UpdateCurrentCellState();			//This function is currently unused. 
//}}GW_MEMBERS


public:
//GW_MEMBERS{{(CGWGrid,"Construction")
	CGWGrid();				//Default constructor.
	virtual ~CGWGrid();		//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWGrid,"Dynamap functions")
 	void DynaMapHRow(int nBeginRowNdx,int nEndRowNdx, CRuntimeClass* pRuntimeClass, BOOL bRefresh = TRUE);	// Maps a GCO type to a header row. Obsolete - Use SetRowCellType instead.
 	void DynaMapRow(int nBeginRowNdx,int nEndRowNdx, CRuntimeClass* pRuntimeClass, BOOL bRefresh = TRUE);	// Maps a GCO type to a row. Obsolete - Use SetRowCellType instead.
 	void DynaMapHCol(int nBeginColNdx,int nEndColNdx, CRuntimeClass* pRuntimeClass, BOOL bRefresh = TRUE);	// Maps a GCO type to a header column. Obsolete - Use SetColCellType instead.
 	void DynaMapCol(int nBeginColNdx,int nEndColNdx, CRuntimeClass* pRuntimeClass, BOOL bRefresh = TRUE);	// Maps a GCO type to a column. Obsolete - Use SetColCellType instead.
 	void DynaMapGrid(CRuntimeClass* pRuntimeClass, BOOL bRefresh = TRUE);									// Maps a default GCO. Obsolete - Use SetDefaultCellType instead.
 	void DynaMapRange(int nBeginRowNdx,int nBeginColNdx, int nEndRowNdx,int nEndColNdx, CRuntimeClass* pRuntimeClass, BOOL bRefresh = TRUE); // Maps a GCO type to a range. Obsolete - Use SetCellType instead.
//}}GW_MEMBERS

	
//GW_MEMBERS{{(CGWGrid,"Settings")
	virtual void UpdateGridSettings(CGWGridSettings* pSettings);	// Stores current settings.
	virtual void UpdateGCOMappings(CGWGCOMappings* pSettings);		// Stores current mappings.
	virtual void RestoreGridSettings(CGWGridSettings* pSettings);	// Loads grid settings from an object.
	virtual void RestoreGCOMappings(CGWGCOMappings* pSettings);		// Loads GCO mappings from an object.
	virtual void RestoreCellSettings(CGWCellSettings* pCellSettings,CGWCellSettings* pRowSettings,CGWCellSettings* pColSettings,CGWGridCellObject* pGCO);	//Loads Cell Settings from an object
	virtual void OnSetGridSettings(CGWGridSettings*& pSetting, int nSheet = CURRENT_SHEET);								// Calls a function on CGWDataSource to store the grid settings.
	virtual void OnSetCellSettings(int nRowNdx, int nColNdx, CGWCellSettings*& pSetting, int nSheet = CURRENT_SHEET);	// Calls a function on CGWDataSource to store the cell settings.
	virtual void OnSetGCOMappings(CGWGCOMappings*& pSetting, int nSheet = CURRENT_SHEET);								// Calls a function on CGWDataSource to store the GCO Mappings.	
	virtual void OnSetRowSettings(int nRowNdx, CGWRowSettings*& pSetting, int nSheet = CURRENT_SHEET);					// Calls a function on CGWDataSource to store the row settings.
	virtual void OnSetColumnSettings(int nColNdx, CGWColumnSettings*& pSetting, int nSheet = CURRENT_SHEET);			// Calls a function on CGWDataSource to store the column settings.
	virtual CGWGridSettings* OnGetGridSettings(int nSheet = CURRENT_SHEET);								// Calls a function on CGWDataSource to retrieve the grid settings.
	virtual CGWCellSettings* OnGetCellSettings(int nRowNdx, int nColNdx, int nSheet = CURRENT_SHEET);	// Calls a function on CGWDataSource to retrieve the cell settings.
	virtual CGWGCOMappings* OnGetGCOMappings(int nSheet = CURRENT_SHEET);								// Calls a function on CGWDataSource to retrieve the GCO Mappings.	
	virtual CGWRowSettings* OnGetRowSettings(int nRowNdx, int nSheet = CURRENT_SHEET);					// Calls a function on CGWDataSource to retrieve the row settings.
	virtual CGWColumnSettings* OnGetColumnSettings(int nColNdx, int nSheet = CURRENT_SHEET);			// Calls a function on CGWDataSource to retrieve the column settings.
//}}GW_MEMBERS
									 

//GW_MEMBERS{{(CGWGrid,"Virtual Interface Functions")
	virtual void OnClearSheetData(int nSheet = CURRENT_SHEET);			// Calls a function on CGWDataSource to clear the data on a sheet.
	virtual void OnClearSheetAll(int nSheet = CURRENT_SHEET);			// Calls a function on CGWDataSource to clear the data and settings on a sheet.
	virtual void OnRefreshSheet(int nSheet = CURRENT_SHEET);			// Calls a function on CGWDataSource to reset the sheets row and column counts and refresh any external database link.
	virtual CGWDatabaseRequest* OnGetDatabaseRequest(int nSheet = CURRENT_SHEET);							// Calls a function on CGWDataSource to retieve a database request object for a sheet.
	virtual void OnSetDatabaseRequest(CGWDatabaseRequest* pDatabaseRequest, int nSheet = CURRENT_SHEET);	// Calls a function on CGWDataSource to set a database request object for a particular sheet.
	virtual void OnBindColumn(int nColNdx, int nFieldNdx, CObject* pObject,  int nSheet = CURRENT_SHEET);	// Calls a function on CGWDataSource to bind a column to an arbitrary field or field in a external database link.
	virtual int  OnGetBoundField(int nColNdx, CObject* pObject, int nSheet = CURRENT_SHEET);				// Calls a function on CGWDataSource to return a field index based on a bound column index.
	virtual int OnGetRowOrderIndex(int nRowNdx, int nSheet = CURRENT_SHEET);								// Calls a function on CGWDataSource to	return a original row index based on a sorted row index.
	virtual BOOL OnRegisterValidStringObject(CGWValidStrings* pGWValidStrings);								// Calls a function on CGWDataSource to register a valid string object.
	virtual BOOL OnLookupValidStringObject(CString m_csName, CGWValidStrings*& pValidStringObject);			// Calls a function on CGWDataSource to retrieve a valid string object given its name.
	virtual POSITION OnGetFirstValidStringObject();															// Calls a function on CGWDataSource to retrieve the first registered valid string object.
	virtual void OnGetNextValidStringObject(POSITION& pos, CString& csName, CGWValidStrings*& pValidStringObject);	// Calls a function on CGWDataSource to retrieve the next valid string object.
	virtual void OnRefreshValidStringObjects();													// Calls a function on CGWDataSource to	refresh the valid string objects and run any queries againt external database links.
	virtual void OnRemoveValidStringObject(CGWValidStrings* pGWValidStrings);					// Calls a function on CGWDataSource to remove a valid string object from the collection.
	virtual BOOL OnRegisterContextMenu(CGWContextMenu* pGWContextMenu);							// Calls a function on CGWDataSource to register a context menu.
	virtual BOOL OnLookupContextMenu(CString m_csName, CGWContextMenu*& pContextMenu);			// Calls a function on CGWDataSource to retrieve a context menu given its name.
	virtual void OnRemoveContextMenu(CGWContextMenu* pGWContextMenu);							// Calls a function on CGWDataSource to remove a context menu from the collection.
	virtual POSITION OnGetFirstContextMenu();													// Calls a function on CGWDataSource to retrieve the first registered context menu.
	virtual void OnGetNextContextMenu(POSITION& pos, CString& csName, CGWContextMenu*& pContextMenu);	// Calls a function on CGWDataSource to retrieve the next context menu.
	virtual void OnSetDataEntryMode(int nDataEntryMode = 0, int nDataEntryModeState = 0);				// Calls a function on CGWDataSource to set the data entry mode on the data source.
	virtual void OnGetDataEntryMode(int& nDataEntryMode, int& nDataEntryModeState);						// Calls a function on CGWDataSource to get the data entry mode from the data source.
	virtual void OnSetAddRowIndex(int nAddIndex);														// Calls a function on CGWDataSource to	set the "AddRow" index on the data source.
	virtual BOOL OnGetDataSourceError(CPoint& ptErrorCell, int& nErrorCode, CString& csErrorString, BOOL& bDisplayed);	// Calls a function on CGWDataSource to get error status of the data source.
	void SetAddRowIndex(int nAddIndex);															// Calls a function on CGWDataSource to	set the add row index.			
	BOOL BindSheet(int nSheetNdx, void* pUnk);
//}}GW_MEMBERS





//Message handlers that are dispatched from one of the CWnd derived classes.
public:


//Clipboard and OLE Drag and Drop 
//GW_MEMBERS{{(CGWGrid,"Clipboard and OLE Drag and Drop")
	CString GetNextRow(CString* psClipBuffer);		//Retrieves the next data row from a tab delimited buffer.
	CString GetNextColumn(CString* psClipBuffer);	//Retrieves the next data column from a tab delimitted buffer.
	virtual void PasteData(CString& csClipBuffer, int nStartRow, int nStartColumn, int numRows, int numCols, int nSheet = CURRENT_SHEET);	//Pastes data from a tab delimitted buffer into a sheet.
	void SetClipData(CString& csClipBuffer, int nStartRow, int nStartColumn, int numRows, int numCols, int nSheet = CURRENT_SHEET);			//Builds a tab delimitted buffer from data in the grid.
	void SelectionCells();						// Builds an array of CPoints which contains the all cell coordinates for the current selections. 
	void BuildCellList(CRect rectCells);		// Builds an array of CPoints which contains all cell coordinates within a CRect. 
	void GetClipText(CString& csClipBuffer);	//Builds a tab delimited string consisting of the data which is contained in the cells which make up th ecurrent selection region.
	virtual void GetSizeOfGlobalData(CString& csClipBuffer, int& numRows, int& numCols);	//Calculates the number of rows and columns in a tab delimitted buffer.
	virtual CRect GetDropTrackerRect(CString& csBuffer, CPoint point)						//Calculates the client coordinates of a rectangle which would enclose the area covered by a tab delimitted buffer.
		{return CRect(0,0,0,0);}
//}}GW_MEMBERS

//Cell Identification
//GW_MEMBERS{{(CGWGrid,"Cell Identification")
    inline CGWGridCellObject* GetCaptureCell()						// Retrieve the address of the cell which has captured the input focus.
		{return m_pCellCapture;}
	CRuntimeClass* GetDefaultCellClass(int nSheet = CURRENT_SHEET); // Get the RUNTIME_CLASS structure of the default cell type.
	CGWCellSettings* IdentifyCellSettings(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, int nSheet = CURRENT_SHEET);	// Isolate the common settings from a group of cells.
	CGWCellSettings* IdentifyRowSettings(int nBegRowNdx, int nEndRowNdx, int nSheet = CURRENT_SHEET);									// Isolate the common settings from a group of rows.
	CGWCellSettings* IdentifyColSettings(int nBegColNdx, int nEndColNdx, int nSheet = CURRENT_SHEET);									// Isolate the common settings from a group of columns.
	CGWCellSettings* CreateCombinedSettings(CGWCellSettings* pCellSettings,	CGWCellSettings* pRowSettings, CGWCellSettings* pColSettings, int nSheet); //Identify the seetings for an indvidual cell based on settings ranks
//}}GW_MEMBERS

	
//Operations
public:

//GW_MEMBERS{{(CGWGrid,"Grid Operations")
	virtual CGWGridCellObject* GetControlCell()						// Returns a pointer to the GCO which has an active window control.
		{return m_pControlCell;}
	void SetControlCell(CGWGridCellObject* pControlCell);			// Store the address of a GCO which has an active window control.
	virtual void SetCellAllPanes(int nRowNdx, int nColNdx,UINT bScrollToTop = 0, UINT bScrollToLeft = 0) // Sets the currently selected cell for all panes. Data based indexes.
			{};
	static POSITION RegisterGCO(CRuntimeClass* pRuntimeClass);		// Uses the RUNTIME_CLASS strucutre to add an entry to a CMapStringToOb structure associating a GCO name which its RUNTIME_CLASS structure.
	void operator=(const CGWGrid& otherGrid);						// Copies one grid's settings to another
	virtual void AttachDataSource(CGWDataSource* pGWDataSource);	// Attach the grid to a CGWDataSource object which will persist all properties and potentially all data.
	virtual void AttachInternalDataSource();						// Attach the grid to a CCellDataMap object whose lifetime is controlled by the grid.
	void CreateSelectedRgn(CRgn* rgn);								// Create a CRgn object which covers the client area holding the currently selected cells.
	void CreateCurrentCellRgn(CRgn* rgn);							// Create a CRgn object which covers the client area holding the current cell.
	int CellSelection(int nRowNdx, int nColNdx);					// Checks to see if a particular cell is part of any selected region.
	void HoldUpdates(BOOL bUpdates)									// Temporarily Allows or disallows refreshing of the GCO Cache.
		{m_bOKtoRefresh = (bUpdates) ? FALSE : TRUE;} 
    CRuntimeClass* DefineGridCell(UINT nRowNdx, UINT nColNdx, int nSheet = CURRENT_SHEET);			//Returns the address of the RUNTIME_CLASS structure for the GCO class which is mapped to nRowNdx and nColNdx.
    CRuntimeClass* DefineGridCell(CString csClassName);												//Returns the address of the RUNTIME_CLASS structure for the GCO class based on the class name.
 	BOOL LockRow(int nBeginRowNdx, int nEndRowNdx, BOOL bLock = TRUE, int nSheet = CURRENT_SHEET);		//Locks a row to the top of the grid. Locked row indexes must follow sequentially the fixed rows.
 	BOOL LockColumn(int nBeginColNdx, int nEndColNdx, BOOL bLock = TRUE, int nSheet = CURRENT_SHEET);	//Locks a column to the left of the grid. Locked column indexes must follow sequentially the fixed columns.
 	virtual BOOL AddColumn(CRuntimeClass* runtimeClass, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Appends one or more new rows to the sheet.
 	virtual BOOL AddRow(CRuntimeClass* runtimeClass, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Appends one or more new columns to the sheet.
 	virtual BOOL DeleteColumn(int nColNdx, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Deletes one or more rows from the sheet.
 	virtual BOOL DeleteRow(int nRowNdx, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Deletes one or more columns from the sheet.
 	virtual BOOL InsertColumn(CRuntimeClass* runtimeClass, int nColNdx, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Inserts one or more rows into the sheet.
 	virtual BOOL InsertRow(CRuntimeClass* runtimeClass, int nRowNdx, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Inserts one or more columns into the sheet.
	virtual BOOL MoveColumn(int nBegColNdx, int nEndColNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Move one or more rows within the sheet.
	virtual BOOL MoveRow(int nBegRowNdx, int nEndRowNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Move one or more columns within the sheet.
	virtual BOOL CopyColumn(int nBegColNdx, int nEndColNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Copy one or more rows within the sheet.
	virtual BOOL CopyRow(int nBegRowNdx, int nEndRowNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Copy one or more columns within the sheet.
	void BindColumn(int nColNdx, int nFieldNdx, CObject* pObject,  BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Bind a column index to an arbitrary field number or to a field in an external database link.
	void GetCellUnderPt(CPoint& point,CCellContext& CC, CDC* pDC);		//Uses a CCellContext object but only fills in CC.m_nRowNdx and CC.m_nColNdx. 
	void GetCCUnderPt(CPoint& point, CCellContext& CC);					//Initialize a CCellContext object with the cell that contains the point.
	void SetCurCell(int wRowNdx, int wColNdx,UINT nFlags = 0, UINT bScrollToTop = 0, UINT bScrollToLeft = 0);	// Sets the currently selected cell. Data based indexes. bConcat determines whether there will be multiple selected regions.
	BOOL GetSelection(CRect& SelRect, UINT nRectNum);					//Retrieve the grid based coordinates a particula selected region.
	int  GetSelectionCount()											//Get the number of separate selected regions in the current set of selected cells.
		{return m_paSelectionRects.GetSize();}
	void Select(int nLeft, int nTop, int nRight, int nBottom, int nRowNdx, int nColNdx, UINT nRectNum, BOOL bRedraw = TRUE, BOOL bSetCurrent = TRUE); // Selects a region of cells and sets the current cell according to wRow and wCol.
	void SelectRow(int nRowNdx, UINT nSelRectNdx, BOOL bRedraw = TRUE, BOOL bSetCurrent = TRUE);	// Selects an entire row of gridcells.
	void SelectCol(int nColNdx, UINT nSelRectNdx, BOOL bRedraw = TRUE, BOOL bSetCurrent = TRUE);	// Selects an entire row of gridcells.
	void Refresh();								//Refresh the grid and all its properties. Causes GCOs to be destroyed and recreated.
	void SetEditingNow(BOOL bEditingNow);		//Call to inform the grid that a GCO is in edit mode. Typically called when a window control used for editing is created,
	BOOL GetEditingNow()						//Determine if a cell is in editing mode.
		{return m_bEditingNow;} 
	virtual void GetGridWndClientRect(LPRECT rect)		//Retrieve the client rectangle of the grid's window if the window exists.
		{
			rect->top = rect->left = rect->bottom = rect->right = 0;
			if (m_pGridCWnd && m_pGridCWnd->GetSafeHwnd())
				m_pGridCWnd->GetClientRect(rect);
		}
	virtual CScrollBar* GetGridScrollBarCtrl(int nBar)  //Retrieve the pointer to a grid scrollbar if the grid window exists.
		{
			if (m_pGridCWnd && m_pGridCWnd->GetSafeHwnd())
				return m_pGridCWnd->GetScrollBarCtrl(nBar);
			return NULL;
		}
    inline BOOL IsRowSelected()							//Test to see if selection consists of one or more selected rows.
		{return m_bRowSelected;}
    inline BOOL IsColSelected()							//Test to see if selection consists of one or more selected columns.
		{return m_bColumnSelected;}
	inline int GetCurrentSheet(int nSheet = CURRENT_SHEET) //Retrieve the index of the current sheet.
		{return m_nCurrentSheet;}
	inline void SetCurrentSheet(int nIndex)				//Sets the current sheet but does not activate it. See ActivateSheet().
		{   m_nCurrentSheet = nIndex;}
	inline CWnd*    GetGridCWnd()						//Retrieve the CWnd* attached to this grid if it exists.           
		{return m_pGridCWnd;}
    inline int GetVPageSize()							//Get the number of rows currently visible in the grid.
		{return m_nVPageSize;}
    inline int GetHPageSize()							//Get the number of columns currently visible in the grid.
		{return m_nHPageSize;} 
    inline CRect GetGridRect()							//Get the client coordinates of the area of the window which is actually in use by the grid.
		{return m_GridRect;}
    inline CRect GetGridLessFixedRowsNCols()			//Get the client coordinates of the area of the grid less any fixed rows and columns.
		{return m_GridLessFixedRowsNCols;}		
    inline CRect GetGridLessLockedRowsNCols()			//Get the client coordinates of the area of the grid less any locked rows and columns.
		{return m_GridLessLockedRowsNCols;}
	virtual void SetShowTabs(BOOL bShowTabs, BOOL bRefresh = TRUE);		//Make the sheet tabs visible or invisible.
	BOOL GetShowTabs();
	void SetSettingsRank(int nCellSettingsRank, int nRowSettingsRank, int nColSettingsRank);	//Adjust the ranking or priority of cell property settings between row, column and cell settings structure.
//}}GW_MEMBERS
	

//GW_MEMBERS{{(CGWGrid,"Grid Overideables")
	virtual void FlagCellError(int nRowNdx, int nColNdx);	//Called when an error occurs in an CRecordset operation.
	virtual void OnChangeColWidth(int nColNdx, float& nNewWidth, int nUnits = DEFAULT_UNITS);	// Called when a Column was resized. Passes the Column the index.
	virtual void OnChangeRowHeight(int nRowNdx, float& nNewHeight, int nUnits = DEFAULT_UNITS);	// Called when a Row was resized. Passes the Row index.
	virtual void OnSelectionChange(int& nRowNdx, int& nColNdx, CRect* pRect, int nSelRectNdx);	// Called when a different cell is selected.
	virtual void OnPostSelectionChange(int nRowNdx, int nColNdx);			//Called after a selection has been made. It cannot be changed at this point. See also: OnSelectionChange().
	virtual void OnGCOChange(int nRowNdx, int nColNdx, CString csCellText);	//Called when the contents of a GCO has been changed by the user. 
	virtual CString GetSettingsFile()				//Override to adjust the name of the initial settings file.
		{return m_csSettingsFile;}  
	virtual CString GetSettingsFilePath()			//Override to adjust the location of the initial settings file.
		{return m_csSettingsFilePath;}  
	virtual void GridOnInitialUpdate();				//Called as part of the grid initialization phase after the CWnd for the grid has been created. 
	virtual void Initialize();						//This function is called from the constructor and is usually maintained by the GridWiz Wizard.
	virtual void InitializeColWidths();				//Called from OnInitialUpdate to pre-set the widths any columns
	virtual void GridOnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Called in response to a WM_HSCROLL message.
	virtual void GridOnSize(UINT nType, int cx, int cy);							//Called in response to a WM_SIZE message.
	virtual void GridOnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Called in response to a WM_VSCROLL message.
    virtual void GridOnPaint(CPaintDC* pDC);										//Called in response to a WM_PAINT message.
	virtual void GridOnMouseMove(UINT nFlags, CPoint point);						//Called in response to a WM_MOUSEMOVE message.
	virtual void GridOnLButtonDown(UINT nFlags, CPoint point);						//Called in response to a WM_LBUTTONDOWN message.
	virtual void OnLButtonDownTabSet(UINT nFlags, CPoint point);					//Called in response to a WM_LBUTTONDOWN message. (Obsolete)
	virtual void GridOnLButtonUp(UINT nFlags, CPoint point);						//Called in response to a WM_LBUTTONUP message.
	virtual void GridOnRButtonUp(UINT nFlags, CPoint point);						//Called in response to a WM_RBUTTONUP message.
	virtual void GridOnTimer(UINT nIDEvent);										//Called in response to a WM_TIMER message.
	virtual void GridOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);				//Called in response to a WM_KEYDOWN message.
	virtual void GridOnDestroy();													//Called in response to a WM_DESTROY message.
	virtual void GridOnLButtonDblClk(UINT nFlags, CPoint point);					//Called in response to a WM_LBUTTONDBLCLK message.
	virtual void GridOnChar(UINT nChar, UINT nRepCnt, UINT nFlags);					//Called in response to a WM_CHAR message.
	virtual void DoSetCursor(UINT nFlags, CPoint& point);							//Called to allow the grid to set the cursor shape during a WM_MOUSEMOVE message.
    virtual void GridOnUpdate(CGWGrid* pSender, LPARAM lHint, CObject* pHint);		//Called when the Grid in general needs to be updated.                 
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Sheet Operations")
	int GetBoundField(int nColNdx, CObject* pObject, int nSheet = CURRENT_SHEET);	// Retrieve a field index for a previously bound column index.
	CString GetSheetName(int nSheet);							// Get the name of the sheet given its index.
	int GetSheetIndex(CString csSheetName)						// Get the index of the sheet given its name.
	{
		for (int x = 0; x < GetNumSheets(); x++)
		{
			if (GetSheetName(x) == csSheetName)
				return x;
		}
		return -1;
	}
	void SetSheetName(int nSheet, CString csSheetName);			// Set the name of the sheet.
	virtual void ActivateSheet(int nSheet);						// Activate the sheet causing it to evaulate any external database link.
	virtual void RemoveSheet(int nSheet);						// Remove the sheet from the collection of sheets.
	virtual void InsertSheet(int nSheet, CString csCaption);	// Insert a new sheet into the collection of sheets.
	virtual void MoveSheet(int nSheet, int nCount);				// Rearrange the sheets in the collection of sheets.
	virtual int AddSheet(CString csSheetName);					// Append a new sheet to the collection of sheets.
    int GetNumSheets();											// Retrieve the number of sheets in the collection.
	virtual void ResetSheet();									// This function is called when a new sheet is added to make sure that the sheet is built according to the Grid Global settings.
	void ClearSheetData(int nSheet = CURRENT_SHEET)				// Clear the data contained in the sheet.
			{
				OnClearSheetData(nSheet);
				if (m_pGridCWnd)
					m_pGridCWnd->Invalidate();
			}
	void ClearSheetAll(int nSheet = CURRENT_SHEET)				// Clear the data and the cell settings in the sheet.
			{
				OnClearSheetAll(nSheet); 
				Refresh();
			}
	void RefreshSheet(int nSheet = CURRENT_SHEET)				// Force the sheet to recalculate the maximum row and column index.
			{
				OnRefreshSheet(nSheet); 
				Refresh();
			}
	void ResetSheetDBSettings(int nSheet = CURRENT_SHEET);			// Force the sheet to re-evaluate data from a external database link.
	virtual void CheckSheetSettings(CGWDataSource* pGWDataSource);	// Make sure the sheet has a valid Grid settings object.
	void RepaintBookmarkRow(_variant_t& varBookmark){
		ASSERT(m_pGWDataSource);
		int nRow = m_pGWDataSource->GetBookmarkRow(varBookmark, m_nVScrollPos, m_nVScrollPos + m_nVPageSize, m_nCurrentSheet);
		InvalidateRow(nRow,nRow);
	}
	void AppendBookmarkRow(_variant_t& varBookmark){
		ASSERT(m_pGWDataSource);
		int nRow = m_pGWDataSource->AppendBookmarkRow(varBookmark, m_nCurrentSheet);
		AddRow(NULL,1, TRUE);
	}
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWGrid,"Sheet Notification Overideables")
	virtual void OnActivateSheet(int nSheet = CURRENT_SHEET);		// Called in response to the user clicking a sheet tab or when ActivateSheet is called in code. 
	virtual BOOL OnDeactivateSheet(int nSheet = CURRENT_SHEET);		// Called in response to the user clicking a sheet tab.
	virtual void OnAddSheet(CString csCaption)						// Called in response to the user adding a new sheet via the AddSheet function.
	{ };
	virtual void OnRemoveSheet(int nSheet)							// Called in response to the user removing a sheet via the RemoveSheet function.
	{ };
	virtual void OnInsertSheet(int nSheet, CString csCaption)		// Called in response to the user inserting a new sheet via the InsertSheet function.
	{ };
	virtual void OnChangeSheet(int nSheet, CString csCaption)		// Called in response to the user changing the sheet name via the SetSheetName function.
	{ };
	virtual void OnMoveSheet(int nSheet, int nCount)				// Called in response to the user moving a sheet via the MoveSheet function.
	{ };
//}}GW_MEMBERS	
	
//GW_MEMBERS{{(CGWGrid,"Row Properties")
	BOOL SetRowCellType(int nBegRowNdx, int nEndRowNdx,  CString csClassName, int nSheet = CURRENT_SHEET);			//Set the cell type for an entire row or set of rows.
	void SetRowOCXClassName(int nBegRowNdx, int nEndRowNdx, CString csOCXClassName, int nSheet = CURRENT_SHEET);	//Set the OCXClassName for an entire row or set of rows. See Also CGWOCXCell.
	void SetRowProtection(int nBegRowNdx, int nEndRowNdx, BOOL bProtected, int nSheet = CURRENT_SHEET);				//Set cell protection for entire row or set of rows. 
	void SetRowAutomaticBackColor(int nBegRowNdx, int nEndRowNdx, BOOL bAutomatic, int nSheet = CURRENT_SHEET);		//Set the automatic background color for all cells in a row or set of rows. 
	void SetRowAutomaticTextColor(int nBegRowNdx, int nEndRowNdx, BOOL bAutomatic, int nSheet = CURRENT_SHEET);		//Set the automatic text color property for all cells in a row or set of rows.
	void SetRowTextColor(int nBegRowNdx, int nEndRowNdx, COLORREF rgbTextColor, int nSheet = CURRENT_SHEET);		//Set the text color property for all cells in a row or set of rows.
	void SetRowBackColor(int nBegRowNdx, int nEndRowNdx, COLORREF rgbBackColor, int nSheet = CURRENT_SHEET);		//Set the Back Color property for all cells in a row or set of rows.
	void SetRowAutomaticFont(int nBegRowNdx, int nEndRowNdx, BOOL bAutomaticFont, int nSheet = CURRENT_SHEET);		//Set the Automatic Font property for all cells in a row or set of rows.
	void SetRowFont(int nBegRowNdx, int nEndRowNdx, LOGFONT* pLogFont, int nPointSize, int nSheet = CURRENT_SHEET);	//Set the Font property for all cells in a row or set of rows.
	void SetRowFontBold(int nBegRowNdx, int nEndRowNdx, BOOL bFontBold, int nSheet = CURRENT_SHEET);				//Set the Font Bold property for all cells in a row or set of rows.
	void SetRowFontFaceName(int nBegRowNdx, int nEndRowNdx, _TCHAR* lpszFaceName, int nSheet = CURRENT_SHEET);		//Set the Font Face Name property for all cells in a row or set of rows.
	void SetRowFontItalic(int nBegRowNdx, int nEndRowNdx, BOOL bFontItalic, int nSheet = CURRENT_SHEET);			//Set the Font Italic property for all cells in a row or set of rows.
	void SetRowFontPointSize(int nBegRowNdx, int nEndRowNdx, int nFontPointSize, int nSheet = CURRENT_SHEET);		//Set the Font Point Size property for all cells in a row or set of rows.
	void SetRowFontStrikeThru(int nBegRowNdx, int nEndRowNdx, BOOL bFontStrikeThru, int nSheet = CURRENT_SHEET);	//Set the Font Strike Thru property for all cells in a row or set of rows.
	void SetRowFontUnderline(int nBegRowNdx, int nEndRowNdx,BOOL bFontUnderline, int nSheet = CURRENT_SHEET);		//Set the Font Underline property for all cells in a row or set of rows.
	void SetRowBorderStyle(int nBegRowNdx,  int nEndRowNdx, CRect rectBorderStyles, int nSheet = CURRENT_SHEET);	//Set the Border Style property for all cells in a row or set of rows.
	void SetRowBorderColor(int nBegRowNdx,  int nEndRowNdx, COLORREF rgbBorderColor, int nSheet = CURRENT_SHEET);	//Set the Border Color property for all cells in a row or set of rows.
	void SetRowFormat(int nBegRowNdx,  int nEndRowNdx, CString csFormat, int nSheet = CURRENT_SHEET);				//Set the Format property for all cells in a row or set of rows.
	void SetRowInputMask(int nBegRowNdx,  int nEndRowNdx, CString csInputMask, int nSheet = CURRENT_SHEET);			//Set the Input Mask property for all cells in a row or set of rows.
	void SetRowEditFlag(int nBegRowNdx,  int nEndRowNdx, int nEditFlag, int nSheet = CURRENT_SHEET);				//Set the Edit Flag property for all cells in a row or set of rows.
	void SetRowControlStyles(int nBegRowNdx,  int nEndRowNdx, DWORD dwPrimaryControlStyle, DWORD dwSecondaryControlStyle, int nSheet = CURRENT_SHEET);	//Set the Control Styles property for all cells in a row or set of rows.
	void SetRowExtendedCellStyle(int nBegRowNdx,  int nEndRowNdx, DWORD dwExtendedCellStyles, int nSheet = CURRENT_SHEET);	//Set the Extended Cell Styles property for all cells in a row or set of rows.
	void SetRowTextAlignment(int nBegRowNdx,  int nEndRowNdx, UINT nVertAlignment, UINT nHorzAlignment, BOOL bWordWrap, int nSheet = CURRENT_SHEET);	//Set the Text Alignment property for all cells in a row or set of rows.
	void SetRowTextOrientation(int nBegRowNdx, int nEndRowNdx, int nOrientation, int nSheet = CURRENT_SHEET);				//Set the Text Orientation property for all cells in a row or set of rows.
	void SetRowPattern(int nBegRowNdx, int nEndRowNdx, UINT nPatternID, COLORREF rgbForecolor, int nSheet = CURRENT_SHEET);	//Set the Pattern property for all cells in a row or set of rows.
	void SetRowValidStrings(int nBegRowNdx, int nEndRowNdx,	CGWValidStrings* pValidStrings, int nSheet = CURRENT_SHEET);	//Set the Valid Strings property for all cells in a row or set of rows.
	void SetRowContextMenu(int nBegRowNdx, int nEndRowNdx,CGWContextMenu* pContextMenu, int nSheet = CURRENT_SHEET);		//Set the Context Menu property for all cells in a row or set of rows.
	void SetRowMinimumValue(int nBegRowNdx, int nEndRowNdx, double dMinimum, int nSheet = CURRENT_SHEET);			//Set the Minimum Value property for all cells in a row or set of rows.
	void SetRowMaximumValue(int nBegRowNdx, int nEndRowNdx, double dMaximum, int nSheet = CURRENT_SHEET);			//Set the Maximum Value property for all cells in a row or set of rows.
	void SetRowMaxTextLength(int nBegRowNdx, int nEndRowNdx, int nMaxLen, int nSheet = CURRENT_SHEET);				//Set the Max Text Length property for all cells in a row or set of rows.
	void SetRowAutoSizeRowHeight(int nBegRowNdx, int nEndRowNdx, BOOL bAutoSizeRowHeight, int nSheet = CURRENT_SHEET);		//Automatically size height of row to fit wrapped text in specified rows.
	void SetRowAutoSizeColumnWidth(int nBegRowNdx, int nEndRowNdx, BOOL bAutoSizeColumnWidth, int nSheet = CURRENT_SHEET);	//Automatically size width of column to fit single line text for specified rows.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Row Operations")
	int GetRowNdx(int wRow);	//Retrieve the data Row index for the given visual grid row. 
	int GridRow(int nRowNdx);	//Give back the nth row/col from the top of the grid window based
	float  GetRowHeight(int nRowNdx, int nUnits = DEFAULT_UNITS, int nSheet = CURRENT_SHEET);			// Retrieves the Height in device points for a row based on data indexes.	
	void SetRowHeight(int nRowNdx, float nRowHeight, BOOL bRepaint = TRUE, int nUnits = DEFAULT_UNITS, int nSheet = CURRENT_SHEET);	// Sets the height of a row (logical points) based on data indexes.
	void ShowRow(int wRowNdx,BOOL bVisible = TRUE,  BOOL bRedraw = TRUE, int nSheet = CURRENT_SHEET);	//Determines whether a grid row from being drawn. Data based index.
	BOOL IsRowHidden(int nRowNdx, int nSheet = CURRENT_SHEET);		//Determines whether the row at nRowNdx is a hidden row.
	BOOL IsRowProtected(long nRowNdx, int nSheet = CURRENT_SHEET);	//Determines whether the row at nRowNdx is a protected.
	BOOL RowVisible(int nRowNdx);									//Determines whether the row at nRowNdx is currently in view?
	BOOL RowSelected(int nRowNdx, int nSheet = CURRENT_SHEET);		//Determines whether a particular row is part of a selected region.
	void ResetRow(int nBegRowNdx, int nEndRowNdx);					//Reset all the cells in a row or set of rows.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Row Notification Overideables")
	virtual void OnAddRow(int nCount, int nSheet = CURRENT_SHEET);					//Called in response to the AddRow function.
	virtual void OnDeleteRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);	//Called in response to the DeleteRow function or the user deleteing a row via the keyboard.	
	virtual void OnInsertRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);	//Called in response to the InsertRow function.
	virtual void OnMoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Called in response to the MoveRow function or a drag and drop operation.
	virtual void OnCopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Called in response to the CopyRow function or a drag and drop operation.
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWGrid,"Column Properties")
	BOOL SetColCellType(int nBegColNdx, int nEndColNdx, CString csClassName, int nSheet = CURRENT_SHEET);			//Set the cell type for an entire column or set of columns.
	void SetColOCXClassName(int nBegColNdx, int nEndColNdx, CString csOCXClassName, int nSheet = CURRENT_SHEET);	//Set the OCXClassName for an entire column or set of columns. See Also CGWOCXCell.
	void SetColProtection(int nBegColNdx, int nEndColNdx, BOOL bProtected, int nSheet = CURRENT_SHEET);				//Set cell protection for entire column or set of columns. 
	void SetColAutomaticBackColor(int nBegColNdx, int nEndColNdx, BOOL bAutomatic, int nSheet = CURRENT_SHEET);		//Set the automatic background color for all cells in a column or set of columns. 
	void SetColAutomaticTextColor(int nBegColNdx, int nEndColNdx, BOOL bAutomatic, int nSheet = CURRENT_SHEET);		//Set the automatic text color property for all cells in a column or set of columns.
	void SetColTextColor(int nBegColNdx, int nEndColNdx, COLORREF rgbTextColor, int nSheet = CURRENT_SHEET);		//Set the text color property for all cells in a column or set of columns.
	void SetColBackColor(int nBegColNdx, int nEndColNdx, COLORREF rgbBackColor, int nSheet = CURRENT_SHEET);		//Set the Back Color property for all cells in a column or set of columns.
	void SetColAutomaticFont(int nBegColNdx, int nEndColNdx, BOOL bAutomaticFont, int nSheet = CURRENT_SHEET);		//Set the Automatic Font property for all cells in a column or set of columns.
	void SetColFont(int nBegColNdx, int nEndColNdx, LOGFONT* pLogFont, int nPointSize, int nSheet = CURRENT_SHEET); //Set the Font property for all cells in a column or set of columns.
	void SetColFontBold(int nBegColNdx, int nEndColNdx, BOOL bFontBold, int nSheet = CURRENT_SHEET);				//Set the Font Bold property for all cells in a column or set of columns.
	void SetColFontFaceName(int nBegColNdx, int nEndColNdx, _TCHAR* lpszFaceName, int nSheet = CURRENT_SHEET);		//Set the Font Face Name property for all cells in a column or set of columns.
	void SetColFontItalic(int nBegColNdx, int nEndColNdx, BOOL bFontItalic, int nSheet = CURRENT_SHEET);			//Set the Font Italic property for all cells in a column or set of columns.
	void SetColFontPointSize(int nBegColNdx, int nEndColNdx, int nFontPointSize, int nSheet = CURRENT_SHEET);		//Set the Font Point Size property for all cells in a column or set of columns.
	void SetColFontStrikeThru(int nBegColNdx, int nEndColNdx, BOOL bFontStrikeThru, int nSheet = CURRENT_SHEET);	//Set the Font Strike Thru property for all cells in a column or set of columns.
	void SetColFontUnderline(int nBegColNdx, int nEndColNdx, BOOL bFontUnderline, int nSheet = CURRENT_SHEET);		//Set the Font Underline property for all cells in a column or set of columns.
	void SetColBorderStyle(int nBegColNdx, int nEndColNdx, CRect rectBorderStyles, int nSheet = CURRENT_SHEET);		//Set the Border Style property for all cells in a column or set of columns.
	void SetColBorderColor(int nBegColNdx, int nEndColNdx, COLORREF rgbBorderColor, int nSheet = CURRENT_SHEET);	//Set the Border Color property for all cells in a column or set of columns.
	void SetColFormat(int nBegColNdx, int nEndColNdx, CString csFormat, int nSheet = CURRENT_SHEET);				//Set the Format property for all cells in a column or set of columns.
	void SetColInputMask(int nBegColNdx, int nEndColNdx, CString csFormat, int nSheet = CURRENT_SHEET);				//Set the Input Mask property for all cells in a column or set of columns.
	void SetColEditFlag(int nBegColNdx, int nEndColNdx, int nEditFlag, int nSheet = CURRENT_SHEET);					//Set the Edit Flag property for all cells in a column or set of columns.
	void SetColControlStyles(int nBegColNdx, int nEndColNdx, DWORD dwPrimaryControlStyle, DWORD dwSecondaryControlStyle, int nSheet = CURRENT_SHEET);	//Set the Control Styles property for all cells in a column or set of columns.
	void SetColExtendedCellStyle(int nBegColNdx,  int nEndColNdx, DWORD dwExtendedCellStyles, int nSheet = CURRENT_SHEET);	//Set the Extended Ce;; Styles property for all cells in a column or set of columns.
	void SetColTextAlignment(int nBegColNdx, int nEndColNdx, UINT nVertAlignment, UINT nHorzAlignment, BOOL bWordWrap, int nSheet = CURRENT_SHEET);		//Set the Text Alignment property for all cells in a column or set of columns.
	void SetColTextOrientation(int nBegColNdx, int nEndColNdx, int nOrientation, int nSheet = CURRENT_SHEET);							//Set the Text Orientation property for all cells in a column or set of columns.
	void SetColPattern(int nBegColNdx, int nEndColNdx, UINT nPatternID, COLORREF rgbForecolor, int nSheet = CURRENT_SHEET);				//Set the Pattern property for all cells in a column or set of columns.
	void SetColValidStrings(int nBegColNdx, int nEndColNdx,	CGWValidStrings* pValidStrings, int nSheet = CURRENT_SHEET);				//Set the Valid Strings property for all cells in a column or set of columns.
	void SetColContextMenu(int nBegColNdx, int nEndColNdx, CGWContextMenu* pContextMenu, int nSheet = CURRENT_SHEET);					//Set the Context Menu property for all cells in a column or set of columns.
	void SetColMinimumValue(int nBegColNdx, int nEndColNdx, double dMinimum, int nSheet = CURRENT_SHEET);				//Set the Minimum Value property for all cells in a column or set of columns.
	void SetColMaximumValue(int nBegColNdx, int nEndColNdx, double dMaximum, int nSheet = CURRENT_SHEET);				//Set the Maximum Value property for all cells in a column or set of columns.
	void SetColMaxTextLength(int nBegColNdx, int nEndColNdx, int nMaxLen, int nSheet = CURRENT_SHEET);					//Set the Max Text Length property for all cells in a column or set of columns.
	void SetColAutoSizeRowHeight(int nBegColNdx, int nEndColNdx, BOOL bAutoSizeRowHeight, int nSheet = CURRENT_SHEET);		//Automatically size height of row to fit wrapped text in specified columns.
	void SetColAutoSizeColumnWidth(int nBegColNdx, int nEndColNdx, BOOL bAutoSizeColumnWidth, int nSheet = CURRENT_SHEET);	//Automatically size width of column to fit single line text for specified columns.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Column Operations")
	inline int GetColNdx(int wCol)						//Retrieve the data column index for the given visual grid column.
		{ return ((wCol >= m_nFixedColumns + m_nLockedColumns)
		  ? (wCol + m_nHScrollPos - m_nFixedColumns - m_nLockedColumns)
		  : (wCol));}
	int GridCol(int nColNdx);							//Retrieve the ordinal number of the column from the left side of the grid.
	float  GetColWidth(int nColNdx, int nUnits = DEFAULT_UNITS, int nSheet = CURRENT_SHEET);				// Retrieves the Width of a column in device points
	void SetColWidth(int nColNdx, float nColumnWidth, BOOL bRepaint = TRUE, int nUnits = DEFAULT_UNITS, int nSheet = CURRENT_SHEET);	// Sets the width of a column (logical points) based on data indexes.
	void ShowColumn(int wColNdx,BOOL bVisible = TRUE,  BOOL bRedraw = TRUE, int nSheet = CURRENT_SHEET);	//Determines whether a grid column from being drawn. Data based index.
	BOOL IsColumnHidden(int nColNdx, int nSheet = CURRENT_SHEET);		//Determines whether a particular column is hidden.
	BOOL IsColumnProtected(long nColNdx, int nSheet = CURRENT_SHEET);	//Determines whether a particular column is protected.
	BOOL ColVisible(int nColNdx);										//Determines whether a particular column is currently in view?
	BOOL ColSelected(int nColNdx, int nSheet = CURRENT_SHEET);			//Determines whether a particular column is part of a selected region.
	void ResetColumn(int nBegColNdx, int nEndColNdx);					//Reset all the cells within a column or range of columns.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Column Notification Overideables")
	virtual void OnAddColumn(int nCount, int nSheet = CURRENT_SHEET);					//Called in response to the AddColumn function.
	virtual void OnDeleteColumn(int nColNdx, int nCount, int nSheet = CURRENT_SHEET);	//Called in response to the DeleteColumn function or the user deleteing a row via the keyboard.	
	virtual void OnInsertColumn(int nColNdx, int nCount, int nSheet = CURRENT_SHEET);	//Called in response to the InsertColumn function.
	virtual void OnMoveColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int  nSheet = CURRENT_SHEET);	//Called in response to the MoveColumn function or a drag and drop operation.nSheet = CURRENT_SHEET);
	virtual void OnCopyColumn(UINT nBegColNdx, UINT nEndColNdx, UINT nInsertBefore, int  nSheet = CURRENT_SHEET);	//Called in response to the CopyColumn function or a drag and drop operation.nSheet = CURRENT_SHEET);
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWGrid,"Cell Properties")
	BOOL SetCellType(int nRowNdx, int nColNdx, CString csClassName, int nSheet = CURRENT_SHEET);												//Set the cell type for an individual cell.
	BOOL SetCellType(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, CString csClassName, int nSheet = CURRENT_SHEET);			//Set the cell type for a range of cells.
	void SetOCXClassName(int nRowNdx, int nColNdx, CString csOCXClassName, int nSheet = CURRENT_SHEET);											//Set the OCXClassName for an individual cell.. See Also CGWOCXCell.
	void SetOCXClassName(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, CString csOCXClassName, int nSheet = CURRENT_SHEET);	//Set the OCXClassName for a range of cells.
	void SetCellProtection(int nRowNdx, int nColNdx, BOOL bProtected, int nSheet = CURRENT_SHEET);												//Set cell protection for an individual cell. 
	void SetCellProtection(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bProtected, int nSheet = CURRENT_SHEET);		//Set cell protection for a range of cells.
	void SetAutomaticBackColor(int nRowNdx, int nColNdx,  BOOL bAutomatic, int nSheet = CURRENT_SHEET);											//Set the automatic background color for an individual cell.
	void SetAutomaticBackColor(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bAutomatic, int nSheet = CURRENT_SHEET);	//Set the automatic background color a range of cells.
	void SetAutomaticTextColor(int nRowNdx, int nColNdx,  BOOL bAutomatic, int nSheet = CURRENT_SHEET);											//Set the automatic text color property for an individual cell.
	void SetAutomaticTextColor(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bAutomatic, int nSheet = CURRENT_SHEET);	//Set the automatic text color property for a range of cells.
	void SetTextColor(int nRowNdx, int nColNdx,  COLORREF rgbTextColor, int nSheet = CURRENT_SHEET);											//Set the text color property for an individual cell.
	void SetTextColor(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, COLORREF rgbTextColor, int nSheet = CURRENT_SHEET);		//Set the text color property for a range of cells.
	void SetBackColor(int nRowNdx, int nColNdx,  COLORREF rgbBackColor, int nSheet = CURRENT_SHEET);											//Set the Back Color property for an individual cell.
	void SetBackColor(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, COLORREF rgbBackColor, int nSheet = CURRENT_SHEET);		//Set the Back Color property for a range of cells.
	void SetAutomaticFont(int nRowNdx, int nColNdx, BOOL bAutomaticFont, int nSheet = CURRENT_SHEET);											//Set the Automatic Font property for an individual cell.
	void SetAutomaticFont(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bAutomaticFont, int nSheet = CURRENT_SHEET);		//Set the Automatic Font property for a range of cells.
	void SetCellFont(int nRowNdx, int nColNdx, LOGFONT* pLogFont, int nPointSize, int nSheet = CURRENT_SHEET);									//Set the Font property for an individual cell.
	void SetCellFont(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx,  LOGFONT* pLogFont, int nPointSize, int nSheet = CURRENT_SHEET); //Set the Font property for a range of cells.
	void SetCellFontBold(int nRowNdx, int nColNdx,BOOL bFontBold, int nSheet = CURRENT_SHEET);													//Set the Font Bold property for an individual cell.
	void SetCellFontBold(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bFontBold, int nSheet = CURRENT_SHEET);			//Set the Font Bold property for a range of cells.
	void SetCellFontFaceName(int nRowNdx, int nColNdx, _TCHAR* lpszFaceName, int nSheet = CURRENT_SHEET);										//Set the Font Face Name property for an individual cell.
	void SetCellFontFaceName(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx,_TCHAR* lpszFaceName, int nSheet = CURRENT_SHEET);	//Set the Font Face Name property for a range of cells.
	void SetCellFontItalic(int nRowNdx, int nColNdx,BOOL bFontItalic, int nSheet = CURRENT_SHEET);												//Set the Font Italic property for an individual cell.
	void SetCellFontItalic(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx,BOOL bFontItalic, int nSheet = CURRENT_SHEET);		//Set the Font Italic property for a range of cells.
	void SetCellFontPointSize(int nRowNdx, int nColNdx, int nFontPointSize, int nSheet = CURRENT_SHEET);										//Set the Font Point Size property for an individual cell.
	void SetCellFontPointSize(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, int nFontPointSize, int nSheet = CURRENT_SHEET);	//Set the Font Point Size property for a range of cells.
	void SetCellFontStrikeThru(int nRowNdx, int nColNdx, BOOL bFontStrikeThru, int nSheet = CURRENT_SHEET);										//Set the Font Strike Thru property for an individual cell.
	void SetCellFontStrikeThru(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bFontStrikeThru, int nSheet = CURRENT_SHEET);	//Set the Font Strike Thru property for a range of cells.
	void SetCellFontUnderline(int nRowNdx, int nColNdx,BOOL bFontUnderline, int nSheet = CURRENT_SHEET);										//Set the Font Underline property for an individual cell.
	void SetCellFontUnderline(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx,BOOL bFontUnderline, int nSheet = CURRENT_SHEET);	//Set the Font Underline property for a range of cells.
	void SetBorderStyle(int nRowNdx, int nColNdx, CRect rectBorderStyles, int nSheet = CURRENT_SHEET);											//Set the Border Style property for an individual cell.
	void SetBorderStyle(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, CRect rectBorderStyles, int nSheet = CURRENT_SHEET);	//Set the Border Style property for a range of cells.
	void SetBorderColor(int nRowNdx, int nColNdx, COLORREF rgbBorderColor, int nSheet = CURRENT_SHEET);											//Set the Border Color property for an individual cell.
	void SetBorderColor(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, COLORREF rgbBorderColor, int nSheet = CURRENT_SHEET);	//Set the Border Color property for a range of cells.
	void SetFormat(int nRowNdx, int nColNdx, CString csFormat, int nSheet = CURRENT_SHEET);														//Set the Format property for an individual cell.
	void SetFormat(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, CString csFormat, int nSheet = CURRENT_SHEET);				//Set the Format property for a range of cells.
	void SetInputMask(int nRowNdx, int nColNdx, CString csInputMask, int nSheet = CURRENT_SHEET);												//Set the Input Mask property for an individual cell.
	void SetInputMask(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, CString csInputMask, int nSheet = CURRENT_SHEET);			//Set the Input Mask property for a range of cells.
	void SetEditFlag(int nRowNdx, int nColNdx, int nEditFlag, int nSheet = CURRENT_SHEET);														//Set the Edit Flag property for an individual cell.
	void SetEditFlag(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, int nEditFlag, int nSheet = CURRENT_SHEET);				//Set the Edit Flag property for a range of cells.
	void SetControlStyles(int nRowNdx, int nColNdx, DWORD dwPrimaryControlStyle, DWORD dwSecondaryControlStyle, int nSheet = CURRENT_SHEET);	//Set the Control Styles property for an individual cell.
	void SetControlStyles(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx,DWORD dwPrimaryControlStyle, DWORD dwSecondaryControlStyle, int nSheet = CURRENT_SHEET);	//Set the Control Styles property for a range of cells.
	void SetExtendedCellStyle(int nRowNdx, int nColNdx, DWORD dwExtendedCellStyle, int nSheet = CURRENT_SHEET);	//Set the Extended Cell Styles property for an individual cell.
	void SetExtendedCellStyle(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx,DWORD dwExtendedCellStyle, int nSheet = CURRENT_SHEET);	//Set the Extended Cell Styles property for a range of cells.
	void SetCellBitmap(int nRowNdx, int nColNdx, HBITMAP hBitmap, int nSheet = CURRENT_SHEET);	//Set the Extended Cell Styles property for an individual cell.
	void SetCellBitmap(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, HBITMAP hBitmap, int nSheet = CURRENT_SHEET);	//Set the Extended Cell Styles property for a range of cells.
	void SetCellBitmapAlignment(int nRowNdx, int nColNdx, DWORD dwBitmapAlignment, int nSheet = CURRENT_SHEET);	//Set the Extended Cell Styles property for an individual cell.
	void SetCellBitmapAlignment(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, DWORD dwBitmapAlignment, int nSheet = CURRENT_SHEET);	//Set the Extended Cell Styles property for a range of cells.
	void SetTextAlignment(int nRowNdx, int nColNdx, UINT nVertAlignment, UINT nHorzAlignment, BOOL bWordWrap, int nSheet = CURRENT_SHEET);											//Set the Text Alignment property for an individual cell.
	void SetTextAlignment(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, UINT nVertAlignment,UINT nHorzAlignment, BOOL bWordWrap, int nSheet = CURRENT_SHEET);		//Set the Text Alignment property for a range of cells.
	void SetTextOrientation(int nRowNdx, int nColNdx, int nOrientation, int nSheet = CURRENT_SHEET);											//Set the Text Orientation property for an individual cell.
	void SetTextOrientation(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, int nOrientation, int nSheet = CURRENT_SHEET);		//Set the Text Orientation property for a range of cells.
	void SetPattern(int nRowNdx, int nColNdx, UINT nPatternID, COLORREF rgbForecolor, int nSheet = CURRENT_SHEET);								//Set the Pattern property for an individual cell.
	void SetPattern(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, UINT nPatternID, COLORREF rgbForecolor, int nSheet = CURRENT_SHEET);	//Set the Pattern property for a range of cells.
	void SetValidStrings(int nRowNdx, int nColNdx, CGWValidStrings* pValidStrings, int nSheet = CURRENT_SHEET);									//Set the Valid Strings property for an individual cell.
	void SetValidStrings(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, CGWValidStrings* pValidStrings, int nSheet = CURRENT_SHEET);		//Set the Valid Strings property for a range of cells.
	void SetContextMenu(int nRowNdx, int nColNdx, CGWContextMenu* pContextMenu, int nSheet = CURRENT_SHEET);									//Set the Context Menu property for an individual cell.
	void SetContextMenu(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, CGWContextMenu* pContextMenu, int nSheet = CURRENT_SHEET);			//Set the Context Menu property for a range of cells.
	void GroupCells(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, int nSheet = CURRENT_SHEET);								//Take a group of individual cells and group them together making one cell.
	void UnGroupCells(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, int nSheet = CURRENT_SHEET);								//Take a group cell and break it up into its individual cells.
	void SetCellGroup(int nRowNdx, int nColNdx, CRect& rectCellGroup, int nSheet);																//Assign a cell group to an individual cell. 
	BOOL GetCellGroup(int nRowNdx, int nColNdx, CRect& rectCellGroup, int nSheet);																//Retrieves the cell group for a cell. 
	void SetMinimumValue(int nRowNdx, int nColNdx, double dMinimum, int nSheet = CURRENT_SHEET);												//Set the Minimum Value property for an individual cell.
	void SetMinimumValue(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, double dMaximum, int nSheet = CURRENT_SHEET);			//Set the Minimum Value property for a range of cells.
	void SetMaximumValue(int nRowNdx, int nColNdx, double dMinimum, int nSheet = CURRENT_SHEET);												//Set the Maximum Value property for an individual cell.
	void SetMaximumValue(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, double dMaximum, int nSheet = CURRENT_SHEET);			//Set the Maximum Value property for a range of cells.
	void SetMaxTextLength(int nRowNdx, int nColNdx, int nMaxLen, int nSheet = CURRENT_SHEET);													//Set the Max Text Length property for an individual cell.
	void SetMaxTextLength(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, int nMaxLen, int nSheet = CURRENT_SHEET);				//Set the Max Text Length property for a range of cells.
	void SetAutoSizeRowHeight(int nRowNdx, int nColNdx, BOOL bAutoSizeRowHeight, int nSheet = CURRENT_SHEET);											//Automatically size height of row to fit wrapped text.
	void SetAutoSizeRowHeight(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bAutoSizeRowHeight, int nSheet = CURRENT_SHEET);		//Automatically size width of column to fit single line text.
	void SetAutoSizeColumnWidth(int nRowNdx, int nColNdx, BOOL bAutoSizeColumnWidth, int nSheet = CURRENT_SHEET);										//Automatically size height of row to fit wrapped text in range of cells.
	void SetAutoSizeColumnWidth(int nBegRowNdx, int nBegColNdx, int nEndRowNdx, int nEndColNdx, BOOL bAutoSizeColumnWidth, int nSheet = CURRENT_SHEET);	//Automatically size width of column to fit single line text for range of cells.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Cell Operations")
	CRect GetCellRect(int nRowNdx, int nColNdx, CDC* pDC = NULL, BOOL bAccountForGroups = TRUE);	// Retrieves the CRect for a grid cell based on data indexes in Device Units.
	CRect GetTextRect(int nRowNdx, int nColNdx, CDC* pDC);											// Retrieves the Text rect area of a cell in logical points.
	CGWGridCellObject* GetGCO(int nRow, int nCol);													// Retreive a GCO pointer for a particular row and column.
	BOOL IsCellProtected(long nRowNdx, long nColNdx, int nSheet = CURRENT_SHEET);					// Determines whether an individual cell is protected.
	BOOL CellSelected(int nRowNdx, int nColNdx, int nSheet = CURRENT_SHEET);						// Checks to see if a particular cell is contained in a selected region
	BOOL UpdateCurrentCell();																		// Forces the current cell to validate and commit any changed data
	void ResetCell(int nRowNdx, int nColNdx, BOOL bRedraw = TRUE);									// Forces a cell to reload its preperties from the persistent data source.
    CGWGridCellObject*& GetFocusCell()																// Returns a pointer to the cell which currently has focus.
		{return m_pGCOFocus;}  
	void SetCellText(int nRowNdx, int nColNdx, LPTSTR lpszCellText, int nSheetNdx = CURRENT_SHEET);	// Set the string value of a cell.
	CString GetCellText(int nRowNdx, int nColNdx, int nSheetNdx = CURRENT_SHEET);					// Get the string value of a cell.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Standard Cell Notifications")
	virtual void OnCellDeactivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch)	//This virtual function is fired from a GCO to notify the grid that the editing control is about to be removed from a cell and destroyed.
		{};
	virtual void OnCellActivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch)		//This virtual function is fired from a GCO to notify the grid that the editing control is about to displayed and activated.
		{};
	virtual void OnCellClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO)														//This virtual function is fired from a GCO to notify the grid that the cell has received a "Click" event.
		{ };	
	virtual void OnCellDblClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO)													//This virtual function is fired from a GCO to notify the grid that the cell has received a "DblClk" event.
		{ };	
	virtual void OnCellCreateHwnd(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch)	//This virtual function is fired from a GCO to notify the grid that the cell's editing control has been created.
		{ };	
	virtual void OnCellDestroyHwnd(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch)	//This virtual function is fired from a GCO to notify the grid that the cell's editing control is about to be destroyed.
		{ };	
	virtual void OnCellChar(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags)			//This virtual function is fired from a GCO to notify the grid that the cell just received a WM_CHAR message.
		{ };	
	virtual void OnCellKeyDown(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags)			//This virtual function is fired from a GCO to notify the grid that the cell just received a WM_KEYDOWN message.
		{ };		
	virtual void OnCellKeyUp(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT& nChar, UINT& nRepCnt, UINT& nFlags)			//This virtual function is fired from a GCO to notify the grid that the cell just received a WM_KEYUP message.
		{ };	
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWGrid,"Special Cell Notifications")
	virtual void OnCellSelChange(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, int nItemCount, CString* pSelection, void* pExtraData, int* pItems, BOOL& bSendExtraData);	//Called from a GCO with a drop down list to notify the grid that the user has made a selection in the list.
	virtual void OnCellNotify(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT nNotification)		//Generic mechanism for GCOs to pass custom notifications to the grid.
		{ }; 
	virtual void OnCellError(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO)								//Called when a cell detects an error through a validation routine.
		{ }; 
	virtual BOOL OnCellValidateData(int nRowNdx, int nColNdx, CString& csFormatedText)						//Called from the GCO to allow grid perform custom validations on cells before the data is committed to the data source.
		{return TRUE;}
	virtual void OnGetCellDropDownGrid(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CGWGridPopup*& pPopupGrid, CRect& CtrlRect, int& nNumItems);	//Called by the CGWDropDownGridCell Object to allow the grid to identify a custom pop-up grid to be displayed when the user clicks the "down arrow".
	virtual BOOL OnCellDrawToDC(int nRowNdx, int nColNdx, CRect rectCell, CDC* pDC, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch)	//Called from the main drawing routine to allow the grid to take over drawing for certain cells. See Also: m_bWantDrawNotify
		{return FALSE;};	
//}}GW_MEMBERS	

//Modes and States.
//GW_MEMBERS{{(CGWGrid,"Modes and States")
	virtual BOOL OnGetDesignMode();													//Retrieves the design mode setting.
	virtual void OnSetDesignMode(BOOL bDesignMode);									//Sets the Design mode member.
	void SetDataEntryMode(int nDataEntryMode = 0, int nDataEntryModeState = 0);		//Sets the data entry mode for the grid. Used by the "AddRow" feature only.
	void GetDataEntryMode(int& nDataEntryMode, int& nDataEntryModeState);			//Gets the data entry mode for the grid. Used by the "AddRow" feature only.
    BOOL IsGridEnabled()															//Retrieves the enabled status of the grid.
		{return m_bEnabled;}    
    void SetGridEnabled(BOOL bEnabled)												//Sets the enabled status of the entire grid.
		{m_bEnabled = bEnabled; Refresh();}
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Drawing Operations")
	void InvalidateCell(int nRowNdx, int nColNdx, BOOL bErase = TRUE);				//Force a cell to repaint itself.
	void InvalidateRow(int nBeginRowNdx, int nEndRowNdx, BOOL bErase = TRUE);		//Force a set of rows to repaint.
	void InvalidateColumn(int nBeginColNdx, int nEndColNdx, BOOL bErase = TRUE);	//Force a set of columns to repaint.
	void InvalidateRange(int nBeginRowNdx, int nBeginColNdx, int nEndRowNdx, int nEndColNdx, BOOL bErase = TRUE);	//Force a set of cells to repaint.
	void InvertSelection();							// Inverts the current selected range and current cell.
	void InvertCurrentCell();						// Inverts the current current cell.
	void InvalidateSelection();						// Force the selected cells to repaint.
	CBrush* CreateCachedBrush(COLORREF rgbColor);	// Create a cached brush for a GCO
	CFont* CreateCachedFont(LOGFONT lf);			// Create a cached font for a GCO
	CGWGridDC* GetCachedDC(CGWGrid* pGrid); 		// Retrieve the client DC for the grid
	virtual void UpdateDrawingTools(CDC* pDC, LOGFONT* pLogFont, int nPointSize = 0); // Deletes and recreates font and drawing tools 
	inline CFont*   GetCurrentFont()				// Retrieve the current font.
		{return &m_CurrentFont;}				
	inline CPen*    GetGridLinePen()				// Retrieve the current grid line pen.
		{return &m_GridLinePen;}
	inline CBrush*  GetBackgroundBrush()			// Retrieve the current background brush.
		{return &m_BackgroundBrush;}
	inline CBrush*  GetFixedCellBrush()				// Retrieve the current fixed cell brush.
		{return &m_FixedCellBrush;}
	void SetGridFont(LOGFONT* lf, BOOL bRedraw = TRUE, int nPointSize = 0, int nSheet = CURRENT_SHEET);	// Call this to set the current font.
	LOGFONT* GetGridFont()							// Get the address of the grid logfont structure.
		{return &m_LogFont;}
//}}GW_MEMBERS	


    
//GW_MEMBERS{{(CGWGrid,"Grid Sizing")
	virtual void SizeGridToFit(BOOL bHorizontal, BOOL bVertical)	//For a grid view or control to change its size to fit the current data.
		{};
	virtual void SetIntegralHeight()								//Change the height of a grid view or control fit an exact number of rows.
		{};
 	virtual void RecalcGridLayout(UINT nOperation, int nHint = 0);	//Force the GCOs to be destroyed and recreated.
	BOOL ResizeParentToGrid();										// Resize the frame  to match the size of the grid.
//}}GW_MEMBERS	
	
//GW_MEMBERS{{CGWGrid, "Drawing Overideables")
	virtual CRect CalcDrawRect(CRect rectCell, CDC* pDC)			//Calculate the coordinates to be used for drawing the cell.
											{ CRect rectDrawRect(rectCell.left,
																   rectCell.top,
																   rectCell.right += 1,
   																   rectCell.bottom += 1);
											    return rectDrawRect;
											 }
	virtual CRect CalcTextRect(CRect rectCell, CDC* pDC)			//Calculate the coordinates to be used for drawing text in the cell.
											{ CRect rectDrawRect = CalcDrawRect(rectCell, pDC);
											   CRect rectTextRect(rectDrawRect.left +  2, 
													   		      rectDrawRect.top +  2,
													   		      rectDrawRect.right - 3,
													   		      rectDrawRect.bottom - 1);
											    return rectTextRect;
											 }
	virtual CRect CalcPrintTextRect(CRect rectCell, CDC* pDC)			//Calculate the coordinates to be used for drawing text in the cell.
											{ CRect rectDrawRect = CalcDrawRect(rectCell, pDC);
											  float fXMultiplier =  (float) ((float) pDC->GetDeviceCaps(LOGPIXELSX) / (float) m_LOGPIXELSX);   
											  float fYMultiplier =  (float) ((float) pDC->GetDeviceCaps(LOGPIXELSY) / (float) m_LOGPIXELSY);   
											  CRect rectTextRect(rectDrawRect.left +  (int) (2 * fXMultiplier), 
													   		      rectDrawRect.top +  (int) (2 * fYMultiplier),
													   		      rectDrawRect.right - (int) (3 * fXMultiplier),
													   		      rectDrawRect.bottom - (int) (1 * fYMultiplier));
											    return rectTextRect;
											 }
	virtual void OnHighlightCurrentCell(CDC* pDC, CRect* pRect, BOOL bSelected = TRUE);	//Overide this to customize the selection highlighting
	virtual void OnHighlightSelection(CDC* pDC, CRect* pRect, BOOL bSelected = TRUE);	//Overide this to customize the current cell highlighting.
	virtual BOOL PrepareGridCell(CDC* pDC, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CRect DrawRect);	//Called to draw the cell background and borders.
	virtual BOOL DrawGridCell(CDC* pDC, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CRect DrawRect, CRect TextRect);	//Called to draw the cell contents.
	virtual void GridOnDraw(CDC* pDC);						// Called to draw the grid into the Device Context specified by pDC.
	virtual void UpdateRowHeight(int nRowNdx, float nRowHeight, int nSheet);  //Updates the row height for autosizing without drawing.
	virtual void UpdateColWidth(int nColNdx, float nColWidth, int nSheet);     //Updates the column width for autosizing without drawing.
	virtual BOOL CalcCellSizes(CDC* pDC);                             //Implements auto sizing during OnDraw.
	virtual BOOL CalcControlSize()		                         // Implements auto control sizing (OLE Control only).
					{
						return FALSE;
					}
	virtual void UpdateCellSizes(int nSaveVPageSize, int nSaveHPageSize);
	virtual void OnDrawOutOfBounds(CRect& Rect, CDC* pDC);	// Called from OnDraw to draw portion of the view outside the grid.
	virtual void GridOnDrawPrint(CDC* pDC);					// Called to draw the grid into the Device Context specified by pDC for printing.
	virtual BOOL IsPageBreakColumn(int nColNdx)				// Is the column a page break column?
		{return FALSE;}  
	virtual BOOL IsPageBreakRow(int nRowNdx)				// Is the row a page break row?
		{return FALSE;} 
//}}GW_MEMBERS	

//GW_MEMBERS{{CGWGrid, "Grid Data Access Overideables")
	virtual void OnGetFixedCellText(int nRowNdx, int nColNdx, CString& csCellText); //This function can be called by GCOs and various grid operations to get the text.
	virtual void OnGetCellText(int nRowNdx, int nColNdx, CString& csCellText);		//This function can be called by GCOs and various grid operations to get the text.
	virtual void OnGetCellLong(int nRowNdx, int nColNdx, long& nCellLong);			//This function can be called by GCOs and various grid operations to get the numeric data.
	virtual void OnGetCellObject(int nRowNdx, int nColNdx, CObject*& pObject);		//This function can be called by GCOs and various grid operations to retrieve a previously associated CObject pointer.
	virtual void OnGetCellFloat(int nRowNdx, int nColNdx, double& nCellFloat);		//This function can be called by GCOs and various grid operations to get the numeric data.
	virtual void OnGetCellTime(int nRowNdx, int nColNdx, CGWDateTime& CellTime);	//This function can be called by GCOs and various grid operations to get the date/time data.
	virtual void OnGetDefaultCellText(int nRowNdx, int nColNdx, CString& csDefaultVal);		//This fucntion is called during the "AddRow" processing to obtain default values for each cell in the new row.
	virtual void OnSetCellText(int nRowNdx, int nColNdx, CString& csCellText);		//This function can be called by GCOs and various grid operations to store text data for a cell.
	virtual void OnSetCellLong(int nRowNdx, int nColNdx, long& nCellLong);			//This function can be called by GCOs and various grid operations to store numeric data for a cell.
	virtual void OnSetCellObject(int nRowNdx, int nColNdx, CObject*& pObject);		//This function can be called by GCOs and various grid operations to store a CObject pointer within a cell.
	virtual void OnSetCellFloat(int nRowNdx, int nColNdx, double& nCellFloat);		//This function can be called by GCOs and various grid operations to store numeric data for a cell.
	virtual void OnSetCellTime(int nRowNdx, int nColNdx, CGWDateTime& CellTime);	//This function can be called by GCOs and various grid operations to store date/time data for a cell.
	virtual void OnSetCellVariant(int nRowNdx, int nColNdx, VARIANT& vt, UINT vID);  //This function can be called by GCOs and various grid operations to make generic data requests of a cell.
	virtual void OnGetCellTipText(int nRowNdx, int nColNdx, CString& csText)		//This function can be called by the grid framework to request text to be used as a tooltip for this cell.
		{};
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Cell Functional Overides")
	virtual void OnGetCellVariant(int nRowNdx, int nColNdx, VARIANT& vt, UINT vID);   //Called to retrieve generic information about a cell.
	virtual BOOL OnGetCellValidString(int nRowNdx, int nColNdx, CString& csValidString, void*& pItemDataPtr, int nStringIndex);		//Called from GCOs to retrieve valid strings for drop down list type cells.
	virtual void OnGetCellContextMenu(int nRowNdx, int nColNdx, CString csContextMenuName, CMenu*& pContextMenu);					//Called to retrieve a context menu for a cell.
	virtual void OnGetCellLBStyle(int nRowNdx, int nColNdx, int& nNumStrings, int nTotalStrings, BOOL& bExactWidth, CRect rectCell); //Called to retrieve information for formating the listbox portion of a drop down list cell.
	virtual CBitmap* OnGetCellBitmap(int nRowNdx, int nColNdx, BOOL& bStretch, int& nJustify)										//Called to retrieve a CBitmap pointer for a cell.
		{return NULL;}
//}}GW_MEMBERS	
//GW_MEMBERS{{(CGWGrid,"Clipboard Notification Overideables")
	virtual void GridOnEditCut();			//Called in response to an ID_EDIT_CUT command message.
	virtual void GridOnEditPaste();			//Called in response to an ID_EDIT_PASTE command message.
	virtual void GridOnEditCopy();			//Called in response to an ID_EDIT_COPY command message.
	virtual void GridOnEditClear();			//Called in response to an ID_EDIT_CLEAR command message.
	virtual void GridOnEditDelete();		//Called in response to an ID_EDIT_DELETE command message.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGrid,"Drag and Drop Notification Overideables")
	virtual COleDataSource* CreateOleDataSource();					//Called when drag and drop is initiated to constructs an COleDataSource object.
	virtual void DestroyOleDataSource(COleDataSource* pDataSource);  ////Called when drag and drop is terminates to destroy the COleDataSource object.
	virtual DROPEFFECT GetValidDropEffects();						//Called during drag to allow grid to identify possible DRAGEFFECTs based on the position of the mouse.
	virtual BOOL IsAcceptableDataType(COleDataObject* pDataObject);	//Called during draging to allow the grid to determine if the COleDataObject contains an acceptable format.
	virtual void GetSizeOfDataObject(COleDataObject* pDataObject, int& nNumDragRows, int& nNumDragCols, CString& csClipBuffer);	//Called to allow the grid to identify the size in rows and columns of the COleDataObject.
	virtual DROPEFFECT CalculateDropEffect(DWORD dwKeyState, CPoint point); //Called to allow the grid to control current DROPEFFECT, given the status of the keyboard, the location of the mouse, and any drag styles controled by the grid.
	virtual BOOL OnDropMove(int RowNdx, int nColNdx, CPoint point, COleDataObject* pDataObject, CString& csClipBuffer); //Called to notify the grid that a COleDropTarget::OnDrop() has ocurred when the DROPEFFECT was DROPEFFECT_MOVE.
	virtual BOOL OnDropCopy(int nRowNdx, int nColNdx, CPoint point, COleDataObject* pDataObject, CString& csClipBuffer);	//Called to notify the grid that a COleDropTarget::OnDrop() has ocurred when the DROPEFFECT was DROPEFFECT_COPY.
	virtual void OnDropOverlay(int nStartRow, int nStartColumn, int numRows, int numCols, COleDataObject* pDataObject, CString& csClipBuffer);	//Called to notify the grid that a COleDropTarget::OnDrop() has ocurred when the DROPEFFECT was DROPEFFECT_COPY or DROPEFFECT_MOVE.
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point, BOOL* pbCancelDefaultAction);	//Called by the framework when the mouse is dragged over the target window.		
	virtual void OnDragLeave(CWnd* pWnd, BOOL* pbCancelDefaultAction);																		//Called by the framework when the mouse leaves the target window.		
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point, BOOL* pbCancelDefaultAction);		//Called by the framework when the mouse moves over the target window.		
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point, BOOL* pbCancelDefaultAction);			//Called by the framework when the user drops onto the target window.		
	virtual void OnDragComplete(COleDataSource* pDataSource, DROPEFFECT dropEffect);			//Called by the framework to notify the source of the completed operation.		
	virtual SCODE GiveFeedback(DROPEFFECT dropEffect, BOOL* pbCancelDefaultAction);				//Called by the framework so you can provide the visual feedback to the user.		
//}}GW_MEMBERS	


//Member access functions
public:

//GW_MEMBERS{{(CGWGrid,"Grid Member Access Functions")
	CGWContextMenu* GetContextMenu(int nSheet = CURRENT_SHEET);			//Retrieve the sheets default context menu.
	CGWContextMenu* GetTabMenu(int nSheet = CURRENT_SHEET);				//Retrieve the sheets defualt tab context menu.
	void EnableCellTips(BOOL bEnableCellTips)							//Turns cell tips on or off for the entire grid.
	{	
		m_bEnableCellTips = bEnableCellTips;
	}
	void GetSettingsRank(int& nCellSettingsRank, int &nRowSettingsRank, int& nColSettingsRank)	//Obtain the rank to be applied to row, column and cell settings.
	{
		nCellSettingsRank = m_nCellSettingsRank;
		nRowSettingsRank = m_nRowSettingsRank;
		nColSettingsRank = m_nColSettingsRank;
	}
	int GetRowColUnits(int nSheet = CURRENT_SHEET)						//Retrieve the sheet level Row/Column units property.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nRowColUnits : m_nRowColUnits;}
	int GetAddRow(int nSheet = CURRENT_SHEET)							//Get the value of the AddRow property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nAddRow : m_nAddRow;}
	BOOL GetAutoSizeColumns(int nSheet = CURRENT_SHEET)					//Get the value of the Auto Size Columns property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bAutoSizeColumns : m_bAutoSizeColumns;}
	int GetGridStyle(int nSheet = CURRENT_SHEET)						//Get the value of the Grid Style property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nGridStyle : m_nGridStyle;}
	COLORREF GetBackColor(int nSheet = CURRENT_SHEET)					//Get the value of the Back Color property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_BackgroundColor : m_BackgroundColor;}
	COLORREF GetOutOfBoundsColor(int nSheet = CURRENT_SHEET)			//Get the value of the Out Of Bounds Color property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_clrfOutOfBounds : m_clrfOutOfBounds;}
	int GetRangeDragStyle(int nSheet = CURRENT_SHEET)					//Get the value of the Range Drag Style property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nRangeDragStyle : m_nRangeDragStyle;}
	int GetRowDragStyle(int nSheet = CURRENT_SHEET)						//Get the value of the Row Drag Style property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nRowDragStyle : m_nRowDragStyle;}
	int GetColumnDragStyle(int nSheet = CURRENT_SHEET)					//Get the value of the Column Drag Style property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nColumnDragStyle : m_nColumnDragStyle;}
	int GetEditFlag(int nSheet = CURRENT_SHEET)							//Get the value of the Edit Flag property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nEditFlag : m_nEditFlag;}
	int GetTabControl(int nSheet = CURRENT_SHEET)						//Get the value of the Tab Control property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nTabControl : m_nTabControl;}
	BOOL GetWantDropNotify(int nSheet = CURRENT_SHEET)					//Get the value of the Want Drop Notify property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bWantDropNotify : m_bWantDropNotify;}
	BOOL GetHiliteNoFocus(int nSheet = CURRENT_SHEET)					//Get the value of the Hilite No Focus property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bHiliteNoFocus : m_bHiliteNoFocus;}
	BOOL GetVirtualDataMode(int nSheet = CURRENT_SHEET)					//Get the value of the Virtual Data Mode property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bVirtualDataMode : m_bVirtualDataMode;}
	BOOL GetClipHeadings(int nSheet = CURRENT_SHEET)					//Get the value of the Clip Headings property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bClipHeadings : m_bClipHeadings;}
	BOOL GetShowEditIndicators(int nSheet = CURRENT_SHEET)				//Get the value of the Show Edit Indicators property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bShowEditIndicators : m_bShowEditIndicators;}
	int GetStringCount(int nSheet = CURRENT_SHEET)						//Get the value of the String Count property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nStringCount : m_nStringCount;}
	void GetTextAlignment(int& nVertAlign, int& nHorzAlign, BOOL& bWordWrap, int nSheet = CURRENT_SHEET)	//Get the value of the Text Alignment property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 nVertAlign = (pGridSettings) ? pGridSettings->m_nVertAlign : m_nVertAlign;
		 nVertAlign = (pGridSettings) ? pGridSettings->m_nHorzAlign : m_nHorzAlign;
		 nVertAlign = (pGridSettings) ? pGridSettings->m_bWordWrap : m_bWordWrap;}
	CRect GetCellBorder(int nSheet = CURRENT_SHEET)						//Get the value of the Cell Border property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_rectBorder : m_rectBorder;}
	UINT GetCellFillPattern(int nSheet = CURRENT_SHEET)					//Get the value of the Cell Fill Pattern property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nPatternID : m_nPatternID;}
	COLORREF GetForecolor(int nSheet = CURRENT_SHEET)					//Get the value of the Forecolor property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_rgbForecolor : m_rgbForecolor;}
	BOOL GetBorder(int nSheet = CURRENT_SHEET)							//Get the value of the Border property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bBorder : m_bBorder;}
	int GetNumColumns(int nSheet = CURRENT_SHEET)						//Get the value of the Num Columns property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nMaxColumns : m_nMaxColumns;}
	BOOL GetColSelect(int nSheet = CURRENT_SHEET)						//Get the value of the Column Select property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bColSelect : m_bColSelect;}
	BOOL GetColResize(int nSheet = CURRENT_SHEET)						//Get the value of the Column Resize property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bResizeCols : m_bResizeCols;}
	float GetDefaultColumnWidth(int nSheet = CURRENT_SHEET)				//Get the value of the Default Column Width property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
			 if (pGridSettings)
			 {
				return (pGridSettings->m_nRowColUnits == PIXELS) ? pGridSettings->m_nColWidth : pGridSettings->m_nColWidthChars;
			 }
         return (m_nRowColUnits == PIXELS) ? m_nColWidth : m_nColWidthChars;
	    }
	UINT GetDisableNoScroll(int nSheet = CURRENT_SHEET)					//Get the value of the Disable No Scroll property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nDisableNoScroll : m_nDisableNoScroll;}
	BOOL GetDragAndDrop(int nSheet = CURRENT_SHEET)						//Get the value of the Drag And Drop property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
	return (pGridSettings) ? pGridSettings->m_bDragAndDrop : m_bDragAndDrop;}
	COLORREF GetFixedCellColor(int nSheet = CURRENT_SHEET)				//Get the value of the Fixed Cell Color property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_FixedCellColor : m_FixedCellColor;}
	int GetFixedColumns(int nSheet = CURRENT_SHEET)						//Get the value of the Fixed Columns property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nFixedColumns : m_nFixedColumns;}
	int GetFixedRows(int nSheet = CURRENT_SHEET)						//Get the value of the Fixed Rows property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nFixedRows : m_nFixedRows;}
	BOOL GetFocusRect(int nSheet = CURRENT_SHEET)						//Get the value of the Focus Rect property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bShowFocusRect : m_bShowFocusRect;}
	BOOL GetFontBold(int nSheet = CURRENT_SHEET)						//Get the value of the Font Bold property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_LogFont.lfWeight == FW_BOLD : m_LogFont.lfWeight == FW_BOLD;}
	_TCHAR*  GetFontFaceName(int nSheet = CURRENT_SHEET)				//Get the value of the Font Face Name property for this sheet.
 		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? (_TCHAR*) pGridSettings->m_LogFont.lfFaceName : (_TCHAR*) m_LogFont.lfFaceName;}
	BOOL GetFontItalic(int nSheet = CURRENT_SHEET)						//Get the value of the Font Italic property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_LogFont.lfItalic : m_LogFont.lfItalic;}
	int GetFontPointSize(int nSheet = CURRENT_SHEET)					//Get the value of the Font Point Size property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nPointSize : m_nPointSize;}
	BOOL GetFontTransparent(int nSheet = CURRENT_SHEET)					//Get the value of the Font Transparent property for this sheet.
		{return FALSE;}
	BOOL GetFontStrikeThru(int nSheet = CURRENT_SHEET)					//Get the value of the Font Strike Thru property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_LogFont.lfStrikeOut : m_LogFont.lfStrikeOut;}
	BOOL GetFontUnderline(int nSheet = CURRENT_SHEET)					//Get the value of the Font Underline property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_LogFont.lfUnderline : m_LogFont.lfUnderline;}
	COLORREF GetGridLineColor(int nSheet = CURRENT_SHEET)				//Get the value of the Grid Line Color property for this sheet.
 		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_GridLineColor : m_GridLineColor;}
	BOOL GetGridLines(int nSheet = CURRENT_SHEET)						//Get the value of the Grid Lines property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bGridLines : m_bGridLines;}
	BOOL GetHighlightSelection(int nSheet = CURRENT_SHEET)				//Get the value of the Highlight Selection property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bInvertSelection : m_bInvertSelection;}
	int GetPenWidth(int nSheet = CURRENT_SHEET)							//Get the value of the Pen Width property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_PenWidth.x : m_PenWidth.x;}
	const _TCHAR* GetPrintCaption(int nSheet = CURRENT_SHEET)			//Get the value of the Print Caption property for this sheet.	
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (const _TCHAR*) ((pGridSettings) ? pGridSettings->m_csPrintCaption.GetBuffer(pGridSettings->m_csPrintCaption.GetLength()) : 
								   m_csPrintCaption.GetBuffer(m_csPrintCaption.GetLength()));}
	BOOL GetRecordsetEnable(int nSheet = CURRENT_SHEET)					//Get the value of the Recordset Enable property for this sheet.
 		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bRecordsetEnable : m_bRecordsetEnable;}
	float GetDefaultRowHeight(int nSheet = CURRENT_SHEET)				//Get the value of the Default Row Height property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
			 if (pGridSettings && nSheet != m_nCurrentSheet && nSheet != CURRENT_SHEET)
			 {
				return (pGridSettings->m_nRowColUnits == PIXELS) ? pGridSettings->m_nRowHeight : pGridSettings->m_nRowHeightPoints;
			 }
			 return (m_nRowColUnits == PIXELS) ? m_nRowHeight : m_nRowHeightPoints;
		}
	int GetNumRows(int nSheet = CURRENT_SHEET)							//Get the value of the Num Rows property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nMaxRows : m_nMaxRows;}
	BOOL GetRowSelect(int nSheet = CURRENT_SHEET)						//Get the value of the Row Select property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bRowSelect : m_bRowSelect;}
	BOOL GetRowResize(int nSheet = CURRENT_SHEET)						//Get the value of the Row Resize property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bResizeRows : m_bResizeRows;}
	UINT GetScrollBars(int nSheet = CURRENT_SHEET)						//Get the value of the Scroll Bars property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 if (pGridSettings)
		 {
			 if (pGridSettings->m_hBar && pGridSettings->m_vBar) 	return SB_BOTH;
			 else if (pGridSettings->m_hBar) 						return SB_HORZ;
			 else if (pGridSettings->m_vBar) 						return SB_VERT;
			 return SB_NONE;
		 }
		 if (m_hBar && m_vBar) 	return SB_BOTH;
		 else if (m_hBar) 		return SB_HORZ;
		 else if (m_vBar) 		return SB_VERT;
		 return SB_NONE;}
	BOOL GetShowCurrentCell(int nSheet = CURRENT_SHEET)					//Get the value of the Show Current Cell property for this sheet.
 		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_bShowCurrentCell : m_bShowCurrentCell;}
	int GetSizingRegionWidth(int nSheet = CURRENT_SHEET)				//Get the value of the Sizing Region Width property for this sheet.
 		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nSizingRegionWidth : m_nSizingRegionWidth;}
	BOOL GetSynchronizePanes(int nSheet = CURRENT_SHEET)				//Get the value of the Synchronize Panes property for this sheet.
 		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		return (pGridSettings) ? pGridSettings->m_bSynchronizePanes : m_bSynchronizePanes;}
	COLORREF GetTextColor(int nSheet = CURRENT_SHEET)					//Get the value of the Text Color property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		return (pGridSettings) ? pGridSettings->m_TextColor : m_TextColor;}
	BOOL GetThumbScroll(int nSheet = CURRENT_SHEET)						//Get the value of the Thumb Scroll property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		return (pGridSettings) ? pGridSettings->m_bThumbScroll : m_bThumbScroll;}
	BOOL GetSizeColumnsTopToBottom(int nSheet = CURRENT_SHEET)			//Get the value of the Size Columns Top To Bottom property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		return (pGridSettings) ? pGridSettings->m_bSizeColumnsTopToBottom : m_bSizeColumnsTopToBottom;}
	BOOL GetSizeRowsLeftToRight(int nSheet = CURRENT_SHEET)				//Get the value of the Size Rows Left To Right property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		return (pGridSettings) ? pGridSettings->m_bSizeRowsLeftToRight : m_bSizeRowsLeftToRight;}
	BOOL GetShowTreeLines(int nSheet = CURRENT_SHEET)					//Get the value of the Show Tree Lines property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		return (pGridSettings) ? pGridSettings->m_bShowTreeLines : m_bShowTreeLines;}
    BOOL GetGridError()													//Retrieve the error status of the grid.
		{return m_bGridError;} 
    CPoint GetCurrentCell()												//Retrieve a CPoint which contains the coordinates of the current cell.
		{return m_CurrentCell; }
	int GetVScrollPos(int nSheet = CURRENT_SHEET)						//Get value of the vertical scroll position. This will identify the row index of the first non-fixed row.
		{if (nSheet != CURRENT_SHEET && nSheet != m_nCurrentSheet)
			{
				 CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
				 return (pGridSettings) ? pGridSettings->m_nVScrollPos : -1;
			}
		 return m_nVScrollPos;}
    int GetHScrollPos(int nSheet = CURRENT_SHEET)						//Get value of the horizontal scroll position. This will identify the column index of the first non-fixed Column.
		{if (nSheet != CURRENT_SHEET && nSheet != m_nCurrentSheet)
			{
				 CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
				 return (pGridSettings) ? pGridSettings->m_nHScrollPos : -1;
			}
		 return m_nHScrollPos;}
	int GetLockedColumns(int nSheet = CURRENT_SHEET)					//Get the value of the Locked Columns property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nLockedColumns : m_nLockedColumns;}
    int GetLockedRows(int nSheet = CURRENT_SHEET)						//Get the value of the Locked Rows property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nLockedRows : m_nLockedRows;}
	int GetDockedColumns(int nSheet = CURRENT_SHEET)					//Get the value of the Docked Columns property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nDockedColumns : m_nDockedColumns;}
    int GetDockedRows(int nSheet = CURRENT_SHEET)						//Get the value of the Docked Rows property for this sheet.
		{CGWGridSettings* pGridSettings = OnGetGridSettings(nSheet);
		 return (pGridSettings) ? pGridSettings->m_nDockedRows : m_nDockedRows;}
	void SetContextMenu(CGWContextMenu* pContextMenu, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Set the value of the Default Context Menu property for this sheet.
	void SetTabMenu(CGWContextMenu* pContextMenu, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Default Tab Context Menu property for this sheet.
	void SetRowColUnits(int nUnits, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Row Col Units property for this sheet.
	void SetSettingsFile(CString csInitFile);																//Set the value of the Settings File property for this sheet. This can be a file name or a string resource id which identifies a property stream created by the GridWiz Workshop.
	void SetSettingsFilePath(CString csInitFile);															//Set the value of the Settings File Path property for this sheet.
	void SetAddRow(int nAddRow, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);							//Set the value of the AddRow property for this sheet.
	void SetAutoSizeColumns(BOOL bAutoSizeColumns, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Auto Size Columns property for this sheet. This property makes all the columns the same size initially.
	void SetGridStyle(UINT nGridStyle, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Grid Style property for this sheet.
	void SetBackColor(COLORREF clrf, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Back Color property for this sheet.
	void SetOutOfBoundsColor(COLORREF clrf, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Out Of Bounds Color property for this sheet.
	void SetRangeDragStyle(int nStyle, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Range Drag Style property for this sheet.
	void SetRowDragStyle(int nStyle, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Row Drag Style property for this sheet.
	void SetColumnDragStyle(int nStyle, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Column Drag Style property for this sheet.
	void SetEditFlag(int nEditFlag, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Edit Flag property for this sheet.
	void SetControlStyles(DWORD dwPrimaryControlStyle, DWORD dwSecondaryControlStyle, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Set the Control Styles property for this sheet.
	void SetExtendedCellStyle(DWORD dwExtendedCellStyle, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Set the Control Styles property for this sheet.
	void SetTabControl(int nTabControl, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Tab Control property for this sheet.
	void SetWantDropNotify(BOOL bWantDropNotify, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Want Drop Notify property for this sheet.
	void SetHiliteNoFocus(BOOL bHiliteNoFocus, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Hilite No Focus property for this sheet.
	void SetVirtualDataMode(BOOL bVirtualDataMode, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Virtual Data Mode property for this sheet.
	void SetClipHeadings(BOOL bClipHeadings, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Clip Headings property for this sheet.
	void SetShowEditIndicators(BOOL bShowEditIndicators, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Set the value of the Show Edit Indicators property for this sheet.
	void SetStringCount(int nStringCount, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the String Count property for this sheet.
	void SetTextAlignment(int nVertAlign, int nHorzAlign, BOOL bWordWrap, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Set the value of the Text Alignment property for this sheet.
	void SetCellBorder(CRect rectBorder, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Cell Border property for this sheet.
	void SetCellFillPattern(UINT nPatternID, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Cell Fill Pattern property for this sheet.
	void SetForecolor(COLORREF clrf, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Forecolor property for this sheet.
	void SetBorder(BOOL bBorder, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);							//Set the value of the Border property for this sheet.
	void SetNumColumns(UINT nNumCols, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Num Columns property for this sheet.
	BOOL SetColSelect(BOOL bColSelect, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Col Select property for this sheet.
	BOOL SetColResize(BOOL bColResize, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Col Resize property for this sheet.
	void SetDefaultColumnWidth(float nColWidth, BOOL bRefresh = TRUE, int nUnits = DEFAULT_UNITS, int nSheet = CURRENT_SHEET);	//Set the value of the Default Column Width property for this sheet.
    void SetDisableNoScroll(UINT sbCode = SB_BOTH, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Disable No Scroll property for this sheet.
	void SetDragAndDrop(BOOL bDragAndDrop, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Drag And Drop property for this sheet.
	void SetFixedCellColor(COLORREF clrf, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Fixed Cell Color property for this sheet.
	void SetFocusRect(BOOL bFocusRect, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Focus Rect property for this sheet.
	void SetFontBold(BOOL bFontBold, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Font Bold property for this sheet.
	void SetFontFaceName(_TCHAR* lpszFaceName, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Font Face Name property for this sheet.
	void SetFontItalic(BOOL bFontItalic, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Font Italic property for this sheet.
	void SetFontPointSize(int nFontPointSize, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Font Point Size property for this sheet.
	void SetFontStrikeThru(BOOL bFontStrikeThru, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Font Strike Thru property for this sheet.
	void SetFontTransparent(BOOL bFontTransparent, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Font Transparent property for this sheet.
	void SetFontUnderline(BOOL bFontUnderline, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Font Underline property for this sheet.
	void SetGridLineColor(COLORREF clrf, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Grid Line Color property for this sheet.
	void SetGridLines(BOOL bGridLines, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Grid Lines property for this sheet.
	void SetHighlightSelection(BOOL bHighlightSelection, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Set the value of the Highlight Selection property for this sheet.
	void SetPenWidth(int nPenWidth, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Pen Width property for this sheet.
	void SetPrintCaption(const _TCHAR* lpszCaption, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Print Caption property for this sheet.
	void SetRecordsetEnable(BOOL bRecordset, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Recordset Enable property for this sheet.
	void SetDefaultRowHeight(float nRowHeight, BOOL bRefresh = TRUE, int nUnits = DEFAULT_UNITS, int nSheet = CURRENT_SHEET);	//Set the value of the Default Row Height property for this sheet.
	void SetNumRows(UINT nNumRows, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Num Rows property for this sheet.
	BOOL SetRowSelect(BOOL bRowSelect, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Row Select property for this sheet.
	BOOL SetRowResize(BOOL bRowResize, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Row Resize property for this sheet.
	void SetScrollBars(UINT sbCode, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Scroll Bars property for this sheet.
	void SetShowCurrentCell(BOOL bShowCurrentCell, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Show Current Cell property for this sheet.
	void SetSizingRegionWidth(int nSizingRegion, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Sizing Region Width property for this sheet.
	void SetSynchronizePanes(BOOL bSynchronizePanes, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Synchronize Panes property for this sheet.
	void SetTextColor(COLORREF clrf, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);						//Set the value of the Text Color property for this sheet.
	void SetThumbScroll(BOOL bThumbScroll, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Thumb Scroll property for this sheet.
	void SetSizeColumnsTopToBottom(BOOL bSizeColumnsTopToBottom, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Set the value of the Size Columns Top To Bottom property for this sheet.
	void SetSizeRowsLeftToRight(BOOL bSizeRowsLeftToRight, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);		//Set the value of the Size Rows Left To Right property for this sheet.
	void SetShowTreeLines(BOOL bShowTreeLines, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Show Tree Lines property for this sheet.
	void SetGridError(BOOL bGridError, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Grid Error property for this sheet.
    void SetCaptureCell(CGWGridCellObject far* pCellCapture, BOOL bRefresh = TRUE);							//Set the value of the Capture Cell property for this sheet.
	void SetVScrollPos(int nVScrollPos, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the vertical scroll position for this sheet.
	void SetHScrollPos(int nHScrollPos, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the horizontal scroll position for this sheet.
	void SetFixedRows(int nFixedRows, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Fixed Rows property for this sheet.
	void SetFixedColumns(int nFixedColumns, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);				//Set the value of the Fixed Columns property for this sheet.
	void SetDockedRows(int nDockedRows, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);					//Set the value of the Docked Rows property for this sheet.
	void SetDockedColumns(int nDockedColumns, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);			//Set the value of the Docked Columns property for this sheet.
	BOOL SetDefaultCellType(CString csClassName, int nSheet = CURRENT_SHEET);								//Set the value of the Default Cell Type property for this sheet.
	CString GetDefaultCellType(int nSheet = CURRENT_SHEET);													//Get the value of the Default Cell Type property for this sheet.
	void SetAutoSizeRowHeight(BOOL bAutoSizeRowHeight, int nSheet = CURRENT_SHEET);							//Automatically size height of row to fit wrapped text  for the entire sheet
	void SetAutoSizeColumnWidth(BOOL bAutoSizeColumnWidth, int nSheet = CURRENT_SHEET);						//Automatically size width of column to fit single line text for the entire sheet.
	void SetAutoSizeVisibleOnly(BOOL bAutoSizeVisibleOnly);													//Cause autosizing to happen only for visible rows instead of doing the whole sheet at once.
	void SetAutoSizeControlHeight(BOOL bAutoSizeControlHeight);													//Automatically size height of control to fit all rows.
	void SetAutoSizeControlWidth(BOOL bAutoSizeControlWidth);												//Automatically size width of control to fit all columns.
//}}GW_MEMBERS	


	//Cell and Range oriented functions. In order for these to work, you must
	//maintain a collection	of CCellSettings objects. The implementation of
	//CGWDataSource will return a CCellSettings object based on a cell or 
	//range of cell. The CCellDataMap has built in support and can also 
	//be serialized. All property set and get methods work on the current sheet. 
	//To set a property on a particular sheet, you must make it the current sheet.
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

//inline properties sets
//GW_MEMBERS{{(CGWGrid,"Grid inline Property sets")
	inline void GW_ROWCOLUNITS(int nUnits)                      //Sets the Row/Column units property in the Grid Global Settings at Initialization time.
			{SetRowColUnits(nUnits, FALSE);}
	inline void GW_INITIALIZATIONFILE(CString csInitFile)       //Sets the initialization file property in the Grid Global Settings at Initialization time.
			{SetSettingsFile(csInitFile);}
	inline void GW_ADDROW(int nAddRow) 							//Sets the AddRow property in the Grid Global Settings at Initialization time.
			{SetAddRow(nAddRow, FALSE);}
	inline void GW_AUTOSIZECOLUMNS(BOOL bAutoSizeColumns) 		//Sets the autosize columns property in the Grid Global Settings at Initialization time.
			{SetAutoSizeColumns(bAutoSizeColumns, FALSE);}
	inline void GW_GRIDSTYLE(int nGridStyle) 					//Sets the grid style property in the Grid Global Settings at Initialization time.
			{SetGridStyle(nGridStyle, FALSE);}
	inline void GW_BACKCOLOR(COLORREF clrf) 					//Sets the Back color property in the Grid Global Settings at Initialization time.
			{SetBackColor(clrf, FALSE);}
	inline void GW_OUTOFBOUNDSCOLOR(COLORREF clrf)				//Sets the out of bounds color property in the Grid Global Settings at Initialization time.
			{SetOutOfBoundsColor(clrf, FALSE);}
	inline void GW_RANGEDRAGSTYLE(int nStyle)					//Sets the range drag style property in the Grid Global Settings at Initialization time.
			{SetRangeDragStyle(nStyle, FALSE);}
	inline void GW_ROWDRAGSTYLE(int nStyle)						//Sets the row drag style property in the Grid Global Settings at Initialization time.
			{SetRowDragStyle(nStyle, FALSE);}
	inline void GW_COLUMNDRAGSTYLE(int nStyle)					//Sets the column drag style property in the Grid Global Settings at Initialization time.
			{SetColumnDragStyle(nStyle, FALSE);}
	inline void GW_EDITFLAG(int nEditFlag)						//Sets the edit flag property in the Grid Global Settings at Initialization time.
			{SetEditFlag(nEditFlag, FALSE);}
	inline void GW_TABCONTROL(int nTabControl)					//Sets the tab control property in the Grid Global Settings at Initialization time.
			{SetTabControl(nTabControl, FALSE);}
	inline void GW_WANTDROPNOTIFY(BOOL bWantDropNotify)			//Sets the want drop notify property in the Grid Global Settings at Initialization time.
			{SetWantDropNotify(bWantDropNotify, FALSE);}
	inline void GW_HILITENOFOCUS(BOOL bHiliteNoFocus)			//Sets the hilite no focus property in the Grid Global Settings at Initialization time.
			{SetHiliteNoFocus(bHiliteNoFocus, FALSE);}
	inline void GW_VIRTUALDATAMODE(BOOL bVirtualDataMode)		//Sets the virtual data mode property in the Grid Global Settings at Initialization time.
			{SetVirtualDataMode(bVirtualDataMode, FALSE);}
	inline void GW_CLIPHEADINGS(BOOL bClipHeadings)				//Sets the clip headings property in the Grid Global Settings at Initialization time.
			{SetClipHeadings(bClipHeadings, FALSE);}
	inline void GW_SHOWEDITINDICATORS(BOOL bShowEditIndicators)	//Sets the show edit indicators property in the Grid Global Settings at Initialization time.
			{SetShowEditIndicators(bShowEditIndicators, FALSE);}
	inline void GW_STRINGCOUNT(int nStringCount)				//Sets the string count property in the Grid Global Settings at Initialization time.
			{SetStringCount(nStringCount, FALSE);}
	inline void GW_CELLBORDER(CRect rectBorder)					//Sets the cell border property in the Grid Global Settings at Initialization time.
			{SetCellBorder(rectBorder, FALSE);}
	inline void GW_CELLFILLPATTERN(UINT nPatternID)				//Sets the cell fill pattern property in the Grid Global Settings at Initialization time.
			{SetCellFillPattern(nPatternID, FALSE);}
	inline void GW_FORECOLOR(COLORREF clrf)						//Sets the forecolor property in the Grid Global Settings at Initialization time.
			{SetForecolor(clrf, FALSE);}
	inline void GW_BORDER(BOOL bBorder)  						//Sets the border property in the Grid Global Settings at Initialization time.
			{SetBorder(bBorder, FALSE);}
	inline void GW_COLS(int nNumCols)  							//Sets the num columns property in the Grid Global Settings at Initialization time.
			{SetNumColumns(nNumCols, FALSE);}
	inline void GW_COLSELECT(BOOL bColSelect)  					//Sets the column select property in the Grid Global Settings at Initialization time.
			{SetColSelect(bColSelect, FALSE);}
	inline void GW_COLSIZE(BOOL bColResize)                     //Sets the column resize property in the Grid Global Settings at Initialization time.
			{SetColResize(bColResize, FALSE);}
	inline void GW_COLUMNWIDTH(float nColWidth)                 //Sets the column width property in the Grid Global Settings at Initialization time.
			{SetDefaultColumnWidth(nColWidth, FALSE);}
	inline void GW_DISABLENOSCROLL(UINT sbCode)             	//Sets the disable no scroll property in the Grid Global Settings at Initialization time.
			{SetDisableNoScroll(sbCode, FALSE);}
	inline void GW_DRAGANDDROP(BOOL bDragAndDrop)       		//Sets the drag and drop property in the Grid Global Settings at Initialization time.
			{SetDragAndDrop(bDragAndDrop, FALSE);}
	inline void GW_FIXEDCELLCOLOR(COLORREF clrf)             	//Sets the fixed cell color property in the Grid Global Settings at Initialization time.
			{SetFixedCellColor(clrf, FALSE);}
	inline void GW_FOCUSRECT(BOOL bFocusRect)                 	//Sets the focus rect property in the Grid Global Settings at Initialization time.
			{SetFocusRect(bFocusRect, FALSE);}
	inline void GW_FONTBOLD(BOOL bFontBold)                     //Sets the font bold property in the Grid Global Settings at Initialization time.
			{SetFontBold(bFontBold, FALSE);}
	inline void GW_FONTFACENAME(_TCHAR* lpszFaceName)      		//Sets the font face name property in the Grid Global Settings at Initialization time.
			{SetFontFaceName(lpszFaceName, FALSE);}
	inline void GW_FONTITALIC(BOOL bFontItalic)                 //Sets the font italic property in the Grid Global Settings at Initialization time.
			{SetFontItalic(bFontItalic, FALSE);}
	inline void GW_FONTPOINTSIZE(int nFontPointSize)          	//Sets the font pointsize property in the Grid Global Settings at Initialization time.
			{SetFontPointSize(nFontPointSize, FALSE);}
	inline void GW_GRIDLINECOLOR(COLORREF clrf)               	//Sets the grid line color property in the Grid Global Settings at Initialization time.
			{SetGridLineColor(clrf, FALSE);}
	inline void GW_GRIDLINES(BOOL bGridLines)                  	//Sets the grid lines property in the Grid Global Settings at Initialization time.
			{SetGridLines(bGridLines, FALSE);}
	inline void GW_HIGHLIGHTSELECTION(BOOL bHighlightSelection)     		//Sets the highlight selection property in the Grid Global Settings at Initialization time.
			{SetHighlightSelection(bHighlightSelection, FALSE);}
	inline void GW_PENWIDTH(int nPenWidth)                     	//Sets the pen width property in the Grid Global Settings at Initialization time.
			{SetPenWidth(nPenWidth, FALSE);}
	inline void GW_PRINTCAPTION(const _TCHAR* lpszCaption)        //Sets the print caption property in the Grid Global Settings at Initialization time.
			{SetPrintCaption(lpszCaption, FALSE);}
	inline void GW_RECORDSETENABLE(BOOL bRecordset)    			//Sets the recordset enable property in the Grid Global Settings at Initialization time.
			{SetRecordsetEnable(bRecordset, FALSE);}
	inline void GW_ROWHEIGHT(float nRowHeight)                   	//Sets the row height property in the Grid Global Settings at Initialization time.
			{SetDefaultRowHeight(nRowHeight, FALSE);}
	inline void GW_ROWS(int nNumRows)                          	//Sets the num rows property in the Grid Global Settings at Initialization time.
			{SetNumRows(nNumRows, FALSE);}
	inline void GW_ROWSELECT(BOOL bRowSelect)	              	//Sets the row select property in the Grid Global Settings at Initialization time.
			{SetRowSelect(bRowSelect, FALSE);}
	inline void GW_ROWSIZE(BOOL bRowResize)                   	//Sets the row resize property in the Grid Global Settings at Initialization time.
			{SetRowResize(bRowResize, FALSE);}
	inline void GW_SCROLLBARS(UINT sbCode)                     	//Sets the scrollbars property in the Grid Global Settings at Initialization time.
			{SetScrollBars(sbCode, FALSE);}
	inline void GW_SHOWCURRENTCELL(BOOL bShowCurrentCell)      	//Sets the show current cell property in the Grid Global Settings at Initialization time.
			{SetShowCurrentCell(bShowCurrentCell, FALSE);}
	inline void GW_SIZINGREGIONWIDTH(int nSizingRegion)        	//Sets the sizing region width property in the Grid Global Settings at Initialization time.
			{SetSizingRegionWidth(nSizingRegion, FALSE);}
	inline void GW_SYNCHRONIZEPANES(BOOL bSynchronizePanes)    	//Sets the synchronize panes property in the Grid Global Settings at Initialization time.
			{SetSynchronizePanes(bSynchronizePanes, FALSE);}
	inline void GW_TEXTCOLOR(COLORREF clrf)                    	//Sets the text color property in the Grid Global Settings at Initialization time.
			{SetTextColor(clrf, FALSE);}
	inline void GW_THUMBSCROLL(BOOL bThumbScroll)              	//Sets the thumbscroll property in the Grid Global Settings at Initialization time.
			{SetThumbScroll(bThumbScroll, FALSE);}
//}}GW_MEMBERS	
};

/////////////////////////////////////////////////////////////////////////////


//*********************************************************************************************************************
// class CGWGridDC : public CClientDC
//
// This class will build a CClientDC device context and customize it 
// to the current font and drawing tools. Use this class to get Device 
// Contexts that will be passed into member functions of CGWGrid.
// The Destructor cleans up after it so just allocate these on the 
// stack and let them go out of scope.
//
class GW_EXT_CLASS CGWGridDC : public CClientDC
{                           
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWGridDC,"Construction")
	CGWGridDC(CGWGrid* pGV);
	virtual ~CGWGridDC();
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridDC,"Data Members")
	CGWGrid* m_pGV;			//Pointer back to the grid which created the dc.
//}}GW_MEMBERS	
	static int dcCount;  //for diagnostics
	int dcNum;         //tracking DC's and stuff
};

//#ifndef _DEBUG
#ifdef _EVAL
class CEvalDlg : public CDialog
{
// Construction
public:
	CEvalDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEvalDlg)
	enum { IDD = IDD_EVAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEvalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEvalDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
//#endif


#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif //__GRID_H__
