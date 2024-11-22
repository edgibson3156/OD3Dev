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
//gwizgco.h     Header file for GridWiz built in GridCellObjects
#ifndef __GWIZGCO
#define __GWIZGCO 


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
	#ifdef _GWGCOIMP
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

class CGWGrid;
class CGWGridEdit;
class CGWGridDropDown;
class CGWGridListBox;
class CGWGridButton;      
class CGWListBoxPopup;
class CGWCellTip;
class GW_EXT_CLASS CGWGridCellObject : public CObject
{

//GW_CLASS{{(CGWGridCellObject)
/*

The CGWGridCellObject class is the root or base class for all other cell types. It provides a standard interface for
all cell types through which the grid will communicate. It also provides a base level of functionality required to 
display string data in a cell. This class can be used standalone or as a base class. The GridWiz Wizard can be used 
to generate new classes which derive from this one.The appearance of the cell output is controlled by property settings whose values 
are transfered into the GCO from a CGWCellSettings structure when the cell is created. The CGWCellSettings structure
is maintained by the CGWDataSource derived class and is mostly modified by CGWGrid functions. That is, setting cell 
properties involves calling CGWGrid functions which persist the property setting in a CGWCellSettings structure 
stored in the grid CGWDataSource object. When cells are created, the property values are extracted from the 
CGWCellSettings structure. The OnCreate() virtual function is called during the cell's creation process just after
the settings have been applied from the CGWCellSettings structure. Override this function to set an additional 
cell properties.

CGWGridCellObject instances exist only for visible cells. The grid manages a cache of objects and updates this 
cache as the user scrolls, adds or removes rows or changes the size of the grid's client area. Therefore, it is 
important that you never store the address of a CGWGridCellObject for later use. 

 PrepareCell(), DrawCellBorder(), DrawGridCell() virtual functions are called when the cell 
is being painted to the screen or to a report. Override one or more of these functions to change the appearance of the cell. 

The DrawGridCell() function calls the CGWGrid virtual function OnGetCellText() to retrieve the text string to display in the 
cells area. The property settings for the cell then determine how to format it within  the area available.

This is a read-only type cell. That is, there is no editing capability built into this cell. It is possible to change the 
contents of this cell by either drag and drop or via import.

*/

//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWGridCellObject)

//GW_ENUMERATIONS{{(CGWGridCellObject, "Edit event Specifiers.")
	enum nEditFlag
	{
		EDIT_NEVER = 0,					//Grid Cell object never activates embedded windows control.
		EDIT_ON_SETFOCUS = 1,			//Grid Cell object activates embedded windows control when cell gets focus.
		EDIT_ON_LBUTTONUP = 2,			//Grid Cell object activates embedded windows control when cell gets LButtonUp message.
		EDIT_ON_LBUTTONDBLCLK = 3,		//Grid Cell object activates embedded windows control when cell gets LButtonDblClk message.
		EDIT_ALWAYS = 4,				//Grid Cell object activates embedded windows control when cell gets WM_PAINT message.
	} nEditFlags;    
//}}GW_ENUMERATIONS
                              
//GW_ENUMERATIONS{{(CGWGridCellObject, "Cell Border styles.")
	enum BorderStyles
	{
		BS_NONE = 0,
		BS_STANDARD = 0,
		BS_DOT  = 1,
		BS_DASH = 2,
		BS_SOLID_ONE = 3, 
		BS_SOLID_TWO = 4,
		BS_SOLID_THREE = 5,
		BS_DOUBLE = 6,
		BS_RAISED = 7,
		BS_INSET = 8,
	} nBorderStyles;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGridCellObject, "Cell test alignment styles.")
	enum TextAlignment
	{
		VERT_ALIGN_TOP = 0,
		VERT_ALIGN_CENTER = 1,
		VERT_ALIGN_BOTTOM = 2,
		HORZ_ALIGN_LEFT = 0,
		HORZ_ALIGN_CENTER = 1,
		HORZ_ALIGN_RIGHT = 2,
	} nAlign;
//}}GW_ENUMERATIONS

//GW_ENUMERATIONS{{(CGWGridCellObject, "Cell popup tip styles.")
    enum CellTipStyle					
    {
		CELLTIP_DISABLED,				//This cell does not use cell tips.
		CELLTIP_CONTENTS,				//Cell Tip is the contents of the cell if truncated. (DEFAULT)
		CELLTIP_TIP,					//Cell Tip is a popup tip.
    } CellTipStyle;   
//}}GW_ENUMERATIONS

public:
//GW_MEMBERS{{(CGWGridCellObject,"Construction")
	CGWGridCellObject();				//Default Constructor.
	virtual ~CGWGridCellObject();		//Default Destructor.
//}}GW_MEMBERS	

//Working functions
//GW_MEMBERS{{(CGWGridCellObject,"Data Members")
	CGWGrid* m_pGrid;					//The grid to which this GCO belongs.
	UINT m_nRowNdx;						//The cells row index.
	UINT m_nColNdx;						//The cells column index.
	CRect m_rectCellGroup;				//The group cell coordinates if this cell belongs to group.
	CString m_csInitialValue;			//The string for this cell
	CObject* m_pExtraData;				//An extra data pointer for this cell
	BOOL     m_bFontBold;				//The font bold setting for this cell.
	CString  m_csFontName;				//The font face name setting for this cell.
	BOOL     m_bFontItalic;				//The font italic setting for this cell.
	int      m_nFontSize;				//The font point size setting for this cell.
	BOOL     m_bFontStrikeThru;			//The font strike thru setting for this cell.	
	BOOL     m_bFontUnderline;          //The font underline setting for this cell.
	COLORREF m_rgbDefaultBkColor;		//The background color used to draw the cell.
	COLORREF m_rgbDefaultTextColor;		//The text color used to draw the cell.
	BOOL     m_bUseGridFont;			//Flag indicating whether to use the grid's font rather than the cell's font.
	BOOL     m_bUseGridBackColor;		//Flag indicating whether to use the grid's backcolor rather than the cell's backcolor.
	BOOL     m_bUseGridTextColor;		//Flag indicating whether to use the grid's text color rather than the cell's text color.
	BOOL 	 m_bDrawInverted;			//Flag indicating whether to draw certain portions of the cell as inverted so it looks normal when hilighted.
	UINT     m_nDrawTextStyle;			//The style bits applied when the cell calls the CDC DrawText function.
	UINT     m_nVertAlign;				//The vertical text alignment flag.
	UINT     m_nHorzAlign;				//The horizontal text alignment flag.
	BOOL     m_bWordWrap;				//The text word wrap flag.
	DWORD   m_dwPrimaryControlStyle;    //Windows style applied to Primary control in GCO.
	DWORD   m_dwSecondaryControlStyle;  //Windows style applied to Secondary control (if exists) in GCO.
	double m_nMinimum;					//Minimum value allowed to be enterred into a cell.
	double m_nMaximum;					//Maximum value allowed to be enterred into a cell.
	int m_nMaxLen;						//The maximum text length allowed to enterred into a cell.
	CString m_csContextMenuName;		//The name of the context menu to be used for this cell.
	CRect    m_rectBorder;              //The cell border style bits to be used to draw this cell.  
	COLORREF m_rgbBorderColor;  	    //The cell border color to be used to draw this cell.  
	UINT     m_nPatternID;              //The fill pattern to be used to draw this cell.  
	COLORREF m_rgbForecolor;            //The pattern forecolor to be used to draw this cell. 
	CString  m_csFormat; 				//String identifies the format for outputing the cell.
	CString  m_csInputMask; 			//String identifies the format for the input output mask.
	CGWValidStrings* m_pValidStrings;	//The valid string pointer to be used to fill the drop down list portion of the cell.
	BOOL    m_bDataMustFit;             //If set to TRUE, either all the data fits or a line of #'s will be drawn.
	BOOL	m_bProtected;               //Determines whether cell responds to UI messages.
	CString m_csOCXClassName;			//Control or Class Name for embedded OCX control.
	BOOL m_bAutoSizeRowHeight;			//Automatically size height to fit wrapped text.
	BOOL m_bAutoSizeColumnWidth;		//Automatically size Width to fit single line text.
	BOOL m_bSendExtraData;				//Flag indicating whether user item data is sent to the grid when the user makes a selection from a drop list type cell.
	int m_nEditFlag;					//Flag indicating the event which causes the cell to become editable.
	int	m_nCellTipStyle;				//The cell tip style. Either show contents or some sort of tip.
	DWORD m_dwExtendedCellStyle;		//Additional cell styles particular to specialized GCOs.
	HBITMAP m_hBitmap;					//Handle of a bitmap to display in this cell.
	int m_nBitmapStyle;					//Alignment of bitmap within cell.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWGridCellObject,"Protected Data Members")
	CFont*   m_pfontDefault;			//The cells font.
	CFont*   m_pfontControl;			//The font used for controls that the cell manages.
	BOOL	 m_bReadOnly;				//Can be used to turn off editing of cells.
    CWnd* m_pFloatingCtrl;				//Address of the floating window control to be managed by this GCO.
	static UINT m_nCustomDestroy;		//Registered Window message for destroying a cell.
	CBrush* m_pbrushBackGround;			//Address of a CBrush object to be used as the backcolor.		
	CString m_csInternalMask;			//Internal input mask.
	int m_nDigitsToLeft; 				//Number of digits to left of decimal;
	int m_nDigitsToRight; 				//Number of digits to right;  
	int m_nZeroesToLeft; 				//Number of digits formated to zero to the left;
	int m_nZeroesToRight; 				//Number of digits formated to zero to right;  
	BOOL m_bComma;						//Does the format contain commas
	BOOL m_bSign;						//Does the format contain sign
	BOOL m_bDollar;						//Does the format contain a dollar sign
	BOOL m_bPercent;					//Does the format contain a percent sign
	BOOL m_bDecimal;					//Does the format contain a decimal point
	BOOL m_bProcessEditBoxKeyStrokes;	//Allows combobox cell to navigate.
	static CGWCellTip* m_pCellTip;				//The cell tip window associate with this cell.
//}}GW_MEMBERS	

	
//Operations
public:
//GW_MEMBERS{{(CGWGridCellObject,"Operations")
	void Refresh()											//Cause this cell to be redrawn.
		{m_pGrid->InvalidateCell(m_nRowNdx, m_nColNdx);}
	BOOL CreateControlFont(CDC* pDC);						//Create the font to be used for the control managed by this cell.
	void DestroyControlFont();								//Destroy the font used for the control managed by this cell.
	BOOL CreateCellFont(CDC* pDC);							//Create the font to be used for drawing this cell.
	void DestroyCellFont();									//Destroy the font to used for drawing this cell.
	CRect GetCellRect(BOOL bAccountForGroups = TRUE);       //Get the device coordinates for this cell.    
	int GetNextSel(WORD nCurSel);							//Get the next available char to edit in input mask
	int GetPrevSel(WORD nCurSel);							//Get the prior available char to edit in input mask
//}}GW_MEMBERS	
	
//Overridelables; 
public:
//GW_MEMBERS{{(CGWGridCellObject,"Overridelables")
	virtual void Initialize();																			//Assigns the design time property settings.
	virtual void PrepareCell(CDC* pDC, CRect& DrawRect);												//Creates the background brush and fills in the cell.
	virtual void DrawCellBorder(CDC* pDC, CRect& DrawRect);												//Draws the cell's border if any.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Draws the cell's contents or current state.
	virtual void DrawCellBitmap(CDC* pDC, CRect TextRect);												//Draws a bitmap in the cell.
	virtual CGWTabStop GetTabStop(CPoint point);														//Get the next tabstop object within this cell.
	virtual CGWTabStop GetCurrentTabStop()																//Get the current tabstop object within this cell.
			{return CGWTabStop(m_nColNdx, 1);}
	virtual void GCOLostFocus()																			//Event function which notifies that the GCO has lost focus.
		{m_pGrid->m_pGCOFocus = NULL;}
	virtual void GCOSetFocus()																			//Event function which notifies that the GCO has received focus.
		{m_pGrid->m_pGCOFocus = this;};
	virtual void CurrentCellState()																		//Instructs the cell to stop editing and revert to a neutral state.
		{};
	virtual void OnCreate();																			//Called to allow for assignment of properties before the cell is displayed but after the m_pGrid member has been set.
	virtual void GCOOnMouseMove(UINT nFlags, CPoint point)												//Notification from the grid or embedded window control that there is a mousemove message for this cell.
			{m_pGrid->GridOnMouseMove(nFlags, point);};
	virtual void GCOOnLButtonDown(UINT nFlags, CPoint point)											//Notification from the grid or embedded window control that there is a LButtonDown message for this cell.
			{m_pGrid->GridOnLButtonDown(nFlags, point);};
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point)												//Notification from the grid or embedded window control that there is a LButtonUp message for this cell.
			{m_pGrid->GridOnLButtonUp(nFlags, point);};
	virtual void GCOOnRButtonDown(UINT nFlags, CPoint point)											//Notification from the grid or embedded window control that there is a RButtonDown message for this cell.
			{};		
	virtual void GCOOnRButtonUp(UINT nFlags, CPoint point)												//Notification from the grid or embedded window control that there is a RButtonUp message for this cell.
			{m_pGrid->GridOnRButtonUp(nFlags, point);};
	virtual void GCOOnLButtonDblClk(UINT nFlags, CPoint point);											//Notification from the grid or embedded window control that there is a LButtonDblClk message for this cell.
	virtual void GCOOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)									//Notification from the grid or embedded window control that there is a KeyDown message for this cell.
			{m_pGrid->GridOnKeyDown(nChar, nRepCnt, nFlags);};
	virtual void GCOOnChar(UINT nChar, UINT nRepCnt, UINT nFlags)										//Notification from the grid or embedded window control that there is a Char message for this cell.
			{m_pGrid->GridOnChar(nChar, nRepCnt, nFlags);};
    virtual void GCODoSetCursor(UINT nFlags, CPoint& point)												//Event function request that the cell specify a cursor or pass the request on to the grid.
			{m_pGrid->DoSetCursor(nFlags, point);}		
	virtual void SetEditFocus(CGWTabStop* pTabStop)														//Called to set input focus to a particular tab stop within the cell.
			{};    
	virtual void GCOOnInitializeCtrl()																	//Event function which is called after the window control for the cell is created but before it is displayed.
			{};
	virtual void ResetCell()																			//Cause a cell to be rebuilt.
		{};
	virtual void GCOOnTimer(UINT nIDEvent)																//Notification from the grid or embedded window control that there is a Timer message for this cell.
		{m_pGrid->GridOnTimer(nIDEvent); }
	virtual BOOL GetVariableExtents(CDC* pDC, CSize* pszCellSize);										//Check to see if the cell supports autosizing and return the desired size.
//}}GW_MEMBERS	

//Inout Processing
//GW_MEMBERS{{(CGWGridCellObject,"Input Processing")
	virtual CString FormatEnterData(CWnd* pFloatingCtrl)												//Called when the user has entered data and that data needs to be formated before validating and passing it on to the grid.
		{return m_csInitialValue;}
	virtual BOOL ValidateData(CString& csFormatedText, CWnd* pFloatingCtrl)								//Event function which allows for validating data entered by the user before passing it on to the grid.
		{
			BOOL bValid = m_pGrid->OnCellValidateData(m_nRowNdx, m_nColNdx, csFormatedText);
			m_pGrid->SetGridError(!bValid);
			return bValid;
		}
	virtual CString ApplyInputMask(CString csCellText)													//Event function used to apply the input mask as data is being entered into the cell.
		{return TRUE;}
	virtual BOOL CheckInputChar(TCHAR& ch, int& nSel)													//Event function which checks each character entered by the user to see if it is acceptable to the input mask.
		{return TRUE;}
//}}GW_MEMBERS	

//Output Processing
//GW_MEMBERS{{(CGWGridCellObject,"Output Processing")
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);	//Called to format the cell text before drawing.
	virtual void FormatFloatText(CString& csCellText);					//Called to format a floating point value before drawing.
	virtual void FormatIntegerText(CString& csCellText);				//Called to format a integer value before drawing.
	virtual void FormatDateText(CString& csCellText);					//Called to format a date/time value before drawing.
	virtual void SetFormat(CString csFormat);							//Sets the format string for the value of this cell.
//}}GW_MEMBERS	

//Editting Window Control handling Functions
//GW_MEMBERS{{(CGWGridCellObject,"Editting")
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE)	//Causes the window control for this cell to be created and dispalyed.
		{};
	virtual void UpdateControlPosition()								//Called to postion the control above the cell.
		{};
	virtual CRect GetControlPosition()									//Called to retrieve the control position above the cell.
		{return GetCellRect();}
	virtual void CreateFloatingCtrl(CWnd* pParent)						//Called to create the window control(s) for this cell.
		{};
	virtual BOOL IsEditingNow()											//Called to determine if the window control for this cell is active and accepting user input.
		{return FALSE;}
	virtual void SelectStrings(CString csCellText)						//Called to select the strings from the current value.
		{};  
	virtual LPDISPATCH GetGCODispatch()									//Retrieve the IDispatch interface for the OCX managed by this cell.
		{return NULL;}
	virtual void DestroyControl()										//Called to destroy the windows control managed by this cell.
		{m_pFloatingCtrl = NULL;}
//}}GW_MEMBERS	

//Various GCO Notifications
//GW_MEMBERS{{(CGWGridCellObject,"GCO Notifications")
	virtual void GCOOnFloatingButtonClick()								//Event function signaling that a button control managed by this cell has been clicked.
		{};
	virtual void GCOOnFloatingButtonDblClick()							//Event function signaling that a button control managed by this cell has been double clicked.
		{};
    virtual void GCOOnSelChange()										//Event function signaling that a selection change has been made in a drop list control.
		{};	
	virtual void GCOOnSelEndOKFloatingDDL()								//Event function signaling that a SelEndOK event has ocurred in a drop list control.
		{};
	virtual void GCOOnDropDownFloatingDDL()								//Event function signaling that a drop list has been drop down.
		{};
	virtual void GCOOnCloseUpFloatingDDL()								//Event function signaling that a drop list has been closed.
		{};
	virtual void OnAccept()												//Event function signaling that a OK button managed by this cell has been clicked .
		{};
	virtual void OnReject()												//Event function signaling that a Cancel button managed by this cell has been clicked .
		{};
//}}GW_MEMBERS	
	
	
//Member access functions
public:
//GW_MEMBERS{{(CGWGridCellObject,"Member Access Functions")
	inline COLORREF GetBackColor() 				//Get the backcolor member.
		{return m_rgbDefaultBkColor;}
	inline BOOL GetFontBold() 					//Get the FontBold member.
		{return m_bFontBold;}
	inline CString GetFontFaceName() 			//Get the Font FaceName member.
		{return m_csFontName;}
	inline BOOL GetFontItalic() 				//Get the Font Italic member.
		{return m_bFontItalic;}
	inline int GetFontPointSize() 				//Get the Font Point Size member.
		{return m_nFontSize;}
	inline BOOL GetUseGridFont()                //Get the Use Grid Font member.
		{return m_bUseGridFont;}
	inline BOOL GetUseGridBackColor()           //Get the Use Grid BackColor member.
		{return m_bUseGridBackColor;}
	inline BOOL GetUseGridTextColor()           //Get the Use Grid TextColor member.
		{return m_bUseGridTextColor;}
	inline COLORREF GetTextColor() 				//Get the TextColor member.
		{return m_rgbDefaultTextColor;}
	inline BOOL GetDrawInverted()				//Get the DrawInverted member.
		{return m_bDrawInverted;}
    inline UINT GetDrawTextStyle()              //Get the DrawText style member.
		{return m_nDrawTextStyle;}
	inline int GetEditFlag()                    //Get the Edit Event member.
		{return m_nEditFlag;}
    inline BOOL GetProtected()					//Get the Protected member.
		{return m_bProtected;}
	inline double GetMinimum()                  //Get the Minimum value member.
		{return m_nMinimum;}
	inline double GetMaximum()                  //Get the Maximum value member.
		{return m_nMaximum;}
	inline CString GetFormat() 				    //Get the Format string member.
		{return m_csFormat;}
	inline void SetBackColor(COLORREF clrf, BOOL bRefresh = FALSE);					//Set the BackColor member
	inline void SetFontBold(BOOL bFontBold, BOOL bRefresh = FALSE);					//Set the FontBold member.
	inline void SetFontFaceName(_TCHAR* lpszFaceName, BOOL bRefresh = FALSE);		//Set the Font FaceName member.
	inline void SetFontItalic(BOOL bFontItalic, BOOL bRefresh = FALSE);				//Set the Font Italic member.
	inline void SetFontPointSize(int nFontPointSize, BOOL bRefresh = FALSE);		//Set the Font Point Size member.
	inline void SetUseGridFont(BOOL bUseGridFont, BOOL bRefresh = FALSE);			//Set the Use Grid Font member.
	inline void SetUseGridBackColor(BOOL bUseGridBackColor, BOOL bRefresh = FALSE);	//Set the Use Grid BackColor member.
	inline void SetUseGridTextColor(BOOL bUseGridTextColor, BOOL bRefresh = FALSE); //Set the Use Grid TextColor member.
	inline void SetTextColor(COLORREF clrf, BOOL bRefresh = FALSE);					//Set the TextColor member.
	inline void SetDrawInverted(BOOL bDrawInverted, BOOL bRefresh = FALSE);			//Set the DrawInverted member.
    inline void SetDrawTextStyle(UINT nDrawTextStyle, BOOL bRefresh = FALSE);		//Set the DrawText style member.
    inline void SetEditFlag(int nEditFlag, BOOL bRefresh = FALSE)					//Set the Edit Event member.
		{m_nEditFlag = nEditFlag;}
    inline void SetProtected(int bProtected, BOOL bRefresh = FALSE)					//Set the Protected member.
		{m_bProtected = bProtected;}
	inline void SetMinimum(double nMinimum, BOOL bRefresh = TRUE);					//Set the Minimum value member.
	inline void SetMaximum(double nMaximum, BOOL bRefresh = TRUE);					//Set the Maximum value member.
//}}GW_MEMBERS	


//inline properties sets
protected:
//GW_MEMBERS{{(CGWGridCellObject,"Inline Properties Sets")
	inline void GW_BACKCOLOR(COLORREF clrf) 					//Set the BackColor member		
		{SetBackColor(clrf, FALSE);}
	inline void GW_FONTBOLD(BOOL bFontBold)						//Set the FontBold member.
		{SetFontBold(bFontBold, FALSE);}
	inline void GW_FONTFACENAME(_TCHAR* lpszFaceName)			//Set the Font FaceName member. 	
		{SetFontFaceName(lpszFaceName, FALSE);}
	inline void GW_FONTITALIC(BOOL bFontItalic)					//Set the Font Italic member.        
		{SetFontItalic(bFontItalic, FALSE);}
	inline void GW_FONTPOINTSIZE(int nFontPointSize)			//Set the Font Point Size member.  
		{SetFontPointSize(nFontPointSize, FALSE);}
	inline void GW_TEXTCOLOR(COLORREF clrf)						//Set the TextColor member.           
		{SetTextColor(clrf, FALSE);}
	inline void GW_USEGRIDFONT(BOOL bUseGridFont)				//Set the Use Grid Font member.				        
		{SetUseGridFont(bUseGridFont, FALSE);}
	inline void GW_USEGRIDBACKCOLOR(BOOL bUseGridBackColor)		//Set the Use Grid BackColor member.	
		{SetUseGridBackColor(bUseGridBackColor, FALSE);}
	inline void GW_USEGRIDTEXTCOLOR(BOOL bUseGridTextColor)		//Set the Use Grid TextColor member.
		{SetUseGridTextColor(bUseGridTextColor, FALSE);}
	inline void GW_DRAWINVERTED(BOOL bDrawInverted)				//Set the DrawInverted member.		  
		{SetDrawInverted(bDrawInverted, FALSE);}
	inline void GW_TEXTSTYLE(UINT nDrawTextStyle)				//Set the DrawText style member.   		
		{SetDrawTextStyle(nDrawTextStyle, FALSE);}
	inline void GW_EDITFLAG(int nEditFlag)						//Set the Edit Event member.        		
		{SetEditFlag(nEditFlag, FALSE);}
//}}GW_MEMBERS	
};

inline void CGWGridCellObject::SetBackColor(COLORREF clrf, BOOL bRefresh)
{
	m_rgbDefaultBkColor = clrf;
	if (bRefresh)
		Refresh();
}

inline void CGWGridCellObject::SetUseGridFont(BOOL bUseGridFont, BOOL bRefresh)
{
	m_bUseGridFont = bUseGridFont;
	if (bRefresh)
		Refresh();
}

inline void CGWGridCellObject::SetUseGridBackColor(BOOL bUseGridBackColor, BOOL bRefresh)
{
	m_bUseGridBackColor = bUseGridBackColor;
	if (bRefresh)
		Refresh();
}

inline void CGWGridCellObject::SetUseGridTextColor(BOOL bUseGridTextColor, BOOL bRefresh)
{
	m_bUseGridTextColor = bUseGridTextColor;
	if (bRefresh)
		Refresh();
}

inline void CGWGridCellObject::SetFontBold(BOOL bFontBold, BOOL bRefresh)
{
	m_bFontBold = bFontBold;
	if (bRefresh)
		Refresh();
}    

inline void CGWGridCellObject::SetFontFaceName(_TCHAR* lpszFaceName, BOOL bRefresh)
{
	m_csFontName = lpszFaceName;
	if (bRefresh)
		Refresh();
}    

inline void CGWGridCellObject::SetFontItalic(BOOL bFontItalic, BOOL bRefresh)
{
	m_bFontItalic = bFontItalic;
	if (bRefresh)
		Refresh();
}    

inline void CGWGridCellObject::SetFontPointSize(int nFontPointSize, BOOL bRefresh)
{
	m_nFontSize = nFontPointSize;
	if (bRefresh)
		Refresh();
}    

inline void CGWGridCellObject::SetTextColor(COLORREF clrf, BOOL bRefresh)
{
	m_rgbDefaultTextColor = clrf;
	if (bRefresh)
		Refresh();
}

inline void CGWGridCellObject::SetDrawInverted(BOOL bDrawInverted, BOOL bRefresh)
{
	m_bDrawInverted = bDrawInverted;
	if (bRefresh)
		Refresh();
}

inline void CGWGridCellObject::SetDrawTextStyle(UINT nDrawTextStyle, BOOL bRefresh)
{
	m_nDrawTextStyle = nDrawTextStyle;

	if (nDrawTextStyle & DT_WORDBREAK)
		m_bWordWrap = TRUE;				   
	else
		m_bWordWrap = FALSE;

	if (nDrawTextStyle & DT_BOTTOM)
		m_nVertAlign = VERT_ALIGN_BOTTOM;				   
	else if	(nDrawTextStyle & DT_VCENTER)
		m_nVertAlign = VERT_ALIGN_CENTER;				   
	else
		m_nVertAlign = VERT_ALIGN_TOP;				   
	
	if (nDrawTextStyle & DT_RIGHT)
		m_nHorzAlign = HORZ_ALIGN_RIGHT;				   
	else if	(nDrawTextStyle & DT_CENTER)
		m_nHorzAlign = HORZ_ALIGN_CENTER;				   
	else
		m_nHorzAlign = HORZ_ALIGN_LEFT;				   

	if (bRefresh)
		Refresh();
}


inline void CGWGridCellObject::SetMinimum(double nMinimum, BOOL bRefresh)
{
	m_nMinimum = nMinimum;
	if (bRefresh)
		Refresh();
}

inline void CGWGridCellObject::SetMaximum(double nMaximum, BOOL bRefresh)
{
	m_nMaximum = nMaximum;
	if (bRefresh)
		Refresh();
}



class GW_EXT_CLASS CGWHeaderCell: public CGWGridCellObject
{

//GW_CLASS{{(CGWHeaderCell)
/*

The CGWHeaderCell class is typically used for cells which are located in fixed rows or columns. These
are commonly referred to as row and column headers. This cell derives from CGWGridCellObject and adds
functionality for drawing a 3D border for the cell and making its background color appear as a button.

You can use this class as-is or derive a new class from it using the GridWiz Wizard. 

*/
	
	DECLARE_DYNCREATE(CGWHeaderCell)
public:
//GW_MEMBERS{{(CGWHeaderCell,"Construction")
	virtual ~CGWHeaderCell();		//Default Destructor.
	CGWHeaderCell();				//Default Constructor.
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWHeaderCell,"Overriden Virtual Functions")
	virtual void OnCreate();									//Overriden to assign header cell defualt property values.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overriden to take over the drawing of this cell.
	virtual void PrepareCell(CDC* pDC, CRect& DrawRect);			//Overriden to take over the back filling and border drawing of this cell.
//}}GW_MEMBERS	
};


#include <sys/timeb.h> 
/////////////////////////////////////////////////////////////////////////////
// CGWCellTip 
class GW_EXT_CLASS CGWCellTip : public CWnd
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS

public:
//GW_MEMBERS{{(CGWCellTip,"Protected Data Members")
	CGWCellTip();									//Default Contructor.
	CGWCellTip(CString &strClass);					//Construct a CGWCellTip object.
	virtual ~CGWCellTip();							//Default Destructor.
//}}GW_MEMBERS

   
// Attributes
public:
//GW_MEMBERS{{(CGWCellTip,"Data Members")
	static CString m_csClass;						//The window class name for the cell tip window.
	CGWGrid* m_pGrid;								//Pointer to the grid.
	CGWGridCellObject* m_pGCO;						//Pointer the cell object.
	CString m_csCellTip;							//Text value of the cell tip if not cell content style.
	_timeb m_lastTime;								//The system date when the last click ocurred. Used to simulate LButtonDblClk.
//}}GW_MEMBERS

// Operations
public:

//GW_MEMBERS{{(CGWCellTip,"Operations")
	void SetText(LPCTSTR lpszCellTip);				//Set the cell tip text.
	BOOL ShowCellTip();								//Show the cell tip window.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWCellTip,"Overriden Virtual Functions")
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );		//Overriden to apply special create styles.
	virtual void PostNcDestroy( );							//Overriden to delete the C++ object.
//}}GW_MEMBERS

// Implementation
protected:

//GW_MEMBERS{{(CGWCellTip,"Message Handlers")
	afx_msg void OnPaint();											//Passes the paint message on to the grid cell object.
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);							//Called to erase the backgroun of tip window.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);			//Handled to hittest against the tip window and pass on to grid.
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);		//Handled to pass meesage along to grid.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);			//Handled to pass meesage along to grid.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);			//Handled to pass meesage along to grid.
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);			//Handled to pass meesage along to grid.
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);			//Handled to pass meesage along to grid.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Handled to pass meesage along to grid.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Handled to pass meesage along to grid.
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);	//Handled to pass meesage along to grid.
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);	//Responds to this message with the cell or grid specific cursor.
	afx_msg void OnTimer(UINT nIDEvent);							//Handled to make sure tooltip destroys itself correctly.
//}}GW_MEMBERS

	DECLARE_MESSAGE_MAP()
};




#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS


#endif  //__GWIZGCO_H__
