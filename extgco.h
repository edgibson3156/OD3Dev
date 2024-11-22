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
//extgco.h   -    Precompiled headers for GridWiz
#ifndef __EXTGCO_H__
#define __EXTGCO_H__ 

#pragma warning(disable : 4100)

#ifdef _WIN32
#include <afxtempl.h>
#endif

#define REGISTER_EXTENDED_GCOS() \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWLetteredHeaderCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWNumberedHeaderCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWSpinBtnCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWIntCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWFloatCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWDateTimeCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWSpinBtnCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWDialogPromptCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWDropDownGrid)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWProgressCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWTrackBarCell)); \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWModBtnCell)); 
			



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
	#ifdef _GWEXTGCOIMP
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

class GW_EXT_CLASS CGWLetteredHeaderCell: public CGWHeaderCell
{
//GW_CLASS{{(CGWLetteredHeaderCell)
/*

The CGWLetteredHeaderCell derives from CGWHeaderCell and is typically used for cells which are located 
in fixed rows. These are commonly referred to as column headers. The added functionality provided by this 
class is to order the cells alphabetically starting at a through z, then aa, ab through az and so on.

You can use this class as-is or derive a new class from it using the GridWiz Wizard. 

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
	DECLARE_DYNCREATE(CGWLetteredHeaderCell)
public:
//GW_MEMBERS{{(CGWLetteredHeaderCell,"Construction")
	CGWLetteredHeaderCell()				//Default constructor.
		{Initialize();};
//}}GW_MEMBERS

	
//GW_MEMBERS{{(CGWLetteredHeaderCell, "Overriden Virtual Functions")
	virtual void Initialize();				//Overidden to specify initial cell properties.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);  //Overidden to control how the cell is drawn.
//}}GW_MEMBERS

};

class GW_EXT_CLASS CGWNumberedHeaderCell: public CGWHeaderCell
{
//GW_CLASS{{(CGWNumberedHeaderCell)
/*

The CGWNumberedHeaderCell derives from CGWHeaderCell and is typically used for cells which are located 
in fixed rows. These are commonly referred to as column headers. The added functionality provided by this 
class is to number the cells based on their row index.

You can use this class as-is or derive a new class from it using the GridWiz Wizard. 

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
	DECLARE_DYNCREATE(CGWNumberedHeaderCell)
public:
//GW_MEMBERS{{(CGWNumberedHeaderCell,"Construction")
	CGWNumberedHeaderCell() 		//Default constructor.
		{Initialize();}
//}}GW_MEMBERS
	
//GW_MEMBERS{{(CGWNumberedHeaderCell, "Overriden Virtual Functions")
	virtual void Initialize();				//Overidden to specify initial cell properties.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to control how the cell is drawn.
//}}GW_MEMBERS
};


class GW_EXT_CLASS CGWNumEditCell : public CGWEditCell
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CGWNumEditCell)

public:
//Construction
//GW_MEMBERS{{(CGWNumEditCell,"Construction")
	CGWNumEditCell();			//Default constructor.
	~CGWNumEditCell();			//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWNumEditCell,"Data Members")
	CString m_csBuffer;			//Buffer which holds the contents of the control as its being editted.
//}}GW_MEMBERS

// Operations
public:

//GW_MEMBERS{{(CGWNumEditCell, "Overriden Virtual Functions")
	virtual void CreateFloatingCtrl(CWnd* pParent);								//Overidden to create a specific CEdit based windows control.
	virtual BOOL ValidateData(CString& csFormatedText, CWnd* pFloatingCtrl);	//Overidden to perform specific numeric validations.
//}}GW_MEMBERS

public:
	inline void GW_NUMFORMAT(_TCHAR* lpszNumericFormat) 	    {SetFormat(CString(lpszNumericFormat));}
};

class GW_EXT_CLASS CGWIntCell : public CGWNumEditCell
{
//GW_CLASS{{(CGWIntCell)
/*

The CGWIntCell is a derivative of CGWEditCell. Its purpose is to add numeric integer formating and 
validation. The cells based on CGWIntCell will not allow non-numeric data, and can be set up to
accept values in only certain ranges. Numeric and currency formating can be applied as well.

You can use this class as-is or derive a new class from it using the GridWiz Wizard. 

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
protected:
	DECLARE_DYNCREATE(CGWIntCell)

public:
//GW_MEMBERS{{(CGWIntCell,"Construction")
	CGWIntCell();				//Default constructor.
	~CGWIntCell();				//Destructor.
//}}GW_MEMBERS

	
//GW_MEMBERS{{(CGWIntCell, "Overriden Virtual Functions")
	virtual void Initialize();													//Overidden to specify initial cell properties.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);						//Overidden to format freshly entered data prior to validation.
	virtual BOOL ValidateData(CString& csFormatedText, CWnd* pFloatingCtrl);	//Overidden to validate the contents of the edit box before the data is committed via OnSetCellText.
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);			//Overidden to apply any formating characters to the contents of the cell.
//}}GW_MEMBERS

//inline properties sets
protected:
//GW_MEMBERS{{(CGWIntCell, "Inline Property Sets")
	inline void GW_MINIMUMLONG(long nMinimum)		//Sets the design-time minimum value.
			{SetMinimum(nMinimum, FALSE);}
	inline void GW_MAXIMUMLONG(long nMaximum)		//Sets the design-time maximum value.
			{SetMaximum(nMaximum, FALSE);}
//}}GW_MEMBERS
};


class GW_EXT_CLASS CGWFloatCell : public CGWNumEditCell
{
//GW_CLASS{{(CGWFloatCell)
/*

The CGWFloatCell is a derivative of CGWEditCell. Its purpose is to add floating point numeric formating and 
validation. The cells based on CGWFloatCell will not allow non-numeric data, and can be set up to
accept values in only certain ranges. Numeric and currency formating can be applied as well.

You can use this class as-is or derive a new class from it using the GridWiz Wizard. 

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
protected:
	DECLARE_DYNCREATE(CGWFloatCell)

public:
//GW_MEMBERS{{(CGWFloatCell,"Construction")
	CGWFloatCell();			//Default constructor.
	~CGWFloatCell();		//Destructor.
//}}GW_OVERRIDES

	
	
//GW_MEMBERS{{(CGWFloatCell, "Overriden Virtual Functions")
	virtual void Initialize();													//Overidden to specify initial cell properties.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);						//Overidden to format freshly entered data prior to validation.
	virtual BOOL ValidateData(CString& csFormatedText, CWnd* pFloatingCtrl);	//Overidden to validate the contents of the edit box before the data is committed via OnSetCellText.
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);			//Overidden to apply any formating characters to the contents of the cell.
//}}GW_MEMBERS


//inline properties sets
protected:
//GW_MEMBERS{{(CGWFloatCell, "Inline Property Sets")
	inline void GW_MINIMUMFLOAT(double nMinimum)       //Sets the design-time minimum value.
			{SetMinimum(nMinimum, FALSE);}
	inline void GW_MAXIMUMFLOAT(double nMaximum)       //Sets the design-time maximum value.
			{SetMaximum(nMaximum, FALSE);}
//}}GW_MEMBERS

};


/////////////////////////////////////////////////////////////////////////////////
class GW_EXT_CLASS CGWDateTimeCell : public CGWEditCell
{
//GW_CLASS{{(CGWDateTimeCell)
/*

The CGWDateTimeCell is a derivative of CGWEditCell. Its purpose is to add date and time formating and 
validation. The cells based on CGWDateTimeCell will not allow non-numeric data, and can be set up to
accept values in only certain ranges. Several different formating options can be applied as well.

You can use this class as-is or derive a new class from it using the GridWiz Wizard. 

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
protected:
	DECLARE_DYNCREATE(CGWDateTimeCell)

public:
//GW_MEMBERS{{(CGWDateTimeCell,"Construction")
	CGWDateTimeCell();			//Default constructor.
	~CGWDateTimeCell();			//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWDateTimeCell, "Overriden Virtual Functions")
	virtual void Initialize();													//Overidden to specify initial cell properties.
	virtual void SetFormat(CString csFormat);									//Overidden to apply the format string to the date.
	virtual void CreateFloatingCtrl(CWnd* pParent);								//Overidden to create a special CEdit based windows control for this cell.
	virtual CString ApplyInputMask(CString csCellText);							//Overidden to apply a date input mask prior to editing the data.
	virtual BOOL CheckInputChar(TCHAR& ch, int& nSel);							//Overidden to check enetred data against the input mask.
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);			//Overidden to apply any formating characters to the contents of the cell.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);						//Overidden to format freshly entered data prior to validation.
	virtual BOOL ValidateData(CString& csFormatedText, CWnd* pFloatingCtrl);	//Overidden to validate the contents of the edit box before the data is committed via OnSetCellText.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);			//Overidden to control the hiding and showing of the special CEdit based windows control. 
//}}GW_MEMBERS

//inline properties sets
protected:
//GW_MEMBERS{{(CGWDateTimeCell, "Inline Property Sets")
	inline void GW_NUMFORMAT(_TCHAR* lpszNumericFormat) 	   //Sets the design-time date/time format.
			{SetFormat(CString(lpszNumericFormat));}
//}}GW_MEMBERS

};
/////////////////////////////////////////////////////////////////////////////


class GW_EXT_CLASS CGWSpinBtnCell: public CGWIntCell
{
//GW_CLASS{{(CGWSpinBtnCell)
/*

The CGWSpinBtnCell is a derivative of CGWIntCell. Its purpose is to add spin button capability. The 
cells based on CGWSpinBtnCell will not allow non-numeric data, and can be set up to
accept values in only certain ranges. Several different formating options can be applied as well.

You can use this class as-is or derive a new class from it using the GridWiz Wizard. 

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//Construction
public:
	DECLARE_DYNCREATE(CGWSpinBtnCell)

public:
//GW_MEMBERS{{(CGWSpinBtnCell,"Construction")
	CGWSpinBtnCell();				//Default constructor
	virtual ~CGWSpinBtnCell();		//Destructor.
//}}GW_MEMBERS

//Operations
//GW_MEMBERS{{(CGWSpinBtnCell,"Operations")
	CRect GetSpinBtnRect();			//Calculate and return the coordinates for the spin button.
//}}GW_MEMBERS


// Overrides
public:
//GW_MEMBERS{{(CGWSpinBtnCell, "Overriden Virtual Functions")
	virtual void OnCreate();											//Overidden to specify additional creation criteria.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to control how the cell is drawn.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);	//Overidden to control the hiding and showing of the special CEdit based windows control. 
	virtual CRect GetControlPosition();									//Overidden to calculate and return the screen location of edit box.
	virtual void GCOOnLButtonDown(UINT nFlags, CPoint point);			//Overidden to accept notification of the WM_LBUTTONDOWN message.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONUP message.
	virtual void GCOOnLButtonDblClk(UINT nFlags, CPoint point);			//Overidden to accept notification of the WM_LBUTTONDBLCLK message.
	virtual void GCOLostFocus();										//Overidden to accept notification of the WM_KILLFOCUS message.
    virtual void GCODoSetCursor(UINT nFlags, CPoint& point);			//Overidden to accept notification of the WM_SETFOCUS message.
//}}GW_MEMBERS

};

class GW_EXT_CLASS CGWDialogPromptCell: public CGWButtonCell
{
//GW_CLASS{{(CGWDialogPromptCell)
/*

The CGWDialogPromptCell derives from CGWButtonCell and manages a push button on the right side of the cell. 
The click events for the button are handled and passed on to CGWGrid virtual functions. The 
CGWGrid::OnCellNotify() function is passed the row and column coordinates along with either BN_CLICKED 
or BN_DBLCLICK identifiers. These click events are intended to provide a processing point for you to 
show a dialog.

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

//Construction
public:
//GW_MEMBERS{{(CGWDialogPromptCell,"Construction")
	CGWDialogPromptCell();				//Default constructor
	virtual ~CGWDialogPromptCell();		//Destructor.
//}}GW_MEMBERS

	DECLARE_DYNCREATE(CGWDialogPromptCell)

//Operations
public:
//GW_MEMBERS{{(CGWDialogPromptCell,"Operations")
	virtual CRect GetButtonRect();		//Overidden to calculate and return the coordinates for the button.
//}}GW_MEMBERS

// Overrides
public:
//GW_MEMBERS{{(CGWDialogPromptCell, "Overriden Virtual Functions")
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);		//Overidden to control the hiding and showing of the special CEdit based windows control. 
	virtual void UpdateControlPosition();									//Overidden to move the combobox control the correct location in the cell.
	virtual void GCOOnFloatingButtonClick()									//Overidden to accept notification of the BN_CLICKED message.
											{
												m_pGrid->SetControlCell(this);
												CPoint pt;
												GetCursorPos(&pt);
												m_pGrid->GetGridCWnd()->ScreenToClient(&pt);
												GCOOnLButtonDown(0, pt);
												GCOOnLButtonUp(0, pt);
												if (m_pFloatingCtrl)
													m_pFloatingCtrl->RedrawWindow();
												m_pGrid->OnCellNotify(m_nRowNdx, m_nColNdx, this, BN_CLICKED);
											}
	virtual void GCOSetFocus()												//Overidden to accept notification of the WM_SETFOCUS message.
								{if (!m_pFloatingButton && GetEditFlag() == EDIT_ON_SETFOCUS) 
									{
										MoveFloatingCtrl(TRUE);
										m_pGrid->GetFocusCell() = this;
									}
								};

	virtual void GCOLostFocus()												//Overidden to accept notification of the WM_KILLFOCUS message.
								{if (m_pFloatingButton && GetEditFlag() != EDIT_ALWAYS) 
									MoveFloatingCtrl(FALSE);
								 m_pGrid->GetFocusCell() = NULL;}
//}}GW_MEMBERS
};

/////////////////////////////////////////////////////////////////////////////
class GW_EXT_CLASS CGWNumEdit : public CGWGridEdit
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
//Operations
public:
//GW_MEMBERS{{(CGWNumEdit,"Operations")
	BOOL ValidNumChar(UINT nChar);								//Test for valid characters for this cell.
//}}GW_MEMBERS

//Message Handlers
public:
//GW_MEMBERS{{(CGWNumEdit,"Message Handlers")
	 void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Overidden to monitor keystrokes into the cell.
//}}GW_MEMBERS

	DECLARE_MESSAGE_MAP()
};

class GW_EXT_CLASS CGWDateTimeEdit : public CGWGridEdit
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
//Operations
public:
//GW_MEMBERS{{(CGWDateTimeEdit,"Operations")
	BOOL ValidDateChar(UINT nChar);								//Test for valid characters for this cell.
//}}GW_MEMBERS

//Message Handlers
public:
//GW_MEMBERS{{(CGWNumEdit,"Message Handlers")
	 void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		//Overidden to monitor keystrokes into the cell.
//}}GW_MEMBERS

	DECLARE_MESSAGE_MAP()
};

class CGWGridPopup;
class GW_EXT_CLASS CGWDropDownGrid : public CGWEditCell
{

//GW_CLASS{{(CGWDropDownGrid)
/*

The CGWComboBoxCell class derives directly from CGWEditCell and is modeled after the CGWComboboxCell.
Instead of showing a list when the drop button is pushed, this cell pops up a grid.The combobox control 
is created and displayed over the cell giving the impression that the cell is editable. When the user exists 
the cell after editing, the contents of the combobox is read and passed on to the grid via the OnSetCellText() 
virtual function. Additionally, the CBN_SELCHANGE notification is trapped and the CGWGrid virtual function 
OnCellSelChange is called with information on the selection being made. The popup grid is created automatically
and can be formated with a settings file. You may also create your own popup grid and use it by overriding
the CGWGrid virtual function OnGetCellDropDownGrid.

The combobox is usually created when the user clicks the cell, but can be created at other times based on the 
setting of the Edit Event property. The function responsible for this is called MoveFloatingCtrl(). MoveFloatingCtrl 
actually handles both showing the combobox and removal. When called with a value of TRUE, the function calls another virtual 
function called CreateFloatingCtrl. This function actually creates the Window to be displayed. When called 
with a value of FALSE, MoveFloatingCtrl validates the contents of the combobox by calling the CGWGrid virtual 
function OnCellValidateData and provided there were no errors, calls the CGWGrid virtual function called 
OnSetCellText to pass the data onto the grid for storage. 

There are two ways to populate the grid portion of the combobox. The first method invloves overriding the 
CGWGrid virtual function OnGetCellValidString(). This function is called repeatedly just prior to the drop being
displayed. The function returns a boolean value which when set to FALSE stops the loop. Otherwise, the GCO keeps
calling OnGetCellValidString to add new entries to the drop list. The second method uses the CGWValidStringObject
class to build a list of strings. The CGWValidStringsObject name is then associated a range of cells. When the
cell is created, the address of the CGWValidStringsObject is provided to the cell. 

The CGWDropDownGrid differs from the CGWDropDownListCell in that the elements of the combobox are created 
separately and the drop list can be multi-column. This allows for multi-selection drop lists and a better 
overall grid user-interface. Otherwise, both classes operate essentially the same.
	

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

protected: // create from serialization only
	DECLARE_DYNCREATE(CGWDropDownGrid)
public:
//GW_MEMBERS{{(CGWDropDownGrid,"Construction")
	CGWDropDownGrid();			//Default constructor
	~CGWDropDownGrid();			//Destructor.
//}}GW_MEMBERS


//Data Members
public:
//GW_MEMBERS{{(CGWDropDownGrid,"Data Members")
	CGWGridPopup*	m_pPopupGrid;				// Address of the GridWiz popup Grid Object used for the drop down list.
	BOOL 			m_bSnapUp;					// Determines whether the control is in the state of closing the drop list.
    int 			m_nCurrentSelection;		// Identifes the row index of the selected item in the grid.
	int				m_nNumItems;				// Identifes the number of rows to be visible in the grid. Controls the size of the drop list window.
	BOOL			m_bSendExtraData;			// Determines whether strings or keys will be passed between the owner grid and this grid cell object.
	CStringArray 	m_Strings;					// Array which holds the strings to be displayed in the drop list.
	CPtrArray    	m_Ptrs;						// Array of pointers which are associated with the strings.
	BOOL            m_bDirty;					// Determines whether the data in the edit portion of the GCO has been changed. 
    CUIntArray 		m_arraySelections;			// Array used to store multiple selections.
	int				m_nDisplayColumn;			// Column index which is displayed in grid cell. Specify -1 for tabbed string. Defaults to 0;
	int				m_nExtraDataField;			// Field index of the extra data item which is part of a VSO based on SQL result set. Defaults to last field.
//}}GW_MEMBERS
	
//CGWGridcellObject 
public:                         
//GW_MEMBERS{{(CGWDropDownGrid, "Overriden Virtual Functions")
	virtual void CurrentCellState();			//Overidden to reset the editing state of the control.
	virtual void OnCreate();					//Overidden to specify additional creation criteria.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to control how the cell is drawn.
	virtual void GCOOnLButtonDown(UINT nFlags, CPoint point);			//Overidden to accept notification of the WM_LBUTTONDOWN message.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_LBUTTONUP message.
	virtual void GCOLostFocus();										//Overidden to accept notification of the WM_KILLFOCUS message.
    virtual void GCODoSetCursor(UINT nFlags, CPoint& point);			//Overidden to accept notification of the WM_SETFOCUS message.
	virtual void GCOOnInitializeCtrl();									//Overidden to perform special initialization on this cell type.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);	//Overidden to control the hiding and showing of the special CEdit based windows control. 
	virtual void CreateFloatingCtrl(CWnd* pParent);						//Overidden to create a special CEdit based windows control for this cell.
	virtual void DestroyControl();										//Overidden to destroy additional elements of the cell.
	virtual void GCOOnMouseMove(UINT nFlags, CPoint point);				//Overidden to accept notification of the WM_MOUSEMOVE message.
	virtual void GCOOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Overidden to accept notification of the WM_KEYDOWN message.
    virtual void  GCOOnSelChange();										//Overidden to accept notification of the LBN_SELCHANGE message.
	virtual void AddStrings();											//Calls grid virtual functions to add strings to the string collection.
	virtual void SelectStrings(CString csCellText);						//Called to select the strings from the current value.
	virtual void Initialize();											//Overidden to specify initial cell properties.
	virtual void FormatCellText(CString& csCellText, CDC* pDC = NULL);	//Overidden to apply any formating characters to the contents of the cell.
	virtual CString FormatEnterData(CWnd* pFloatingCtrl);				//Overidden to format freshly entered data prior to validation.
//}}GW_MEMBERS


//Operations
public:
//GW_MEMBERS{{(CGWDropDownGrid,"Operations")
	CRect GetBtnRect();									//Calculates the rectangle for the button which launches the popup grid.
	virtual void  SetNumItems(int nNumItems)			//Sets the numbers of rows to be visible in the drop down grid. Controls the size of the grid.
		{m_nNumItems = nNumItems;}
	virtual int   AddString(const _TCHAR* lpszStr);		//Adds strings to collection of strings which will be displayed by the grid.
	virtual void  ResetContent();						//Removes all of the strings and associated pointers from the string list.
	virtual void  InsertString(int nIndex, CString& str);	//Inserts a string into the array of strings.
	virtual void  DeleteString(int nIndex);					//Removes a string from the array of strings.
	virtual void* GetItemDataPtr(int nIndex);				//Retrieves a pointer associated with a particular string.
	virtual void  SetItemDataPtr(int nIndex, void* ptr);	//Associates a pointer value with a string.
	virtual void  ShowGrid(BOOL bShow);						//Show or hide the grid portion of the cell. 
	virtual CRect GetControlPosition();						//Overidden to calculate and return the screen location of edit box.
	void SetCurSel(int nCurSel)								//Sets the currently selected item.
			{m_nCurrentSelection = nCurSel;}
	int GetCurSel()											//Retrieves the index of the currently selected item.
			{return m_nCurrentSelection;}
//}}GW_MEMBERS

};


class GW_EXT_CLASS CGWModEdit : public CGWGridEdit
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWModEdit,"Operations")
	BOOL ValidNumChar(UINT nChar);		//Test for valid characters for this cell.
//}}GW_MEMBERS
	
	DECLARE_MESSAGE_MAP()
//GW_MEMBERS{{(CGWModEdit, "Overriden Virtual Functions")
	 afx_msg void OnKillFocus(CWnd* pWnd);	//Message handled to trigger commitment mechanism for cell data.
//}}GW_MEMBERS
	
};

class CGWGridBitmapButton;
class GW_EXT_CLASS CGWModBtnCell : public CGWEditCell
{
//GW_CLASS{{(CGWModBtnCell)
/*

The CGWModBtnCell derives from CGWEditCell and manages a two push buttons on the right side of the cell. 
The first button is the "Accept" button and the second the "Reject". Clicking the Accept button will cause
contents of the edit portion of the cell to be processed and sent to the grid via CGWGrid::OnSetCellText(). 
Clicking the Reject button will cause the contents to be removed and a empty string will be passed to 
the grid via OnSetCellText.

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

protected: 
	DECLARE_DYNCREATE(CGWModBtnCell)
public:

//GW_MEMBERS{{(CGWModBtnCell,"Construction")
	CGWModBtnCell();		//Default constructor
	~CGWModBtnCell();		//Destructor.
//}}GW_MEMBERS

// Attributes
public:
//GW_MEMBERS{{(CGWModBtnCell,"Data Members")
	CGWGridBitmapButton* m_pFloatingAcceptBtn;			//Pointer to the accept bitmap button.
	CGWGridBitmapButton* m_pFloatingDeleteBtn;			//Pointer to the reject bitmap button.
//}}GW_MEMBERS

// Operations
public:

// Implementation
//GW_MEMBERS{{(CGWModBtnCell,"Implemenation")
	virtual void OnAccept();							//Called when the Accept button is clicked.
	virtual void OnReject();							//Called when the reject button is clicked.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWModBtnCell,"Overriden Virtual Functions")
	virtual void Initialize();							//Overidden to specify initial cell properties.
	virtual CRect GetControlPosition();					//Overidden to calculate and return the screen location of edit control.
	virtual void CreateFloatingCtrl(CWnd* pParent);		//Overidden to create a special bitmap button controls and edit box for this cell.
	virtual void DestroyControl();						//Overidden to destroy additional elements of the cell.
	virtual void GCOOnInitializeCtrl();					//Overidden to perform special initialization on this cell type.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);	//Overidden to control the hiding and showing of the buttons and the edit box. 
	virtual void SetRect(LPRECT lpRect);				//Overidden to set the editing rectangle within the control.
	virtual void UpdateControlPosition();				//Overidden to move the edit control the correct location in the cell.
//}}GW_MEMBERS
};

class GW_EXT_CLASS CGWGridBitmapButton : public CBitmapButton
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWGridBitmapButton, "Overriden Virtual Functions")
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	//Message handled to monitor mouse clicks.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	//Message handled to monitor mouse clicks.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	//Message handled to monitor mouse movement.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Message handled to monitor keystrokes into cells.
	afx_msg void OnKillFocus(CWnd* pWnd);			//Message handled to trigger commitment mechanism for cell data.
	afx_msg void OnDestroy();						//Message handled to destroy the control.
	afx_msg UINT OnGetDlgCode();					//Handled so that all keys are sent to the control when the grid is in a dialog box.
	long OnCustomDestroy(UINT nMsg, long l);		//Handled to monitor special destruction requests made by grid.
//}}GW_MEMBERS
	
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
class CGWOverFlowCell : public CGWEditCell
{
protected: // create from serialization only
	CGWOverFlowCell();
	DECLARE_DYNCREATE(CGWOverFlowCell)
	~CGWOverFlowCell();
    
    static CString 	m_csLastCellString;
    static CRect    m_rectLastStringRect;
    static int      m_nLastRow;
// Attributes
public:

// Operations
public:

// Implementation
	virtual void Initialize();

//BEGIN_VIRTUAL_FUNCTIONS(CGWOverFlowCell)
	virtual void PrepareCell(CDC* pDC, CRect& DrawRect);
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);
	virtual CRect GetControlPosition();
//END_VIRTUAL_FUNCTIONS
};


#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS


#endif                          

/////////////////////////////////////////////////////////////////////////////
// E:\GWiz35\INCLUDE\cmbogrid.h : interface of the CGWCellPopupGrid class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __CGWCellPopupGrid_H__
#define __CGWCellPopupGrid_H__

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

class GW_EXT_CLASS CGWCellPopupGrid : public CGWGridPopup
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public: 
//GW_MEMBERS{{(CGWCellPopupGrid,"Construction")
	CGWCellPopupGrid();					//Constructs the popup grid object.
	virtual ~CGWCellPopupGrid();		//Destructor.
//}}GW_MEMBERS

	DECLARE_DYNCREATE(CGWCellPopupGrid)
	DECLARE_GRIDCELL_MAP(CGWCellPopupGrid)

// Attributes
public:
//GW_MEMBERS{{(CGWCellPopupGrid,"Data Members")
	CGWDropDownGrid* m_pGCO;			//The GCO to which this grid popup belongs to.
//}}GW_MEMBERS

// Operations
public:
//GW_MEMBERS{{(CGWCellPopupGrid,"Operations")
	void Initialize();					//Initialize the control with design time values.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWCellPopupGrid,"Overriden Virtual Functions")
	virtual void GridOnInitialUpdate();		//Initializes the grid before the grid is displayed.
	virtual void OnPostSelectionChange(int nRowNdx, int nColNdx);	//Virtual function event notification that the user has changed selection in the grid.
//}}GW_MEMBERS

// Generated message map functions
protected:
//GW_MEMBERS{{(CGWCellPopupGrid,"Message Handlers")
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);			//Message handler to fire events when the grid has been clicked.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Message handler used to navigate the grid by keypress.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()
};


class GW_EXT_CLASS CGWProgressCell : public CGWGridCellObject
{
//GW_CLASS{{(CGWProgressCell)
/*

The CGWProgressCell derives from CGWGridCellObject and draws a progress meter in the cell based on the 
current value in relationship to the minimum and maximum values set for the cell. Use the CGWGrid 
SetMinimumValue() and SetMaximumValue() to specify the range. You will need to invalidate the cell in order
to reflect changes in the cells value. For example, if you set the cells value programmatically using the 
CGWGrid SetCellText() function, you will then need to call InvalidateCell() in order for the progress 
meter to be updated.

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	
public: 
//GW_MEMBERS{{(CGWProgressCell,"Construction")
	CGWProgressCell();			//Default Constructor.
	~CGWProgressCell();			//Defualt Destructor.
//}}GW_MEMBERS

	DECLARE_DYNCREATE(CGWProgressCell)

// Attributes
public:
//GW_MEMBERS{{(CGWProgressCell,"Data Members")
	int m_nMin;					//The minimum value. 
	int m_nMax;					//The maximum value.	
	COLORREF m_rgbBarColor;		//The color used to for displaying the progress bar.
//}}GW_MEMBERS

// Operations
public:
//GW_MEMBERS{{(CGWProgressCell,"Operations")
	void Initialize();			//Initialize the control with design time values.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWProgressCell,"Overriden Virtual Functions")
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overriden to take over the drawing for this cell.
	virtual void PrepareCell(CDC* pDC, CRect& DrawRect);	//Overriden to take over the preparation and back filling for this cell.
//}}GW_MEMBERS
};

class GW_EXT_CLASS CGWTrackerButton : public CGWGridButton
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWCellPopupGrid,"Message Handlers")
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	//Message handler to detect the beginning of a dragging operation.
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	//Message handler to detect the ending of a dragging operation.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	//Message handler to monitor a dragging operation.
//}}GW_MEMBERS
	DECLARE_MESSAGE_MAP()
};


class GW_EXT_CLASS CGWTrackBarCell : public CGWGridCellObject
{
//GW_CLASS{{(CGWTrackBarCell)
/*

The CGWTrackBarCell derives from CGWGridCellObject and draws a trackbar in the cell based on the 
current value in relationship to the minimum and maximum values set for the cell. Use the CGWGrid 
SetMinimumValue() and SetMaximumValue() to specify the range. You will need to invalidate the cell in order
to reflect changes in the cells value. For example, if you set the cells value programmatically using the 
CGWGrid SetCellText() function, you will then need to call InvalidateCell() in order for the progress 
meter to be updated. As the trackbar is dragged, the value of the cell is reported to the grid through
the CGWGrid OnSetCellText() method.

To use this GCO, you need to define the constant USE_EXTENDED_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_EXTENDED_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	
public: 
//GW_MEMBERS{{(CGWTrackBarCell,"Construction")
	CGWTrackBarCell();			//Default Constructor.
	~CGWTrackBarCell();			//Defualt Destructor.
//}}GW_MEMBERS

	DECLARE_DYNCREATE(CGWTrackBarCell)


// Attributes
public:
//GW_MEMBERS{{(CGWTrackBarCell,"Data Members")
	int m_nStep;				//The scale to which increments are measured.
	int m_nMin;					//The minimum value.
	int m_nMax;					//The maximum value.
	CGWGridButton* m_pFloatingButton;	//The address of the floating button which the user will drag.
//}}GW_MEMBERS

// Operations
public:
//GW_MEMBERS{{(CGWTrackBarCell,"Operations")
	void SetPos(int nPos);		//Programmatically set the position of the drag button.
	virtual void Initialize();	//Initialize the cell with the design time values.
	CRect GetSliderRect();		//Retrieves the ractangle maintained by the slider button.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWTrackBarCell,"Overriden Virtual Functions")
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overriden to take over the draw for this cell.
	virtual void PrepareCell(CDC* pDC, CRect& DrawRect);	//Overriden to take over the back filling of this cell.
	virtual void GCODoSetCursor(UINT nFlags, CPoint& point);	//Overriden to control the cursor shape during mouse movement.
	virtual void GCOOnMouseMove(UINT nFlags, CPoint point);		//Overriden to trap mouse movement for this cell.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);	//Overriden to control how and when this cell is activated.
	virtual void GCOOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	//Overriden to trap keyboard input into this cell.
	virtual void GCOOnLButtonDown(UINT nFlags, CPoint point);			//Overriden to trap mouse activity for this cell.
	virtual void GCOOnLButtonUp(UINT nFlags, CPoint point);				//Overriden to trap mouse activity for this cell.
	virtual void CreateFloatingCtrl(CWnd* pParent);		//Overriden to create the button which is used to move the slider.
//}}GW_MEMBERS
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS


#endif  //__EXTGCO_H__
