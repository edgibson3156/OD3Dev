// OD3Doc.h : interface of the COD3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OD3DOC_H__8BDEC0ED_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_OD3DOC_H__8BDEC0ED_1681_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectHeader.h"
#include "SysConfig.h"
#include "Item.h"
#include "BeamDlg.h"
#include "Element.h"
#include "JobSheet.h"


class CBeamDlg;
class CElement;
class CBeamElement;
class CAccDlg;
class CItem;

#define ISBEAM 1
#define ISACCESSORY 2

// A4 page size and maximums
#define A4_X 2100
#define A4_Y 2970

class COD3Doc : public CDocument
{
protected: // create from serialization only
	COD3Doc();
	DECLARE_DYNCREATE(COD3Doc)

// Attributes
public:
	CWnd*			pAppWnd;
	CProjectHeader*	m_pProjectHeader;	// pointer to the Header info, job no, etc.
	CSysConfig*		m_pProjectSettings;	// pointer to the Data Source & line associations.
	CDaoDatabase*	m_pDB;				// Pointer to Current Database
	bool			m_ODDB_Open;		// Status of Database
	CBeamDlg*		m_pBeamModeless;
	CAccDlg*		m_pAccModeless;
	bool			m_bProcessAll;
	bool			m_bPrompt;
	CBeamElement*	m_pFailedBeam;
	bool			m_bIsGenerated;
	bool			m_bIsGenerating;
	CString			m_sCustomerFilter;								
	CStringArray	m_printSelArr;								// Which elements am I to print

	CTypedPtrList<CObList, CItem*> m_tplItemList;				// a list of all the items in the project
	CTypedPtrList<CObList, CItem*> m_tplAccItemList;			// Accessory item list
	CTypedPtrList<CObList, CElement*> m_tplCutList;				// a list of elements cut from the item list
	CTypedPtrList<CObList, CElement*> m_tplCopyList;			// a list of elements copied from the item list
	CTypedPtrList<CObList, CAssociation*> m_tplMirror;			// a copy of product v production line associations	
	CTypedPtrList<CObList, CJobSheet*> m_tplJobSheet;			// List of item job sheets 



	// Operations
public:
	CProjectHeader*	GetProjectHeader(){return this->m_pProjectHeader;}
	CSysConfig*		GetProjectSettings(){return this->m_pProjectSettings;}
	CItem* CreateItem(int nItemID);
	CItem* CreateItem(int nItemID, int iDummy);
	//CItem* GetItemPointer(int nItemID);
	CItem* GetItemPointer(int nItemID, int iType);
	bool ValidateItem(CItem* pItem);
	bool GenerateItem(CItem* pItem);
	CString GetMemberTypeLabel(int nType);
	int  GetMemberTypeValue(LPCTSTR sType);
	int	 GetElementCount(int);
	void SortByItemID(int iType);
	void ItemSwap(CItem* pItem1, CItem* pItem2, int iType);
	void CheckDirty();
	void BoxDone();
	void UpdateDoc(int);
	void OnPreviousBeam(CBeamDlg*);
	void OnNextBeam(CBeamDlg*);
	void GetScriptOps(CItem* pItem, int nMemberType);
	void GenerateOutput(CItem* pItem);
	void OnNextItem(){OnProcessAddNewitem();};
	void OnNextBeam(){OnProcessAddNewbeam();};
	void OnGenerateAll(){OnProcessGenerateAll();};
	void DeleteItem(CItem* pItem);
	void CreateBeamDialog(CItem* pItem, CBeamElement* pBeam, int cElementCounter);
	void CreateBeamDialog(CItem* pItem, CBeamElement* pBeam, CString mark);
	void RefreshBeamDialog(CItem* pItem, CBeamElement* pBeam, int cElementCounter);
	bool TransferItem(CItem* pItem);
	bool TransferItemb(CItem* pItem);
	void CopyPartToDisk(CString& szSorcePath, CString& szTargetPath);
	void UpdateGrid(CItem* pItem);
	void AddBeam(CItem* pItem); 
	void UpdateStatusBar(LPCTSTR lpszText);
	int  GetOpCount();
	int	 GetElementOpCount(CItem* pItem);
	void InitProgressIndicator(int nOpCount);
	void CloseProgressIndicator();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COD3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void printCoilPlanning(CDC *pDC);
	void	setCoilDataList(void);
	CString setCoilDBPath();
	float	getTotalWeight(void);
	void	setGroupType(CString sSearch, CString &sType, CString &sGroup);
	CString createAccFileName(int iItemNum);
	bool ValidateAccItem(CItem *pItem);
	bool GenerateAccItem(CItem *pItem);
	bool writeInkJetFile(CItem *pItem);
	bool writeInkJetFile2(CItem *pItem);
	void removeFile(CFileFind *file);
	bool TestMedia();
	bool TestMedia2();
	bool testForManualHashCodes(void);
	bool compareMirrorAsso(void);
	void removeMirror(void);
	void storeMirrorAsso(void);
	virtual ~COD3Doc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void printJobSheet(CJobSheet *pSheet, CDC *pDC);
	void createJobLists(void);
	bool testBounds(CDC *pDC, int *yPos, int *iPageNum);
	//{{AFX_MSG(COD3Doc)
	afx_msg void OnDbConnect();
	afx_msg void OnDbDisconnect();
	afx_msg void OnOpenSysconfig();
	afx_msg void OnUpdateDbConnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDbDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpenSysconfig(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddNewitem(CCmdUI* pCmdUI);
	afx_msg void OnFileImportProjectsettings();
	afx_msg void OnFileImportD3();
	afx_msg void OnProcessAddNewbeam();
	afx_msg void OnProcessAddNewaccessory();
	afx_msg void OnProcessAddNewitem();
	afx_msg void OnProcessDeleteBeam();
	afx_msg void OnProcessDeleteAccessory();
	afx_msg void OnProcessGenerateAll();
	afx_msg void OnProcessGenerateItem();
	afx_msg void OnProcessValidateAll();
	afx_msg void OnProcessValidateItem();
	afx_msg void OnProcessDeleteItem();
	afx_msg void OnFileTransfer();
	afx_msg void OnFileTransfer2();
	afx_msg void OnImportAsw();
	afx_msg void OnExportD3();
	afx_msg void OnUpdateExportD3(CCmdUI* pCmdUI);
	afx_msg void OnPrintSummary();
	afx_msg void OnUpdatePrintSummary(CCmdUI* pCmdUI);
	afx_msg void OnPrintJobsheets();
	afx_msg void OnUpdatePrintJobsheets(CCmdUI* pCmdUI);
	afx_msg void OnCoilSendjob();
	afx_msg void OnUpdateCoilSendjob(CCmdUI* pCmdUI);
	afx_msg void OnCoilUpdatejob();
	afx_msg void OnCoilPrintlive();
	afx_msg void OnCoilExportlive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OD3DOC_H__8BDEC0ED_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
