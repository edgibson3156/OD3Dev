// Line2.cpp: implementation of the CLine2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "Line2.h"
#include "Element.h"
#include "BeamOps.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CLine2::MAX_MARK_LENGTH = 8;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
CLine2::CLine2()
{

}

CLine2::~CLine2()
{

}
*/

//////////////////////////////////////////////////////////////////////
////
void CLine2::GetPartFileName( CString* psz, CString& sItemID, short iPartIndex )	
{
	int count =0;
	char extension[4] ="   ";
	char temp[13] ="";
	char fname[40] ="";
	char filename[40];
	
	CString szProjectName	= _T("");
	CString szDocTitle	= _T("");
	szProjectName = this->m_pDoc->m_pProjectHeader->m_sProjectName;

	szDocTitle = szProjectName;
	szDocTitle += ".";
	szDocTitle += sItemID;

	if( szDocTitle.CompareNoCase( "Untitled" ) )
	{
		lstrcpy( (LPSTR)filename, (const char*)szDocTitle );

		while( filename[count]!='.' && filename[count]!='\0' )
			++count;
	
		strcpy( extension, &filename[count+1] );
		strcpy( fname, filename );
		strcpy( &fname[count], &extension[1] );
	
		while( strlen( fname )>5 )
		{
			strcpy( temp, fname );
			strcpy( fname, &temp[1] );
		}
	
		strcat( fname, "-" );
		sprintf( &fname[strlen(fname)], "%-2.2i", iPartIndex );
		strcat( fname, ".ORD" );
	}

	*psz =fname;
}

//////////////////////////////////////////////////////////////////////
//	BuildDetails(CItem* pItem)		A function to retrieve data from the item's element list
//									and write it to the output file
//
//	NB: Line 2 requires a separate file for each 'part', but many 'parts' can be on the same disk.
//		By convention the filename is built using the last three digits of the order number
//		and the last two digits of the od2 'work file' filename extension. 
//		Also by convention the od2 'work file' filename is built from the order number and the item no.
//		(e.g. Item 1 of order P99999 would be saved to P99999.001)
//
void CLine2::BuildDetails(CItem* pItem)	
{
	CString TempPath;
	
	CElement* pElement;
	CBeamElement* pBeamRecord;
	CHole* pOperation;
	COutputList* pOut;

	POSITION posElement, posOps;
	char szBuffer[80];
	CString szDetailText  = _T("");

	CString szPartFileName = _T("");
	CString szFullFilePath;

	// convert Item number to 3 char string (emulates the OD2 filename extension)
	CString sItemID;
	int nItemID = pItem->m_nItemID;
	sItemID.Format("%d",nItemID);
	if (nItemID > 9 && nItemID < 100)
	{
		sItemID = "0" + sItemID;
	}

	if (nItemID < 10)
	{
		sItemID = "00" + sItemID;
	}

	// Get section
	CString szTempSection = pItem->GetProfile();

/*	Trap no longer required -  JRZ/240 & JRZ/300 will now have 18 dia holes with 70mm c/cs

	// Special Trap for John Reid Special Sections with 14 dia holes
	if (szTempSection.Left(6) == "JRZ/24" || szTempSection.Left(6) == "JRZ/30")
	{
		CString szItem;
		int nItemID = pItem->m_nItemID;
		szItem.Format("%d",nItemID);
		CString szMsg;
		szMsg = "Item ";
		szMsg += szItem;
		szMsg += " is a John Reid Special Section ";
		szMsg += szTempSection;
		szMsg += "\n\n Line 2 requires a tool change for 14 dia. holes";
		szMsg += "\n\n Issue Special Instruction Sheet";
		szMsg += "\n Y2.513 or Y2.523 as appropriate";
		AfxMessageBox(szMsg,MB_ICONWARNING);
	}
*/
	short iPartIndex = 0;
	posElement = pItem->m_tplElementList.GetHeadPosition();
	while (posElement)
	{
		pElement = pItem->m_tplElementList.GetNext(posElement);
		pBeamRecord = (CBeamElement*)pElement;
		++iPartIndex;
	
		this->GetPartFileName( &szPartFileName, sItemID, iPartIndex);

      //file name
		sprintf( szBuffer, "%-8.8s", (const char*)szPartFileName );
		szDetailText =szBuffer;
		
	  //section size	
		szDetailText +=" 12515";

	  //quantity
		sprintf( szBuffer, " %-i", pBeamRecord->GetQty() );
	  	szDetailText +=szBuffer;
	  	
	  //bundle count
		sprintf( szBuffer, " %-i", pBeamRecord->GetBundle() );
	  	szDetailText +=szBuffer;

      //mark
		CString szMark =pBeamRecord->GetMark();
		// Remove any spaces present
		szMark.Replace(" ", "");
		sprintf( szBuffer, " %8.*s", szMark.GetLength(), (const char*)szMark );
	  	szDetailText +=szBuffer;

	  //qty hits
		sprintf( szBuffer, " %-i", pBeamRecord->m_tplHitList.GetCount() );
	  	szDetailText +=szBuffer;

		//hit details
	  	posOps = pBeamRecord->m_tplHitList.GetHeadPosition();
	    while(posOps)
		{
			pOperation =(CHole*)pBeamRecord->m_tplHitList.GetNext(posOps);
		
			//position
			sprintf( szBuffer, " %i", pOperation->GetPosX());
			szDetailText +=szBuffer;
			//punch
			sprintf( szBuffer, " %li", pOperation->GetPunch());
	  		szDetailText +=szBuffer;
		}

		//end of part 	
	  	szDetailText +="\n";
		
		//save job to disk
		POSITION pos = m_pDoc->m_pProjectSettings->m_tplOutputList.GetHeadPosition();
	
		while(pos)
		{
			pOut = m_pDoc->m_pProjectSettings->m_tplOutputList.GetNext(pos);
			if (pOut->m_sPLine == "Line_2")
			{
				szFullFilePath = pOut->m_sPath;
				break;
			}
		}
		szFullFilePath += ("\\" + szPartFileName);

		CFileException e;

		CFile PartFile( szFullFilePath, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone);

		if( e.m_cause == CFileException::badPath)
		{
			CWinApp* pApp;
			CWnd*	 pAppWnd;
			DWORD	flags = OFN_PATHMUSTEXIST;
			CString szFileName;
			pApp	= AfxGetApp();
			pAppWnd = pApp->m_pMainWnd;

			CFileDialog dlgOpen(TRUE,
								"ORD",
								NULL,
								flags,
								"Line 2 Output Files (*.ORD)|*.ORD||",
								pAppWnd);

			if (dlgOpen.DoModal() == IDOK)
			{
				szFileName = dlgOpen.GetPathName();
			}
		}
	
		PartFile.Write( (const void FAR*)(const char*)szDetailText, szDetailText.GetLength() );
	
		//	create a new 'PrintHitList' to be read by the CLeftView print function
		//  and delete ScriptList & HitList to avoid duplications on repeated generation

		//	First step through the 'PrintHitList'
		//	Compare 'PrintHitList OldOps' with 'HitList NewOps'.
		//	If 'OldOp' is not in new 'HitList' delete it.
		//  When all OldOps have been checked empty the PrintHitList
		//	ready for it to be re-populated by the HitList.
		
		POSITION posOld;
		POSITION posNew;
		CHole* pOldOp;
		CHole* pNewOp;

		posOld = pBeamRecord->m_tplPrintHitList.GetHeadPosition();
		while (posOld)
		{
			pOldOp = pBeamRecord->m_tplPrintHitList.GetNext(posOld);
			posNew = pBeamRecord->m_tplHitList.GetHeadPosition();
			while(posNew)
			{
				pNewOp =(CHole*)pBeamRecord->m_tplHitList.GetNext(posNew);
				if(pOldOp != pNewOp)
				{}
				else
				{
					break;
				}
			}
			// finished looping through PrintHitList - no match found for new op
			delete pOldOp;		// ... so trash unwanted operation
		}

		if(!pBeamRecord->m_tplPrintHitList.IsEmpty())
		{
			pBeamRecord->m_tplPrintHitList.RemoveAll();	// empty the current list
		}

		posOps = pBeamRecord->m_tplHitList.GetHeadPosition();
		while(posOps)
		{
			pOperation =(CHole*)pBeamRecord->m_tplHitList.GetNext(posOps);
			pBeamRecord->m_tplPrintHitList.AddTail(pOperation); // add to new list
		}
		pBeamRecord->m_tplHitList.RemoveAll();

		posOps = pBeamRecord->m_tplScriptList.GetHeadPosition();

		while(posOps)
		{
			pOperation =(CHole*)pBeamRecord->m_tplScriptList.GetNext(posOps);
			delete pOperation;
		}
		pBeamRecord->m_tplScriptList.RemoveAll();
	

	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//	
void CLine2::GetNewFileName(CString& szFileName)
{
	CWinApp* pApp;
	CWnd*	 pAppWnd;
	CString	 sDefaultDir;
	LPSTR	 lpstrDefaultDir;
	CString	 sPathName;
	DWORD	flags = OFN_PATHMUSTEXIST;
	COutputList* pList;
	pApp	= AfxGetApp();
	pAppWnd = pApp->m_pMainWnd;

	POSITION pos = this->m_pDoc->m_pProjectSettings->m_tplOutputList.GetHeadPosition(); 
	while(pos)
	{
		pList = this->m_pDoc->m_pProjectSettings->m_tplOutputList.GetNext(pos); 
		if (pList->m_sPLine == "Line_3")
		{
			sDefaultDir = pList->m_sPath;
		}
	}
	lpstrDefaultDir = sDefaultDir.GetBuffer(1);

	CFileDialog dlgOpen(FALSE,
						"L3",
						NULL,
						flags,
						"Line 3 Output Files (*.L3)|*.L3||",
						pAppWnd);

	dlgOpen.m_ofn.lpstrInitialDir = lpstrDefaultDir;

	if (dlgOpen.DoModal() == IDOK)
	{
		szFileName = dlgOpen.GetPathName();
	}
}