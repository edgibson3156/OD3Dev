// ImportDet3.cpp: implementation of the CImportDet3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "ImportDet3.h"
#include "misc.h"
#include "DaoProductCode.h"
#include "DlgNewProject.h"
#include "DlgWernik.h"
#include "DaoEavesBySlope.h"
#include "ProductData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImportDet3::CImportDet3()
{
	m_DocSize.cx=m_DocSize.cy = 0;
	m_nGauge=
	m_nWeight = 0.0l;

	m_pItem = NULL;
	m_pBeam = NULL;
	m_pDoc = NULL;

	m_iIsWernik=0;
}

CImportDet3::~CImportDet3()
{
	CImportD3Acc* pAcc;
	CImportD3Beam* pBeam;

	while(!m_tplAccessoryList.IsEmpty())
	{
		pAcc = m_tplAccessoryList.GetTail();
		pAcc = m_tplAccessoryList.RemoveTail();
		delete pAcc;
	}

	while(!m_tplBeamList.IsEmpty())
	{
		pBeam = m_tplBeamList.GetTail();
		pBeam = m_tplBeamList.RemoveTail();
		delete pBeam;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// ParseALargeFile - parses a large file and uses a progress bar to 
//					 indicate the progress of the parsing operation. 
//
//		Returns TRUE if successful, or FALSE otherwise. 
//		hwndParent - parent window of the progress bar. 
//		lpszFileName - name of the file to parse.
//
//		Global variable 
//			g_hinst - instance handle

// 	extern HINSTANCE g_hinst;
	
BOOL ParseALargeFile(HWND hwndParent, LPSTR lpszFileName)
{ 
/*    RECT rcClient;  // client area of parent window 
    int cyVScroll;  // height of scroll bar arrow 
    HWND hwndPB;    // handle of progress bar 
    HANDLE hFile;   // handle of file 
    DWORD cb;       // size of file and count of bytes read 
    LPCH pch;       // address of data read from file 
    LPCH pchTmp;    // temporary pointer 
	
    // Ensure that the common control DLL is loaded and create a 
    // progress bar along the bottom of the client area of the 
    // parent window. Base the height of the progress bar on 
    // the height of a scroll bar arrow.
//	LPINITCOMMONCONTROLSEX lpInitCtrls;
//	lpInitCtrls->dwICC = ICC_PROGRESS_CLASS;
//	lpInitCtrls->dwSize = sizeof(ICC_PROGRESS_CLASS);
	InitCommonControls() /*Ex(lpInitCtrls)*/;
		
/*	GetClientRect(hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(0, PROGRESS_CLASS, (LPSTR) NULL, 
							WS_CHILD | WS_VISIBLE, rcClient.left, 
							rcClient.bottom - cyVScroll,
							rcClient.right, cyVScroll, 
							hwndParent, (HMENU) 0, g_hinst, NULL);  

    // Open the file for reading, and retrieve the size of the file. 
    hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, 
	        (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, 
		    FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);  

    if (hFile == (HANDLE) INVALID_HANDLE_VALUE)
		return FALSE;  

    cb = GetFileSize(hFile, (LPDWORD) NULL);
	
    // Set the range and increment of the progress bar. 
    SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, cb / 2048)); 
    SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0);
	
	// Parse the file. 
    pch = (LPCH) LocalAlloc(LPTR, sizeof(char) * 2048);
	pchTmp = pch; 
    do {
		ReadFile(hFile, pchTmp, sizeof(char) * 2048, &cb, 
				 (LPOVERLAPPED) NULL);
		 
        // Include here any code that parses the file.         .  
   
		// Advance the current position of the progress bar 
        // by the increment.
		SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
		} while (cb);
	
	CloseHandle((HANDLE) hFile);
	DestroyWindow(hwndPB); 
*/
    return TRUE;

}	

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	OpenFile()
/*
	Design:		Detail 3 Documents are serialized using the private profile strings
				to produce human readable documents as opposed to binary documents.
				MFC serialization methods are not used.

	Method:
				call common File|Open dialog
				get filename

				read file

				if read ok
				get reference to view
				set reference to first beam
				set reference to first accessory
				set display mode
		
				return success/failure
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool CImportDet3::OpenFile()
{
	CWinApp	*pApp;
	CWnd	*pAppWnd;
	CString	sDefaultDir(_T("")), sPathName(_T(""));
	LPSTR	lpstrDefaultDir;
	LPSTR	lpszPathName;
	bool	bFileReadSuccess = false;
	DWORD	flags = OFN_FILEMUSTEXIST|
					OFN_HIDEREADONLY|
     				OFN_PATHMUSTEXIST|
					OFN_SHAREWARN;

	pApp	= AfxGetApp();
	pAppWnd = pApp->m_pMainWnd;


	sDefaultDir = m_pDoc->m_pProjectSettings->m_sAutoFileInputPath;
	lpstrDefaultDir = sDefaultDir.GetBuffer(1);

	CFileDialog dlgOpen(TRUE, "TXT", NULL, flags,
							"Ayrshire Detail 3 (*.d3)|*.d3||",
							pAppWnd);

	// Set default directory
	dlgOpen.m_ofn.lpstrInitialDir = lpstrDefaultDir;

	// Open common dialog
	if (dlgOpen.DoModal() == IDOK)
	{
 
		AfxGetApp()->DoWaitCursor(0); // same as CCmdTarget::RestoreWaitCursor   
		
		// Get file path
		sPathName = dlgOpen.GetPathName();
		// Set the d3 file name
		m_fileName = dlgOpen.GetFileName();

		// Set member file path and name
		m_sD3FileName = sPathName;
		
		try
		{
			CFile fD3Import( sPathName, CFile::modeCreate|
								CFile::modeNoTruncate|
								CFile::modeRead|
								CFile::shareDenyNone);

			lpszPathName = sPathName.GetBuffer(1);

			// Close the file pointer
			fD3Import.Close();

			// Read document
			bFileReadSuccess = this->Read((LPSTR)lpszPathName);
		}
		catch(CFileException *e)
		{
			// Report file exception
			e->ReportError(MB_ICONWARNING);	
			// Remove exception and continue app
			e->Delete();
		}
	}

	//return success/failure
	return bFileReadSuccess;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	Read()		Read 'Det3' document from disk.
/*
	Design:

	read document specific attributes

		Owner
		File
		Project
		DrawnBy
		
	read beam list
	read accessory list
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool CImportDet3::Read(LPSTR lpszDocSource)
{
	CString szSection	= "Document";
	CString szDefault   = _T(""); 
	CString szEntry		= _T("");
	CString szReturnBuffer   = _T("");
	CBigIni ABigIni(lpszDocSource);


  //read document specific attributes
	szEntry	= "File"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szFile = szReturnBuffer;

	szEntry	= "ReleaseType"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szReleaseType = szReturnBuffer;

	szEntry	= "Project"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szProject = szReturnBuffer;

	szEntry	= "Owner"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szOwner = szReturnBuffer;
	SimpleFindAndReplace((LPSTR)(const char*)this->m_szOwner, "~~", "\r\n" );

	szEntry	= "Comment"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szComments = szReturnBuffer;
	szEntry	= "GeneralDrawingComment"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szComments = this->m_szComments + "\r\n" + szReturnBuffer;
	SimpleFindAndReplace((LPSTR)(const char*)this->m_szComments, "~~", "\r\n" );

	szEntry	= "DeliverTo"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDestination = szReturnBuffer;
	SimpleFindAndReplace((LPSTR)(const char*)this->m_szDestination, "~~", "\r\n" );

	szEntry	= "DeliveryDate"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szDeliveryDate = szReturnBuffer;
	
	szEntry	= "PackingRequirements"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	this->m_szPackingSpec = szReturnBuffer;
	SimpleFindAndReplace((LPSTR)(const char*)this->m_szPackingSpec, "~~", "\r\n" );

	/***************************************************************/
	szEntry	= "Version"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szVersion = szReturnBuffer;

	szEntry	= "BuildOrigin"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szbOrigin = szReturnBuffer;

	szEntry	= "Client"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szClient = szReturnBuffer;

	szEntry	= "DrawnBy"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szDrawnBy= szReturnBuffer;

	szEntry	= "Detailer"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szDetailer = szReturnBuffer;

	szEntry	= "JobNo"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szJobNO = szReturnBuffer;

	szEntry	= "Part"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szPart = szReturnBuffer;

	szEntry	= "Reference"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szRef = szReturnBuffer;

	szEntry	= "ModifiedDate"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szModifiedDate = szReturnBuffer;

	szEntry	= "CheckedBy"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szCheckedBy = szReturnBuffer;

	szEntry	= "CheckedDate"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szCheckedDate = szReturnBuffer;

	szEntry	= "ApprovedBy"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szApprovedBy = szReturnBuffer;

	szEntry	= "ApprovedDate"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szApprovedDate= szReturnBuffer;

	szEntry	= "RevisedBy"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szRevisedBy = szReturnBuffer;

	szEntry	= "GeneralDrawingComment"; 
	ABigIni.GetPrivateProfileString( szSection, szEntry, szDefault, szReturnBuffer );
	m_szDrawingComment = szReturnBuffer;
	/***************************************************************/

  //read beam list
  	this->ReadBeamList(ABigIni);
	
  //read accessory list
 	this->ReadAccList(ABigIni);


	return TRUE;
}
	


//////////////////////////////////////////////////////////////////////////////
//	Procedure:	Find~~~~()	Test if item mark is in beam/accessory list.
//	Returns 	true/false indicating if item is in list
//
//				two similar function for beams and accessories having
/*
	Design:
	
	for each mark in list
		if test mark = this mark
			return beam
			
	return null
*/
//----------------------------------------------------------------------------
//	FindBeamByMark()
//
CImportD3Beam* CImportDet3::FindBeamByMark(LPCSTR lpszTestMark)
{
  // ... for each mark in list
  	POSITION pos = this->m_tplBeamList.GetHeadPosition();
  	while(pos)
	{
  	  	CImportD3Beam* pRecord = (CImportD3Beam*)this->m_tplBeamList.GetNext(pos);
  	  	
  	  //if test mark = this mark
  	  	if(!lstrcmp(pRecord->GetMark(), lpszTestMark))
  		{
		  //return existance
		  	return pRecord;
	  	}
	}
  //return non existance
  	return NULL;
}
//----------------------------------------------------------------------------
//	FindAccessory
//
CImportD3Acc* CImportDet3::FindAccessory(LPCSTR lpszTestMark)
{
  	POSITION pos = this->m_tplAccessoryList.GetHeadPosition();

	// ... for each mark in list
  	while(pos)
	{
  	  	CImportD3Acc* pRecord = (CImportD3Acc*)this->m_tplAccessoryList.GetNext(pos);
  	  	
  	  //if test mark = this mark
  	  	if(!lstrcmp( pRecord->GetMark(), lpszTestMark))
  		{
		  //return existance
		  	return pRecord;
	  	}
	}
			
  //return non existance
  	return NULL;
}    
//----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//	Procedure:	Get~~~Index()	return zero based index of object in list.
//				two similar function for beams and accessories
//				each having different return types and arguments
/*
	Design:
	
	for each object in list
		if test object = this object
			return index
			
	return 0
*/
//----------------------------------------------------------------------------
//	GetBeamIndex
//
int CImportDet3::GetBeamIndex(CImportD3Beam* pThisBeam)
{
	int iIndex = 0;
	
	POSITION pos = this->m_tplBeamList.GetHeadPosition();
  //for each object in list
	while(pos)
	{
		CImportD3Beam* pTestObject =(CImportD3Beam*)this->m_tplBeamList.GetNext(pos);

      //if test object = this object
		if(pTestObject == pThisBeam)
		{		
		  //return index
		  	return iIndex;
		}

		++iIndex;
	}
			
		//return 0
	return 0;
}

//----------------------------------------------------------------------------
//	GetAccIndex
//
int CImportDet3::GetAccIndex(CImportD3Acc* pThisAccessory)
{
	int iIndex = 0;
	
	POSITION pos = this->m_tplAccessoryList.GetHeadPosition();
  //for each object in list
	while(pos)
	{
		CImportD3Acc* pTestObject =(CImportD3Acc*)this->m_tplAccessoryList.GetNext(pos);

      //if test object = this object
		if( pTestObject == pThisAccessory )
		{		
		  //return index
		  	return iIndex;
		}

		++iIndex;
	}
			
	//return 0
	return 0;
}
//----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//	Procedure:	Is~~Head()	Test for first beam/accessory in list
/*
	Design:
*/
//----------------------------------------------------------------------------
//	IsBeamHead
//
bool CImportDet3::IsBeamHead(CImportD3Beam* pBeam)
{
  	if(pBeam != NULL )
  		return false;
  	
  	if(this->m_tplBeamList.IsEmpty() ||
	  		 pBeam != (CImportD3Beam*)this->m_tplBeamList.GetHead())
	{
   		return false;
	}
	else
	{
		return true;
	}
}
//----------------------------------------------------------------------------
//	IsAccHead
//
bool CImportDet3::IsAccHead(CImportD3Acc* pAccessory)
{
  	if(pAccessory==NULL)
  		return false;
  	
  	if(this->m_tplAccessoryList.IsEmpty() ||
  		pAccessory != (CImportD3Acc*)this->m_tplAccessoryList.GetHead())
  		{
	   		return false;
   		}
	else
		{
			return true;
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	ItemMarkExists()	Test if item mark is in beam list.
//	Returns 	TRUE/FALSE indicating if item is in beam list
/*
	Design:
	
	find beam in list
	if beam found	
		return success
			
	return failure
*/
//----------------------------------------------------------------------------
/*
BOOL CBeamList::ItemMarkExists( LPCSTR lpszTestMark )
	{
  //find beam in list
  	CBeam* pRecord =this->FindRecord( lpszTestMark );
  	
  //if beam found	
  	if( pRecord!=NULL )
	  	{
	  //return success
	  	return TRUE;
	  	}
			
  //return failure
  	return FALSE;
	}    
*/	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
bool CImportDet3::ItemMarkExists(LPCSTR lpszTestMark)
{
  //search beam list...
  	CImportD3Beam* pBeamRecord = (CImportD3Beam*) this->FindBeamByMark(lpszTestMark);
  	
  //...if beam found return success	
  	if( pBeamRecord != NULL )
	{
		return true;
	}

  //search accessory list...
  	CImportD3Acc* pAccRecord = (CImportD3Acc*) this->FindAccessory(lpszTestMark);
  	
  //...if accessory found return success	
  	if( pAccRecord != NULL )
	{
		return true;
	}
			
  //... if not, return failure
  	return FALSE;
}    
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	Is~~Tail()	Test for first beam/accessory in repsective list
//
//----------------------------------------------------------------------------
//	IsTail()	Test for first beam
//
bool CImportDet3::IsBeamTail(CImportD3Beam* pBeam)
{
  	if( pBeam == NULL )
  		return false;
  	
  	if( this->m_tplBeamList.IsEmpty() ||
  				pBeam != (CImportD3Beam*)this->m_tplBeamList.GetTail())
	{
   		return false;
	}
	else
	{
		return true;
	}
}
//----------------------------------------------------------------------------
//	IsAccTail()	Test for first accessory
//
bool CImportDet3::IsAccTail( CImportD3Acc* pAccessory )
{
  	if(pAccessory!= NULL)
		return false;

	if(this->m_tplAccessoryList.IsEmpty() ||
		   		 pAccessory != this->m_tplAccessoryList.GetTail())
	{
		return false;
	}
	else
	{
		return true;
	}
}
//----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	Read~~()	Read beam/accessory list from source.
/*
	Design:
*/
//----------------------------------------------------------------------------
//	ReadBeamList
//
bool CImportDet3::ReadBeamList(CBigIni& ABigIni)
{
    int		iBeamIndex	= 0;
	bool	loop		= true;
	CString szMsg		= _T("");
	CString sBeamIndex	= _T("");
	LPCTSTR lpszText	= _T("");
	CString	sSwageBeam	= _T("SWAGEBEAM");
	CString	sProduct;
	
	do
	{	
	    CImportD3Beam* pNewBeam = new CImportD3Beam();
	
		if(pNewBeam->Read(ABigIni, iBeamIndex ) != false )
		{
			if(!sSwageBeam.CompareNoCase(pNewBeam->GetProductType()))
			{
				if(m_iIsWernik==0)
				{
					CDlgWernik dlgWernik;

					// Open the question dialog
					m_iIsWernik = dlgWernik.DoModal();
				}

				if(isWernik())
				{
					sProduct = pNewBeam->GetProductName();
					sProduct += _T("W");

					// Change to Wernik
					pNewBeam->SetProductName(sProduct.GetBuffer(sProduct.GetLength()));
				}
			}

			// display beam index in status bar
			sBeamIndex.Format("%d",iBeamIndex);
			szMsg = "Reading Beam No. ";
			szMsg += sBeamIndex;
			lpszText = (LPCTSTR)szMsg;
			this->UpdateStatusBar(lpszText);

			// add beam to list of imported beams
			this->m_tplBeamList.AddTail(pNewBeam);
			++iBeamIndex;
		}
		else
		{
			szMsg = _T("");
			lpszText = (LPCTSTR)szMsg;
			this->UpdateStatusBar(lpszText);
			delete pNewBeam;
			break;
		}
		
	}while(true);


	if( iBeamIndex == 0 )
		return false;

	return true;
}
//----------------------------------------------------------------------------
//	ReadAccList()	
//
bool CImportDet3::ReadAccList(CBigIni& ABigIni)
{
    int iIndex = 0;
	CString szMsg		= _T("");
	CString sIndex		= _T("");
	LPCTSTR lpszText	= _T("");
	
	do
	{	
	    CImportD3Acc* pNewAccessory = new CImportD3Acc();
	
		if(pNewAccessory->Read(ABigIni, iIndex) != false)
		{
			sIndex.Format("%d",iIndex);
			szMsg = "Reading Accessory No. ";
			szMsg += sIndex;
			lpszText = (LPCTSTR)szMsg;
			this->UpdateStatusBar(lpszText);

			this->m_tplAccessoryList.AddTail(pNewAccessory);
			++iIndex;
		}
		else
		{
			szMsg = _T("");
			lpszText = (LPCTSTR)szMsg;
			this->UpdateStatusBar(lpszText);
			delete pNewAccessory;
			break;
		}
		
	}while(true);

	if( iIndex == 0 )
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Sort~~ByAscendingProductName()	Sort beam/accessory list using Bubble sort...
//
//-----------------------------------------------------------------------------------------
//	SortBeamsByAscendingProductName()	Sort beam list using Bubble sort...
//
void CImportDet3::SortBeamsByAscendingProductName()
{
	POSITION ResultsPosition;
	CImportD3Beam* pRecord1;
	CImportD3Beam* pRecord2;
	bool bModified = false;
	char szProductName1[80];
	char szProductName2[80];

  start:
	bModified = false;

  //get results head for sort
  	ResultsPosition = this->m_tplBeamList.GetHeadPosition();
  	if(!ResultsPosition)
  		return;

  //bubble sort 	
  	do
	{
	  //get record1	
		pRecord1 =(CImportD3Beam*)this->m_tplBeamList.GetNext(ResultsPosition);
		if(!ResultsPosition)
			break;
				
	  //get record2	
		pRecord2 =(CImportD3Beam*)this->m_tplBeamList.GetNext(ResultsPosition);
			
	  //do comparison
		lstrcpy((LPSTR)szProductName1, pRecord1->GetProductName());
		lstrcpy((LPSTR)szProductName2, pRecord2->GetProductName());
		if(lstrcmp((LPSTR)szProductName1, (LPSTR)szProductName2) > 0)
  		{
	  	  //do swap	
	  	  	this->BeamSwap( pRecord1, pRecord2 );
	  		bModified = true;
  		}

  		ResultsPosition = this->m_tplBeamList.Find(pRecord2);
	  	  	
  	}while(ResultsPosition);
		
	if(bModified != false)
		goto start;
}

//-----------------------------------------------------------------------------------------
//	SortAccByAscendingProductName()	Sort accessory list using Bubble sort...
//
void CImportDet3::SortAccByAscendingProductName()
{
	POSITION ResultsPosition;
	CImportD3Acc* pRecord1;
	CImportD3Acc* pRecord2;
	bool bModified = false;
	char szProductName1[80];
	char szProductName2[80];

  start:
	bModified = false;

  //get results head for sort
  	ResultsPosition = this->m_tplAccessoryList.GetHeadPosition();
  	if( !ResultsPosition )
  		return;

  //bubble sort 	
  	do
	{
	  //get record1	
		pRecord1 =(CImportD3Acc*)this->m_tplAccessoryList.GetNext(ResultsPosition);
		if( !ResultsPosition )
			break;
				
	  //get record2	
		pRecord2 =(CImportD3Acc*)this->m_tplAccessoryList.GetNext(ResultsPosition);
			
	  //do comparison
		lstrcpy((LPSTR)szProductName1, pRecord1->GetType());
		lstrcpy((LPSTR)szProductName2, pRecord2->GetType());
		if(lstrcmp((LPSTR)szProductName1, (LPSTR)szProductName2) > 0)
  		{
			//do swap	
	  	  	this->AccSwap( pRecord1, pRecord2 );
	  		bModified = true;
  		}

  		ResultsPosition = this->m_tplAccessoryList.Find(pRecord2);
	  	  	
  	}while(ResultsPosition);
		
	if( bModified != false )
		goto start;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	FindListedItem()	Find matching item in the document's m_tplItemList
//
bool CImportDet3::FindListedItem(CImportD3Beam* pD3Beam, bool &bIgnore)
{
	POSITION pos;
	CString  sProductCode	= _T("");
	CString	 sListedName	= _T("");
	CString  sListedCode	= _T("");
	CString  sCode			= _T("");
	bool	 bMatchFound	= false;

	CString	 sRelType		= (CString)this->GetReleaseType();
	CString	 sProductName	= (CString)pD3Beam->GetProductName();
	int		 nType			= pD3Beam->GetMemberType();;
	int		 nListedType	= 0;

	CItem*	 pItem;
	CItem*	 pLastItem;
	bool	 bIsEaves;

	// test to see if its an SBE product
	if(sRelType != _T("SBE") && sRelType != _T("AYRDT_SBE"))
	{}
	else if((CString)pD3Beam->GetProductType() != _T("ASSOCIATED_SECTION") && 
			(CString)pD3Beam->GetProductType() != _T("SWAGEBEAM") )
	{
		this->GetSBEName(sProductName);
	}

	// Check if the product is an eaves beam
	if((CString)pD3Beam->GetProductType() == _T("EAVES_BEAM"))
	{
		// Perform eaves beam slope testing
		sProductCode = findEavesBeam(pD3Beam->GetProductName(), pD3Beam->GetSlope());
		bIsEaves = true;
	}
	else
	{
		// get product code for this beam
		sProductCode = this->FindProductCode(sProductName, nType);
		bIsEaves = false;
	}

	// Test if the product is in the ignore list
	if(!(bIgnore=ignoreItem(sProductName)))
	{
		//now step through the document's item list looking for a match with the current beam
		pos = this->m_pDoc->m_tplItemList.GetHeadPosition();

		while(pos)
		{
			while(!bMatchFound)
			{
				pItem = this->m_pDoc->m_tplItemList.GetNext(pos);

				sListedName = pItem->GetProfile();
				nListedType = pItem->GetType();
				sListedCode = pItem->GetProductCode();

				// Use different search for product matching eaves beams
				if(bIsEaves)
				{
					if(sListedCode == sProductCode)
					{
						// Set member pointer
						m_pItem = pItem;
						// Return found
						return(true);
					}
				}
				else
				{
					if(
						( sListedCode == sProductCode ) || 
						( (sListedName == (CString)pD3Beam->GetProductName()) &&
						  (nListedType == pD3Beam->GetMemberType() ) ) )
					{
						if(sListedName == "TP")	// need to check all inputs for TP Custom to identify if same item or not
						{
							if (pD3Beam->GetGauge() != pItem->GetGauge())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
			
							int nDepth = pD3Beam->GetDimC() + pD3Beam->GetDimE() + pD3Beam->GetDimF();
							if (nDepth != pItem->GetDepth())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}

							if (pD3Beam->GetDimA() != pItem->GetTopFlange())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
					
							if (pD3Beam->GetSlope() != pItem->GetTopFlangeSlope())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
						
							if (pD3Beam->GetTopLip() != pItem->GetTopFlangeLip())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
						
							if (pD3Beam->GetDimB() != pItem->GetBottomFlange())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
						
							if (pD3Beam->GetTPBSlope() != pItem->GetBottomFlangeSlope())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
						
							if (pD3Beam->GetBottomLip() != pItem->GetBottomFlangeLip())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
						
							if (pD3Beam->GetDimC() != pItem->GetDimC())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
						
							if (pD3Beam->GetDimF() != pItem->GetDimF())
							{
								bMatchFound = false;
								break;
							}
							else
							{
								bMatchFound = true;
							}
						}	// end of TP conditional checks

						this->m_pItem = pItem;
						return true;

					}		//	end of matched product code condition
				}
				
				//	 check that we are not at the end of the list before repeating the loop
				if (this->m_pDoc->m_tplItemList.IsEmpty())
				{
					break;
				}
				else
				{
					pLastItem = this->m_pDoc->m_tplItemList.GetTail();
					if (pItem == pLastItem)
					{
						break;
					}
				}

			}		// end of bMatchFound while loop

		}		// end of ItemList while loop
	}


	//item does not exist
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	FindListedBeam()	Find matching element in the CItem's m_tplElementList
//

bool CImportDet3::FindListedBeam(CImportD3Beam* pD3Beam)
{
	POSITION pos;
	CElement* pElement;
	CString	 sMark = _T("");

	pos = m_pItem->m_tplElementList.GetHeadPosition();
	while(pos)
	{
		pElement = m_pItem->m_tplElementList.GetNext(pos);
		sMark = pElement->GetMark();

		if(sMark == (CString)pD3Beam->GetMark())
		{
			m_pBeam = (CBeamElement*)pElement;
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CompareBeam()	Compare the CBeamElement data with the CImportD3Beam data
//
bool CImportDet3::CompareBeam(CImportD3Beam* pD3Beam)
{

	CBeamDlg* pDlg = 0;
	int	cBeamCounter;
	int	nQty;
	CString	szMarkNo;
	CString	szSPC;
	CString	szComment;
	int	nBundleCount;
	int	nLength;
	int	nSpan1;
	int	nSpan2;
	int	nSpan3;
	int	nOHang1;
	int	nOHang2;
	int	nCol1;
	int	nCol2;
	int	nEBSlope;
	int	nMemberType;
	int nItemID;
	CString szMsg;
	CString sItemID;
	CString szItemLabel;

	nItemID = m_pItem->GetItemID();
	sItemID.Format("%d",nItemID);
	szItemLabel = "Item ";
	szItemLabel += sItemID;

	m_pBeam->GetBeam(pDlg,
					cBeamCounter,
					nQty,
					szMarkNo,
					szSPC,
					szComment,
					nBundleCount,
					nLength,
					nSpan1,
					nSpan2,
					nSpan3,
					nOHang1,
					nOHang2,
					nCol1,
					nCol2,
					nEBSlope,
					nMemberType);

	if(nQty != pD3Beam->GetQty())
	{
		szMsg = szItemLabel;
		szMsg += "/nnQuantity for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(szSPC != (CString)pD3Beam->GetSPC())
	{
		szMsg = szItemLabel;
		szMsg += "/nnSPC code for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(szComment != (CString)pD3Beam->GetComment())
	{
		szMsg = szItemLabel;
		szMsg += "/nnComment for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(nLength != pD3Beam->GetLength())
	{
		szMsg = szItemLabel;
		szMsg += "/nnLength for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(nSpan1 != pD3Beam->GetSpan1())
	{
		szMsg = szItemLabel;
		szMsg += "/nnSpan1 for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(nSpan2 != pD3Beam->GetSpan2())
	{
		szMsg = szItemLabel;
		szMsg += "/nnSpan2 for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(nSpan3 != pD3Beam->GetSpan3())
	{
		szMsg = szItemLabel;
		szMsg += "/nnSpan3 for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(nOHang1 != pD3Beam->GetOverhang1())
	{
		szMsg = szItemLabel;
		szMsg += "/nnOverhang1 for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

	if(nOHang2 != pD3Beam->GetOverhang2())
	{
		szMsg = szItemLabel;
		szMsg += "/nnOverhang2 for mark ";
		szMsg +=	szMarkNo;
		szMsg += " has been revised";
		AfxMessageBox(szMsg);
		return true;
	}

//	if(nCol1 != pD3Beam->GetColumnWidth1())
//	{
//		szMsg = szItemLabel;
//		szMsg += "/nnColumn Width 1 for mark ";
//		szMsg +=	szMarkNo;
//		szMsg += " has been revised";
//		AfxMessageBox(szMsg);
//		return true;
//	}
//	if(nCol2 != pD3Beam->GetColumnWidth2())
//	{
//		szMsg = szItemLabel;
//		szMsg += "/nnColumn Width 1 for mark ";
//		szMsg +=	szMarkNo;
//		szMsg += " has been revised";
//		AfxMessageBox(szMsg);
//		return true;
//	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ListImportedItems()	Create list of items - i.e. different products
//
void CImportDet3::ListImportedItems()
{
	POSITION  posBeam;
	POSITION  posItem;
	POSITION  posAcc;

	CString	  sProductName;
	CString	  sProductCode;	
	CString	  sRelType;		
	CString	  sCode;			
	CString	  szMsg;			
	CString	  sItemID;		
	CString	  szMark;		
	CString	  szItemLabel;	
	CString	  szStatusMsg;	
	LPCTSTR	  lpszText		= _T("");

	CItem*			pItem=NULL;
	CImportD3Beam*	pD3Beam;
	CBeamElement*	pBeam;

	CImportD3Acc*		pD3Acc;
	CAccessoryElement*	pAcc;
	bool				bIgnore;

	int		nType=0, iOffset;
	int		nItemID=0;
	int		nTag;
	LPCTSTR	lpszTestMark = _T("");
	
	// get start of the beam list (should have been sorted by name before this call)
	posBeam = this->m_tplBeamList.GetHeadPosition();

	// get start of the accessory list (should have been sorted by name before this call)
	posAcc = this->m_tplAccessoryList.GetTailPosition();
	 
	// get the start of the document's item list
	posItem = this->m_pDoc->m_tplItemList.GetHeadPosition();

	while(posBeam)
	{
		// get pointer to each imported beam in turn
		pD3Beam = this->m_tplBeamList.GetNext(posBeam);

		// now check to see if beams of this sort already exist
		if (this->FindListedItem(pD3Beam, bIgnore))
		{
			// item already exists - get it's ID
			nItemID = m_pItem->GetItemID();
			sItemID.Format("%d",nItemID);
			szItemLabel = "Item ";
			szItemLabel += sItemID;

			// now check to see if this mark number is duplicated
			if (this->FindListedBeam(pD3Beam))
			{
				// this element already exists - so prompt user for action
				szMark = (CString)pD3Beam->GetMark();
				szMsg = szItemLabel;
				szMsg += ": Mark ";
				szMsg += szMark;
				szMsg += " already exists.";
				szMsg += "\n\nOverwrite existing data?";

				if (AfxMessageBox(szMsg,MB_ICONQUESTION + MB_YESNO) != IDNO)
				{
					// User chose to overwrite the data -
					// delete the element and insert the new one
					m_pItem->DeleteBeam(m_pBeam);
					pBeam = this->AddBeamElement(pD3Beam);
					m_pItem->CreateOrderedBeamList(pBeam);
					m_pItem->ResetBeamCounter();
				}
			}
			else
			{
				// element does not exist - update message bar
				szMark = (CString)pD3Beam->GetMark();
				szStatusMsg = "Creating "+ szItemLabel;
				szStatusMsg += ": Mark ";
				szStatusMsg += szMark;
				lpszText = (LPCTSTR)szStatusMsg;
				this->UpdateStatusBar(lpszText);

				// now add it to the element list
				pBeam = this->AddBeamElement(pD3Beam) ;
				m_pItem->CreateOrderedBeamList(pBeam);
				m_pItem->ResetBeamCounter();
			}
		}
		else
		{
			// no similar item - so create a new one
			// get item data

			// Is this item in the ignore list
			if(!bIgnore)
			{
				//	Make sure the item list is not empty ...
				if (!this->m_pDoc->m_tplItemList.IsEmpty())
				{
					// Now get the last item ID ...
					pItem = this->m_pDoc->m_tplItemList.GetTail();
					ASSERT_VALID(pItem);
					nItemID = pItem->GetItemID();
				}

				// and increment item ID for this new item
				++nItemID;

				// Send message to Status Bar
				sItemID.Format("%d",nItemID);
				szItemLabel = "Item ";
				szItemLabel += sItemID;
				szMark = (CString)pD3Beam->GetMark();
				szStatusMsg = "Creating "+ szItemLabel;
				szStatusMsg += ": Mark ";
				szStatusMsg += szMark;
				lpszText = (LPCTSTR)szStatusMsg;
				this->UpdateStatusBar(lpszText);

				// Create new CItem object and add it to the item list
				m_pItem = this->m_pDoc->CreateItem(nItemID);
				// NB: function call creates the CItem object and adds it to Item list as well

				//  Check that the item is a 'beam' not an 'accessory'
				bool bIsBeam = false;
				switch (pD3Beam->GetMemberType())
				{
				case PURLIN:
					bIsBeam = true;
					break;
				case RAIL:
					bIsBeam = true;
					break;
				case PRESSED:
					bIsBeam = true;
					break;
				case STOCK:
					bIsBeam = true;
					break;
				case STUD:
					bIsBeam = true;
					break;
				default:
					bIsBeam = false;
					break;
				}

				// and populate the item data ....
				this->m_pItem->SetItemID(nItemID);
				this->m_pItem->SetBeam(bIsBeam);
				this->m_pItem->SetType(pD3Beam->GetMemberType());
				this->m_pItem->SetProductCode(this->m_sProductCode);
				this->m_pItem->SetProductName(this->m_sProductName);
				this->m_pItem->SetProfile(this->m_sProfile);
				this->m_pItem->SetSectionID(this->m_sSectionID);
				this->m_pItem->SetProductWeight(this->m_nWeight);

				//	special data items required for TP Custom items
					/*
					gauge, depth
					top flange,    top flange slope,    top lip,
					bottom flange, bottom flange slope, bottom lip,
					dim c, dim f.
					*/
				int nDepth = pD3Beam->GetDimC() + pD3Beam->GetDimE() + pD3Beam->GetDimF();

				this->m_pItem->SetGauge(pD3Beam->GetGauge());
				this->m_pItem->SetDepth(nDepth);
				this->m_pItem->SetTopFlange(pD3Beam->GetDimA());
				this->m_pItem->SetTopFlangeSlope(pD3Beam->GetSlope());
				this->m_pItem->SetTopFlangeLip(pD3Beam->GetTopLip());
				this->m_pItem->SetBottomFlange(pD3Beam->GetDimB());
				this->m_pItem->SetBottomFlangeSlope(pD3Beam->GetTPBSlope());
				this->m_pItem->SetBottomFlangeLip(pD3Beam->GetBottomLip());
				this->m_pItem->SetDimC(pD3Beam->GetDimC());
				this->m_pItem->SetDimF(pD3Beam->GetDimF());

				// .. and add the beam to the Element List
				pBeam = this->AddBeamElement(pD3Beam);
				this->m_pItem->CreateOrderedBeamList(pBeam);
				this->m_pItem->ResetBeamCounter();
			}
		}
	}	
	//	All imported beams have now been assigned to Items
	//  clear Status Bar message
	szStatusMsg = _T("");
	lpszText = (LPCTSTR)szStatusMsg;
	this->UpdateStatusBar(lpszText);


	// Reset item ID for accessories
	nItemID=0;

	// Accessories
	while(posAcc)
	{
		// get pointer to each accessory in turn
		pD3Acc = this->m_tplAccessoryList.GetPrev(posAcc);

		// Does the accessory item exist
		if( !(pItem=testAccessory(pD3Acc->GetProductName())) )
		{
			nTag = 1;
			// Get item data	
			sProductName = (CString)pD3Acc->GetProductName();
			nType = 0;
			sProductCode = this->FindProductCode(sProductName, nType);

			// Is the accessory in the database ?
			if(sProductCode.GetLength())
			{
				//	Just in case there are not any existing items yet ...
				if (!this->m_pDoc->m_tplAccItemList.IsEmpty())
				{
					// Get the last item ID and increment it
					pItem = this->m_pDoc->m_tplAccItemList.GetTail();
					nItemID = pItem->GetItemID();
				}
				// Move to the next ID
				nItemID++;


				// Create new accessory item object
				pItem = this->m_pDoc->CreateItem(nItemID, 0);

				// Populate the item data
				pItem->SetItemID(nItemID);
				pItem->SetProductName(sProductName);
				nType = 0;
				pItem->SetType(nType);
				pItem->SetProdLine(D_BRACE);
				pItem->SetProdLineLabel(_T("Diagonal_Brace"));
				pItem->SetProductCode(this->FindProductCode(sProductName, nType));
				
				// Set to accessory item
				pItem->SetBeam(false);
				pItem->SetProductWeight(m_nWeight);
				pItem->SetGauge(m_nGauge);
				
				// now add this accessory to the item's element list 
				nTag += (nItemID * 1000);
				pAcc = this->AddAccessoryElement(pD3Acc, nTag);
				pItem->m_tplElementList.AddTail(pAcc);
			}
		}
		else
		{
			iOffset = 1;
			// Test if the mark already exisits in the item
			if(pItem->getAccessory(pD3Acc->GetMark()))
			{
				// Format the mark name
				szMark.Format("%s_%i", pD3Acc->GetMark(), iOffset++);

				// Change the mark number to be unique
				while(pItem->getAccessory(szMark))
				{
					// Format the mark name
					szMark.Format("%s_%i", pD3Acc->GetMark(), iOffset++);
				}

				// Set new mark name
				pD3Acc->SetMark(szMark.GetBuffer(szMark.GetLength()));
			}
			
			// Increment the element ID number
			nTag ++;
			// Create the accessory element
			pAcc = this->AddAccessoryElement(pD3Acc, nTag);
			// Add the new accessory to the item list
			pItem->m_tplElementList.AddTail(pAcc);
		}

		if(pItem)
		{
			// Sort into lengths
			pItem->SortElementsByLength();
		}
	}

	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetSBEName()		A function to convert the default Product Name string into the SBE name string
//
CString CImportDet3::GetSBEName(CString& sProductName)
{
	CString sTempName = (CString)this->GetReleaseType();

	if(sTempName != _T("SBE") && sTempName != _T("AYRDT_SBE"))
	{}
	else
	{
		sTempName = _T("SBE");

		if(sProductName.Left(2) == _T("1/"))
		{
			sTempName += " ZETA " + sProductName;
		}
		else if (sProductName.Left(2) == _T("2/"))
		{
			sTempName += " ZETA II " + sProductName;
		}
		else  if (sProductName.Left(1) == _T("Z") || sProductName.Left(1) == _T("C"))
		{
			sTempName += sProductName;
		}
//  EXTRA CODE REQUIRED FORE NEW PRESSED SECTONS ??
		else
		{
			sTempName += sProductName;
		}
		
		sProductName = sTempName;
		
	}
	return sProductName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AddBeamElement()		A function to convert an CImportedD3Beam to a CBeamElement and return a pointer to the element
//
CBeamElement* CImportDet3::AddBeamElement(CImportD3Beam* pD3Beam)
{
	CString sProduct	= pD3Beam->GetProductName();
	CString sSection	= _T("");

	// set common element data
	CBeamElement* pBeam = new CBeamElement;
	pBeam->m_pItem = this->m_pItem;
	pBeam->SetMark((CString)pD3Beam->GetMark());
	pBeam->SetQty(pD3Beam->GetQty());
	
	// set bundle count to maximum for given section size
	pBeam->SetBundle(this->GetMaxBundleCount());

	CString szCommentText = _T("");
	szCommentText = pD3Beam->GetComment();
	pBeam->SetComment(szCommentText);

	if (sProduct.Left(2) == "EB")
	{
		pBeam->SetEBSlope(pD3Beam->GetSlope());
	}
	else
	{
		pBeam->SetEBSlope(0);
	}

	// Test member types for stud and pressed
	if(pD3Beam->GetMemberType() == Stud || pD3Beam->GetMemberType() == Pressed ||
		pD3Beam->GetMemberType() == Floor_Joist)
	{
		pBeam->SetMemberType(Purlin);
	}
	else
	{
		pBeam->SetMemberType(pD3Beam->GetMemberType());
	}

	pBeam->SetLength(pD3Beam->GetLength());
	pBeam->SetOHang1(pD3Beam->GetOverhang1());
	pBeam->SetOHang2(pD3Beam->GetOverhang2());
	pBeam->SetSPCode(pD3Beam->GetSPC());
	pBeam->SetSpan1(pD3Beam->GetSpan1());
	pBeam->SetSpan2(pD3Beam->GetSpan2());
	pBeam->SetSpan3(pD3Beam->GetSpan3());	
	pBeam->SetCol1(pD3Beam->GetColumn1());
	pBeam->SetCol2(pD3Beam->GetColumn2());
	
	// add non-standard holes
	pD3Beam->AddExtraHolesToList(pBeam);

	return pBeam;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AddAccessoryElement()		A function to convert an CImportD3Acc to a CAccessoryElement and return a pointer to the element
//
CAccessoryElement* CImportDet3::AddAccessoryElement(CImportD3Acc* pD3Acc, int nTag)
{
	CString sProduct	= pD3Acc->GetType();
	CString szCommentText = pD3Acc->GetComment();
	CString sSection;
	CString sGauge;

//	this->SplitProductID(sProduct, sSection, sGauge);

	// set common element data
	CAccessoryElement* pAcc = new CAccessoryElement;

	pAcc->SetElementID(nTag);
//	pAcc->SetSection(sSection);
//	pAcc->SetGauge(sGauge);
	pAcc->SetMark((CString)pD3Acc->GetMark());
	pAcc->SetQty(pD3Acc->GetQty());
	pAcc->SetBundle(0);	// VHF TODO: need input from user after item# allocated

	// Set the comments
	pAcc->SetComment(szCommentText);

	//Fields
	pAcc->SetField1(pD3Acc->GetField1());
	pAcc->SetField2(pD3Acc->GetField2());
	pAcc->SetField3(pD3Acc->GetField3());
	pAcc->SetField4(pD3Acc->GetField4());
	pAcc->SetField5(pD3Acc->GetField5());
	
	// Set to accessory
	pAcc->SetType(0);
	// Set the sleevelength
	pAcc->SetLength(pD3Acc->GetSleeveLength());

	// add non-standard holes
//	pD3Acc->AddExtraHolesToList(pAcc);

	return pAcc;
}

//////////////////////////////////////////////////////////////////////////////////////
//
void CImportDet3::SplitProductID(LPCTSTR sProduct, CString& sSection, CString& sGauge)
{
		CString sTemp	= ((CString)sProduct).Right(2);
		sGauge			= sTemp.Left(1) + "." + sTemp.Right(1);
		sSection		= ((CString)sProduct).Left(5);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Sort~~ByAscendingMark()	Bubble sort...
//
//-----------------------------------------------------------------------------------------
//	SortBeamByAscendingMark()
//
void CImportDet3::SortBeamByAscendingMark()
	{
	POSITION ResultsPosition;
	CImportD3Beam* pRecord1;
	CImportD3Beam* pRecord2;
	bool bModified = false;
	char szProductName1[80];
	char szProductName2[80];

  start:
	bModified = false;

  //get results head for sort
  	ResultsPosition =this->m_tplBeamList.GetHeadPosition();
  	if(!ResultsPosition)
  		return;

  //bubble sort 	
  	do
	{
	  //get record1	
		pRecord1 =(CImportD3Beam*)this->m_tplBeamList.GetNext(ResultsPosition);
		if(!ResultsPosition)
			break;
				
	  //get record2	
		pRecord2 =(CImportD3Beam*)this->m_tplBeamList.GetNext(ResultsPosition);
			
	  //do comparison
		lstrcpy((LPSTR)szProductName1, pRecord1->GetMark());
		lstrcpy((LPSTR)szProductName2, pRecord2->GetMark());
		if( lstrcmp((LPSTR)szProductName1, (LPSTR)szProductName2) > 0)
		{
	  	  //do swap	
	  	  	this->BeamSwap( pRecord1, pRecord2 );
	  		bModified=TRUE;
		}

  		ResultsPosition = this->m_tplBeamList.Find(pRecord2);
	  	  	
  	  	}while(ResultsPosition);
		
	if( bModified != false )
		goto start;
}

//-----------------------------------------------------------------------------------------
//	SortAccByAscendingMark()
//
void CImportDet3::SortAccByAscendingMark()
{
	POSITION ResultsPosition;
	CImportD3Acc* pRecord1;
	CImportD3Acc* pRecord2;
	bool bModified = false;
	char szProductName1[80];
	char szProductName2[80];

  start:
	bModified = false;

  //get results head for sort
  	ResultsPosition =this->m_tplAccessoryList.GetHeadPosition();
  	if(!ResultsPosition)
  		return;

  //bubble sort 	
  	do
	{
	  //get record1	
		pRecord1 =(CImportD3Acc*)this->m_tplAccessoryList.GetNext(ResultsPosition);
		if(!ResultsPosition)
			break;
				
	  //get record2	
		pRecord2 =(CImportD3Acc*)this->m_tplAccessoryList.GetNext(ResultsPosition);
			
	  //do comparison
		lstrcpy((LPSTR)szProductName1, pRecord1->GetMark());
		lstrcpy((LPSTR)szProductName2, pRecord2->GetMark());
		if(lstrcmp((LPSTR)szProductName1, (LPSTR)szProductName2) > 0)
  		{
	  	  //do swap	
	  	  	this->AccSwap( pRecord1, pRecord2 );
	  		bModified = true;
  		}

  		ResultsPosition = this->m_tplAccessoryList.Find(pRecord2);
	  	  	
  	  	}while( ResultsPosition );
		
	if(bModified != false)
		goto start;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	~~Swap()		Swap record positions in beam/accessory lists
//
//-----------------------------------------------------------------------------------------
//	BeamSwap()
//
void CImportDet3::BeamSwap(CImportD3Beam* pBeam1, CImportD3Beam* pBeam2)
{
	POSITION ResultsPosition1;
	POSITION ResultsPosition2;

  //remove
	ResultsPosition1 =this->m_tplBeamList.Find(pBeam1);
	this->m_tplBeamList.RemoveAt(ResultsPosition1);						  		

  //insert after	 
	ResultsPosition2 =this->m_tplBeamList.Find(pBeam2);
	this->m_tplBeamList.InsertAfter(ResultsPosition2, pBeam1);						  		
}
//-----------------------------------------------------------------------------------------
//	AccSwap()
//
void CImportDet3::AccSwap(CImportD3Acc* pAccessory1, CImportD3Acc* pAccessory2)
{
	POSITION ResultsPosition1;
	POSITION ResultsPosition2;

  //remove
	ResultsPosition1 =this->m_tplAccessoryList.Find(pAccessory1);
	this->m_tplAccessoryList.RemoveAt(ResultsPosition1);						  		

  //insert after	 
	ResultsPosition2 =this->m_tplAccessoryList.Find(pAccessory2);
	this->m_tplAccessoryList.InsertAfter(ResultsPosition2, pAccessory1);
}

/*
//----------------------------------------------------------------------------
BOOL CBeamList::DeleteRecord( CBeam* pBeam )
	{
	POSITION p =this->Find( pBeam );
	if( p )
		{
		this->RemoveAt( p );
		delete pBeam;
		return TRUE;
		}
    
    return FALSE;
    }
*/

//---------------------------------------------------------------------------
//	Procedure:	Copy()		Copy this object marked as specified into target.
/*
	Design:
	
	find beam by itemmark
	if beam found
		then copy beam attributes into target
		return success
	                  
	return failure	                  
*/
/*---------------------------------------------------------------------------
BOOL CBeamList::Copy( CBeam* pTarget, LPCSTR lpszTestMark )
	{
  //find beam by itemmark
  	CBeam* pRecord =this->FindRecord( lpszTestMark );
  	
  //if beam found
  	if( pRecord!=NULL )
  		{
	  //then copy beam attributes into target
	  	pRecord->Copy( pTarget );
	  	
	  //return success
	  	return TRUE;
	  	}
	                  
  //return failure	                  
  	return FALSE;
	}	
*/


	
//----------------------------------------------------------------------------
//	Procedure:	IsTail()	Test for lst beam
/*
	Design:
*/


//----------------------------------------------------------------------------
//	Procedure:	Write()	Write beam list to target.
/*
	Design:
*/
/*
//----------------------------------------------------------------------------
BOOL CBeamList::Write( CBigIni& ABigIni )
	{
	POSITION p =this->GetHeadPosition();
	int iIndex = 0;
	while( p )
		{
		CBeam* pBeam = (CBeam*)this->GetNext( p );
		pBeam->Write( ABigIni, iIndex );
		++iIndex;
		}

	return TRUE;
	}
*/
//----------------------------------------------------------------------------
//	Procedure:	SortByAssendingProductName()
/*	Design:
*/

//----------------------------------------------------------------------------
//	Procedure:	SortByAssendingMark()
/*	Design:
	Bubble sort...
*/

//----------------------------------------------------------------------------
//	Procedure:	Swap()
/*	Design:
*/
//////////////////////////////////////////////////////////////////////////
//	FindProductCode()
//
CString CImportDet3::FindProductCode(LPCTSTR sProductName, int nMemberType)
{
	// Create "SelectProductByNameType" recordset from database
	CDaoDatabase* pDB = this->m_pDoc->m_pProjectSettings->m_pDB;
	CDaoProductCode* m_pSelectProductCodeSet = new CDaoProductCode(pDB);	
	CString sProductCode;
	
	// Convert nMemberType to three character CString
	CString sType;
	CString sTemp;
	CString sSearchName;

	if (nMemberType <= 9)
	{
		sType = _T("00");
		sTemp.Format("%d",nMemberType);
		sType += sTemp;
	}
	else if (nMemberType <= 99 && nMemberType > 9)
	{
		sType = _T("0");
		sTemp.Format("%d",nMemberType);
		sType += sTemp;
	}

	// Exception code for some Associated Sections
	sTemp = sProductName;
	if (sTemp == _T("TP Custom"))
	{
		sSearchName = sTemp.Left(2);
	}
	else if(!sTemp.Mid(0, 3).CompareNoCase(_T("SB2")) ||
			!sTemp.Mid(0, 3).CompareNoCase(_T("SB3")))
	{
		// Type Swagebeam
		sType = _T("007");

		// Set search database name
		sSearchName = sProductName;
	}
/*	else if (sTemp.Left(3) == _T("TPN") || sTemp.Left(3) == _T("TPP"))
	{
		if (sTemp.Left(5) == _T("TPN15") || sTemp.Left(5) == _T("TPP15"))
		{
			sSearchName = sProductName;
		}
		else
		{
			sSearchName = sTemp.Left(6);
		}
//		sType = _T("008")
	} */
	else
	{
			sSearchName = sProductName;
	}

	// Set parameters to filter recordset
	m_pSelectProductCodeSet->m_Type_Ident = sType;
	m_pSelectProductCodeSet->m_Product_Name_Ident = sSearchName;
	
	// Open recordset
	m_pSelectProductCodeSet->Open();

	// Get recordset data
//	while (!m_pSelectProductCodeSet->IsEOF())
//	{
		m_sProductCode = m_pSelectProductCodeSet->m_ProductCode;
		m_sProductName = m_pSelectProductCodeSet->m_Aviion_Desc;
		m_sProfile = m_pSelectProductCodeSet->m_ProductName;
		m_sSectionID = m_pSelectProductCodeSet->m_Section_ID;
		m_nGauge = m_pSelectProductCodeSet->m_Gauge;
		m_nWeight = m_pSelectProductCodeSet->m_Weight;

//		m_pSelectProductCodeSet->MoveNext();
//	}
	
	// Close recordset and release memory
	m_pSelectProductCodeSet->Close();	
	delete(m_pSelectProductCodeSet);	
	
	return m_sProductCode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetProjectHeader()		Call the new  project header dialog and populate it with data captured from D3 file
//							Give the user opportunity to update empty fields as required.
//
void CImportDet3::SetProjectHeader()
{
	// Call the project header dialog ...
	CDlgNewProject StartDlg;

	StartDlg.m_editProjectName = modifyImportName(this->m_fileName);
	StartDlg.m_editCustomerName = this->m_szOwner;
	StartDlg.m_editCustomerRef = this->m_szProject;
	StartDlg.m_editJobDestination = this->m_szDestination;
	StartDlg.m_editDueDate = this->m_szDeliveryDate;
	StartDlg.m_editComments = this->m_szComments + "\r\n" + this->m_szPackingSpec;

	if(StartDlg.DoModal() == IDOK)
	{	
		COD3App* pApp = (COD3App*)AfxGetApp();
		this->m_pDoc->m_pProjectHeader->m_sAppVersion = pApp->m_sAppVer;
	
		// Assign the data captured from input.
		this->m_pDoc->m_pProjectHeader->m_nProjectType		= StartDlg.m_radioProjectType;
		this->m_pDoc->m_pProjectHeader->m_sProjectName		= StartDlg.m_editProjectName;
		this->m_pDoc->m_pProjectHeader->m_sCustomerName		= StartDlg.m_editCustomerName;
		this->m_pDoc->m_pProjectHeader->m_sCustomerRef		= StartDlg.m_editCustomerRef;	
		this->m_pDoc->m_pProjectHeader->m_sJobDestination	= StartDlg.m_editJobDestination;
		this->m_pDoc->m_pProjectHeader->m_sComments			= StartDlg.m_editComments;	


		// VHF TODO: Sort out CString to CTime data type for due date.
		this->m_pDoc->m_pProjectHeader->m_sDueDate		= StartDlg.m_editDueDate;
		
	}
	else
	{
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//	GetMaxBundleCount()		function to return the maximum number of parts in a bundle based
//							on the section size.
//
int CImportDet3::GetMaxBundleCount()
{
	int nMaxCount;
	CString szSection = this->m_pItem->GetSectionID();
	if (szSection.Left(3) == _T("SBE"))
	{
		szSection = szSection.Right(szSection.GetLength()-3);
	}
	if (szSection.Left(2) == _T("JR"))
	{
		szSection = szSection.Right(szSection.GetLength()-2);
	}

	if (szSection == _T("1/150")){nMaxCount = 30;}
	else if (szSection == _T("1/175")){nMaxCount = 28;}
	else if (szSection == _T("1/200")){nMaxCount = 26;}
	else if (szSection == _T("1/125")){nMaxCount = 30;}
	else if (szSection == _T("Z/240")){nMaxCount = 28;}
	else if (szSection == _T("Z/300")){nMaxCount = 14;}
	else if (szSection.Left(2) == _T("2/")){nMaxCount = 28;}
	else if (szSection.Left(2) == _T("3/")){nMaxCount = 40;}
	else if (szSection == _T("Z/125") ||
			 szSection == _T("Z/140") ||
			 szSection == _T("Z/155")){nMaxCount = 50;}
	else if (szSection == _T("Z/170") ||
			 szSection == _T("Z/185") ||
			 szSection == _T("Z/200")){nMaxCount = 40;}
	else if (szSection == _T("EB160")) {nMaxCount = 18;}
	else if (szSection == _T("EB240")){nMaxCount = 12;}
	else {nMaxCount = 20;}


	return nMaxCount;
}

///////////////////////////////////////////////////////////////////////
void CImportDet3::UpdateStatusBar(LPCTSTR lpszText)
{
	CWinApp*	pApp	= AfxGetApp();
	CMainFrame* pAppWnd	= (CMainFrame*)pApp->m_pMainWnd;

	pAppWnd->StatusBarMsgUpdate(lpszText);
}

CString CImportDet3::modifyImportName(CString name)
{
	CString newName, lastChar;
	int		pos;

	// Find extention pos
	pos = name.ReverseFind('.');
	newName = name.Left(name.GetLength()-(name.GetLength()-pos));

	// Get the last character from the string
	lastChar=newName.GetAt(newName.GetLength()-1);

	// Is it a char or a number
	if(!atoi(lastChar))
	{
		// Remove the character
		newName.SetAt(newName.GetLength()-1, '\0');
	}

	// Add a 'P' to the front of the string
	newName.Insert(0, "P");
	

	return(newName);
}

bool CImportDet3::WriteD3Header(CBigIni& ABigIni)
{
	CString szSection	= "Document";
	CString szEntry		= _T("");


	// Wrtie D3 file document header
	szEntry	= "File"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szFile);

	szEntry	= "ReleaseType"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szReleaseType );

	szEntry	= "Project"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szProject );

	szEntry	= "Owner"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szOwner );
	//SimpleFindAndReplace((LPSTR)(const char*)this->m_szOwner, "~~", "\r\n" );

	szEntry	= "Comment"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szComments );

	szEntry	= "DeliverTo"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szDestination );
	//SimpleFindAndReplace((LPSTR)(const char*)this->m_szDestination, "~~", "\r\n" );

	szEntry	= "DeliveryDate"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szDeliveryDate );
	
	szEntry	= "PackingRequirements"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szPackingSpec );
	//SimpleFindAndReplace((LPSTR)(const char*)this->m_szPackingSpec, "~~", "\r\n" );

	szEntry	= "Version"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szVersion );

	szEntry	= "BuildOrigin"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szbOrigin );

	szEntry	= "Client"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szClient );

	szEntry	= "DrawnBy"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szDrawnBy );

	szEntry	= "Detailer"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szDetailer );

	szEntry	= "JobNo"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szJobNO );

	szEntry	= "Part"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szPart );

	szEntry	= "Reference"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szRef );

	szEntry	= "ModifiedDate"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szModifiedDate );

	szEntry	= "CheckedBy"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szCheckedBy );

	szEntry	= "CheckedDate"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szCheckedDate );

	szEntry	= "ApprovedBy"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szApprovedBy );

	szEntry	= "ApprovedDate"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szApprovedDate );

	szEntry	= "RevisedBy"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szRevisedBy );

	szEntry	= "GeneralDrawingComment"; 
	ABigIni.WritePrivateProfileString( szSection, szEntry, m_szDrawingComment );



	return(true);
}

CItem* CImportDet3::testAccessory(CString sName)
{
	CItem		*pItem=NULL;
	POSITION	pos;
	bool		bFound=false;

	// Get the head position for the accessory items
	pos = m_pDoc->m_tplAccItemList.GetHeadPosition();

	while(pos)
	{
		// Get the next item object
		pItem = m_pDoc->m_tplAccItemList.GetNext(pos);
	
		// Test for a matching product name
		if(pItem->GetProductName() == sName)
		{
			// Set flag and exit loop
			bFound = true;
			break;
		}
	}
	
	// Find anything
	if(bFound)
		return(pItem);
	else
		return(NULL);
}

bool CImportDet3::ignoreItem(CString sProductName)
{
	CDaoGetIgnore	*product = new CDaoGetIgnore(m_pDoc->m_pProjectSettings->m_pDB);
	bool			bResult=false;

	// Set search criteria
	product->m_Sel_Name = sProductName;

	// Open the record set
	product->Open();

	if(product->GetRecordCount())
	{
		// Set return flag
		bResult = true;
	}

	// Close the record set
	product->Close();

	// Free object
	delete product;


	return(bResult);
}

CString CImportDet3::findEavesBeam(CString sName, int iAngle)
{
	
	CString	sResult;


	if(iAngle >= 0 && iAngle <= 5)
		iAngle = 5;
	else if(iAngle > 5 && iAngle <= 10)
		iAngle = 10;
	else
		iAngle = 15;

	try
	{
		CDaoEavesBySlope	eaves(m_pDoc->m_pProjectSettings->m_pDB);
		CProductData		eavesData(m_pDoc->m_pProjectSettings->m_pDB);

		// Set search criteria
		eaves.m_iAngle = iAngle;
		eaves.m_Prod_name = sName;

		// Open the recordset
		eaves.Open();

		if(eaves.GetRecordCount())
		{
			// Set product result
			sResult = eaves.m_ProductCode;
		}

		// Close recordset
		eaves.Close();


		// Set search criteria
		eavesData.m_Product_Ident = sResult;

		// Open recordset
		eavesData.Open();

		if(eavesData.GetRecordCount() > 0)
		{
			// Set class members
			sResult = m_sProductCode=eavesData.m_ProductCode;
			m_sProductName = eavesData.m_Aviion_Desc;
			m_sProfile = eavesData.m_ProductName;
			m_sSectionID = eavesData.m_Section_ID;
			m_nGauge = eavesData.m_Gauge;
			m_nWeight = eavesData.m_Weight;
		}

		// Close recordset
		eavesData.Close();
	}
	catch(CDaoException *e)
	{
		// Report error
		e->ReportError(MB_OK);
		// Delete exception
		e->Delete();
	}


	return(sResult);
}
