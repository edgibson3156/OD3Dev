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
///////////////////////////////////////////////////////
//stdgrid.h   -    Precompiled headers for GridWiz
#ifndef __EDITGCO_H__
#define __EDITGCO_H__ 

#pragma warning(disable : 4100)

#ifdef _WIN32
#include <afxtempl.h>
#endif


#define REGISTER_EDIT_GCOS() \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWEditCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWDropDownListCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWComboBoxCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWCheckBoxCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWRadioBtnCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWButtonCell));	



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
	#ifdef _GWEDITGCOIMP
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

class GW_EXT_CLASS CGWEditCell: public CGWGridCellObject
{
//GW_CLASS{{(CGWEditCell)
/*

The CGWEditCell class derives directly from CGWGridCellObject and adds editing functionality through
a edit box control. The edit box control is created and displayed over the cell giving the impression
that the cell is editable. When the user exists the cell after editing, the contents of the edit box 
is read and passed on to the grid via the OnSetCellText() virtual function. The edit box is usually created
when the user clicks the cell, but can be created at other times based on the setting of the Edit Event 
property. The function responsible for this is called MoveFloatingCtrl(). MoveFloatingCtrl actually handles
both showing the edit box and removal. When called with a value of TRUE, the function calls another virtual 
function called CreateFloatingCtrl. This function actually creates the Window to be displayed. When called 
with a value of FALSE, MoveFloatingCtrl validates the contents of the edit box by calling the CGWGrid virtual 
function OnCellValidateData and provided there were no errors, calls the CGWGrid virtual function called 
OnSetCellText to pass the data onto the grid for storage. 


To use this GCO, you need to define the constant USE_EDIT_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EDIT_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWEditCell)
public:
//GW_MEMBERS{{(CGWEditCell,"Construction")
	CGWEditCell();				//Default constructor.
	virtual ~CGWEditCell();		//Destructor.
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWEditCell,"Data Members")
    CGWGridEdit* m_pFloatingEditCtrl;			//Contains the address of the CEdit derivative control.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWEditCell,"Operations")
	virtual void SetSel(int nStart, int nEnd);	//Sets the location of the caret within the edit box.
//}}GW_MEMBERS

//Member access functions
public:
//GW_MEMBERS{{(CGWEditCell,"Member access")
	inline void SetEditStyles(DWORD dwEditStyles, BOOL bRefresh=FALSE);		//Sets the windows styles associated with the edit box.
	inline DWORD GetEditStyles()											//Gets the windows styles associated with the edit box.
									{return m_dwPrimaryControlStyle;}
//}}GW_MEMBERS
	

//Overridden CGWGridCellObject virtual function	
//GW_MEMBERS{{(CGWEditCell, "Overriden Virtual Functions")
	virtual void UpdateControlPosition();									//Overidden to move the edit control the correct location in the cell.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);		//Overidden to hide or show the edit box.
	virtual void CreateFloatingCtrl(CWnd* pParent);							//Overidden to create the edit box.
	virtual void GCOLostFocus();											//Overidden to accept notification of losing focus and destroy the edit box.
	virtual void CurrentCellState();										//Overidden to reset the editing state of the control.
	virtual void DestroyControl();											//Overidden to destroy the CEdit derivative window.
	virtual void GCOOnChar(UINT nChar, UINT nRepCnt, UINT nFlags);			//Overidden to accept notification of the WM_CHAR message.
	virtual void GCOOnLButtonDblClk(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONDBLCLK message.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);					//Overidden to accept notification of the WM_LBUTTONUP message.
	virtual void GCOOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);		//Overidden to accept notification of the WM_KEYDOWN message.
	virtual void SetRect(LPRECT lpRect);									//Overidden to set the editing rectangle within the control.
	virtual void SetEditFocus(CGWTabStop* pTabStop)							//Overidden to set the focus to the edit box within the cell.
									{MoveFloatingCtrl(TRUE); m_pGrid->GetFocusCell() = this;}
	virtual void GCOSetFocus()												//Overidden to accept notification of the WM_SETFOCUS message.
								{if (!m_pFloatingEditCtrl && GetEditFlag() == EDIT_ON_SETFOCUS) 
									{
										MoveFloatingCtrl(TRUE);
										m_pGrid->GetFocusCell() = this;
									}
								};
	virtual void ResetCell();													//Overidden to cause a cell to re-initialize itself from settings stored in the grid's data source.
	virtual BOOL ValidateData(CString& csFormatedText, CWnd* pFloatingCtrl);	//Overidden to validate the contents of the edit box before the data is committed via OnSetCellText.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);						//Overidden to format freshly entered data prior to validation.
	virtual BOOL IsEditingNow()													//Overidden to provide information about the editing state of the cell.
								{if (m_pFloatingEditCtrl) return TRUE;
									 return FALSE;}
	virtual CString ApplyInputMask(CString csCellText);							//Overidden to apply the input mask to the cell.
	virtual BOOL CheckInputChar(TCHAR& ch, int& nSel);							//Overidden to check data entry when input masks are used.
	virtual CRect GetControlPosition();											//Overidden to retrieve the screen location of edit box.
//}}GW_MEMBERS

//inline properties sets
protected:
	inline void GW_EDITSTYLES(DWORD dwEditStyles)       {SetEditStyles(dwEditStyles, FALSE);}

};

inline void CGWEditCell::SetEditStyles(DWORD dwEditStyles, BOOL bRefresh)
{
	m_dwPrimaryControlStyle = dwEditStyles;
	if (bRefresh)
		Refresh();
}


class GW_EXT_CLASS CComboBoxEdit : public CEdit
{
//GW_INTERNAL_CLASS{{(CComboBoxEdit)
/*


*/
//}}GW_CLASS	
// Construction
public:
	CComboBoxEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboBoxEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();										//Handled so that all keys are sent to the control when the grid is in a dialog box.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


class GW_EXT_CLASS CGWDropDownListCell: public CGWGridCellObject
{
//GW_CLASS{{(CGWDropDownListCell)
/*

The CGWDropDownListCell class derives directly from CGWGridCellObject and adds editing functionality through
a combobox control. The combobox control is created and displayed over the cell giving the impression
that the cell is editable. When the user exists the cell after editing, the contents of the combobox 
is read and passed on to the grid via the OnSetCellText() virtual function. Additionally, the CBN_SELCHANGE
notification is trapped and the CGWGrid virtual function OnCellSelChange is called with information on the
selection being made.

The combobox is usually created when the user clicks the cell, but can be created at other times based on the 
setting of the Edit Event property. The function responsible for this is called MoveFloatingCtrl(). MoveFloatingCtrl 
actually handles both showing the combobox and removal. When called with a value of TRUE, the function calls another virtual 
function called CreateFloatingCtrl. This function actually creates the Window to be displayed. When called 
with a value of FALSE, MoveFloatingCtrl validates the contents of the combobox by calling the CGWGrid virtual 
function OnCellValidateData and provided there were no errors, calls the CGWGrid virtual function called 
OnSetCellText to pass the data onto the grid for storage. 

There are two ways to populate the listbox portion of the combobox. The first method invloves overriding the 
CGWGrid virtual function OnGetCellValidString(). This function is called repeatedly just prior to the drop being
displayed. The function returns a boolean value which when set to FALSE stops the loop. Otherwise, the GCO keeps
calling OnGetCellValidString to add new entries to the drop list. The second method uses the CGWValidStringObject
class to build a list of strings. The CGWValidStringsObject name is then associated a range of cells. When the
cell is created, the address of the CGWValidStringsObject is provided to the cell. 
	

To use this GCO, you need to define the constant USE_EDIT_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EDIT_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWDropDownListCell)
public:
//GW_MEMBERS{{(CGWDropDownListCell,"Data Members")
	CStringArray 	m_Strings;					//Strings which are displayed in the drop list portion of the cell.
	CPtrArray    	m_Ptrs;						//Extra data pointers associated with strings.
    int 			m_nNumItems;				//Number of items visible in the listbox portion. 
    int 			m_nCurrentSelection;		//The index of the currently selected item.
	BOOL            m_bDirty;					//Identifies the control is dirty or has been updated and not committed.
    CGWGridDropDown* m_pFloatingDDL;			//Address of the CComboBox derivative window used for this cell.
	CComboBoxEdit	m_ComboBoxEdit;
	int				m_nExtraDataField;			// Field index of the extra data item which is part of a VSO based on SQL result set. Defaults to last field.
//}}GW_MEMBERS
public:
//Construction
//GW_MEMBERS{{(CGWDropDownListCell,"Construction")
	virtual ~CGWDropDownListCell();				//Default constructor.
	CGWDropDownListCell();						//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWDropDownListCell,"Overrideables")
	virtual void AddStrings();					//Calls grid virtual functions to add strings to the string collection.
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWDropDownListCell,"Operations")
	virtual int   AddString(const _TCHAR* lpszStr);			//Adds a string to the string array.
	virtual void  ResetContent();							//Removes and frees all strings and extra data items.
	virtual void  InsertString(int nIndex, CString& str);	//Inserts a string into the array of strings.
	virtual void  DeleteString(int nIndex);					//Removes a string from the array of strings.
	virtual void* GetItemDataPtr(int nIndex);				//Retrieves a pointer associated with a particular string.
	virtual void  SetItemDataPtr(int nIndex, void* ptr);	//Associates a pointer value with a string.
	void SetCurSel(int nCurSel)								//Sets the currently selected item.
				{m_nCurrentSelection = nCurSel;}
	int GetCurSel()											//Retrieves the index of the currently selected item.
				{return m_nCurrentSelection;}
//}}GW_MEMBERS

	
//Member access functions
//GW_MEMBERS{{(CGWDropDownListCell,"Member Access")
	inline int GetNumItems() 					//Retrieves the maximum number of items to be displayed at once.
		{return m_nNumItems;}
	virtual void  SetNumItems(int nNumItems)	//Sets the maximum number of items to be displayed at once.
		{m_nNumItems = nNumItems;}
//}}GW_MEMBERS


//Overridden CGWGridCellObject virtual functions
//GW_MEMBERS{{(CGWDropDownListCell, "Overriden Virtual Functions")
	virtual void OnCreate();											//Overidden to specify additional creation criteria.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);	//Overidden to hide or show the combobox.
	virtual void UpdateControlPosition();								//Overidden to move the combobox control the correct location in the cell.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to perform specific drawing for this cell.
	virtual void CreateFloatingCtrl(CWnd* pParent);						//Overidden to create the combobox.
	virtual void GCOLostFocus();										//Overidden to accept notification of the WM_KILLFOCUS message.
	virtual void CurrentCellState();									//Overidden to reset the editing state of the control.
	virtual void DestroyControl();										//Overidden to destroy the CEdit derivative window.
	virtual void GCOOnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Overidden to accept notification of the WM_CHAR message.
	virtual void GCOOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Overidden to accept notification of the WM_KEYDOWN message.
	virtual void GCOOnLButtonDblClk(UINT nFlags, CPoint point);			//Overidden to accept notification of the WM_LBUTTONDBLCLK message.
	virtual void GCOOnSelEndOKFloatingDDL();							//Overidden to accept notification of the CBN_SELENDOK message.
	virtual void GCOOnDropDownFloatingDDL();							//Overidden to accept notification of the CBN_DROPDOWN message.
	virtual void GCOOnCloseUpFloatingDDL();								//Overidden to accept notification of the CBN_CLOSEUP message.
	virtual void SetEditFocus(CGWTabStop* pTabStop)						//Overidden to set the focus to the combobox box within the cell.
			{MoveFloatingCtrl(TRUE);}
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONDOWN message. 
	virtual void GCOOnInitializeCtrl();									//Overidden to perform special initialization on this cell type.
	virtual void GCOSetFocus()											//Overidden to accept notification of the WM_SETFOCUS message.
			{if (!m_pFloatingDDL && GetEditFlag() == EDIT_ON_SETFOCUS) 
				{
					MoveFloatingCtrl(TRUE);
					m_pGrid->GetFocusCell() = this;
				}
			};
	virtual BOOL IsEditingNow()											//Overidden to provide information about the editing state of the cell.
			{if (m_pFloatingDDL) return TRUE;
				 return FALSE;}
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);	//Overidden to apply any formating characters to the contents of the cell.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);				//Overidden to format freshly entered data prior to validation.
	virtual void ResetCell();											//Overidden to cause a cell to re-initialize itself from settings stored in the grid's data source.
//}}GW_MEMBERS

//inline properties sets
protected:
	inline void GW_NUMITEMS(int nNumItems)       	  {SetNumItems(nNumItems);}
};


/////////////////////////////////////////////////////////////////////////////////////
// CGWRadioBtn
class GW_EXT_CLASS CGWRadioBtn : public CObject
{
//GW_INTERNAL_CLASS{{(CGWRadioBtn)
/*
*/
//}}GW_CLASS	
public:

//GW_MEMBERS{{(CGWRadioBtn,"Construction")
	CGWRadioBtn(CGWGridCellObject* pGCO, int nIndex, CString csCaption, CString csValue);
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWRadioBtn,"Data Members")
	CGWGridCellObject* m_pGCO;					//Pointer to the grid cell object which contains this CGWRadioBtn object.
	int m_nIndex;								//The index of this button within the cell. 
	CString m_csCaption;						//Caption displayed alongside this button in the cell.
	CString m_csValue;							//The value of the cell if this button is on.
	BOOL m_bStatus;								//The on/off status of this button.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWRadioBtn,"Operations")
	BOOL HitTest(CPoint point);					//Tests if a client coordinate is within the button.
	BOOL GetStatus();							//Gets the current on/off status of this CGWRadioBtn object.
	void SetStatus(BOOL bStatus);				//Sets the current on/off status of this CGWRadioBtn object.
	virtual void Draw(CDC* pDC);				//Draws the radio button to the device context.
//}}GW_MEMBERS
};

/////////////////////////////////////////////////////////////////////////////////////
// CGWRadioBtnCell
class GW_EXT_CLASS CGWRadioBtnCell: public CGWGridCellObject
{
//GW_CLASS{{(CGWRadioBtnCell)
/*

The CGWRadioBtnCell cell derives from CGWGridCellObject and provides the user interface of one or more 
radio buttons in a cell. The radio button can either have a checked or unchecked status in the case of 
a single radio button. In this case the value of the cell is "1" if checked and "0" or blank if unchecked.
To obtain multiple radio buttons in a cell, assign a CGWValidStringsObject or override the OnGetCellValidString
virtual function on the CGWGrid derived class. In this case the cell will display a radio button next to each 
entry in the list and the value of the cell will the string which has the checked radio button.


To use this GCO, you need to define the constant USE_EDIT_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EDIT_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWRadioBtnCell)
public:
//GW_MEMBERS{{(CGWRadioBtnCell,"Data Members")
	CObArray m_arBtns;			//Array of CGWRadioBtn objects
	BOOL m_bChecked;			//Indicates whether any have been checked.
	CSize m_sizeCheckBox;		//Size box used to dimension the radio button.
//}}GW_MEMBERS

//Construction
//GW_MEMBERS{{(CGWRadioBtnCell,"Construction")
	virtual ~CGWRadioBtnCell();	//Destructor.
	CGWRadioBtnCell();			//Default Constructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWRadioBtnCell, "Overriden Virtual Functions")
	virtual void OnCreate();											//Overidden to specify additional creation criteria.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to perform specific drawing for this cell.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONDOWN message. 
	virtual void GCOOnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Overidden to accept notification of the WM_CHAR message.
	virtual void SetStatus(BOOL bChecked);								//Overidden to communicate the status or value of the cell.
	virtual BOOL GetStatus();											//Overidden to communicate the status or value of the cell.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);				//Overidden to format freshly entered data prior to validation.
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);	//Overidden to apply any formating characters to the contents of the cell.
    virtual void GCODoSetCursor(UINT nFlags, CPoint& point);			//Overidden to set the cursor when the mouse is over the radio button.
	virtual void DestroyControl();										//Overidden to destroy additional elements of the cell.
//}}GW_MEMBERS
};


/////////////////////////////////////////////////////////////////////////////////////
// CGWCheckBox
class GW_EXT_CLASS CGWCheckBox : public CObject
//GW_INTERNAL_CLASS{{(CGWCheckBox)
/*
*/
//}}GW_CLASS	
{
public:
//GW_MEMBERS{{(CGWCheckBox,"Construction")
	CGWCheckBox(CGWGridCellObject* pGCO, int nIndex, CString csCaption, CString csValue);  //Constructor
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWCheckBox,"Data Members")
	CGWGridCellObject* m_pGCO;					//Pointer to the grid cell object which contains this CGWCheckBox object.	
	int m_nIndex;								//The index of this button within the cell. 
	CString m_csCaption;						//Caption displayed alongside this button in the cell.
	CString m_csValue;							//The value of the cell if this button is on.
	BOOL m_bStatus;								//The on/off status of this button.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWCheckBox,"Operations")
	BOOL HitTest(CPoint point);					//Tests if a client coordinate is within the button.
	BOOL GetStatus();							//Gets the current on/off status of this CGWRadioBtn object.
	void SetStatus(BOOL bStatus);				//Sets the current on/off status of this CGWRadioBtn object.
	virtual void Draw(CDC* pDC);				//Draws the radio button to the device context.
//}}GW_MEMBERS
};

/////////////////////////////////////////////////////////////////////////////////////
// CGWCheckBoxCell
class GW_EXT_CLASS CGWCheckBoxCell: public CGWGridCellObject
{
//GW_CLASS{{(CGWCheckBoxCell)
/*

The CGWCheckBoxCell cell derives from CGWGridCellObject and provides the user interface of one or more 
check boxes in a cell. The check box can either have a checked or unchecked status in the case of 
a check box button. In this case the value of the cell is "1" if checked and "0" or blank if unchecked.
To obtain multiple check boxes in a cell, assign a CGWValidStringsObject or override the OnGetCellValidString
virtual function on the CGWGrid derived class. In this case the cell will display a check box next to each 
entry in the list and the value of the cell will the string which has the checked  checkbox button.


To use this GCO, you need to define the constant USE_EDIT_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EDIT_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWCheckBoxCell)
public:
//GW_MEMBERS{{(CGWCheckBoxCell,"Data Memebers")
	CObArray m_arBoxes;			//Array of CGWCheckBox objects
	BOOL m_bChecked;			//Indicates whether any have been checked.
	CSize m_sizeCheckBox;		//Size box used to dimension the checkbox button.
//}}GW_MEMBERS

//Construction
//GW_MEMBERS{{(CGWCheckBoxCell,"Construction")
	virtual ~CGWCheckBoxCell();		//Destructor
	CGWCheckBoxCell();				//Default Constructor
//}}GW_MEMBERS


//Member access functions
//GW_MEMBERS{{(CGWCheckBoxCell,"Member Access")
	inline void SetCheckBoxWidth(int nWidth, BOOL bRefresh = TRUE);		//Sets the width of the checkbox.	
	inline void SetCheckBoxHeight(int nHeight, BOOL bRefresh = TRUE);	//Sets the height of the checkbox.
	inline int GetCheckBoxWidth()										//Return the width of the checknbox.
									{return m_sizeCheckBox.cx;}
	inline int GetCheckBoxHeight()										//Return the height of the checkbox.
									{return m_sizeCheckBox.cy;}
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWCheckBoxCell, "Overriden Virtual Functions")
	virtual void OnCreate();											//Overidden to specify additional creation criteria.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to perform specific drawing for this cell.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONDOWN message. 
	virtual void GCOOnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Overidden to accept notification of the WM_CHAR message.
	virtual void SetStatus(BOOL bChecked);								//Overidden to communicate the status or value of the cell.
	virtual BOOL GetStatus();											//Overidden to communicate the status or value of the cell.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);				//Overidden to format freshly entered data prior to validation.
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);	//Overidden to apply any formating characters to the contents of the cell.
    virtual void GCODoSetCursor(UINT nFlags, CPoint& point);			//Overidden to set the cursor when the mouse is over the checkbox button.
	virtual void DestroyControl();										//Overidden to destroy additional elements of the cell.
//}}GW_MEMBERS


//inline properties sets
protected:
	inline void GW_CHECKBOXWIDTH(int nWidth)                {SetCheckBoxWidth(nWidth, FALSE);}
    inline void GW_CHECKBOXHEIGHT(int nHeight)              {SetCheckBoxHeight(nHeight, FALSE);}
};


inline void CGWCheckBoxCell::SetCheckBoxWidth(int nWidth, BOOL bRefresh)
{
	m_sizeCheckBox.cx = nWidth;
	if (bRefresh)
		Refresh();
}

inline void CGWCheckBoxCell::SetCheckBoxHeight(int nHeight, BOOL bRefresh)
{
	m_sizeCheckBox.cy = nHeight;
	if (bRefresh)
		Refresh();
}


class GW_EXT_CLASS CGWComboBoxCell : public CGWEditCell
{
//GW_CLASS{{(CGWComboBoxCell)
/*

The CGWComboBoxCell class derives directly from CGWEditCell and adds editing functionality through
a combobox control. The combobox control is created and displayed over the cell giving the impression
that the cell is editable. When the user exists the cell after editing, the contents of the combobox 
is read and passed on to the grid via the OnSetCellText() virtual function. Additionally, the CBN_SELCHANGE
notification is trapped and the CGWGrid virtual function OnCellSelChange is called with information on the
selection being made.

The combobox is usually created when the user clicks the cell, but can be created at other times based on the 
setting of the Edit Event property. The function responsible for this is called MoveFloatingCtrl(). MoveFloatingCtrl 
actually handles both showing the combobox and removal. When called with a value of TRUE, the function calls another virtual 
function called CreateFloatingCtrl. This function actually creates the Window to be displayed. When called 
with a value of FALSE, MoveFloatingCtrl validates the contents of the combobox by calling the CGWGrid virtual 
function OnCellValidateData and provided there were no errors, calls the CGWGrid virtual function called 
OnSetCellText to pass the data onto the grid for storage. 

There are two ways to populate the listbox portion of the combobox. The first method invloves overriding the 
CGWGrid virtual function OnGetCellValidString(). This function is called repeatedly just prior to the drop being
displayed. The function returns a boolean value which when set to FALSE stops the loop. Otherwise, the GCO keeps
calling OnGetCellValidString to add new entries to the drop list. The second method uses the CGWValidStringObject
class to build a list of strings. The CGWValidStringsObject name is then associated a range of cells. When the
cell is created, the address of the CGWValidStringsObject is provided to the cell. 

The CGWComboBoxCell differs from the CGWDropDownListCell in that the elements of the combobox are created 
separately. This allows for multi-selection drop lists and a better overall grid user-interface. Otherwise, 
both classes operate essentially the same.
	

To use this GCO, you need to define the constant USE_EDIT_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EDIT_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWComboBoxCell)
public:
//GW_MEMBERS{{(CGWComboBoxCell,"Data Memebers")
	CGWGridListBox*   m_pFloatingListBox;			//Address of the CListBox derivative window used for this cell.	
	CGWListBoxPopup*	m_pFloatingPopup;			//Address of the CWnd derivative window used for this cell.
	BOOL 			m_bSnapUp;						//State variable indicating the control is closing the listbox portion of the cell.
	CStringArray 	m_Strings;						//The array of strings used to populate the listbox.
	CPtrArray    	m_Ptrs;							//Extra data pointers associated with each string.
    int 			m_nNumItems;					//Maximum number of visible items.
    int 			m_nCurrentSelection;			//The current selected index.
    CUIntArray 		m_arraySelections;				//Array used to store multiple selections.
	int				m_nExtraDataField;			// Field index of the extra data item which is part of a VSO based on SQL result set. Defaults to last field.
//}}GW_MEMBERS

public:                         
//CGWGridcellObject Overrides
//GW_MEMBERS{{(CGWComboBoxCell, "Overriden Virtual Functions")
	virtual void CurrentCellState();									//Overidden to reset the editing state of the control.
	virtual void OnCreate();											//Overidden to specify additional creation criteria.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to perform specific drawing for this cell.
	virtual void GCOOnLButtonDown(UINT nFlags, CPoint point);			//Overidden to accept notification of the WM_LBUTTONDOWN message.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONUP message.
	virtual void GCOLostFocus();										//Overidden to accept notification of the WM_KILLFOCUS message.
    virtual void GCODoSetCursor(UINT nFlags, CPoint& point);			//Overidden to set the cursor when the mouse is over the drop arrow button.
	virtual void GCOOnInitializeCtrl();									//Overidden to perform special initialization on this cell type.
	virtual void AddStrings();											//Overriden to control grid virtual functions to add strings to the string collection.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);	//Overidden to hide or show the combobox.
	virtual void CreateFloatingCtrl(CWnd* pParent);						//Overidden to create the edit box, popup window and listbox.
	virtual void DestroyControl();										//Overidden to destroy the windows controls for this cell.
	virtual void GCOOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Overidden to accept notification of the WM_KEYDOWN message.
	virtual void GCOOnChar(UINT nChar, UINT nRepCnt, UINT nFlags);	//Overidden to accept notification of the WM_CHAR message.
	virtual CRect GetControlPosition();									//Overidden to calculate and return the screen location of edit box.
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);	//Overidden to apply any formating characters to the contents of the cell.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);				//Overidden to format freshly entered data prior to validation.
    virtual void  GCOOnSelChange();										//Overidden to accept notification of the LBN_SELCHANGE message.
	virtual void SelectStrings(CString csCellText);						//Called to select the strings from the current value.
//}}GW_MEMBERS

public:
//Construction
//GW_MEMBERS{{(CGWComboBoxCell,"Construction")
	virtual ~CGWComboBoxCell();			//Destructor.
	CGWComboBoxCell();					//Default Constructor.
//}}GW_MEMBERS

//Operations
//GW_MEMBERS{{(CGWComboBoxCell,"Operations")
	CRect GetBtnRect();												//Calculates the rectangle for the drop button.
	virtual void  SetNumItems(int nNumItems)						//Sets the maximum number of visible items.
		{m_nNumItems = nNumItems;}
	virtual int   AddString(const _TCHAR* lpszStr);					//Adds a string to the string collection.
	virtual void  ResetContent();									//Removes and destroys all strings and extra data pointers.
	virtual void  InsertString(int nIndex, CString& str);			//Inserts a string into the string collection.
	virtual void  DeleteString(int nIndex);							//Removes a string from the string collection.
	virtual void* GetItemDataPtr(int nIndex);						//Retrieve an extra data pointer associated with a string.
	virtual void  SetItemDataPtr(int nIndex, void* ptr);			//Assign an extra data pointer to a string.
	virtual void  ShowListBox(BOOL bShow);							//Show or hide the listbox portion of the cell. 
	void SetCurSel(int nCurSel)										//Set the current selection for the cell.
								{m_nCurrentSelection = nCurSel;}
	int GetCurSel()													//Retrieve the current selection for the cell. 
								{return m_nCurrentSelection;}
//}}GW_MEMBERS

//Member access functions
//GW_MEMBERS{{(CGWComboBoxCell,"Member Access")
	inline void SetLBStyles(DWORD dwLBStyles, BOOL bRefresh=FALSE);	//Controls the window style of the listbox.
	inline int  GetNumItems()										//Return the maximum number of visible items.
								{return m_nNumItems;}
	inline DWORD GetLBStyles()										//Retrieve the window style of the listbox.
								{return m_dwSecondaryControlStyle;}
//}}GW_MEMBERS

	
//inline properties sets
protected:
	inline void GW_NUMITEMS(int nNumItems)              {SetNumItems(nNumItems);}
	inline void GW_LISTBOXSTYLES(DWORD dwLBStyles)       {SetLBStyles(dwLBStyles, FALSE);}
};

inline void CGWComboBoxCell::SetLBStyles(DWORD dwLBStyles, BOOL bRefresh)
{
	m_dwSecondaryControlStyle = dwLBStyles;
	if (bRefresh)
		Refresh();
}


class GW_EXT_CLASS CGWButtonCell: public CGWGridCellObject
{
//GW_CLASS{{(CGWButtonCell)
/*

The CGWButtonCell very simply manages a push button over the entire cell. The click events for the button are handled
and passed on to CGWGrid virtual functions. The CGWGrid::OnCellNotify() function is passed the row and column coordinates
along with either BN_CLICKED or BN_DBLCLICK identifiers.


To use this GCO, you need to define the constant USE_EDIT_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EDIT_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

	DECLARE_DYNCREATE(CGWButtonCell)

public:
//GW_MEMBERS{{(CGWButtonCell,"Data Members")
	CGWGridButton* m_pFloatingButton;
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWButtonCell,"Construction")
	virtual ~CGWButtonCell();	//Destructor.
	CGWButtonCell();			//Default Constructor.
//}}GW_MEMBERS

	
//CGWGridcellObject Overrides
//GW_MEMBERS{{(CGWButtonCell, "Overriden Virtual Functions")
	virtual void GCOOnFloatingButtonClick();							//Overidden to accept notification of the BN_CLICKED message.
	virtual void GCOOnFloatingButtonDblClick();							//Overidden to accept notification of the BN_DBLCLK message.
	virtual CRect GetButtonRect();										//Overidden to calculate and return the coordinates for the button.
	virtual void GCOLostFocus();										//Overidden to accept notification of the WM_KILLFOCUS message.	
	virtual void CurrentCellState();									//Overidden to reset the editing state of the control.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);	//Overidden to hide or show the button.
	virtual void UpdateControlPosition();								//Overidden to move the button control the correct location in the cell.
	virtual void CreateFloatingCtrl(CWnd* pParent);						//Overidden to create the button.
	virtual void DestroyControl();										//Overidden to destroy the CEdit derivative window.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONUP message.
	virtual void GCOSetFocus()											//Overidden to accept notification of the WM_SETFOCUS message.	
		{if (!m_pFloatingButton && GetEditFlag() == EDIT_ON_SETFOCUS) 
			{
				MoveFloatingCtrl(TRUE);
				m_pGrid->GetFocusCell() = this;
			}
		};
	virtual BOOL IsEditingNow()											//Overidden to provide information about the editing state of the cell.
			{if (m_pFloatingButton) return TRUE;
				 return FALSE;}
	virtual void GCOOnLButtonDown(UINT nFlags, CPoint point)			//Overidden to accept notification of the WM_LBUTTONDOWN message.
			{if (m_pGrid->GetCurrentCell() != CPoint(m_nRowNdx, m_nColNdx))
				m_pGrid->GridOnLButtonDown(nFlags, point);};
	virtual void ResetCell();											//Overidden to cause a cell to re-initialize itself from settings stored in the grid's data source.
//}}GW_MEMBERS
};

class GW_EXT_CLASS CGWGridEdit : public CEdit
{
//GW_INTERNAL_CLASS{{(CGWGridEdit)
/*
*/
//}}GW_CLASS	
public:
//Construction
//GW_MEMBERS{{(CGWGridEdit,"Construction")
	~CGWGridEdit();
//}}GW_MEMBERS

//Construction
//GW_MEMBERS{{(CGWGridEdit,"Operations")
	void ResizeControl(BOOL bVert);	//Resizes the control while typing. Implements support for AutoSizing.
//}}GW_MEMBERS


//GW_MEMBERS{{(CGWGridEdit, "Overriden Virtual Functions")
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);				//Message handled to monitor keystrokes into cells.
	void OnLButtonDown(UINT nFlags, CPoint point);						//Message handled to monitor mouse clicks in cells.
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);					//Message handled to monitor keystrokes into cells.
	afx_msg void OnKillFocus(CWnd* pWnd);								//Message handled to trigger commitment mechanism for cell data.
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Handled to monitor use of the ALT key.
	afx_msg UINT OnGetDlgCode();										//Handled so that all keys are sent to the control when the grid is in a dialog box.
	long OnSetSel(UINT wParam, long lParam);							//Handled to monitor the WM_SETSEL message.
	long OnCustomDestroy(UINT nMsg, long l);							//Handled to monitor special destruction requests made by grid.
	afx_msg void OnDestroy();										//Message handled to destroy the control.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()

};

class GW_EXT_CLASS CGWGridDropDown : public CComboBox
{
//GW_INTERNAL_CLASS{{(CGWGridDropDown)
/*
*/
//}}GW_CLASS	
public:
//GW_MEMBERS{{(CGWGridDropDown, "Overriden Virtual Functions")
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Message handled to monitor keystrokes into cells.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Message handled to monitor keystrokes into cells.
	afx_msg void OnKillFocus(CWnd* pWnd);							//Message handled to trigger commitment mechanism for cell data.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);			//Message handled to monitor mouse clicks in cells.
	afx_msg UINT OnGetDlgCode();									//Handled so that all keys are sent to the control when the grid is in a dialog box.
	long OnCustomDestroy(UINT nMsg, long l);						//Handled to monitor special destruction requests made by grid.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()

};

class GW_EXT_CLASS CGWGridButton : public CButton
{
//GW_INTERNAL_CLASS{{(CGWGridButton)
/*
*/
//}}GW_CLASS	
public:
//GW_MEMBERS{{(CGWGridButton, "Overriden Virtual Functions")
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);			//Message handled to monitor mouse clicks in cells.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);			//Message handled to monitor mouse clicks in cells.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);			//Message handled to monitor mouse clicks in cells.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Message handled to monitor keystrokes into cells.
	afx_msg void OnKillFocus(CWnd* pWnd);							//Message handled to trigger commitment mechanism for cell data.
	afx_msg void OnDestroy();										//Message handled to destroy the control.
	afx_msg UINT OnGetDlgCode();									//Handled so that all keys are sent to the control when the grid is in a dialog box.
	long OnCustomDestroy(UINT nMsg, long l);						//Handled to monitor special destruction requests made by grid.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()

};




class GW_EXT_CLASS CGWGridListBox : public CListBox
{
//GW_INTERNAL_CLASS{{(CGWGridListBox)
/*
*/
//}}GW_CLASS	
public:
//Construction
//GW_MEMBERS{{(CGWGridListBox,"Construction")
	CGWGridListBox();					//Default constructor.
	virtual ~CGWGridListBox();			//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWGridListBox, "Overriden Virtual Functions")
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Message handled to monitor keystrokes into cells.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Message handled to monitor keystrokes into cells.
	afx_msg void OnKillFocus(CWnd* pWnd);							//Message handled to trigger commitment mechanism for cell data.
	afx_msg void OnDestroy();										//Message handled to destroy the control.
	afx_msg UINT OnGetDlgCode();									//Handled so that all keys are sent to the control when the grid is in a dialog box.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);			//Message handled to monitor mouse clicks in cells.
	long OnCustomDestroy(UINT nMsg, long l);						//Handled to monitor special destruction requests made by grid.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CListBoxPopup window

class GW_EXT_CLASS CGWListBoxPopup : public CWnd
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
// Construction
//GW_MEMBERS{{(CGWListBoxPopup,"Construction")
	CGWListBoxPopup();				//Default Constructor.
	virtual ~CGWListBoxPopup();		//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWListBoxPopup,"Data Members")
	CGWGrid* m_pGrid;				//Pointer to the parent CGWGrid object.
	static CString  m_strClass;		//Window class name.
	CGWComboBoxCell* m_pGCO;		//Pointer to the grid cell object owning this window.
//}}GW_MEMBERS

protected:
//GW_MEMBERS{{(CGWListBoxPopup, "Overriden Virtual Functions")
	afx_msg void OnSelChangeFloatingListBox();			//Message handled to monitor for LBN_SELCHANGE messages.
	long OnCustomDestroy(UINT nMsg, long l);			//Handled to monitor special destruction requests made by grid.
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


#endif  //__EDITGCO_H__
