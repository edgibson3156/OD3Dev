/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1999 McRae Software International, Inc.
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
// hierctrl.h : interface of the CGWHierarchyGridView class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __CGWHierarchyGridCtrl_H__
#define __CGWHierarchyGridCtrl_H__


#ifndef CTRL_BASE_CLASS 
#define CTRL_BASE_CLASS CGWGridCtrl
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

class GW_EXT_CLASS CGWHierarchyGridCtrl : public CTRL_BASE_CLASS
{
//GW_CLASS{{(CGWHierarchyGridCtrl)
/*

The GridWiz Tree-Grid based classes provide a hybrid user interface which combines the 
flexibility of the of the GridWiz Grid and the organization of a Tree control. The 
implementation of this specialized control is accomplished by either the CGWHierarchyGridView 
class and the CGWHierarchyGridCtrl. The CGWHierarchyGridView class can be used as a 
replacement a the CView object and CGWHierarchyGridCtrl can be used as a child control on 
dialogs, forms and property pages.
  
Implementing CGWHierarchyGridCtrl derived classes is very similar to using any 
other CWnd child window. As described earlier in the section "Implementing a CGWGridCtrl", 
there are two ways to create a these objects. The first way is to use a dialog template which 
contains a custom control as a place holder. Specify the C++ class name for the Custom Controls
window class name. Then add the REGISTER_GW_CUSTOM_CONTROL macro with the class name. The macro
registers the C++ Class name as a registered window class. When the dialog gets created,
a instance of the custom control will be created automatically. See the "Getting Started"
section of the Online help for additional details. 

The other way is to simply call the create function passing in the parent address, resource id, 
and the CRect containing the coordinates for the CGWHierarchyGridCtrl window.   

Grid Control objects behave identically to Grid View objects. The core difference is that 
a Grid Control has a GridOnInitialUpdate method instead of OnInitialUpdate. One other difference
is that Controls dont have a built-in print and print-preview feature. To print from a control,
you will need to use the GridWiz Wizard to generate a CGWReport object with a CGWGridItem. Then 
Attach the Grid Control the CGWGridRpt object in the GetGridReport function. See the 
Report sample app for additional details on reporting.

***This header file and the appropriate libraries are included into your project by adding the USE_TREE_GRID 
define-constant in your stdafx.h file prior to including stdgrid.h.


The default implementation of CGWHierarchyGridView provides a single sheet grid/outline view. To obtain a multi-sheet 
version of your grid, you will need to define CTRL_BASE_CLASS to be CGWTabGridCtrl inside your stdafx.h file
before including stdgrid.h.

The most noteworthy difference between using this grid class as opposed to CGWGridCtrl is that most of the 
data access functions, such as OnGetCellText and OnSetCellText have an additional argument which identifies the 
Node ID for the row. In fact, the concept of using row indexes for identifying rows goes away. Rows are now identified
by their node id. A cell will still have a row index, but this index will not be a vaild indication of where 
the row is in the grid. The reason for this being that simply expanding and collapsing nodes will cause row indexes to 
change. However, some CGWGrid function do rely solely on row indexes and wont work with node ids. Examples of these
are property setting routines such as SetBackColor, etc. To use these functions, you will need to convert the 
node id to the appropriate row index by calling GetNodeRow(). Conversely, some virtual functions and message handlers
report row indexes only. If you need to convert from row index to node id, call GetNode().

As was noted earlier, the implementations of the several data access functions have been changed to accomodate 
node identifiers. A collection of additional functions are available for manipulating the hierarchy of the 
outline. This includes support for indenting and outdenting rows. 


See the chapter on "Getting Started" for more information on how to use the GridWiz Wizard to build new GridWiz 
based classes. 

Also see the class documentation for CGWGridCtrl and CGWTabGridCtrl for additional implementation details.	

*/
//}}GW_CLASS	
public: 
//GW_ENUMERATIONS{{(CGWHierarchyGridCtrl, "Outline node expand and collapse codes. Passed to the Expand() function.")
	enum nExpandCode
	{
		COLLAPSE = 0,
		COLLAPSERESET = 1,
		EXPAND = 2,
		TOGGLE = 3,
	} nExpandCodes;
//}}GW_ENUMERATIONS


	DECLARE_DYNCREATE(CGWHierarchyGridCtrl)
	DECLARE_GRIDCELL_MAP(CGWHierarchyGridCtrl)
	DECLARE_GW_CUSTOM_CONTROL()

	
//GW_MEMBERS{{(CGWHierarchyGridCtrl,"Construction")
	CGWHierarchyGridCtrl();				//Default Constructor.
	virtual ~CGWHierarchyGridCtrl();	//Default Destructor.
//}}GW_MEMBERS	

// Attributes
public:

//GW_MEMBERS{{(CGWHierarchyGridCtrl,"Data Members")
	CObArray m_arrayNodeIDs;		//Array containing the node ids.
	int m_nVisibleItemCount;				//Temporary variable containing the number of potentially visible items.
//}}GW_MEMBERS	

public:
//GW_MEMBERS{{(CGWHierarchyGridCtrl,"Overriden Virtual Functions")
	virtual void Initialize();
	virtual BOOL MoveRow(int nBegRowNdx, int nEndRowNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET); //Overriden to convert from row to node.
	virtual BOOL CopyRow(int nBegRowNdx, int nEndRowNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET); //Overriden to convert from row to node.
 	virtual BOOL DeleteRow(int nRowNdx, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Overriden to convert from row to node.
	virtual void OnInsertRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);							//Overriden to convert deleted rows to nodes.	
	virtual void OnMoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Overriden to convert row index to node id.
	virtual void OnCopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Overriden to convert row index to node id.
	virtual void OnDeleteRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);				//Overriden to convert row index to node id.
	virtual void OnSelectionChange(int& nRowNdx, int& nColNdx, CRect* pRect, int nSelRectNdx);	//Overriden to convert row index to node id.
	virtual void OnSetCellText(int nRowNdx, int nColNdx, CString& csCellText);					//Overriden to convert row index to node id.
	virtual void OnGetCellLong(int nRowNdx, int nColNdx, long& nCellLong);						//Overriden to convert row index to node id.
	virtual void OnAddRow(int nCount, int nSheet = CURRENT_SHEET);						//Overriden to convert row index to node id.
	virtual void OnGetCellObject(int nRowNdx, int nColNdx, CObject*& pObject);			//Overriden to convert row index to node id.
	virtual void OnGetCellText(int nRowNdx, int nColNdx, CString& csCellText);			//Overriden to convert row index to node id.
	virtual void OnGetCellTime(int nRowNdx, int nColNdx, CGWDateTime& CellTime);		//Overriden to convert row index to node id.
	virtual void OnSetCellTime(int nRowNdx, int nColNdx, CGWDateTime& CellTime);		//Overriden to convert row index to node id.
	virtual void OnSetCellLong(int nRowNdx, int nColNdx, long& nCellLong);				//Overriden to convert row index to node id.
	virtual void OnSetCellFloat(int nRowNdx, int nColNdx, double& nCellFloat);			//Overriden to convert row index to node id.
	virtual DROPEFFECT CalculateDropEffect(DWORD dwKeyState, CPoint point);				//Overriden to disallow certain drag operations involving parent/child relationships.
	virtual void OnActivateSheet(int nSheet);											//Overriden to call RecalcHierarchy.
	virtual void AttachInternalDataSource();											//Overriden to attach to a CGWHierarchyMap.
	virtual void AttachDataSource(CGWDataSource* pGWDataSource);						//Overriden to attach to a CGWHierarchyMap.
	virtual void OnGetCellVariant(int nRowNdx, int nColNdx, VARIANT& vt, UINT vID);		//Overriden to answer specifc questions on individual nodes.
	virtual void OnCellNotify(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT nNotification);	//Overriden to notify the grid to expand or collapse a particular node.
	virtual void OnCellDblClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);		//Overriden to expand or collapse the row that was clicked.
	virtual void GridOnEditCut();						//Cut text on the clipboard by accessing data by node, instead of row.
	virtual void GridOnEditPaste();						//Paste text from the clipboard by node, instead of row.
	virtual void GridOnEditCopy();						//Copy text on the clipboard by accessing data by node, instead of row.
	virtual void GridOnInitialUpdate();					//Overriden to call RecalcHierarchy.
//}}GW_MEMBERS	


// Operations
//GW_MEMBERS{{(CGWHierarchyGridCtrl,"Operations")
	CObject* GetNode(int nRowNdx)							//Retrieve node id for a particular row index .
	{
		CObject* pNode;
		if (nRowNdx - m_nFixedRows < 0 || nRowNdx - m_nFixedRows >= m_arrayNodeIDs.GetSize())
			pNode = NULL;
		else
			pNode = m_arrayNodeIDs[nRowNdx - m_nFixedRows];
		return pNode;
	}
	int GetNodeRow(CObject* pNode)							//Retrieve arow index for a particular node id.
	{
		for (int x = 0; x < m_arrayNodeIDs.GetSize(); x++)
		{
			if (pNode == m_arrayNodeIDs[x])
				return x + m_nFixedRows;
		}
		return -1;
	}
	BOOL CanPromote(CObject* pNode);				//Checks to see whether a node can be promoted or indented.
	BOOL CanDemote(CObject* pNode);					//Checks to see whether a node can be demoted or outdented.
	void Promote(CObject* pNode);					//Promote or indent a node one level.
	void Demote(CObject* pNode);					//Demote or outdent a node one level.
	void ShowTreeLines(BOOL bShowTreeLines)			//Shows or hides tree lines
	{
		m_bShowTreeLines = bShowTreeLines;
	}
//}}GW_MEMBERS	


//GW_MEMBERS{{(CGWHierarchyGridCtrl,"Message Handlers")
	afx_msg void OnSize(UINT nType, int cx, int cy);		//Called when the user changes the size of the view or window.
	afx_msg  void OnGridEditChange(UINT nID)				//Called when the user changes the value of a cell through a edit control.
		{OnGridEditChange();}
	afx_msg void OnGridEditChange();						//Called when the user changes the value of a cell through a edit control.
	virtual void OnNodesDemote();							//Command handler for demoting a row.
	virtual void OnUpdateNodesDemote(CCmdUI* pCmdUI);		//Command UI handler for demoting a row.
	virtual void OnNodesPromote();							//Command handler for promoting a row.
	virtual void OnUpdateNodesPromote(CCmdUI* pCmdUI);		//Command UI handler for promoting a row.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWHierarchyGridCtrl, "Registered GridWiz Messages")
	long OnGetNode(WPARAM wParam, LPARAM lParam);		//Sent to retrieve a Node ID from a row. 			
//}}GW_MEMBERS	
	
	
	DECLARE_MESSAGE_MAP()

//Overrideables
public:
//GW_MEMBERS{{(CGWHierarchyGridCtrl,"Overrideables")
	virtual void RecalcHierarchy();								//Builds an array of all visible node ids.
	virtual CObject* GetNextVisibleItem(CObject* pBaseNode);	//Retrieve the next visible node id given a node id.
	virtual CObject* GetNextItem(CObject* pBaseNode);			//Get the next node id following a particular node id.
	virtual long GetLevel(CObject* pNode);						//Get the level of a particular node id.
	virtual void GetCellText(int nRowNdx, int nColNdx, CObject* pNode, CString& csCellText);	//Get the text for a cell on a particular row with a node id matching pNode.
	virtual CObject* GetPreviousItem(CObject* pBaseNode);		//Get the previous node id.
	virtual CObject* GetParent(CObject* pNode);					//Get the parent node id if any.
	virtual void SetCellText(int nRowNdx, int nColNdx, CObject* pNode, CString& csCellText);	//Set the text for a cell on a particular row with a node id matching pNode.
	virtual long GetVisibleItemCount();							//Get the number of potentially visible nodes. All nodes whose parents are expanded up to the root.
	virtual long GetItemCount();								//Get the total number of nodes.
	virtual BOOL HasChildren(CObject* pNode);					//Answers the question of whether a node is a parent node.
	virtual BOOL IsExpanded(CObject* pNode);					//Answers the question of whether a parent node is expanded.
	virtual void Expand(CObject* pNode, UINT nExpandCode);		//Causes a parent node to expand, collapse or toggle.
	virtual CObject* GetPreviousVisibleItem(CObject* pNode);	//Get the previous visible item.
	virtual CObject* InsertNode(CObject* pParentNode, CObject* pPrevNode);	//Insert a new node into the hierarchy under a particular parent before a particular node.
	virtual BOOL IsChildOf(CObject* pMoveNode, CObject* pNode, int nSheet = CURRENT_SHEET);	//Answers the questions whether a node is a child of a particular node.
	virtual CObject* GetNextSibling(CObject* pNode);			//Get the next sibling of pNode.
	virtual void MoveNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, int nInsertBefore, CObject* pInsertBeforeNode, int nSheet = CURRENT_SHEET);	//Move a node or group of nodes and insert before a particular node.
	virtual void CopyNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, int nInsertBefore, CObject* pInsertBeforeNode, int nSheet = CURRENT_SHEET);	//Copy a node or group of nodes and insert before a particular node.
	virtual void DeleteNode(int nRowNdx, CObject* pNode, int nSheet = CURRENT_SHEET);	//Delete a particular from the hierarchy.
	virtual void CopyNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, CString& csClipText, int nSheet = CURRENT_SHEET);	//Copy a group of nodes and place the text in a buffer.
	virtual void CutNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, CString& csClipText, int nSheet = CURRENT_SHEET);	//Cut a group of nodes and place the text in a buffer.
	virtual void PasteNode(int nBegRowNdx, CObject* pNode, CString& csClipText, int nSheet = CURRENT_SHEET);										//Paste a text buffer beginning at a particular node location.
	virtual CObject* AddNode(int nSheet);															//Append a node to hierarchy.
	virtual void GetCellTime(int nRowNdx, int nColNdx, CObject* pNode, CGWDateTime& CellTime);		//Gets the cell date/time value for a particular node.
	virtual void SetCellTime(int nRowNdx, int nColNdx, CObject* pNode, CGWDateTime& CellTime);		//Sets the cell date/time value for a particular node.
	virtual void GetCellLong(int nRowNdx, int nColNdx, CObject* pNode, long& nCellLong);			//Gets the cell long integer for a particular node.
	virtual void SetCellLong(int nRowNdx, int nColNdx, CObject* pNode, long& nCellLong);			//Sets the cell long integer for a particular node.
	virtual void SetCellFloat(int nRowNdx, int nColNdx, CObject* pNode, double& fCellFloat);		//Gets the cell float point value for a particular node.
	virtual void GetCellFloat(int nRowNdx, int nColNdx, CObject* pNode, double& fCellFloat);		//Sets the cell float point value for a particular node.
	virtual BOOL OnCanPromote(CObject* pNode, int nSheet = CURRENT_SHEET);		//Answers the question of whether a node can be promoted or indented.
	virtual BOOL OnCanDemote(CObject* pNode, int nSheet = CURRENT_SHEET);		//Answers the question of whether a node can be demoted or outdented.
	virtual void OnPromote(CObject* pNode, int nSheet = CURRENT_SHEET);			//Called in response to a request to promote or indent a particular node.
	virtual void OnDemote(CObject* pNode, int nSheet = CURRENT_SHEET);			//Called in response to a request to demote or outdent a particular node.
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

#endif //#ifndef __CGWHierarchyGridCtrl_H__
