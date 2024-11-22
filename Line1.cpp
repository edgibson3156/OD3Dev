// Line1.cpp: implementation of the CLine1 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "Line1.h"
#include "Element.h"
#include "BeamOps.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CLine1::MAX_MARK_LENGTH = 8;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/* CLine1::CLine1()
{

}

CLine1::~CLine1()
{

} */
//////////////////////////////////////////////////////////////////////
//
void CLine1::GetPartFileName( CString* psz, /*COD3Doc* pDocument,*/ CString& sItemID)	
{
//	CString szPathName	= this->m_pDoc->GetPathName();
	
	CString szFileName	= this->m_pDoc->m_pProjectHeader->m_sProjectName;

//	int nDirPath = szPathName.GetLength() - (szFileName.GetLength() + 4);
//	CString szDirPath	= szPathName.Left(nDirPath);

	if (szFileName.Left(1)!="S")
	{	goto step2;
	
		
	while( szFileName.GetLength() >11 )
		{
		CString szTemp = szFileName;
		szFileName = (const char*)szTemp + 1;
		}

		*(char*)(const char*)szFileName ='S';		
	
			
	*psz = szFileName;
	}

	
	{
//		szFileName = szFileName.Left(1);
//		szFileName += szFileName.Right(3);
		szFileName += sItemID;
		szFileName += ".ORD";
	


		while( szFileName.GetLength() >11 )
		{
		CString szTemp = szFileName;
		szFileName = (const char*)szTemp + 1;
		}

		*(char*)(const char*)szFileName ='S';		
	
		
	*psz = szFileName;
	}
	goto step1;
step2:

	
{
if (szFileName.Left(1) != "P")

	{
		AfxMessageBox("Filename must reflect the job number");
		CString szDocTitle;
		GetNewFileName(szDocTitle);
		char szBuffer[80] ="";
		char* pchar;
		CString szFileName	= _T("");
		CString szExtension = _T("");
		
		if(szDocTitle.CompareNoCase("Untitled"))
		{
			lstrcpy((LPSTR)szBuffer,(const char*)szDocTitle );
		
			pchar = szBuffer;
			while( *pchar != '.' )
				++pchar;

			szExtension = pchar + 1;		
			*pchar = 0;			

			szFileName = szBuffer;
			szFileName += (const char*)szExtension + 1;
			szFileName += ".ORD";
		}
	


	while( szFileName.GetLength() >11 )
		{
		CString szTemp = szFileName;
		szFileName = (const char*)szTemp + 1;
		}

		*(char*)(const char*)szFileName ='P';		
	
			
	*psz = szFileName;
	}



	else
	{
//		szFileName = szFileName.Left(1);
//		szFileName += szFileName.Right(3);
		szFileName += sItemID;
		szFileName += ".ORD";
	


		while( szFileName.GetLength() >11 )
		{
		CString szTemp = szFileName;
		szFileName = (const char*)szTemp + 1;
		}

		*(char*)(const char*)szFileName ='P';		
	
	
	*psz = szFileName;
	step1:	;
	}

}
}

void CLine1::BuildDetails(CItem* pItem)	
{
	CString sItemID;
	int nItemID = pItem->m_nItemID;
	sItemID.Format("%d",nItemID);
	if (nItemID < 10){sItemID = "0" + sItemID;}

	CString szJobFileName = _T("");
	CString szFullFilePath;
	this->GetPartFileName( &szJobFileName, sItemID);

	CElement* pElement;
	CBeamElement* pBeamRecord;
	CHole* pOperation;
	COutputList* pOut;

	POSITION posElement, posOps;
	char szBuffer[80];
	CString szDetailText  = _T("");

	short iPartIndex = 1;

	// Section Place holder
	CString TempSection;

	posElement = pItem->m_tplElementList.GetHeadPosition();
	while (posElement)
	{
		pElement = pItem->m_tplElementList.GetNext(posElement);
		pBeamRecord = (CBeamElement*)pElement;

	  //part name
		CString szPartName = (const char*)szJobFileName.Mid(1, 6);
//		sprintf( szBuffer, "%-6.6s/%2.2i\r\n", (const char*)szJobFileName, iPartIndex );
		sprintf( szBuffer, "%-6.6s/%2.2i\r\n", (const char*)szPartName, iPartIndex );
		szDetailText +=szBuffer;

  	 // Section size	(VHF 18/1/1999 - Includes fix for Line 1 customer special part names)
  
	 // Get section
		TempSection = pItem->GetProfile();
	

	// Check if this is an SBE Special
		if (TempSection.Left(3) == _T("SBE"))
		{
			// Slice out "SBE_ZETA etc"
		   TempSection = TempSection.Right(7);
		   if (TempSection.Left(1) == _T("E") && TempSection.Left(2) != _T("EB"))
		   {
			   TempSection = TempSection.Right(6);
		   }
		}
		// Check if this is a John Reid Special
		else if (TempSection.Left(2) == "JR")
		{
			// Slice out jr_
			TempSection = TempSection.Right(TempSection.GetLength() - 2);
		}


	// Trim off first 2 chars (e.g. "1/" for 1/17516)
		sprintf( szBuffer, " %s", (const char*)TempSection+2 );

	// Appen last two chars (e.g. 17516 becomes 1716)
		sprintf( &szBuffer[3], (const char*)TempSection+5 );

	// Add to detail text
		szDetailText +=szBuffer;
		szDetailText +="\r\n";

	//quantity
		sprintf( szBuffer, " %-3i\r\n", pBeamRecord->GetQty() );
  		szDetailText +=szBuffer;
	
	//bundle count
		sprintf( szBuffer, " %-2i\r\n", pBeamRecord->GetBundle() );
			szDetailText +=szBuffer;
    //mark
		CString szMark =pBeamRecord->GetMark();
		// Remove any spaces present
		szMark.Replace(" ", "");
		sprintf( szBuffer, "%s\r\n", (const char*)szMark );
	  	szDetailText +=szBuffer;

	//hit details
	  	posOps = pBeamRecord->m_tplHitList.GetHeadPosition();
	    while(posOps)
		{
			pOperation =(CHole*)pBeamRecord->m_tplHitList.GetNext(posOps);
		
		//position
			sprintf( szBuffer, " %i\r\n", pOperation->GetPosX());
			szDetailText +=szBuffer;
		//punch
			sprintf( szBuffer, " %li\r\n", pOperation->GetPunch());
	  		szDetailText +=szBuffer;
		}

		//null position/punch at end of part
	  	szDetailText +=" 0\r\n";
	  	szDetailText +=" 0\r\n";

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
	
		++iPartIndex;
	}	/* posElement == NULL */


//job terminator
	szDetailText +="!!!\r\n";

//save job to disk
	POSITION pos = m_pDoc->m_pProjectSettings->m_tplOutputList.GetHeadPosition();
	
	while(pos)
	{
		pOut = m_pDoc->m_pProjectSettings->m_tplOutputList.GetNext(pos);

		if (pOut->m_sPLine == "Line_1")
		{
			szFullFilePath = pOut->m_sPath;
			break;
		}
	}

	szFullFilePath += ("\\" + szJobFileName);

	CFileException e;

	CFile PartFile( szFullFilePath, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone);

	if( e.m_cause==CFileException::badPath)
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
							"Line 1 Output Files (*.ord)|*.ord||",
							pAppWnd);

		if (dlgOpen.DoModal() == IDOK)
		{
			szFileName = dlgOpen.GetPathName();
		}
	}
	PartFile.Write( (const void FAR*)(const char*)szDetailText, szDetailText.GetLength() );
}
		



/////////////////////////////////////////////////////////////////////////////////////////
//	
void CLine1::GetNewFileName(CString& szFileName)
{
	CWinApp* pApp;
	CWnd*	 pAppWnd;
	CString	 sDefaultDir;
	LPSTR	 lpstrDefaultDir;
	CString	 sPathName;
//	LPSTR	 lpszPathName;
	DWORD	flags = OFN_PATHMUSTEXIST;
	COutputList* pList;
	pApp	= AfxGetApp();
	pAppWnd = pApp->m_pMainWnd;

	POSITION pos = this->m_pDoc->m_pProjectSettings->m_tplOutputList.GetHeadPosition(); 
	while(pos)
	{
		pList = this->m_pDoc->m_pProjectSettings->m_tplOutputList.GetNext(pos); 
		if (pList->m_sPLine == "Line_1")
		{
			sDefaultDir = pList->m_sPath;
		}
	}
	lpstrDefaultDir = sDefaultDir.GetBuffer(1);

	CFileDialog dlgOpen(FALSE,
						"ORD",
						NULL,
						flags,
						"Line 1 Output Files (*.ord)|*.ord||",
						pAppWnd);

	dlgOpen.m_ofn.lpstrInitialDir = lpstrDefaultDir;

	if (dlgOpen.DoModal() == IDOK)
	{
		szFileName = dlgOpen.GetPathName();
	}
}