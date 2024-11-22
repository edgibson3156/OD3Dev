// CeeSection.cpp: implementation of the CCeeSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "od3.h"
#include "Element.h"
#include "CeeSection.h"

// Defined in mainframe.cpp
#include "CeeSectFail.h"
extern CCeeSectFail ceeFailDlg;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCeeSection::CCeeSection(COD3Doc *document)
{
	int	i;

	// Store current document
	this->m_pDoc = document;

	m_pCitem = NULL;


	// Clear array counter
	for(i=0; i<CEEPUNCHCOUNT; i++)
		sHoles[i].count = 0;
}

CCeeSection::~CCeeSection()
{
	HOLES		*pHole=NULL;
	POSITION	pos;

	// Get the head position
	pos = m_punchCodes.GetHeadPosition();

	while(pos)
	{
		// Get the data pointer
		pHole = m_punchCodes.GetNext(pos);
		// Release memory
		delete pHole;
	}

	// Remove pointer ref
	m_punchCodes.RemoveAll();
}

// Test if the item is a Cee section under modified code
bool CCeeSection::ceeTest(CItem *pItem)
{
	bool		result=false;
	CElement	element;
	int			lineNum = pItem->GetProdLine();
	CString		pCode = pItem->GetSectionID();

	m_pCitem = pItem;

	// Test for Cee section and modified line number
	if(element.getPart(pCode) == IDS_PART3 && (lineNum == 2 || lineNum == 3))
		result=true;


	return(result);
}



// Test all comments in each item and return variance
bool CCeeSection::performTest(CItem *pItem)
{
	int					count=0, lineNum=0;
	bool				result=true, quit=false;
	CBeamOps			*pBeamOp=NULL, *beam=NULL;
	CElement			*element=NULL;
	CBeamElement		*bElement=NULL;
	CDaoDatabase		*pDB = m_pDoc->GetProjectSettings()->m_pDB;
	CDaoImportedHoles	*pD3Hole=NULL;
	POSITION			pos, mainPos, loop;
	HOLES				*hole, *holePtr;


	// for each item in list
  	mainPos = pItem->m_tplElementList.GetHeadPosition();

	// Get the manufacturing line number
	lineNum = pItem->GetProdLine();
  	
	// Loop through elements
	while(mainPos)
	{
		// Get the next element pointer
  	  	bElement = (CBeamElement*)pItem->m_tplElementList.GetNext(mainPos);
		// Get hole head pointer
		pos = bElement->m_tplAddList.GetHeadPosition();

		// Loop through hole process
		while (pos)									
		{
			pBeamOp = bElement->m_tplAddList.GetNext(pos);
			// Test for punch
			if(!pBeamOp->GetOpType().CompareNoCase(_T("Punch")))
			{
				hole = new HOLES;
				pD3Hole	= new CDaoImportedHoles(pDB);
				// Set section id
				pD3Hole->m_Section_Ident = pItem->GetSectionID();
				// Set hole name
				pD3Hole->m_D3_HoleName = pBeamOp->GetOperation();
				// open the recordset
				if(!pBeamOp->GetOperation().Left(1).CompareNoCase(_T("#")))
				{
					// Manual punchcode added by user
					hole->punch = _T("#");
				}
				else
				{
					// open the record set
					pD3Hole->Open();

					// Store punchcode
					if(pD3Hole->m_Punch_Code.IsEmpty())
						hole->punch = pBeamOp->GetOperation();
					else
						hole->punch = pD3Hole->m_Punch_Code;
				}

				// Store data
				hole->comment = pBeamOp->GetComment();
				hole->iiD = bElement->GetElementID();
				hole->mark = bElement->GetMark();
				hole->holeText = pD3Hole->m_D3_HoleName;
				
				
				// Test for empty list
				if(!m_punchCodes.GetCount())
					loop = this->m_punchCodes.AddHead(hole);	
				else
					loop = m_punchCodes.InsertAfter(loop, hole);
				
				// Move data pos
				count++;

				// Delete recordset
				delete pD3Hole;
				pD3Hole = NULL;
			}
		}
	}

	// Get the head pos of the list
	loop = m_punchCodes.GetHeadPosition();
	// Clear counter
	count=0;


	while(loop)
	{
		// Get the data
		holePtr = (HOLES *)m_punchCodes.GetNext(loop);

		// Sort comments by punchcodes
		sortCommentByPunch(holePtr->punch, holePtr->comment, holePtr->mark, &quit, lineNum, holePtr->holeText);

		// Delete the hole object
		delete holePtr;
	}
	
	// Clear pointers
	m_punchCodes.RemoveAll();


	result=testCommentsByPunch();

	if((!result || quit) && !ceeFailDlg.IsWindowVisible())
	{
		ceeFailDlg.setActiveDoc(this->m_pDoc);
		ceeFailDlg.ShowWindow(SW_SHOW);
	}
	
	if(quit)
		result=false;

	// Release used memory
	cleanMemory();

	return(result);
}



void CCeeSection::sortCommentByPunch(CString punchCode, CString comment, 
										CString mark, bool *quit, int lineNum, CString D3Text)
{
	CString	warn;
	

	// Compare punch codes
	if(!punchCode.CompareNoCase("G"))
	{
		// Top and bottom flange (14 Dia)
		sHoles[0].punch = punchCode;
		sHoles[0].D3Text = D3Text;

		sHoles[0].mark.Add(mark);
		sHoles[0].comment.Add(comment);
		sHoles[0].count++;
	}
	else if(!punchCode.CompareNoCase("B"))
	{
		// Lower flange hole (14 Dia) (have to punch top and bottom)
		sHoles[1].punch = punchCode;
		sHoles[1].D3Text = D3Text;

		sHoles[1].mark.Add(mark);
		sHoles[1].comment.Add(comment);
		sHoles[1].count++;
	}
	else if(!punchCode.CompareNoCase("T"))
	{
		// Top flange hole (14 Dia) (have to punch top and bottom)
		sHoles[2].punch = punchCode;
		sHoles[2].D3Text = D3Text;

		sHoles[2].mark.Add(mark);
		sHoles[2].comment.Add(comment);
		sHoles[2].count++;
	}
	else if(!punchCode.CompareNoCase("N") || 
		!punchCode.CompareNoCase("L"))
	{
		// Centre line (14 Dia)
		sHoles[3].punch = _T("N");
		sHoles[3].D3Text = D3Text;

		sHoles[3].mark.Add(mark);
		sHoles[3].comment.Add(comment);
		sHoles[3].count++;
	}
	else if(!punchCode.CompareNoCase("V"))
	{
		// Lower fixing hole (14 Dia)
		sHoles[4].punch = punchCode;
		sHoles[4].D3Text = D3Text;

		sHoles[4].mark.Add(mark);
		sHoles[4].comment.Add(comment);
		sHoles[4].count++;
	}
	else if(!punchCode.CompareNoCase("R"))
	{
		// Upper fixing hole (14 Dia)
		sHoles[5].punch = punchCode;
		sHoles[5].D3Text = D3Text;

		sHoles[5].mark.Add(mark);
		sHoles[5].comment.Add(comment);
		sHoles[5].count++;
	}
	else if(!punchCode.CompareNoCase("F"))
	{
		// Lower and Upper fixing holes (14 Dia)
		sHoles[6].punch = punchCode;
		sHoles[6].D3Text = D3Text;

		sHoles[6].mark.Add(mark);
		sHoles[6].comment.Add(comment);
		sHoles[6].count++;
	}
	else if(!punchCode.CompareNoCase("GG"))
	{
		// Top and bottom flange holes (18 Dia) NOT POSSIBLE WITH STANDARD PRESS SETTINGS (LINE 2)
		sHoles[7].punch = punchCode;
		sHoles[7].D3Text = D3Text;

		sHoles[7].mark.Add(mark);
		sHoles[7].comment.Add(comment);
		sHoles[7].count++;
		
		// Dont continue
	//	if(lineNum==2)
	//	{
	//		*quit=true;
	//		// Format error string
	//		warn.Format(IDS_CEE_PUNCH_MSG, punchCode, D3Text);
//
//			addDataToList(m_pCitem->GetItemID(), mark, PUNCHFAULT, warn);
//		}
	}
	else if(!punchCode.CompareNoCase("TT"))
	{
		// Upper flange hole (18 Dia) NOT POSSIBLE WITH STANDARD PRESS SETTINGS (LINE 2)
		sHoles[8].punch = punchCode;
		sHoles[8].D3Text = D3Text;

		sHoles[8].mark.Add(mark);
		sHoles[8].comment.Add(comment);
		sHoles[8].count++;
		
		// Dont continue
		if(lineNum==2)
		{
			*quit=true;
			// Format error string
			warn.Format(IDS_CEE_PUNCH_MSG, punchCode, D3Text);

			addDataToList(m_pCitem->GetItemID(), mark, PUNCHFAULT, warn);
		}
	}
	else if(!punchCode.CompareNoCase("BB"))
	{
		// Lower flange hole (18 Dia) NOT POSSIBLE WITH STANDARD PRESS SETTINGS (LINE 2)
		sHoles[9].punch = punchCode;
		sHoles[9].D3Text = D3Text;

		sHoles[9].mark.Add(mark);
		sHoles[9].comment.Add(comment);
		sHoles[9].count++;
		
		// Dont continue
//		if(lineNum==2)
	//	{
	//		*quit=true;
	//		// Format error string
	//		warn.Format(IDS_CEE_PUNCH_MSG, punchCode, D3Text);
////
	//		addDataToList(m_pCitem->GetItemID(), mark, PUNCHFAULT, warn);
//		}
	}
	else if(!punchCode.CompareNoCase("C") ||
				!punchCode.CompareNoCase("E"))
	{
		// Centre line (18 Dia)
		sHoles[10].punch = _T("C");
		sHoles[10].D3Text = D3Text;

		sHoles[10].mark.Add(mark);
		sHoles[10].comment.Add(comment);
		sHoles[10].count++;
	}
	else if(!punchCode.CompareNoCase("Z"))
	{
		// Lower fixing hole (18 Dia)
		sHoles[11].punch = punchCode;
		sHoles[11].D3Text = D3Text;

		sHoles[11].mark.Add(mark);
		sHoles[11].comment.Add(comment);
		sHoles[11].count++;
	}
	else if(!punchCode.CompareNoCase("Q"))
	{
		// Upper fixing hole (18 Dia)
		sHoles[12].punch = punchCode;
		sHoles[12].D3Text = D3Text;

		sHoles[12].mark.Add(mark);
		sHoles[12].comment.Add(comment);
		sHoles[12].count++;
	}
	else if(!punchCode.CompareNoCase("A") ||
				!punchCode.CompareNoCase("D"))
	{
		// Upper and lower fixing holes (18 Dia)
		sHoles[13].punch = _T("A");
		sHoles[13].D3Text = D3Text;

		sHoles[13].mark.Add(mark);
		sHoles[13].comment.Add(comment);
		sHoles[13].count++;
	}
	else
	{
		// Load user warning string
		warn.Format(IDS_PUNCHCOMMENTWARN ,punchCode, m_pCitem->GetItemID(), mark, comment);

		if(punchCode.CompareNoCase(_T("#")))
			AfxMessageBox(warn, MB_ICONINFORMATION);
	}

	return;
}

// Loop through punchcodes and comments
bool CCeeSection::testCommentsByPunch()
{
	bool	result = true;
	int		j, pos;
	CString	firstComment ,sText;

	
	// Loop punchcodes
	for(pos=0; pos<CEEPUNCHCOUNT; pos++)
	{
		if(sHoles[pos].count)
		{
			// Store first comment
			firstComment = getValidComment(pos);

			if(firstComment.GetLength())
			{
				// Loop comments
				for(j=0; j<sHoles[pos].count; j++)
				{
					// Test first valid comment with remaining comments
					if(firstComment.CompareNoCase(sHoles[pos].comment.GetAt(j)) &&
						sHoles[pos].comment.GetAt(j).GetLength())
					{
						// Set fail
						result=false;

						// Format error string
						sText.Format(IDS_PUNCHPOS_MSG, sHoles[pos].comment.GetAt(j), firstComment, sHoles[pos].D3Text);

						addDataToList(m_pCitem->GetItemID(), sHoles[pos].mark.GetAt(j), COMMENTFAULT, sText);
					}
				}
			}
		}
	}

	return(result);
}

void CCeeSection::addDataToList(int iID, CString mark, int flag, CString sError)
{
	LVITEM				lvItem;
	CString				itemText;
	int					iFlag;
	CCeeItemFaultDes	*pFault=NULL;

	// Test for duplicates
	iFlag=isDuplicated(iID, mark, flag);


	if(sError.GetLength() > 0 && (pFault = ceeFailDlg.getErrorDesPtr(iID)))
	{
		pFault->m_ErrorText.Add(sError);
		pFault->m_markText.Add(mark);
	}


	if(flag==PUNCHFAULT && iFlag==0)
	{
		// Set list control data structure
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = ceeFailDlg.m_fList.GetItemCount();
		// Item number
		lvItem.iSubItem = 0;
		itemText.Format("%i", m_pCitem->GetItemID());
		lvItem.pszText = itemText.GetBuffer(itemText.GetLength());
		ceeFailDlg.m_fList.InsertItem(&lvItem);
			
		// Mark number
		lvItem.iSubItem = 1;
		lvItem.pszText = mark.GetBuffer(mark.GetLength());
		ceeFailDlg.m_fList.SetItem(&lvItem);


		// Punch fault
		lvItem.iSubItem = 2;
		lvItem.pszText = _T("TRUE");
		ceeFailDlg.m_fList.SetItem(&lvItem);

		if(!pFault)
		{
			// Create new error descrition for the item
			pFault = new CCeeItemFaultDes();

			// Set data
			pFault->m_iItemID = iID;
			pFault->m_ErrorText.Add(sError);
			pFault->m_markText.Add(mark);

			ceeFailDlg.m_tplErrors.AddTail(pFault);
		}

	}
	else if(flag==COMMENTFAULT && iFlag==0)
	{
		// Set list control data structure
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = ceeFailDlg.m_fList.GetItemCount();
		// Item number
		lvItem.iSubItem = 0;
		itemText.Format("%i", m_pCitem->GetItemID());
		lvItem.pszText = itemText.GetBuffer(itemText.GetLength());
		ceeFailDlg.m_fList.InsertItem(&lvItem);
			
		// Mark number
		lvItem.iSubItem = 1;
		lvItem.pszText = mark.GetBuffer(mark.GetLength());
		ceeFailDlg.m_fList.SetItem(&lvItem);

		// Comment fault
		lvItem.iSubItem = 3;
		lvItem.pszText = _T("TRUE");
		ceeFailDlg.m_fList.SetItem(&lvItem);

		if(!pFault)
		{
			// Create new error descrition for the item
			pFault = new CCeeItemFaultDes();

			// Set data
			pFault->m_iItemID = iID;
			pFault->m_ErrorText.Add(sError);
			pFault->m_markText.Add(mark);

			ceeFailDlg.m_tplErrors.AddTail(pFault);
		}
	}
	else if(iFlag>COMMENTFAULT)
	{
		// Set list control data structure
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = iFlag-COMMENTFAULT-1;
		// Item number
		lvItem.iSubItem = 0;
		itemText.Format("%i", m_pCitem->GetItemID());
		lvItem.pszText = itemText.GetBuffer(itemText.GetLength());
		//ceeFailDlg.m_fList.SetItem(&lvItem);
			
		// Mark number
		lvItem.iSubItem = 1;
		lvItem.pszText = mark.GetBuffer(mark.GetLength());
		ceeFailDlg.m_fList.SetItem(&lvItem);

		// Punch fault
		lvItem.iSubItem = 2;
		lvItem.pszText = _T("TRUE");
		ceeFailDlg.m_fList.SetItem(&lvItem);

		// Comment fault
		lvItem.iSubItem = 3;
		lvItem.pszText = _T("TRUE");
		ceeFailDlg.m_fList.SetItem(&lvItem);

		if(!pFault)
		{
			// Create new error descrition for the item
			pFault = new CCeeItemFaultDes();

			// Set data
			pFault->m_iItemID = iID;
			pFault->m_ErrorText.Add(sError);
			pFault->m_markText.Add(mark);

			ceeFailDlg.m_tplErrors.AddTail(pFault);
		}
	}


	return;
}

int CCeeSection::isDuplicated(int iID, CString mark, int flag)
{
	int		found=0;
	int		count = ceeFailDlg.m_fList.GetItemCount();
	int		i;
	CString	sItem, sMark, sPunchErr, sCommentErr, strTmp;

	// Convert id into string
	strTmp.Format("%i", iID);

	for(i=0; i<count && found==0; i++)
	{
		// Get the text from the list control
		sItem = ceeFailDlg.m_fList.GetItemText(i,0);
		sMark = ceeFailDlg.m_fList.GetItemText(i,1);
		sPunchErr = ceeFailDlg.m_fList.GetItemText(i,2);
		sCommentErr = ceeFailDlg.m_fList.GetItemText(i,3);

		if((sMark==mark && sItem==strTmp))
		{
			switch(flag)
			{
				case PUNCHFAULT:
					found=PUNCHFAULT;
					break;

				case COMMENTFAULT:
					if(!sPunchErr.IsEmpty())
					{
						// Punch variable set (append to found item)
						found=COMMENTFAULT+(i+1);
					}
					else
					{
						found=COMMENTFAULT;
					}
					break;
			}
		}
	}


	return(found);
}

void CCeeSection::cleanMemory()
{
	int		pos;

	// Loop punchcodes
	for(pos=0; pos<CEEPUNCHCOUNT; pos++)
	{
		if(sHoles[pos].count)
		{
			// Remove comments and marks
			sHoles[pos].comment.RemoveAll();
			sHoles[pos].comment.FreeExtra();

			sHoles[pos].mark.RemoveAll();
			sHoles[pos].mark.FreeExtra();
		}
	}

	return;
}

CString CCeeSection::getValidComment(int index)
{
	CString comment;
	int		i;

	// Loop through comments
	for(i=0; i<sHoles[index].count; i++)
	{
		// Test string size
		if(sHoles[index].comment.GetAt(i).GetLength())
		{
			// Store first valid comment
			comment = sHoles[index].comment.GetAt(i);

			// Exit loop
			break;
		}
	}


	return(comment);
}
