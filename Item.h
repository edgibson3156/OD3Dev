// Item.h: interface for the CItem class.
//
// CItem objects are lists of the beam or accessory elements
// in the sales order item.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__CF0E8FBA_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_)
#define AFX_ITEM_H__CF0E8FBA_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OD3Doc.h"
#include "OD3View.h"
#include "Element.h"

class CElement;
class CBeamElement;
class CAccessoryElement;

class CItem : public CObject  
{
	DECLARE_SERIAL(CItem)

public:
	// Data items
	int		m_nItemID;		//	user generated reference number (cf Aviion Sales Order item number.)
	bool	m_bIsBeam;		//	true if item is beam, false if accessory
	int		m_nType;
	CString m_sProductCode;
	CString	m_sProductName;
	CString	m_sProfile;
	CString	m_sSectionID;
	double	m_dGauge;
	int		m_nDepth;
	int		m_nTopFlange;
	int		m_nTopFlangeSlope;
	int		m_nTopFlangeLip;
	int		m_nBottomFlange;
	int		m_nBottomFlangeSlope;
	int		m_nBottomFlangeLip;
	int		m_nDimC;
	int		m_nDimF;
	double	m_nWeight;
	int		m_nProdLine;
	CString	m_sProdLine;
	CElement* m_pFailedBeam;

	COD3Doc* m_pDoc;
	bool	m_bIsNonStand;

//	Declare an array of flags to indicate whether a specific punch has alrady been 
//	allocated for use in this item
	bool	m_bPunchUsedFlag[20];
	CString m_szPunchGauge[20];
//	bool	m_bHoleTypeUsed[100];

	//	declare a list of pointers to the beam or accessory objects	contained in this item.
	CTypedPtrList<CObList, CElement*>	m_tplElementList;	
	CTypedPtrList<CObList, CElement*>	m_tplModifyList;	

public:
	CItem();
	virtual ~CItem();
	virtual void Serialize(CArchive &ar);

	CAccessoryElement	*getAccessory(CString sMark);
	CElement			*FindElementByID(int&);
	CElement			*GetElement();
	CBeamElement		*FindBeamByMark(LPCTSTR lpszTestMark);
	bool				ElementMarkExists(LPCTSTR lpszTestMark);
	void				ResetBeamCounter();
	void				ResetPunchFlags();
	void				ResetPunchGauge();
	void				copyAccessory(CAccessoryElement *pAcc);
	void				deleteAccessoy(CAccessoryElement *pAcc);
	void 				SortElementsByLength(void);

	void SetItemID(int nItemID){m_nItemID = nItemID;};
	int	GetItemID(){return m_nItemID;};

	void SetBeam(bool bIsBeam){m_bIsBeam = bIsBeam;};
	bool IsBeam(){return m_bIsBeam;};

	void SetType(int nType){m_nType = nType;};
	int	GetType(){return m_nType;};

	void SetProductCode(LPCTSTR sProductCode){m_sProductCode = sProductCode;}
	CString GetProductCode(){return m_sProductCode;}

	void SetProductName(LPCTSTR sProductName){m_sProductName = sProductName;}
	CString GetProductName(){return m_sProductName;}

	void SetProfile(LPCTSTR sProfile){m_sProfile = sProfile;}
	CString GetProfile(){return m_sProfile;}

	void SetSectionID(LPCTSTR sSectionID){m_sSectionID = sSectionID;}
	CString GetSectionID(){return m_sSectionID;}

//	add data items for TP Custom specification
	void SetGauge(double dGauge){m_dGauge = dGauge;}
	double GetGauge(){return m_dGauge;}

	void SetDepth(int nDepth){m_nDepth = nDepth;}
	int GetDepth(){return m_nDepth;}

	void SetTopFlange(int nTopFlange){m_nTopFlange = nTopFlange;}
	int GetTopFlange(){return m_nTopFlange;}
	
	void SetTopFlangeSlope(int nTopFlangeSlope){m_nTopFlangeSlope = nTopFlangeSlope;}
	int GetTopFlangeSlope(){return m_nTopFlangeSlope;}

	void SetTopFlangeLip(int nTopFlangeLip){m_nTopFlangeLip = nTopFlangeLip;}
	int GetTopFlangeLip(){return m_nTopFlangeLip;}

	void SetBottomFlange(int nBottomFlange){m_nBottomFlange = nBottomFlange;}
	int GetBottomFlange(){return m_nBottomFlange;}
	
	void SetBottomFlangeSlope(int nBottomFlangeSlope){m_nBottomFlangeSlope = nBottomFlangeSlope;}
	int GetBottomFlangeSlope(){return m_nBottomFlangeSlope;}

	void SetBottomFlangeLip(int nBottomFlangeLip){m_nBottomFlangeLip = nBottomFlangeLip;}
	int GetBottomFlangeLip(){return m_nBottomFlangeLip;}

	void SetDimC(int nDimC){m_nDimC = nDimC;}
	int GetDimC(){return m_nDimC;}

	void SetDimF(int nDimF){m_nDimF = nDimF;}
	int GetDimF(){return m_nDimF;}

//	
	void SetProductWeight(double nProductWeight){m_nWeight = nProductWeight;}
	double GetProductWeight(){return m_nWeight;}

	void SetProdLineLabel(LPCTSTR sProdLine){m_sProdLine = sProdLine;};
	CString GetProdLineLabel(){return m_sProdLine;};

	void SetProdLine(int nProdLine){m_nProdLine = nProdLine;};
	int GetProdLine(){return m_nProdLine;};

	void SetNonStandardFlag(bool bIsNonStand){m_bIsNonStand = bIsNonStand;};
	bool GetNonStandardFlag(){return m_bIsNonStand;};

	void SetFailedBeam(CElement* pElement){m_pFailedBeam = pElement;};
	CElement* GetFailedBeam(){return m_pFailedBeam;};

	bool SortBeamElementsByLength();
	void CreateOrderedBeamList(CBeamElement* pNewElement);
	void CreateOrderedAccessoryList(CAccessoryElement* pNewElement);

	CBeamElement* CreateElement();
	void DeleteBeam(CBeamElement* pBeam);
	void CutBeam(CBeamElement* pBeam, COD3View* pView);
	void CopyBeam(CBeamElement* pCopyBeam, COD3View* pView);
	void PasteBeam(COD3View* pView);

	bool SetLineFlag();
};

#endif // !defined(AFX_ITEM_H__CF0E8FBA_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_)
