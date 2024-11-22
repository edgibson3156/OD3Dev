// Element.cpp: implementation of the CElement class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "stdlib.h"
#include "OD3.h"
#include "MainFrm.h"
#include "Element.h"
#include "BeamDlg.h"
#include "OD3Doc.h"
#include "Scripts.h"
#include "BeamOps.h"
#include "PunchValue.h"
#include "DaoDimValue.h"
#include "Hole.h"
#include "od3gridctrl.h"
#include "ProductMods.h"
//#include "SysConfig.h"	// imported from jbs

// Added for use of std math function
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------
// Global objects 
// declared in mainfrm.cpp
//---------------------------------------------------------
#include "Line1.h"
extern CLine1 Line1;

//////////////////////////////////////////////////////////////////////
// Class CElement Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL (CElement, CObject, 0)

CElement::CElement()
{
	int		m_nElementID = 0;		//  internal reference ID (volatile - reset each time a beam element is added to the item's element list
	int		m_nQty		 = 0;
	CString	m_sMark		 = _T("");	//  customer defined reference number
	CString	m_sSection	 = _T("");	//	section type = leftmost 5 chars of product ID
	CString	m_sGauge	 = _T("");	//	gauge of the material in millimetres

	m_pDoc = NULL;
	m_pItem = NULL;

	m_hitTwo=m_extraFeed=m_hitThree = 0.0L;
}

CElement::~CElement()
{

}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
void CElement::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_nElementID;
		ar << m_nQty;
		ar << m_sMark;
		ar << m_sSection;
		ar << m_sGauge;
	}
	else
	{
		ar >> m_nElementID;
		ar >> m_nQty;
		ar >> m_sMark;
		ar >> m_sSection;
		ar >> m_sGauge;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class CBeamElement
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBeamElement,CElement,0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBeamElement::CBeamElement()
{
	// Archived variables
	CString			m_sSPC			= _T("");	//	standard part code as defined in OD3 database
	CString			m_sComment		= _T("");	//	free text entered by user (may be null)
	int				m_nBdlQty		= 0;		//  number of parts in a bundle irrespective of Mark No
	int				m_nOLength		= 0;		//	overall length of beam
	int				m_nSpan1		= 0;		//	span1 dimension in millimetres (may be null)
	int				m_nSpan2		= 0;		//	span2 dimension in millimetres (may be null)
	int				m_nSpan3		= 0;		//	span3 dimension in millimetres (may be null)
	int				m_nOHang1		= 0;		//	overhang1 dimension in millimetres (may be null)
	int				m_nOHang2		= 0;		//	overhang2 dimension in millimetres (may be null)
	int				m_nCol1			= 0;		//	Column1 flange width dimension in millimetres (may be null)
	int				m_nCol2			= 0;		//	Column2 flange width dimension in millimetres (may be null)
	int				m_nSlope		= 0;		//	slope of top flange (applies to eaves beams only - may be null)
	int				m_nType			= 0;		//	member type = 1 (purlin) or 2 (rail)

	// Non-archived Validation variables
	
	CString			m_sProdLine		= _T("");
	long			m_OpScriptID	= 0;
	int				m_nProdLine		= 0;
	int				m_nHits			= 0;
	bool			m_bIgnoreMesage = false;

	// Set to standard punch outputs
	m_extra = false;
}

CBeamElement::~CBeamElement()
{
	CBeamOps*	pBeamOp;
	CBeamOps*	pScript;
	CHole*		pHit;
	POSITION	pos;
	
	pos = m_tplAddList.GetHeadPosition();
	while (pos)	
	{
		pBeamOp = m_tplAddList.GetNext(pos);
		delete pBeamOp;
	}
	m_tplAddList.RemoveAll();
	pos = m_tplScriptList.GetHeadPosition();
	while(pos)
	{
		pScript = m_tplScriptList.GetNext(pos);
		delete pScript;
	}
	m_tplScriptList.RemoveAll();

	pos = m_tplHitList.GetHeadPosition();
	while(pos)
	{
		pHit = m_tplHitList.GetNext(pos);
		delete pHit;
	}
	m_tplHitList.RemoveAll();

	pos = m_tplPrintHitList.GetHeadPosition();

	while(pos)
	{
		pHit = m_tplPrintHitList.GetNext(pos);
		delete pHit;
	}
	m_tplPrintHitList.RemoveAll();

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UpdateBeam()	A functon to update a CBeamElement object with data gathered from the modeless dialog box
//				
//				
void CBeamElement::UpdateBeam(CBeamDlg* pDlg)
{
	// get data from dialog
	this->m_nElementID	= pDlg->m_cBeamCounter;
	this->m_nQty		= pDlg->m_editQty;
	this->m_sMark		= pDlg->m_editMarkNo;
	this->m_sSPC		= pDlg->m_editSPC;
	this->m_nBdlQty		= pDlg->m_editBundleCount;
	this->m_nOLength	= pDlg->m_editLength;
	this->m_nSpan1		= pDlg->m_editSpan1;
	this->m_nSpan2		= pDlg->m_editSpan2;
	this->m_nSpan3		= pDlg->m_editSpan3;
	this->m_nOHang1		= pDlg->m_editOHang1;
	this->m_nOHang2		= pDlg->m_editOHang2;
//	this->m_nCol1		= pDlg->m_editCol1;
//	this->m_nCol2		= pDlg->m_editCol2;
	this->m_nSlope		= pDlg->m_editEBSlope;
	this->m_nType		= pDlg->m_nMemberType; 

	// Process Grid Input
	this->ProcessGridInput(pDlg);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// GetBeam()	An access functon to retrieve private member data. (does not return grid data)
//				
void CBeamElement::GetBeam( CBeamDlg*	pDlg,
							int&		nElementID,
							int&		nQty,
							CString&	sMark,
							CString&	sSPC,
							CString&	sComment,
							int&		nBdlQty,
							int&		nOLength,
							int&		nSpan1,
							int&		nSpan2,
							int&		nSpan3,
							int&		nOHang1,
							int&		nOHang2,
							int&		nCol1,
							int&		nCol2,
							int&		nSlope,
							int&		nType
						  )
{
	nElementID	= this->m_nElementID;
	nQty		= this->m_nQty;
	sMark		= this->m_sMark;
	sSPC		= this->m_sSPC;
	sComment	= this->m_sComment;
	nBdlQty		= this->m_nBdlQty;
	nOLength	= this->m_nOLength;
	nSpan1		= this->m_nSpan1;
	nSpan2		= this->m_nSpan2;
	nSpan3		= this->m_nSpan3;
	nOHang1		= this->m_nOHang1;
	nOHang2		= this->m_nOHang2;
	nCol1		= this->m_nCol1;
	nCol2		= this->m_nCol2;
	nSlope		= this->m_nSlope;
	nType		= this->m_nType;
}

/////////////////////////////////////////////////////////////
// FindBeamByElementID() A function to return a pointer found in the CItem m_tplElementList.
//			 to a specified CBeam object. If beam doesn't exist it will be created. 

CBeamElement* CBeamElement::FindBeamByElementID(/*CItem* pItem,*/ int& nElementID)
{			
	CBeamElement*	pListedBeam;
	POSITION pos;
	
	pos = this->m_pItem->m_tplElementList.GetHeadPosition();
	while(pos)
	{
		pListedBeam = (CBeamElement*)m_pItem->m_tplElementList.GetNext(pos);	// so get pointer to each beam in list ...
		if(pListedBeam->GetElementID() == nElementID)							// ... and look for a matching ID ...
		{
			return pListedBeam;												// ... found one, so return its address.
		}
	}

	//	either list is empty or no match was found ...
	//  so create a new beam, and return its address.
	CBeamElement* pNewBeam = new CBeamElement;			
	pNewBeam->m_pItem = this->m_pItem;
	return pNewBeam;									
} 

void CBeamElement::Serialize(CArchive &ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_sSPC;
		ar << m_sComment;
		ar << m_nBdlQty;
		ar << m_nOLength;
		ar << m_nSpan1;
		ar << m_nSpan2;
		ar << m_nSpan3;
		ar << m_nOHang1;
		ar << m_nOHang2;
		ar << m_nCol1;
		ar << m_nCol2;
		ar << m_nSlope;
		ar << m_nType;
	}
	else
	{
		ar >> m_sSPC;
		ar >> m_sComment;
		ar >> m_nBdlQty;
		ar >> m_nOLength;
		ar >> m_nSpan1;
		ar >> m_nSpan2;
		ar >> m_nSpan3;
		ar >> m_nOHang1;
		ar >> m_nOHang2;
		ar >> m_nCol1;
		ar >> m_nCol2;
		ar >> m_nSlope;
		ar >> m_nType;
	}
	m_tplAddList.Serialize(ar);
}

//////////////////////////////////////////////////////////
// GotValidScript()
//
bool CBeamElement::GotValidScript(/*CItem* pItem,*/ /*CDaoDatabase* m_pDB*/)
{
	CDaoDatabase	*pDB = this->m_pDoc->GetProjectSettings()->m_pDB;
	POSITION		pos;
	CBeamOps		*pOps=NULL;


	// Remove any un-wanted beam ops (remain after a generation failure)
	pos = m_tplScriptList.GetHeadPosition();

	while(pos)
	{
		pOps = m_tplScriptList.GetNext(pos);
		delete pOps;
	}

	if(m_tplScriptList.GetCount())
	{
		// Remove ops pointer list
		m_tplScriptList.RemoveAll();
		// Remove created holes
		DeleteHits();
	}


	// Create a new dynaset from the SelectOpScriptbyLineSecSPC Query
	CScripts* m_pScript = new CScripts(pDB);

	m_pScript->m_Line_Ident =  this->m_pItem->GetProdLineLabel();
	if (m_pScript->m_Line_Ident == _T(""))
	{
		AfxMessageBox("Production Line not set");
		return false;
	}
	m_pScript->m_Section_Ident = this->m_pItem->GetSectionID();
	m_pScript->m_SPC_Ident = this->m_sSPC;

	// Open recordset
	m_pScript->Open();

	this->m_OpScriptID = m_pScript->m_Op_Script_ID;

	while (!m_pScript->IsEOF())
	{
		CBeamOps* pBeamOp = new CBeamOps();

		CString	szMsg = "Item No.";
		CString sItemID;
		sItemID.Format("%d",this->m_pItem->GetItemID());
		szMsg += sItemID;
		CElement* pElement = (CElement*)this;
		CString szMark = pElement->GetMark();

///*
#if 0
		if(szMark == "R42")
		{
			szMsg += ": Mark No. ";
			szMsg += szMark;
			CString szSection = m_pScript->m_Section_Ident;
			CString szSPC = m_pScript->m_SPC_Ident;
			szMsg += "\n Section: ";
			szMsg += szSection;
			szMsg += " SPC = ";
			szMsg += szSPC;
			szMsg += " : Op Sequence ID ";
			CString szHit = _T("");
			szHit.Format("%d",(m_pScript->m_Operation_Sequence_No));
			szMsg += szHit;
			szMsg += "\nCBeamOps object @ ";
			CString szPointer = _T("");
			szPointer.Format("%p",pBeamOp);
			szMsg += szPointer;
			szMsg += "\n\nScript: ";
			CString szScript = _T("");
			szScript.Format("%.6li",m_pScript->m_Op_Script_ID);
			szMsg += szScript;
			AfxMessageBox(szMsg);
		}
#endif
//*/
		pBeamOp->SetScriptID(m_pScript->m_Op_Script_ID);
		pBeamOp->SetOpSeqID(m_pScript->m_Operation_Sequence_No);			// ... set the Line variable ...

		pBeamOp->SetAbsolute(false);
		if(m_pScript->m_Absolute != FALSE){pBeamOp->SetAbsolute(true);}		// ... set the Section variable ...

		pBeamOp->SetPositive(false);
		if(m_pScript->m_Positive != FALSE){pBeamOp->SetPositive(true);}		// ... set the SPC variable ...

		pBeamOp->SetMultiplied(false);
		if(m_pScript->m_Multiplied != FALSE){pBeamOp->SetMultiplied(true);}	// ... set the Script ID variable ...

		pBeamOp->SetMultiplier(m_pScript->m_MultiplierValue);				// ... set the Script ID variable ...
		pBeamOp->SetOpType(m_pScript->m_Operation_Type);					// ... set the Script ID variable ...
		pBeamOp->SetOperation(m_pScript->m_Operation_Code);					// ... set the Script ID variable ...

//	VHF TODO:  Add to list in OpSeqID order
		this->m_tplScriptList.AddTail(pBeamOp);								// ... and add it to the list.
	
		m_pScript->MoveNext();												// ... Now get next record.
	}
	m_pScript->Close();
	delete(m_pScript);

	if (m_tplScriptList.IsEmpty()){return false;}
	else {return true;}

}

/////////10////////20////////30////////40////////50////////60////////70////////80////////90////////100///////110///////120///////130
// ProcessScript() A function convert script operations into real world values.
//
bool CBeamElement::ProcessScript(/*CItem* pItem,*//* CDaoDatabase* m_pDB*/)
{
	
	CBeamOps*		pBeamOp;
	POSITION		pos;
	UINT			nList;
	bool			bProcessExtra = false;
	int				cOpCounter = 0;
	int				nOps;
	int				nSeq;
	double			nFeed = 0;
	double			nPunchValue = 0;
	CString			sRetainedComment;
	long			nPreviousHoleType;
	CBeamElement	*pBeam = (CBeamElement*)this;

	// Set class member flag for standard hashcodes
	m_extra=bProcessExtra;

	this->m_bIsNonStandardHole = false;
	this->m_pItem->SetNonStandardFlag(false);
	this->m_nHits = 0;


	CElement* pElement = (CElement*)this;
	CString szMark = pElement->GetMark();
	CString sItemID;
	CString szMsg;
	int nItemID = this->m_pItem->GetItemID();
	sItemID.Format("%d",nItemID);

	LPCTSTR lpszText = _T("");

process:
	if(!bProcessExtra){nList=SCRIPT;}else{nList=EXTRA;}
	switch (nList)
	{
	case SCRIPT:										// Process the standard holes defined by the SPC script

#ifdef _DEBUG
		szMsg = "Item No. ";
		szMsg += sItemID;
		szMsg += ": Processing mark ";
		szMsg += szMark;
		lpszText = (LPCTSTR)szMsg;
		this->UpdateStatusBar(lpszText);
#endif
		
		pos = this->m_tplScriptList.GetHeadPosition();
		nOps = this->m_tplScriptList.GetCount();
		for (nSeq = 1; nSeq <= nOps; ++nSeq)			// Make sure we get all Ops in sequence
		{
			while (pos)									// Keep scanning until the end of list
			{
				pBeamOp = m_tplScriptList.GetNext(pos);

				if (pBeamOp->GetOpSeqID() != nSeq)		// Search for nth operation
				{}										// ... loop if not in sequence
				else
				{
					ProcessOperation(/*m_nHits,*/ nFeed, nPunchValue, sRetainedComment, nPreviousHoleType, /*pItem,*/ pBeamOp, /*m_pDB,*/ nList);
					this->UpdateProgressIndicator(++cOpCounter);
					break;
				}
			}
		}
		m_extra=bProcessExtra = true;
		goto process;
		break;
	case EXTRA:											// Process any non-standard holes entered into 'grid'


#ifdef _DEBUG

		szMsg = "Item No. ";
		szMsg += sItemID;
		szMsg += ": Processing Extra Holes for mark ";
		szMsg += szMark;
		lpszText = (LPCTSTR)szMsg;
		this->UpdateStatusBar(lpszText);
#endif		

		pos = this->m_tplAddList.GetHeadPosition();
		nOps = this->m_tplAddList.GetCount();

		for (nSeq = 1; nSeq <= nOps; ++nSeq)			// Make sure we get all Ops in sequence
		{
			while (pos)									// Keep scanning until the end of list
			{
				pBeamOp = m_tplAddList.GetNext(pos);

				if (pBeamOp->GetOpSeqID() != nSeq)		// Search for nth operation
				{}										// ... loop if not in sequence
				else
				{
					this->ProcessOperation(/*nHits,*/ nFeed, nPunchValue, sRetainedComment, nPreviousHoleType, /*pItem,*/ pBeamOp, /*m_pDB,*/ nList);

					if (this->m_bIsNonStandardHole != false)
					{
						this->m_pItem->SetNonStandardFlag(true);
						return false;
					}
					this->UpdateProgressIndicator(++cOpCounter);
					break;
				}
			}
		}
		break;
	}
//	we should now have processed all standard operations defined in the script
//	and all the non-standard holes defined by user input to the grid

//  now need to deal with beginning and end of part terminators - these vary with prodline

	CString sPunch = _T("");
	LPCTSTR lpszPunch = (LPCTSTR)sPunch;
	bool bFirstLastFlag = true;
	switch (m_pItem->GetProdLine())
	{
	case LINE_1:
		nFeed = 0;
		nPunchValue = 1;
		this->CreateHole(nFeed, lpszPunch, nPunchValue, bFirstLastFlag);
		nFeed = this->GetLength();
		nPunchValue = 1;
		this->CreateHole( nFeed, lpszPunch, nPunchValue, bFirstLastFlag);
		break;
	case LINE_2:
		nFeed = 32;
		nPunchValue = 256;
		this->CreateHole( nFeed, lpszPunch, nPunchValue, bFirstLastFlag);
		nFeed = this->GetLength();
		nPunchValue = 0;
		this->CreateHole( nFeed, lpszPunch, nPunchValue, bFirstLastFlag);
		break;
	case LINE_3:
		nFeed = 32;
		nPunchValue = 1;
		this->CreateHole( nFeed, lpszPunch, nPunchValue, bFirstLastFlag);
		nFeed = this->GetLength();
		nPunchValue = 0;
		this->CreateHole( nFeed, lpszPunch, nPunchValue, bFirstLastFlag);

		// Test if the section is an ASF that needs services holes
		if(m_pItem && m_pItem->GetType() == 9)
		{
			// Generate service holes at 610mm centres
			if(!createASFServiceHoles())
			{
				if(!GetComment().Compare("Service Holes"))
				{
					// Failed to create service holes
					szMsg.Format(IDS_NOSERVICEFAULT, m_pItem->GetItemID(), pBeam->GetMark());
					AfxMessageBox(szMsg, MB_OK|MB_ICONINFORMATION);
				}
			}
		}
		break;
	default:
		AfxMessageBox("Oops! shouldn't be here -  No Line specified");
		return false;
	}
	bFirstLastFlag = false;
	

	// now we've got them all they need sorting by ascending position.
	this->SortOpsByHolePosition();
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
void CBeamElement::ReversePunching(/*CItem* pItem,*/ double& nFeed, LPCTSTR lpszPunch, double& nPunchValue)
{
	int nOverallLength = this->GetLength();
	CString sPunch = (CString)lpszPunch;
	
	switch (this->m_pItem->GetProdLine())
	{
	case LINE_1:
		if( sPunch==("D") || sPunch==("E") || sPunch==("W") )
		{
			nFeed = ( nOverallLength-nFeed-100 );
		}
		else if( sPunch ==("A") && nFeed == 47 /* sPunch!=("#3") && sPunch!=("L") &&  sPunch!=("#2")*/ )
		{
			nFeed = ( nOverallLength-nFeed );
			nPunchValue = 10;		// "L"
		}
		else if( sPunch ==("#3") && nFeed == 47)
		{
			nFeed = ( nOverallLength-nFeed );
			nPunchValue = 2;
		}
		else if( sPunch ==("L") && nFeed == (nOverallLength - 47))
		{
			nFeed = ( nOverallLength-nFeed );
			nPunchValue = 20;	// "A"
		}
		else if( sPunch ==("#2") && nFeed == (nOverallLength - 47))
		{
			nFeed = ( nOverallLength-nFeed );
			nPunchValue = 4;
		}
		else
		{
			nFeed = ( nOverallLength-nFeed );
		}
		break;

#if 0 // No requirement
	case LINE_3:
		if( sPunch==("W") || /*sPunch==("#13") ||*/ sPunch==("#14") )
		{
			nFeed = ( nOverallLength-nFeed-100 );
		}
		else
		{
			nFeed = ( nOverallLength-nFeed );
		}
		break;
#endif

	default:
		nFeed = ( nOverallLength-nFeed );
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreateHole()			A function to create a CHole object from supplied feed and punch data 
//
void CBeamElement::CreateHole(double nFeed, LPCTSTR lpszPunch, double nPunchValue, bool bFirstLastFlag)
{
	CHole* pHit = new CHole();
	
	double nTempFeed = nFeed;	

	// Increment punch hits
	m_nHits++;

	if(!bFirstLastFlag)
	{
		// now fix reverse punching for membertype 2
		if (this->GetMemberType() != 1 && this->GetMemberType() != 8 && this->GetMemberType() != 7)
		{
			this->ReversePunching(/*pItem,*/ nFeed, lpszPunch, nPunchValue);
		}

		// now check that position value is legal
		if( !this->CheckLegalPosition(/*pItem,*/ /*nHits,*/ nFeed) )
		{
			this->DeleteHits();
			return;
		}
	}

	pHit->SetPosX((int)(nFeed+0.5L));
	//pHit->SetPosY(nOffset);
	pHit->SetPunch((long)nPunchValue);
	this->m_tplHitList.AddTail(pHit);


	// Restore feed value
	nFeed = nTempFeed;

	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// DeleteHits()			A function to delete CHole objects and remove from the HitList 
//						This function is called if a non standard requirement is encountered
//						that requires the user to over-ride entries in the BeamDialog 'grid'
//						That event causes an interruption of the generation process that must be
//						restarted after modifications have been made.  This function cleans up the
//						partially created HitList to avoid duplicated output.
//
void CBeamElement::DeleteHits()
{
	POSITION pos;
	CHole* pHit;

	pos = this->m_tplHitList.GetHeadPosition();

	while (pos)
	{
		pHit = this->m_tplHitList.GetNext(pos);
		delete pHit;
	}
	this->m_tplHitList.RemoveAll();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProcessOperation()	A function to analyse CBeamOp variables and create new CHole objects
//						take as arguments:
//	not required					int& nHits - a ref to the number of Hits previously created,
//						double& nFeed - a ref to the feed position for the current operation
//						double& nPunchValue - a ref to the punch value for the current operation
//
//						CItem* pItem - a pointer to the item containing this beam element
//						CBeamOps* pBeamOp - a pointer to the current hole definition operation
//						CDaoDatabase* m_pDB - a pointer to the connected OD3 data source
//
void CBeamElement::ProcessOperation(double& nFeed, double& nPunchValue, CString& sRetainedComment, long& nPreviousHoleType, CBeamOps* pBeamOp, UINT nList)
{
	CDaoDatabase* pDB	= this->m_pDoc->GetProjectSettings()->m_pDB;

	int nItemID = this->m_pItem->GetItemID();
	int nElementID = this->m_nElementID - (nItemID * 1000);

	CElement* pElement	= (CElement*)this;
	CString szMark = pElement->GetMark();

	CString sSectionID = this->m_pItem->GetSectionID();

	int		nMultiplier = pBeamOp->GetMultiplier();
	CString sOpType		= pBeamOp->GetOpType();
	CString sOpDef		= pBeamOp->GetOperation();
	CString sComment	= pBeamOp->GetComment();
	bool	bIsCSunk	= pBeamOp->GetCSunk();

	CString	sPunch		= _T("");
	CString	sDim		= _T("");
	CString	sDefaultPunch		= _T("");
	CString szMsg		= _T("");
	CString sItemID		= _T("");
	sItemID.Format("%d",nItemID);

	LPCTSTR lpszPunch	= (LPCTSTR)sPunch;
	LPCTSTR lpszOpDef	= (LPCTSTR)sOpDef;
	LPCTSTR lpszComment = (LPCTSTR)sComment;

	// For line and part testing
	CString lineIdent	= this->m_pItem->GetProdLineLabel();
	CString sectionID	= this->m_pItem->GetSectionID();
	int		partCode,i	= 0;
	CString punchCode;
	CString warnMsg;


	double	nDim;
	long lHoleID	= 0;
	int nLineID		= 0;

	// Processing for "Punch" OpType
	if (sOpType == _T("Punch"))
	{		
		//	special processing to convert D3 'Extra hole' descriptions to Alpha punch code
		if (sOpDef.GetLength() > 4)
		{
			//	we've got a customer specified additional hole
			CDaoImportedHoles* pD3Hole	= new CDaoImportedHoles(pDB);
			pD3Hole->m_Section_Ident	= this->m_pItem->GetSectionID();
			pD3Hole->m_D3_HoleName		= sOpDef;
				
			pD3Hole->Open();

#ifdef _DEBUG
			if (pD3Hole->GetRecordCount() > 1)
			{
				szMsg = _T("Invalid Data ! \nA single record should be returned");
				AfxMessageBox(szMsg);
			}
#endif				

			nLineID		= m_pItem->GetProdLine();
			lHoleID		= pD3Hole->m_Additional_Hole_ID;
			sPunch		= pD3Hole->m_Punch_Code;
			lpszPunch	= (LPCTSTR)sPunch;
			lpszOpDef	= (LPCTSTR)sOpDef;

		//	First check that hole ID is valid
			if (lHoleID > 1000)
			{
				this->m_bIsNonStandardHole = true;
				this->TrapNonStandardHoles(lpszOpDef);
//				szMsg = this->GetMsgHeader();
//				szMsg += _T("\n\nHole type - ");
//				szMsg += _T("'") + (CString)lpszOpDef + _T("'");
//				szMsg += _T("\n is a non-standard requirement!");
//				AfxMessageBox(szMsg);
//				this->m_pItem->SetFailedBeam(pElement);
//				this->DeleteHits();
				pD3Hole->Close();
				delete(pD3Hole);
				return;
			}

		//  Trap countersunk holes
			if (sSectionID.Find(_T("C"),0) != -1)
			{}
			else if (bIsCSunk == true && this->m_bIgnoreMsg != true)
			{
				szMsg = this->GetMsgHeader();
				szMsg += _T("\n\nHole type - ");
				szMsg += _T("'") + (CString)lpszOpDef + _T("'");
				szMsg += _T("\n is marked as COUNTERSUNK!");
				szMsg += _T("\n\n Click 'YES' to continue processing as NOT countersunk!");
				szMsg += _T("\n\n Click 'Cancel' to continue and suppress further messages for this element");
				szMsg += _T("\n\n Click 'NO' to CHANGE the hole type");

				int iButton = AfxMessageBox(szMsg,MB_ICONWARNING|MB_YESNOCANCEL);

				switch (iButton)
				{
				case IDYES:
					break;
				case IDCANCEL:
					this->m_bIgnoreMsg = true;
					break;
				case IDNO:
					this->m_bIsNonStandardHole = true;
					this->m_pItem->SetFailedBeam(pElement);
					this->DeleteHits();
					pD3Hole->Close();
					delete(pD3Hole);
					return;
				}
			}

		//	Special Routine for Cee Sections and Pressed sections
#if 0
			CString sPunchMsg = _T("");
			bool bDisplayMsg	= false;
			if (sSectionID.Find(_T("C"),0) != -1 || this->m_nType == 8 )
			{
				bDisplayMsg = CheckPunchConflicts(pBeamOp, lHoleID, lpszOpDef, sPunchMsg, sRetainedComment, nPreviousHoleType, sDefaultPunch, szMsg);
				// Display warnings if flag set
				if (bDisplayMsg)
				{
					if(AfxMessageBox(szMsg,MB_ICONWARNING|MB_OKCANCEL)==IDOK)
					{}
					else
					{
						this->m_bIsNonStandardHole = true;
						this->m_pItem->SetFailedBeam(pElement);
						this->DeleteHits();
						pD3Hole->Close();
						delete(pD3Hole);
						return;
					}
				}
			}

#endif
			nPreviousHoleType = lHoleID;
//			sRetainedComment = sComment;
			bool bMultipleHitCase = false;

			// Test line vs product against punch code)
			modifyHoleProcess(lineIdent,sectionID,sPunch, &pD3Hole->m_On_Line);

			
			//	Standard processing for extra holes
			if ( pD3Hole->m_On_Line == TRUE)	
			{
				this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

				//	special processing to deal with trapped invalid ops for Line_2 Zeds
				if (bMultipleHitCase == false && this->m_bIsNonStandardHole == true)
				{

					//				this->m_bIsNonStandardHole = true;
					this->TrapNonStandardHoles(lpszOpDef);
//					szMsg = this->GetMsgHeader();
//					szMsg += _T("\n\nHole type - ");
//					szMsg += _T("'") + (CString)lpszOpDef + _T("'");
//					szMsg += _T("\n is a non-standard requirement!");
//					AfxMessageBox(szMsg);
//					this->m_pItem->SetFailedBeam(pElement);
//					this->DeleteHits();
					pD3Hole->Close();
					delete(pD3Hole);
					return;	
				}	
			}
			else if (pD3Hole->m_On_Line != TRUE && m_bIsNonStandardHole == false)
			{
			//  Special processing for multiple hit cases before calling non-standard message box
				int i = 0;
				double nDatum = nFeed;

				switch (lHoleID)
				{
				// 14 Dia slot (H code)
				case 17:
					// Test line and paroduct (Zeds)
					if(lineIdent == _T("Line_3" && getPart(sectionID)==IDS_PART4))
					{
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					else if(lineIdent == _T("Line_2" && getPart(sectionID)==IDS_PART4))
					{
						nFeed-=13;
						// Use Square holes to punch slot
						for(i=0; i<3; i++)
						{
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							nFeed+=13;
						}
						nFeed=nDatum;
					}
					else if(lineIdent.CompareNoCase(_T("Line_2")))
					{
						// Not trapped for line 1
						warnMsg.Format(IDS_PUNCH_FAIL,m_pItem->GetItemID(),m_sMark,lpszPunch,lHoleID,nFeed);
						AfxMessageBox(warnMsg,MB_ICONERROR);
					}
					break;

				case 68:	/* == "14dia x1 on centre line"*/
					lpszPunch = (LPCTSTR)_T("N");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					bMultipleHitCase = false;
					break;
				case 78:	/* == "2x 14dia at 100c/cs on centre line"*/
					if(getPart(sectionID) == IDS_PART3)
					{
						// For Cee section on line2
						nFeed -= 50;
						lpszPunch = (LPCTSTR)_T("N");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						nFeed += 100;
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
						
					}
					else
					{
						nFeed = nFeed-50;
						lpszPunch = (LPCTSTR)_T("U");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

						if(bMultipleHitCase == true)
						{
							nFeed = nFeed+100;
							lpszPunch = (LPCTSTR)_T("N");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							bMultipleHitCase = false;
						}
					}
					break;
				case 79:	/* == "2x 14dia x2 at 100c/c on gauge lines"*/
					nFeed = nFeed-50;
					lpszPunch = (LPCTSTR)_T("K");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

					if(bMultipleHitCase == true)
					{
						nFeed = nFeed+100;
						lpszPunch = (LPCTSTR)_T("F");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
					}
					break;
				case 80:	/* == "2x 18dia at 100c/c on centre line"*/
					if((lineIdent == _T("Line_2") || lineIdent == _T("Line_3")) && (getPart(sectionID)==IDS_PART3))
					{
						/********************** Cee section on line 2/3 ***************************/
						// Move feed
						nFeed -= 50;
						// Swap punch code
						lpszPunch = (LPCTSTR)_T("C");
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						// Move feed
						nFeed += 100;
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						// Clean flag
						bMultipleHitCase = false;
						/**************************************************************************/
					}
					else
					{
						nFeed = nFeed-50;
						lpszPunch = (LPCTSTR)_T("E");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

						if(bMultipleHitCase == true)
						{
							nFeed = nFeed+100;
							lpszPunch = (LPCTSTR)_T("C");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							bMultipleHitCase = false;
						}
					}
					break;
				case 81:	/* == "2x 18dia at 100c/c on cleat lines"*/
					nFeed = nFeed-50;
					lpszPunch = (LPCTSTR)_T("E");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

					if(bMultipleHitCase == true)
					{
						nFeed = nFeed+100;
						lpszPunch = (LPCTSTR)_T("C");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
					}
					break;
				case 82:	/* == "2x 18dia x2 at 100c/c on cleat lines"*/
					// Perform line and section test
					if(lineIdent == _T("Line_2") && (getPart(sectionID)==IDS_PART5))
					{
						/********************** Zed section on line 2 *****************************/
						// Move feed
						nFeed = nFeed-50;
						// Set punch
						lpszPunch = (LPCTSTR)_T("D");
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						// Move feed
						nFeed = nFeed+100;	
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						/**************************************************************************/
					}
					else
					{
						nFeed = nFeed-50;
						lpszPunch = (LPCTSTR)_T("D");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

						if(bMultipleHitCase == true)
						{
							nFeed = nFeed+100;
							lpszPunch = (LPCTSTR)_T("A");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							bMultipleHitCase = false;
						}
					}
					break;
				case 83:	/* == "2x 18dia x2 at 100c/cs on gauge lines"*/
					// Perform line and section test
					if(lineIdent == _T("Line_2") && (getPart(sectionID)==IDS_PART3))
					{
						/********************** Cee section on line 2 *****************************/
						// Move feed
						nFeed -= 50;
						// Swap punch code
						lpszPunch = (LPCTSTR)_T("A");
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						// Move feed
						nFeed += 100;
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						// Clean flag
						bMultipleHitCase = false;
						/**************************************************************************/
					}
					else
					{
						nFeed = nFeed-50;
						lpszPunch = (LPCTSTR)_T("D");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

						if(bMultipleHitCase == true)
						{
							nFeed = nFeed+100;
							lpszPunch = (LPCTSTR)_T("A");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							bMultipleHitCase = false;
						}
					}
					break;
				case 84:	/* == "3x 14sqr x2 on cleat lines"*/
					nFeed = nFeed-100;
					for (i = 0; i<3; i++)
					{
						nFeed = nFeed+50;
						lpszPunch = (LPCTSTR)_T("S");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 85:	/* == "4x 14sqr on cleat lines"*/
					nFeed = nDatum-100;
					lpszPunch = (LPCTSTR)_T("X");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					nFeed = nDatum-50;
					lpszPunch = (LPCTSTR)_T("W");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					if(bMultipleHitCase == true)
					{
						nFeed = nFeed+100;
						lpszPunch = (LPCTSTR)_T("X");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
					}
					nFeed = nDatum+100;
					lpszPunch = (LPCTSTR)_T("X");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					break;
				case 86:	// == "18dia x25slot x1 on cleat line" (1/125) 
					// Get the part code
					partCode=getPart(sectionID);
					if (bMultipleHitCase == true || ( !(lineIdent==_T("Line_1"))
														&& partCode>=IDS_PART8 && partCode<=IDS_PART10) )
					{
						nFeed = nFeed-18;
						bMultipleHitCase = false;
						for (i = 0; i<5; i++)
						{
							nFeed = nFeed+6;
							lpszPunch = (LPCTSTR)_T("C");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						}
					}
					else
					{
							lpszPunch = (LPCTSTR)_T("Y");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;

				// Double fixing hole (18 * 25 slot)
				case 87: 
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						lpszPunch = (LPCTSTR)_T("C");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;

				case 88:	// == "18dia x25slot x1 on lower gauge line"
					
					lpszPunch = (LPCTSTR)_T("Z");

					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;

				case 89:	/* == "2x 18dia x2 at 70c/cs on gauge lines"*/
					nFeed = nFeed-35;
					lpszPunch = (LPCTSTR)_T("D");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

					if(bMultipleHitCase == true)
					{
						nFeed = nFeed+70;
						lpszPunch = (LPCTSTR)_T("A");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
					}
					break;
				case 92:  /* == 18dia x25slot x3 on EB cleat lines (EB160)*/
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						lpszPunch = (LPCTSTR)_T("AZ");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 93:  /* == 18dia x25slot x2 on EB cleat lines (EB160)*/
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						lpszPunch = (LPCTSTR)_T("CZ");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 95:  /* == 18dia x25slot x2 in web cleat lines (EB240)*/
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						lpszPunch = (LPCTSTR)_T("QZ");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;

				// Lower slot 14 * 25
				case 98:	
					// Test for line number and product
					if(lineIdent == _T("Line_2") && (partCode=getPart(sectionID)) )
					{
						switch(partCode)
						{
							// ZED's
							case IDS_PART4:
								//nFeed = nFeed-17;
								nFeed -= 13;
#ifdef NOTTEST
								// Get the partnumber
								int pos = sectionID.Find('/');
								CString partName;
								int pNum;

								partName = sectionID.Mid(pos+1, sectionID.GetLength());
								pNum = atoi(partName);

								// Set punch for desired ZED part code
								if(pNum > 155)
									lpszPunch = (LPCTSTR)_T("#11");
								else
									lpszPunch = (LPCTSTR)_T("#11");
#endif

								lpszPunch = (LPCTSTR)_T("#11");
								for (i = 0; i<3; i++)
								{
									// Perform two hits for 25mm slot (using squares instead of round)
									// Line two 14mm dia only //
									this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef,
														sComment, bMultipleHitCase);

									// Move punch pos
									nFeed = nFeed+13;
								}
						}
					}
					else
					{
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef,
														sComment, bMultipleHitCase);
					}
					break;

				case 100:
					// Test for line number and product
					if(lineIdent == _T("Line_2") && (partCode=getPart(sectionID)))
					{
						switch(partCode)
						{
							// ZED's
							case IDS_PART4:
								// Move feed pos
								nFeed -= 13;
#ifdef NOTTEST
								// Get the partnumber
								int pos = sectionID.Find('/');
								CString partName;
								int pNum;

								partName = sectionID.Mid(pos+1, sectionID.GetLength());
								pNum = atoi(partName);

								// Set punch for desired ZED part code
								if(pNum > 155)
									lpszPunch = (LPCTSTR)_T("H");
								else
									lpszPunch = (LPCTSTR)_T("H");
#endif

								lpszPunch = (LPCTSTR)_T("H");
								for (i = 0; i<3; i++)
								{
									// Perform two hits for 25mm slot (using squares instead of round)
									// Line two 14mm dia only //
									this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef,
														sComment, bMultipleHitCase);

									// Move punch pos
									nFeed = nFeed+13;
								}
						}
					}
					else
					{
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef,
														sComment, bMultipleHitCase);
					}
					break;

				case 97:  /* == 18dia x25slot x1 in web cleat line (EB160)*/
				case 151:  /* == 18dia x25slot x1 on centre line (EB160)*/
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						lpszPunch = (LPCTSTR)_T("C");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 104:	/* == "2x 14sqr at 100c/c on cleat lines"*/
					nDatum = nFeed;
					nFeed = nDatum-50;
					lpszPunch = (LPCTSTR)_T("W");

					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

					if(bMultipleHitCase == true)
					{
						nFeed = nFeed+100;
						lpszPunch = (LPCTSTR)_T("X");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
					}
					break;
				case 105:	/* == "2x 14sqr x2 at 100c/c on cleat lines"*/
					nFeed = nFeed-50;
					lpszPunch = (LPCTSTR)_T("S");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					nFeed = nFeed+100;
					lpszPunch = (LPCTSTR)_T("S");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					break;
				case 109:	/* == "14dia x2 on gauge lines" - Line_2 only*/
					lpszPunch = (LPCTSTR)_T("#24");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					bMultipleHitCase = false;
					break;
				case 110:	/* == "14dia on lower gauge line" - Line_2 only*/
					lpszPunch = (LPCTSTR)_T("#16");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					bMultipleHitCase = false;
					break;
				case 111:	/* == "14dia on upper gauge line" - Line_2 only*/
					lpszPunch = (LPCTSTR)_T("#8");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					bMultipleHitCase = false;
					break;
				case 114:	/* == "2x 14dia x2 at 100c/c on gauge lines"*/
					// Perform line and section test
					if((lineIdent == _T("Line_2") || lineIdent == _T("Line_3")) && (getPart(sectionID)==IDS_PART3))
					{
						/********************** Cee section on line 2 *****************************/
						// Move feed
						nFeed -= 50;
						// Swap punch code
						lpszPunch = (LPCTSTR)_T("F");
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						// Move feed
						nFeed += 100;
						// Create hole
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						// Clean flag
						bMultipleHitCase = false;
						/**************************************************************************/
					}
					else
					{
						nFeed = nFeed-50;
						lpszPunch = (LPCTSTR)_T("J");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

						if(bMultipleHitCase == true)
						{
							nFeed = nFeed+100;
							lpszPunch = (LPCTSTR)_T("G");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							bMultipleHitCase = false;
						}
					}
					break;

				// Lower fixing hole (18 * 25 slot)
				case 116:
					nFeed = nFeed-18;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;

				case 117:	// == "18dia x25slot x2 on cleat lines"
					partCode = getPart(sectionID);
					// Perform Line3 test
					// Product Z300 and Zeta 2
					if(lineIdent == _T("Line_3") && partCode == IDS_PART6)
					{
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						break;
					}

					lpszPunch = (LPCTSTR)_T("A");
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 118:	/* == "2x 18dia at 100c/c on centre line"*/
					nFeed = nFeed-50;
					lpszPunch = (LPCTSTR)_T("E");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

					if(bMultipleHitCase == true)
					{
						nFeed = nFeed+100;
						lpszPunch = (LPCTSTR)_T("C");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
					}
					break;
				case 120:	/* == "2x 18dia x2 at 100c/c on cleat lines"*/
					if(getPart(sSectionID) == IDS_PART1)
					{
						nFeed = nFeed-50;
						lpszPunch = (LPCTSTR)_T("D");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

						if(bMultipleHitCase == true)
						{
							nFeed = nFeed+100;
							lpszPunch = (LPCTSTR)_T("D");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							bMultipleHitCase = false;
						}
					}
					else
					{
						nFeed = nFeed-50;
						lpszPunch = (LPCTSTR)_T("D");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);

						if(bMultipleHitCase == true)
						{
							nFeed = nFeed+100;
							lpszPunch = (LPCTSTR)_T("A");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
							bMultipleHitCase = false;
						}
					}
					break;
				case 122:	/* == "2x 14dia x2 at 70c/c on cleat lines"*/
					nFeed = nFeed-105;
					for (i = 0; i<2; i++)
					{
						nFeed = nFeed+70;
						lpszPunch = (LPCTSTR)_T("F");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 123:	/* == "2x 14dia x2 at 100c/c on cleat lines"*/
					nFeed = nFeed-150;
					for (i = 0; i<2; i++)
					{
						nFeed = nFeed+100;
						lpszPunch = (LPCTSTR)_T("F");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 124:	/* == "18dia x25slot x1 on lower gauge line" */
					if( getPart(sectionID)==IDS_PART6)
					{
						lpszPunch = (LPCTSTR)_T("LH");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					else
					{
						nFeed = nFeed-18;
						bMultipleHitCase = false;
						for (i = 0; i<5; i++)
						{
							nFeed = nFeed+6;
							lpszPunch = (LPCTSTR)_T("Z");
							this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						}
					}
					break;
/*				case 125:  // == 14dia Both flanges (Line 2 only - Staggered pair == #128 && #4 (square hole in top flange!!) )
					lpszPunch = (LPCTSTR)_T("#132");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					break;	*/
				case 127:  // == 18dia x25slot x1 on web CL (EB160)
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						lpszPunch = (LPCTSTR)_T("C");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
				case 132:  // == 14dia x25slot in unsheeted flanges (top hats) 
					nFeed = nFeed-18;
					bMultipleHitCase = false;
					for (i = 0; i<5; i++)
					{
						nFeed = nFeed+6;
						lpszPunch = (LPCTSTR)_T("H");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					}
					break;
/*				case 133:  // == 14dia top flange (Line 2 only - #4 (square hole in top flange!!) )
					lpszPunch = (LPCTSTR)_T("#4");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					break;
				case 134:  // == 14dia bottom flange (Line 2 only - #128)
					lpszPunch = (LPCTSTR)_T("#128");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					break;
				case 135:  // == 18dia top flange (Line 2 only - #1 (square hole in top flange!!) )
					lpszPunch = (LPCTSTR)_T("#1");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					break;
				case 136:  // == 18dia bottom flange (Line 2 only - #2)
					lpszPunch = (LPCTSTR)_T("#2");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					break;	
				case 141:	// == "2x 14sqr at 100c/c on centre line"
					nDatum = nFeed;
					nFeed = nDatum-50;
					lpszPunch = (LPCTSTR)_T("W");
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					if(bMultipleHitCase == true)
					{
						nFeed = nFeed+100;
						lpszPunch = (LPCTSTR)_T("X");
						this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
						bMultipleHitCase = false;
					}
					break;	*/
				default:
					// Any codes not trapped
					warnMsg.Format(IDS_PUNCH_FAIL,m_pItem->GetItemID(),m_sMark,lpszPunch,lHoleID,nFeed);
					AfxMessageBox(warnMsg,MB_ICONERROR);
					break;
				}
				nPreviousHoleType = lHoleID;
				sRetainedComment = sComment;
			}
			else	/* i.e. Hole not defined as 'On-Line' in DB and m_bIsNonStandardHole == true */
			{
				this->m_bIsNonStandardHole = true;
				this->TrapNonStandardHoles(lpszOpDef);
//				szMsg = this->GetMsgHeader(/*pItem,*/ /*nHits+1*/);
//				szMsg += _T("\n\n'");
//				szMsg += sOpDef;
//				szMsg += _T("' is a non-standard requirement!");
//				AfxMessageBox(szMsg);
//				this->m_pItem->SetFailedBeam(pElement);
//				this->DeleteHits();
				pD3Hole->Close();
				delete(pD3Hole);
				return;
			}

			pD3Hole->Close();
			delete(pD3Hole);
			
		}
		else
		{
		//	Processing for standard holes	
			punchCode=lpszPunch = lpszOpDef;
			bool	bMultipleHitCase = false;
			double	tmp=nFeed;

			// Get the part code
			partCode=getPart(sectionID);

			// If we get a standard H code we need to loop 3 times
			// to generate a slotted hole, There is no single punch hit for slots 14mm (line2)
			if(partCode == IDS_PART4 && !lineIdent.CompareNoCase(_T("Line_2")) 
				&& !punchCode.CompareNoCase(_T("H")) )
			{
				// For Zed section on line2
				nFeed-=13;
				for(i=0; i<3; i++)
				{
					// Create the new hole
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					// Move the feed pos
					nFeed+=13;
				}
				nFeed=tmp;
			}
			else if((partCode == IDS_PART5 && !lineIdent.CompareNoCase(_T("Line_2")) 
				&& !punchCode.CompareNoCase(_T("D"))) ||
				/* zeta */
				((partCode>=IDS_PART8 && partCode<=IDS_PART10) && 
				lineIdent.CompareNoCase(_T("Line_1") ) && 
				(!punchCode.CompareNoCase( _T("W")) || !punchCode.CompareNoCase(_T("E")))) ||
				/* zeta 200 */
				(partCode==IDS_PART5 && !lineIdent.CompareNoCase(_T("Line_3")) && 
				!punchCode.CompareNoCase( _T("W"))) )
			{
				// Punch code w & e for Zeta1 on line2/3 requires 100 C/L
				// Punch code d for 1/200 on line2 requires 100 C/L
				for(i=0; i<2; i++)
				{
					// Create the new hole
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					// Move the feed pos
					nFeed+=100;
				}
				nFeed=tmp;
			}
			else if((lineIdent.CompareNoCase(_T("Line_1")) && (partCode>=IDS_PART8 && partCode<=IDS_PART10) &&
						!punchCode.CompareNoCase(_T("Y"))) ||
						/* Zeta 1 */
						(partCode==IDS_PART5 && lineIdent.CompareNoCase(_T("Line_1")) 
						&& !punchCode.CompareNoCase(_T("H")) || !punchCode.CompareNoCase(_T("J"))) ||
						/* Zeta 2 or Z300 */
						((partCode==IDS_PART1 || partCode==IDS_PART6) && lineIdent.CompareNoCase(_T("Line_1")) 
						&& !punchCode.CompareNoCase(_T("H")) || !punchCode.CompareNoCase(_T("J")))
						)
			{
				// 18 mm slot on Zeta's on line 2 and 3
				nFeed-=18;
				bMultipleHitCase = false;
				for (i=0; i<5; i++)
				{
					// Move the feed pos
					nFeed+=6;
					// Create the new hole
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
				}
				nFeed=tmp;
			}
			else if(!lineIdent.CompareNoCase(_T("Line_3")) && !punchCode.CompareNoCase(_T("D"))
						&& partCode==IDS_PART5)
			{
				// Zeta 1/200 100 C/L main fixing holes
				for(i=0; i<2; i++)
				{
					// Create the new hole
					this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
					// Move the feed pos
					nFeed+=100;
				}
				nFeed=tmp;
			}
			else
				this->DefineHole(pBeamOp, nFeed, lHoleID, lpszPunch, lpszOpDef, sComment, bMultipleHitCase);
		}
		sRetainedComment = sComment;
	}
	else if (sOpType == _T("Dim"))
	{
		char* m_pz = sOpDef.GetBuffer(1);
		if (*m_pz > 47 && *m_pz < 58 || *m_pz == 45 || *m_pz == 43)
		{
			// we've got a numeric value
			nDim = atoi ((const char*)sOpDef);
		}
		else
		{
			// we've got a dimension code to interpret
			CDaoDimValue* pSet = new CDaoDimValue(pDB);

			// Set parameters
			pSet->m_Section_Ident	= this->m_pItem->GetSectionID();
			pSet->m_Dim_Ident		= sOpDef;
		
			// Open recordset
			pSet->Open();

			if (pSet->GetRecordCount() > 1)
			{
				szMsg = _T("Invalid Data ! \nA single record should be returned");
				AfxMessageBox(szMsg);
			}

			sDim = pSet->m_Dimension_Value;
	
			pSet->Close();
			delete(pSet);
			
			// Check for proportional overlap
			int ch = sDim.Find(_T("."));
			if (ch >= 0)
			{
				ch = sDim.Find(_T("L"));
				double fFactor = atof((const char*)sDim.Left(ch));

				if(sOpDef.Right(1) == _T("1"))
				{
					nDim = this->m_nSpan1 * fFactor;
				}
				else if(sOpDef.Right(1) == _T("2"))
				{
					nDim = this->m_nSpan2 * fFactor;
				}
				else if(sOpDef.Right(1) == _T("3"))
				{
					nDim = this->m_nSpan3 * fFactor;
				}
			}
			else
			{	
				nDim = atoi ((const char*)sDim);
			}
		}
	}
	else if (sOpType == _T("Gen"))		// its a length op
	{
		if (sOpDef == _T("SPAN1")) {nDim = m_nSpan1;}
		if (sOpDef == _T("SPAN2")) {nDim = m_nSpan2;}
		if (sOpDef == _T("SPAN3")) {nDim = m_nSpan3;}
		if (sOpDef == _T("OHANG1")){nDim = m_nOHang1;}
		if (sOpDef == _T("OHANG2")){nDim = m_nOHang2;}
		if (sOpDef == _T("LENGTH")){nDim = m_nOLength;}
		if (sOpDef == _T("COL1"))  {nDim = m_nCol1;}
		if (sOpDef == _T("COL2"))  {nDim = m_nCol2;}
		if (sOpDef == _T("N/A"))
		{
			return;
		}
	}

	if (sOpType != _T("Punch"))
	{
		if (pBeamOp->GetMultiplied())
		{
			nDim *= nMultiplier;
		}
		else
		{
			nDim /= nMultiplier;
		}
		if (pBeamOp->GetAbsolute())
		{
			// its an absolute dimension
			// trap special case for manual input of extra holes
			// Negative Abosulte Value is illegal
			if (pBeamOp->GetPositive() && nDim >= 0)         // VHF TODO:  Make sure that the values stored in the list are unsigned??
			{
				nFeed = nDim;
			}
			else
			{
				AfxMessageBox(_T("Illegal operation \nAbsolute negative feed!"));
			}
		}
		else	//	its relative
		{
			if (pBeamOp->GetPositive() && nDim >= 0)
			{
				nFeed += nDim;
			}
			else
			{
				if (nDim > 0)
				{
					nFeed -= nDim;
				}
				else
				{
					nFeed += nDim;
				}
			}
		}		// end of 'Absolute' loop
	}		// end of 'OpType' conditionals
}		// end of main processing loop

///////////////////////////////////////////////////////////////////////////////////////////////////
// TrapSpecialCodes()
//
// Legal hole descriptions from D3 input, or combination codes from manual input may require special processing
//		depending on which production line is to be used for manufacture.
//
// The purpose of this function is to analysis the hole description, the section size and production line and
//		decide whether special processing is required.
//
// Special processing may include:
//		Automatic adjustment of hole position and repetition of 'punch' call,
//		Declaration of 'Non-standard hole' that requires manual input of an appropriate code in the element dialog.
//
// Because the punch tools at a single station require a minimum distance between them (74mm) flags are used to
//		to record whether a particular punch has been used for a give CItem.  If a subsequent punch instruction
//		would lead to a punch conflict an error message nbase on the status of the flags will be called.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
CString CBeamElement::TrapSpecialCodes(/*CItem* pItem,*/ CString& sPunch, CString& sComment, LPCTSTR lpszOpDef, long lHoleID, bool& bMultipleHitCase)
{
	CString szSectionID = this->m_pItem->GetSectionID();
	CString szSection = szSectionID.Right(5);
	CString sOpDef = (CString)lpszOpDef;
	CString itemType = m_pItem->GetSectionID(); // Get item type
	CString tmp;
	int nSize = atoi(szSectionID.Right(3));
	int	intPart;


	switch (this->m_pItem->GetProdLine())
	{
	case LINE_1:
	// Special processing to trap codes 'A' & 'L' in Line_1, 1/150 sections
		if(sPunch == _T("A") || sOpDef == _T("A"))
		{
			if(szSection != _T("1/200"))
			{
				sPunch = _T("#3");
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				bMultipleHitCase = false;
			}
			else
			{
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
				bMultipleHitCase = false;
			}
		}
		else if(sPunch == _T("L") || sOpDef == _T("L"))
		{
			if(szSection != _T("1/200"))
			{
				sPunch = _T("#2");
				this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
				bMultipleHitCase = false;
			}
			else
			{
				this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
				bMultipleHitCase = false;
			}
		}
		else if(sPunch == _T("E") || sOpDef == _T("E"))
		{
			if(szSection != _T("1/200"))
			{
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
				bMultipleHitCase = false;
			}
		}
		else if(sPunch == _T("D") || sOpDef == _T("D"))
		{
			if(szSection == _T("1/200"))
			{
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
				bMultipleHitCase = false;
			}
		}
		else if(sPunch == _T("W") || sOpDef == _T("W"))
		{
			if(szSection != _T("1/200"))
			{
				this->m_pItem->m_bPunchUsedFlag[12] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[13] = TRUE;
				bMultipleHitCase = false;
			}
		}
		break;
	case LINE_2:
		//	PunchUsedFlag based on Line_3 numbering
		//  i.e. 10Back = 1, 10Front = 2, 1Back = 19, 1Front=20
		//	therefore PunchUsedFlag[1] and PunchUsedFlag[2] are never true
		//	and PunchUsedFlag[13] is always true (datum hole =#256)
		if(sPunch == _T("A"))	/* #1 && #2  */
		{
			if (lHoleID == 75 && getPart(itemType) != IDS_PART3)	/* Special case for Associated Sections	*/
			{
				sPunch = _T("#96");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[9]  = TRUE;
				this->m_pItem->m_bPunchUsedFlag[12] = TRUE;

			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
			}
		}
		else if(sPunch == _T("AZ"))	// #1 && #2 && #32 in EB240 
		{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
		}
		else if(sPunch == _T("B"))	/* 14dia hole to unsheeted flange */
		{
			if (szSectionID.Left(1) == "Z" || szSection.Left(1) == "Z")
			{
				switch (nSize)
				{
				case 240:
				case 300:
				//	sPunch = _T("#8");
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
				default:
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
				}
			}												/* Cee */
			else if (lHoleID == 134 && getPart(itemType) != IDS_PART3 ) 
			{	
				/* Special case for Associated Sections	*/
				sPunch = _T("#4");		/* NB: Square hole in bottom flange only	*/
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			}
		}
		else if(sPunch == _T("BB"))	// 18dia x1 on bottom flange
		{
												   /* Cee */
			if(lHoleID == 136 && getPart(itemType) != IDS_PART3) 
			{
				/* Special case for Associated Sections	*/
				sPunch = _T("#1");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;	// #2
			}
		}
		else if(sPunch == _T("C"))	/* #1 single hole on CL  */
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
		}
		else if(sPunch == _T("CZ"))	/* #1 && #32 in EB160 */
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
		}
		else if(sPunch == _T("D"))	/* #1 && #2 x2 @ 100 c/cs  */
		{
			// Test for 1/200
			if(getPart(itemType) != IDS_PART5 )
			{
				sPunch = _T("A");
				bMultipleHitCase = true;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
			}
		}
		else if(sPunch == _T("E"))	/* #1 x2 @ 100 c/cs on CL  */
		{
			sPunch = _T("C");
			bMultipleHitCase = true;
			this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
		}
		else if(sPunch == _T("F"))	/* 14 dia web pair */
		{
/*			if (szSectionID.Left(1) == "Z")
			{
				switch (nSize)
				{
				case 125:
				case 140:
				case 155:
				case 170:
					sPunch = _T("#136");	
					this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
					bMultipleHitCase = false;
					break;
/*				default:
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[12] = TRUE;		// Tool change required - how do we flag it 
				}	
			}	
			else */ if (lHoleID == 109 || lHoleID == 129 ) /* Special case for Associated Sections	*/
			{	
				// Test for Cee Section
				if(getPart(itemType) == IDS_PART3 )
				{
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[14] = TRUE;
				}
				else
				{
					sPunch = _T("#24");
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
				}
			}
/*			else if (lHoleID == 132 ) // Special case for 14dia x25slots in Top Hat Sections	
			{	
				sPunch = _T("#24");
				bMultipleHitCase = true;
				this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
			}	*/
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[8]  = TRUE;		// #136
			}
		}
		else if(sPunch == _T("G"))
		{
			if (szSectionID.Left(1) == "Z")
			{
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
				bMultipleHitCase = false;
				this->m_bIsNonStandardHole = false;
			}
			else if (lHoleID == 125 ) /*szSectionID.Left(2) == _T("DP") || szSectionID.Left(2) == _T("TP")) */
			{	
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
				sPunch = _T("#132");		/* NB: Square hole in top flange only	*/
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
			}
		}
		else if(sPunch == _T("GG"))	// 18dia x1 on both flanges
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[3] = TRUE;	// #2
			this->m_pItem->m_bPunchUsedFlag[4] = TRUE;	// #1
		}
		else if(sPunch == _T("H"))
		{
			// Zed 125-200 or 1/200
			if(getPart(itemType) == IDS_PART4 || getPart(itemType) == IDS_PART5) 
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			}
			else
			{
				if (lHoleID == 132) // Special case for 14dia x25slots in Top Hat Sections
				{
					bMultipleHitCase = true;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;	// #16
					this->m_pItem->m_bPunchUsedFlag[8] = TRUE;	// #8
					sPunch = _T("#24");
				}
				else
				{
				bMultipleHitCase = false;
				this->m_bIsNonStandardHole = true;
	//			this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
	//			this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
				}
			}
		}
		else if(sPunch == _T("N"))	// 14dia x1 on centreline
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[11] = TRUE;	// #128
		}	
		else if(sPunch == _T("Q"))	// 18dia x1 on upper gauge line
		{
			if (lHoleID == 77 && getPart(itemType) != IDS_PART3)	/* Special case for Associated Sections	*/
			{
				sPunch = _T("#32");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[9]  = TRUE;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[12] = TRUE;		
			}
		}
		else if(sPunch == _T("QZ"))	// #1 && #2 in EB240 
		{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
		}
		else if(sPunch == _T("R"))	/*  14 dia in upper web = #128 */
		{
			if (szSectionID.Left(1) == "Z")
			{
				switch (nSize)
				{
				case 125:
				case 140:
				case 155:
				case 170:
					bMultipleHitCase = false;
					this->m_bIsNonStandardHole = true;	/* not available for small Zeds */
					break;
				default:
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
				}
			}
			else if (lHoleID == 111 && getPart(itemType) != IDS_PART3)
			{
				sPunch = _T("#16");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
			}
		}
		else if(sPunch == _T("S"))
		{
			if (szSectionID.Left(1) == "Z")
			{
				switch (nSize)
				{
				case 125:
				case 140:
				case 155:
				case 170:
				//	sPunch = _T("#36");
					this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
					bMultipleHitCase = false;
					break;
				default:
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
					break;
				}
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			}
		}
		else if(sPunch == _T("T"))
		{
			if (szSectionID.Left(1) == "Z" || szSection.Left(1) == "Z")
			{
				switch (nSize)
				{
				case 125:
				case 140:
				case 155:
				case 170:
					bMultipleHitCase = false;
					this->m_bIsNonStandardHole = false;
					break;
				case 240:
				case 300:
					//sPunch = _T("#16");
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
					break;
				default:
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
				}
			}
			else if (lHoleID == 133 && getPart(itemType) != IDS_PART3)	/* Special case for Associated Sections	*/
			{
				sPunch = _T("#128");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
			}
		}
		else if(sPunch == _T("TT"))	// 18dia x1 on top flange
		{
													   /* Cee */
			if (lHoleID == 135 && getPart(itemType) != IDS_PART3)	
			{
				/* Special case for Associated Sections	*/
				sPunch = _T("#2");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;	// #1
			}
		}
		else if(sPunch == _T("U"))	/*  14dia x25slot on lower gauge line  */
		{
				bMultipleHitCase = true;
		}
		else if(sPunch == _T("V"))	/*  14 dia in lower web  */
		{
			if (szSectionID.Left(1) == "Z")
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;  // = #128
			}
			else if (lHoleID == 110 && getPart(itemType) != IDS_PART3)
			{
				sPunch = _T("#8");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;	// = #128
			}
		}
		else if(sPunch == _T("W"))
		{
//			this->m_bIsNonStandardHole = true;
			bMultipleHitCase = true;
			sPunch = _T("X");
			this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
		}
		else if(sPunch == _T("X"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
		}
		else if (sPunch == _T("Y"))	//	single 18 x 43 slot
		{
			int partID = getPart(itemType);
			
			bMultipleHitCase = false;
			if(!(partID >= IDS_PART8 && partID <= IDS_PART10))
			{
				
				if (szSectionID.Right(5) == _T("1/125"))
				{
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
				}
				else
				{
					this->m_bIsNonStandardHole = true;
					// need a message here to identify what punch is regarded as non-standard
					// this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
				}
			}
		}
		else if(sPunch == _T("Z"))	// 18dia x1 on lower gauge line
		{
			if(getPart(itemType) != IDS_PART5)
			{
				if (lHoleID == 76)	/* Special case for Associated Sections	*/
				{
					sPunch = _T("#64");
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[12]  = TRUE;
				}
				else if (lHoleID == 88 || lHoleID == 139 )	/* Special case for Zeta2 Sections	*/
				{
					sPunch = _T("#2");
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				}
				else if (lHoleID == 124)	/* Special case for slots in Zed240/300 Sections	*/
				{
					sPunch = _T("#1");
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[2] = TRUE;	
				}
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[12] = TRUE;		/* ?? #64 */
			}
		}
		else if(sPunch == _T("#16"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
		}
		else if(sPunch == _T("#8"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
		}
		break;
/*			SPECIAL CASE TO SORT OUT - SINGLE SLEEVE HOLE IN 1/200
			  (CAN'T DO IT ON LINE 2 - IN ANY CASE)
		else if(sPunch == _T("#20"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
		}
		break;
*/
	case LINE_3:
		if(sPunch == _T("A") || sPunch == _T("SR"))	// "SR" = 2x 18dia holes in Swagebeam
		{
			intPart = getPart(itemType);
			if(intPart == IDS_PART1)
			{
				// Use #5 AND #6 // hard wired case
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
				this->m_pItem->m_szPunchGauge[5] = sComment;
				this->m_pItem->m_szPunchGauge[6] = sComment;
			}
			else if(intPart >=IDS_PART8 && intPart <= IDS_PART10)
			{
				// Zeta1 centre line main fixing hole
				sPunch = _T("C");
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				this->m_pItem->m_szPunchGauge[6] = sComment;
				this->m_pItem->m_szPunchGauge[3] = sComment;
			}
		}
		else if(sPunch == _T("B"))
		{
			if(getPart(itemType) == IDS_PART1)
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
				this->m_pItem->m_szPunchGauge[9] = sComment;
			}
			else
			{
				if ((lHoleID == 106 || lHoleID == 134) && getPart(itemType) != IDS_PART3 )
				{
					bMultipleHitCase = false;
					sPunch = _T("V");
					this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
					this->m_pItem->m_szPunchGauge[5] = sComment;
				}
	//			else if(lHoleID == 134)
	//			{
	//				bMultipleHitCase = false;
	//				sPunch = _T("R");
	//				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
	//				this->m_pItem->m_szPunchGauge[4] = sComment;
	//			}
				else
				{
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
					this->m_pItem->m_szPunchGauge[7] = sComment;
				}
			}
		}
		else if(sPunch == _T("C") || sOpDef == _T("C"))
		{
		}
		else if(sPunch == _T("D"))
		{
			if(getPart(itemType) == IDS_PART1)
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
				this->m_pItem->m_szPunchGauge[5] = sComment;
			}
			else
			{
				sPunch = _T("A");
				bMultipleHitCase = true;
				this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
				this->m_pItem->m_szPunchGauge[3] = sComment;
				this->m_pItem->m_szPunchGauge[6] = sComment;
			}
		}
		else if(sPunch == _T("E"))
		{
			// Zeta 1 Centre line main fixing hole
			if(getPart(itemType) >= IDS_PART8 && getPart(itemType) <= IDS_PART10)
				sPunch = _T("C");
			else
				sPunch = _T("#13");

			bMultipleHitCase = true;
			this->m_pItem->m_bPunchUsedFlag[13] = TRUE;
			this->m_pItem->m_szPunchGauge[13] = sComment;
		}
		else if(sPunch == _T("F"))
		{
			if(lHoleID == 109 && getPart(itemType) != IDS_PART3)
			{
				bMultipleHitCase = false;
				sPunch = _T("G");
				this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
				this->m_pItem->m_szPunchGauge[2] = sComment;
				this->m_pItem->m_szPunchGauge[7] = sComment;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
				this->m_pItem->m_szPunchGauge[4] = sComment;
				this->m_pItem->m_szPunchGauge[5] = sComment;
			}
		}
		else if(sPunch == _T("G"))
		{
			if(getPart(itemType) == IDS_PART1 || getPart(itemType) == IDS_PART3)
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
				this->m_pItem->m_szPunchGauge[4] = sComment;
				this->m_pItem->m_szPunchGauge[9] = sComment;
			}
			else
			{
				if (lHoleID == 112)
				{
					bMultipleHitCase = false;
					sPunch = _T("F");
					this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
					this->m_pItem->m_szPunchGauge[4] = sComment;
					this->m_pItem->m_szPunchGauge[5] = sComment;
				}
				else
				{
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
					this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
					this->m_pItem->m_szPunchGauge[2] = sComment;
					this->m_pItem->m_szPunchGauge[7] = sComment;
				}
			}
		}
		else if(sPunch == _T("H"))
		{
			// 1/200 (convert to J)
			if(getPart(itemType) == IDS_PART5)
				sPunch = _T("J");

			if (lHoleID == 116)
			{
				// special case for 18 dia slots in 1/200
				bMultipleHitCase = true;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
				this->m_pItem->m_szPunchGauge[10] = sComment;
				this->m_pItem->m_szPunchGauge[11] = sComment;
			}
		}
		else if(sPunch == _T("J")) /* 14 dia version of D for Cees */
		{
			if(getPart(itemType) == IDS_PART1 || getPart(itemType) == IDS_PART5)
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
				this->m_pItem->m_szPunchGauge[10] = sComment;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
				this->m_pItem->m_szPunchGauge[11] = sComment;
			}
			else
			{
				sPunch = _T("G");
				bMultipleHitCase = true;
				this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
				this->m_pItem->m_szPunchGauge[2] = sComment;
				this->m_pItem->m_szPunchGauge[7] = sComment;
			}
		}
		else if(sPunch == _T("K")) /* 14 dia version of D for Zeds */
		{
			sPunch = _T("F");
			bMultipleHitCase = true;
			this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
			this->m_pItem->m_szPunchGauge[4] = sComment;
			this->m_pItem->m_szPunchGauge[5] = sComment;
		}
		else if(sPunch == _T("L") || sOpDef == _T("L"))
		{
			if( (getPart(itemType) >= IDS_PART8 && getPart(itemType) <= IDS_PART10) )
			{
				// 18 dia centreline main fixing
				sPunch = _T("C");
			}
			else
			{
				// Main fixing holes
				sPunch = _T("A");
			}
		}
		else if(sPunch == _T("M"))
		{
			if(getPart(itemType) == IDS_PART1)
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[11] = TRUE;
				this->m_pItem->m_szPunchGauge[11] = sComment;
			}
		}
		else if(sPunch == _T("N"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[12] = TRUE;
			this->m_pItem->m_szPunchGauge[12] = sComment;
		}
		else if(sPunch == _T("Q") || sPunch == _T("TT") )
		{
//			if(lHoleID == 77)
//			{
//				sPunch = _T("#9");
//				bMultipleHitCase = false;
//				this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
//				this->m_pItem->m_szPunchGauge[9] = sComment;
//			}
//			else
//	{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
				this->m_pItem->m_szPunchGauge[6] = sComment;
//	}
		}
		else if(sPunch == _T("R"))
		{
			if(lHoleID == 111 && getPart(itemType) != IDS_PART3)
			{
				sPunch = _T("T");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
				this->m_pItem->m_szPunchGauge[2] = sComment;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
				this->m_pItem->m_szPunchGauge[4] = sComment;
			}
		}
		else if(sPunch == _T("T"))
		{
			if(getPart(itemType) == IDS_PART1)
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
				this->m_pItem->m_szPunchGauge[2] = sComment;
			}
			else
			{
				if((lHoleID == 113 || lHoleID == 133) && getPart(itemType) != IDS_PART3)
				{
					sPunch = _T("R");
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
					this->m_pItem->m_szPunchGauge[4] = sComment;
				}
	//			else if(lHoleID == 133)
	//			{
	//				sPunch = _T("V");
	//				bMultipleHitCase = false;
	//				this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
	//				this->m_pItem->m_szPunchGauge[5] = sComment;
	//			}
				else
				{
					bMultipleHitCase = false;
					this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
					this->m_pItem->m_szPunchGauge[2] = sComment;
				}
			}
		}
		else if(sPunch == _T("U"))/* 14 dia version of E */
		{
			sPunch = _T("#12");
			bMultipleHitCase = true;
			this->m_pItem->m_bPunchUsedFlag[12] = TRUE;
			this->m_pItem->m_szPunchGauge[12] = sComment;
		}
		else if(sPunch == _T("V"))
		{
			if(lHoleID == 110 && getPart(itemType) != IDS_PART3)
			{
				sPunch = _T("B");
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
				this->m_pItem->m_szPunchGauge[7] = sComment;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
				this->m_pItem->m_szPunchGauge[5] = sComment;
			}
		}
		else if(sPunch == _T("W"))
		{
			intPart = getPart(itemType);
			// Zeta1 is a multiple hit
			if(intPart >=IDS_PART8 && intPart <= IDS_PART10)
				bMultipleHitCase = true;
			else
				bMultipleHitCase = false;

			this->m_pItem->m_bPunchUsedFlag[14] = TRUE;
			this->m_pItem->m_szPunchGauge[14] = sComment;
		}
		else if(sPunch == _T("S"))
		{
			if(getPart(itemType) == IDS_PART1)
			{
				// Use #7 AND #8 // hard wired case
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[7] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
				this->m_pItem->m_szPunchGauge[7] = sComment;
				this->m_pItem->m_szPunchGauge[8] = sComment;
			}
			else
			{
				bMultipleHitCase = false;
				this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
				this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
				this->m_pItem->m_szPunchGauge[8] = sComment;
				this->m_pItem->m_szPunchGauge[9] = sComment;
			}
		}
		else if(sPunch == _T("X"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
			this->m_pItem->m_szPunchGauge[8] = sComment;
		}
		else if(sPunch == _T("Y"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[10] = TRUE;
			this->m_pItem->m_szPunchGauge[10] = sComment;
		}
		else if(sPunch == _T("Z") || sPunch == _T("BB") )
		{
		}
		else if(sPunch == _T("AZ"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[12] = TRUE;
			this->m_pItem->m_szPunchGauge[3] = sComment;
			this->m_pItem->m_szPunchGauge[6] = sComment;
			this->m_pItem->m_szPunchGauge[12] = sComment;
		}
		else if(sPunch == _T("SR"))	// == Swagedetail "R" = 2x 18dia holes
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
			this->m_pItem->m_szPunchGauge[6] = sComment;
			this->m_pItem->m_szPunchGauge[3] = sComment;
		}
		else if(sPunch == _T("SB"))	// == Swagedetail "B" = 1x 18dia hole on lower gauge line
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
			this->m_pItem->m_szPunchGauge[3] = sComment;
		}
		else if(sPunch == _T("ST"))	// == Swagedetail "T" = 1x 18dia hole on upper gauge line
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			this->m_pItem->m_szPunchGauge[6] = sComment;
		}
		else if(sPunch == _T("SX"))	// == Swagedetail "X" = 4x 18dia holes on gauge lines
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[3] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[4] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[5] = TRUE;
			this->m_pItem->m_szPunchGauge[3] = sComment;
			this->m_pItem->m_szPunchGauge[6] = sComment;
			this->m_pItem->m_szPunchGauge[4] = sComment;
			this->m_pItem->m_szPunchGauge[5] = sComment;
		}
		else if(sPunch == _T("SS"))	// == Swagedetail "S" = 2x 14sq on gauge lines
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[9] = TRUE;
			this->m_pItem->m_szPunchGauge[8] = sComment;
			this->m_pItem->m_szPunchGauge[9] = sComment;
		}
		else if(sPunch == _T("SD") )	// == Swagedetail "D" = 18dia bottom flange hole
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[13] = TRUE;
			this->m_pItem->m_szPunchGauge[13] = sComment;
		}
		else if(sPunch == _T("SU") )	// == Swagedetail "U" = 18dia top flange hole
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
			this->m_pItem->m_szPunchGauge[2] = sComment;
		}
		else if(sPunch == _T("SF") )	// == Swagedetail "F" = 18dia flange holes
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[13] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[2] = TRUE;
			this->m_pItem->m_szPunchGauge[13] = sComment;
			this->m_pItem->m_szPunchGauge[2] = sComment;
		}
		else if(sPunch == _T("QZ"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[12] = TRUE;
			this->m_pItem->m_bPunchUsedFlag[6] = TRUE;
			this->m_pItem->m_szPunchGauge[12] = sComment;
			this->m_pItem->m_szPunchGauge[6] = sComment;
		}
		break;
/*			SPECIAL CASE TO SORT OUT - SINGLE SLEEVE HOLE IN 1/200
		else if(sPunch == _T("#20"))
		{
			bMultipleHitCase = false;
			this->m_pItem->m_bPunchUsedFlag[8] = TRUE;
		}
		break;
*/
	default:
		AfxMessageBox("Oops! shouldn't be here -  No Line specified");
	}

	return sPunch;
}
////////////////////////////////////////////////////////////////////////////////////////////
//	CheckPunchConflicts()
//
//	Special processing for Cee Sections - relies on the comment field being populated
//	with the gauge lines - protocol established with SBE.
//
//	Design: 1) make sure that the comment field is populated - it may not be for 'centreline' punches
//			2) check on current punch allocation for this item by calling line specific function
//			3) if potential conflict display message
// 
bool  CBeamElement::CheckPunchConflicts(CBeamOps* pBeamOp, long lHoleID, LPCTSTR lpszOpDef, CString& sPunchMsg, CString& sRetainedComment, long& nPreviousHoleType, CString& sDefaultPunch, CString& szMsg)
{
	int nLineID			= m_pItem->GetProdLine();
	CString sComment	= pBeamOp->GetComment();
	bool bDisplayMsg	= false;
		
	//  make sure that the comment field for each hole is populated
	switch (lHoleID)
	{
	case 68:
	case 78:
	case 72:
	case 80:
		if (sComment == _T(""))
		{
			sComment = _T("on centreline");
			pBeamOp->SetComment(sComment);
		}
		break;
	case 69:
	case 71:
	case 125:
	case 112:
	case 113:
	case 106:
	case 133:
	case 134:
	case 135:
	case 136:
		if (sComment == _T(""))
		{
			sComment = _T("flange hole");
			pBeamOp->SetComment(sComment);
		}
		break;
	case 77:
	case 75:
	case 76:
	case 83:
	case 109:
	case 110:
	case 111:
	case 114:
	case 121:
		if (sComment == _T(""))
		{
			sComment = _T("on gaugeline");
			pBeamOp->SetComment(sComment);
		}
		break;
	}

	//  Now check that the punch required has not already been used for something else
	//  and warn to check centres if the 'opposite' punch has already been specified  
	switch (nLineID)
	{
	case LINE_2:
		m_pItem->m_bPunchUsedFlag[13]=true;
		bDisplayMsg = this->CheckLine2ExtraHole(pBeamOp, lHoleID, sPunchMsg, sRetainedComment, nPreviousHoleType, sDefaultPunch);
		break;
	case LINE_3:
		m_pItem->m_bPunchUsedFlag[1]=true;
		bDisplayMsg = this->CheckLine3ExtraHole(pBeamOp, lHoleID, sPunchMsg, sRetainedComment, nPreviousHoleType, sDefaultPunch);
		break;
	}

	// Display warnings if customer comment attached to this hole definition
	// is not the same as the retained comment, or if the hole type changes
	if (bDisplayMsg)
//					|| /*(nElementID == 1 && m_nHits == 0)*//* sRetainedComment == _T("") */ (sComment != _T("") && (sComment != sRetainedComment || lHoleID != nPreviousHoleType) ))
	{
		szMsg = this->GetMsgHeader();
		szMsg += "\n\nHole type - ";
		szMsg += "'" + (CString)lpszOpDef + "'";
		szMsg += "\n\nNB: Customer comment for this hole :-";
		szMsg += "\n\n' " + sComment + " '\n";
		szMsg += sPunchMsg;
		szMsg += sDefaultPunch;
	}
	return bDisplayMsg;

}
////////////////////////////////////////////////////////////////////////////////////////////
//
double CBeamElement::GetPunchValue(/*CItem* pItem,*/ /*CElement* pElement,*/ CBeamOps* pBeamOp, /*CDaoDatabase* pDB,*/ LPCTSTR lpszPunch/*, int nHits*/)
{
	CDaoDatabase	*pDB	= this->m_pDoc->GetProjectSettings()->m_pDB;
	CPunchValue		*pSet	= new CPunchValue(pDB);
	int				lineNum = this->m_pItem->GetProdLine();
	double			nPunchValue = 0;
	double			modified = 0.0L;


	// Set up recordset SQL parameters
	pSet->m_Line_Ident		= this->m_pItem->GetProdLineLabel();
	pSet->m_Section_Ident	= this->m_pItem->GetSectionID();
	pSet->m_Script_Ident	= pBeamOp->GetScriptID();
	pSet->m_Punch_Ident		= (CString)lpszPunch;

	// check validity of ScriptID

	// case 1: pBeamOp->m_ScriptID not initialised
	if(pBeamOp->GetScriptID() > 10000)
	{
		if(this->m_OpScriptID > 10000)
		{
			pBeamOp->SetScriptID(10);
		}
		else
		{
			pBeamOp->SetScriptID(this->m_OpScriptID);
		}

/*
#ifdef _DEBUG
			szMsg = this->GetMsgHeader(pItem, nHits+1);
			szMsg += "\nIllegal Script ID > 1000 - ";
			szMsg += "Setting ScriptID to ";
			CString szScript = _T("");
			long nScript = pBeamOp->GetScriptID();
			szScript.Format("%.6li",nScript);
			szMsg += szScript;
			szMsg += "\n" + pBeamOp->GetOperation();
			szMsg += " : " + sPunch;
			szMsg += "\nCBeamOps object @ ";
			CString szPointer = _T("");
			szPointer.Format("%p",pBeamOp);
			szMsg += szPointer;
			AfxMessageBox(szMsg);
#endif
*/
		// refresh m_Script_Ident with new value
		pSet->m_Script_Ident = pBeamOp->GetScriptID();
	}

	// case 2: Script value not set 
	// (shouldn't occur - but trap for nonstandard manual input)
	if(pBeamOp->GetScriptID() <= 0)
	{
		if(this->m_OpScriptID <= 0)
		{
			pBeamOp->SetScriptID(10);
		}
		else
		{
			pBeamOp->SetScriptID(this->m_OpScriptID);
		}
/*
#ifdef _DEBUG
			szMsg = this->GetMsgHeader(pItem, nHits+1);
			szMsg += "\nIllegal Script ID < 0 - ";
			szMsg += "Setting ScriptID to ";
			CString szScript = _T("");
			long nScript = pBeamOp->GetScriptID();
			szScript.Format("%.6li",nScript);
			szMsg += szScript;
			szMsg += "\n" + pBeamOp->GetOperation();
			szMsg += " : " + sPunch;
			szMsg += "\nCBeamOps object @ ";
			CString szPointer = _T("");
			szPointer.Format("%p",pBeamOp);
			szMsg += szPointer;
			AfxMessageBox(szMsg);
#endif
*/
			// refresh m_Script_Ident with new value
		pSet->m_Script_Ident = pBeamOp->GetScriptID();
	}

/*
		else
		{
			nScriptID = pBeamOp->GetScriptID();
			if (nScriptID > 10000){nScriptID = 10;}
			pSet->m_Script_Ident = nScriptID;

			if(pSet->m_Script_Ident > 1000)
			{
				szMsg = "Item No.";
				szMsg += sItemID;
				szMsg += ": Mark No. ";
				szMsg += szMark;
				szMsg += " : Hit No. ";
				CString szHit = _T("");
				szHit.Format("%d",(nHits+1));
				szMsg += szHit;
				szMsg += "\nCBeamOps object @ ";
				CString szPointer = _T("");
				szPointer.Format("%p",pBeamOp);
				szMsg += szPointer;
				szMsg += "\nLooking for punch value";
				szMsg += "\nIllegal Script ID > 1000 - ";
				CString szScript = _T("");
				szScript.Format("%.6li",pSet->m_Script_Ident);
				szMsg += szScript;
				szMsg += "\n" + pBeamOp->GetOperation();
				szMsg += " : Code " + sPunch;

				pSet->m_Script_Ident = this->m_OpScriptID;

				szMsg += "\nSetting ScriptID to ";
				szScript.Format("%.6li",pSet->m_Script_Ident);
				szMsg += szScript;

				AfxMessageBox(szMsg);
			}

		}
*/
	// Perform Line Vs produt test and modify punch code if required
	if(allowModPass(lineNum, pSet->m_Section_Ident))
	{
		try
		{
			// Open the record set
			pSet->Open();

			// Modify the punch code
			nPunchValue = modifyPunchCodes(lineNum, pSet->m_Section_Ident, pSet->m_Punch_Ident, pSet->m_Value);
		}
		catch(CDaoException *e)
		{
			// Report error
			e->ReportError(MB_OK);
			// Delete exception
			e->Delete();
		}
	}
	else
	{
		// OK got valid data so go to database			
		pSet->Open();

		if (pSet->GetRecordCount() > 1)
		{
			CString szMsg = _T("Invalid Data ! \nA single record should be returned");
			AfxMessageBox(szMsg);
		}
			
		nPunchValue = pSet->m_Value;

		// now check validity of returned value
		if (nPunchValue < 1)
		{
			CString szMsg = this->GetMsgHeader(/*pItem,*/ /*nHits+1*/);


#ifdef _DEBUG
				szMsg += "\n\nLine: ";
				szMsg += pSet->m_Line_Ident;
				szMsg += "\nSection: ";
				szMsg += pSet->m_Section_Ident;
				szMsg += "\nPunchCode: ";
				szMsg += pSet->m_Punch_Ident;
				szMsg += "\nScript: ";
				CString szScript = _T("");
				szScript.Format("%.6li",pSet->m_Script_Ident);
				szMsg += szScript;
				szMsg += "\nPunchValue: ";
				CString szValue = _T("");
				szValue.Format("%g",pSet->m_Value);
				szMsg += szValue;
#endif

			szMsg += _T("\n\nNo Punch value assigned for code ");
			szMsg += (CString)lpszPunch;
			AfxMessageBox(szMsg);

			m_bIsNonStandardHole = true;

			CElement* pElement = (CElement*)this;
			this->m_pItem->SetFailedBeam(pElement);
			this->DeleteHits();
			pSet->Close();
			delete(pSet);
			return nPunchValue;
		}
	}

	pSet->Close();
	delete(pSet);


	return nPunchValue;
}
////////////////////////////////////////////////////////////////////////////////////
//
void CBeamElement::DefineHole(CBeamOps* pBeamOp, double nFeed, long lHoleID, LPCTSTR lpszPunch, LPCTSTR lpszOpDef, CString& sComment, bool& bMultipleHitCase)
{

	CString sPunch = (CString)lpszPunch;
	CString sOpDef = (CString)lpszOpDef;
	double nPunchValue = 0;
	bool bFirstLastFlag = false;

	this->TrapSpecialCodes(sPunch, sComment, lpszOpDef, lHoleID, bMultipleHitCase);
	nPunchValue = this->GetPunchValue(pBeamOp, sPunch);
	lpszPunch = (LPCTSTR)sPunch;

	// OpType "Punch" is last data element in a hole definition so assign
	// current feed and punch data to a new CHole object and add it to
	// the element's list of operations
	this->CreateHole(nFeed, lpszPunch, nPunchValue, bFirstLastFlag);

	// Perform secondary punch commands
	if(m_hitTwo > 0.0L)
		this->CreateHole(nFeed+m_extraFeed, lpszPunch, m_hitTwo, bFirstLastFlag);
	if(m_hitThree > 0.0L)
		this->CreateHole(nFeed+m_extraFeed, lpszPunch, m_hitThree, bFirstLastFlag);
}

////////////////////////////////////////////////////////
//
CString CBeamElement::GetMsgHeader()
{
	int nItemID = this->m_pItem->GetItemID();
	CString sItemID = _T("");
	sItemID.Format("%d",nItemID);

	CElement* pElement = (CElement*)this;
	CString szMark = pElement->GetMark();

	CString szHit = _T("");
	szHit.Format("%d",(this->m_nHits)+1);

	CString	szMsg = _T("Item No.");
			szMsg += sItemID;
			szMsg += _T(": Mark No. ");
			szMsg += szMark;
			szMsg += _T(" : Hit No. ");
			szMsg += szHit;

	return szMsg;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//	TrapNonStandardHoles()
void CBeamElement::TrapNonStandardHoles(LPCTSTR lpszOpDef)
{
	CString szMsg;
	CElement* pElement = (CElement*)this;

	szMsg = this->GetMsgHeader();
	szMsg += _T("\n\nHole type - ");
	szMsg += _T("'") + (CString)lpszOpDef + _T("'");
	szMsg += _T("\n is a non-standard requirement!");
	AfxMessageBox(szMsg);
//				this->m_bIsNonStandardHole = true;
	this->m_pItem->SetFailedBeam(pElement);
	this->DeleteHits();
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
bool CBeamElement::CheckLegalPosition(/*CItem* pItem,*/ /*int nHit,*/ double nFeed )
{
	CElement* pElement = (CElement*)this;
	CString szSPC = this->GetSPCode();
	CString szMsg = _T("");

	if(szSPC == _T("NON") || szSPC == _T("NONP") || szSPC == _T("NONR") ||szSPC == _T("EBNON") )
	{
		if (nFeed < 0)
		{
			szMsg = this->GetMsgHeader(/*pItem,*/ /*nHit*/);
			szMsg += "\n\nERROR: Negative position value";
		}
		else if (nFeed > this->GetLength())
		{
			szMsg = this->GetMsgHeader(/*pItem,*/ /*nHit*/);
			szMsg += "\n\nERROR: Hole position past end of beam";
		}
		else
		{
			return true;
		}
		szMsg += "\n\nCheck entries in Beam Input Dialog";
		AfxMessageBox(szMsg,MB_ICONSTOP,MB_OK);
		this->m_bIsNonStandardHole = true;
		this->m_pItem->SetFailedBeam(pElement);
		return false;
	}
	else
	{
		if (nFeed < 0)
		{
			szMsg = this->GetMsgHeader(/*pItem,*/ /*nHit*/);
			szMsg += "\n\nERROR: Negative position value";
		}
		else if (nFeed > this->GetLength())
		{
			szMsg = this->GetMsgHeader(/*pItem,*/ /*nHit*/);
			szMsg += "\n\nERROR: Hole position past end of beam";
		}
		else
		{
			return true;
		}
		szMsg += "\n\nPotential Script error in database for SPC '";
		szMsg += szSPC + "'";
		szMsg += "\n\nRaise a fault log indicating Job No, Section and SPC";
		szMsg += "\nand seek advice on how to procede";
		AfxMessageBox(szMsg,MB_ICONSTOP,MB_OK);
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CreateOrderedScriptList()	Add beam elements to a CItem element list in DESCENDING order of length
//
void CBeamElement::CreateOrderedScriptList(CBeamOps* pBeamOp)
{
/*	POSITION pos;
	CBeamOp* pRec;
	int test, key;
	
	// get sequenceID of current op
	test = pBeamOp->GetOpSeqID();

	// get head position of script list
	pos = this->m_tplScriptList.GetHeadPosition();		

	// if list empty add to tail and exit
	if(!pos)
	{
		this->m_tplScriptList.AddTail(pNewElement);
		return;
	}

	// at least one operation in list so check to see if it's the same as the new one
	while (pos)
	{
		pRec = (CBeamOp*)this->m_tplScriptList.GetNext(pos);
		if(pRec != pBeamOp)									// does Op already exist?
		{}													// this one doesn't match - try next
		else												// this one does 
		{
			if(pRec->GetOpSeqID() != test)					// if the operation has changed so we need to re-order the list
			{												// it has so ...
				this->m_tplScriptList.GetPrev(pos);		// ... get position of pRec ...
				this->m_tplElementList.RemoveAt(pos);		// ... and remove it.
			}
			else											// it hasn't changed so ...
			{
				return;										// ... we don't do anything.
			}
		}
	}


	pos = this->m_tplElementList.GetHeadPosition();			// refresh head position of element list


	do																	// at least one beam in list so force 'do'
	{																	// get nth record in element list and find its length
		pRec = (CBeamElement*)this->m_tplElementList.GetNext(pos);
		key = pRec->GetLength();

		// do comparison
		if(test < key)													// newbeam is shorter
		{
			if (pos == NULL)											// pRec is last in list
			{
				this->m_tplElementList.AddTail(pNewElement);			// so add newbeam to tail
				return;
			}
		}
		else															// newbeam is longer
		{	
			if(!pos)													// and we're at the end of the list
			{
				pos = this->m_tplElementList.GetTailPosition();			// so get tail position
				this->m_tplElementList.InsertBefore(pos, pNewElement);	//  and insert before 
				return;
			}
			else if (!this->m_tplElementList.GetPrev(pos))				// we're at the head of the list 
			{															// all remaining elements are shorter
				this->m_tplElementList.AddHead(pNewElement);			// so add the new element to the head
			}
			else														// we're in the middle of the list
			{															// all remaining elements are shorter
				this->m_tplElementList.InsertBefore(pos, pNewElement);	// so insert it before the next one	
				return;													// and exit
			}
		}
	} while(pos); //	check against next key
*/	
}
	
	


bool CBeamElement::SortOpsByHolePosition()
{
	POSITION pos;
	CHole* pHit1;
	CHole* pHit2;
	CHole* pTempHole;
	int test, key;

start:
	bool bModified = false;
	
	// get head position
	pos = this->m_tplHitList.GetHeadPosition();
		if(!pos){return false;}

	// bubble sort - VHF TODO: use a more efficient method - see qsort
	do
	{
		// get rec1
		pHit1 = this->m_tplHitList.GetNext(pos);
			if(!pos){break;}
		test = pHit1->GetPosX();

		// get rec2
		pHit2 = this->m_tplHitList.GetNext(pos);
		key = pHit2->GetPosX();

		// do comparison
		if(test > key)
		{
			// do swap
			pTempHole = new CHole;
			pTempHole->SetPosX(pHit1->GetPosX());
			pTempHole->SetPosY(pHit1->GetPosY());
			pTempHole->SetPunch(pHit1->GetPunch());

			pHit1->SetPosX(pHit2->GetPosX());
			pHit1->SetPosY(pHit2->GetPosY());
			pHit1->SetPunch(pHit2->GetPunch());

			pHit2->SetPosX(pTempHole->GetPosX());
			pHit2->SetPosY(pTempHole->GetPosY());
			pHit2->SetPunch(pTempHole->GetPunch());

			delete pTempHole;
			
			bModified = true;
		}
		pos = this->m_tplHitList.Find(pHit2);

	}while(pos);

	if(bModified ==true)
		goto start;
		
	return true;
}
/////////////////////////////////////////////////////////////////////////////
//
void CBeamElement::ProcessGridInput(CBeamDlg* pDlg)
{
	
/*	if (!this->m_tplAddList.IsEmpty())
	{
		this->RemoveXtraHoleList();
	}
*/

	COD3GridCtrl *pGrid = (COD3GridCtrl*)pDlg->GetDlgItem(IDC_EXTRA_HOLE_GRID);

	POSITION	pos;
	CBeamOps	*pOperation;
	int			nSheet = CURRENT_SHEET;
	int			nBegRowNdx = 1;
	int			nBegColNdx = 0 /* 1 changed to trap deleted rows */ ;
	int			nEndRowNdx = NROWS;
	int			nEndColNdx = NCOLS;
	int			nRowNdx;
	int			nColNdx;
	int			nSeqID = 0;
	int			nRowsDeleted = 0;
	bool		bUpdated = false;
	CString		sCellText;
	LPCTSTR		lpszCellText;

	// Clear list
	resetExtraHolesList();


	// Loop through grid data
	for (nRowNdx = nBegRowNdx; nRowNdx < (nEndRowNdx +1); ++nRowNdx)
	{
		for (nColNdx = nBegColNdx; nColNdx < (nEndColNdx +1); ++nColNdx)
		{
			// Get text from the grid
			sCellText = pGrid->GetCellText(nRowNdx, nColNdx, nSheet);

			// Process data in grid
			if((nColNdx > 0 && nColNdx < 6) && sCellText.GetLength())
			{
				lpszCellText = sCellText.GetBuffer(1);
				nSeqID++;
				pos = this->m_tplAddList.GetHeadPosition();
				while(pos)
				{
					pOperation = this->m_tplAddList.GetNext(pos);
					if (pOperation->GetOpSeqID() != nSeqID)					//  does the operation already exist?
					{}														//  this one doesn't match - try next one
					else
					{																//  this one does match ...
						this->InterpretGridText(lpszCellText, pOperation, nRowNdx);	//  so use function to update values
						bUpdated = true;											//  set flag to skip addition to list.
						break;
					}
				}
				if (bUpdated != true)
				{
					pOperation = new CBeamOps();									//  no matching operations so create new 
					pOperation->SetOpSeqID(nSeqID);									//  set ID
					this->InterpretGridText(lpszCellText, pOperation, nRowNdx);		//  and use function to update remaining values
					this->m_tplAddList.AddTail(pOperation);							//  position in list defined by grid cell mapping
				}
				bUpdated = false;
			}
		}
	}	

	return;
}
///////////////////////////////////////////////////////////////////////////////////////
//
bool CBeamElement::CheckLine2ExtraHole(CBeamOps* pBeamOp, long lHoleID, CString& sPunchMsg, CString& sRetainedComment, long& nPreviousHoleType, CString& sDefaultPunch)
{
	CString sComment	= pBeamOp->GetComment();

	//	If the 'hole comment' or 'hole type' changes
	//  Check usage of other punches to find conflicts
	if (sComment != _T("") && (sComment != sRetainedComment || lHoleID != nPreviousHoleType))
	{
		switch (lHoleID)
		{
		case 11:	/* F == "14dia x2 on gauge lines" */
				// This is only be available on Line_2 for John Reid
				//	AND it even then needs a tool change
			if(m_pItem->m_bPunchUsedFlag[64] == TRUE)
			{
				sPunchMsg += _T("\n Punch #64 already allocated");
			}
			if(m_pItem->m_bPunchUsedFlag[128] == TRUE)
			{
				sPunchMsg += _T("\n Punch #128 already allocated");
			}
			break;
		case 12:	/* V == "14dia x1 on lower gauge line" */
			if(m_pItem->m_bPunchUsedFlag[64] == TRUE)
			{
				sPunchMsg += _T("\n Punch #64 already allocated");
			}
			if(m_pItem->m_bPunchUsedFlag[128] == TRUE)
			{
				sPunchMsg += _T("\n Punch #128 already allocated");
			}
			break;
		case 13:	/* R == "14dia x1 on upper gauge line"*/
			if(m_pItem->m_bPunchUsedFlag[128] == TRUE)
			{
				sPunchMsg += "\n Punch #128 already allocated";
			}
			if(m_pItem->m_bPunchUsedFlag[64] == TRUE)
			{
				sPunchMsg += "\n Punch #64 already allocated";
			}
			break;
		case 65:	/* G == "14dia Both flanges"*/
			if(m_pItem->m_bPunchUsedFlag[8] == TRUE)
			{
				sPunchMsg += "\n Punch #8 already allocated";
			}
			if(m_pItem->m_bPunchUsedFlag[16] == TRUE)
			{
				sPunchMsg += "\n Punch #16 already allocated";
			}
			break;
		case 66:	// B == "14dia bottom flange"
//		case 133:	// T == "14dia in top flange" - NB Cee's are now type 1 in DB45 
			if(m_pItem->m_bPunchUsedFlag[128] == TRUE)
			{
				sPunchMsg += "\n Punch #128 already allocated";
			}
			if(m_pItem->m_bPunchUsedFlag[64] == TRUE)
			{
				sPunchMsg += "\n Punch #64 already allocated";
			}
			break;
		case 67:	// T == "14dia top flange" 
//		case 134:	// B == "14dia in bottom flange"
			if(m_pItem->m_bPunchUsedFlag[1] == TRUE)
			{
				sPunchMsg += _T("\n Punch #1 already allocated");
			}
			if(m_pItem->m_bPunchUsedFlag[2] == TRUE)
			{
				sPunchMsg += _T("\n Punch #2 already allocated");
			}
			break;
		case 69:	/* == "18dia Both flanges"*/
			if(m_pItem->m_bPunchUsedFlag[1] == TRUE)
			{
				sPunchMsg += "\n Punch #1 already allocated";
			}
			if(m_pItem->m_bPunchUsedFlag[2] == TRUE)
			{
				sPunchMsg += "\n Punch #2 already allocated";
			}
			break;
		case 71:	/* T == "18dia top flange" */
			if(m_pItem->m_bPunchUsedFlag[1] == TRUE)
			{
				sPunchMsg += _T("\n Punch #1 already allocated");
			}
			if(m_pItem->m_bPunchUsedFlag[2] == TRUE)
			{
				sPunchMsg += _T("\n Punch #2 already allocated");
			}
			break;
		case 70:	/*  == "18dia bottom flange"*/
			if(m_pItem->m_bPunchUsedFlag[128] == TRUE)
			{
				sPunchMsg += "\n Punch #128 already allocated";
			}
			if(m_pItem->m_bPunchUsedFlag[64] == TRUE)
			{
				sPunchMsg += "\n Punch #64 already allocated";
			}
			break;
		case 75:	/* A == "18dia x2 on gauge lines"*/
			if(m_pItem->m_bPunchUsedFlag[1] == TRUE)
			{
				sPunchMsg += "\n Punch #1 already allocated";
			}
			if(m_pItem->m_bPunchUsedFlag[2] == TRUE)
			{
				sPunchMsg += "\n Punch #2 already allocated";
			}
			break;
		case 121:	/* Q == "18dia x1 on lower gauge line" */
			if(m_pItem->m_bPunchUsedFlag[1] == TRUE)
			{
				sPunchMsg += _T("\n Punch #1 already allocated");
			}
			if(m_pItem->m_bPunchUsedFlag[2] == TRUE)
			{
				sPunchMsg += _T("\n Punch #2 already allocated");
			}
			break;
		case 77:	/* Z == "18dia x1 on upper gauge line"*/
			if(m_pItem->m_bPunchUsedFlag[128] == TRUE)
			{
				sPunchMsg += "\n Punch #128 already allocated";
			}
			if(m_pItem->m_bPunchUsedFlag[64] == TRUE)
			{
				sPunchMsg += "\n Punch #64 already allocated";
			}
			break;
		}
	}
	return false; /* This needs to be sorted out */
}

///////////////////////////////////////////////////////////////////////////////////////
//
bool CBeamElement::CheckLine3ExtraHole(CBeamOps* pBeamOp, long lHoleID, CString& sPunchMsg, CString& sRetainedComment, long& nPreviousHoleType, CString& sDefaultPunch)
{
	CString sComment	= pBeamOp->GetComment();
	bool bDisplayFlag	= false;

	//  Check usage of other punches to find conflicts
	//	if the 'hole comment' or 'hole type' changes
	if (sComment != _T("") && (sComment != sRetainedComment || lHoleID != nPreviousHoleType))
	{
		switch (lHoleID)
		{
		case 109:	/* G == "14dia x2 on gauge lines"  (NB: See Datasheet Y3.711 for "14 dia. holes less than 74mm apart") */
		case 114:	/*   == "2x 14dia x2 at 100c/c on gauge lines" */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCHES #2 AND #7\n";
			if(m_pItem->m_bPunchUsedFlag[2] == TRUE && (CString)m_pItem->m_szPunchGauge[2] != sComment)
			{
				sPunchMsg += "\n Punch #2 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[1] == TRUE && (CString)m_pItem->m_szPunchGauge[2] != sComment)
			{
			/*	sPunchMsg += "\n First Choice for this hole group is Punch #2";
				sPunchMsg += "\n but Punch #1 is allocated for the datum hole.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			*/
			}
			if(m_pItem->m_bPunchUsedFlag[7] == TRUE && (CString)m_pItem->m_szPunchGauge[7] != sComment)
			{
				sPunchMsg += "\n Punch #7 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[8] == TRUE && (CString)m_pItem->m_szPunchGauge[7] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #7";
				sPunchMsg += "\n but Punch #8 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[2] != TRUE && m_pItem->m_bPunchUsedFlag[7] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 110:	/* B == "14dia x1 on lower gauge line" (NB: See Datasheet Y3.711 for "14 dia. holes less than 74mm apart") */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #7\n";
			if(m_pItem->m_bPunchUsedFlag[7] == TRUE && (CString)m_pItem->m_szPunchGauge[7] != sComment)
			{
				sPunchMsg += "\n Punch #7 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[8] == TRUE && (CString)m_pItem->m_szPunchGauge[7] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #7";
				sPunchMsg += "\n but Punch #8 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[7] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 111:	/* R == "14dia x1 on upper gauge line" (NB: See Datasheet Y3.711 for "14 dia. holes less than 74mm apart") */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #2\n";
			if(m_pItem->m_bPunchUsedFlag[2] == TRUE && (CString)m_pItem->m_szPunchGauge[2] != sComment)
			{
				sPunchMsg += "\n Punch #2 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[1] == TRUE && (CString)m_pItem->m_szPunchGauge[2] != sComment)
			{
			/*	sPunchMsg += "\n First Choice for this hole group is Punch #2";
				sPunchMsg += "\n but Punch #1 is allocated for the datum hole.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			*/
			}
			else if(m_pItem->m_bPunchUsedFlag[2] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 112:	/* F == "14dia Both flanges" (NB: See Datasheet Y3.711 for "14 Dia. holes at least 74mm apart") */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCHES #4 AND #5\n";
			if(m_pItem->m_bPunchUsedFlag[4] == TRUE && (CString)m_pItem->m_szPunchGauge[4] != sComment)
			{
				sPunchMsg += "\n Punch #4 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[3] == TRUE && (CString)m_pItem->m_szPunchGauge[4] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #4";
				sPunchMsg += "\n but Punch #3 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			if(m_pItem->m_bPunchUsedFlag[5] == TRUE && (CString)m_pItem->m_szPunchGauge[5] != sComment)
			{
				sPunchMsg += "\n Punch #5 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			if(m_pItem->m_bPunchUsedFlag[6] == TRUE && (CString)m_pItem->m_szPunchGauge[5] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #5";
				sPunchMsg += "\n but Punch #6 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[4] != TRUE && m_pItem->m_bPunchUsedFlag[5] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 106:	/* B == "14dia Bottom C Flange" (NB: See Datasheet Y3.711 for "14 Dia. holes at least 74mm apart") */
		case 134:	// B == "14dia in bottom flange 
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #5\n";
			if(m_pItem->m_bPunchUsedFlag[5] == TRUE && (CString)m_pItem->m_szPunchGauge[5] != sComment)
			{
				sPunchMsg += "\n Punch #5 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			if(m_pItem->m_bPunchUsedFlag[6] == TRUE && (CString)m_pItem->m_szPunchGauge[5] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #5";
				sPunchMsg += "\n but Punch #6 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[5] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 113:	/* R == "14dia Top flange" (NB: See Datasheet Y3.711 for "14 Dia. holes at least 74mm apart") */
		case 133:   // B == 14dia in top flange 
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #4\n";
			if(m_pItem->m_bPunchUsedFlag[4] == TRUE && (CString)m_pItem->m_szPunchGauge[4] != sComment)
			{
				sPunchMsg += "\n Punch #4 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[3] == TRUE && (CString)m_pItem->m_szPunchGauge[4] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #4";
				sPunchMsg += "\n but Punch #3 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[4] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 68:	/*   == "14dia x1 on centre line" */
		case 78:	/*   == "2x 14dia at 100c/c on centre line" */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #12\n";
			if(m_pItem->m_bPunchUsedFlag[12] == TRUE && (CString)m_pItem->m_szPunchGauge[12] != sComment)
			{
				sPunchMsg += "\n Punch #12 already allocated on different gauge line. \n";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[11] == TRUE && (CString)m_pItem->m_szPunchGauge[12] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #12";
				sPunchMsg += "\n but Punch #11 has also been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[12] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 69:	/* == "18dia Both flanges"*/
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCHES #3 AND #6\n";
			if(m_pItem->m_bPunchUsedFlag[3] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n Punch #3 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[4] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #3";
				sPunchMsg += "\n but Punch #4 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			if(m_pItem->m_bPunchUsedFlag[6] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n Punch #6 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[5] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #6";
				sPunchMsg += "\n but Punch #5 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[3] != TRUE && m_pItem->m_bPunchUsedFlag[6] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 70:	/*  == "18dia bottom flange"*/
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #3\n";
			if(m_pItem->m_bPunchUsedFlag[3] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n Punch #3 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[4] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #3";
				sPunchMsg += "\n but Punch #4 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[3] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 71:	/* T == "18dia top flange" */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #6\n";
			if(m_pItem->m_bPunchUsedFlag[6] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n Punch #6 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[5] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #6";
				sPunchMsg += "\n but Punch #5 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[6] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 72:	/* T == "18dia x1 on centre line" */
		case 80:	/*   == "2x 18dia at 100c/c on centre line" */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #13\n";
			if(m_pItem->m_bPunchUsedFlag[13] == TRUE && (CString)m_pItem->m_szPunchGauge[13] != sComment)
			{
				sPunchMsg += "\n Punch #13 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[14] == TRUE && (CString)m_pItem->m_szPunchGauge[13] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #13";
				sPunchMsg += "\n but Punch #14 has also been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[13] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 75:	/* A == "18dia x2 on gauge lines"*/
		case 83:	/*   == "2x 18dia x2 at 100c/c on gauge lines" */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCHES #3 AND #6\n";
			if(m_pItem->m_bPunchUsedFlag[3] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n Punch #3 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[4] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #3";
				sPunchMsg += "\n but Punch #4 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			if(m_pItem->m_bPunchUsedFlag[6] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n Punch #6 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[5] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #6";
				sPunchMsg += "\n but Punch #5 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[3] != TRUE && m_pItem->m_bPunchUsedFlag[6] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 121:	/* Q == "18dia x1 on lower gauge line" */
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #3\n";
			if(m_pItem->m_bPunchUsedFlag[3] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n Punch #3 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[4] == TRUE && (CString)m_pItem->m_szPunchGauge[3] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #3";
				sPunchMsg += "\n but Punch #4 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.\n";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[3] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		case 77:	/* Z == "18dia x1 on upper gauge line"*/
			sDefaultPunch = "\n Press 'OK' to ACCEPT DEFAULT PUNCH #6\n";
			if(m_pItem->m_bPunchUsedFlag[6] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n Punch #6 has already been allocated for another operation";
				sPunchMsg += "\n Press 'Cancel' to REDEFINE PUNCH FOR THIS OPERATION. \n";
				bDisplayFlag = true;
//				this->m_bIsNonStandardHole = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[5] == TRUE && (CString)m_pItem->m_szPunchGauge[6] != sComment)
			{
				sPunchMsg += "\n First Choice for this hole group is Punch #6";
				sPunchMsg += "\n but Punch #5 has already been allocated for another hole type.";
				sPunchMsg += "\n Check for 74mm min. distance between punches.";
				bDisplayFlag = true;
			}
			else if(m_pItem->m_bPunchUsedFlag[6] != TRUE)
			{
				bDisplayFlag = true;
			}
			break;
		}
	}
	return bDisplayFlag;
}
/////////////////////////////////////////////////////////////////////////////
//
void CBeamElement::InterpretGridText(LPCTSTR lpszCellText, CBeamOps* pOperation, int nRow)
{
	// 1. capture the string
	// 2. get the first character
	// 3. check for illegal entries
	// 4. check for dimension op.
	// 5. check for punch op.

	CString		sOperation, sComment;
	LPCTSTR		lpszOpText;
	long		nScriptID;		/*	database reference for SPC script for specific section/line setup
									this is used in SQL to limit number of records returned in dynaset
									the same technique is used for additional holes but there is no associated script
									since a 'NON' spc will require specification of all individial holes
									the scriptID used for NON will be used for all additional holes regardless of the
									spc for the element as a whole.  A default value of 10 may be used */

/*	long		m_nSeqID;		//	incremental sequence number (irrespective of whether dim or punch)
	CString		m_sOpType;		//	type of operation (Generic|Dimension|Punch)
	CString		m_sOperation;	//	operation text as specified in OD3 database operation scripts or by user input
	CString		m_sComment;		//	comment attached to an additional hole in 'd3' beam
	bool		m_bAbsolute;	//	absolute|relative dimension indicator
	bool		m_bPositive;	//	positive|negative dimension indicator
	bool		m_bMultiplied;	//	multiply(true)|divide(false) dimension modification indicator
	int			m_nMultiplier;	//	value used as a dimension modifier based on value of m_nMultiplied
*/

	if(strlen(lpszCellText) > 6)
	{
		// we got a D3 additional hole description
		nScriptID = 10;
		sOperation = _T("Punch");
		lpszOpText = (LPCTSTR)sOperation;

/*
#ifdef _DEBUG
			CString szMsg = "CBeamOps object @ ";
			CString szPointer = _T("");
			szPointer.Format("%p",pOperation);
			szMsg += szPointer;
			szMsg += "\nD3 AdditionalHole - ";
			szMsg += (CString)lpszCellText;
			szMsg += "\n\nScript: ";
			CString szScript = _T("");
			szScript.Format("%.6li",nScriptID);
			szMsg += szScript;
			AfxMessageBox(szMsg);
#endif
*/
		pOperation->SetScriptID(nScriptID);
		pOperation->SetOpType(lpszOpText);
		pOperation->SetAbsolute(true);
		pOperation->SetPositive(true);
		pOperation->SetMultiplied(true);
		pOperation->SetMultiplier(1);
		pOperation->SetOperation(lpszCellText);

		COD3GridCtrl *pGrid = (COD3GridCtrl*)m_pDoc->m_pBeamModeless->GetDlgItem(IDC_EXTRA_HOLE_GRID);
		// Get the comment text
		sComment = pGrid->GetCellText(nRow, 6, 0);
		pOperation->SetComment(sComment.GetBuffer(sComment.GetLength()));
		return;
	}

	if(*lpszCellText < 48)		// it is neither a number nor an uppercase character
	{
		switch (*lpszCellText)
		{
		case 42: /*  "*"  */
			// we've got a multiplier!!
			pOperation->SetMultiplied(true);
			// and its value is -
			pOperation->SetMultiplier(atoi(lpszCellText));
			// VHF TODO:  Do we need to support this operation for manual input ??
			AfxMessageBox("This operation is not supported");
			break;
		case 43: /* "+"  */
			// its a relative dimension and its positive
			nScriptID = 10;
			sOperation = _T("Dim");
			lpszOpText = (LPCTSTR)sOperation;
			pOperation->SetScriptID(nScriptID);	// default ID for "NON" used for all additional holes
			pOperation->SetOpType(lpszOpText);
			pOperation->SetAbsolute(false);
			pOperation->SetPositive(true);
			pOperation->SetMultiplied(true);
			pOperation->SetMultiplier(1);
			pOperation->SetOperation(lpszCellText);
			break;
		case 45: /* "-"  */
			// its a relative dimension and its negative
			nScriptID = 10;
			sOperation = _T("Dim");
			lpszOpText = (LPCTSTR)sOperation;
			pOperation->SetScriptID(nScriptID);	// default ID for "NON" used for all additional holes
			pOperation->SetOpType(lpszOpText);
			pOperation->SetAbsolute(false);
			pOperation->SetPositive(false);
			pOperation->SetMultiplied(true);
			pOperation->SetMultiplier(1);
			pOperation->SetOperation(lpszCellText);
			break;
		case 47: /*  "/"  */
			// we've got a divisor!!
			pOperation->SetMultiplied(false);
			// and its value is -
			pOperation->SetMultiplier(atoi(lpszCellText));
			// VHF TODO:  Do we need to support this operation for manual input ??
			AfxMessageBox("This operation is not supported");
			break;
		case 35:
			// its a hash punch code
			nScriptID = 10;
			sOperation = _T("Punch");
			lpszOpText = (LPCTSTR)sOperation;
			pOperation->SetScriptID(nScriptID);
			pOperation->SetOpType(lpszOpText);
			pOperation->SetAbsolute(true);
			pOperation->SetPositive(true);
			pOperation->SetMultiplied(true);
			pOperation->SetMultiplier(1);
			pOperation->SetOperation(lpszCellText);
			break;
		default:
			AfxMessageBox(_T("Illegal entry"));
			break;
		}
	}
	// check for dimension op.
	else if (*lpszCellText >47 && *lpszCellText <58)
	{
		// we've got an absolute dimension
		nScriptID = 10;						// This may be dangerous TO DO: add code to test SPC then use script ID 20 or 30 depending on NONP or NONR
		sOperation = _T("Dim");
		lpszOpText = (LPCTSTR)sOperation;
		pOperation->SetScriptID(nScriptID);	// default ID for "NON" used for all additional holes
		pOperation->SetOpType(lpszOpText);
		pOperation->SetAbsolute(true);
		pOperation->SetPositive(true);
		pOperation->SetMultiplied(true);
		pOperation->SetMultiplier(1);
		pOperation->SetOperation(lpszCellText);
	}

	// check for punch op
	else if (*lpszCellText >64 && *lpszCellText <91)
	{
		// we've got a punch operation
		nScriptID = 10;
		sOperation = _T("Punch");
		lpszOpText = (LPCTSTR)sOperation;
		pOperation->SetScriptID(nScriptID);
		pOperation->SetOpType(lpszOpText);
		pOperation->SetAbsolute(true);
		pOperation->SetPositive(true);
		pOperation->SetMultiplied(true);
		pOperation->SetMultiplier(1);
		pOperation->SetOperation(lpszCellText);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	RemoveXtraHoleList()	A function to delete CBeamOp objects and remove the list of pointers
//
void CBeamElement::RemoveXtraHoleList()
{
	POSITION pos = this->m_tplAddList.GetHeadPosition();
	CBeamOps* pBeamOp;
	while (pos)	
	{
		pBeamOp = m_tplAddList.GetNext(pos);
		delete pBeamOp;
	}
	m_tplAddList.RemoveAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CBeamElement::UpdateProgressIndicator(int cOpCounter)
{
	CMainFrame	*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	CRect		sbRect;

	pMainFrm->m_wndStatusBar.GetItemRect(1, &sbRect);  

	if (pMainFrm->m_bProgCreated == false)
	{
		//Create the progress control
		pMainFrm->m_progressBar.Create(WS_VISIBLE|WS_CHILD, 
										sbRect, &pMainFrm->m_wndStatusBar, 1); 

		// Set the range
		pMainFrm->m_progressBar.SetRange(0, 10); 
		// Set the step amount
		pMainFrm->m_progressBar.SetStep(1); 
		pMainFrm->m_bProgCreated = true;
	}

	// Move progress pos
	pMainFrm->m_progressBar.StepIt();

	return;
}

void CBeamElement::UpdateStatusBar(LPCTSTR lpszText)
{
	CWinApp* pApp;
	CMainFrame* pAppWnd;
	pApp = AfxGetApp();
	pAppWnd = (CMainFrame*)pApp->m_pMainWnd;

	pAppWnd->StatusBarMsgUpdate(lpszText);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class CAccessoryElement
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CAccessoryElement,CElement,0)

CAccessoryElement::CAccessoryElement()
{
	m_nType = 5;
}

CAccessoryElement::~CAccessoryElement()
{
	CAccOps*	pAccOp;
	POSITION	pos;
	
	if (!m_tplOpList.IsEmpty())
	{
		for (pos = m_tplOpList.GetHeadPosition();pos != NULL;)
		{
			pAccOp = m_tplOpList.GetNext(pos);
			delete pAccOp;
		}
	}
}

void CAccessoryElement::Serialize(CArchive &ar)
{
	int	i;
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_nQty;
		ar << m_sComment;
		ar << m_nBdlQty;
		ar << m_iSleeveLength;

		for(i=0; i< (sizeof(m_iField) / sizeof(m_iField[0])); i++)
		{
			ar << m_iField[i];
		}
		
	}
	else
	{
		ar >> m_nQty;
		ar >> m_sComment;
		ar >> m_nBdlQty;
		ar >> m_iSleeveLength;

		for(i=0; i< (sizeof(m_iField) / sizeof(m_iField[0])); i++)
		{
			ar >> m_iField[i];
		}
	}
	m_tplOpList.Serialize(ar);
}

// NEED TO FORCE ACTUAL VALUES //
double CElement::modifyPunchCodes(int line, CString partName, CString punchCode, double orgCode)
{
	CString		buffer;
	double		modified = -1.0L;

	// Clear double strike punch code and feed
	m_hitTwo=m_extraFeed=m_hitThree = 0.0L;

	// Convert partname
	switch(getPart(partName))
	{
		// Zeta 2
		case IDS_PART1:
			modified = zeta2(line, partName, punchCode, orgCode);
			break;

		// Eaves
		case IDS_PART2:
			modified = eaves(line, partName, punchCode, orgCode);
			break;

		// Cee
		case IDS_PART3:
			modified = cee(line, partName, punchCode);
			break;

		// Zed 125-200
		case IDS_PART4:
			modified = zed(line, partName, punchCode, orgCode);
			break;

		// 1/200
		case IDS_PART5:
			modified = z1_200(line, partName, punchCode);
			break;

		// Z/300
		case IDS_PART6:
			modified = z240_300(line, partName, punchCode, orgCode);
			break;

		// Z/240
		case IDS_PART7:
			modified = z240_300(line, partName, punchCode, orgCode);
			break;

		// Zeta1 (1/125 1/150 1/170)
		case IDS_PART8:
		case IDS_PART9:
		case IDS_PART10:
			modified = zeta(line, partName, punchCode, orgCode);
			break;
	}
	
	if(modified == -1)
		AfxMessageBox("Modified = -1 using punchcode: "+punchCode + "  Partnumber: " + partName + 
						" Please inform developer of punch error.\n\n\t\t\tDo not use this output.");

	return(modified);
}

int CElement::getPart(CString partRef)
{
	int		pos, i, number, part=IDS_PART1;
	CString	partCode;
	CString	partSearch;
	bool	ceeSection=false;


	// Find '/' in the part name
	if((pos = partRef.Find('/')) <= 0)
	{
		// Perform search for eaves
		if( (pos = partRef.Find("EB",0)) != -1)
			pos++;
		else if( (pos = partRef.Find("SB2", 0)) != -1 ||
					(pos = partRef.Find("SB3", 0)) != -1)
		{
			// Swagebeam product dont modify pos as there are no SBE products
			// for these products
		}
		else if( (pos = partRef.Find("PRESS", 0)) != -1)
		{
			// Pressed section implement like C
			part=IDS_PART3;
			return(part);
		}
		else
		{	
			pos=partRef.Find("C");
			// Test for Cee section
			if((pos != -1))
			{
				ceeSection = true;
				partSearch.Insert(0, partRef.Mid(pos, 1));
			}
		}
	}

	if(!ceeSection)
	{
		// Perform final test for 1/ variants
		if(partRef.Find(_T("1/")) >=0 )
		{
			// Load size into string
			partSearch=partRef.Mid(pos-1, 5);
		}
		else
		{
			// Get part test string
			partSearch.Insert(0, partRef.Mid(pos-1, 2));
		}
	}

	// If part returns a Z perform further test
	if(!partSearch.CompareNoCase("Z/"))
	{
		number = atoi(partRef.Mid(pos+1, partRef.GetLength()-pos));

		if(number==240 || number==300)
		{
			partSearch.Format("%i", number);
		}
	}

	for(i=0; i<(ITEMCOUNT+1); i++)
	{
		// Load part int resource
		partCode.LoadString(part);
		//if(partCode.Find(partSearch, 0) == 0)
		if(!partCode.CompareNoCase(partSearch))
			break;

		// Move to next resource value
		part++;
	}

	if(i>ITEMCOUNT)
		part = 0;

	// Return selected part
	return(part);
}

// Modify Zeta2 on line3 punch codes
double CElement::zeta2(int line, CString partName, CString punchCode, double orgCode)
{
	double	modified = -1.0L;


	// Test line number
	switch(line)
	{
		case 2:
		{
			if(!punchCode.CompareNoCase("A"))
			{
				// Upper and lower fixing holes (18 Dia)
				/******* use compound instructions *******
				modified = 1;
				m_hitTwo = 2;
				******************************************/
				modified = 3;
			}
			else if(!punchCode.CompareNoCase("S"))
			{	
				// Sag bar (14 Dia square)
				modified = 4;
			}
			else if(!punchCode.CompareNoCase("T"))
			{
				// Top flange hole (14 Dia)
				modified = 64;
			}
			else if(!punchCode.CompareNoCase("B"))
			{
				// Bottom flange hole (14 Dia)
				modified = 16;
			}
			else if(!punchCode.CompareNoCase("D"))
			{
				// Double hit two A punches with a seperation of 100
				//modified = 1.0L;
			}
			else if(!punchCode.CompareNoCase("G"))
			{
				// Top and bottom flange hole (14 Dia)
				modified = 32;
			}
			else if(!punchCode.CompareNoCase("J"))
			{
				// Requires two punches (18 Dia slot pair)
				/******* use compound instructions *******
				modified = 1;
				m_hitTwo = 2;
				*****************************************/
				modified = 3;
			}
			else if(!punchCode.CompareNoCase("M"))
			{
				// 18 Dia slot lower fixing slot
				modified = 2;
			}
			else if(!punchCode.CompareNoCase("Z") ||
				(!punchCode.CompareNoCase("#2") && !m_extra) )
			{
				// 18 Dia lower fixing hole
				modified = 2;
			}
			else
			{
				// Test for hash code (manual entries)
				modified = stripHashCode(punchCode, line);
			}
		}
		break;

		case 3:
		{
			// Compare punch codes
			if(!punchCode.CompareNoCase("A"))
			{
				modified = pow(2, 2);
			}
			else if(!punchCode.CompareNoCase("S"))
			{	
				modified = pow(2, 4);
			}
			else if(!punchCode.CompareNoCase("T"))
			{
				modified = orgCode;
			}
			else if(!punchCode.CompareNoCase("B"))
			{
				modified = orgCode;
			}
			else if(!punchCode.CompareNoCase("D"))
			{
				// Double hit two A punches with a seperation of 100
				m_hitTwo=modified = pow(2 ,2);
				m_extraFeed = 100;
			}
			else if(!punchCode.CompareNoCase("G"))
			{
				modified = pow(2, 12);
			}
			else if(!punchCode.CompareNoCase("H"))
			{
				modified = pow(2, 2);
			}
			else if(!punchCode.CompareNoCase("M"))
			{
				//modified = pow(2, 10);
			}
			else if(!punchCode.CompareNoCase("Z"))
			{
				modified = pow(2, 2);
			}
			else
			{
				// Test for hash code (manual entries)
				modified = stripHashCode(punchCode, line);
			}
		}
		break;
	}


	return(modified);
}

double CElement::eaves(int line, CString partName, CString punchCode, double orgCode)
{
	double	modified = -1.0L;
	CString size;


	// Test line number
	switch(line)
	{
	case 2:
		// Eaves 240 //////////////////////////////////////////////
		// Three hit punch code
		if(!punchCode.CompareNoCase("AZ"))
		{
			/***** Use compound instruction *****
			// Webbing 1
			modified = 2;	
			// Webbing 2
			m_hitTwo = 1;	
			// Bottom
			m_hitThree = 128;
			*************************************/
			modified = 131;
		}
		// Compare punch codes
		else if(!punchCode.CompareNoCase("QZ"))
		{
			/***** Use compound instruction *****
			// Webbing 1
			modified = 1;
			// Webbing 2
			m_hitTwo = 2;
			*************************************/
			modified = 3;
		}
		///////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////
		//Eaves 160 ///////////////////////////////////////////////
		// Compare punch codes
		else if(!punchCode.CompareNoCase("CZ"))
		{
			/***** Use compound instruction *****
			// Centre line
			modified = 1;	
			// Bottom
			m_hitTwo = 2;
			************************************/
			modified = 3;
		}
		
		else if(!punchCode.CompareNoCase("BB"))
		{	
			// Lower punch
			size = partName.Mid(partName.GetLength()-3);

			// Test beam gauge and change punch to suit
			if(atoi(size) == 160)
				modified = 2;
			else if(atoi(size) == 240)
				modified = 128;
		}
		else if(!punchCode.CompareNoCase("C"))
		{
			// Centre line
			modified = 1;
		}
		else
		{
			// Test for hash code (manual entries)
			modified = stripHashCode(punchCode, line);
		}
		break;


	case 3:
		if(!punchCode.CompareNoCase("AZ"))
		{
			modified = orgCode;
		}
		// Compare punch codes
		else if(!punchCode.CompareNoCase("QZ"))
		{
			modified = pow(2, 2) + pow(2, 3);
		}
		else if(!punchCode.CompareNoCase("CZ"))
		{
			modified = orgCode;
		}
		else if(!punchCode.CompareNoCase("BB"))
		{	
			// Lower punch
			modified = pow(2, 8);
			/*
			size = partName.Mid(partName.GetLength()-3);
			
			// Test beam gauge and change punch to suit
			if(atoi(size) == 160)
				modified = 2;
			else if(atoi(size) == 240)
				modified = 128;
			*/
		}
		else if(!punchCode.CompareNoCase("C"))
		{
			// Centre line
			modified = pow(2, 11);
		}
		else if(!punchCode.CollateNoCase("T"))
		{
			// Top flange hole 14dia
			modified = pow(2, 13);
		}
		else if(!punchCode.CollateNoCase("B"))
		{
			// Bottom flange hole 14dia
			modified = pow(2, 12);
		}
		else if(!punchCode.CollateNoCase("G"))
		{
			// Both flange holes 14dia
			modified = pow(2, 13) + pow(2, 12);
		}
		else if(!punchCode.CollateNoCase("R"))
		{
			// Upper fixing hole 14dia
			modified = pow(2, 5);
		}
		else if(!punchCode.CollateNoCase("F"))
		{
			// Both fixing holes 14dia
			modified = pow(2, 5) + pow(2, 4);
		}
		else if(!punchCode.CollateNoCase("V"))
		{
			// Bottom fixing hole 14dia
			modified = pow(2, 4);
		}
		else
		{
			// Test for hash code (manual entries)
			modified = stripHashCode(punchCode, line);
		}
		break;
	}

	return(modified);
}

double CElement::zed(int line, CString partName, CString punchCode, double orgCode)
{
	int		pos=0, pNum=0;
	double	modified = -1.0L;
	CString	partNum;

	// Get the partnumber
	pos = partName.Find('/');

	partNum = partName.Mid(pos+1, partName.GetLength());
	pNum = atoi(partNum);

	// Test line number
	switch(line)
	{
	// Line 2
	case 2:
		// Test part variant
		if(pNum > 155)
		{
			if(!punchCode.CompareNoCase("V"))
			{
				// Fixing holes
				punchCode = _T("F");
			}

			// Compare punch codes
			if(!punchCode.CompareNoCase("F"))
			{
				// Double 14 dia round
				modified = 32;
			}
			else if(!punchCode.CompareNoCase("S"))
			{
				// Double hit two square punches (100c/c handled)
				modified = 4;
			}
			else if(!punchCode.CompareNoCase("V"))
			{	
				// Not possible to punch seperate fixing holes
				// lower 14 dia fixing hole cant do this
				//modified = -1; 
			}
			else if(!punchCode.CompareNoCase("H"))
			{
				// 14 dia 25 slot (have to loop) USE SQUARE
				modified = 4;
			}
			else if(!punchCode.CompareNoCase("#11") /*&& !m_extra*/)
			{
				// Not possible to punch seperate fixing holes
				// lower 14 dia 25 slot (have to loop) cant do this so punch both
				// USE SQUARES
				modified = 4;
			}
			else if(!punchCode.CompareNoCase("#36") && !m_extra)
			{
				// Double hit two square punches (100c/c handled)
				modified = 4;
			}
			else if(!punchCode.CompareNoCase("T"))
			{
				// Flange hole 14 dia.
				modified = 64;
			}
			else if(!punchCode.CompareNoCase("B"))
			{
				// Flange hole 14 dia.
				modified = 16;
			}
			else if(!punchCode.CompareNoCase("G"))
			{
				// Sheeted flange hole 14 dia. Top and bottom
				modified = 16;
				m_hitTwo = 64;
			}
			else
			{
				// Test for hash code (manual entries)
				modified = stripHashCode(punchCode, line);
			}
		}
		else
		{
			if(!punchCode.CompareNoCase("B") || (!punchCode.CompareNoCase("T")))
			{
				// Not possible to punch seperate holes in flanges
				// Set to double punch
				punchCode = _T("G");

			}

			// Compare punch codes
			if(!punchCode.CompareNoCase("F"))
			{
				// Double 14 dia round
				modified = 16;
				m_hitTwo = 64;
			}
			else if(!punchCode.CompareNoCase("V"))
			{	
				// lower 14 dia fixing hole
				modified = 16; //64;
			}
			else if(!punchCode.CompareNoCase("H"))
			{
				// 14 dia 25 slot (have to loop)
				modified = 2;
				m_hitTwo = 4;
			}
			else if(!punchCode.CompareNoCase("#11") /*&& !m_extra*/)
			{
				// lower 14 dia 25 slot (have to loop)
				modified = 2;
			}
			else if((!punchCode.CompareNoCase("#36") && !m_extra) || !punchCode.CompareNoCase("S"))
			{
				// Double hit two square punches (100c/c handled)
				modified = 2;
				m_hitTwo = 4;
			}
			else if(!punchCode.CompareNoCase("T"))
			{
				// Sheeted flange hole 14 dia.cant do this
				//modified = -1;
			}
			else if(!punchCode.CompareNoCase("B"))
			{
				// Sheeted flange hole 14 dia.cant do this
				//modified = -1;
			}
			else if(!punchCode.CompareNoCase("G"))
			{
				// Sheeted flange hole 14 dia. Top and bottom
				modified = 32;
			}
			else
			{
				// Test for hash code (manual entries)
				modified = stripHashCode(punchCode, line);
			}
		}
		break;

	// Line 3
	case 3:
		// Test part variant
		if(pNum > 155)
		{
			// Compare punch codes
			if(!punchCode.CompareNoCase("F"))
			{
				// Double 14 dia round
				modified = pow(2, 12);
			}
			else if(!punchCode.CompareNoCase("S"))
			{
				// Double hit two square punches (100c/c handled)
				modified = pow(2, 4);
			}
			else if(!punchCode.CompareNoCase("V"))
			{	
				// lower 14 dia fixing hole 
				modified = pow(2, 12);
			}
			else if(!punchCode.CompareNoCase("H"))
			{
				// 14 dia 25 slot
				modified = pow(2, 6);
			}
			else if(!punchCode.CompareNoCase("#11"))
			{
				// lower 14 dia 25 slot
				modified = pow(2, 6);
			}
			/*
			else if(!punchCode.CompareNoCase("#36") && !m_extra)
			{
				// Double hit two square punches (100c/c handled)
				modified = pow(2, 3); 
			}
			*/
			else if(!punchCode.CompareNoCase("T"))
			{
				// Flange hole 14 dia.
				modified = pow(2, 1);
			}
			else if(!punchCode.CompareNoCase("B"))
			{
				// Flange hole 14 dia.
				modified = pow(2, 2);
			}
			else if(!punchCode.CompareNoCase("G"))
			{
				// Sheeted flange hole 14 dia. Top and bottom
				modified = pow(2, 1) + pow(2, 2);
			}
			else
			{
				// Test for hash code (manual entries)
				modified = stripHashCode(punchCode, line);
			}
		}
		else // Small Zeds
		{
			// Compare punch codes
			if(!punchCode.CompareNoCase("F"))
			{
				// Double 14 dia round
				modified = pow(2, 2) + pow(2, 13);
			}
			else if(!punchCode.CompareNoCase("V"))
			{	
				// lower 14 dia fixing hole
				modified = pow(2, 2);
			}
			else if(!punchCode.CompareNoCase("H"))
			{
				// 14 dia 25 slot
				modified = pow(2, 6) + pow(2, 5);
			}
			else if(!punchCode.CompareNoCase("#11"))
			{
				// lower 14 dia slot
				modified = pow(2, 6);
			}
			else if(/*(!punchCode.CompareNoCase("#36") && !m_extra) ||*/ 
				!punchCode.CompareNoCase("S"))
			{
				// Double hit two square punches (100c/c handled)
				modified = pow(2, 7) + pow(2, 4);
			}
			else if(!punchCode.CompareNoCase("T"))
			{
				// Sheeted flange hole 14
				modified = pow(2, 1);
			}
			else if(!punchCode.CompareNoCase("B"))
			{
				// Sheeted flange hole 14 dia
				modified = orgCode;
			}
			else if(!punchCode.CompareNoCase("G"))
			{
				// Sheeted flange hole 14 dia. Top and bottom
				modified = pow(2, 1) + pow(2, 12);
			}
			else
			{
				// Test for hash code (manual entries)
				modified = stripHashCode(punchCode, line);
			}
		}
		break;
	}


	return(modified);
}


double CElement::z1_200(int line, CString partName, CString punchCode)
{
	double	modified = -1.0L;


	// Test line number
	switch(line)
	{
	case 2:
		// Compare punch codes
		if(!punchCode.CompareNoCase("A") || !punchCode.CompareNoCase("L"))
		{
			// Single and double fixing holes
			/******* use compound instructions *******
			modified = 8;
			m_hitTwo = 128;
			*****************************************/
			modified = 136;
		}
		else if(!punchCode.CompareNoCase("D"))
		{
			// Double fixing holes C/L 100
			/******* use compound instructions *******
			modified = 8;
			m_hitTwo = 128;
			*****************************************/
			modified = 136;
		}
		else if(!punchCode.CompareNoCase("#64") && !m_extra)
		{
			// Lower fixing holes
			modified = 128;
		}
		else if(!punchCode.CompareNoCase("H"))
		{
			// Slotted double fixing holes (18 * 25)
			/******* use compound instructions *******
			modified = 8;
			m_hitTwo = 128;	
			*****************************************/
			modified = 136;
		}
		else if( (!punchCode.CompareNoCase("#20") && !m_extra) || 
					!punchCode.CompareNoCase("C"))
		{
			// Slotted lower fixing holes (18 * 25)
			modified = 128;	
		}
		else if(!punchCode.CompareNoCase("S") || !punchCode.CompareNoCase("X"))
		{
			// Double sag bar holes
			/******* use compound instructions *******
			modified = 2;
			m_hitTwo = 4;
			*****************************************/
			modified = 6;
		}
		else if(!punchCode.CompareNoCase("T"))
		{
			// Top flange hole
			modified = 64;
		}
		else if(!punchCode.CompareNoCase("B"))
		{
			// Bottom flange hole
			modified = 16;
		}
		else if(!punchCode.CompareNoCase("G"))
		{
			// Top and bottom flange holes
			/******* use compound instructions *******
			modified = 64;
			m_hitTwo = 16;
			*****************************************/
			modified = 80;
		}
		else if(!punchCode.CompareNoCase("Z"))
		{
			// Lower fixing holes
			modified = 128;
		}
		else
		{
			// Test for hash code (manual entries)
			modified = stripHashCode(punchCode, line);
		}
		break;


	case 3:
		// Compare punch codes
		if(!punchCode.CompareNoCase("A") || !punchCode.CompareNoCase("L"))
		{
			// Single and double fixing holes
			modified = pow(2, 3) + pow(2, 8);
		}
		else if(!punchCode.CompareNoCase("D"))
		{
			// Double fixing holes C/L 100
			modified = pow(2, 3) + pow(2, 14);
		}
		/*
		else if(!punchCode.CompareNoCase("#64") && !m_extra)
		{
			// Lower fixing holes
			modified = pow(2, 14);
		}
		*/	  /*!punchCode.CompareNoCase("H")*/
		else if(!punchCode.CompareNoCase("J") || !punchCode.CompareNoCase("#20"))
		{
			// Slotted double fixing holes (18 * 25) (#20 lower gauge line slotted hole)
			modified = pow(2, 3) + pow(2, 8);
		}
		else if(!punchCode.CompareNoCase("C"))
		{
			// Slotted lower fixing holes (18 * 25)
			modified = pow(2, 8);
		}
		else if(!punchCode.CompareNoCase("S") || !punchCode.CompareNoCase("X")
			|| !punchCode.CompareNoCase("W"))
		{
			// Double sag bar holes
			modified = pow(2, 7) + pow(2, 4);
		}
		else if(!punchCode.CompareNoCase("T"))
		{
			// Top flange hole
			modified = pow(2, 1);
		}
		else if(!punchCode.CompareNoCase("B"))
		{
			// Bottom flange hole
			modified = pow(2, 12);
		}
		else if(!punchCode.CompareNoCase("G"))
		{
			// Top and bottom flange holes
			modified = pow(2, 1) + pow(2, 12);
		}
		else if(!punchCode.CompareNoCase("Z"))
		{
			// Lower fixing holes
			modified = pow(2, 8);
		}
		else
		{
			// Test for hash code (manual entries)
			modified = stripHashCode(punchCode, line);
		}
		break;
	}


	return(modified);
}

void CElement::modifyHoleProcess(CString lineIdent, CString sectionID, CString sPunch, int *on_Line)
{

	// ZED 125 - 200 or 1/200
	if(lineIdent != "Line_1" && 
		(getPart(sectionID)==IDS_PART4 || getPart(sectionID)==IDS_PART5)
		&& (sPunch == "H" || sPunch == "#11" || sPunch == "#20"))
	{
		*on_Line = false;
	}

	
	return;
}

double CElement::z240_300(int line, CString partName, CString punchCode, double orgCode)
{
 	double modified = -1.0L;
 
 
 	// Test line number
 	if(line==3)
 	{
 		// Compare punch codes				   // Slotted 18 dia holes
 		if(!punchCode.CompareNoCase("A") || !punchCode.CompareNoCase("H"))
 		{
 			// 18 dia fixing holes
 			modified = pow(2, 2);
 		}
 		else if(!punchCode.CompareNoCase("S"))
 		{
 			// Square holes
 			modified = orgCode;
 		}
 		else if(!punchCode.CompareNoCase("T"))
 		{
 			// 14 dia flange hole
 			modified = pow(2, 12);
 		}
 		else if(!punchCode.CompareNoCase("B"))
 		{
 			// 14 dia flange hole
 			modified = pow(2, 12);	
 		}
 		else if(!punchCode.CompareNoCase("G"))
 		{
 			// Top and bottom flange holes
 			modified = orgCode;
 		}
		else if(!punchCode.CompareNoCase("LH"))
		{
			// Not a conventional punch code Lower Slot (only changed on Z300 line 3)
			modified = pow(2, 10);
		}
 		else
 		{
 			// Test for hash code (manual entries)
 			modified = stripHashCode(punchCode, line);
 		}
 	}
 	else if(line==2)
 	{
 
 		// Use the new punch code layout
 		if(!punchCode.CompareNoCase("A"))
 		{
 			// Upper and lower fixing holes (18 Dia)
 			/******* use compound instructions *******
 			modified = 1;
			m_hitTwo = 2;
 			******************************************/
 			modified = 3;
 		}
 		else if(!punchCode.CompareNoCase("S"))
 		{	
 			// Sag bar (14 Dia square)
 			modified = 4;
 		}
 		else if(!punchCode.CompareNoCase("T"))
 		{
 			// Top flange hole (14 Dia)
 			modified = 16;
 		}
 		else if(!punchCode.CompareNoCase("B") || !punchCode.CompareNoCase("#8"))
 		{
 			// Bottom flange hole (14 Dia)
 			modified = 64;
 		}
 		else if(!punchCode.CompareNoCase("D"))
 		{
 			// Double hit two A punches with a seperation of 100
 			//modified = 1.0L;
 		}
		else if(!punchCode.CompareNoCase("G"))
 		{
 			// Top and bottom flange hole (14 Dia)
 			modified = 32;
 		}
 		else if(!punchCode.CompareNoCase("J"))
 		{
 			// Requires two punches (18 Dia slot pair)
 			/******* use compound instructions *******
 			modified = 1;
 			m_hitTwo = 2;
 			*****************************************/
 			modified = 3;
 		}
 		else if(!punchCode.CompareNoCase("M"))
 		{
 			// 18 Dia slot lower fixing slot
 			modified = 2;
 		}
 		else if(!punchCode.CompareNoCase("Z") ||
 			(!punchCode.CompareNoCase("#2") && !m_extra) )
 		{
 			// 18 Dia lower fixing hole
 			modified = 2;
 		}
 		else
 		{
 			// Test for hash code (manual entries)
 			modified = stripHashCode(punchCode, line);
 		}
	}
 
 
 	return(modified);
}

// Look up modified tools and allow a modified punch pass
bool CElement::allowModPass(int lineNum, CString sectionID)
{

/* For line mods debug display ***/
//#define SHOWLINE 1
/*********************************/

	extern	CProductMods prodMods;
	int	i,	partID;
	bool	result=false;
	CString resource;

	// Clear double strike punch code and feed
	m_hitTwo=m_extraFeed=m_hitThree = 0.0L;

	if(prodMods.fileOK)
	{
		partID = getPart(sectionID);
		resource.LoadString(partID);

		switch(lineNum)
		{
			case 1:
				for(i=0; i<12; i++)
				{
					if(prodMods.m_line1[i] && !resource.CompareNoCase(prodMods.m_lineDes[i]))
					{
						// Matched product code and line mods are active
						result=true;
#ifdef SHOWLINE
						AfxMessageBox("Line1 "+ sectionID);
#endif
						break;
					}
				}
				break;

			case 2:
				for(i=0; i<12; i++)
				{
					if(prodMods.m_line2[i] && !resource.CompareNoCase(prodMods.m_lineDes[i]))
					{
						// Matched product code and line mods are active
						result=true;
#ifdef SHOWLINE
						AfxMessageBox("Line2 "+ sectionID);
#endif
						break;
					}
				}
				break;

			case 3:
				for(i=0; i<12; i++)
				{
					if(prodMods.m_line3[i] && !resource.CompareNoCase(prodMods.m_lineDes[i]))
					{
						// Matched product code and line mods are active
						result=true;
#ifdef SHOWLINE
						AfxMessageBox("Line3 "+ sectionID);
#endif
						break;
					}
				}
				break;
		}
	}
	else
	{
		if(prodMods.warn)
		{
			// Warn user about possible punch code fault
			AfxMessageBox(IDS_MISSINGCONFIG, MB_ICONWARNING);
			// Display once
			prodMods.warn = false;
		}
	}

	return(result);
}

double CElement::cee(int line, CString partName, CString punchCode)
{
	double	modified = -1.0L;

	// Test line number
	switch(line)
	{
	case 2:
		// Compare punch codes
		if(!punchCode.CompareNoCase("G"))
		{
			// Top and bottom flange (14 Dia)
			modified = 32;
		}
		else if(!punchCode.CompareNoCase("B"))
		{
			// Lower flange hole (14 Dia) (have to punch top and bottom)
			modified = 32;
		}
		else if(!punchCode.CompareNoCase("T"))
		{
			// Top flange hole (14 Dia) (have to punch top and bottom)
			modified = 32;
		}
		else if(!punchCode.CompareNoCase("N") || !punchCode.CompareNoCase("L"))
		{
			// Centre line (14 Dia)
			modified = 4;
		}
		else if(!punchCode.CompareNoCase("V"))
		{
			// Lower fixing hole (14 Dia)
			modified = 16;
		}
		else if(!punchCode.CompareNoCase("R"))
		{
			// Upper fixing hole (14 Dia)
			modified = 64;
		}
		else if(!punchCode.CompareNoCase("F"))
		{
			// Lower and Upper fixing holes (14 Dia)
			modified = 16;
			m_hitTwo = 64;
		}
		else if(!punchCode.CompareNoCase("GG"))
		{
			// Top and bottom flange holes (18 Dia) NOT POSSIBLE WITH STANDARD PRESS SETTINGS
			modified = 3;
		}
		else if(!punchCode.CompareNoCase("TT"))
		{
			// Upper flange hole (18 Dia) NOT POSSIBLE WITH STANDARD PRESS SETTINGS
			modified = -1;
		}
		else if(!punchCode.CompareNoCase("BB"))
		{
			// Lower flange hole (18 Dia) NOT POSSIBLE WITH STANDARD PRESS SETTINGS
			modified = 2;
		}
		else if(!punchCode.CompareNoCase("C"))
		{
			// Centre line (18 Dia)
			modified = 1;
		}
		else if(!punchCode.CompareNoCase("Z"))
		{
			// Lower fixing hole (18 Dia)
			modified = 128;
		}
		else if(!punchCode.CompareNoCase("Q"))
		{
			// Upper fixing hole (18 Dia)
			modified = 8;
		}
		else if(!punchCode.CompareNoCase("A"))
		{
			// Upper and lower fixing holes (18 Dia)
			modified = 8;
			m_hitTwo = 128;	
		}
		else if(!punchCode.CompareNoCase("U"))
		{
			// 100 C/L on centre line (14 Dia)
			modified = 4;
		}
		else if(!punchCode.CompareNoCase("K")) // F
		{
			// 100 C/L upper and lower fixing holes (14 Dia)
			modified = 16;
			m_hitTwo = 64;	
		}
		else if(!punchCode.CompareNoCase("E"))
		{
			// 100 C/L on centre line (18 Dia)
			modified = 1;
			m_hitTwo = 1;
		}
		else if(!punchCode.CompareNoCase("D")) // A
		{
			// 100 C/L upper and lower fixing holes (18 Dia)
			modified = 8;
			m_hitTwo = 128;	
		}
		else
		{
			// Test for hash code (manual entries)
			modified = stripHashCode(punchCode, line);
		}
		break;

	case 3:
		// Compare punch codes
		if(!punchCode.CompareNoCase("G"))
		{
			// Top and bottom flange (14 Dia)
			modified = pow(2, 4) + pow(2, 5);
		}
		else if(!punchCode.CompareNoCase("B"))
		{
			// Lower flange hole (14 Dia)
			modified = pow(2, 4);
		}
		else if(!punchCode.CompareNoCase("T"))
		{
			// Top flange hole (14 Dia) (have to punch top and bottom)
			modified = pow(2, 5);
		}
		else if(!punchCode.CompareNoCase("N") || !punchCode.CompareNoCase("L"))
		{
			// Centre line (14 Dia)
			modified = pow(2, 13);
		}
		else if(!punchCode.CompareNoCase("V"))
		{
			// Lower fixing hole (14 Dia)
			modified = pow(2, 12);
		}
		else if(!punchCode.CompareNoCase("R"))
		{
			// Upper fixing hole (14 Dia)
			modified = pow(2, 1);
		}
		else if(!punchCode.CompareNoCase("F"))
		{
			// Lower and Upper fixing holes (14 Dia)
			modified = pow(2, 12) + pow(2, 1);
		}
		else if(!punchCode.CompareNoCase("GG"))
		{
			// Top and bottom flange holes (18 Dia)
			modified = pow(2, 2) + pow(2, 3);
		}
		else if(!punchCode.CompareNoCase("TT"))
		{
			// Upper flange hole (18 Dia)
			modified = pow(2, 3);
		}
		else if(!punchCode.CompareNoCase("BB"))
		{
			// Lower flange hole (18 Dia)
			modified = pow(2, 2);
		}
		else if(!punchCode.CompareNoCase("C"))
		{
			// Centre line (18 Dia)
			modified = pow(2, 15);
		}
		else if(!punchCode.CompareNoCase("Z"))
		{
			// Lower fixing hole (18 Dia)
			modified = pow(2, 8);
		}
		else if(!punchCode.CompareNoCase("Q"))
		{
			// Upper fixing hole (18 Dia)
			modified = pow(2, 11);
		}
		else if(!punchCode.CompareNoCase("A"))
		{
			// Upper and lower fixing holes (18 Dia)
			modified = pow(2, 8) + pow(2, 11);
		}
		else if(!punchCode.CompareNoCase("U"))
		{
			// 100 C/L on centre line (14 Dia)
			modified = pow(2, 13);
		}
		else if(!punchCode.CompareNoCase("K")) // F
		{
			// 100 C/L upper and lower fixing holes (14 Dia)
			modified = pow(2, 2) + pow(2, 1);
		}
		else if(!punchCode.CompareNoCase("E"))
		{
			// 100 C/L on centre line (18 Dia)
			modified = pow(2, 15);
		}
		else if(!punchCode.CompareNoCase("D")) // A
		{
			// 100 C/L upper and lower fixing holes (18 Dia)
			modified = pow(2, 14) + pow(2, 3);
		}
		else
		{
			// Test for hash code (manual entries)
			modified = stripHashCode(punchCode, line);
		}
		break;
	}


	return(modified);
}


// Use the new punch code layout (database changes will remove this function requirement)
double CElement::zeta(int line, CString partName, CString punchCode, double orgCode)
{
	double modified = -1.0L;


	// Test line number
	switch(line)
	{
	case 2:
	// Compare punch codes
	if(!punchCode.CompareNoCase("A"))
	{
		// Centre line (18 Dia)
		modified = 8;
	}
	else if(!punchCode.CompareNoCase("C"))
	{
		// Centre line (18 Dia)
		modified = 8;
	}
	else if(!punchCode.CompareNoCase("X"))
	{
		// Centre line 100 C/L Square
		modified = 4;
	}
	else if(!punchCode.CompareNoCase("T"))
	{
		// Top flange hole (14 Dia)
		modified = 64;
	}
	else if(!punchCode.CompareNoCase("B"))
	{
		// Bottom flange hole (14 Dia)
		modified = 16;
	}
	else if(!punchCode.CompareNoCase("G"))
	{
		// Both flange holes (14 Dia)
		/******* use compound instructions *******
		modified = 16;
		m_hitTwo = 64;
		*****************************************/
		modified = 80;
	}
	else if(!punchCode.CompareNoCase("L"))
	{
		// Single punch on centre line (18mm)
		modified = 8;
	}
	else if(!punchCode.CompareNoCase("Y"))
	{
		// Single punch on centre line (18mm) slot
		modified = 8;
	}
	else
	{
		// Test for hash code (manual entries)
		modified = stripHashCode(punchCode, line);
	}
	break;

	case 3:
		// Compare punch codes
		if(!punchCode.CompareNoCase("A"))
		{
			// Centre line (18 Dia)
			modified = orgCode;
		}
		else if(!punchCode.CompareNoCase("C"))
		{
			// Centre line (18 Dia)
			modified = pow(2, 11);
		}
		else if(!punchCode.CompareNoCase("X") || !punchCode.CompareNoCase("W"))
		{
			// Centre line 100 C/L Square
			modified = orgCode;
		}
		else if(!punchCode.CompareNoCase("T"))
		{
			// Top flange hole (14 Dia)
			modified = pow(2, 13);
		}
		else if(!punchCode.CompareNoCase("B"))
		{
			// Bottom flange hole (14 Dia)
			modified = pow(2, 12);
		}
		else if(!punchCode.CompareNoCase("G"))
		{
			// Both flange holes (14 Dia)
			modified = pow(2, 13) + pow(2, 12);
		}
		else if(!punchCode.CompareNoCase("L"))
		{
			// Single punch on centre line (18mm)
			modified = orgCode;
		}
		else if(!punchCode.CompareNoCase("Y"))
		{
			// Single punch on centre line (18mm) slot
			modified = orgCode;
		}
		else if(!punchCode.CompareNoCase("V"))
		{
			// Drain hole
			modified = orgCode;
		}
		else
		{
			// Test for hash code (manual entries)
			modified = stripHashCode(punchCode, line);
		}
		break;
	}	


	return(modified);
}


// Remove hash from front of the punch code
double CElement::stripHashCode(CString punchCode, int line)
{
	double	modified = -1.0L;
	CString	value;

	if(!punchCode.Left(1).CompareNoCase(_T("#")))
	{
		// Extract the number
		value=punchCode.Mid(1, punchCode.GetLength());
		modified = atof(value);

		// Test line number
		if(modified!=0 && line==3)
		{
			modified=pow(2, (modified-1));
		}

		if(modified == 0)
			modified = -1.0L;
	}
	

	return(modified);
}

void CBeamElement::resetExtraHolesList()
{
	POSITION	pos;
	CBeamOps	*pRemoveOp=NULL;

	// Get the head pos
	pos = m_tplAddList.GetHeadPosition();

	// Delete all holes
	while(pos)
	{
		pRemoveOp = m_tplAddList.GetNext(pos);
		delete pRemoveOp;
	}

	// Clean list
	m_tplAddList.RemoveAll();
	
}

bool CBeamElement::createASFServiceHoles()
{
	int				iMaxLen = GetLength();
	int				iInc = SERVICEHOLES;
	double			nFeed = (double)((SERVICEHOLES/2)-SERVICE_TOOL_OFFSET);
	CPunchValue		*pSet = new CPunchValue(m_pDoc->GetProjectSettings()->m_pDB);
	bool			bResult=false;


	// Set up recordset SQL parameters
	pSet->m_Line_Ident		= m_pItem->GetProdLineLabel();
	pSet->m_Section_Ident	= m_pItem->GetSectionID();
	pSet->m_Script_Ident	= 10;			// NON standard script
	pSet->m_Punch_Ident		= _T("AS");		// Punch code for service hole

	// Open the recordset
	pSet->Open();

	// Found record
	if(pSet->GetRecordCount())
	{
		// Test for hole requirement
		if(!GetComment().Compare("Service Holes"))
		{
			// Test position
			while((int)(nFeed+SERVICE_TOOL_OFFSET) <= iMaxLen-(SERVICEHOLES/2))
			{
				// Set return state
				bResult=true;
				// Create the hole in the element
				CreateHole(nFeed, NULL, pSet->m_Value, false);
				// Move to the next hole centre
				nFeed+=iInc;
			}
		}
	}

	// Close the recordset
	pSet->Close();

	// Free memory
	delete pSet;


	return(bResult);
}
