 
/////////////////////////////////////////////////////////////////////////////
// gwocxcel.h : interface of the CGWOCXCell class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __CGWOCXCell_H__
#define __CGWOCXCell_H__


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

class GW_EXT_CLASS CGWStream : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_SERIAL(CGWStream)
public:
//Construction
//GW_MEMBERS{{(CGWStream,"Construction")
	CGWStream();			//Default Constructor.
	~CGWStream();			//Default Destructor.
//}}GW_MEMBERS	

//Attributes
//GW_MEMBERS{{(CGWStream,"Data Members")
	COleStreamFile m_OleStreamFile;			//A stream object which will hold settings from the embedded ocx.
//}}GW_MEMBERS	

//Methods
//GW_MEMBERS{{(CGWStream,"Operations")
	IStream* GetStream();						//Retrieve the address of the IStream object.
	BOOL	 CreateStream();					//Create a Stream object.
	void operator=(CGWStream& otherGWStream);	//Copy one CGWStream object to another.
	virtual void Serialize(CArchive& ar);		//Store or load a CGWStream object to and from a CArchive object.
//}}GW_MEMBERS	

	//This version table helps track changes in this object. When changes are made to the 
	//schema of this object, insert version Identifier just before Current_Version_Number so that
	//Current_Version_Number is always the last entry in the table.
	enum {
				Current_Version_Number,
			  } Version_Table;
};



class GW_EXT_CLASS CGWOCXCell : public CGWEditCell
{
//GW_CLASS{{(CGWOCXCell)
/*

The CGWOCXCell class derives from CGWEditCell and adds editing functionality through
a ActiveX control. The ActiveX control is created and displayed over the cell giving the impression
that the cell is editable. When the user exists the cell after editing, the contents of the ActiveX 
is read using the Text property and passed on to the grid via the OnSetCellText() virtual function. 
The ActiveX is usually created when the user clicks the cell, but can be created at other times based on the 
setting of the Edit Event property. The function responsible for this is called MoveFloatingCtrl(). 
MoveFloatingCtrl actually handles both showing the edit box and removal. When called with a value of TRUE, 
the function calls another virtual function called CreateFloatingCtrl. This function actually creates the ActiveX 
to be displayed. When called with a value of FALSE, MoveFloatingCtrl validates the contents of the ActiveX by 
calling the CGWGrid virtual function OnCellValidateData and provided there were no errors, calls the 
CGWGrid virtual function called OnSetCellText to pass the data onto the grid for storage. 

The CreateFloatingCtrl() function uses the OCXClassName property of the cell to determine the ActiveX to 
create. There are several CGWGrid virtual functions which get called along the way to provide access to 
the ActiveX Control IDispatch interface so that additional properties and methods can be accessed.

To use this GCO, you need to define the constant USE_OLE_GCOS in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
2) Invoking the REGISTER_OLE_GCOS macro in your application at least once for the targeted grid
before the GCOs will be used.
3) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	

protected: // create from serialization only
	DECLARE_DYNCREATE(CGWOCXCell)

// Construction
public:
//GW_MEMBERS{{(CGWStream,"Construction")
	CGWOCXCell();			//Default Constructor.
	~CGWOCXCell();			//Default Destructor.
//}}GW_MEMBERS	

// Operations
public:
//GW_MEMBERS{{(CGWStream,"Overriden Virtual functions")
	virtual void Initialize();													//Overriden to set design-time properties for this GCO.
	virtual void CreateFloatingCtrl(CWnd* pParent);								//Overriden to create the floating control or ocx.
	virtual void CurrentCellState();											//Overidden to reset the editing state of the control.
	virtual void DestroyControl();												//Overidden to destroy the CEdit derivative window.									
	virtual void GCOOnChar(UINT nChar, UINT nRepCnt, UINT nFlags);				//Overidden to accept notification of the WM_CHAR message.
	virtual void GCOOnInitializeCtrl();											//Overidden to perform special initialization on this cell type.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);			//Overidden to hide or show the ocx.
	virtual void SetRect(LPRECT lpRect);										//Overidden to set the editing rectangle within the control.
	virtual BOOL ValidateData(CString& csFormatedText, CWnd* pFloatingCtrl);	//Overidden to validate the contents of the edit box before the data is committed via OnSetCellText.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overidden to perform specific drawing for this cell.
	virtual LPDISPATCH GetGCODispatch();										//Overidden to retrieve the address IDispatch for the OCX embedded in this cell.
//}}GW_MEMBERS	

	LPCLSID GetPropPageIDs(ULONG& cPropPages);									//Get the class ID of the property pages for the ocx embedded in this cell.
	void OnProperties();														//Dispaly the property page for the ocx embedded in this cell.
	void GetUserType(LPTSTR lpszUserType);										//Get the user readable type name for the ocx embedded in this cell.																											
	void SaveStream(CGWStream& GWStream);										//Store the property stream for the ocx in this cell into a CGWStream object.
};

#define DECLARE_GRIDWIZ_EVENT_MAP() \
	DECLARE_EVENTSINK_MAP() \
	afx_msg BOOL OnMouseDownOCX(UINT nID, short Button, short Shift, long x, long y); \
	afx_msg BOOL OnMouseMoveOCX(UINT nID, short Button, short Shift, long x, long y); \
	afx_msg BOOL OnMouseUpOCX(UINT nID, short Button, short Shift, long x, long y); \
	afx_msg BOOL OnClickOCX(UINT nID); \
	afx_msg BOOL OnDblClickOCX(UINT nID); \
	afx_msg BOOL OnKeyDownOCX(UINT nID, short KeyCode, short Shift); \
	afx_msg BOOL OnKeyPressOCX(UINT nID, short FAR* KeyAscii); \
	afx_msg BOOL OnKeyUpOCX(UINT nID, short KeyCode, short Shift); \
	BOOL OnEvent(UINT idCtrl, AFX_EVENT* pEvent, \
		AFX_CMDHANDLERINFO* pHandlerInfo); \
	afx_msg LPDISPATCH GetCellDispatch(long nRowNdx, long nColNdx); \


/////////////////////////////////////////////////////////////////////////////


#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif //#ifndef __CGWOCXCell_H__
