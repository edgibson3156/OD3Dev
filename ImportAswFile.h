// ImportAswFile.h: interface for the CImportAswFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTASWFILE_H__B51EFA13_81B6_4840_9583_364B67FCF6E1__INCLUDED_)
#define AFX_IMPORTASWFILE_H__B51EFA13_81B6_4840_9583_364B67FCF6E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OD3Doc.h"
#include "DaoProductCode.h"

/************** Data storage for importing ASW file data ******************/
/**************************************************************************/
class CImpAswDataHole : public CObject  
{
public:
	CImpAswDataHole();
	virtual ~CImpAswDataHole();

//protected:
	CString m_sPunchCode;
	int		m_iPos;
	
};

class CImpAswDataAcc : public CObject  
{
public:
	CImpAswDataAcc();
	virtual ~CImpAswDataAcc();

//protected:
	CString m_sProduct;
	int		m_iQuantity;
	
};

class CImpAswData : public CObject  
{
public:
	CImpAswData();
	virtual ~CImpAswData();

//protected:
	CString m_sMark;
	CString	m_sProduct;
	int		m_iPunchCount;
	int		m_iQuantity;
	int		m_iLength;
	
	// List pointers
	CTypedPtrList<CObList, CImpAswDataHole*> m_tplDataHoles;	// List pointer to imported holes
};
/**************************************************************************/
/**************************************************************************/


/****************** Main ASW file reading class ***************************/
class CImportAswFile : public CObject  
{
public:
	bool importFile(void);
	CImportAswFile(COD3Doc *document);
	virtual ~CImportAswFile();

protected:
	void		splitMark(CString mark);
	CImpAswData	*storeHoles(CString lineData, CImpAswData *beamData, CStdioFile *file, int *res);
	int			storeBeamLength(CString lineData, CImpAswData *beamData);
	int			storeMatName(CString lineData, CImpAswData *beamData);
	int			storeQuantity(CString lineData, CImpAswData *beamData);
	void		addHoles(CBeamElement *pElement, CImpAswData *data);
	void		addElement(CItem *pItem, CImpAswData *data);
	CItem		*testDuplicate(CDaoProductCode *code);
	void		createDocItems(void);
	void		createHole(CString data, CString punch, CImpAswData *pBeam);
	bool		storeBeamData(CStdioFile *file);
	bool		storeUserData(CString lineData, int eof, CStdioFile *file);
	bool		fileRead(CStdioFile *file);
	int			isSwageFile(CStdioFile *file);
	int			isWernik(void){if(m_iIsWernik==IDYES)return(true);else return(false);};
	
	/* File compare strings *********************************/
	// Customer details
	CString m_sCname;
	CString m_sOrder;
	CString m_sCount;
	CString m_sBeam;

	// For items //
	CString m_sMark;
	CString m_sLenPunch;
	CString m_sLenNoPunch;
	CString m_sBeamType;
	CString m_sQuantity;
	CString m_sComment;

	// For holes //
	CString m_sRound;
	CString m_sSquare;
	CString m_sFlange;
	CString m_sFour;
	CString m_sTop;
	CString m_sBottom;
	CString m_sTopFlange;
	CString m_sBottomFlange;
	CString	m_sCutMark;

	CString m_sAccessory;
	/*********************************************************/
	
	COD3Doc	*m_pDoc;			// Pointer to current document
	CString m_sCustName;		// String customer name
	CString m_sOrderNum;		// String order number
	CString	m_sOrderComment;	// Extra comments
	int		m_iBeamCount;		// Total beam count
	int		m_iPosBeam;			// Point in file where beams start
	int		m_iPosAcc;			// Point in file where accessories start

	int			 m_fullLength;		// Beam full length (sub beams)
	int			 m_startOffset;		// Incrementor (sub beams)
	int			 m_beamRemain;		// Remaining length (sub beams)
	CStringArray m_sMarkSplit;		// Marks (sub beams)
	int			 m_iMarkSplit;		// Marks count (sub beams)
	int			 m_iMarkSplitInc;	// Marks incrementor (sub beams)
	CString		 m_sStoreFirstMark;	// First mark store
	int			 m_iIsWernik;		// Is this swagebeam a type Wernik

	// List pointer
	CTypedPtrList<CObList, CImpAswData*> m_tplDataList;	  // List pointer to imported file data
	CTypedPtrList<CObList, CImpAswDataAcc*> m_tplDataAcc; // List pointer to imported accessories
	
};
/**************************************************************************/


#endif // !defined(AFX_IMPORTASWFILE_H__B51EFA13_81B6_4840_9583_364B67FCF6E1__INCLUDED_)
