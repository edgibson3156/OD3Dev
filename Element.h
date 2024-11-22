// Element.h: interface for the CElement class.
//
//	A CElement object is abstract and provides to root for CBeam and CAccessory objects
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENT_H__E54C5C61_27BF_11D3_A15C_0060082A2F7E__INCLUDED_)
#define AFX_ELEMENT_H__E54C5C61_27BF_11D3_A15C_0060082A2F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BeamOps.h"
#include "AccOps.h"
#include "DlgAccessories.h"
#include "Item.h"
#include "Line1.h"
#include "Scripts.h"
#include "Hole.h"

class COD3Doc;
class CBeamDlg;
class CItem;
class CScripts;

#define ITEMCOUNT 10
#define SERVICEHOLES 610		// Distance between service hole centres
#define SERVICE_TOOL_OFFSET 50	// Tool offset on line 3

class CElement : public CObject  
{
	DECLARE_SERIAL (CElement)

protected:
	double		stripHashCode(CString punchCode, int line);
	double		zeta(int line, CString partName,  CString punchCode, double orgCode);
	double		cee(int line, CString partName, CString punchCode);
	bool		allowModPass(int lineNum, CString sectionID);
	void		modifyHoleProcess(CString lineIdent, CString sectionID, CString sPunch, int *on_Line);
	double		z1_200(int line, CString partName, CString punchCode);
	double		z240_300(int line, CString partName, CString punchCode, double orgCode);
	double		zed(int line, CString partName, CString punchCode, double orgCode);
	double		eaves(int line, CString partName, CString punchCode, double orgCode);
	double		zeta2(int line, CString partName, CString punchCode, double orgCode);
	double		m_hitTwo;
	double		m_hitThree;
	double		m_extraFeed;

	int			m_nElementID;	//	unique system generated ref number.
	int			m_nQty;			//	required quantity
	CString		m_sMark;		//	unique (customer specified) reference number
	CString		m_sSection;		//	section profile and depth, e.g. 1/125
	CString		m_sGauge;		//	gauge of the material in millimetres

	double		modifyPunchCodes(int line, CString partName, CString punchCode, double orgCode);

public:
	COD3Doc*	m_pDoc;
	CItem*		m_pItem;

	bool		m_extra;

public:
	CElement();
	virtual ~CElement();
	virtual void Serialize(CArchive &ar);

	void SetElementID(int nElementID){m_nElementID = nElementID;};
	int GetElementID(){return m_nElementID;};

	void SetQty(int nQty){m_nQty = nQty;};
	int GetQty(){return this->m_nQty;};

	void SetMark(LPCTSTR sMark){m_sMark = sMark;};
	CString GetMark(){return m_sMark;};

	void SetSection(LPCTSTR sSection){m_sSection = sSection;};
	CString GetSection(){return m_sSection;};

	void SetGauge(LPCTSTR sGauge){m_sGauge = sGauge;};
	CString SetGauge(){return m_sGauge;};

	int  getPart(CString partRef);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CBeamElement Class Declaration
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EXTRA	1
#define SCRIPT	0

#include "DaoImportedHoles.h"

class CBeamElement : public CElement
{
	DECLARE_SERIAL(CBeamElement)


protected:
	void		resetExtraHolesList(void); // Deletes all extra holes in the linked list
	bool		createASFServiceHoles(void); // Creates ASF service holes

	CString		m_sSPC;					//	standard part code as defined in OD3 database
	CString		m_sComment;				//	free text entered by user (may be null)
	int			m_nBdlQty;				//	number of parts in bundle (irrespective of mark no)
	int			m_nOLength;				//	overall length of beam
	int			m_nSpan1;				//	span1 dimension in millimetres (may be null)
	int			m_nSpan2;				//	span2 dimension in millimetres (may be null)
	int			m_nSpan3;				//	span3 dimension in millimetres (may be null)
	int			m_nOHang1;				//	overhang1 dimension in millimetres (may be null)
	int			m_nOHang2;				//	overhang2 dimension in millimetres (may be null)
	int			m_nCol1;				//	Column1 Flange width dimension in millimetres (may be null)
	int			m_nCol2;				//	Column2 Flange width dimension in millimetres (may be null)
	int			m_nSlope;				//	slope of top flange (applies to eaves beams only - may be null)
	int			m_nType;				//	member type = 1 (purlin) or 2 (rail)
	bool		m_bIsNonStandardHole;

public:
	// Non-archive variables
	CBeamDlg*	m_pBeamModeless;	//	ponter to manual input dialog
	CScripts*	m_pScript;
	long		m_OpScriptID;
	int			m_nHits;			//	number of hits required to insert specified holes
	bool		m_bIgnoreMsg;

public:
	CTypedPtrList<CObList, CBeamOps*>	m_tplAddList;		//	pointer to list of additional hole operations for manual input
	CTypedPtrList<CObList, CHole*>		m_tplHitList;		//	pointer to list of Hits, i.e. Position + Punch pair
	CTypedPtrList<CObList, CBeamOps*>	m_tplScriptList; 	//	pointer to data 'script' i.e. list of SPC operations
	CTypedPtrList<CObList, CHole*>		m_tplPrintHitList;	//	pointer to list of Hits, i.e. Position + Punch pair

public:
	CBeamElement();
	virtual ~CBeamElement();
	virtual void Serialize(CArchive &ar);

	CBeamElement* FindBeamByElementID(/*CItem* pItem,*/ int& nElementID);
	void UpdateBeam(CBeamDlg* pDlg);

private:
	void InterpretGridText(LPCTSTR lpszCellText, CBeamOps* pOperation, int nRow);
	void RemoveXtraHoleList();
	void CreateHole(double nFeed, LPCTSTR lpszPunch, double nPunchValue, bool bFirstLastFlag);
	void ProcessOperation(/*int &nHits,*/ double& nFeed, double& nPunchValue, CString& sRetainedComment, long& nPreviousHoleType, /*CItem* pItem,*/ CBeamOps* pBeamOp, /*CDaoDatabase* m_pDB,*/ UINT nList);	
	void ReversePunching(/*CItem* pItem,*/ double& nFeed, LPCTSTR lpszPunch, double& nPunchValue);
	void CreateOrderedScriptList(CBeamOps* pBeamOp);
	void DeleteHits();
	void UpdateProgressIndicator(int cOpCounter);
	void UpdateStatusBar(LPCTSTR lpszText);
	bool CheckLegalPosition(/*CItem* pItem,*/ /*int nHit,*/ double nFeed );
	CString GetMsgHeader(/*CItem* pItem,*/ /*int nHit*/);
	CString TrapSpecialCodes(CString& sPunch, CString& sComment, LPCTSTR lpszOpDef, long lHoleID, bool& bMultipleHitCase);
	double GetPunchValue(/*CItem* pItem,*/ /*CElement* pElement,*/ CBeamOps* pBeamOp, /*CDaoDatabase* m_pDB,*/ LPCTSTR lpszPunch/*, int nHits*/);
	void DefineHole(CBeamOps* pBeamOp, double nFeed, long lHoleID, LPCTSTR lpszPunch, LPCTSTR lpszOpDef, CString& sComment, bool& bMultipleHitCase);	
	bool CheckPunchConflicts(CBeamOps* pBeamOp, long lHoleID, LPCTSTR lpszOpDef, CString& sPunchMsg, CString& sRetainedComment, long& nPreviousHoleType, CString& sDefaultPunch, CString& szMsg);
	bool CheckLine2ExtraHole(CBeamOps* pBeamOp, long lHoleID, CString& sPunchMsg, CString& sRetainedComment, long& nPreviousHoleType, CString& sDefaultPunch);
	bool CheckLine3ExtraHole(CBeamOps* pBeamOp, long lHoleID, CString& sPunchMsg, CString& sRetainedComment, long& nPreviousHoleType, CString& sDefaultPunch);
	void TrapNonStandardHoles(LPCTSTR lpszOpDef);
public:
	void SetSPCode(LPCTSTR sSPC){m_sSPC = sSPC;};
	CString GetSPCode(){return this->m_sSPC;};

	void SetComment(LPCTSTR	sComment){m_sComment = sComment;};
	CString GetComment(){return this->m_sComment;};

	void SetBundle(int nBdlQty){m_nBdlQty = nBdlQty;};
	int GetBundle(){return this->m_nBdlQty;};

	void SetLength(int nOLength){m_nOLength = nOLength;};
	int GetLength(){return this->m_nOLength;};

	void SetSpan1(int nSpan1){m_nSpan1 = nSpan1;};
	int GetSpan1(){return m_nSpan1;};

	void SetSpan2(int nSpan2){m_nSpan2 = nSpan2;};
	int GetSpan2(){return m_nSpan2;};

	void SetSpan3(int nSpan3){m_nSpan3 = nSpan3;};
	int GetSpan3(){return m_nSpan3;};

	void SetOHang1(int nOHang1){m_nOHang1 = nOHang1;};
	int GetOHang1(){return m_nOHang1;};

	void SetOHang2(int nOHang2){m_nOHang2 = nOHang2;};
	int GetOHang2(){return m_nOHang2;};

	void SetEBSlope(int nSlope){m_nSlope = nSlope;};
	int GetEBSlope(){return m_nSlope;};

	void SetCol1(int nCol1){m_nCol1 = nCol1;};
	int GetCol1(){return m_nCol1;};

	void SetCol2(int nCol2){m_nCol2 = nCol2;};
	int GetCol2(){return m_nCol2;};

	void SetMemberType(int nType){m_nType = nType;};
	int GetMemberType(){return m_nType;};

	void ProcessGridInput(CBeamDlg* pDlg);

	bool GotValidScript(/*CItem* pItem,*/ /*CDaoDatabase* m_pDB*/);
	
	bool ProcessScript(/*CItem* pItem,*/ /*CDaoDatabase* m_pDB*/);
	bool GetNonStandardFlag(){return m_bIsNonStandardHole;};
	bool SortOpsByHolePosition();

	void GetBeam(CBeamDlg*		pDlg,
				 int			&nElementID,
				 int			&nQty,
				 CString		&sMark,
				 CString		&sSPC,
				 CString		&sComment,
				 int			&nBdlQty,
				 int			&nOLength,
				 int			&nSpan1,
				 int			&nSpan2,
				 int			&nSpan3,
				 int			&nOHang1,
				 int			&nOHang2,
				 int			&nCol1,
				 int			&nCol2,
				 int			&nSlope,
				 int			&nType);
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CAccessoryElement Class Declaration
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAccessoryElement : public CElement  
{
	DECLARE_SERIAL(CAccessoryElement)

protected:
	CString		m_sComment;			// Free text entered by user
	int			m_nBdlQty;			// Number of parts in bundle
	int			m_nType;			// Member type = 5 (accessories)
	short		m_iField[5];		// Data field array
	int			m_iSleeveLength;	// Length of accessory

	CTypedPtrList<CObList, CAccOps*>	m_tplOpList;	//	pointer to data 'script' for accessory definition,
														//		e.g. length, dimA, dimB, etc.
														//		the data required varies for each accessory product ID
														//		each type will need a handler to manipulate the data
														//		into valid chunks
public:
	CAccessoryElement();
	virtual ~CAccessoryElement();
	virtual void Serialize(CArchive &ar);

	void SetComment(LPCTSTR	sComment){m_sComment = sComment;};
	CString GetComment(){return this->m_sComment;};

	void SetBundle(int nBdlQty){m_nBdlQty = nBdlQty;};
	int GetBundle(){return this->m_nBdlQty;};

	void SetType(int nType){m_nType = nType;};
	int GetType(){return this->m_nType;};

	void SetField1( short i )	{ this->m_iField[0] =i; }
	short GetField1( void ) 	{ return this->m_iField[0]; }	

	void SetField2( short i )	{ this->m_iField[1] =i; }
	short GetField2( void ) 	{ return this->m_iField[1]; }	

	void SetField3( short i )	{ this->m_iField[2] =i; }
	short GetField3( void ) 	{ return this->m_iField[2]; }	
	
	void SetField4( short i )	{ this->m_iField[3] =i; }
	short GetField4( void ) 	{ return this->m_iField[3]; }	
	
	void SetField5( short i )	{ this->m_iField[4] =i; }
	short GetField5( void ) 	{ return this->m_iField[4]; }
	
	void SetLength( int i )	{ m_iSleeveLength = i; }
	short GetLength( void ) 	{ return m_iSleeveLength; }

};

#endif // !defined(AFX_ELEMENT_H__E54C5C61_27BF_11D3_A15C_0060082A2F7E__INCLUDED_)
