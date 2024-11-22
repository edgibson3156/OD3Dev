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
// GWOleControl.h : Declaration of the CGWOleControl OLE control class.
#ifndef __CGWOLETREECONTROL_H__
#define __CGWOLETREECONTROL_H__
/////////////////////////////////////////////////////////////////////////////
// CGWOleTreeControl : See GWOleTreeControl.cpp for implementation.
#define GW_EXT_CLASS

class GW_EXT_CLASS CGWOleTreeControl : public CGWOleControl
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_DYNCREATE(CGWOleTreeControl)
// Constructor
public:
//GW_ENUMERATIONS{{(CGWGrid, "Outline Expand codes")
	enum nExpandCode
	{
		COLLAPSE = 0,
		COLLAPSERESET = 1,
		EXPAND = 2,
		TOGGLE = 3,
	} nExpandCodes;
//}}GW_ENUMERATIONS

//GW_MEMBERS{{(CGWOleTreeControl,"Construction")
	CGWOleTreeControl();			//Constructor
	~CGWOleTreeControl();			//Destructor
//}}GW_MEMBERS	
	
	DECLARE_GRIDCELL_MAP(CGWOleTreeControl)

//GW_MEMBERS{{(CGWOleTreeControl,"Data Members")
	CObArray m_arrayNodeIDs;			//Array containing the node ids.
	CGWHierarchyMap* m_pDataSource;		//Address of GridWiz data source
//}}GW_MEMBERS	
		
//GW_MEMBERS{{(CGWOleTreeControl,"COleControl Virtual Function Overrides")
	virtual void ExchangeGridGlobalSettings(CPropExchange* pPX);	//Exchange grid settings. Called from DoPropExchange.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWOleTreeControl,"Outline Implementation")
	virtual void RecalcHierarchy();									//Builds an array of all visible node ids.
	virtual CObject* GetNextVisibleItem(CObject* pBaseNode);		//Retrieve the next visible node id given a node id.
	virtual CObject* GetNextItem(CObject* pBaseNode);				//Get the next node id following a particular node id.
	virtual long GetLevel(CObject* pNode);							//Get the level of a particular node id.
	virtual CObject* GetPreviousItem(CObject* pBaseNode);			//Get the previous node id.
	virtual CObject* GetParent(CObject* pNode);						//Get the parent node id if any.
	virtual void GetCellText(int nRowNdx, int nColNdx, CObject* pNode, CString& csCellText);		//Get the text for a cell on a particular row with a node id matching pNode.
	virtual void SetCellText(int nRowNdx, int nColNdx, CObject* pNode, CString& csCellText);		//Set the text for a cell on a particular row with a node id matching pNode.
	virtual void SetCellLong(int nRowNdx, int nColNdx, CObject* pNode, long& nCellLong);			//Sets the cell long integer for a particular node.
	virtual void GetCellLong(int nRowNdx, int nColNdx, CObject* pNode, long& nCellLong);			//Gets the cell long integer for a particular node.
	virtual void SetCellFloat(int nRowNdx, int nColNdx, CObject* pNode, double& fCellFloat);		//Sets the cell float point value for a particular node.
	virtual void GetCellFloat(int nRowNdx, int nColNdx, CObject* pNode, double& fCellFloat);		//Gets the cell float point value for a particular node.
	virtual void SetCellTime(int nRowNdx, int nColNdx, CObject* pNode, CGWDateTime& CellTime);		//Sets the cell date/time value for a particular node.
	virtual void GetCellTime(int nRowNdx, int nColNdx, CObject* pNode, CGWDateTime& CellTime);		//Gets the cell date/time value for a particular node.
	virtual long GetVisibleItemCount();															//Get the number of potentially visible nodes. All nodes whose parents are expanded up to the root.
	virtual BOOL HasChildren(CObject* pNode);													//Answers the question of whether a node is a parent node.
	virtual BOOL IsExpanded(CObject* pNode);													//Answers the question of whether a parent node is expanded.
	virtual void Expand(CObject* pNode, UINT nExpandCode);										//Causes a parent node to expand, collapse or toggle.
	virtual CObject* GetPreviousVisibleItem(CObject* pNode);									//Get the previous visible item.
	virtual CObject* InsertNode(CObject* pParentNode, CObject* pPrevNode);						//Insert a new node into the hierarchy under a particular parent before a particular node.
	virtual CObject* AddNode(int nSheet);														//Append a node to hierarchy.
	virtual BOOL IsChildOf(CObject* pMoveNode, CObject* pNode, int nSheet = CURRENT_SHEET);		//Answers the questions whether a node is a child of a particular node.
	virtual CObject* GetNextSibling(CObject* pNode);											//Get the next sibling of pNode.
	BOOL CanPromote(CObject* pNode);								//Answers the question of whether a node can be promoted or indented.
	BOOL CanDemote(CObject* pNode);									//Answers the question of whether a node can be demoted or outdented.
	void Promote(CObject* pNode);									//Called in response to a request to promote or indent a particular node.
	void Demote(CObject* pNode);									//Called in response to a request to demote or outdent a particular node.
	long GetNodeRow(CObject* pObject);								//Retrieve arow index for a particular node id.
	virtual void MoveNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, int nInsertBefore, CObject* pInsertBeforeNode, int nSheet = CURRENT_SHEET);	//Move a node or group of nodes and insert before a particular node.
	virtual void CopyNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, int nInsertBefore, CObject* pInsertBeforeNode, int nSheet = CURRENT_SHEET);	//Copy a node or group of nodes and insert before a particular node.
	virtual void DeleteNode(int nRowNdx, CObject* pNode, int nSheet = CURRENT_SHEET);				//Delete a particular from the hierarchy.
	virtual void CopyNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, CString& csClipText, int nSheet = CURRENT_SHEET);	//Copy a group of nodes and place the text in a buffer.
	virtual void CutNode(int nBegRowNdx, CObject* pBegNode, int nEndRowNdx, CObject* pEndNode, CString& csClipText, int nSheet = CURRENT_SHEET);	//Cut a group of nodes and place the text in a buffer.
	CObject* GetNode(int nRowNdx)							//Retrieve node id for a particular row index .
	{
		CObject* pNode;
		if (nRowNdx - m_nFixedRows < 0 || nRowNdx - m_nFixedRows >= m_arrayNodeIDs.GetSize())
			pNode = NULL;
		else
			pNode = m_arrayNodeIDs[nRowNdx - m_nFixedRows];
		return pNode;
	}
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWOleTreeControl,"GridWiz Virtual Function Overrides")
	virtual CGWDataSource* CreateDataSource();										//Called to create the GridWiz data source.
	virtual void OnAddRow(int nCount, int nSheet = CURRENT_SHEET);					//Called in response to the AddRow function.
	virtual void OnGetCellObject(int nRowNdx, int nColNdx, CObject*& pObject);		//Overriden to convert row index to node id.
	virtual void OnGetCellText(int nRowNdx, int nColNdx, CString& csCellText);		//Overriden to defer to the data grid pointed to by m_pDataGrid.
	virtual void OnInsertRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);	//Overriden to convert row index to node id.
	virtual void OnMoveRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Overriden to convert row index to node id.
	virtual void OnCopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);	//Overriden to convert row index to node id.
	virtual void OnDeleteRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);	//Overriden to convert row index to node id.
	virtual void OnSelectionChange(int& nRowNdx, int& nColNdx, CRect* pRect, int nSelRectNdx);	//Overriden to convert row index to node id.
	virtual void OnSetCellText(int nRowNdx, int nColNdx, CString& csCellText);		//Overriden to convert row index to node id.
	virtual void OnSetCellLong(int nRowNdx, int nColNdx, long& nCellLong);			//Overriden to convert row index to node id.
	virtual void OnSetCellFloat(int nRowNdx, int nColNdx, double& nCellFloat);		//Overriden to convert row index to node id.
	virtual void OnSetCellTime(int nRowNdx, int nColNdx, CGWDateTime& CellTime);	//Overriden to convert row index to node id.
	virtual void OnGetCellTime(int nRowNdx, int nColNdx, CGWDateTime& CellTime);	//Overriden to convert row index to node id.
	virtual void AttachInternalDataSource();										//Overriden to attach to a CGWHierarchyMap.
	virtual void AttachDataSource(CGWDataSource* pGWDataSource);					//Overriden to attach to a CGWHierarchyMap.
	virtual void OnGetCellLong(int nRowNdx, int nColNdx, long& nCellLong);			//Overriden to convert row index to node id.
	virtual void OnCellClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);	//Overriden to convert row index to node id.
	virtual void OnGetCellVariant(int nRowNdx, int nColNdx, VARIANT& vt, UINT vID);	//Overriden to answer specifc questions on individual nodes.
	virtual void OnCellNotify(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, UINT nNotification);	//Overriden to notify the grid to expand or collapse a particular node.
	virtual void OnCellDblClick(short Button, short Shift, int nRowNdx, int nColNdx, CGWGridCellObject* pGCO);	//Overriden to expand or collapse the row that was clicked.
	virtual void GridOnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	//Overriden to fire a scroll event
	virtual void GridOnEditCut();				//Cut text on the clipboard by accessing data by node, instead of row.
	virtual void GridOnEditPaste();				//Paste text from the clipboard by node, instead of row.
	virtual void GridOnEditCopy();				//Copy text on the clipboard by accessing data by node, instead of row.
	virtual BOOL OnCanPromote(CObject* pNode, int nSheet = CURRENT_SHEET);		//Answers the question of whether a node can be promoted or indented.
	virtual BOOL OnCanDemote(CObject* pNode, int nSheet = CURRENT_SHEET);		//Answers the question of whether a node can be demoted or outdented.
	virtual void OnPromote(CObject* pNode, int nSheet = CURRENT_SHEET);			//Called in response to a request to promote or indent a particular node.
	virtual void OnDemote(CObject* pNode, int nSheet = CURRENT_SHEET);			//Called in response to a request to demote or outdent a particular node.
	virtual DROPEFFECT CalculateDropEffect(DWORD dwKeyState, CPoint point);		//Overriden to disallow certain drag operations involving parent/child relationships.
	virtual void OnActivateSheet(int nSheet);									//Overriden to call RecalcHierarchy.
	virtual CBitmap* OnGetCellBitmap(int nRowNdx, int nColNdx, BOOL& bStretch, int& nJustify);		//Called to retrieve a CBitmap pointer for a cell.
	virtual BOOL MoveRow(int nBegRowNdx, int nEndRowNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Overriden to convert from row to node.
	virtual BOOL CopyRow(int nBegRowNdx, int nEndRowNdx, int nInsertBefore, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Overriden to convert from row to node.
 	virtual BOOL DeleteRow(int nRowNdx, int nCount = 1, BOOL bRefresh = TRUE, int nSheet = CURRENT_SHEET);	//Overriden to convert from row to node.
	void SetClipData(CString& csClipBuffer, int nStartRow, int nStartColumn, int numRows, int numCols, int nSheet = CURRENT_SHEET);			//Builds a tab delimitted buffer from data in the grid.
//}}GW_MEMBERS	

protected:
//GW_MEMBERS{{(CGWOleTreeControl,"GridWiz Message Handlers")
	afx_msg void OnNodesDemote();								//Command handler for demoting a row.
	afx_msg void OnUpdateNodesDemote(CCmdUI* pCmdUI);			//Command UI handler for demoting a row.
	afx_msg void OnNodesPromote();								//Command handler for promoting a row.
	afx_msg void OnUpdateNodesPromote(CCmdUI* pCmdUI);			//Command UI handler for promoting a row.
	afx_msg  void OnGridEditChange(UINT nID)					//Called when the user changes the value of a cell through a edit control.
		{
			OnGridEditChange();
		}
	afx_msg void OnGridEditChange();							//Called when the user changes the value of a cell through a edit control.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWOleTreeControl,"CWnd Message Handlers")
	afx_msg void OnSize(UINT nType, int cx, int cy);			//Called when the user changes the size of the view or window.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);		//The framework calls this member function when an application requests that the Windows window be created by calling the Create or CreateEx member function.
//}}GW_MEMBERS	
	DECLARE_MESSAGE_MAP()

//GW_MEMBERS{{(CGWOleTreeControl,"Disaptch Implementation")
	afx_msg LPDISPATCH Sheet(short nSheetNdx);					//This function creates and returns a new Sheet object corresponding to the nSheetNdx argument.
	afx_msg long GetRows();							//This property indicates and controls the number of rows on the current sheet as well as the default sheet.
	afx_msg void SetRows(long nNewValue);			//This property indicates and controls the number of rows on the current sheet as well as the default sheet.
	afx_msg void CalcOutlineFromTabs();				//This function is called after the grid has been loaded with text to expand the tabs into the appropriate levels. This is part of a quick-load method.
//}}GW_MEMBERS	
	DECLARE_DISPATCH_MAP()

//GW_MEMBERS{{(CGWOleTreeControl, "Registered GridWiz Messages")
	long OnGetNode(WPARAM wParam, LPARAM lParam);		//Sent to retrieve a Node ID from a row. 			
//}}GW_MEMBERS	

// Event maps
	//{{AFX_EVENT(CGWOleTreeControl)
	void FireOnPromote(OLE_HANDLE NodeHandle, long nRowNdx, BOOL FAR* bProcessDefault)
		{FireEvent(eventidOnPromote,EVENT_PARAM(VTS_HANDLE  VTS_I4  VTS_PBOOL), NodeHandle, nRowNdx, bProcessDefault);}
	void FireOnDemote(OLE_HANDLE NodeHandle, long nRowNdx, BOOL FAR* bProcessDefault)
		{FireEvent(eventidOnDemote,EVENT_PARAM(VTS_HANDLE  VTS_I4  VTS_PBOOL), NodeHandle, nRowNdx, bProcessDefault);}
	void FireOnExpand(OLE_HANDLE NodeHandle, long nRowNdx, BOOL FAR* bProcessDefault)
		{FireEvent(eventidOnExpand,EVENT_PARAM(VTS_HANDLE  VTS_I4  VTS_PBOOL), NodeHandle, nRowNdx, bProcessDefault);}
	void FireOnCollapse(OLE_HANDLE NodeHandle, long nRowNdx, BOOL FAR* bProcessDefault)
		{FireEvent(eventidOnCallapse,EVENT_PARAM(VTS_HANDLE  VTS_I4  VTS_PBOOL), NodeHandle, nRowNdx, bProcessDefault);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGWOleTreeControl)
	dispidRows = 0x10001,
	dispidPromoteRow = 0x10002,
	dispidDemoteRow = 0x10003,
	dispidExpandRow = 0x10004,
	dispidCollapseRow = 0x10005,
	dispidToggleRow = 0x10006,
	eventidOnPromote = 1051L,
	eventidOnDemote = 1052L,
	eventidOnExpand = 1053L,
	eventidOnCallapse = 1054L,
	//}}AFX_DISP_ID
	};
};
#endif
