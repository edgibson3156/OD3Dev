// ImportDet3.h: interface for the CImportDet3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTDET3_H__C32195C4_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_IMPORTDET3_H__C32195C4_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImportD3Acc.h"
#include "ImportD3Beam.h"
#include "DaoGetIgnore.h"
#include "OD3Doc.h"
#include "Element.h"
#include "MainFrm.h"

class CBeamElement;

class CImportDet3 : public CObject  
{
// Attributes
public:
	COD3Doc	*m_pDoc;
	CString m_fileName;

	CTypedPtrList<CObList, CImportD3Beam*> m_tplBeamList;
	CTypedPtrList<CObList, CImportD3Acc*>  m_tplAccessoryList;

private:
	CSize	m_DocSize;
	CString	m_sD3FileName;
		
	CString m_szReleaseType;
	CString	m_szOwner;
	CString m_szFile;
	CString	m_szProject;
	CString m_szComments;
	CString	m_szDestination;
	CString	m_szDeliveryDate;
	CString	m_szPackingSpec;

	CString	m_szVersion;
	CString	m_szbOrigin;
	CString	m_szClient;
	CString	m_szDrawnBy;
	CString	m_szDetailer;
	CString	m_szJobNO;
	CString	m_szPart;
	CString	m_szRef;
	CString	m_szModifiedDate;
	CString	m_szCheckedBy;
	CString	m_szCheckedDate;
	CString	m_szApprovedBy;
	CString	m_szApprovedDate;
	CString	m_szRevisedBy;
	CString	m_szDrawingComment;


//	CTypedPtrList<CObList, CItem*> m_tplD3ItemList;  

	CString	m_sProductCode;
	CString	m_sProductName;
	CString	m_sProfile;
	CString	m_sSectionID;
	double	m_nGauge;
	double	m_nWeight;
	int		m_iIsWernik;

	CItem*	m_pItem;
	CBeamElement* m_pBeam;

public:

// Operations
private:
	bool Read(LPSTR lpszDocSource);
	bool ReadBeamList(CBigIni& ABigIni);
	bool ReadAccList(CBigIni& ABigIni);
	bool FindListedItem(CImportD3Beam* pD3Beam, bool &bIgnore);
	bool FindListedBeam(CImportD3Beam* pD3Beam);
	bool CompareBeam(CImportD3Beam* pD3Beam);
	int  GetMaxBundleCount();


	bool ItemMarkExists(LPCSTR lpszTestMark);
	CString FindProductCode(LPCTSTR sProductName, int nMemberType);
	CString GetSBEName(CString& sProductName);

	bool IsBeamHead(CImportD3Beam* pBeam);
	bool IsBeamTail(CImportD3Beam* pBeam);
	int GetBeamIndex(CImportD3Beam* pThisBeam);
	CImportD3Beam* FindBeamByMark(LPCSTR lpszTestMark);
	BOOL ParseALargeFile(HWND hwndParent, LPSTR lpszFileName);

	void SortBeamByAscendingMark();
	void BeamSwap(CImportD3Beam* pBeam1, CImportD3Beam* pBeam2);

	bool IsAccHead(CImportD3Acc* pAccessory);
	bool IsAccTail( CImportD3Acc* pAccessory);
	int GetAccIndex(CImportD3Acc* pThisAccessory);
	CImportD3Acc* FindAccessory(LPCSTR lpszTestMark);

	void SortAccByAscendingMark();
	void AccSwap(CImportD3Acc* pAccessory1, CImportD3Acc* pAccessory2);

	CBeamElement*		AddBeamElement(CImportD3Beam*	pD3Beam /*, int nTag */);
	CAccessoryElement*	AddAccessoryElement(CImportD3Acc* pD3Acc, int nTag);
	void SplitProductID(LPCTSTR sProduct, CString& sSection, CString& sGauge);
	
public:
	CItem* testAccessory(CString sName);
	bool WriteD3Header(CBigIni& ABigIni);
	CString getD3FileName(void) { return(m_sD3FileName);};

	CImportDet3();
	virtual ~CImportDet3();

	CSize GetDocSize(void){return(const CSize)m_DocSize;}
	void  SetDocSize(CSize size){this->m_DocSize = size;}
	int	  isWernik(void){if(m_iIsWernik==IDYES)return(true);else return(false);};

	void SetOwner(LPCTSTR lpsz)		{this->m_szOwner = lpsz;} 	
	void SetFile (LPCTSTR lpsz)		{this->m_szFile	 = lpsz;}
	void SetProject(LPCTSTR lpsz)	{this->m_szProject = lpsz;}
	void SetComment(LPCTSTR lpsz)	{this->m_szComments = lpsz;} 	
	LPCTSTR GetReleaseType()	{return (LPCTSTR) this->m_szReleaseType;}
	void	SetReleaseType(CString sRel) { m_szReleaseType=sRel; };
	LPCTSTR GetOwner()	{return (LPCTSTR) this->m_szOwner;}
	LPCTSTR GetFile()	{return (LPCTSTR) this->m_szFile;}
	LPCTSTR GetProject(){return (LPCTSTR) this->m_szProject;}
	LPCTSTR GetComment(){return (LPCTSTR) this->m_szComments;}

	/******************************************************************/
	void SetVersionNo(CString str)		{m_szVersion = str;}
	CString GetVersionNo(void)			{return(m_szVersion);}

	void SetBuildOrigin(CString str)	{m_szbOrigin = str;}
	CString GetBuildOrigin(void)		{return(m_szbOrigin);}

	void SetClient(CString str)			{m_szClient= str;}
	CString GetClient(void)				{return(m_szClient);}

	void SetDrawnBy(CString str)		{m_szDrawnBy = str;}
	CString GetDrawnBy(void)			{return(m_szDrawnBy);}

	void SetDetailer(CString str)		{m_szDetailer = str;}
	CString GetDetailer(void)			{return(m_szDetailer);}

	void SetJobNO(CString str)			{m_szJobNO = str;}
	CString GetJobNO(void)				{return(m_szJobNO);}

	void SetPart(CString str)			{m_szPart = str;}
	CString GetPart(void)				{return(m_szPart);}

	void SetRef(CString str)			{m_szRef= str;}
	CString GetRef(void)				{return(m_szRef);}

	void SetModifiedDate(CString str)	{m_szModifiedDate = str;}
	CString GetModifiedDate(void)		{return(m_szModifiedDate);}

	void SetCheckedBy(CString str)		{m_szCheckedBy = str;}
	CString GetCheckedBy(void)			{return(m_szCheckedBy);}

	void SetCheckedDate(CString str)	{m_szCheckedDate = str;}
	CString GetCheckedDate(void)		{return(m_szCheckedDate);}

	void SetApprovedBy(CString str)		{m_szApprovedBy = str;}
	CString GetApprovedBy(void)			{return(m_szApprovedBy);}

	void SetApprovedDate(CString str)	{m_szApprovedDate = str;}
	CString GetApprovedDate(void)		{return(m_szApprovedDate);}

	void SetRevisedBy(CString str)		{m_szRevisedBy = str;}
	CString GetRevisedBy(void)			{return(m_szRevisedBy);}

	void SetDrawingComment(CString str)	{m_szDrawingComment = str;}
	CString GetDrawingComment(void)		{return(m_szDrawingComment);}
	/******************************************************************/

	bool OpenFile();
	void SetProjectHeader();
	void SortBeamsByAscendingProductName();
	void SortAccByAscendingProductName();
	void ListImportedItems();
	void UpdateStatusBar(LPCTSTR lpszText);
protected:
	CString findEavesBeam(CString sName, int iAngle);
	bool	ignoreItem(CString sProductName);
	CString modifyImportName(CString name);
	
};

#endif // !defined(AFX_IMPORTDET3_H__C32195C4_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
