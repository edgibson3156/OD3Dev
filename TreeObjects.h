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
// GridObjects.h : header file
//
//These are the objects which are manipulated through Dispatch 
//interfaces. These objects then interact with the Grid OCX;

#ifndef __TREEOBJECTS_H__
#define __TREEOBJECTS_H__
/////////////////////////////////////////////////////////////////////////////
// CGWSheet command target
#include "gridobjects.h"
class CGWTreeSheet : public CGWSheet
{
	friend class CGWRange;
	friend class CGWRow;
	friend class CGWColumn;
	friend class CGWCell;

	DECLARE_DYNCREATE(CGWTreeSheet)

	CGWTreeSheet();           // protected constructor used by dynamic creation
	CGWTreeSheet(CGWGrid* pGrid, short nSheetNdx);
// Operations
public:
// Implementation
protected:
	virtual ~CGWTreeSheet();

	// Generated message map functions
	//{{AFX_MSG(CGWTreeSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGWTreeSheet)
	afx_msg OLE_HANDLE GetNode(long nRowNdx);
	afx_msg OLE_HANDLE GetParent(OLE_HANDLE NodeHandle);
	afx_msg long GetNodeRow(OLE_HANDLE NodeHandle);
	afx_msg long GetParentRow(OLE_HANDLE NodeHandle);
	afx_msg OLE_HANDLE GetNextSibling(OLE_HANDLE NodeHandle);
	afx_msg BOOL HasChildren(OLE_HANDLE NodeHandle);
	afx_msg BOOL CanPromote(OLE_HANDLE NodeHandle);
	afx_msg BOOL CanDemote(OLE_HANDLE NodeHandle);
	afx_msg OLE_HANDLE GetNextVisibleItem(OLE_HANDLE NodeHandle);
	afx_msg OLE_HANDLE GetNextItem(OLE_HANDLE NodeHandle);
	afx_msg short GetLevel(OLE_HANDLE NodeHandle);
	afx_msg OLE_HANDLE GetPreviousItem(OLE_HANDLE NodeHandle);
	afx_msg long GetVisibleItemCount();
	afx_msg OLE_HANDLE InsertNode(OLE_HANDLE ParentNodeHandle, OLE_HANDLE InsertAfterNodeHandle);
	afx_msg OLE_HANDLE AddNode();
	afx_msg BOOL IsChildOf(OLE_HANDLE NodeHandle, OLE_HANDLE TestParentNodeHandle);
	afx_msg BSTR GetNodeText(OLE_HANDLE NodeHandle, long nColNdx);
	afx_msg void SetNodeText(OLE_HANDLE NodeHandle, long nColNdx, LPCTSTR csCellText);
	afx_msg void Promote(OLE_HANDLE NodeHandle);
	afx_msg void Demote(OLE_HANDLE NodeHandle);
	afx_msg void Expand(OLE_HANDLE NodeHandle);
	afx_msg void Collapse(OLE_HANDLE NodeHandle);
	afx_msg void Toggle(OLE_HANDLE NodeHandle);
	afx_msg void PromoteRow(long nRowNdx);
	afx_msg void DemoteRow(long nRowNdx);
	afx_msg void ExpandRow(long nRowNdx);
	afx_msg void CollapseRow(long nRowNdx);
	afx_msg void ToggleRow(long nRowNdx);
	afx_msg BOOL GetShowTreeLines();
	afx_msg void SetShowTreeLines(BOOL bShowTreeLines);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif