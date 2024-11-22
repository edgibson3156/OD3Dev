// Item.cpp: implementation of the CItem class.
//
// CItem objects are lists of all the elements
//  (either beam or accessory) in the this sales order item.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "OD3Doc.h"
#include "Item.h"
#include "Element.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CItem,CObject,0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItem::CItem()
{
	m_nItemID		= 0;
	m_nType			= 0;
	m_bIsBeam		= true;	//	OK for manual input, but ...
							//	... needs an IsBeamList() call when importing d3 files??

	m_nProdLine		= 0;
	m_bIsNonStand	= false;

	m_dGauge=
	m_nWeight = 0.0l;

	m_nDepth=
	m_nTopFlange=
	m_nTopFlangeSlope=
	m_nTopFlangeLip=
	m_nBottomFlange=
	m_nBottomFlangeSlope=
	m_nBottomFlangeLip=
	m_nDimC=
	m_nDimF=
	m_nProdLine = 0;

	m_pFailedBeam = NULL;
	m_pDoc = NULL;

	memset(m_bPunchUsedFlag,0,sizeof(m_bPunchUsedFlag));
}

CItem::~CItem()
{
	POSITION			pos;

	// Get the head position
	pos = m_tplElementList.GetHeadPosition();

	while(pos)
	{
		if(this->IsBeam())
		{
			delete m_tplElementList.GetNext(pos);				
		}
		else
		{
			CAccessoryElement	*pAcc=NULL;
			pAcc = (CAccessoryElement *)m_tplElementList.GetNext(pos);
			delete pAcc;
		}
	}

	m_tplElementList.RemoveAll();
}


///////////////////////////////////////////////////////////////////
//
void CItem::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	int nIsBeam;

	if (ar.IsStoring())
	{
		nIsBeam = (int)m_bIsBeam;

		ar << m_nItemID;
		ar << nIsBeam;
		ar << m_nType;
		ar << m_sProductCode;
		ar << m_sProductName;
		ar << m_sProfile;
		ar << m_sSectionID;
		ar << m_nWeight;
		ar << m_dGauge;
		ar << m_nDepth;
		ar << m_nTopFlange;
		ar << m_nTopFlangeSlope;
		ar << m_nTopFlangeLip;
		ar << m_nBottomFlange;
		ar << m_nBottomFlangeSlope;
		ar << m_nBottomFlangeLip;
		ar << m_nDimC;
		ar << m_nDimF;
	}
	else
	{
		ar >> m_nItemID;
		ar >> nIsBeam;
		m_bIsBeam = (nIsBeam != 0);
		ar >> m_nType;
		ar >> m_sProductCode;
		ar >> m_sProductName;
		ar >> m_sProfile;
		ar >> m_sSectionID;
		ar >> m_nWeight;
		ar >> m_dGauge;
		ar >> m_nDepth;
		ar >> m_nTopFlange;
		ar >> m_nTopFlangeSlope;
		ar >> m_nTopFlangeLip;
		ar >> m_nBottomFlange;
		ar >> m_nBottomFlangeSlope;
		ar >> m_nBottomFlangeLip;
		ar >> m_nDimC;
		ar >> m_nDimF;

		// If the item is an accessory process it down the Brace mill
		if(!IsBeam())
		{
			// Set line lable
			SetProdLineLabel(_T("Diagonal_Brace"));
			// Set the mill number
			SetProdLine(D_BRACE);
		}
	}
	m_tplElementList.Serialize(ar);
}
///////////////////////////////////////////////////////////////////
//
CElement* CItem::FindElementByID(int& cBeamCounter)
{			
	CElement*	pElement;
	POSITION	pos;
	int			nElementID;

	pos = m_tplElementList.GetHeadPosition();

	while(pos)
	{														// ... the correct mark number ...
		pElement = m_tplElementList.GetNext(pos);
		nElementID = pElement->GetElementID();
		if(nElementID == cBeamCounter)
		{
			return pElement;
		}	// ... found it, so return a pointer.
	}

/*	//	either list is empty or no match was found ...
	CElement* pNewElement = new CBeamElement();	// so create a new beam, ...
	pNewElement->m_pItem = this;
	
	//	now find the right place in list - ascending order of length.

	m_tplElementList.AddTail(pNewElement);			// add it to the list ...
	return pNewElement;							// and return it address.
	*/
	return NULL;
} 

///////////////////////////////////////////////////////////////////
//	GetElement()	A function to step through the Item's element list and return a pointer to each element in turn.
//
CElement* CItem::GetElement()
{
	POSITION	pos;
	CElement*	pElement;
	
	// for each item in list
  	pos = this->m_tplElementList.GetHeadPosition();
  	
	while(pos)
	{
  	  	pElement = (CElement*)this->m_tplElementList.GetNext(pos);
		return pElement;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool CItem::SetLineFlag()
{
	POSITION		pos;
	CAssociation*	pAssn;
	CString			sLine = _T("");
	CString			sRollSet = _T("");
	CString			sSection = _T("");
	CString			sTemp = _T("");

	pos = this->m_pDoc->m_pProjectSettings->m_tplAssociationList.GetHeadPosition();

	while(pos)
	{
		pAssn = this->m_pDoc->m_pProjectSettings->m_tplAssociationList.GetNext(pos);
		pAssn->GetAssociation(sRollSet,sLine);
		
		sTemp = this->m_sSectionID;

		// filter out the John Reid & SBE specials by getting the last 5 significant characters
		if (sTemp.Left(2) == _T("JR") || sTemp.Left(3) == _T("SBE"))
		{
			sSection = sTemp.Right(5);
			//	special trap for C sections with 4 digit section code
			if(sSection.Left(1) == _T("E") && sSection.Left(2) != _T("EB"))
			{
				sSection = sTemp.Right(4);
			}
		}
		// filter out the 'forward slash' in PJR sections (introduced in PurlinDetail 2.1 - July 2002)
		else if (sTemp.Left(4) == _T("PJR/"))
		{
			sSection = sTemp.Left(3) + sTemp.Right(3);
		}
		else if(!sTemp.Right(1).CompareNoCase(_T("W")))
		{
			// Swagebeam type Wernik, remove the "W" to pass validation
			sSection = sTemp.Mid(0, sTemp.GetLength()-1);
		}
		else
		{
			sSection = sTemp;
		}

		if (sSection != sRollSet)
		{}	//	loop			
		else
		{
			if (sLine == "Line_1"){m_nProdLine = LINE_1;}
 			else if (sLine == "Line_2"){m_nProdLine = LINE_2;}
			else if (sLine == "Line_3"){m_nProdLine = LINE_3;}

			m_sProdLine = sLine;
			return true;
		}
	}

	if (m_sProdLine = ""){return false;}
	else {return true;}
}

//////////////////////////////////////////////////////////////
// CreateElement()	A function to create a new CBeamElement object 
//					and add it to the item's element list.
CBeamElement* CItem::CreateElement()
{
	CBeamElement* pNewElement = new CBeamElement();	// create new item ...
	pNewElement->m_pItem = this;
	this->CreateOrderedBeamList(pNewElement);
//	this-> m_tpList.AddTail(pNewItem);		// ... add it to the list ...
	this->m_pDoc->SetModifiedFlag();						// ... remind user to save file on exit ...
	this->m_pDoc->SetTitle(NULL);
	this->m_pDoc->UpdateAllViews(NULL);
	return pNewElement;						// ... return pointer to new item.
}

///////////////////////////////////////////////////////////////////////////////////////////
//	CutBeam()		Remove a CBeamElement pointer from the item's element list
//
void CItem::CutBeam(CBeamElement* pBeam, COD3View* pView)
{
	POSITION pos;

	// Find the object
	if((pos = m_tplElementList.Find(pBeam)))
	{
		// Remove the pointer
		m_tplElementList.RemoveAt(pos);
		// Add the pointer to the cut list
		m_pDoc->m_tplCutList.AddTail((CElement*)pBeam);
		// Modify the document
		m_pDoc->SetModifiedFlag();
		m_pDoc->SetTitle(NULL);
	}

	return;
}

///////////////////////////////////////////////////////////////////////////////////////////
//	CopyBeam()		Copy an existing CBeamElement to a new object and add its pointer
//					to the item's element list
//
void CItem::CopyBeam(CBeamElement* pCopyBeam, COD3View* pView)
{
	POSITION pos1;
	POSITION pos2;

	CElement* pCopyElement = (CElement*)pCopyBeam;
	CBeamOps* pCopyOp;

	CElement* pNewElement = new CBeamElement();
	CBeamElement* pNewBeam = (CBeamElement*)pNewElement;
	pNewBeam->m_pItem = this;
	CBeamOps* pNewOp;
	
	CElement* pTest;

	pos1 = this->m_tplElementList.GetHeadPosition();

	while(pos1)
	{
		pTest = this->m_tplElementList.GetNext(pos1);
		if (pCopyElement->GetMark() == pTest->GetMark())
		{
			int nElementID = this->m_tplElementList.GetCount();
			CString szMark = pCopyElement->GetMark();
			pNewElement->SetElementID(++nElementID);
			pNewElement->SetMark(szMark += "X");
			pNewElement->SetQty(pCopyElement->GetQty());
			pNewElement->SetSection(pCopyElement->GetSection());
			pNewBeam->SetBundle(pCopyBeam->GetBundle());
			pNewBeam->SetEBSlope(pCopyBeam->GetEBSlope());
			pNewBeam->SetLength(pCopyBeam->GetLength());
			pNewBeam->SetMemberType(pCopyBeam->GetMemberType());
			pNewBeam->SetOHang1(pCopyBeam->GetOHang1());
			pNewBeam->SetOHang2(pCopyBeam->GetOHang2());
			pNewBeam->SetSpan1(pCopyBeam->GetSpan1());
			pNewBeam->SetSpan2(pCopyBeam->GetSpan2());
			pNewBeam->SetSpan3(pCopyBeam->GetSpan3());
			LPCTSTR lpszCode = pCopyBeam->GetSPCode();
			pNewBeam->SetSPCode(lpszCode);
			pNewBeam->SetComment(pCopyBeam->GetComment().GetBuffer(1));

			pos2 = pCopyBeam->m_tplAddList.GetHeadPosition();
			while(pos2)
			{
				pNewOp = new CBeamOps();
	
				pCopyOp = pCopyBeam->m_tplAddList.GetNext(pos2);
				
				pNewOp->SetAbsolute(pCopyOp->GetAbsolute());
				pNewOp->SetMultiplied(pCopyOp->GetMultiplied());
				pNewOp->SetPositive(pCopyOp->GetPositive());
				pNewOp->SetMultiplier(pCopyOp->GetMultiplier());
				pNewOp->SetScriptID(pCopyOp->GetScriptID());
				pNewOp->SetOpSeqID(pCopyOp->GetOpSeqID());
				pNewOp->SetComment(pCopyOp->GetComment());
				pNewOp->SetOperation(pCopyOp->GetOperation());
				pNewOp->SetOpType(pCopyOp->GetOpType());

				pNewBeam->m_tplAddList.AddTail(pNewOp);
			}
			
			this->m_pDoc->m_tplCopyList.AddTail(pNewBeam);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//	PasteBeam()		Add a CBeamElement pointer to the item's element list
//
void CItem::PasteBeam(COD3View* pView)
{
	POSITION		pos;
	CElement		*pElement;
	CBeamElement	*pBeam;
	CString			sMark;


	if(pView->m_bCut == true)
	{
		pos = this->m_pDoc->m_tplCutList.GetHeadPosition();
		while(pos)
		{
			pElement = this->m_pDoc->m_tplCutList.GetNext(pos);

			// Test for duplicate marks in accessories
			if(!IsBeam())
			{
				// Get the mark number
				sMark = pElement->GetMark();

				// Test for duplicate mark number
				if(getAccessory(sMark))
				{
					while(getAccessory(sMark))
						sMark += _T("x");
				}
				// Set the mark number
				pElement->SetMark(sMark);
			}

			pBeam = (CBeamElement*)pElement;
			this->CreateOrderedBeamList(pBeam);
		}

		m_pDoc->m_tplCutList.RemoveAll();
		pView->m_bCut = false;
	}
	else if(pView->m_bCopy == true)
	{
		pos = this->m_pDoc->m_tplCopyList.GetHeadPosition();
		while(pos)
		{
			pElement = this->m_pDoc->m_tplCopyList.GetNext(pos);

			// Test for duplicate marks in accessories
			if(!IsBeam())
			{
				// Get the mark number
				sMark = pElement->GetMark();

				// Test for duplicate mark number
				if(getAccessory(sMark))
				{
					while(getAccessory(sMark))
						sMark += _T("x");
				}
				// Set the mark number
				pElement->SetMark(sMark);
			}
			
			pBeam = (CBeamElement*)pElement;
			this->CreateOrderedBeamList(pBeam);
		}

		m_pDoc->m_tplCopyList.RemoveAll();
		pView->m_bCopy = false;

	}
	
	m_pDoc->SetModifiedFlag();
	m_pDoc->SetTitle(NULL);

#ifndef ALLVIEW
	pView->RedrawListControls();		
#else
	m_pDoc->UpdateAllViews(NULL);
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CreateOrderedBeamList()	Add beam elements to a CItem element list in DESCENDING order of length
//
void CItem::CreateOrderedBeamList(CBeamElement* pNewBeam)
{
	POSITION			pos;
	CElement			*pElement = (CElement*)pNewBeam;
	CElement			*pElRec;
	CBeamElement		*pRec;
	CAccessoryElement	*pAcc=NULL;
	int test, key;
	CString szTest(_T(""));
	CString szKeyMark(_T(""));
	
	// get length of new beam
	test = pNewBeam->GetLength();

	// get head position of element list
	pos = this->m_tplElementList.GetHeadPosition();		


	// if list empty add to tail and exit
	if(!pos)
	{
		this->m_tplElementList.AddTail(pNewBeam);
		ResetBeamCounter();
		return;
	}

	// at least one beam in list so check to see if it's the same as the new one
	while (pos)
	{
		pRec = (CBeamElement*)this->m_tplElementList.GetNext(pos);

		if(pRec == pNewBeam)								
		{
#if 0
			// Remove this beam from the list incase length has been modified
			m_tplElementList.RemoveAt(m_tplElementList.Find(pRec));
			test=pNewBeam->GetLength();
#endif
			return;
		}
	}

	// Get the head position
	if((pos=this->m_tplElementList.GetHeadPosition()))
	{
		do																	// at least one beam in list so force 'do'
		{																	// get nth record in element list and find its length
			pElRec = this->m_tplElementList.GetNext(pos);

			if(pRec->IsKindOf(RUNTIME_CLASS(CAccessoryElement)))
			{
				pAcc = (CAccessoryElement*)pElRec;
				key = pAcc->GetLength();
			}
			else
			{
				pRec = (CBeamElement*)pElRec;
				key = pRec->GetLength();
			}

#if 0	// Sort order changes required in streamline before use
			// Are we the same length
			if(test==key)
			{
				// Same length? continue searching for lengths of the same value
				// When value changes insert element
				while(pos)
				{
					pElRec = this->m_tplElementList.GetNext(pos);
					pRec = (CBeamElement*)pElRec;
					key = pRec->GetLength();

					// Variance
					if(key!=test)
					{
						// Test for valid pointer
						if(!pos)
							pos = this->m_tplElementList.GetTailPosition();

						// Get insertion location
						this->m_tplElementList.GetPrev(pos);
						// Quit while loop
						break;
					}
				}

				// Test for valid pointer
				if(pos)
					this->m_tplElementList.InsertBefore(pos, pNewBeam);
				else
					this->m_tplElementList.AddTail(pNewBeam);

				this->ResetBeamCounter();

				return;
			}
			else 
#endif
			if(test < key)												// newbeam is shorter
			{
				if (pos == NULL)											// pRec is last in list
				{
					this->m_tplElementList.AddTail(pNewBeam);				// so add newbeam to tail
					this->ResetBeamCounter();
					return;
				}
			}
			else															// newbeam is longer
			{	
				if(!pos)													// and we're at the end of the list
				{
					pos = this->m_tplElementList.GetTailPosition();			// so get tail position
					this->m_tplElementList.InsertBefore(pos, pNewBeam);		//  and insert before 
					this->ResetBeamCounter();
					return;
				}
				else if (!this->m_tplElementList.GetPrev(pos))				// we're at the head of the list 
				{															// all remaining elements are shorter
					this->m_tplElementList.AddHead(pNewBeam);				// so add the new element to the head
					this->ResetBeamCounter();
	//				return;
				}
				else														// we're in the middle of the list
				{															// all remaining elements are shorter
					this->m_tplElementList.GetPrev(pos);					// so reset 'pos' to current position
					if (pos == NULL)
					{
						this->m_tplElementList.AddHead(pNewBeam);				// so add the new element to the head
						this->ResetBeamCounter();
						return;
					}
					else
					{
						this->m_tplElementList.InsertAfter(pos, pNewBeam);		// and insert it after the current one	
						this->ResetBeamCounter();
						return;													// and exit
					}
				}
			}
		} while(pos); //	check against next key
	}
	else
	{
		// Add the new item to the list
		m_tplElementList.AddTail(pNewBeam);
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CItem::CreateOrderedAccessoryList(CAccessoryElement* pNewElement)
{
/*	This cannot not work because we do not know the length of the accessory until after it has been processed
	e.g. for diagonal brace we need dimensions A & B to specify the product.  The length is determined by AViiON,
	and AViiON does the sorting
*/
/*	POSITION pos;
	CAccessoryElement* pRec;
	int test, key;
	
	// get length of new beam
	test = pNewElement->GetLength();

	// get head position of element list
	pos = this->m_tplElementList.GetHeadPosition();		

	// if list empty add to tail and exit
	if(!pos)
	{
		this->m_tplElementList.AddTail(pNewElement);
		return;
	}

	// at least one beam in list so check to see if it's the same as the new one
	while (pos)
	{
		pRec = (CAccessoryElement*)this->m_tplElementList.GetNext(pos);
		if(pRec != pNewElement)								// does beam already exist?
		{}													// this one doesn't match - try next
		else												// this one does 
		{
			if(pRec->GetLength() != test)					// if the length has changed we need to re-order the list
			{												// it has so ...
				this->m_tplElementList.GetPrev(pos);		// ... get position of pRec ...
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
		pRec = (CAccessoryElement*)this->m_tplElementList.GetNext(pos);
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

/*
//////////////////////////////////////////////////////////////////////
//
bool CItem::SortBeamElementsByLength()
{

//	CreateOrderedList();
	POSITION pos;
	CBeamElement* pRec1;
	CBeamElement* pRec2;
	CBeamElement* pTempRec;
	int test, key;

start:
	bool bModified = false;
	
	// get head position
	pos = this->m_tplElementList.GetHeadPosition();
		if(!pos){return false;}

	// bubble sort - VHF TODO: use a more efficient method - see qsort
	do
	{
		// get rec1
		pRec1 = (CBeamElement*)this->m_tplElementList.GetNext(pos);
			if(!pos){break;}
		test = pRec1->GetLength();

		// get rec2
		pRec2 = (CBeamElement*)this->m_tplElementList.GetNext(pos);
		key = pRec2->GetLength();

		// do comparison
		if(test > key)
		{
			// do swap !!!

//			memcpy
			pTempRec = new CBeamElement;
/*			pTempRec->SetPosX(pRec1->GetLength());
			pTempRec->SetPosY(pRec1->GetPosY());
			pTempRec->SetPunch(pRec1->GetPunch());

			pRec1->SetPosX(pRec2->GetLength());
			pRec1->SetPosY(pRec2->GetPosY());
			pRec1->SetPunch(pRec2->GetPunch());

			pRec2->SetPosX(pTempRec->GetLength());
			pRec2->SetPosY(pTempRec->GetPosY());
			pRec2->SetPunch(pTempRec->GetPunch()); */

/*			delete pTempRec;
			
			bModified = true;
		}
		pos = this->m_tplElementList.Find(pRec2);

	}while(pos);

	if(bModified ==true)
		goto start;
		
	return true;
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
bool CItem::ElementMarkExists(LPCTSTR lpszTestMark)
{
  //search beam list...
  	CBeamElement* pBeamRecord = (CBeamElement*) this->FindBeamByMark(lpszTestMark);
  	
  //...if beam found return success	
  	if( pBeamRecord != NULL )
	{
		return true;
	}

  //search accessory list...
/*  	CImportD3Acc* pAccRecord = (CImportD3Acc*) this->FindAccessory(lpszTestMark);
  	
  //...if accessory found return success	
  	if( pAccRecord != NULL )
	{
		return true;
	}	*/
			
  //... if not, return failure
  	return FALSE;
}    
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
CBeamElement* CItem::FindBeamByMark(LPCTSTR lpszTestMark)
{
  // ... for each mark in list
  	POSITION pos = this->m_tplElementList.GetHeadPosition();
  	while(pos)
	{
  	  	CBeamElement* pRecord = (CBeamElement*)this->m_tplElementList.GetNext(pos);
  	  	
  	  //if test mark = this mark
  	  	if(!lstrcmp((LPCTSTR)pRecord->GetMark(), lpszTestMark))
  		{
		  //return existance
		  	return pRecord;
	  	}
	}
  //return non existance
  	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////
//	DeleteBeam()
//
void CItem::DeleteBeam(CBeamElement* pBeam) 
{
	POSITION pos;
	CElement*	pElement = (CElement*)pBeam;
	CElement*	pTest;
	CString szMark;

	szMark = pElement->GetMark();

	pos = this->m_tplElementList.GetHeadPosition();

	while(pos)
	{
		pTest = this->m_tplElementList.GetNext(pos);
		if(pTest->GetMark() != szMark)
		{
		}
		else
		{
			if(!pos)
			{
				pos = this->m_tplElementList.GetTailPosition();
			}
			else
			{
				this->m_tplElementList.GetPrev(pos);
			}
//			this->m_tplElementList.RemoveAt(pos);
			delete pElement;
			this->m_tplElementList.RemoveAt(pos);
			break;
		}
	}
	this->ResetBeamCounter();
}

void CItem::ResetBeamCounter()
{
	CElement*	pElement;
	POSITION pos;
	int cBeamCounter;

	pos = this->m_tplElementList.GetHeadPosition();
	cBeamCounter = m_nItemID * 1000;
	while (pos)
	{
		pElement = this->m_tplElementList.GetNext(pos);
		pElement->SetElementID(++cBeamCounter);
	}

}

void CItem::ResetPunchFlags()
{
	int i = 0;
	for (i=0;i<20;i++)
	{
		this->m_bPunchUsedFlag[i] = false;
	}
}

void CItem::ResetPunchGauge()
{
	int i = 0;
	for (i=0;i<20;i++)
	{
		this->m_szPunchGauge[i] = _T("");
	}
}


CAccessoryElement* CItem::getAccessory(CString sMark)
{
	CAccessoryElement	*pAcc=NULL;
	CElement			*pElement=NULL;
	POSITION			pos;

	// Get the head position for the elements
	pos = m_tplElementList.GetHeadPosition();

	while(pos)
	{
		// Get the next element object
		pElement = m_tplElementList.GetNext(pos);

		if(!pElement->GetMark().CompareNoCase(sMark))
		{
			// Set accessory pointer
			pAcc = (CAccessoryElement *)pElement;
			// Exit from loop
			break;
		}
	}


	return(pAcc);
}

void CItem::deleteAccessoy(CAccessoryElement *pAcc)
{
	POSITION	pos;

	// Find the element in the list
	if((pos=m_tplElementList.Find(pAcc)))
	{
		// Delete the object
		delete pAcc;
		// Remove the pointer in the list
		m_tplElementList.RemoveAt(pos);
		// Reset the elemnt list
		ResetBeamCounter();
	}
}

void CItem::copyAccessory(CAccessoryElement *pAcc)
{
	CAccessoryElement	*pNewAcc = new CAccessoryElement;
	CString				sMark = pAcc->GetMark();

	pNewAcc->SetBundle(pAcc->GetBundle());
	pNewAcc->SetComment(pAcc->GetComment());
	pNewAcc->SetElementID(pAcc->GetElementID());
	pNewAcc->SetField1(pAcc->GetField1());
	pNewAcc->SetField2(pAcc->GetField2());
	pNewAcc->SetField3(pAcc->GetField3());
	pNewAcc->SetField4(pAcc->GetField4());
	pNewAcc->SetField5(pAcc->GetField5());
	pNewAcc->SetGauge(pAcc->SetGauge());
	pNewAcc->SetLength(pAcc->GetLength());
	pNewAcc->SetQty(pAcc->GetQty());
	pNewAcc->SetType(pAcc->GetType());
	pNewAcc->SetMark(sMark);

	pNewAcc->m_pItem = this;

	// Add the new accessory to the list
	m_pDoc->m_tplCopyList.AddTail(pNewAcc);
}

void CItem::SortElementsByLength()
{
	
	POSITION			pos, first, second;
	CAccessoryElement	*pAcc1=NULL, *pAcc2=NULL;

	if(!IsBeam() && m_tplElementList.GetCount() > 1)
	{
		// Get the head position
		pos = m_tplElementList.GetHeadPosition();

		while(pos)
		{
			// Store current position
			first = pos;

			// Get a brace object
			pAcc1 = (CAccessoryElement *)m_tplElementList.GetNext(pos);

			if(pos)
			{
				// Store current position
				second = pos;
				// Get a brace object
				pAcc2 = (CAccessoryElement *)m_tplElementList.GetNext(pos);
				// Set the position back one
				pos = second;
			}

			// Test length of brace objects
			if(pAcc1->GetLength() < pAcc2->GetLength())
			{
				// Swap pointer positions
				m_tplElementList.SetAt(first, pAcc2);
				m_tplElementList.SetAt(second, pAcc1);

				// Start loop again
				pos = m_tplElementList.GetHeadPosition();
			}
		}

		// Reset the element list
		ResetBeamCounter();
	}

}
