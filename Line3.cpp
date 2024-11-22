// Line3.cpp: implementation of the CLine3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "Line3.h"
#include "Element.h"
#include "BeamOps.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CLine3::MAX_MARK_LENGTH = 8;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
CLine3::CLine3()
{

}

CLine3::~CLine3()
{

}
*/

//////////////////////////////////////////////////////////////////////
//  GetPartFileName()
//
//	NB: By convention, in OD2, the filename is built using the order number
//		and the last two digits of the od2 'work file' filename extension. 
//		Also by convention the od2 'work file' filename is built from the order number and the item no.
//		(e.g. Item 1 of order P99999 would be saved to P99999.001)
//
void CLine3::GetPartFileName( CString* psz, CString& sItemID)	
{
	char szBuffer[80] ="";
	char* pchar;
	CString szDocTitle	= _T("");
	CString szProjectName	= _T("");
	CString szExtension = _T("");
	CString szFileName = _T("");

	szProjectName = this->m_pDoc->m_pProjectHeader->m_sProjectName;

	if (szProjectName.Left(1) != "P" && szProjectName.Left(1) != "S")

	{
		AfxMessageBox("Filename must reflect the job number");
		GetNewFileName(szProjectName);
	}

	szDocTitle = szProjectName;
	szDocTitle += ".";
	szDocTitle += sItemID;
	
	if(szDocTitle.CompareNoCase("Untitled"))
	{
		lstrcpy((LPSTR)szBuffer,(const char*)szDocTitle );
		
		pchar = szBuffer;
		while( *pchar != '.' )
			++pchar;

		szExtension = pchar + 1;		
		*pchar = 0;			

		szFileName = szBuffer;
		szFileName += (const char*)szExtension;
		szFileName += ".L3";
	}
/*	else
	{
		szFileName += sItemID;
		szFileName += ".L3";
	}
*/

	while( szFileName.GetLength() >12 )
	{
		CString szTemp = szFileName;
		szFileName = (const char*)szTemp + 1;
	}	
		
	*psz = szFileName;
}

//////////////////////////////////////////////////////////////////////
////
void CLine3::BuildDetails(CItem* pItem)	
{
	CString TempPath;

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

	short iPartIndex = 1;

	CString szJobFileName = _T("");
	CString szFullFilePath;
	this->GetPartFileName( &szJobFileName, sItemID);

	CElement* pElement, partSearch;
	CBeamElement* pBeamRecord;
	CHole* pOperation;
	COutputList* pOut;

	POSITION posElement, posOps;
	char szBuffer[80];
	CString szDetailText  = _T("");

	// document name
	sprintf( szBuffer, "<Document>%s\r\n", (const char*) szJobFileName);
	szDetailText += szBuffer;

	// section size
//	CString szSection = pItem->GetProductName();

//	We may need a routine here to strip out a slash in the profile name
//	do we also need to insert an underscore
//	what abot JR and SBE ???
	CString szSection;
	CString szTemp = pItem->GetProfile();
	CString szMarker;
	CString szLabel;
	int nPos = szTemp.Find(_T("/"),0);
	if (nPos > 0)
	{
		szSection = szTemp.Mid(nPos-1,1);
		szSection += "_";
		szSection += szTemp.Right((szTemp.GetLength())-(nPos+1));
	}
	else
	{
		if (szTemp.Left(3) == _T("SBE"))
		{
			szTemp = szTemp.Mid(3,(szTemp.GetLength()-3));
		}

		szMarker = szTemp.Left(3);
		if (szMarker.Left(3) == _T("SIG"))
		{
			szSection = szMarker;
			szSection += _T("_");
			szSection += szTemp.Right((szTemp.GetLength())-3);
		}
		else if (szMarker.Left(2) == _T("EB") || szMarker.Left(2) == _T("VB") || szMarker.Left(2) == _T("CW") || szMarker.Left(2) == _T("PS"))
		{
			szSection = szMarker.Left(2);
			szSection += _T("_");
			szSection += szTemp.Right((szTemp.GetLength())-2);
		}
		else if (szMarker.Left(1) == _T("C"))
		{
			szSection = szMarker.Left(1);
			szSection += _T("_");
			szSection += szTemp.Right((szTemp.GetLength())-1);
		}
		else if(partSearch.getPart(szTemp) == IDS_PART11)
		{
			// Swagebeam
			szSection = szMarker.Left(2);
			szSection += _T("_");
			szSection += szTemp.Right((szTemp.GetLength())-2);
		}
		else if (szMarker.Left(2) == _T("UR"))
		{
			szSection = szMarker.Left(2);
			szSection += _T("_");
			szSection += szTemp.Right(szTemp.GetLength()-2);
		}
	}

	sprintf( szBuffer, "<Section>%s\r\n\r\n", (const char*) szSection );
	szDetailText += szBuffer;

	posElement = pItem->m_tplElementList.GetHeadPosition();
	while (posElement)
	{
		pElement = pItem->m_tplElementList.GetNext(posElement);
		pBeamRecord = (CBeamElement*)pElement;

      //bundle count
		sprintf( szBuffer, "<Part#%i:BundleQuantity>%i\r\n", iPartIndex, pBeamRecord->GetBundle() );
	  	szDetailText +=szBuffer;

      //mark
		CString szMark =pElement->GetMark();
		// Remove any spaces present
		szMark.Replace(" ", "");
		sprintf( szBuffer, "<Part#%i:Mark>%s\r\n", iPartIndex, (const char*)szMark );
	  	szDetailText +=szBuffer;

	  //quantity
		sprintf( szBuffer, "<Part#%i:Quantity>%i\r\n", iPartIndex, pElement->GetQty() );
	  	szDetailText +=szBuffer;
	  	
	  //hit details
	  	int iHitIndex = 1;
	  	posOps = pBeamRecord->m_tplHitList.GetHeadPosition();
        while( posOps )
  		{
			pOperation =(CHole*)pBeamRecord->m_tplHitList.GetNext(posOps);
	  		
		  //position
			int nPos = pOperation->GetPosX();
			sprintf( szBuffer, "<Part#%i:Position#%i>%i\r\n", iPartIndex, iHitIndex, pOperation->GetPosX());
		  	szDetailText +=szBuffer;

		  //punch
		  	if( posOps != NULL )
			{
				sprintf( szBuffer, "<Part#%i:Punch#%i>%li\r\n", iPartIndex, iHitIndex, pOperation->GetPunch() );
			}
			else
			{
				sprintf( szBuffer, "<Part#%i:Punch#%i>END\r\n", iPartIndex, iHitIndex );
			}
		  	szDetailText +=szBuffer;
		  	
		  	++ iHitIndex;
	  	}

	  	szDetailText += "\r\n";

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
		if (!pBeamRecord->m_tplHitList.IsEmpty())
		{
			pBeamRecord->m_tplHitList.RemoveAll();
		}

		posOps = pBeamRecord->m_tplScriptList.GetHeadPosition();

		while(posOps)
		{
			pOperation =(CHole*)pBeamRecord->m_tplScriptList.GetNext(posOps);
			delete pOperation;
		}
		if (!pBeamRecord->m_tplScriptList.IsEmpty())
		{
			pBeamRecord->m_tplScriptList.RemoveAll();
		}
		
		++iPartIndex;
	}


	//save job to disk
	POSITION pos = m_pDoc->m_pProjectSettings->m_tplOutputList.GetHeadPosition();
	
	while(pos)
	{
		pOut = m_pDoc->m_pProjectSettings->m_tplOutputList.GetNext(pos);
		if (pOut->m_sPLine == "Line_3")
		{
			szFullFilePath = pOut->m_sPath;
			break;
		}
	}
	szFullFilePath += ("\\" + szJobFileName);

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
							"L3",
							NULL,
							flags,
							"Line 3 Output Files (*.L3)|*.L3||",
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
void CLine3::GetNewFileName(CString& szFileName)
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