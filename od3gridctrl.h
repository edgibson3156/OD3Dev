 
/////////////////////////////////////////////////////////////////////////////
// od3gridctrl.h : interface of the COD3GridCtrl class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __COD3GridCtrl_H__
#define __COD3GridCtrl_H__

// Number of columns and rows in ctrl
#define NCOLS 7
#define NROWS 201


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



class COD3GridCtrl : public CGWGridCtrl
{
public: 
	COD3GridCtrl();
	DECLARE_DYNCREATE(COD3GridCtrl)
	DECLARE_GRIDCELL_MAP(COD3GridCtrl)
	DECLARE_GW_CUSTOM_CONTROL()

// Attributes
public:

// Operations
public:
	void Initialize();
	virtual void GridOnInitialUpdate();
// Implementation
public:
	virtual ~COD3GridCtrl();
	virtual void RefreshGrid();

protected:


// Generated message map functions
protected:
	//{{AFX_MSG(COD3GridCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


//BEGIN_VIRTUAL_FUNCTIONS(COD3GridCtrl)
	virtual void InitializeColWidths();
	virtual void OnCellSelChange(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, int nItemCount, CString* pSelection, void* pExtraData, int* pItems, BOOL& bSendExtraData);
	virtual void OnCopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet = CURRENT_SHEET);
	virtual void OnDeleteRow(int nRowNdx, int nCount, int nSheet = CURRENT_SHEET);
	virtual void OnGetCellContextMenu(int nRowNdx, int nColNdx, CString csContextMenuName, CMenu*& pContextMenu);
	virtual void OnGetCellText(int nRowNdx, int nColNdx, CString& csCellText);
	virtual void OnSetCellText(int nRowNdx, int nColNdx, CString& csCellText);
	virtual void OnCellDeactivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch);
//END_VIRTUAL_FUNCTIONS

};

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS

#endif //#ifndef __COD3GridCtrl_H__
