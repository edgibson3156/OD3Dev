// SysTemplate.cpp: implementation of the CSysTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "SysTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CSysTemplate, CObject, 8)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysTemplate::CSysTemplate()
{

}

CSysTemplate::~CSysTemplate()
{
	CAssociation* pAssociation;
	COutputList*  pOutputList;
	POSITION pos;
	
	if (!m_tplAssociationList.IsEmpty())									//	Associations already in list, so ...
	{	
		for (pos = m_tplAssociationList.GetHeadPosition(); pos != NULL;)	// ... loop through list ... 
		{
			pAssociation = m_tplAssociationList.GetNext(pos);			// ... get a pointer to the object ...
			delete pAssociation;								// ... delete the object ...
		}
		m_tplAssociationList.RemoveAll();								// ... and destroy the list
	}

	if (!m_tplOutputList.IsEmpty())									//	Associations already in list, so ...
	{															// ... check for duplicates ...
		for (pos = m_tplOutputList.GetHeadPosition(); pos != NULL;)	// ... loop through list ... 
		{
			pOutputList = m_tplOutputList.GetNext(pos);
			delete pOutputList;
		}														// Loop has finished without finding a match ...
		m_tplOutputList.RemoveAll();								// ... and destroy the list
	}															// ... or list is empty ...
}

//////////////////////////////////////////////////////////////////////
void CSysTemplate::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_sDataSource;
		ar << m_sDBaseVersion;
		ar << m_sProjectInputPath;
		ar << m_sAutoFileInputPath;
		ar << m_nProcessAll;
		ar << m_nProcessAuto;
		ar << m_sReportAutomatic;
		ar << m_sReportNonAuto;
	}
	else
	{
		ar >> m_sDataSource;
		ar >> m_sDBaseVersion;
		ar >> m_sProjectInputPath;
		ar >> m_sAutoFileInputPath;
		ar >> m_nProcessAll;
		ar >> m_nProcessAuto;
		ar >> m_sReportAutomatic;
		ar >> m_sReportNonAuto;
	}
	m_tplAssociationList.Serialize(ar);
	m_tplOutputList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// OPEN CONFIGURATION SETTINGS TEMPLATE
void CSysTemplate::LoadTemplate()
{
	CWinApp* pApp;
	CWnd*	 pAppWnd;
	CString	 sFile;

	DWORD	flags = 
			OFN_FILEMUSTEXIST|
			OFN_HIDEREADONLY|
			OFN_PATHMUSTEXIST;

	pApp = AfxGetApp();
	pAppWnd = pApp->m_pMainWnd;

	CFileDialog dlgOpen(TRUE,
						"TXT",
						NULL,
						flags,
						"Microsoft Notepad (*.TXT)|*.TXT||",
						pAppWnd);

	if (dlgOpen.DoModal() == IDOK)
	{
		sFile = dlgOpen.GetPathName();

		CFile* pFile = new CFile();
		CFileException e;
		pFile->Open (sFile,
					 true,
					 NULL);	
		if( !pFile->Open(sFile,
						 CFile::modeCreate |
						 CFile::modeNoTruncate |
						 CFile::shareDenyRead |
						 CFile::modeRead, &e ) )
		{
			#ifdef _DEBUG
			   afxDump << "File could not be opened " << e.m_cause << "\n";
			#endif
		}
/*
		CArchive* &ar;
		ar.IsLoading();
		this->Serialize(CArchive &ar);	
*/
		pFile->Close();
		delete pFile;
/*
//comment for CFile::Close
// If you used new to allocate the CFile object on the heap,
// then you must delete it after closing the file.
// Close sets m_hFile to CFile::hFileNull.

//example for CFile::CFile
char* pFileName = "test.dat";
TRY
{
   CFile f( pFileName, CFile::modeCreate | CFile::modeWrite );
}
CATCH( CFileException, e )
{
   #ifdef _DEBUG
      afxDump << "File could not be opened " << e->m_cause << "\n";
   #endif
}
END_CATCH

//example for CFile::Open
CFile f;
CFileException e;
char* pFileName = "test.dat";
if( !f.Open( pFileName, CFile::modeCreate | CFile::modeWrite, &e ) )
   {
#ifdef _DEBUG
   afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
   }

//example for CFile::Read
extern CFile cfile;
char pbuf[100];
UINT nBytesRead = cfile.Read( pbuf, 100 );

*/
	}
}
