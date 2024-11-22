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
//settings.h     

#ifndef __SETTINGS_H__
#define __SETTINGS_H__ 

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


#define		CELL_PROTECTED				0x0001
#define		CELL_FONT					0x0002
#define		CELL_COLOR					0x0004
#define		CELL_TEXT_COLOR				0x0008
#define		CELL_BORDER					0x0010
#define		CELL_TEXT_FORMAT			0x0020
#define		CELL_PATTERN				0x0040
#define		CELL_GCO_NAME				0x0080 
#define		CELL_AUTOMATIC_BACKCOLOR	0x0100
#define		CELL_AUTOMATIC_TEXTCOLOR	0x0200
#define		CELL_AUTOMATIC_FONT			0x0400
#define		CELL_BORDER_COLOR			0x0800		
#define		CELL_TEXT_ALIGN				0x1000		
#define		CELL_FORMAT					0x2000		
#define		CELL_VALID_STRINGS			0x4000		
#define		CELL_EDIT_FLAG				0x8000 
#define		CELL_FONT_BOLD				0x00010000
#define		CELL_FONT_NAME				0x00020000
#define		CELL_FONT_ITALIC			0x00040000
#define		CELL_FONT_SIZE				0x00080000
#define		CELL_FONT_STRIKETHRU		0x00100000
#define		CELL_FONT_UNDERLINE			0x00200000
#define		CELL_INPUT_MASK				0x00400000
#define		CELL_CONTEXT_MENU			0x00800000
#define		CELL_MINIMUM_VALUE			0x01000000
#define		CELL_MAXIMUM_VALUE			0x02000000
#define		CELL_MAXIMUM_LENGTH			0x04000000
#define		CELL_BITMAP					0x08000000
#define		CELL_BITMAP_STYLE			0x10000000
#define		CELL_OCX_CLASS				0x20000000
#define		CELL_EXTRA_DATA				0x40000000
#define		CELL_CONTROL_STYLE			0x80000000

#define		CELL_EX_AUTOSIZE_ROW_HEIGHT		0x00000001
#define		CELL_EX_AUTOSIZE_COLUMN_WIDTH	0x00000002
#define		CELL_EX_EXTENDED_CELL_SETTINGS	0x00000004







class CGWValidStrings;
class CGWContextMenu;
class GW_EXT_CLASS CGWCellSettings : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
protected: // create from serialization only
	DECLARE_SERIAL(CGWCellSettings)
public:

//GW_MEMBERS{{(CGWCellSettings,"Construction")
	CGWCellSettings();									//Default Constructor.
	CGWCellSettings(CRuntimeClass* pRuntimeClass);		//Construct a CellSettings object based on the design time values of a particular GCO.
	CGWCellSettings(CGWCellSettings* pCellSettings);	//Construct a CellSettings object based on another CellSettings Object.
	virtual ~CGWCellSettings()							//Default Destructor.
		{};
	void operator=(CGWCellSettings& pSettings);			//Copies one CGWCellSettings object to another.
//}}GW_MEMBERS
	
	
//GW_MEMBERS{{(CGWCellSettings,"Data Member Access")
	inline void ResetSettings()							//Reset the bit fields.
		{
			m_bitFieldSettings = 0;
			m_bitExFieldSettings = 0;
		}
	inline void SetSettings()							//Set all bits in bit fields on.
		{
			m_bitFieldSettings = 0xFFFFFFFF;
			m_bitExFieldSettings = 0xFFFFFFFF;
		}
	inline void SetEditFlag(int nEditFlag)									//Set the edit flag member and turn on its bit in the bit field.
		{
			m_nEditFlag = nEditFlag; 
			m_bitFieldSettings |= CELL_EDIT_FLAG;
		}
	inline void ResetEditFlag()												//Reset the edit flag member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_EDIT_FLAG;
		}
	inline void SetAutoSizeRowHeight(BOOL bAutoSizeRowHeight)				//Set the AutoSizeRowHeight member and turn on its bit in the bit field.
		{
			m_bAutoSizeRowHeight = bAutoSizeRowHeight; 
			m_bitExFieldSettings |= CELL_EX_AUTOSIZE_ROW_HEIGHT;
		}
	inline void ResetAutoSizeRowHeight()									//Reset the AutoSizeRowHeight member's bit in the bit field.
		{
			m_bitExFieldSettings &= ~CELL_EX_AUTOSIZE_ROW_HEIGHT;
		}
	inline void SetAutoSizeColumnWidth(BOOL bAutoSizeColumnWidth)			//Set the AutoSizeColumnWidth member and turn on its bit in the bit field.
		{
			m_bAutoSizeColumnWidth = bAutoSizeColumnWidth; 
			m_bitExFieldSettings |= CELL_EX_AUTOSIZE_COLUMN_WIDTH;
		}
	inline void ResetAutoSizeColumnWidth()									//Reset the AutoSizeColumnWidth member's bit in the bit field.
		{
			m_bitExFieldSettings &= ~CELL_EX_AUTOSIZE_COLUMN_WIDTH;
		}
	inline void SetControlStyles(DWORD dwPrimaryControlStyle, DWORD dwSecondaryControlStyle)	//Set the ControlStyles member and turn on its bit in the bit field.
		{
			m_dwPrimaryControlStyle = dwPrimaryControlStyle; 
			m_dwSecondaryControlStyle = dwSecondaryControlStyle; 
			m_bitFieldSettings |= CELL_CONTROL_STYLE;
		}
	inline void ResetControlStyles()										//Reset the ControlStyles member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_CONTROL_STYLE;
		}
	inline void SetExtendedCellStyle(DWORD dwExtendedCellStyle)			//Set the Extended Cell Styles member and turn on its bit in the bit field.
		{
			m_dwExtendedCellStyle = dwExtendedCellStyle; 
			m_bitExFieldSettings |= CELL_EX_EXTENDED_CELL_SETTINGS;
		}
	inline void ResetExtendedCellStyle()									//Reset the Extended Cell Styles member's bit in the bit field.
		{
			m_bitExFieldSettings &= ~CELL_EX_EXTENDED_CELL_SETTINGS;
		}
	inline void SetProtected(int bProtected)								//Set the Protected member and turn on its bit in the bit field.
		{
			m_bProtected = bProtected; 
			m_bitFieldSettings |= CELL_PROTECTED;
		}
	inline void ResetProtected()											//Reset the Protected member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_PROTECTED;
		}
	inline void SetCellFontBold(BOOL bBold)									//Set the CellFontBold member and turn on its bit in the bit field.
		{
			m_bFontBold = bBold; 
			m_bitFieldSettings |= CELL_FONT_BOLD;
		}
	inline void ResetCellFontBold()											//Reset the CellFontBold member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_FONT_BOLD;
		}
	inline void SetCellFontName(LPCTSTR lpszFontName)						//Set the CellFontName member and turn on its bit in the bit field.
		{
			m_csFontName = lpszFontName; 
			m_bitFieldSettings |= CELL_FONT_NAME;
		}
	inline void ResetCellFontName()											//Reset the CellFontName member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_FONT_NAME;
		}
	inline void SetCellFontItalic(BOOL bItalic)								//Set the CellFontItalic member and turn on its bit in the bit field.
		{
			m_bFontItalic = bItalic; 
			m_bitFieldSettings |= CELL_FONT_ITALIC;
		}
	inline void ResetCellFontItalic()										//Reset the CellFontItalic member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_FONT_ITALIC;
		}
	inline void SetCellFontSize(int nSize)									//Set the CellFontSize member and turn on its bit in the bit field.
		{
			m_nFontSize = nSize; 
			m_bitFieldSettings |= CELL_FONT_SIZE;
		}
	inline void ResetCellFontSize()											//Reset the CellFontSize member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_FONT_ITALIC;
		}
	inline void SetCellFontStrikeThru(BOOL bStrikeThru)						//Set the CellFontStrikeThru member and turn on its bit in the bit field.
		{	
			m_bFontStrikeThru = bStrikeThru; 
			m_bitFieldSettings |= CELL_FONT_STRIKETHRU;
		}
	inline void ResetCellFontStrikeThru()									//Reset the CellFontStrikeThru member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_FONT_STRIKETHRU;
		}
	inline void SetCellFontUnderline(BOOL bUnderline)						//Set the CellFontUnderline member and turn on its bit in the bit field.
		{
			m_bFontUnderline = bUnderline; 
			m_bitFieldSettings |= CELL_FONT_UNDERLINE;
		}
	inline void ResetCellFontUnderline()									//Reset the CellFontUnderline member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_FONT_UNDERLINE;
		}
	inline void SetCellColor(COLORREF rgbColor)								//Set the CellColor member and turn on its bit in the bit field.
		{
			m_rgbDefaultBkColor = rgbColor; 
			m_bitFieldSettings |= CELL_COLOR;
		}
	inline void ResetCellColor()											//Reset the CellColor member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_COLOR;
		}
	inline void SetCellTextColor(COLORREF rgbColor)							//Set the CellTextColor member and turn on its bit in the bit field.
		{
			m_rgbDefaultTextColor = rgbColor; 
			m_bitFieldSettings |= CELL_TEXT_COLOR;
		}
	inline void ResetCellTextColor()										//Reset the CellTextColor member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_TEXT_COLOR;
		}
	inline void SetCellBorder(CRect rectBorder)								//Set the CellBorder member and turn on its bit in the bit field.
		{
			m_rectBorder = rectBorder; 
			m_bitFieldSettings |= CELL_BORDER;
		}
	inline void ResetCellBorder()											//Reset the CellBorder member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_BORDER;
		}
	inline void SetCellBorderColor(COLORREF rgbBorderColor)					//Set the CellBorderColor member and turn on its bit in the bit field.
		{
			m_rgbBorderColor = rgbBorderColor; 
			m_bitFieldSettings |= CELL_BORDER_COLOR;
		}
	inline void ResetCellBorderColor()										//Reset the CellBorderColor member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_BORDER_COLOR;
		}
	inline void SetCellTextFormat(CString csFormat)							//Set the CellTextFormat member and turn on its bit in the bit field.
		{
			m_csFormat = csFormat; 
			m_bitFieldSettings |= CELL_TEXT_FORMAT;
		}
	inline void ResetCellTextFormat()										//Reset the CellTextFormat member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_TEXT_FORMAT;
		}
	inline void SetCellGCOName(CString csClassName)							//Set the CellGCOName member and turn on its bit in the bit field.
		{
			m_csGCOName = csClassName; 
			m_bitFieldSettings |= CELL_GCO_NAME;
		}
	inline void ResetCellGCOName()											//Reset the CellGCOName member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_GCO_NAME;
		}
	inline void SetCellAutomaticTextColor(BOOL bUseGridTextColor)			//Set the CellAutomaticTextColor member and turn on its bit in the bit field.
		{
			m_bUseGridTextColor = bUseGridTextColor; 
			m_bitFieldSettings |= CELL_AUTOMATIC_TEXTCOLOR;
		}
	inline void ResetCellAutomaticTextColor()								//Reset the CellAutomaticTextColor member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_AUTOMATIC_TEXTCOLOR;
		}
	inline void SetCellAutomaticBackColor(BOOL bUseGridBackColor)			//Set the CellAutomaticBackColor member and turn on its bit in the bit field.
		{
			m_bUseGridBackColor = bUseGridBackColor; 
			m_bitFieldSettings |= CELL_AUTOMATIC_BACKCOLOR;
		}
	inline void ResetCellAutomaticBackColor()								//Reset the CellAutomaticBackColor member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_AUTOMATIC_BACKCOLOR;
		}
	inline void SetCellAutomaticFont(BOOL bUseGridFont)						//Set the CellAutomaticFont member and turn on its bit in the bit field.
		{
			m_bUseGridFont = bUseGridFont; 
			m_bitFieldSettings |= CELL_AUTOMATIC_FONT;
		}
	inline void ResetCellAutomaticFont()									//Reset the CellAutomaticFont member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_AUTOMATIC_FONT;
		}
	inline void SetCellPattern(UINT nPatternID, COLORREF rgbForecolor)		//Set the CellPattern member and turn on its bit in the bit field.
		{
			m_nPatternID = nPatternID;
			m_rgbForecolor = rgbForecolor;
			m_bitFieldSettings |= CELL_PATTERN;
		}
	inline void ResetCellPattern()											//Reset the CellPattern member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_PATTERN;
		}
	inline void SetCellAlignment(UINT nVertAlign, UINT nHorzAlign, BOOL bWordWrap)	//Set the CellAlignment member and turn on its bit in the bit field.
		{
			m_nVertAlign = nVertAlign;
			m_nHorzAlign = nHorzAlign;
			m_bWordWrap = bWordWrap;
			m_bitFieldSettings |= CELL_TEXT_ALIGN;
		}
	inline void ResetCellAlignment()										//Reset the CellAlignment member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_TEXT_ALIGN;
		}
	inline void SetCellFormat(CString csFormat)								//Set the CellFormat member and turn on its bit in the bit field.
		{
			m_csFormat = csFormat;
			m_bitFieldSettings |= CELL_FORMAT;
		}
	inline void ResetCellFormat()											//Reset the CellFormat member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_FORMAT;
		}
	inline void SetCellValidStrings(CGWValidStrings* pValidStrings)			//Set the CellValidStrings member and turn on its bit in the bit field.
		{
			m_pValidStrings = pValidStrings;
			m_bitFieldSettings |= CELL_VALID_STRINGS;
		}
	inline void ResetCellValidStrings()										//Reset the CellValidStrings member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_VALID_STRINGS;
			m_pValidStrings = NULL;
		}
	inline void SetCellContextMenu(CString csContextMenuName)				//Set the CellContextMenu member and turn on its bit in the bit field.
		{
			m_csContextMenuName = csContextMenuName;
			m_bitFieldSettings |= CELL_CONTEXT_MENU;
		}
	inline void ResetCellContextMenu()										//Reset the CellContextMenu member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_CONTEXT_MENU;
			m_csContextMenuName.Empty();
		}
	inline void SetCellInputMask(CString csInputMask)						//Set the CellInputMask member and turn on its bit in the bit field.
		{
			m_csInputMask = csInputMask;
			m_bitFieldSettings |= CELL_INPUT_MASK;
		}
	inline void ResetCellInputMask()										//Reset the CellInputMask member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_INPUT_MASK;
		}
	inline void SetCellMinimum(double nMinimum)								//Set the CellMinimum member and turn on its bit in the bit field.
		{
			m_nMinimum = nMinimum; 
			m_bitFieldSettings |= CELL_MINIMUM_VALUE;
		}
	inline void ResetCellMinimum()											//Reset the CellMinimum member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_MINIMUM_VALUE;
		}
	inline void SetCellMaximum(double nMaximum)								//Set the CellMaximum member and turn on its bit in the bit field.
		{
			m_nMaximum = nMaximum; 
			m_bitFieldSettings |= CELL_MAXIMUM_VALUE;
		}
	inline void ResetCellMaximum()											//Reset the CellMaximum member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_MAXIMUM_VALUE;
		}
	inline void SetCellMaxLen(int nMaxLen)									//Set the CellMaxLen member and turn on its bit in the bit field.
		{
			m_nMaxLen = nMaxLen; 
			m_bitFieldSettings |= CELL_MAXIMUM_LENGTH;
		}
	inline void ResetCellMaxLen()											//Reset the CellMaxLen member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_MAXIMUM_LENGTH;
		}
	inline void SetCellBitmap(HBITMAP hBitmap)								//Set the CellBitmap member and turn on its bit in the bit field.
		{
			m_hBitmap = hBitmap; 
			m_bitFieldSettings |= CELL_BITMAP;
		}
	inline void ResetCellBitmap()											//Reset the CellBitmap member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_MAXIMUM_LENGTH;
		}
	inline void SetCellBitmapStyle(int nBitmapStyle)						//Set the CellBitmapStyle member and turn on its bit in the bit field.
		{
			m_nBitmapStyle = nBitmapStyle; 
			m_bitFieldSettings |= CELL_BITMAP_STYLE;
		}
	inline void ResetCellBitmapStyle()										//Reset the CellBitmapStyle member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_BITMAP_STYLE;
		}
	inline void SetCellOCXClass(CString csOCXClassName)						//Set the CellOCXClass member and turn on its bit in the bit field.
		{
			m_csOCXClassName = csOCXClassName;
			m_bitFieldSettings |= CELL_OCX_CLASS;
		}
	inline void ResetCellOCXClass()											//Reset the CellOCXClass member's bit in the bit field.
		{
			m_bitFieldSettings &= ~CELL_OCX_CLASS;
		}
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWCellSettings,"Operators")
	void operator&=(CGWCellSettings& pOtherCellSettings);			//Copy one CGWCellSettings to another.
//}}GW_MEMBERS

	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
		   GRIDWIZ_352 = 0,
			PRE_RELEASE = 1, 
			GRIDWIZ_354 = 2, 
			GRIDWIZ_355 = 3, 
		   Current_Version_Number,
		 } Version_Table;
	virtual void Serialize(CArchive& ar);

	
//GW_MEMBERS{{(CGWCellSettings,"Operations")
	DWORD		m_bitFieldSettings;			//DWORD Bit field showing which members have been initialized.
	DWORD		m_bitExFieldSettings;		//DWORD Bit field showing which extended members have been initialized.
	int			m_nEditFlag;				//Edit on entry/click/dblclick
	BOOL		m_bProtected;				//Does the cell respond to keys or mouse.
	DWORD		m_dwPrimaryControlStyle;	//Window Styles to apply to the primary control in the GCO.
	DWORD		m_dwSecondaryControlStyle;	//Window Styles to apply to the secondary control (if exists) in the GCO.
	BOOL		m_bFontBold;				//The Font Bold indicator for the cell font.
	CString		m_csFontName;				//The Font Face name for the cell font.
	BOOL		m_bFontItalic;				//The Font Italic indicator for the cell font.
	int			m_nFontSize;				//The font size.
	BOOL		m_bFontStrikeThru;          //The Font Strike Thru indicator for the cell font.
	BOOL		m_bFontUnderline;           //The Font Underline indicator for the cell font.
	COLORREF	m_rgbDefaultBkColor;		//Fill color
	COLORREF	m_rgbDefaultTextColor;		//Text Color
	BOOL		m_bUseGridFont;				//Automatic Font. Use the grid font.
	BOOL		m_bUseGridBackColor;		//Automatic fill color. Use the grid fill color.
	BOOL		m_bUseGridTextColor;		//Automatic text color. Use the grid text color.
	BOOL 		m_bDrawInverted;			//Draw cell in inverse video.
	UINT		m_nDrawTextStyle;			//Allows setting of additional drawtext styles.
	UINT		m_nVertAlign;				//Verical alignment within cell.
	UINT		m_nHorzAlign;				//Horizontal alignment within cell.
	BOOL		m_bWordWrap;				//Wrap text to multiple lines.
	CRect		m_rectBorder;         		//Border style  
	COLORREF	m_rgbBorderColor;			//Border Color
	UINT		m_nPatternID;				//Fill Pattern
	COLORREF	m_rgbForecolor;				//Pattern Forecolor
	CString		m_csFormat; 				//String identifies the output format.
	CString		m_csInputMask;				//String identifies the input mask format. 
	CString		m_csGCOName;				//CString containing the cell type for this cell. This takes precedence over all other mappings.
	CGWValidStrings* m_pValidStrings;		//Points to an object which holds the valid for this cell. These values are primarily used for ComboBox type cells.
	CString		m_csContextMenuName;		//Name of context menu for this cell.
	CRect		m_rectCellGroup;			//Cell group rectangle.
	double		m_nMinimum;					//Cell minimum allowable value.
	double		m_nMaximum;					//Cell maximum allowable value.
	int			m_nMaxLen;					//Maximum length of text allowed in cell.
	HBITMAP		m_hBitmap;					//Bitmap Handle.
	int			m_nBitmapStyle;				//Bitmap justification and strecth.
	BOOL		m_bAutoSizeRowHeight;		//Automatically size height to fit wrapped text.
	BOOL		m_bAutoSizeColumnWidth;		//Automatically size Width to fit single line text.
	CString		m_csOCXClassName;			//The name or class Id for an OCX control
	DWORD		m_dwExtendedCellStyle;		//Additional cell styles particular to specialized GCOs.
//}}GW_MEMBERS

};


class 	CRecordset;
class	CDocument;
class   CGWOleSwitch;
class GW_EXT_CLASS CGWGridSettings : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
protected: // create from serialization only
	DECLARE_SERIAL(CGWGridSettings)
public:
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
			PRE_UNICODE = 0, 
			GRIDWIZ_352 = 1,
			PRE_RELEASE = 2, 
			GRIDWIZ_354 = 3, 
			GRIDWIZ_355 = 4, 
			Current_Version_Number,
		 } Version_Table;

//GW_MEMBERS{{(CGWGridSettings,"Construction")
	CGWGridSettings()							//Default Constructor.
		{
			m_csTabMenuName = "Default";
			m_bWordWrap = FALSE;
		}
	virtual ~CGWGridSettings();					//Default Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWGridSettings,"Operations")
	void operator=(CGWGridSettings& pSettings);		//Copies on CGWGridSettings object to another.
	virtual void Serialize(CArchive& ar);			//Stores and loads a CGWGridSettings object to an from a CArchive object.
//}}GW_MEMBERS

//Data members
//GW_MEMBERS{{(CGWGridSettings,"Data Members")
	int 			m_nAddRow;                      // Allow on additional row for adding new row. Automatically incremented.
 	BOOL 			m_bAutoSizeColumns;             // Force all columns to fit exactly in the grid.
	COLORREF 		m_BackgroundColor; 				// RGB the background color for each cell.
	BOOL 			m_bBorder;       				// Draw a rectangle around the grid.
	int				m_nMaxColumns;					// Top of ScrollRange (Set this!)
	int				m_nMaxRows;             		// This one too.
    BOOL 			m_bResizeRows;   				// Determines whether the user can resize via fixed rows
    BOOL 			m_bResizeCols;  		 		// and Columns. Default TRUE;
    BOOL 			m_bRowSelect;   				// Determines whether the user can select rows by clicking on a fixed header
    BOOL 			m_bColSelect;  		  			// Determines whether the user can select columns by clicking on a fixed header font determine the extents.
    UINT 			m_nDisableNoScroll;				// Determines whether scrollbars are removed or just diabled.
    BOOL 			m_bDragAndDrop;            		// Enable drag and drop
	COLORREF 		m_FixedCellColor;      			// Fixed cell color. Defaults to COLOR_BTNFACE
	int				m_nFixedColumns;  	 			// Determines the number of fixed columns. 
	int 			m_nFixedRows;      				// Determines the number of fixed rows.
	int				m_nLockedColumns;  	 			// Determines the number of fixed columns. 
	int 			m_nLockedRows;      			// Determines the number of fixed rows.
	int				m_nDockedColumns;  	 			// Determines the number of columns docked on right. 
	int 			m_nDockedRows;      			// Determines the number of rows docked on left.
	LOGFONT 		m_LogFont;              		// The LogFont structure for the current Font
	int 	 		m_nPointSize;          			// The point size of the font to be used.
	COLORREF 		m_GridLineColor;      		 	// RGB value of the gridlines.
	BOOL			m_bGridLines;      				// Toggles whether there are visible gridlines.
	BOOL 			m_bInvertSelection;   			// Determines whether the selecting process will use Inverse Video to highlight.
	UINT 			m_nGridStyle;			        // Determines the grid style including the ability to select multiple regions
	POINT 			m_PenWidth;          			// The width of the pen in logical points.
    BOOL 			m_bRecordsetEnable;				// Is this grid used to go after a CRecordset Object
	BOOL			m_bShowFocusRect;  				// Controls whether the focus rect thing is drawn around current selection. Default is FALSE.
    BOOL 			m_vBar;                         // Determines whether the vertical scroll bars are visible or not.
	BOOL 			m_hBar;							// Determines whether the horizontal scroll bars are visible or not.
	BOOL 			m_bShowCurrentCell;   			// Determines whether the current cell has a selection box.
	UINT 			m_nSizingRegionWidth;          	// The size of the area used to resize rows and columns with the mouse. 
	BOOL 			m_bSynchronizePanes;    		// Controls whether one pane can drive another.
	COLORREF 		m_TextColor;           			// RGB value of the Cell Text. Defaults to COLOR_WINDOW.
	BOOL			m_bThumbScroll;   				// Enables or disables the thumbscroll.
	COLORREF 		m_HighlightColor;     			// Hightlight color. Not being used.
	int				m_nMinColumn;           		// Defaults to 1. Don't set < 1.
	int				m_nMinRow;              		// Defaults to 1. Don't set < 1.
    CString 		m_csPrintCaption;               // Caption used for the default grid printing.
	UINT 		  	m_nCurrentCursor;  				// The ResourceID of the current cursor.
	HCURSOR		  	m_hUserDefinedCursor;			// A curosr handle to be used instead of the grid's default.
    int 			m_nHScrollPos;        			// Corresponds to the position of the horizontal scroll bar.
    int 			m_nVScrollPos;       			// Corresponds to the position of the vertical scroll bar.
	CRecordset* 	m_pSet;         				// Automatically connect to a CRecordSet. Defaults to NULL.
	CDocument*      m_pDoc;							// Document pointer for the grid view.
    CGWOleSwitch*   m_pGWOleSwitch;                 // The CGWOleSwitch object has virtual functions which are routed to the m_pGWDropTarget object only when Drag and Drop are enabled.
	BOOL 			m_bGridError;                   // Is the cell which was editted in error?
    POINT   		m_CurrentCell;   				// The cell with focus.
    RECT 			m_rectCurrentCell;              // The CRect coordinates of the current cell.
	BOOL 			m_bSplitterRow;					// Controls how the splitter handles fixed rows.
	BOOL 			m_bSplitterCol;    				// Controls how the splitter handles fixed columns.		
    int 			m_nRowHeight;          			// The default extents of a grid cell in
    int 			m_nColWidth;           			// logical points.             
    float 			m_nRowHeightPoints;          	// The default height of a grid cell based on the current font.             
    float 			m_nColWidthChars;           	// The default width of a grid cell based on the current font.             
	int             m_nRowColUnits;                 // The defualt units for sizing a cell: PIXELS or CHARS
	CPtrArray     	m_paSelectionRects; 			// Holds the currently selected regions stored as CRect*. The members of the each CRect are Grid Row and Column indexes.  
	CGWMapIntToInt 	m_mwpHiddenRows;    			// Keeps track of any hidden rows.
	CGWMapIntToInt 	m_mwtpRowInfo;      			// Stores row height in pixels.
	CGWMapIntToInt 	m_mwtpRowHeight;      			// Stores row height in points.
	CGWMapIntToInt 	m_mwpHiddenColumns; 			// Keeps track of any hidden rows.
	CGWMapIntToInt 	m_mwtpColumnInfo;   			// Stores column width in pixels.
	CGWMapIntToInt 	m_mwtpColumnWidth;   			// Stores column width in characters.
	CGWMapIntToInt  m_mwtpMinColSize;               // Stores the minimum columns sizes.
	CString         m_csDefaultCellType;			// The default cell type name.
	CString			m_csContextMenuName;			// The name of the defualt context menu.
	UINT m_nRangeDragStyle;							// Controls drag and drop for rows.
	UINT m_nRowDragStyle;							// Controls drag and drop for columns.
	UINT m_nColumnDragStyle;						// Controls drag and drop for ranges.
	COLORREF m_clrfOutOfBounds;						// Area outside of grid but inside the window.
	int  m_nEditFlag;								// Controls how cells get activated.
	int  m_nTabControl;                             // Controls how the grid reacts to tab key.
	BOOL m_bWantDropNotify;							// Controls whether user is responsible for unpacking data when grid is drop target.
	BOOL m_bHiliteNoFocus;							// Controls whether the grid loses the hilight when it loses focus.
	BOOL m_bVirtualDataMode;						// Flag indicating whether user is handling data access through event handlers.
	BOOL m_bClipHeadings;							// Controls whether to include headings in clipboard operations.
	BOOL m_bShowEditIndicators;						// Controls whether edit status is shown in first fixed column.
	int  m_nStringCount;							// Number of strings to show when drop lists are displayed.
	int  m_bProtected;								// Controls whether entire sheet is protected by default.
	UINT     m_nVertAlign;							// Default vertical text alignment for sheet.
	UINT     m_nHorzAlign;							// Default horizontal text alignment for sheet.
	BOOL     m_bWordWrap;							// Default word wrap setting for sheet.
	CRect    m_rectBorder;         					// Default cell border style.
	UINT     m_nPatternID;							// Default cell fill pattern
	COLORREF m_rgbForecolor;						// Default cell pattern forecolor
	CString  m_csFormat; 							// String identifies the default cell output format.
	CString  m_csInputMask;							// String identifies the default cell input mask format. 
	BOOL m_bSizeColumnsTopToBottom;     // Determines whether sizing colums can be done from top to bottom rather than only in column headers. 
	BOOL m_bSizeRowsLeftToRight;		// Determines whether sizing rows can be done from left to right rather than only in row headers. 
	BOOL m_bShowTreeLines;				// Determines whether tree lines are shown.
	CString m_csTabMenuName;			// The context menu to be displayed over the tab area.
	BOOL m_bAutoSizeRowHeight;			// Automatically size height to fit wrapped text for all cells on the sheet.
	BOOL m_bAutoSizeColumnWidth;		// Automatically size Width to fit single line text for all cells on the sheet.
	BOOL m_bAutoSizeControlHeight;		// Automatically size height of grid window to fit all rows.
	BOOL m_bAutoSizeControlWidth;		// Automatically size Width of grid window to fit all columns.
	BOOL m_bAutoSizeVisibleOnly;		// Restrict autosize routine to access only cells that would be visible and all rows and columns.
	DWORD m_dwPrimaryControlStyle;		// Window control style to be applied to primary child control in cell.
	DWORD m_dwSecondaryControlStyle;	// Window control style to be applied to secondary child control in cell.
	DWORD m_dwExtendedCellStyle;		// Additional cell styles particular to specialized GCOs.
//}}GW_MEMBERS

};
    
class GW_EXT_CLASS CGWRowSettings : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
protected: 
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
		   Current_Version_Number,
		 } Version_Table;

	DECLARE_SERIAL(CGWRowSettings)
public:

//GW_MEMBERS{{(CGWRowSettings,"Construction")
	CGWRowSettings()									//Default Constructor,
		{};
	CGWRowSettings(CGWRowSettings* pRowSettings);		//Construct a CGWRowSettings object from another.
	virtual ~CGWRowSettings()							//Default Destructor.
		{};
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWRowSettings,"Operations")
	virtual void Serialize(CArchive& ar);			//Store and load a CGWRowSettings to and from a CArchive object.
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWRowSettings,"Data Members")
	CGWCellSettings	m_GWCellSettings;               // Default cell settings.
//}}GW_MEMBERS
};

    
class GW_EXT_CLASS CGWColumnSettings : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
protected: 
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
		   Current_Version_Number,
		 } Version_Table;
	DECLARE_SERIAL(CGWColumnSettings)
public:
//GW_MEMBERS{{(CGWColumnSettings,"Construction")
	CGWColumnSettings()										//Default Constructor,
		{ 
			m_nFieldIndex = -1;
		}
	CGWColumnSettings(CGWColumnSettings* pColSettings);		//Construct a CGWColumnSettings object from another.
	virtual ~CGWColumnSettings()							//Default Destructor.
		{};
//}}GW_MEMBERS

	
//GW_MEMBERS{{(CGWColumnSettings,"Operations")
	virtual void Serialize(CArchive& ar);			//Store and load a CGWColumnSettings to and from a CArchive object.
//}}GW_MEMBERS

//Data members
//GW_MEMBERS{{(CGWColumnSettings,"Data Members")
	int m_nFieldIndex;							    //Determines which datbase field this column is bound to.
	CGWCellSettings	m_GWCellSettings;				// Default cell settings.
//}}GW_MEMBERS
};


class GW_EXT_CLASS CGWGCOMappings : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
protected:
	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
		   Current_Version_Number,
		 } Version_Table;
	DECLARE_SERIAL(CGWGCOMappings)
public:
//GW_MEMBERS{{(CGWGCOMappings,"Construction")
	CGWGCOMappings()										//Default Constructor,
		{};
	virtual ~CGWGCOMappings();								//Default Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWGCOMappings,"Operations")
	virtual void Serialize(CArchive& ar);					//Store and load a CGWGCOMappings to and from a CArchive object.
//}}GW_MEMBERS

//Data members
//GW_MEMBERS{{(CGWGCOMappings,"Data Members")
	CStringArray 	m_RegisteredGCONames;					//Names of registered Grid Cell Objects.		
    CGWMapIntToInt 	m_mapFixedRowToGCONames;   				//Names of GCOs mapped to fixed rows.
    CGWMapIntToInt 	m_mapRowToGCONames;        				//Names of GCOs mapped to non-fixed rows.
    CGWMapIntToInt 	m_mapFixedColToGCONames;   				//Names of GCOs mapped to fixed columns.
    CGWMapIntToInt 	m_mapColToGCONames;        				//Names of GCOs mapped to non-fixed columns.
    CPtrArray 		m_arrayRanges;   						//Array of defined ranges.
    CUIntArray 		m_arrayGCOIndex;						//Indexes into registered GCO names for ranges.
	CString         m_csDefaultCellType;					//The name default cell type.
//}}GW_MEMBERS
};


#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif //__SETTINGS_H__
