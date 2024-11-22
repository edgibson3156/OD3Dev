// SysConfig.cpp: implementation of the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "SysConfig.h"
#include "AssociationPage.h"
#include "InputPage.h"
#include "ManualInputPage.h"
#include "OutputPage.h"
#include "ProcessingPage.h"
#include "ReportsPage.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CSysConfig, CObject, 8)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Construction
CSysConfig::CSysConfig()
{
	m_ODDB_Open = false;
	m_pDB = NULL;
}


// Destruction
CSysConfig::~CSysConfig()
{
	CAssociation* pAssociation;
	COutputList*  pOutputList;
	CReports*	  pReportList;
	POSITION pos;
	
	if (!m_tplAssociationList.IsEmpty())									//	There are associations already in list,
	{																		//	 so ...
		for (pos = m_tplAssociationList.GetHeadPosition(); pos != NULL;)	// ... loop through list ... 
		{
			pAssociation = m_tplAssociationList.GetNext(pos);				// ... get a pointer to the object ...
			delete pAssociation;											// ... delete the object ...
		}
		m_tplAssociationList.RemoveAll();									// ... and destroy the list
	}

	if (!m_tplOutputList.IsEmpty())									//	There are associations already in list,
	{																//   so ...
		for (pos = m_tplOutputList.GetHeadPosition(); pos != NULL;)	// ... loop through list ... 
		{
			pOutputList = m_tplOutputList.GetNext(pos);				// ... get a pointer to the object ...
			delete pOutputList;										// ... delete the object ...
		}														
		m_tplOutputList.RemoveAll();									// ... and destroy the list
	}

	if (!m_tplReportList.IsEmpty())									//	There are associations already in list,
	{																//   so ...
		for (pos = m_tplReportList.GetHeadPosition(); pos != NULL;)	// ... loop through list ... 
		{
			pReportList = m_tplReportList.GetNext(pos);				// ... get a pointer to the object ...
			delete pReportList;										// ... delete the object ...
		}
		m_tplReportList.RemoveAll();									// ... and destroy the list
	}	

	if (m_pDB && m_pDB->m_pWorkspace)
	{
		delete m_pDB;	//	destroy to pointer to the database
	}										
}

//////////////////////////////////////////////////////////////////////
void CSysConfig::Serialize(CArchive &ar)
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
		ar >> m_sReportNonAuto;
	}
	m_tplAssociationList.Serialize(ar);
	m_tplOutputList.Serialize(ar);
	m_tplReportList.Serialize(ar);
}

////////////////////////////////////////////////////////////////////////////////////
// AutoDbConnect()	establish a connection with the database based on the info 
//					contained in the project settings imported with File|Open.
//
void CSysConfig::AutoDbConnect() 
{	
	//First check DB not open already ...
	CMainFrame	*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	int			result=0;

	if (m_ODDB_Open)
	{
		AfxMessageBox("Database is already open",
						MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		// Test if loading from selected user template file
		if(!pMainFrm->m_suppress)
		{
			result = AfxMessageBox("Connect to Database " + m_sDataSource,
							MB_YESNO|MB_ICONQUESTION);
		}
		else
			result = IDYES;


		if(result == IDYES)
		{
			m_pDB = new CDaoDatabase(NULL);
			
			try
			{
				m_pDB->Open( m_sDataSource, false, true, _T(""));

				m_ODDB_Open = true;

//				VHF TODO: This version check is rubbish
//				GetVersion() returns the version of the Jet DataBase engine
//				Not the version of the Access database itself!!
//				Is the check necessary ?
//				Will it trap different versions of Access? - YES but so what?

				if (m_pDB->GetVersion() != m_sDBaseVersion)
				{
					if(AfxMessageBox("This file was created using version "
										+ m_sDBaseVersion + " of the database"
										+ "\n"
										+ "\nYou are trying to connect to version "
										+ m_pDB->GetVersion()
										+ "\n"
										+ "\nYou may continue with this version"
										+ "or reconnect to a different one"
										+ "\n"
										+ "\nReconnect to a different database ?",
										MB_YESNO|MB_ICONWARNING) == IDYES)
					{
						OnDbDisconnect();
						OnDbConnect();
					}
					else
					{
						m_sDBaseVersion = m_pDB->GetVersion();
					}
				}

			}
			catch(CDaoException *e)
			{
				// Report error
				e->ReportError(MB_OK);
				// Delete exception
				e->Delete();
				// Attempt to re-connect to a database
				OnDbConnect();
			}
		}
		else
		{
			OnDbConnect();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
// OnDbConnect()	establish a connection with the database
void CSysConfig::OnDbConnect() 
{	
	CWinApp* pApp;
	CWnd* pAppWnd;

	//First check DB not open already ...
	if (m_ODDB_Open)
	{
		AfxMessageBox("Database is already open",
						MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		DWORD	flags = 
				OFN_FILEMUSTEXIST|
				OFN_HIDEREADONLY|
				OFN_PATHMUSTEXIST;

		pApp = AfxGetApp();
		pAppWnd = pApp->m_pMainWnd;

		CString		sDefaultDir;
		LPCTSTR		lpstrDefaultDir;

		sDefaultDir = "M:\\OD3";
		lpstrDefaultDir = sDefaultDir.GetBuffer(1);
	
		CFileDialog dlgOpen(TRUE,
							"MDB",
							NULL,
							flags,
							"Microsoft Access (*.MDB)|*.MDB||",
							pAppWnd);
	
		dlgOpen.m_ofn.lpstrInitialDir = lpstrDefaultDir;

		if (dlgOpen.DoModal() == IDOK)
		{
			AfxGetApp()->DoWaitCursor(1); 
			m_sDataSource = dlgOpen.GetPathName();
			m_pDB = new CDaoDatabase(NULL);

			try
			{
				m_pDB->Open(m_sDataSource, false, true, _T(""));

				m_ODDB_Open = true;
				m_sDBaseVersion = m_pDB->GetVersion();
			}
			catch(CDaoException *e)
			{
				// Report failure to user
				e->ReportError(MB_OK);
				// Handle exception and continue
				e->Delete();
			}
			AfxGetApp()->DoWaitCursor(-1); 
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
// OnDBDisconnect()		Disconnect from database
void CSysConfig::OnDbDisconnect() 
{
	if (!m_ODDB_Open)
	{	// This should never happen but just in case
		AfxMessageBox ("Database is already closed",
						MB_OK|MB_ICONINFORMATION);
		m_ODDB_Open = false;
	}
	else
	{	// Close database connection
		AfxMessageBox ("Closing Datasource " + m_sDataSource,
						MB_OK|MB_ICONINFORMATION);
		m_pDB->Close();
		// Set database status
		m_ODDB_Open = false;
	}
}


////////////////////////////////////////////////////////////////////////////////////
// OnOpenSysConfig()		Create property sheets (System Configuration)
void CSysConfig::OnOpenSysconfig() 
{
	// Declare Property sheet object
	CPropertySheet  SystemConfiguration(" System Configuration Options ", NULL, 0 );

	// Declare Page objects
	CAssociationPage	Association;
	CInputPage			InputFiles;
	CManualInputPage	ManualInput;
	COutputPage			OutputFiles;
	CProcessingPage		Processing;
	CReportsPage		Reports;

    // Display member data from the CSysConfig object

	// Set Individual Property for Page One
	Association.m_pDB = this->m_pDB;
	Association.m_pDoc = this->m_pDoc;

	// Set Individual Property for Page Two
	InputFiles.m_editProjectPath	= m_sProjectInputPath;
	InputFiles.m_editAutoInputPath	= m_sAutoFileInputPath;

	// Set Individual Propert for Page Three - Manual Input - NONE REQUIRED
	

	// Set Individual Property for Page Four
	OutputFiles.m_pDB = m_pDB;
	OutputFiles.m_pDoc = this->m_pDoc;

	// Set Individual Property for Page Five
	Processing.m_radioProcessAll = m_nProcessAll;
	Processing.m_radioProcessAuto = m_nProcessAuto;

	// Set Individual Property for Page Six
	Reports.m_pDB = this->m_pDB;
	Reports.m_pDoc = this->m_pDoc;
	Reports.m_editNonAutoLines	= m_sReportNonAuto;

	SystemConfiguration.AddPage(&Association);
	SystemConfiguration.AddPage(&InputFiles);
	SystemConfiguration.AddPage(&ManualInput);
	SystemConfiguration.AddPage(&OutputFiles);
	SystemConfiguration.AddPage(&Processing);
	SystemConfiguration.AddPage(&Reports);

	if (SystemConfiguration.DoModal() == IDOK) 
	{
		// Recover input from Individual Property Pages

		// Page One (Associations) - not required - see m_tplAssociationList	

		// Page Two (InputFiles)
		m_sProjectInputPath		= InputFiles.m_editProjectPath;
		m_sAutoFileInputPath	= InputFiles.m_editAutoInputPath;

		// Page Three - Manual Input - NOT REQUIRED

		// Page Four (OutputFiles) - not required - see m_tplOutputList

		// Page Five (Processing)
		m_nProcessAll	= Processing.m_radioProcessAll;
		m_nProcessAuto	= Processing.m_radioProcessAuto;

		// Page Six (Reports)
		//  see m_recordList for storage path for 'AutoLines'
		m_sReportNonAuto	= Reports.m_editNonAutoLines;
	}
}

/////////10////////20////////30////////40////////50////////60////////70////////80////////90////////100///////110///////120///////130
// AddAssociation() A function to add a new product and production line association to the list.
//
//				No duplicates allowed - once a product is assigned to
//				a production line it must not also be assigned to a
//				different line in the same set-up.
bool CSysConfig::AddAssociation(CString& sRollSet,CString& sProductionLine)
{
	POSITION pos;
	CAssociation* pListedAssociation;
	CString sListedSetting = _T("");
	CString sListedLine = _T("");

	if (!m_tplAssociationList.IsEmpty())						//	Associations already in list, so ...
	{															// ... check for duplicates ...
		for (pos = m_tplAssociationList.GetHeadPosition(); pos != NULL;)	// ... loop through list ... 
		{
			pListedAssociation = m_tplAssociationList.GetNext(pos);
			pListedAssociation->GetAssociation(sListedSetting,sListedLine);
			if (sListedSetting != sRollSet)						// ... looking for a match ...
			{
			}													// ... no match, so re-run loop.
			else
			{													// ... display a warning if found..
				AfxMessageBox("You have already assigned this setting to a production line",
								MB_OK|MB_ICONEXCLAMATION);
				return false;									// ... and return to property sheet.
			}
		}														// Loop has finished without finding a match ...
	}															// ... or list is empty ...

	CAssociation* pAssociate = new CAssociation();				// ... so, create new item ...
	pAssociate->SetAssociation(sRollSet,sProductionLine);		// ... set the member variables ...
	m_tplAssociationList.AddTail(pAssociate);							// ... and add it to the list.
	return true;
}

/////////10////////20////////30////////40////////50////////60////////70////////80////////90////////100///////110///////120///////130
// DeleteAssociation() A function to remove a product and production line association from the list.
//
bool CSysConfig::DeleteAssociation(CString& sRollSet,CString& sProductionLine)
{
	POSITION pos = m_tplAssociationList.GetHeadPosition();
	POSITION Endpos = m_tplAssociationList.GetTailPosition();
	CAssociation* pListedAssociation;
	CString sListedSetting = _T("");
	CString sListedLine = _T("");

	while(pos)															// Loop through list ... 
	{
		if (pos == Endpos)
		{
			pListedAssociation = m_tplAssociationList.GetAt(Endpos);
			pListedAssociation->GetAssociation(sListedSetting,sListedLine);
			m_tplAssociationList.RemoveAt(Endpos);
			delete pListedAssociation;								
			return true;				
		}

		pListedAssociation = m_tplAssociationList.GetNext(pos);					// ... get pointer to each list entry in turn
		pListedAssociation->GetAssociation(sListedSetting,sListedLine);	// ... use pointer to get data
		if (sListedSetting != sRollSet)									// ... look for a match ...
		{}																// ..  no match this time - try again
		else															// Got a match
		{
			m_tplAssociationList.GetPrev(pos);									// ... reset pos to matching item ...
			m_tplAssociationList.RemoveAt(pos);									// ... remove the pointer from list ...
			delete pListedAssociation;									// ... delete the object.
			return true;												// ... and return
		}
	}	// Loop has finished without finding a match ...
	
	// We should never get here but!
	AfxMessageBox("Association not listed",
					MB_OK|MB_ICONEXCLAMATION);							// ... display a warning if match not found..
	return false;														// ... and return to property sheet.
}

/////////10////////20////////30////////40////////50////////60////////70////////80////////90////////100///////110///////120///////130
// AddOutputAss() A function to link generated output for a production line to the output file directory list.
//
bool CSysConfig::AddOutputAss (CString& sPLine,CString& sPath)
{
	POSITION pos;
	COutputList* pListedAssociation;
	CString sListedPath = _T("");
	CString sListedPLine = _T("");

	if (!m_tplOutputList.IsEmpty())
	{
		for (pos = m_tplOutputList.GetHeadPosition(); pos != NULL;)
		{
			pListedAssociation = (COutputList*)m_tplOutputList.GetNext(pos);
			pListedAssociation->GetOutput(sListedPLine,sListedPath);
			
			if (sListedPath != sPath)
			{}
			else
			{
				AfxMessageBox("You have already assigned this Path to a Production Line",
								MB_OK|MB_ICONINFORMATION);
				return false;
			}
		}
	}

	COutputList* pOutput = new COutputList();
 	pOutput->SetOutput(sPLine,sPath);
	m_tplOutputList.AddTail(pOutput);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
/////
bool CSysConfig::DeleteOutput(CString& sProductionLine, CString& sPath)
{
	POSITION pos = m_tplOutputList.GetHeadPosition();
	POSITION Endpos = m_tplOutputList.GetTailPosition();
	COutputList* pListedAssociation;
	CString sListedLine = _T("");
	CString sListedPath = _T("");

	while(pos)															
	{
		if (pos == Endpos)
		{
			pListedAssociation = m_tplOutputList.GetAt(Endpos);
			pListedAssociation->GetOutput (sListedLine,sListedPath);
			m_tplOutputList.RemoveAt(Endpos);
			delete pListedAssociation;								
			return true;				
		}

		pListedAssociation = m_tplOutputList.GetNext(pos);				
		pListedAssociation->GetOutput (sListedLine,sListedPath);
		
		if (sListedLine != sProductionLine)								
		{}															
		else														
		{
			m_tplOutputList.GetPrev(pos);								
			m_tplOutputList.RemoveAt(pos);								
			delete pListedAssociation;								
			return true;											
		}
	}	// Loop has finished without finding a match ...
	
	// We should never get here but!
	AfxMessageBox("Association not listed",
					MB_OK|MB_ICONEXCLAMATION);						
	return false;														
}

/////////10////////20////////30////////40////////50////////60////////70////////80////////90////////100///////110///////120///////130
// AddReportAss() A function to link generated output for a production line to the report file directory list.
//
bool CSysConfig::AddReportAss (CString& sPLine,CString& sPath)
{
	POSITION pos;
	CReports* pListedAssociation;
	CString sListedPath = _T("");
	CString sListedPLine = _T("");

	if (!m_tplReportList.IsEmpty())
	{
		for (pos = m_tplReportList.GetHeadPosition(); pos != NULL;)
		{
			pListedAssociation = (CReports*)m_tplReportList.GetNext(pos);
			pListedAssociation->GetOutput(sListedPLine,sListedPath);
			
			if (sListedPath != sPath)
			{
			}
			else
			{
				AfxMessageBox("You have already assigned this Path to a Production Line",
								MB_OK|MB_ICONINFORMATION);
				return false;
			}
		}
	}

	CReports* pReport = new CReports();
 	pReport->SetOutput(sPLine,sPath);
	m_tplReportList.AddTail(pReport);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
/////
bool CSysConfig::DeleteReport(CString& sProductionLine, CString& sPath)
{
	POSITION pos = m_tplReportList.GetHeadPosition();
	POSITION Endpos = m_tplReportList.GetTailPosition();
	CReports* pListedAssociation;
	CString sListedLine = _T("");
	CString sListedPath = _T("");

	while(pos)														
	{
		if (pos == Endpos)
		{
			pListedAssociation = m_tplReportList.GetAt(Endpos);
			pListedAssociation->GetOutput (sListedLine,sListedPath);
			m_tplReportList.RemoveAt(Endpos);
			delete pListedAssociation;								
			return true;				
		}
			
		pListedAssociation = m_tplReportList.GetNext(pos);				
		pListedAssociation->GetOutput (sListedLine,sListedPath);	
		
		if (sListedLine != sProductionLine)							
		{}															
		else														
		{
			m_tplReportList.GetPrev(pos);								
			m_tplReportList.RemoveAt(pos);								
			delete pListedAssociation;								
			return true;											
		}
 	}
	
	// We should never get here but!
	AfxMessageBox("Association not listed",
					MB_OK|MB_ICONEXCLAMATION);
	return false;
}

