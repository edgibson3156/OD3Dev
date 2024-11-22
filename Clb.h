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
//////////////////////////////////////////////////////////////////////
// CLB ListBox class

#ifndef __CLB_H__
#define __CLB_H__

#ifndef __AFXEXT_H__
#include <afxext.h>
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


class GW_EXT_CLASS CLB : public CListBox
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	
public:
//Construction
//GW_MEMBERS{{(CLB,"Construction")
	CLB();		//Default constructor
//}}GW_MEMBERS


//GW_MEMBERS{{(CLB,"Data Members")
	BOOL m_bAlreadyDragging;		//Mode variable checked during mouse move.
	int m_currLine;					//Currently selected line.
	BOOL m_bDragMode;				//Identifies when the control is acting as a darg source.
	CLB* m_lbDragSource;			//Pointer to a drag source.
	CString m_csDragString;			//Value of the string to be dragged.
	BOOL m_bDeleteEnabled;			//Allow deletes from this listbox.
    CObArray m_coaValidTargets;		//Array of valid targets for this listybox.
//}}GW_MEMBERS

//Operations
//GW_MEMBERS{{(CLB,"Operations")
	CLB* ValidDropTarget(CPoint point);	//Check to see if mouse is over a valid drop target.
	BOOL ValidDragSource();				//Identifes this listbox as a drag source.
	void CLBClientRect(CRect* pRect);	//Retrieves the client rect.
	void CLBAddString(CString& str);	//Adds a string to the listbox.
	void RegisterDragDrop(CLB& clbTarget);	//Registers a valid Drop target.
	void EnableDelete();				//Enables deleting of rows.
//}}GW_MEMBERS
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif //__CLB_H__
