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
// hiermap.h : interface of the CGWHierarchyMap class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __CGWHierarchyMap_H__
#define __CGWHierarchyMap_H__


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

class GW_EXT_CLASS CGWNode : public CObject
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_SERIAL(CGWNode)
public:
//GW_MEMBERS{{(CGWNode,"Construction")
	CGWNode();					//Default Constructor.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWNode,"Data Members")
	CGWNode* m_pParent;			//This nodes parent node id.
	BOOL    m_bExpanded;		//Indicates whether this node is expanded.
	int		m_nRowNdx;			//RowNdx into CCellDataMap.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWNode,"Operations")
	virtual void Serialize(CArchive& ar);	//Store or load this CGWNode object to and from a CArchive object.
	void operator=(CGWNode& otherNode);		//Copies a CGWNode object to another.
//}}GW_MEMBERS	
};

class GW_EXT_CLASS CGWHierarchySheet : public CSheet
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
	DECLARE_SERIAL(CGWHierarchySheet)
public: 
//GW_MEMBERS{{(CGWHierarchySheet,"Construction")
	CGWHierarchySheet();		//Default Constructor.
	~CGWHierarchySheet();		//Default Destructor.
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWHierarchySheet,"Data Members")
	CObList m_listNodes;		//Collection of nodes.
//}}GW_MEMBERS	
	
//GW_MEMBERS{{(CGWHierarchySheet,"Operations")
	virtual void Serialize(CArchive& ar);				//Stores and loads a CGWHierarchySheet to and from a CArchive object.
	void FixupNodeList();								//Iterate through the node list and fixup parent child relationships.
	void operator=(CGWHierarchySheet& otherSheet);		//Copy one CGWHierarchySheet object to another.
	CObject* GetPreviousItem(CObject* pNode, POSITION pos=NULL);			//Get the previous node from the node list.
	CObject* GetNextItem(CObject* pNode, POSITION pos=NULL);				//Get the next node from the node list.
	CObject* GetPreviousVisibleItem(CObject* pNode, POSITION pos=NULL);	//Get the previous visible node from the node list.
	CObject* GetNextVisibleItem(CObject* pNode, POSITION pos=NULL);		//Get the next visible node from the node list.
	CObject* GetParent(CObject* pNode);					//Get a nodes parent.
	CObject* GetNextSibling(CObject* pNode, POSITION pos=NULL);			//Get the next visible sibling.
	CObject* GetFirstChild(CObject* pNode);				//Get a node's first child.
	CObject* NodeFromHandle(int nHandle);				//Retrieve a node from a integer handle id.
	int GetSafeNodeHandle(CObject* pNode);				//Get a handle of a node id.
	virtual void ClearSheetData();					//Clear the sheet's data only.			
//}}GW_MEMBERS	

	
//GW_MEMBERS{{(CGWHierarchySheet,"Overriden Virtual Functions")
	virtual void RefreshSheet(CGWMapIntToPtr* pMap, BOOL bFixupGroups = TRUE);
	virtual void ClearSheetAll();					//Clear the sheet's data and display settings.
//}}GW_MEMBERS	

//Overrideables
public:
//GW_MEMBERS{{(CGWHierarchySheet,"Overrideables")
	virtual void CreateTempList(CObList* pDestList, CObject* pBegNode, CObject* pEndNode);		//Create a list of nodes in preparation for a copy or move operation.
	virtual void RemoveNodesFromList(CObList* pList);											//Remove a subset of nodes from a list.
	virtual void InsertIntoList(CObList* pList, CObject* pInsertBefore);						//Insert a list of nodes into the node list.
	virtual void CopyList(CObList* pSourceList, CObList* pDestList);							//Copy a group of nodes from one location in the node list to another.
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CObject* pNode, CString& csCellText);	//Get the cell text associated with a cell on a row based on its node id.
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CObject* pNode, CString& csCellText);	//Set the cell text associated with a cell on a row based on its node id.
	virtual void SetCellLong(UINT nRowNdx, UINT nColNdx, CObject* pNode, long& nCellLong);		//Set the cell long integer value associated with a cell on a row based on its node id.
	virtual void GetCellLong(UINT nRowNdx, UINT nColNdx, CObject* pNode, long& nCellLong);		//Get the cell long integer value associated with a cell on a row based on its node id.
	virtual void SetCellFloat(UINT nRowNdx, UINT nColNdx, CObject* pNode, double& fCellFloat);	//Get the cell floating point value associated with a cell on a row based on its node id.
	virtual void GetCellFloat(UINT nRowNdx, UINT nColNdx, CObject* pNode, double& fCellFloat);	//Set the cell floating point value associated with a cell on a row based on its node id.
	virtual void SetCellTime(UINT nRowNdx, UINT nColNdx, CObject* pNode, CGWDateTime& CellTime);	//Get the cell date/time value associated with a cell on a row based on its node id.
	virtual void GetCellTime(UINT nRowNdx, UINT nColNdx, CObject* pNode, CGWDateTime& CellTime);	//Set the cell date/time value associated with a cell on a row based on its node id.
	virtual void InsertRow(UINT nRowNdx, UINT nCount, CObject* pNode);							//Insert a new row into the grid and assign a the node id.
	virtual void DeleteRow(UINT nRowNdx, UINT nCount, CObject* pNode);							//Delete one or more rows by node id.
	virtual void MoveRow(UINT nRowNdx, UINT nCount, CObject* pNode);							//Move one or more rows by node id.
	virtual CObject* InsertNode(CObject* pParent, CObject* pInsertBefore);						//Insert one or more rows by node id before a particular node.
	virtual void MoveNode(CObject* pBegNode, CObject* pEndNode, CObject* pInsertBeforeNode);	//Move one or more nodes by node id before another node.
	virtual void CopyNode(CObject* pBegNode, CObject* pEndNode, CObject* pInsertBeforeNode);	//Copy one or more nodes by node id before another node.
	virtual void DeleteNode(CObject* pNode);						//Delete one or more nodes.
	virtual CObject* AddNode();										//Append a new node.
	virtual int GetItemCount();										//Get the total number of nodes.
	virtual int GetVisibleItemCount();								//The total number of visible items.
	virtual int GetLevel(CObject* pParent);							//Get the level of a particular node.
	virtual BOOL IsNodeVisible(CObject* pNode);						//Check to see if the node is visible. All parents must be expanded.
	virtual BOOL IsChildOf(CObject* pMoveNode, CObject* pNode);     //Check to see if a node is a child of another node.
	virtual BOOL IsExpanded(CObject* pNode);						//Check to see if a node has been expanded.
	virtual void Expand(CObject* pNode, UINT nCode);				//Expand, collapse or toggle a particular node.
	virtual BOOL HasChildren(CObject* pNode, POSITION pos=NULL);						//Check to see if a node has children.
	virtual BOOL CanPromote(CObject* pNode);						//Check to see if a node can be promoted or indented.
	virtual BOOL CanDemote(CObject* pNode);							//Check to see if a node can be demoted or outdented.
	virtual void Promote(CObject* pNode);							//Promote or indent a node.
	virtual void Demote(CObject* pNode);							//Demote or outdent a node.
	virtual void ImportData(CGWImportExportObject* pGWImportExportObject);		//Import data from an external source.
//}}GW_MEMBERS	
};


class GW_EXT_CLASS CGWHierarchyMap : public CCellDataMap
{

//GW_CLASS{{(CGWHierarchyMap)
/*

The CGWHierarchyMap derives from the CCellDataMap class and provides persistance and other services to grids which 
are based on either CGWGridCtrl and CGWGridView grids. The added functionality deals mainly with managing nodes in 
a doubly linked list as well as maintaining the parent child relationships required for an outline format. The cells 
are still identified by row and column indexes, except when storing and retrieving data. In this case, the row index 
is replaced by a node index. The node index is managed by the CGWHierarchyMap object. When new Rows or Nodes are added, 
the hierarchy map allocates a node and keeps track of parent and sibling relationships. The Hierarchy view and control 
have overridden most of the grid vitual functions and will convert row indexes into Node IDs. Other functions are 
provided for traversing the list retrieving node identifiers for related nodes. 

In order to use a hierarchical/outline grid, you must attach to data source of this type. Hierarchical grids built by the
GridWiz Wizard automatically take of this for you. See the CGWHierarchyGridView and CGWHierarchyGridCtrl for details on
implementing these grids. In most cases, functions on those classes directly call functions on this class, relieveing 
you from needing to know any details of this class. 

See the article "Hierarchical/Outline Grids" for additional implementation details. There is also a sample application
called HIERGRID.

*/
//}}GW_CLASS	



public: 
//GW_ENUMERATIONS{{(CGWHierarchyMap, "Outline node expand and collapse codes. Passed to the Expand() function.")
	enum nExpandCode
	{
		COLLAPSE = 0,
		COLLAPSERESET = 1,
		EXPAND = 2,
		TOGGLE = 3,
	} nExpandCodes;
//}}GW_ENUMERATIONS

	DECLARE_SERIAL(CGWHierarchyMap)

//GW_MEMBERS{{(CGWHierarchyMap,"Construction")
	CGWHierarchyMap();
	~CGWHierarchyMap();
//}}GW_MEMBERS	

// Operations
public:
//GW_MEMBERS{{(CGWHierarchyMap,"Operations")
	CObject* GetPreviousItem(CObject* pNode, int nSheet = 0);			//Get the previous node from the node list.
	CObject* GetNextItem(CObject* pNode, int nSheet = 0);				//Get the next node from the node list.
	CObject* GetPreviousVisibleItem(CObject* pNode, int nSheet = 0);	//Get the previous visible node from the node list.
	CObject* GetNextVisibleItem(CObject* pNode, int nSheet = 0);		//Get the next visible node from the node list.
	CObject* GetParent(CObject* pNode, int nSheet = 0);					//Get a nodes parent.
	CObject* GetNextSibling(CObject* pNode, int nSheet = 0);			//Get the next visible sibling.
	CObject* GetFirstChild(CObject* pNode, int nSheet = 0);				//Get a node's first child.
	CObject* NodeFromHandle(int nHandle, int nSheet = 0);				//Retrieve a node from a integer handle id.
	int GetSafeNodeHandle(CObject* pNode, int nSheet = 0);				//Get a handle of a node id.
	void CalcOutlineFromTabs();											//Build the outline from raw data loaded into the data source.
	void FixupNodeList(int nSheet = 0);									//Remove any unmapped rows.
//}}GW_MEMBERS	
	

//GW_MEMBERS{{(CGWHierarchyMap,"Overriden Virtual Functions")
	virtual void Initialize();											//Assigns design time property values.
	virtual void LoadSettings(CString csSettingsFile);					//Loads the data source from a file or custom resource.
	virtual void CopySheet(int nSourceSheetNdx, int nDestSheetNdx);		//Copies one sheet to another.
	virtual void AddRow(UINT nCount, int nSheet = 0);											//Overriden to append a node.
	virtual void DeleteRow(UINT nRowNdx, UINT nCount, int nSheet = 0);							//Overriden to delete a node.
	virtual void GetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0);	//Overriden to retrieve a node id.
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);	//Overriden to convert row index to node id.
	virtual void InsertRow(UINT nRowNdx, UINT nCount, int nSheet = 0);							//Overriden to convert row index to node id.
	virtual void MoveRow(UINT nRowNdx, UINT nCount, int nSheet = 0);							//Overriden to convert row index to node id.
	virtual void Serialize(CArchive& ar);														//Stores and loads a CGWHierarchyMap to and from a CArchive object.
	virtual void SetCellObject(UINT nRowNdx, UINT nColNdx, CObject*& pObject, int nSheet = 0);	//Overriden to assign a node id to a row,
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CString& csCellText, int nSheet = 0);	//Overriden to convert row index to node id.
	virtual int AddSheet(CString csSheetName, CObject* pSheetExtraData = NULL);					//Overriden to create an instance of a CGWHierarchySheet object.
	virtual void InsertNewSheet(int nInsertBefore, CString csSheetName, CObject* pSheetExtraData);	//Overriden to create an instance of a CGWHierarchySheet object.
	virtual void RefreshSheet(int nSheet = 0);							//Calls Refresh sheet on the sheet.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWHierarchyMap,"Overrideables")
	virtual void GetCellText(UINT nRowNdx, UINT nColNdx, CObject* pNode, CString& csCellText, int nSheet = 0);		//Get the cell text associated with a cell on a row based on its node id.
	virtual void SetCellText(UINT nRowNdx, UINT nColNdx, CObject* pNode, CString& csCellText, int nSheet = 0);		//Set the cell text associated with a cell on a row based on its node id.
	virtual void SetCellLong(UINT nRowNdx, UINT nColNdx, CObject* pNode, long& nCellLong, int nSheet = 0);			//Set the cell long integer value associated with a cell on a row based on its node id.
	virtual void GetCellLong(UINT nRowNdx, UINT nColNdx, CObject* pNode, long& nCellLong, int nSheet = 0);			//Get the cell long integer value associated with a cell on a row based on its node id.
	virtual void SetCellFloat(UINT nRowNdx, UINT nColNdx, CObject* pNode, double& fCellFloat, int nSheet = 0);		//Get the cell floating point value associated with a cell on a row based on its node id.
	virtual void GetCellFloat(UINT nRowNdx, UINT nColNdx, CObject* pNode, double& fCellFloat, int nSheet = 0);		//Set the cell floating point value associated with a cell on a row based on its node id.
	virtual void SetCellTime(UINT nRowNdx, UINT nColNdx, CObject* pNode, CGWDateTime& CellTime, int nSheet = 0);	//Set the cell date/time value associated with a cell on a row based on its node id.
	virtual void GetCellTime(UINT nRowNdx, UINT nColNdx, CObject* pNode, CGWDateTime& CellTime, int nSheet = 0);	//Get the cell date/time value associated with a cell on a row based on its node id.
	virtual void InsertRow(UINT nRowNdx, UINT nCount, CObject* pNode, int nSheet = 0);								//Insert a new row into the grid and assign a the node id.
	virtual void DeleteRow(UINT nRowNdx, UINT nCount, CObject* pNode, int nSheet = 0);								//Delete one or more rows by node id.
	virtual void MoveRow(UINT nRowNdx, UINT nCount, CObject* pNode, int nSheet = 0);								//Move one or more rows by node id.
	virtual CObject* InsertNode(CObject* pParent, CObject* pInsertBefore, int nSheet = 0);							//Insert one or more rows by node id before a particular node.
	virtual void MoveNode(CObject* pBegNode, CObject* pEndNode, CObject* pInsertBeforeNode, int nSheet = 0);		//Move one or more nodes by node id before another node.
	virtual void CopyNode(CObject* pBegNode, CObject* pEndNode, CObject* pInsertBeforeNode, int nSheet = 0);		//Copy one or more nodes by node id before another node.
	virtual void DeleteNode(CObject* pNode, int nSheet = 0);						//Delete one or more nodes.
	virtual CObject* AddNode(int nSheet = 0);										//Append a new node.
	virtual int GetItemCount(int nSheet = 0);										//Get the total number of nodes.
	virtual int GetVisibleItemCount(int nSheet = 0);								//The total number of visible items.
	virtual int GetLevel(CObject* pParent, int nSheet = 0);							//Get the level of a particular node.
	virtual BOOL IsExpanded(CObject* pNode, int nSheet = 0);						//Check to see if a node has been expanded.
	virtual void Expand(CObject* pNode, UINT nCode, int nSheet = 0);				//Expand, collapse or toggle a particular node.
	virtual BOOL HasChildren(CObject* pNode, int nSheet = 0);						//Check to see if a node has children.
	virtual BOOL IsChildOf(CObject* pMoveNode, CObject* pNode, int nSheet = 0);		//Check to see if a node is a child of another node.
	virtual BOOL CanPromote(CObject* pNode, int nSheet = 0);						//Check to see if a node can be promoted or indented.
	virtual BOOL CanDemote(CObject* pNode, int nSheet = 0);							//Check to see if a node can be demoted or outdented.
	virtual void Promote(CObject* pNode, int nSheet = 0);							//Promote or indent a node.
	virtual void Demote(CObject* pNode, int nSheet = 0);							//Demote or outdent a node.
	virtual CGWCellSettings* GetCellSettings(UINT nRowNdx, UINT nColNdx, int nSheet = 0);					//Get the cell settings for a row or node				
	virtual void SetCellSettings(UINT nRowNdx, UINT nColNdx, CGWCellSettings*& pSetting, int nSheet = 0);	//Set the cell settings for a row or node
	virtual void SetRowSettings(int nRowNdx, CGWRowSettings*& pSetting, int nSheet = 0);					//Set the rows cell settings based on rowndx or node id.
	virtual CGWRowSettings* GetRowSettings(int nRowNdx, int nSheet = 0);									//Get the rows cell settings based on rowndx or node id.
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

#endif //#ifndef __CGWHierarchyMap_H__
