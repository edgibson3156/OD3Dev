/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1998 McRae Software International, Inc.
//
//	Warning:  This computer program and source code  is  protected by copyright law and
//	international treaties and is the property of McRae Software International, Inc.
//  Unauthorized use, reproduction or distribution of this program
//	or source,  will result in severe civil and criminal penalties, and will be prosecuted 
//	to the maximum extent possible under law. 
//
//  If you are unsure whether you have the right to view or use this program,
//  Contact McRae Software International, Inc.
/////////////////////////////////////////////////////////////////////////////
 
/////////////////////////////////////////////////////////////////////////////
// hiercell.h : interface of the CHierarchyCell class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __CHierarchyCell_H__
#define __CHierarchyCell_H__

#include "gwizgco.h"

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
	#ifdef _GWHIERIMP
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

#ifdef _WIN32
#include <oleauto.h>
#endif

class GW_EXT_CLASS CHierarchyCell : public CGWEditCell
{
//GW_CLASS{{(CHierarchyCell)
/*

The CHierarchyCell class derives from CGWEditCell and adds indenting functionality based on the node level
for a particular row. This identing provides visual feedback of parent-child relationships between nodes.
The underlying editbox control is created and displayed over the cell giving the impression
that the cell is editable. When the user exists the cell after editing, the contents of the editbox 
is read  and passed on to the grid via the OnSetCellText() virtual function. 
The editbox is usually created when the user clicks the cell, but can be created at other times based on the 
setting of the Edit Event property. The function responsible for this is called MoveFloatingCtrl(). 
MoveFloatingCtrl actually handles both showing the edit box and removal. When called with a value of TRUE, 
the function calls another virtual function called CreateFloatingCtrl. This function actually creates the editbox 
to be displayed. When called with a value of FALSE, MoveFloatingCtrl validates the contents of the ActiveX by 
calling the CGWGrid virtual function OnCellValidateData and provided there were no errors, calls the 
CGWGrid virtual function called OnSetCellText to pass the data onto the grid for storage. 

This cell is really only useful in grids that are based on CGWHierarchyView and CGWHierarchyCtrl. In cases
where the GridWiz Wizard was used to generate the grid class, the first column is automatically mapped to 
CHierarchyCell. The cell uses the CGWGrid virtual functions OnGetCellObject and OnSetCellObject to pass the node id 
back and forth between the GCO and the grid. The cell uses the CGWGrid function OnGetCellLong method to obtain
the node level for a particular row. The cell uses the CGWGrid::OnGetCellVariant function to retrieve additional information
such as whether to show tree lines and boxes,  whether the node has other siblings and if its a parent node. The cell uses
the CGWGrid::OnCellNotify to inform the grid that a node box has been clicked signaling that the state of a parent node
should toggle between expanded and collapsed.

To use this GCO, you need to define the constant USE_TREE_GRID in your stdafx.h file prior to including 
stdgrid.h. Also, you will need to register this GCO by one of the following methods:
1) using it in a GCO MACRO within the BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP macros.
before the GCOs will be used.
2) Pass the address of the RUNTIME_CLASS structure for this GCO to the CGWGrid::RegisterGCO function 
in your application at least once for the targeted grid before the GCOs will be used.

*/
//}}GW_CLASS	
protected: // create from serialization only
	DECLARE_DYNCREATE(CHierarchyCell)

public:
//GW_ENUMERATIONS{{(CHierarchyCell, "Variant request IDs used when this GCO calls OnGetCelLVariant() to retrieve information about the node.")
	enum nVariantRequestID
	{
		HAS_CHILDREN = 1,
		IS_EXPANDED = 2,
		HAS_ANOTHER_SIBLING = 3,	
		PARENT_ROW_INDEX = 4,		
		SHOW_LINES = 5,				
	} nVariantRequestIDs;
//}}GW_ENUMERATIONS
	
//GW_ENUMERATIONS{{(CHierarchyCell, "Cell notification ids used when this cell wants to notify the grid of specific events.")
	enum nCellNotification
	{
		NODE_CLICK = 1,
	} nCellNotifications;
//}}GW_ENUMERATIONS

//GW_MEMBERS{{(CHierarchyCell,"Construction")
	CHierarchyCell();			//Defualt Constructor.
	~CHierarchyCell();			//Defualt Destructor.
//}}GW_MEMBERS

// Attributes
//GW_MEMBERS{{(CHierarchyCell,"Data Members")
	int m_nIndent;				//Number of pixels to indent the levels.
	BOOL m_bShowLines;			//Indicator to control whether to draw dotted lines between nodes.	
	BOOL m_bShowBoxes;			//Show the expand/collapse boxes.
//}}GW_MEMBERS


//GW_MEMBERS{{(CHierarchyCell,"Operations")
	CRect GetNodeRect();		//Calculate the rectangle where the expand/collapse box will be drawn.
//}}GW_MEMBERS

//GW_MEMBERS{{(CHierarchyCell,"Overrideables")
	virtual void DrawHierarchyBoxes(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);		//Draw the expand/collapse boxes, tree lines and node bitmaps.
//}}GW_MEMBERS

//GW_MEMBERS{{(CHierarchyCell,"Overriden Virtual Functions")
	virtual void Initialize();												//Overriden to set design time properties during object creation.
	virtual void DrawGridCell(CDC* pDC, UINT nRowNdx, UINT nColNdx, CRect& DrawRect, CRect& TextRect);	//Overriden to take over the drawing of this cell.
	virtual void MoveFloatingCtrl(BOOL bShow, BOOL bSetFocus = TRUE);		//Creates and moves the floating edit control.
	virtual void GCODoSetCursor(UINT nFlags, CPoint& point);				//Identifies the cursor as the mouse drags over the cell.
	virtual void GCOOnLButtonDown(UINT nFlags, CPoint point);				//Traps LButtonDown message and hit-tests the expand/collapse boxes.
	virtual void GCOOnLButtonDblClk(UINT nFlags, CPoint point);				//Traps LButtonDblClk message and hit-tests the expand/collapse boxes.
	virtual void SetRect(LPRECT lpRect);									//Sets the editing rectangle of the floating edit control.
	virtual BOOL GetVariableExtents(CDC* pDC, CSize* pszCellSize);			//Overriden to add the indent to the size of the desired cell.
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

#endif //#ifndef __CHierarchyCell_H__
