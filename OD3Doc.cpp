// OD3Doc.cpp : implementation of the COD3Doc class
//

#include "stdafx.h"
#include <direct.h>
#include "OD3.h"
#include "LeftView.h"
#include "MainFrm.h"

#include "OD3Doc.h"
#include "SysConfig.h"
#include "SysTemplate.h"
#include "Item.h"
#include "Element.h"
//#include "Accessory.h"
#include "ImportDet3.h"
#include "D3splitter.h"

#include "DlgNewProject.h"
#include "DlgProjectOptions.h"
#include "DlgItemList.h"
#include "CeeSection.h"
#include "ImportAswFile.h"
#include "DaoAccOffset.h"
#include "DaoCoilJob.h"
#include "DaoCoilJobDetails.h"
#include "DaoCoilLiveDuplicateSections.h"
#include "DaoCoilLiveSingleSections.h"
#include "DaoCoilSectionSum.h"
#include "Excel9.h"


#include "Line1.h"
extern CLine1 Line1;

#include "Line2.h"
extern CLine2 Line2;

#include "Line3.h"
extern CLine3 Line3;

#include "ProductMods.h"
extern CProductMods prodMods;

// Defined in mainframe.cpp
#include "CeeSectFail.h"
extern CCeeSectFail ceeFailDlg;

#include "DlgSplitter.h"
#include "DlgUpdateJobStatus.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COD3Doc

IMPLEMENT_DYNCREATE(COD3Doc, CDocument)

BEGIN_MESSAGE_MAP(COD3Doc, CDocument)
	//{{AFX_MSG_MAP(COD3Doc)
	ON_COMMAND(ID_DB_CONNECT, OnDbConnect)
	ON_COMMAND(ID_DB_DISCONNECT, OnDbDisconnect)
	ON_COMMAND(ID_OPEN_SYSCONFIG, OnOpenSysconfig)
	ON_UPDATE_COMMAND_UI(ID_DB_CONNECT, OnUpdateDbConnect)
	ON_UPDATE_COMMAND_UI(ID_DB_DISCONNECT, OnUpdateDbDisconnect)
	ON_UPDATE_COMMAND_UI(ID_OPEN_SYSCONFIG, OnUpdateOpenSysconfig)
	ON_UPDATE_COMMAND_UI(ID_ADD_NEWITEM, OnUpdateAddNewitem)
	ON_COMMAND(ID_FILE_IMPORT_PROJECTSETTINGS, OnFileImportProjectsettings)
	ON_COMMAND(ID_FILE_IMPORT_D3, OnFileImportD3)
	ON_COMMAND(ID_PROCESS_ADD_NEWBEAM, OnProcessAddNewbeam)
	ON_COMMAND(ID_PROCESS_ADD_NEWACCESSORY, OnProcessAddNewaccessory)
	ON_COMMAND(ID_PROCESS_ADD_NEWITEM, OnProcessAddNewitem)
	ON_COMMAND(ID_PROCESS_DELETE_BEAM, OnProcessDeleteBeam)
	ON_COMMAND(ID_PROCESS_DELETE_ACCESSORY, OnProcessDeleteAccessory)
	ON_COMMAND(ID_PROCESS_GENERATE_ALL, OnProcessGenerateAll)
	ON_COMMAND(ID_PROCESS_GENERATE_ITEM, OnProcessGenerateItem)
	ON_COMMAND(ID_PROCESS_VALIDATE_ALL, OnProcessValidateAll)
	ON_COMMAND(ID_PROCESS_VALIDATE_ITEM, OnProcessValidateItem)
	ON_COMMAND(ID_PROCESS_DELETE_ITEM, OnProcessDeleteItem)
	ON_COMMAND(ID_FILE_TRANSFER, OnFileTransfer)
	ON_COMMAND(ID_FILE_TRANSFER2, OnFileTransfer2)
	ON_COMMAND(IDM_IMPORT_ASW, OnImportAsw)
	ON_COMMAND(IDM_EXPORT_D3, OnExportD3)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_D3, OnUpdateExportD3)
	ON_COMMAND(IDM_PRINT_SUMMARY, OnPrintSummary)
	ON_UPDATE_COMMAND_UI(IDM_PRINT_SUMMARY, OnUpdatePrintSummary)
	ON_COMMAND(IDM_PRINT_JOBSHEETS, OnPrintJobsheets)
	ON_UPDATE_COMMAND_UI(IDM_PRINT_JOBSHEETS, OnUpdatePrintJobsheets)
	ON_COMMAND(IDM_COIL_SENDJOB, OnCoilSendjob)
	ON_UPDATE_COMMAND_UI(IDM_COIL_SENDJOB, OnUpdateCoilSendjob)
	ON_COMMAND(IDM_COIL_UPDATEJOB, OnCoilUpdatejob)
	ON_COMMAND(IDM_COIL_PRINTLIVE, OnCoilPrintlive)
	ON_COMMAND(IDM_COIL_EXPORTLIVE, OnCoilExportlive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COD3Doc construction/destruction

COD3Doc::COD3Doc()
{
	// TODO: add one-time construction code here

	m_pProjectHeader = new CProjectHeader();
	m_pProjectSettings = new CSysConfig();
	m_pProjectSettings->m_pDoc = this;
	m_pBeamModeless = NULL;

	// Clean mirror pointer
//	this->m_tplMirror.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// Class Destructor
COD3Doc::~COD3Doc()
{
	POSITION		pos;
	CItem*			pItem;


	// Remove the mirror pointers
	removeMirror();

	delete(m_pProjectHeader);
	delete(m_pProjectSettings);	

	pos = m_tplItemList.GetHeadPosition();
	while(pos)
	{
		pItem = m_tplItemList.GetNext(pos);
		delete(pItem);
	}
	m_tplItemList.RemoveAll();

	// Delete the accessory objects
	pos = m_tplAccItemList.GetHeadPosition();
	while(pos)
		delete m_tplAccItemList.GetNext(pos);

	m_tplAccItemList.RemoveAll();

	// Delete jobsheets
	pos = m_tplJobSheet.GetHeadPosition();
	while(pos)
		delete m_tplJobSheet.GetNext(pos);

	m_tplJobSheet.RemoveAll();

}

/////////////////////////////////////////////////////////////////////////////
// SetTitle()	Set title to document window based on the project name
//
void COD3Doc::SetTitle(LPCTSTR lpszTitle) 
{
	CString sFile = m_pProjectHeader->m_sProjectName;
	lpszTitle = (LPCTSTR) sFile;
	CString		fileName=sFile;

	if(this->IsModified())
		fileName += " *";

	CDocument::SetTitle(fileName);
}


/////////////////////////////////////////////////////////////////////////////
// SetPathName()		Set up  default pathname based on 
//						info supplied in header and property sheets.
//
void COD3Doc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{

	if(strlen(lpszPathName))
		CDocument::SetPathName(lpszPathName, bAddToMRU);
}

/////////////////////////////////////////////////////////////////////////////
// OnNewDocument()
//
BOOL COD3Doc::OnNewDocument()
{
	bool bFlag=true;

	if (!CDocument::OnNewDocument())
	{
		bFlag = false;
	}
	else
	{
		// Call the project header dialog 
		CDlgNewProject StartDlg;
		if(StartDlg.DoModal() == IDOK)
		{	
			COD3App* pApp = (COD3App*)AfxGetApp();
			m_pProjectHeader->m_sAppVersion = pApp->m_sAppVer;
				
			// Assign the data captured from input.
			m_pProjectHeader->m_nProjectType	= StartDlg.m_radioProjectType;
			m_pProjectHeader->m_sProjectName	= StartDlg.m_editProjectName;
			m_pProjectHeader->m_sCustomerName 	= StartDlg.m_editCustomerName;
			m_pProjectHeader->m_sCustomerRef	= StartDlg.m_editCustomerRef;	

			// VHF TODO: Sort out CString to CTime data type for due date.
			m_pProjectHeader->m_sDueDate		= StartDlg.m_editDueDate;
			
			m_pProjectHeader->m_sJobDestination	= StartDlg.m_editJobDestination;

			// Now call the system configuration options dialog
			CDlgProjectOptions SysOptionsDlg;
			SysOptionsDlg.DoModal();

			int options = SysOptionsDlg.m_nProjectSettings;

			switch(options)
			{
			case 1:
				// Set document pointer
				m_pProjectSettings->m_pDoc = this;
				// Connect to the database
				m_pProjectSettings->OnDbConnect();
				// Open the system config dialog
				m_pProjectSettings->OnOpenSysconfig();
				break;
			case 2:
#if 0
				OnFileImportProjectsettings();
#endif
 				break;
			}
									
			//	now refresh the document title and pathname
			LPCTSTR lpszTitle =_T("");
			LPCTSTR lpszPathName =_T("");
			BOOL bAddToMRU = false;		//don't add it to MRU until its saved
			
			SetModifiedFlag(true);
			SetTitle(lpszTitle);
			SetPathName(lpszPathName, bAddToMRU);

		}
		else
		{
			// Document failed
			bFlag = false;
		}
	}
		
	// Return document result
	return(bFlag);
}


/////////////////////////////////////////////////////////////////////////////
// OnOpenDocument()	Open an existing project file
//
BOOL COD3Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	COD3App* pApp = (COD3App*)AfxGetApp();
	m_pProjectHeader->m_sAppVersion = pApp->m_sAppVer;
			
	m_pProjectSettings->AutoDbConnect();

	/* Store a mirror copy of the line / product associations ///
		used for manual hash code testing */
	storeMirrorAsso();
	/////////////////////////////////////////////////////////////


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// OnSaveDocument()		Set up  default path and file name based on 
//						info supplied in header and property sheets.
//
BOOL COD3Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CString sPath = m_pProjectSettings->m_sProjectInputPath;
	CString sFile = m_pProjectHeader->m_sProjectName;
	CString sExtn = ".od3";
	CString sPathName = sPath + "\\" + sFile + sExtn;
	LPCTSTR lpszOldName = (LPCTSTR)sPathName;

	if (lpszPathName != lpszOldName)
	{
		sFile = (CString)lpszPathName;
		int pos = 0;
		while (pos != -1)
		{
			pos = sFile.Find((LPCTSTR) "\\", 0);
			if (pos != -1){sFile = sFile.Right(sFile.GetLength() - ++pos);}
		}

		pos = 0;
		while (pos != -1) 
		{
			pos = sFile.Find((LPCTSTR) ".",0);
			if (pos != -1){sFile = sFile.Left(pos);}
		}

		m_pProjectHeader->m_sProjectName = sFile;
	}
	
	LPCTSTR lpszTitle = (LPCTSTR)sFile;
	BOOL bAddToMRU = true;		//add it to MRU when its saved
	
	SetTitle(lpszTitle);
	SetPathName(lpszPathName, bAddToMRU);

	this->UpdateAllViews(NULL,NULL,NULL);
	return CDocument::OnSaveDocument(lpszPathName);

}

/////////////////////////////////////////////////////////////////////////////
// OnFileImportProjectsettings()	Event handler to call 'Open existing sysconfig template file' function
//
void COD3Doc::OnFileImportProjectsettings() 
{
	CSysTemplate* pTemplate = new CSysTemplate();

	pTemplate->LoadTemplate();
	delete pTemplate;
	m_pProjectSettings->AutoDbConnect();
}

/////////////////////////////////////////////////////////////////////////////
// OnFileImportD3()		Event handler to call 'Open existing D3 file' function
//
void COD3Doc::OnFileImportD3() 
{
	char		buf[250];
/**** Not finished in version 2.4.50.0 ****/
//	CD3splitter	fileSplit;
/**** Not finished in version 2.4.50.0 ****/

	// Is config file missing? do not continue
/**** Not finished in version 2.4.50.0 ****/
//	if(fileSplit.FileOK())
/**** Not finished in version 2.4.50.0 ****/
	{
		CImportDet3	*pImport = new CImportDet3();

		pImport->m_pDoc = this;

		BeginWaitCursor();
		
		if(pImport->OpenFile())
		{
			int				iBeamIndex=0;
			bool			loop=true;
			CImportD3Beam	newBeam;

			while(loop)
			{
				// Read the panels and add included beams to import pointer list
				loop=newBeam.readASFPanels(pImport, iBeamIndex++);
			}

			pImport->SetProjectHeader();
			RestoreWaitCursor();
			pImport->SortBeamsByAscendingProductName();
			pImport->SortAccByAscendingProductName();

/**** Remove these when D3 splitter complete ****/			
			pImport->ListImportedItems();

			EndWaitCursor();
/**** Remove these when D3 splitter complete ****/


/**** Not finished in version 2.4.50.0 ****/
#if 0 
			/******** Perform imported D3 file data product splitting here *********/
			fileSplit.splitD3File(pImport);

			pImport->ListImportedItems();

			EndWaitCursor();


			// Open the export and print D3 file dialog if required
			if(fileSplit.dialogRequired())
			{
				CDlgSplitter dlgSplit;

				// Set the pointer for the split data
				dlgSplit.m_splitClass = &fileSplit;
				// Set pointer for imported data
				dlgSplit.m_pImport = pImport;
				// open dialog
				dlgSplit.DoModal();
			}
#endif
/**** Not finished in version 2.4.50.0 ****/
			
			CDlgItemList ImportDlg;
			ImportDlg.m_pDoc = this;
			ImportDlg.DoModal();

			/* NB: If we need to do anything elese with the 'raw' imported data
				we need to do it now before the pointer to the class and its
				m_tplBeamList & m_tplAccList is destroyed */

			delete pImport;
			SetModifiedFlag();
			SetTitle(NULL);

			
			// Convert import filename to document filename
			if(this->m_pProjectSettings->m_sProjectInputPath.GetLength())
			{
				strcpy(buf, this->m_pProjectSettings->m_sProjectInputPath);
				strcat(buf, "\\");
			}
			else
				strcpy(buf, "C:\\");

			strcat(buf, m_pProjectHeader->m_sProjectName);
			strcat(buf, ".od3");
			SetPathName(buf, false);

			UpdateAllViews(NULL,NULL,NULL);

			// Restore mirror line associations
			storeMirrorAsso();
		}
	}

	return;
}


/////////////////////////////////////////////////////////////////////////////
// COD3Doc serialization

void COD3Doc::Serialize(CArchive& ar)
{
	try
	{
		m_pProjectHeader->Serialize(ar);
		m_pProjectSettings->Serialize(ar);
		m_tplItemList.Serialize(ar);

		// Load / store the accessory data
		m_tplAccItemList.Serialize(ar);

	}
	catch(CArchiveException *e)
	{
		/* Test if the exeption is past the end of the file, this will be caused by
			opening an older version of OD3 file type containg no accessory data class.*/

		// Dont report the end of file exception and continue
		if(e->m_cause != CArchiveException::endOfFile)
			e->ReportError(MB_OK|MB_ICONINFORMATION);

		// Delete the exception
		e->Delete();
	}
}

/////////////////////////////////////////////////////////////////////////////
// COD3Doc diagnostics

#ifdef _DEBUG
void COD3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void COD3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COD3Doc message handlers
/////////////////////////////////////////////////////////////////////////////
// OnProcessAddNewitem()
//
void COD3Doc::OnProcessAddNewitem() 
{
	// Call the items list dialog to set up item numbers for products
	CDlgItemList AddItemsDlg;
	AddItemsDlg.m_pDoc = this;
	AddItemsDlg.m_sFilter = m_sCustomerFilter;
	AddItemsDlg.DoModal();
	m_sCustomerFilter = AddItemsDlg.m_sFilter;
}

/////////////////////////////////////////////////////////////////////////////
// OnProcessDeleteItem()
//
void COD3Doc::OnProcessDeleteItem() 
{
	CItem	*pItem=NULL;
	int		nItemID;
	int		nMemberType = 0;
	CString szMsg;

	CDlgItemList DeleteItemDlg;
	DeleteItemDlg.m_pDoc = this;
	DeleteItemDlg.DoModal();

	if(pItem = DeleteItemDlg.GetItemPointer())
	{
		nItemID = pItem->GetItemID();

		szMsg.Format(IDS_DEL_ITEM, nItemID);
		if(AfxMessageBox(szMsg, MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			// Delete item
			this->DeleteItem(pItem);
		}
		else
		{
			return;
		}

		this->SetModifiedFlag(true);
		this->SetTitle(NULL);
		UpdateAllViews(NULL/*, NULL, NULL*/);
	}


}

///////////////////////////////////////////////////////////////////////////////////
// OnProcessValidateItem()		Message handler - gets pointer to item from dialog
//								and passes it call to ValidateItem()
//
void COD3Doc::OnProcessValidateItem() 
{
	CItem*	pItem;

	this->m_bProcessAll = false;

	// Call the items list dialog to get the item to validate
	CDlgItemList SelectItemDlg;
	SelectItemDlg.m_pDoc = this;
	SelectItemDlg.DoModal();

	pItem = SelectItemDlg.GetItemPointer();

	if (this->ValidateItem(pItem))
	{
		AfxMessageBox("Validation passed");
	}
	else
	{
		CString szMsg;
		szMsg = "Validation has failed!";
		szMsg += "\n\nYou must associate all products in this project";
		szMsg += "\nwith appropriate production lines to complete the validation";
		AfxMessageBox(szMsg);
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// OnProcessValidateAll()		Message handler - calls ValidateItem() inside while loop
//
void COD3Doc::OnProcessValidateAll() 
{
	POSITION	pos;
	CItem*		pItem;
	CString		szMsg;
	CString		sItemID;


	// Process all items ?
	if (m_pProjectSettings->m_nProcessAll !=1)
	{
		m_bProcessAll = true;
	}
	else
	{
		m_bProcessAll = false;
		this->OnProcessValidateItem();
	}

	// step through the item list to validate 'item' data
	pos = this->m_tplItemList.GetHeadPosition();

	while(pos)
	{
		pItem = this->m_tplItemList.GetNext(pos);
		this->ValidateItem(pItem);
	}


	// Validate all accessories
	pos = m_tplAccItemList.GetHeadPosition();

	while(pos)
	{
		// Get the next accessory object
		pItem = this->m_tplAccItemList.GetNext(pos);
		// Validate the accessory
		ValidateAccItem(pItem);
	}

}

///////////////////////////////////////////////////////////////////////////////////////
// OnProcessGenerateItem()		Message handler - call dialog to select item to process
//
void COD3Doc::OnProcessGenerateItem() 
{
	CMainFrame	*pMainFrm=DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	CItem		*pItem;
	int			nItemID;
	int			nOpCount;
	CString		sItemID;
	CString		sText;

	// Call the items list dialog to get the item to validate
	CDlgItemList SelectItemDlg;
	SelectItemDlg.m_pDoc = this;
	SelectItemDlg.DoModal();

	pItem = SelectItemDlg.GetItemPointer();

	BeginWaitCursor(); // display the hourglass cursor

	nOpCount = this->GetElementOpCount(pItem);
	this->InitProgressIndicator(nOpCount);

	this->m_bIsGenerated = false;
	this->m_bIsGenerating = true;

	if (this->ValidateItem(pItem))
	{}
	else
	{
		CString szMsg;
		szMsg = "Validation has failed!";
		szMsg += "\n\nYou must associate all products in this project";
		szMsg += "\nwith appropriate production lines to complete the validation";
		AfxMessageBox(szMsg);
		return;
	}

	// if item fails to generate because of non-standard requirement or
	// NULL punch value exit the loop to reach the CmdTarget break so
	// the modeless dialog will be displayed for updating

	if(!this->GenerateItem(pItem))
	{
		// Remove progress bar
		if(pMainFrm->m_bProgCreated)
		{
			pMainFrm->m_bProgCreated = false;
			pMainFrm->m_progressBar.DestroyWindow();
		}

		return;
	}

	LPCTSTR lpszText = _T("Ready");
	this->UpdateStatusBar(lpszText);

	nItemID = pItem->GetItemID();

	// Format message
	sText.Format("Output Generated for Item %d", nItemID);
	// Create message dialog
	CDlgMessage msg(NULL, sText);

	// Display message
	msg.DoModal();


	this->m_bIsGenerating = false;
	this->m_bIsGenerated = true;

	EndWaitCursor(); // remove the hourglass cursor
	// Remove progress bar
	if(pMainFrm->m_bProgCreated)
	{
		pMainFrm->m_bProgCreated = false;
		pMainFrm->m_progressBar.DestroyWindow();
	}


	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//	OnProcessGenerateAll()		Message handler - calls GenerateItem() inside while loop
//

void COD3Doc::OnProcessGenerateAll() 
{
	CMainFrame		*pMainFrm=DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());
	POSITION		pos;
	CItem*			pItem;
	int				nOpCount;


	// Process all items ?
	if (m_pProjectSettings->m_nProcessAll !=1)
	{
		m_bProcessAll = true;
	}
	else
	{
		m_bProcessAll = false;
		this->OnProcessGenerateItem();
		// Clear waring flag
		prodMods.warn = true;
		return;
	}

	BeginWaitCursor(); // display the hourglass cursor

	nOpCount = this->GetOpCount();
	this->InitProgressIndicator(nOpCount);

	this->m_bIsGenerating = true;

	this->OnProcessValidateAll();

	pos = this->m_tplItemList.GetHeadPosition();

	while(pos)
	{
		this->m_bIsGenerated = false;
		pItem = this->m_tplItemList.GetNext(pos);

		// if item fails to generate because of non-standard requirement or
		// NULL punch value exit the loop to reach the CmdTarget break so
		// the modeless dialog will be displayed for updating

		if(!this->GenerateItem(pItem)){return;}	

		this->m_bIsGenerated = true;
	}

	// Get the head position for the accessories
	pos = this->m_tplAccItemList.GetHeadPosition();

	while(pos)
	{
		// Get the next accessory object
		pItem = this->m_tplAccItemList.GetNext(pos);

		if(GenerateAccItem(pItem))
			m_bIsGenerated = true;
	}
	EndWaitCursor(); // remove the hourglass cursor
	
	
	// Remove progress bar
	if(pMainFrm->m_bProgCreated)
	{
		pMainFrm->m_bProgCreated = false;
		pMainFrm->m_progressBar.DestroyWindow();
	}
	

	LPCTSTR lpszText = _T("Ready");
	this->UpdateStatusBar(lpszText);
	this->CloseProgressIndicator();

	// Dont display completed message if cee sections failed
	if(!ceeFailDlg.IsWindowVisible())
	{	
		// Create message dialog
		CDlgMessage msg(NULL, "Output Generated");

		// Display message
		msg.DoModal();
	}

	this->m_bIsGenerating = false;
	
	// Clear waring flag
	prodMods.warn = true;

}

/////////////////////////////////////////////////////////////////////////////
// COD3Doc commands
/////////////////////////////////////////////////////////////////////////////
// ValidateItem()		
//
bool COD3Doc::ValidateItem(CItem* pItem)
{
	int		nMemberType = 0;
	int		nItemID;
	CString csMsg;
	CString sItemID;
	bool	bResult=true;

	//	Process automatically using defaults or prompt for associations ?
	if (m_pProjectSettings->m_nProcessAuto !=1)
		{m_bPrompt = false;}
	else
		{m_bPrompt = true;}

validate:
	
	nMemberType = pItem->GetType();

	switch(nMemberType)
	{
	case ACCESSORY:
			AfxMessageBox("Not yet implemeted!");
			bResult = false;
		break;

	default:
		// do we need to prompt for associations ?
		if (m_bPrompt)
		{
			this->OnOpenSysconfig();	// get associations into property sheets
			this->CheckDirty();			// force data update
		}

		// check product/production line association exists
		pItem->m_pDoc = this;

		

		if(!pItem->SetLineFlag())
		{
			csMsg = "Production Line Flag not set for item ";
			nItemID = pItem->GetItemID();
			sItemID.Format("%d",nItemID);
			csMsg += sItemID;
			csMsg += "!";
			csMsg += "\n\nMake the necessary product v production line associations";
			csMsg += "\n\nOD3 will then re-validate the project";
			if(AfxMessageBox(csMsg,MB_OKCANCEL) != IDCANCEL)
			{
				this->OnOpenSysconfig();	// get associations into property sheets
				goto validate;
			}
			else
			{
				// Set to fail
				bResult = false;
			}
		}
		else
		{
			if(1 == pItem->GetProdLine())
			{
				// Test for maximum elements (100)
				if(pItem->m_tplElementList.GetCount() > 99)
				{
					// Warn user to many elements
					csMsg.Format(IDS_LINE1_OVERFLOW ,pItem->GetItemID());
					AfxMessageBox(csMsg, MB_ICONWARNING|MB_OK);

					// Set to fail
					bResult = false;
				}
			}
		}
		break;
	}

	return(bResult);
}

////////////////////////////////////////////////////////////////////////////////////////
// GenerateItem()	Command function called by message handler
//					passes pointer to item to process.
//					returns TRUE if generation succesful and FALSE if update required.
//
bool COD3Doc::GenerateItem(CItem* pItem)
{
	// Test for Cee section comments
	CCeeSection	cee(this);
	bool		isOK=true;
	bool		result=true;
	bool		isCee;

	// Compare loaded and current line to product associations
	if(compareMirrorAsso())
	{
		// Line assoications have been changed perform hash code test
		if(testForManualHashCodes())
		{
			/* Inform the user about the manual input hash codes ////////////////
			// give the options to silence the warning and continue generation */
			switch(AfxMessageBox(IDS_MANUAL_CODE_WARNING, MB_ICONWARNING|MB_OKCANCEL))
			{
				case IDCANCEL:
					// Remove and store the current line/product associations
					storeMirrorAsso();
					break;

				case IDOK:
					// Load up manual input dialog

					// Do not generate
					return(false);
					break;
			}
			
		}
	}

	// Perform advanced Cee section search
	if( (isCee=cee.ceeTest(pItem)) )
		isOK = cee.performTest(pItem);

	// Continue looping
	if(isCee && !isOK)
		return true;

	// Cee section fine or not Cee
	if(isOK)
	{
		//	reset 'punch_used' flags
		pItem->ResetPunchFlags();
		pItem->ResetPunchGauge();

		// create local member type variable
		int	nMemberType = 0;

		// set local variable to item member type
		nMemberType = pItem->GetType();

		// pass item pointer and member type to 
		this->GetScriptOps(pItem, nMemberType);

		if (pItem->GetNonStandardFlag() != false)
		{
			CMainFrame	*pMainFrm=DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());

			// Remove progress bar
			if(pMainFrm->m_bProgCreated)
			{
				pMainFrm->m_bProgCreated = false;
				pMainFrm->m_progressBar.DestroyWindow();
			}
			this->UpdateGrid(pItem);

			return false;
		}

		this->GenerateOutput(pItem);
	}
	else
	{
		// Cee section warning
		result=false;
	}

	return(result);

}


/////////////////////////////////////////////////////////////////////////////
// UpdateGrid()
//
void COD3Doc::UpdateGrid(CItem* pItem)
{
	int		nItemID;
	CString	sItemID;

	nItemID = pItem->GetItemID();
	sItemID.Format("%d",nItemID);
	
	CString szMsg = "Item No.";
	szMsg += sItemID;
	szMsg += " - Generation Failed.";
	szMsg += "\n\nView customer drawing and manually input non-standard punch code";
	szMsg += "\n\nIssue Special Instruction Datasheet";
	szMsg += "\nto shop floor to indicate requirements";
	AfxMessageBox(szMsg);

	//	I call the beam dialog here

	CBeamElement* pBeam = (CBeamElement*)pItem->GetFailedBeam();

	if(pBeam)
	{
		int cElementCounter = pBeam->GetElementID();


		if (m_pBeamModeless != NULL)
		{
	//		m_pBeamModeless->m_bUpdate = true;
			this->RefreshBeamDialog(pItem, pBeam, cElementCounter);
		}
		else		// dialog not up - so create it 'new'
		{
			this->CreateBeamDialog(pItem, pBeam, cElementCounter);
	//		m_pBeamModeless->m_bUpdate = true;
		}
		szMsg = "When you have made changes in this dialog";
		szMsg += "\nand received the 'Output Generated' message"; 
		szMsg += "\nyou must REPEAT the Process | Generate | All function";
		szMsg += "\nbefore using the 'Transfer' or 'Print' options.";
		AfxMessageBox(szMsg);
	}

}

/////////////////////////////////////////////////////////////////////////////
// OnProcessAddNewbeam()	message handler - calls command function AddBeam()
//
void COD3Doc::OnProcessAddNewbeam() 
{
	CItem*			pItem;

	// Call the items list dialog to select item to add to
	CDlgItemList SelectItemsDlg;
	SelectItemsDlg.m_pDoc = this;
	SelectItemsDlg.DoModal();

	pItem = SelectItemsDlg.GetItemPointer();

	this->AddBeam(pItem);

	SetModifiedFlag();
	SetTitle(NULL);
	UpdateAllViews(NULL);

}

/////////////////////////////////////////////////////////////////////////////
// AddBeam()	command function 
//
void COD3Doc::AddBeam(CItem* pItem) 
{
	CBeamElement*	pBeam = NULL;
	int		nMemberType = 0;
	int		nItemType = 0;
	int		cElementCounter;
	int		nLastElement;
	CString sProfile("");

	nLastElement = this->GetElementCount(pItem->GetItemID());
	cElementCounter = pItem->GetItemID() * 1000;
	cElementCounter += nLastElement;

	pBeam = new CBeamElement;			// so create a new beam, ...
	++cElementCounter;					// and increment the counter (it's the first one)
	pBeam->m_pItem = pItem;
	pBeam->SetLength(0);

	// ... if the modeless input dialog child is already up, ...
	// ... no need to create it - just set focus to it

	if (m_pBeamModeless != NULL)
	{
		this->RefreshBeamDialog(pItem, pBeam, cElementCounter);
	}
	else		// dialog not up - so create it 'new'
	{
		this->CreateBeamDialog(pItem, pBeam, cElementCounter);
	}
}


//////////////////////////////////////////////////////////////
//  OnProcessDeleteBeam() 
//
void COD3Doc::OnProcessDeleteBeam() 
{
	CItem*	pItem;
	CBeamElement* pBeam;
	int		cElementCounter;

	// Call the delete items dialog and get an item number from the user
	CDlgItemList DeleteItemDlg;
	DeleteItemDlg.m_pDoc = this;
	DeleteItemDlg.DoModal();

	pItem = DeleteItemDlg.GetItemPointer();

	cElementCounter = pItem->GetItemID() * 1000;
	++cElementCounter;

	pBeam = (CBeamElement*)pItem->m_tplElementList.GetHead();

	//  We need to display a list of beams and select which one to delete.
	// ... if the modeless input dialog child is already up, ...
	// ... no need to create it - just set focus to it

	if (m_pBeamModeless != NULL)
	{
		this->RefreshBeamDialog(pItem, pBeam, cElementCounter);
	}
	else		// dialog not up - so create it 'new'
	{
		this->CreateBeamDialog(pItem, pBeam, cElementCounter);
		m_pBeamModeless->m_bUpdate = false;
	}

}



/////////////////////////////////////////////////////////////////
// OnNextBeam() a function to retrieve data from the item's element list
//
void COD3Doc::OnNextBeam(CBeamDlg* pDlg)
{
	CItem*			pItem;
	CElement*		pElement;
	CBeamElement*	pBeam;
	int				cElementCounter;
	int				nLastElement;

	pItem = pDlg->m_pItem;					// ... find matching item ...

	if(pItem != NULL)
	{
		cElementCounter = (pDlg->m_cBeamCounter) + 1;				// ... increment local counter ...
		nLastElement = (pItem->m_tplElementList.GetCount());		// ... get total beam count for this item ...
		if (cElementCounter % 1000 <= nLastElement)					// ... check that it is not the last beam in the list ...
		{															// ... OK it's not ...
			pElement = pItem->m_tplElementList.GetHead();			// ... get pointer first element in list ...
			pBeam = (CBeamElement*)pElement;						// ... cast it as a beam element
			pBeam->m_pItem = pItem;
			pDlg->m_pBeam = pBeam->FindBeamByElementID(/*pItem,*/ cElementCounter);	// ... now the dialog a pointer to this beam
			pDlg->m_cBeamCounter = cElementCounter;					// ... set dialog counter to local counter ...
		}
		
		pDlg->SetActiveWindow();									// ... and re-display the dialog.
	}
	else
	{	
		// what happens is pItem is NULL ?
		AfxMessageBox("Error - No item pointer");
	}
}

/////////////////////////////////////////////////////////////////
// OnPreviousBeam() a function to retrieve data from the item's element list
//
void COD3Doc::OnPreviousBeam(CBeamDlg* pDlg)
{
	CItem*			pItem;
	CBeamElement*	pBeam;
	int				cElementCounter;

//	pItem = GetItemPointer(pDlg->m_nItemID);					// ... find matching item ...
	pItem = pDlg->m_pItem;										// ... find matching item ...
	if (pItem != NULL)
	{
		cElementCounter = (pDlg->m_cBeamCounter) - 1;			// ... decrement local counter ...
		if (cElementCounter % 1000 > 0)						// ... check that we're not already at first beam in the list ...
		{													// ... OK we're not ..
			pBeam = (CBeamElement*)pItem->m_tplElementList.GetHead();	// ... so get pointer first beam in list ...
			pBeam->m_pItem = pItem;
			pDlg->m_pBeam = pBeam->FindBeamByElementID(/*pItem,*/ cElementCounter);		// ... now find this beam and send the dialog its address...
			pDlg->m_pItem = pItem;
			pDlg->m_cBeamCounter = cElementCounter;			// ... set the dialog counter to the local counter
		}
		pDlg->SetActiveWindow();							// ... and re-display the dialog.
	}
	else
	{	
		// what happens is pItem is NULL ?
		AfxMessageBox("Error - No item pointer");
	}
}

//////////////////////////////////////////////////////////////
// BoxDone() Clean up on destruction of modeless dialog
//
void COD3Doc::BoxDone()
{
	// this function is called by the modeless dialog as it terminates
	// it will be re-enabled when OnAddNewItem() is called.
	// I _don't_ delete the MFC CDialog object because the dialog's own
	// code will do that.

	// VHF TODO: Need a switch function to decide whether being called from
	// beam or accessory dialog box.

	// don't delete m_pBeamModeless; !
	m_pBeamModeless = NULL;
}

//////////////////////////////////////////////////////////////
// CreateItem()	A function to create a new CItem object (list)
//				and add it to the item list.
CItem* COD3Doc::CreateItem(int nItemID)
{
	CItem* pNewItem = new CItem();		// create new item ...
	pNewItem->SetItemID(nItemID);		// allocate an itemID
	m_tplItemList.AddTail(pNewItem);	// ... add it to the list ...
	SetModifiedFlag();					// ... remind user to save file on exit ...
	SetTitle(NULL);
	this->UpdateAllViews(NULL);			// ... uodate the tree view
	return pNewItem;					// ... return pointer to new item.
}

// Create an accessory item (Overloaded)
CItem* COD3Doc::CreateItem(int nItemID, int iDummy)
{
	CItem* pNewItem = new CItem();		// create new item ...
	pNewItem->SetItemID(nItemID);		// allocate an itemID
	m_tplAccItemList.AddTail(pNewItem);	// ... add it to the list ...
	SetModifiedFlag();					// ... remind user to save file on exit ...
	SetTitle(NULL);
	this->UpdateAllViews(NULL);			// ... uodate the tree view
	return pNewItem;					// ... return pointer to new item.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	DeleteItem()	A function to delete a pointer to a CItem object and remove it from the documents item list	
//
void COD3Doc::DeleteItem(CItem* pItem)
{
	POSITION	delPos;	
	bool		bRemoved=false;


	// Any beams
	if(m_tplItemList.GetCount())
	{
		// Search beams for selected item
		if((delPos = m_tplItemList.Find(pItem)))
		{
			// Remove the object
			delete pItem;
			// Clean the pointer list
			m_tplItemList.RemoveAt(delPos);
			// Set flag to object found
			bRemoved=true;
		}
	}

	// Has beam object been found
	if(!bRemoved)
	{
		// Any accessories
		if(m_tplAccItemList.GetCount())
		{
			// Search accessories for selected item
			if((delPos = m_tplAccItemList.Find(pItem)))
			{
				// Remove the object
				delete pItem;
				// Clean the pointer list
				m_tplAccItemList.RemoveAt(delPos);
			}
		}
	}

	// Save when exit flag
	SetModifiedFlag();
	// Set title prompt
	SetTitle(NULL);
	// Redraw tree and list views
	UpdateAllViews(NULL);

}


////////////////////////////////////////////////////////////
// GetItemPointer() A function to return a CItem* pointer from the CObList m_tplItemList.
//			 to a specified CItem object. If item doesn't exist it will be created. 
//
CItem* COD3Doc::GetItemPointer(int nItemID, int iType)
{
	POSITION	pos;
	CItem*		pListedItem;


	// Beam or accessory
	if(iType==ISBEAM)
		pos = this->m_tplItemList.GetHeadPosition();
	else
		pos = this->m_tplAccItemList.GetHeadPosition();
	
	while(pos)
	{
		// Get the next beam or accessory object
		if(iType==ISBEAM)
			pListedItem = (CItem*)m_tplItemList.GetNext(pos);
		else
			pListedItem = (CItem*)m_tplAccItemList.GetNext(pos);

		// Test the object
		if(pListedItem->m_nItemID == nItemID)
			return pListedItem;
	}

	return(NULL);
} 

/////////////////////////////////////////////////////////////////////////////
// GetElementCount()	Access function to return the number of beams in an item's element list
//
int COD3Doc::GetElementCount(int nItemID)
{
	CItem*	pItem;
	int		nLastElement;

	pItem = GetItemPointer(nItemID, ISBEAM);						// ... find matching item ...
	if(pItem != NULL)
	{														// ... no matching item ...		
		nLastElement = (pItem->m_tplElementList.GetCount()); 	// ... get total beam count for this item ...
	}
	else
	{
		AfxMessageBox("No item pointer!");
		nLastElement = 0;
	}
	
	return(nLastElement);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UpdateDoc() a function to retrieve data from the ManInputDlg
//
void COD3Doc::UpdateDoc(int nMemberType)
{
//	CAccessoryElement*	pCurrentAcc;
	int			nTestType;

	if (nMemberType<=2){nTestType=BEAM;} else {nTestType=ACCESSORY;}

	switch(nTestType)
	{
	case BEAM:
		CItem*			pItem = this->m_pBeamModeless->m_pItem;
		CBeamElement*	pBeam = this->m_pBeamModeless->m_pBeam;
		int	cElementCounter	  = this->m_pBeamModeless->m_cBeamCounter;		// ... set a local counter;

		//Check that item ID and product name match
		if (pItem->GetProfile() != this->m_pBeamModeless->m_editProfile)
		{
			AfxMessageBox("This item ID has already been allocated to " + pItem->GetProfile(),
					MB_ICONWARNING|IDOK);
		}

		if (pItem->m_bIsBeam)														// ... it should be a beam ...
		{																			// ... and it is, so ...
//			pBeam->UpdateBeam(m_pBeamModeless);										// ... update with data from dialog ...
			pItem->CreateOrderedBeamList(pBeam);									// ... and add it to the list in ascending length order)

//			int nLastBeam = this->GetElementCount(this->m_pBeamModeless->m_nItemID) % 1000;
			if(!pItem->m_tplElementList.IsEmpty())
			{
				CElement* pLastElement = pItem->m_tplElementList.GetTail();
				int nLastElementID = pLastElement->GetElementID();
				if (cElementCounter < nLastElementID)
				{
					pBeam = (CBeamElement*)pItem->FindElementByID(++cElementCounter);	// ... get pointer to next beam from in list ...
					m_pBeamModeless->m_pItem = pItem;									// ... pass a pointer back to the dialog so it can refresh
					m_pBeamModeless->m_pBeam = pBeam;									// ... pass a pointer back to the dialog so it can refresh
					m_pBeamModeless->m_cBeamCounter = cElementCounter;					// ... and pass back the incremented beam counter.
				}
				else
				{
					m_pBeamModeless->m_cBeamCounter = FALSE;		// this implies that there are no more beams in the list
				}
			}
			else		// ... it should be a beam ...but it's already been declared as CAccessory.
			{			
				if (AfxMessageBox("This item number has already be allocated to an accessory item /nDo you wish to Overwrite it",MB_YESNO,0) != IDYES)
				{													// ... don't overwrite the existing item ...
					return;											// ... return to dialog - user should select the AddItem button.
				}
				else
				{													// change exisitng accessory item to beam !!
					// VHF TODO:	We need some more code here to delete all the items in the existing 
					//				element list.  Anything input previously to the item will be lost! 
					pItem->m_bIsBeam = true;
				}
			}
		}
/*	case ACCESSORY:
		cElementCounter = m_pAccModeless->m_cAccCounter;		// ... set a local counter
		pItem = GetItemPointer(m_pAccModeless->m_nItemID);				// ... get a pointer to the item
		if (!pItem->m_bIsBeam)									// ... it should be an accessorty ...
		{														// ... and it is, so ...
		pAcc = (CAccessoryElement*)pItem->GetAcc(cElementCounter);	// ... get pointer to first accessory in list ...
		pAcc->UpdateAcc(pAcc,m_pAccModeless);					// ... update with data from dialog ...
		m_pAccModeless->m_pAcc = pAcc;							// ... pass a pointer back to the dialog
		m_pAccModeless->m_cAccCounter = ++cElementCounter;		// ... and increment the counter.
		}
		else													// ... it should be a beam but ...
		{														// ... it's already been declared as CAccessory.
			if (AfxMessageBox("This item number has already be allocated to a beam item /nDo you wish to Overwrite it",MB_YESNO,0) != IDYES)
			{													// ... don't overwrite the existing item ...
				return;											// ... return to dialog - user should select the AddItem button.
			}
			else
			{													// change exisitng accessory item to beam !!
				// VHF TODO:	We need some more code here to delete all the items in the existing 
				//				element list.  Anything input previously to the item will be lost! 
				pItem->m_bIsBeam = false;
			}
		}
*/	}
	//	Also need to prompt user for beam ID (??)
	//	This will be similar to (if not the same as)
	//	the AddNewBeam handler}
	this->UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// OnDbConnect()
//
void COD3Doc::OnDbConnect() 
{
	m_pProjectSettings->OnDbConnect();
}

/////////////////////////////////////////////////////////////////////////////
// OnUpdateDbConnect()	Enable/Disable DB Connect button according to database status
//
void COD3Doc::OnUpdateDbConnect(CCmdUI* pCmdUI) 
{
	if(m_pProjectSettings->m_ODDB_Open)
		{pCmdUI->SetCheck(1);}
		else
		{pCmdUI->SetCheck(0);}
}

/////////////////////////////////////////////////////////////////////////////
// OnDbDisconnect()
//
void COD3Doc::OnDbDisconnect() 
{
	m_pProjectSettings->OnDbDisconnect();
}

/////////////////////////////////////////////////////////////////////////////
// OnUpdateDbdisconnect()	Enable/Disable DB Disconnect Button according to database status
//
void COD3Doc::OnUpdateDbDisconnect(CCmdUI* pCmdUI) 
{
	if(m_pProjectSettings->m_ODDB_Open)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}	
}

/////////////////////////////////////////////////////////////////////////////
// OnOpenSysconfig()
//
void COD3Doc::OnOpenSysconfig() 
{
	m_pProjectSettings->OnOpenSysconfig();	
}


/////////////////////////////////////////////////////////////////////////////
// OnUpdateOpenSysconfig()	Enable/Disable Property Sheet Connect Button according to database status
//
void COD3Doc::OnUpdateOpenSysconfig(CCmdUI* pCmdUI) 
{
	if(m_pProjectSettings->m_ODDB_Open)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}



/////////////////////////////////////////////////////////////////////////////
// OnUpdateAddNewitem()	Enable/Disable New Item Button according to database status
//
void COD3Doc::OnUpdateAddNewitem(CCmdUI* pCmdUI) 
{
	if(m_pProjectSettings->m_ODDB_Open)
		{pCmdUI->Enable(true);}
	else
		{pCmdUI->Enable(false);}
}


//////////////////////////////////////	
void COD3Doc::GenerateOutput(CItem* pItem)
{
	switch (pItem->GetProdLine())
	{
	case LINE_1:
		Line1.m_pDoc = this;
		Line1.BuildDetails (pItem);
		break;
	case LINE_2:
		Line2.m_pDoc = this;
		Line2.BuildDetails (pItem); 
		break;
	case LINE_3:
		Line3.m_pDoc = this;
		Line3.BuildDetails (pItem);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////
//
void COD3Doc::GetScriptOps(CItem* pItem, int nMemberType)
{
	POSITION pos;
	CElement* pElement;
	CBeamElement* pBeamRecord;

	pos = pItem->m_tplElementList.GetHeadPosition();

	switch(nMemberType)
	{
	case ACCESSORY:
		// Diagonal brace do not use scripts
		break;
	default:
		while(pos)
		{
			pElement = pItem->m_tplElementList.GetNext(pos);
			pElement->m_pDoc = this;
			pElement->m_pItem = pItem;
			pBeamRecord = (CBeamElement*)pElement;

//#ifdef _DEBUG
//    CMemoryState oldMemState, newMemState, diffMemState;
//    oldMemState.Checkpoint();
//#endif
			if (pBeamRecord->GotValidScript(/*pItem,*/ /*this->m_pProjectSettings->m_pDB*/))
			{
				pBeamRecord->ProcessScript(/*pItem,*/ /*this->m_pProjectSettings->m_pDB*/);
//#ifdef _DEBUG
//	newMemState.Checkpoint();
//	if( diffMemState.Difference( oldMemState, newMemState ) )
//	{
//		TRACE( "Memory leaked!\n" );
//		diffMemState.DumpStatistics();
//		diffMemState.DumpAllObjectsSince();
//	}
//#endif
			}
			else
			{
				CString sMark = pElement->GetMark();
				CString sCode = pBeamRecord->GetSPCode();
				CString sMsg = "Script not found for SPC code '"; 
				sMsg += sCode;
				sMsg += "' in element Mark ";
				sMsg += sMark;					

				AfxMessageBox(sMsg,MB_ICONSTOP);
				return;
			}
			if (pBeamRecord->GetNonStandardFlag() != false)
			{
				pItem->SetNonStandardFlag(true);
				return;
			}
			else
			{
				pItem->SetNonStandardFlag(false);
			}
		}
		break;
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CheckDirty() A function to check the status of a boolean flag
//
void COD3Doc::CheckDirty()
{
	if (IsModified() != 0)
	{
		LPCTSTR lpszPathName;
		lpszPathName = GetPathName();
	//	this->OnSaveDocument(lpszPathName);		// save the document
	}
}	


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void COD3Doc::OnProcessAddNewaccessory() 
{
	// TODO: Add your command handler code here
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void COD3Doc::OnProcessDeleteAccessory() 
{
	// TODO: Add your command handler code here
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GetMemberTypeValue()
//
int COD3Doc::GetMemberTypeValue(LPCTSTR lpszType)
{
	int nType;
	CString sType = (CString)lpszType;
	
	if (sType == "001"){nType = PURLIN;}
	else if (sType == "002"){nType = RAIL;}
	else if (sType == "003"){nType = SLEEVE;}
	else if (sType == "004"){nType = STOCK;}
	else if (sType == "007"){nType = SWAGEBEAM;}
	else if (sType == "008"){nType = PRESSED;}
	else if (sType == "000"){nType = ACCESSORY;}
	else if (sType == "009"){nType = STUD;}
	else {return 0;}

	return nType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  GetMemberTypeLabel()
//
CString COD3Doc::GetMemberTypeLabel(int nType)
{
	CString sType;

	switch(nType)
	{
	case PURLIN:
		sType = "Purlin";
		break;
	case RAIL:
		sType = "Rail";
		break;
	case SLEEVE:
		sType = "Sleeve";
		break;
	case STOCK:
		sType = "Stock";
		break;
	case SWAGEBEAM:
		sType = "Swagebeam";
		break;
	case PRESSED:
		sType = "Pressed Section";
		break;
	case ACCESSORY:
		sType = "Accessory";
	case STUD:
		sType = "Stud";
		break;
	}
	return sType;
}

///////////////////////////////////////////////////////////////
//
//
void COD3Doc::SortByItemID(int iType)
{
	POSITION pos;
	CItem* pRecord1;
	CItem* pRecord2;
	bool bModified = false;
	int nItem1;
	int nItem2;


	if(iType==ISBEAM)
	{
start:
		bModified = false;

		//get results head for sort
  		pos =this->m_tplItemList.GetHeadPosition();
  		if(!pos)
  			return;

		//bubble sort 	
  		do
		{
			//get record1	
			pRecord1 =(CItem*)this->m_tplItemList.GetNext(pos);
			nItem1 = pRecord1->GetItemID();
			if(!pos)
				break;
					
			//get record2	
			pRecord2 =(CItem*)this->m_tplItemList.GetNext(pos);
			nItem2 = pRecord2->GetItemID();
				
			//do comparison
			if(nItem1 > nItem2)
  			{
	  			//do swap	
	  	  		this->ItemSwap(pRecord1, pRecord2, ISBEAM);
	  			bModified = true;
  			}

  			pos = this->m_tplItemList.Find(pRecord2);
	  	  		
  		}while(pos);
			
		if(bModified != false)
			goto start;
	}
	else
	{
startACC:
		bModified = false;

		//get results head for sort
  		pos =this->m_tplAccItemList.GetHeadPosition();
  		if(!pos)
  			return;

		//bubble sort 	
  		do
		{
			//get record1	
			pRecord1 =(CItem*)this->m_tplAccItemList.GetNext(pos);
			nItem1 = pRecord1->GetItemID();
			if(!pos)
				break;
					
			//get record2	
			pRecord2 =(CItem*)this->m_tplAccItemList.GetNext(pos);
			nItem2 = pRecord2->GetItemID();
				
			//do comparison
			if(nItem1 > nItem2)
  			{
	  			//do swap	
	  	  		this->ItemSwap(pRecord1, pRecord2, ISACCESSORY);
	  			bModified = true;
  			}

  			pos = this->m_tplAccItemList.Find(pRecord2);
	  	  		
  		}while(pos);
			
		if(bModified != false)
			goto startACC;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//
void COD3Doc::ItemSwap(CItem* pItem1, CItem* pItem2, int iType)
{
	POSITION pos1;
	POSITION pos2;

	if(iType==ISBEAM)
	{
		//remove
		pos1 = this->m_tplItemList.Find(pItem1);
		this->m_tplItemList.RemoveAt(pos1);						  		

		//insert after	 
		pos2 = this->m_tplItemList.Find(pItem2);
		this->m_tplItemList.InsertAfter(pos2, pItem1);	
	}
	else
	{
		// Remove
		pos1 = m_tplAccItemList.Find(pItem1);
		m_tplAccItemList.RemoveAt(pos1);						  		

		// Insert
		pos2 = m_tplAccItemList.Find(pItem2);
		m_tplAccItemList.InsertAfter(pos2, pItem1);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
// CreateBeamDialog()	A function to set up, create and call the modeless beam dialog
//
void COD3Doc::CreateBeamDialog(CItem* pItem, CBeamElement* pBeam, int cElementCounter)
{
	m_pBeamModeless = new CBeamDlg();

	CElement		*pElement=NULL;
	POSITION		pos;

	// Get the head position
	pos = pItem->m_tplElementList.GetHeadPosition();
	while(pos)
	{
		// get the next pos in the list
		pElement = pItem->m_tplElementList.GetNext(pos);

		// Compare mark values
		if(pElement->GetElementID()==cElementCounter)
		{
			// Setup pointers
			pElement->m_pItem = pItem;
			pElement->m_pDoc = this;
			// Found the element
			break;
		}
	}

	m_pBeamModeless->m_pDoc = this;
	m_pBeamModeless->m_pItem = pItem;
	m_pBeamModeless->m_pBeam = pBeam;
	m_pBeamModeless->m_cBeamCounter = cElementCounter;
	m_pBeamModeless->m_pDlg = m_pBeamModeless;
	m_pBeamModeless->Create();
	m_pBeamModeless->ShowWindow(SW_SHOW);

	return;
}

void COD3Doc::CreateBeamDialog(CItem* pItem, CBeamElement* pBeam, CString mark)
{
	bool			found=false;
	int				cElementCounter=-1;
	CElement		*pElement=NULL;
	POSITION		pos;

	m_pBeamModeless = new CBeamDlg();

	// Get the head position
	pos = pItem->m_tplElementList.GetHeadPosition();
	while(pos)
	{
		// get the next pos in the list
		pElement = pItem->m_tplElementList.GetNext(pos);

		// Compare mark values
		if(!pElement->GetMark().Compare(mark))
		{
			// exit from loop
			found=true;
			// Setup pointers
			pElement->m_pItem = pItem;
			pElement->m_pDoc = this;
			// Found the element
			break;
		}
	}

	// Test pointer
	if(found)
	{
		m_pBeamModeless->m_pDoc = this;
		m_pBeamModeless->m_pItem = pItem;
		m_pBeamModeless->m_pBeam = (CBeamElement *)pElement;
		m_pBeamModeless->m_cBeamCounter = pElement->GetElementID();
		m_pBeamModeless->m_pDlg = m_pBeamModeless;
		
		// Create the dialog
		m_pBeamModeless->Create();
		// Show the dialog
		m_pBeamModeless->ShowWindow(SW_SHOW);
	}

	return;
}


/////////////////////////////////////////////////////////////////////////////
// RefreshBeamDialog()	A function to refresh, and call the modeless beam dialog
//
void COD3Doc::RefreshBeamDialog(CItem* pItem, CBeamElement* pBeam, int cElementCounter)
{
	this->m_pBeamModeless->m_pItem = pItem;
	this->m_pBeamModeless->m_pBeam = pBeam;
	this->m_pBeamModeless->m_cBeamCounter = cElementCounter;
	if (cElementCounter/1000 > 1)
	{
		this->m_pBeamModeless->OnRefreshBeam();
	}
	else
	{
		this->m_pBeamModeless->OnNewBeam();
	}
	this->m_pBeamModeless->SetActiveWindow();
}


/////////////////////////////////////////////////////////////////////////////
// OnFileTransfer()		A message handling function to set up file names for transfer of
//						data from hard disk to floppy.
//
void COD3Doc::OnFileTransfer() 
{
	CString		szDocTitle = CDocument::GetPathName();
	POSITION	posItem;
	CItem		*pItem;
	CString		sText, sID;

	// trap case when doc not saved
	if( !szDocTitle.CompareNoCase( "OD3" /*"Untitled"*/ ) )
	{
		return;
	}

	//	step through document's item list
	posItem = this->m_tplItemList.GetHeadPosition();

	while (posItem)
	{
		// Get the next CItem object
		pItem = this->m_tplItemList.GetNext(posItem);

		// Copy the file to the floppy disk
		if(TransferItem(pItem))
		{
			// Create the ink jet file
			if(writeInkJetFile(pItem))
			{
				// Create user information string
				sID.Format("_%i", pItem->GetItemID());
				sText.Format("Transfer complete for item %i\nInkjet file created and saved to A:\\%s.ink",
								pItem->m_nItemID, m_pProjectHeader->m_sProjectName+sID);
			}
			else
			{
				// Create user information string
				sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
			}

			// Inform user
			AfxMessageBox(sText, MB_ICONINFORMATION);
		}
	}

	// Get the head position for the accessories
	posItem = this->m_tplAccItemList.GetHeadPosition();

	while (posItem)
	{
		// Get the next CItem object
		pItem = this->m_tplAccItemList.GetNext(posItem);

		// Copy the file to the floppy disk
		if(TransferItem(pItem))
		{
			// Create the ink jet file
			if(writeInkJetFile(pItem))
			{
				// Create user information string
				sID.Format("_%i", pItem->GetItemID());
				sText.Format("Transfer complete for item %i\nInkjet file created and saved to A:\\%s.ink",
								pItem->m_nItemID, m_pProjectHeader->m_sProjectName+sID);
			}
			else
			{
				// Create user information string
				sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
			}

			// Inform user
			AfxMessageBox(sText, MB_ICONINFORMATION);
		}
	}

	return;
}
//NRC file transfer
/////////////////////////////////////////////////////////////////////////////
// OnFileTransfer2()		A message handling function to set up file names for transfer of
//						data from hard disk to floppy.
//
void COD3Doc::OnFileTransfer2() 
{
	CString		szDocTitle = CDocument::GetPathName();
	POSITION	posItem;
	CItem		*pItem;
	CString		sText, sID;

	// trap case when doc not saved
	if( !szDocTitle.CompareNoCase( "OD3" /*"Untitled"*/ ) )
	{
		return;
	}

	//	step through document's item list
	posItem = this->m_tplItemList.GetHeadPosition();

	while (posItem)
	{
		// Get the next CItem object
		pItem = this->m_tplItemList.GetNext(posItem);

		// Copy the file to the floppy disk
		if(TransferItemb(pItem))
		{
			// Create the ink jet file
			if(writeInkJetFile2(pItem))
			{
				// Create user information string
				sID.Format("_%i", pItem->GetItemID());
				sText.Format("Transfer complete for item %i\nInkjet file created and saved to E:\\%s.ink",
								pItem->m_nItemID, m_pProjectHeader->m_sProjectName+sID);
			}
			else
			{
				// Create user information string
				sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
			}

			// Inform user
			AfxMessageBox(sText, MB_ICONINFORMATION);
		}
	}

	// Get the head position for the accessories
	posItem = this->m_tplAccItemList.GetHeadPosition();

	while (posItem)
	{
		// Get the next CItem object
		pItem = this->m_tplAccItemList.GetNext(posItem);

		// Copy the file to the floppy disk
		if(TransferItemb(pItem))
		{
			// Create the ink jet file
			if(writeInkJetFile2(pItem))
			{
				// Create user information string
				sID.Format("_%i", pItem->GetItemID());
				sText.Format("Transfer complete for item %i\nInkjet file created and saved to e:\\%s.ink",
								pItem->m_nItemID, m_pProjectHeader->m_sProjectName+sID);
			}
			else
			{
				// Create user information string
				sText.Format("Transfer complete for item %i\nInkjet file failed", pItem->m_nItemID);
			}

			// Inform user
			AfxMessageBox(sText, MB_ICONINFORMATION);
		}
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////////////
//	TransferItem()
//
bool COD3Doc::TransferItem(CItem* pItem)
{
	bool		bResult=false;
	POSITION pos;
	POSITION posElement;
	COutputList* pOutputPath;
	CElement* pElement;
	CString szJobFileName = _T("");
	CString szPartFileName =_T("");
	CString szFullFilePath = _T("");
	CString sItemID = _T("");
	CString szLine = _T("");
	CString sListedLine = _T("");
	CString sListedPath = _T("");
	CString szSorcePath = _T("");
	CString szTargetPath = _T("");
	CString szMsg = _T("");
	int iPartIndex, iPos;
	int nItemID = pItem->m_nItemID;
	sItemID.Format("%d",nItemID);

	szMsg = "Insert Disk for Item ";
	szMsg += sItemID;
	szMsg += " into Drive A:\\";

	if(AfxMessageBox(szMsg, MB_OKCANCEL )!=IDOK)
		return(bResult);

	

	if(TestMedia())
	{
		CWaitCursor wait;
		szLine = pItem->GetProdLineLabel();

		if (nItemID > 9 && nItemID < 100)
		{
			sItemID = "0" + sItemID;
		}

		if (nItemID < 10)
		{
			sItemID = "00" + sItemID;
		}

		// get the production line association from the project settings
		pos = this->m_pProjectSettings->m_tplOutputList.GetHeadPosition();

		while (pos)
		{
			pOutputPath = m_pProjectSettings->m_tplOutputList.GetNext(pos);
			pOutputPath->GetOutput(sListedLine,sListedPath);
			if (szLine == sListedLine)
			{
				// re-generate the part file names
				switch (pItem->GetProdLine())
				{
				case LINE_1:
					Line1.m_pDoc = this;
					if (nItemID < 10)
					{
						sItemID.Format("%d",nItemID);
						sItemID = "0" + sItemID;
					}
					else
					{
						sItemID.Format("%d",nItemID);
					}
					Line1.GetPartFileName( &szJobFileName, sItemID);;
					szSorcePath = sListedPath;
					szSorcePath += _T("\\");
					szSorcePath += szJobFileName;
					szTargetPath ="A:\\";
					szTargetPath +=szJobFileName;
					this->CopyPartToDisk(szSorcePath, szTargetPath);
					bResult = true;
					break;
				case LINE_2:
					Line2.m_pDoc = this;
					// special handling for line_2 - separate file for each part!
					posElement = pItem->m_tplElementList.GetHeadPosition();
					iPartIndex = 0; 
					while (posElement)
					{
						pElement = pItem->m_tplElementList.GetNext(posElement);
						iPartIndex ++;
						Line2.GetPartFileName( &szJobFileName, sItemID, iPartIndex );
						szSorcePath = sListedPath;
						szSorcePath += _T("\\");
						szSorcePath += szJobFileName;
						szTargetPath ="A:\\";
						szTargetPath +=szJobFileName;
						this->CopyPartToDisk(szSorcePath, szTargetPath);
						bResult = true;
					}
					break;
				case LINE_3:
					Line3.m_pDoc = this;
					Line3.GetPartFileName( &szJobFileName, sItemID);;
					szSorcePath = sListedPath;
					szSorcePath += _T("\\");
					szSorcePath += szJobFileName;
					szTargetPath ="A:\\";
					szTargetPath +=szJobFileName;
					this->CopyPartToDisk(szSorcePath, szTargetPath);
					bResult = true;
					break;
				case D_BRACE:
					// Get the filename and path
					szSorcePath = createAccFileName(pItem->GetItemID());

					if(szSorcePath.GetLength())
					{
						// Set the target filename and path
						iPos = szSorcePath.ReverseFind('\\');
						szTargetPath.Format("A:\\%s", szSorcePath.Mid(iPos));

						// Copy the file to the floppy disk
						CopyPartToDisk(szSorcePath, szTargetPath);
						bResult = true;
					}
					break;
				}
			}
		}
		wait.Restore();
	}

	return(bResult);
}
//nrc transferitemb  
bool COD3Doc::TransferItemb(CItem* pItem)
{
	bool		bResult=false;
	POSITION pos;
	POSITION posElement;
	COutputList* pOutputPath;
	CElement* pElement;
	CString szJobFileName = _T("");
	CString szPartFileName =_T("");
	CString szFullFilePath = _T("");
	CString sItemID = _T("");
	CString szLine = _T("");
	CString sListedLine = _T("");
	CString sListedPath = _T("");
	CString szSorcePath = _T("");
	CString szTargetPath = _T("");
	CString szMsg = _T("");
	int iPartIndex, iPos;
	int nItemID = pItem->m_nItemID;
	sItemID.Format("%d",nItemID);

	szMsg = "Insert Disk for Item ";
	szMsg += sItemID;
	szMsg += " into Drive E:\\";

	if(AfxMessageBox(szMsg, MB_OKCANCEL )!=IDOK)
		return(bResult);

	

	if(TestMedia2())
	{
		CWaitCursor wait;
		szLine = pItem->GetProdLineLabel();

		if (nItemID > 9 && nItemID < 100)
		{
			sItemID = "0" + sItemID;
		}

		if (nItemID < 10)
		{
			sItemID = "00" + sItemID;
		}

		// get the production line association from the project settings
		pos = this->m_pProjectSettings->m_tplOutputList.GetHeadPosition();

		while (pos)
		{
			pOutputPath = m_pProjectSettings->m_tplOutputList.GetNext(pos);
			pOutputPath->GetOutput(sListedLine,sListedPath);
			if (szLine == sListedLine)
			{
				// re-generate the part file names
				switch (pItem->GetProdLine())
				{
				case LINE_1:
					Line1.m_pDoc = this;
					if (nItemID < 10)
					{
						sItemID.Format("%d",nItemID);
						sItemID = "0" + sItemID;
					}
					else
					{
						sItemID.Format("%d",nItemID);
					}
					Line1.GetPartFileName( &szJobFileName, sItemID);;
					szSorcePath = sListedPath;
					szSorcePath += _T("\\");
					szSorcePath += szJobFileName;
					szTargetPath ="E:\\";
					szTargetPath +=szJobFileName;
					this->CopyPartToDisk(szSorcePath, szTargetPath);
					bResult = true;
					break;
				case LINE_2:
					Line2.m_pDoc = this;
					// special handling for line_2 - separate file for each part!
					posElement = pItem->m_tplElementList.GetHeadPosition();
					iPartIndex = 0; 
					while (posElement)
					{
						pElement = pItem->m_tplElementList.GetNext(posElement);
						iPartIndex ++;
						Line2.GetPartFileName( &szJobFileName, sItemID, iPartIndex );
						szSorcePath = sListedPath;
						szSorcePath += _T("\\");
						szSorcePath += szJobFileName;
						szTargetPath ="E:\\";
						szTargetPath +=szJobFileName;
						this->CopyPartToDisk(szSorcePath, szTargetPath);
						bResult = true;
					}
					break;
				case LINE_3:
					Line3.m_pDoc = this;
					Line3.GetPartFileName( &szJobFileName, sItemID);;
					szSorcePath = sListedPath;
					szSorcePath += _T("\\");
					szSorcePath += szJobFileName;
					szTargetPath ="E:\\";
					szTargetPath +=szJobFileName;
					this->CopyPartToDisk(szSorcePath, szTargetPath);
					bResult = true;
					break;
				case D_BRACE:
					// Get the filename and path
					szSorcePath = createAccFileName(pItem->GetItemID());

					if(szSorcePath.GetLength())
					{
						// Set the target filename and path
						iPos = szSorcePath.ReverseFind('\\');
						szTargetPath.Format("E:\\%s", szSorcePath.Mid(iPos));

						// Copy the file to the floppy disk
						CopyPartToDisk(szSorcePath, szTargetPath);
						bResult = true;
					}
					break;
				}
			}
		}
		wait.Restore();
	}

	return(bResult);
}

/////////////////////////////////////////////////////////////////////////////
// CopyPartToDisk()		A command function to copy data from hard disk to floppy.
//
void COD3Doc::CopyPartToDisk(CString& szSorcePath, CString& szTargetPath)
{
	CFile SourceFile; 	  			 
	CFile TargetFile; 	  			 
			
	if( !SourceFile.Open( szSorcePath, CFile::modeRead|CFile::shareDenyNone ) )
		return; 	  			 

	if( !TargetFile.Open( szTargetPath, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone ) )
		return;

	char szBuffer[64];
	UINT iBytesRead;
	do
	{	
		iBytesRead =SourceFile.Read( &szBuffer, sizeof( szBuffer ) );			   
		TargetFile.Write( &szBuffer, iBytesRead );
	}while( iBytesRead );
}

void COD3Doc::UpdateStatusBar(LPCTSTR lpszText)
{
	CWinApp*	pApp	= pApp = AfxGetApp();
	CMainFrame* pAppWnd = (CMainFrame*)pApp->m_pMainWnd;
	pAppWnd->StatusBarMsgUpdate(lpszText);
}

void COD3Doc::InitProgressIndicator(int nOpCount)
{
/*
	CWinApp* pApp;
	pApp = AfxGetApp();
	CMainFrame* pAppWnd = (CMainFrame*)pApp->m_pMainWnd;

	pAppWnd->m_uiRangeFrom = 0;
	pAppWnd->m_uiRangeTo = 200;
	pAppWnd->m_uiStep = nOpCount/200;
	pAppWnd->CreateProgressIndicator();
*/
}

void COD3Doc::CloseProgressIndicator()
{
/*
	CWinApp* pApp;
	pApp = AfxGetApp();
	CMainFrame* pAppWnd = (CMainFrame*)pApp->m_pMainWnd;

	pAppWnd->CloseProgressIndicator();
*/
}
	
int COD3Doc::GetOpCount()
{
	POSITION itemPos;
	POSITION beamPos;
	CItem* pItem;
	CBeamElement* pBeam;
	int nOpCount = 0;

	itemPos = this->m_tplItemList.GetHeadPosition();

	while (itemPos)
	{
		pItem = this->m_tplItemList.GetNext(itemPos);
		beamPos = pItem->m_tplElementList.GetHeadPosition();
		while (beamPos)
		{
			pBeam = (CBeamElement*)pItem->m_tplElementList.GetNext(beamPos);
			nOpCount += pBeam->m_tplScriptList.GetCount();
			nOpCount += pBeam->m_tplAddList.GetCount();
		}
	}
	return nOpCount;
}

int COD3Doc::GetElementOpCount(CItem* pItem)
{
	POSITION beamPos;
	CBeamElement* pBeam;
	int nOpCount = 0;

	beamPos = pItem->m_tplElementList.GetHeadPosition();
	while (beamPos)
	{
		pBeam = (CBeamElement*)pItem->m_tplElementList.GetNext(beamPos);
		nOpCount += pBeam->m_tplScriptList.GetCount();
		nOpCount += pBeam->m_tplAddList.GetCount();
	}
	return nOpCount;
}

void COD3Doc::storeMirrorAsso()
{
	CAssociation	*assoPtr=NULL, *walker=NULL;
	POSITION		pos, walkerPos;

	
	// Delete memory
	removeMirror();

	// Get the head pos
	walkerPos = m_pProjectSettings->m_tplAssociationList.GetHeadPosition();
	if(walkerPos)
		walker = m_pProjectSettings->m_tplAssociationList.GetAt(walkerPos);

	while(walkerPos)
	{
		// Create new object
		assoPtr = new CAssociation;
		// Set object members
		assoPtr->SetMill(walker->GetMill());
		assoPtr->SetRollSet(walker->GetRollSet());
		// Add object to pointer array
		if(m_tplMirror.GetCount()==0)
			pos = m_tplMirror.AddHead(assoPtr);
		else
			pos = m_tplMirror.InsertAfter(pos, assoPtr);

		// Get the nect object
		m_pProjectSettings->m_tplAssociationList.GetNext(walkerPos);
		if(walkerPos)
			walker = m_pProjectSettings->m_tplAssociationList.GetAt(walkerPos);
	}
	

	return;
}

void COD3Doc::removeMirror()
{
	CAssociation	*assoPtr=NULL, *walker=NULL;
	POSITION		pos;


	if(m_tplMirror.GetCount())
	{
		// Get the head pos
		pos = m_tplMirror.GetHeadPosition();
		assoPtr = m_tplMirror.GetAt(pos);

		while(pos)
		{
			// Free allocated memory
			delete assoPtr;
			// Clean pointer
			assoPtr = NULL;

			// Get the next object
			m_tplMirror.GetNext(pos);

			// Get next pointer
			if(pos)
				assoPtr = m_tplMirror.GetAt(pos);
		}
		
		// Release pointers
		m_tplMirror.RemoveAll();
	}

	return;
}

bool COD3Doc::compareMirrorAsso()
{
	bool			result=false;
	CAssociation	*assoPtr=NULL, *walker=NULL;
	POSITION		mirrorPos, walkerPos;


	// Get the head pos for the mirror
	mirrorPos = m_tplMirror.GetHeadPosition();
	if(mirrorPos)
		assoPtr = m_tplMirror.GetAt(mirrorPos);

	while(mirrorPos && !result)
	{
		// Get the head pos for the current associations
		walkerPos = m_pProjectSettings->m_tplAssociationList.GetHeadPosition();
		if(walkerPos)
			walker = m_pProjectSettings->m_tplAssociationList.GetAt(walkerPos);

		// Get stored mirror data
		assoPtr->GetMill();
		assoPtr->GetRollSet();

		// Loop stored associations searching for differences
		while(walkerPos)
		{
			if(!walker->GetRollSet().CompareNoCase(assoPtr->GetRollSet()) )
			{
				if(walker->GetMill().CompareNoCase(assoPtr->GetMill()) )
				{
					// Mill has changed for this product
					result=true;
				}
				// Product found break loop
				break;
			}
			// Get the next pointer
			m_pProjectSettings->m_tplAssociationList.GetNext(walkerPos);
			// Get the item pointer
			if(walkerPos)
				walker = m_pProjectSettings->m_tplAssociationList.GetAt(walkerPos);
		}
		// Get the next mirror pointer
		m_tplMirror.GetNext(mirrorPos);
		if(mirrorPos)
			assoPtr = m_tplMirror.GetAt(mirrorPos);
	}


	return(result);
}

bool COD3Doc::testForManualHashCodes()
{
	bool			result=false;
	POSITION		itemPos, elementPos, beamOpsPos;
	CItem			*pItem=NULL;
	CBeamElement	*pElement=NULL;
	CBeamOps		*pBeamOp=NULL;

	// Get the head item pos
	itemPos=m_tplItemList.GetHeadPosition();
	if(itemPos)
		pItem=m_tplItemList.GetAt(itemPos);

	// Loop through all items
	while(itemPos && !result)
	{
		// Get the head element pos
		elementPos=pItem->m_tplElementList.GetHeadPosition();
		if(elementPos)
			pElement=(CBeamElement *)pItem->m_tplElementList.GetAt(elementPos);

		// Loop through all element
		while(elementPos && !result)
		{
			// Get the additional holes head pos
			if( (beamOpsPos=pElement->m_tplAddList.GetHeadPosition()) )
			{
				pBeamOp=pElement->m_tplAddList.GetAt(beamOpsPos);

				// Loop through all additional holes
				while(beamOpsPos && !result)
				{
					if(!pBeamOp->GetOpType().CompareNoCase(_T("Punch")))
					{
						if(!pBeamOp->GetOperation().Left(1).CompareNoCase(_T("#")))
						{
							// Hash code is present
							result=true;
						}
					}

					// Move to next hole
					pElement->m_tplAddList.GetNext(beamOpsPos);
					if(beamOpsPos)
						pBeamOp=pElement->m_tplAddList.GetAt(beamOpsPos);
				}
			}

			// Move to next element
			pItem->m_tplElementList.GetNext(elementPos);
			if(elementPos)
				pElement=(CBeamElement *)pItem->m_tplElementList.GetAt(elementPos);
		}
		
		// Get the next item
		m_tplItemList.GetNext(itemPos);
		if(itemPos)
			pItem=m_tplItemList.GetAt(itemPos);
	}


	return(result);
}

// Import ASW file type ///////////////////////////////////////////
void COD3Doc::OnImportAsw() 
{
	// TODO: Add your command handler code here
	CImportAswFile	aswImport(this);	

	aswImport.importFile();

	return;
}

bool COD3Doc::TestMedia()
{
	bool		result=true;
	CFileFind	fileData;

	// Test for readonly
	try
	{
		CFile file(_T("A:\\tmp"), CFile::modeCreate);

		// Close the file
		file.Close();

		// Delete temp file
		_unlink(_T("A:\\tmp"));
	}
	catch(CFileException *e)
	{
		if(e->m_lOsError==19)
			AfxMessageBox(IDS_DISKREADONLY, MB_ICONWARNING);

		else if(e->m_lOsError==21)
			AfxMessageBox(IDS_DISKMISSING, MB_ICONWARNING);

		else
			e->ReportError(MB_ICONWARNING);

		// Delete the file exception
		e->Delete();

		// Set failure flag
		result = false;
	}
	
	// Search for any files
	if(result && fileData.FindFile(_T("A:\\*.*"), 0))
	{
		if(AfxMessageBox(IDS_WARNDIRTY, MB_YESNO|MB_ICONQUESTION) == IDNO)
		{
			// Close file
			fileData.Close();
			// Return with no clean
			return(result);
		}

		// Change to the hour glass cursor
		CWaitCursor	wait;

		// Loop through files
		while(fileData.FindNextFile())
		{
			// Delete the file / directory
			removeFile(&fileData);
		}
		// Delete the file / directory
		removeFile(&fileData);

		// Release file
		fileData.Close();

		// Remove the wait cursor
		wait.Restore();
	}
	

	// Test media for any remaining items
	if(result && fileData.FindFile(_T("A:\\*.*"), 0))
	{
		// Inform user about dirty media
		AfxMessageBox(IDS_MEDIANOTCLEAN, MB_ICONERROR);
		// Set failure flag
		result = false;
	}

	return(result);
}
//test2
bool COD3Doc::TestMedia2()
{
	bool		result=true;
	CFileFind	fileData;

	// Test for readonly
	try
	{
		CFile file(_T("E:\\tmp"), CFile::modeCreate);

		// Close the file
		file.Close();

		// Delete temp file
		_unlink(_T("E:\\tmp"));
	}
	catch(CFileException *e)
	{
		if(e->m_lOsError==19)
			AfxMessageBox(IDS_DISKREADONLY, MB_ICONWARNING);

		else if(e->m_lOsError==21)
			AfxMessageBox(IDS_DISKMISSING, MB_ICONWARNING);

		else
			e->ReportError(MB_ICONWARNING);

		// Delete the file exception
		e->Delete();

		// Set failure flag
		result = false;
	}
	
	// Search for any files
	if(result && fileData.FindFile(_T("E:\\*.*"), 0))
	{
		if(AfxMessageBox(IDS_WARNDIRTY, MB_YESNO|MB_ICONQUESTION) == IDNO)
		{
			// Close file
			fileData.Close();
			// Return with no clean
			return(result);
		}

		// Change to the hour glass cursor
		CWaitCursor	wait;

		// Loop through files
		while(fileData.FindNextFile())
		{
			// Delete the file / directory
			removeFile(&fileData);
		}
		// Delete the file / directory
		removeFile(&fileData);

		// Release file
		fileData.Close();

		// Remove the wait cursor
		wait.Restore();
	}
	

	// Test media for any remaining items
	if(result && fileData.FindFile(_T("E:\\*.*"), 0))
	{
		// Inform user about dirty media
		AfxMessageBox(IDS_MEDIANOTCLEAN, MB_ICONERROR);
		// Set failure flag
		result = false;
	}

	return(result);
}





void COD3Doc::removeFile(CFileFind *file)
{
	CFileFind	newSearch;
	CString h;

	if(file->IsDirectory())
	{
		// Process directory
		CString tmp = file->GetFilePath()+_T("\\");
		// Change to directory and loop file
		if(newSearch.FindFile(file->GetFilePath()+_T("\\*.*"), 0))
		{
			while(newSearch.FindNextFile())
			{
				if(!newSearch.IsDots())
					removeFile(&newSearch);
			}

			removeFile(&newSearch);

			// Release file find
			newSearch.Close();
			// Delete empty directory
			_rmdir(file->GetFilePath());
		}
	}
	else
	{
		// Delete file
		unlink(file->GetFilePath());
	}

	return;
}

bool COD3Doc::writeInkJetFile(CItem *pItem)
{
	POSITION			pos;
	CString				fileName = _T("A:\\"), sText, sID;
	CBeamElement		*pBeam=NULL;
	bool				bResult=false;
	CAccessoryElement	*pAcc=NULL;

	
	// Creat the file name
	sID.Format("_%i", pItem->GetItemID());
	fileName += m_pProjectHeader->m_sProjectName + sID + _T(".ink");

	// Create a new ink file
	try
	{
		// Create the new ink file
		CStdioFile file(fileName, CFile::modeCreate|CFile::modeWrite);

		// Show the hourglass cursor
		CWaitCursor	wait;

		// Write details to the file
		file.WriteString(m_pProjectHeader->m_sCustomerName + "\n");
		file.WriteString(m_pProjectHeader->m_sCustomerRef + "\n");
		file.WriteString(m_pProjectHeader->m_sProjectName + "\n");

		if(pItem->IsBeam())
		{
			// Test manufacturing line
			switch(pItem->GetProdLine())
			{
				case 1:
				case 2:					
					// Write section and profile to disk
					sText = pItem->m_sSectionID;
					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					// Test if this is a press section
					if(pItem->GetType() == PRESSED)
					{
						// Convert string type to Zeta 2/225
						sText = _T("2/225");
					}

					file.WriteString(sText + "\n");


					sText = pItem->m_sProfile;
					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					file.WriteString(sText + "\n");
					break;

				case 3:
					// Write section and profile to disk

					// Remove the char '/' from the string
					sText = pItem->m_sSectionID;
					sText.Replace("/", "");

					// Remove the last char (if W for Wernick)
					if(!sText.Right(1).Compare("W"))
						sText = sText.Mid(0, sText.GetLength()-1);

					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					// Test if this is a press section
					if(pItem->GetType() == PRESSED)
					{
						// Convert string type to Zeta 2/225
						sText = _T("2225");
					}

					file.WriteString(sText + "\n");
					// Remove the char '/' from the string
					sText = pItem->m_sProfile;
					sText.Replace("/", "");
					// Remove the last char (if W for Wernick)
					if(!sText.Right(1).Compare("W"))
						sText = sText.Mid(0, sText.GetLength()-1);

					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					file.WriteString(sText + "\n");
					break;
			}
		}
		else
		{
			// Write section and profile to disk
			file.WriteString("DIAGONAL BRACE\n");
			file.WriteString(_T("BRACE\n"));
		}


		// Write the bundle count
		if(pItem->m_tplElementList.GetCount())
		{
			if(pItem->IsBeam())
			{
				pBeam = (CBeamElement *)pItem->m_tplElementList.GetHead();
				sText.Format("%i\n", pBeam->GetBundle());
			}
			else
			{
				pAcc = (CAccessoryElement *)pItem->m_tplElementList.GetHead();
				sText.Format("%i\n", pAcc->GetBundle());
			}
		}
		else
		{
			// Default to 1 bundle count
			sText.Format("%i\n", 1);
		}

		file.WriteString(sText);
		sText.Format("%i\n", pItem->m_tplElementList.GetCount());
		file.WriteString(sText);
		
		// Get the head position
		pos = pItem->m_tplElementList.GetHeadPosition();

		while(pos)
		{
			// Get the next beam object
			pBeam = (CBeamElement *)pItem->m_tplElementList.GetNext(pos);

			// Write data to file
			if(pItem->IsBeam())
			{
				sText.Format("%i\n", pBeam->GetLength());
			}
			else
			{
				pAcc = (CAccessoryElement *)pBeam;
				sText.Format("%i\n", pAcc->GetLength());
			}
			file.WriteString(sText);

			sText.Format("%i\n", pBeam->GetQty());
			file.WriteString(sText);
			sText.Format("%s\n", pBeam->GetMark());
			file.WriteString(sText);
		}

		// Close the file
		file.Close();

		// Set return flag
		bResult = true;

		// Return to normal cursor
		wait.Restore();
	}
	catch(CFileException *e)
	{
		// Report file exception
		e->ReportError(MB_ICONWARNING);
		// Delete the exception
		e->Delete();
	}
	
	return(bResult);
}
//NRC
bool COD3Doc::writeInkJetFile2(CItem *pItem)
{
	POSITION			pos;
	CString				fileName = _T("E:\\"), sText, sID;
	CBeamElement		*pBeam=NULL;
	bool				bResult=false;
	CAccessoryElement	*pAcc=NULL;

	
	// Creat the file name
	sID.Format("_%i", pItem->GetItemID());
	fileName += m_pProjectHeader->m_sProjectName + sID + _T(".ink");

	// Create a new ink file
	try
	{
		// Create the new ink file
		CStdioFile file(fileName, CFile::modeCreate|CFile::modeWrite);

		// Show the hourglass cursor
		CWaitCursor	wait;

		// Write details to the file
		file.WriteString(m_pProjectHeader->m_sCustomerName + "\n");
		file.WriteString(m_pProjectHeader->m_sCustomerRef + "\n");
		file.WriteString(m_pProjectHeader->m_sProjectName + "\n");

		if(pItem->IsBeam())
		{
			// Test manufacturing line
			switch(pItem->GetProdLine())
			{
				case 1:
				case 2:					
					// Write section and profile to disk
					sText = pItem->m_sSectionID;
					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					// Test if this is a press section
					if(pItem->GetType() == PRESSED)
					{
						// Convert string type to Zeta 2/225
						sText = _T("2/225");
					}

					file.WriteString(sText + "\n");


					sText = pItem->m_sProfile;
					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					file.WriteString(sText + "\n");
					break;

				case 3:
					// Write section and profile to disk

					// Remove the char '/' from the string
					sText = pItem->m_sSectionID;
					sText.Replace("/", "");

					// Remove the last char (if W for Wernick)
					if(!sText.Right(1).Compare("W"))
						sText = sText.Mid(0, sText.GetLength()-1);

					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					// Test if this is a press section
					if(pItem->GetType() == PRESSED)
					{
						// Convert string type to Zeta 2/225
						sText = _T("2225");
					}

					file.WriteString(sText + "\n");
					// Remove the char '/' from the string
					sText = pItem->m_sProfile;
					sText.Replace("/", "");
					// Remove the last char (if W for Wernick)
					if(!sText.Right(1).Compare("W"))
						sText = sText.Mid(0, sText.GetLength()-1);

					if(!sText.Left(3).Compare(_T("SBE")))
						// Remove SBE reference
						sText = sText.Mid(3, sText.GetLength()-3);

					file.WriteString(sText + "\n");
					break;
			}
		}
		else
		{
			// Write section and profile to disk
			file.WriteString("DIAGONAL BRACE\n");
			file.WriteString(_T("BRACE\n"));
		}


		// Write the bundle count
		if(pItem->m_tplElementList.GetCount())
		{
			if(pItem->IsBeam())
			{
				pBeam = (CBeamElement *)pItem->m_tplElementList.GetHead();
				sText.Format("%i\n", pBeam->GetBundle());
			}
			else
			{
				pAcc = (CAccessoryElement *)pItem->m_tplElementList.GetHead();
				sText.Format("%i\n", pAcc->GetBundle());
			}
		}
		else
		{
			// Default to 1 bundle count
			sText.Format("%i\n", 1);
		}

		file.WriteString(sText);
		sText.Format("%i\n", pItem->m_tplElementList.GetCount());
		file.WriteString(sText);
		
		// Get the head position
		pos = pItem->m_tplElementList.GetHeadPosition();

		while(pos)
		{
			// Get the next beam object
			pBeam = (CBeamElement *)pItem->m_tplElementList.GetNext(pos);

			// Write data to file
			if(pItem->IsBeam())
			{
				sText.Format("%i\n", pBeam->GetLength());
			}
			else
			{
				pAcc = (CAccessoryElement *)pBeam;
				sText.Format("%i\n", pAcc->GetLength());
			}
			file.WriteString(sText);

			sText.Format("%i\n", pBeam->GetQty());
			file.WriteString(sText);
			sText.Format("%s\n", pBeam->GetMark());
			file.WriteString(sText);
		}

		// Close the file
		file.Close();

		// Set return flag
		bResult = true;

		// Return to normal cursor
		wait.Restore();
	}
	catch(CFileException *e)
	{
		// Report file exception
		e->ReportError(MB_ICONWARNING);
		// Delete the exception
		e->Delete();
	}
	
	return(bResult);
}
//// end NRC

bool COD3Doc::GenerateAccItem(CItem *pItem)
{
	CAccessoryElement	*pAcc=NULL;
	bool				bResult=false;
	POSITION			pos;
	CString				sPath, sText;
	CStdioFile			file;
	int					iCount=1, iOffset;
	CDaoAccOffset		daoOffset(m_pProjectSettings->m_pDB);

	// Validate the elements
	if(ValidateAccItem(pItem))
	{
		// Create the file name and path
		sPath = createAccFileName(pItem->GetItemID());

		if(sPath.GetLength())
		{
			try
			{
				// Create the file
				file.Open(sPath, CFile::modeCreate|CFile::modeWrite);

				// Set search criteria
				daoOffset.m_prod_code = pItem->GetProductCode();

				// Open the recordset
				daoOffset.Open();

				if(daoOffset.GetRecordCount() > 0)
				{
					// Set offset
					iOffset = (int)daoOffset.m_offset;
					// Close recordaset
					daoOffset.Close();
				}
				else
				{
					iOffset = 0;
				}
				// Write the order number
				sText.Format("%s\n", this->GetTitle());
				file.WriteString(sText);

				// Write item data to the file
				sText.Format("[%s]\n", pItem->GetProductName());
				file.WriteString(sText);

				// Get the head position of the elements
				pos = pItem->m_tplElementList.GetHeadPosition();

				while(pos)
				{
					// Get the next accessory object
					pAcc = (CAccessoryElement *)pItem->m_tplElementList.GetNext(pos);

					// Write quantity to the file
					sText.Format("%i,", pAcc->GetQty());
					file.WriteString(sText);

					// Write length to the file
					sText.Format("%i,", pAcc->GetLength()+iOffset);
					file.WriteString(sText);

					// Write mark to the file
					sText.Format("%s\n", pAcc->GetMark());
					file.WriteString(sText);
				}

				// Close the file
				file.Close();

				// Set return flag
				bResult=true;
			}
			catch(CFileException *e)
			{
				// Report file error
				e->ReportError(MB_OK);
				// Delete exception
				e->Delete();
			}
		}
		else
		{
			// Path not setup
			AfxMessageBox(IDS_DB_PATHMISSING, MB_OK|MB_ICONINFORMATION);
			// Open the dialog
			m_pProjectSettings->OnOpenSysconfig();
		}
	}

	return(bResult);
}

bool COD3Doc::ValidateAccItem(CItem *pItem)
{
	CAccessoryElement	*pAcc=NULL;
	bool				bResult=true;
	POSITION			pos;
	CString				sText;

	
	// Get the head position of the elements
	pos = pItem->m_tplElementList.GetHeadPosition();

	while(pos)
	{
		// Get the next accessory object
		pAcc = (CAccessoryElement *)pItem->m_tplElementList.GetNext(pos);

		// Test valid length
		if(pAcc->GetLength() < 100 || pAcc->GetLength() > 6000)
		{
			// Format the text to inform the user
			sText.Format(IDS_VAL_LENGTH, pAcc->GetLength(), pItem->GetProductName(), pAcc->GetMark());
			AfxMessageBox(sText, MB_ICONINFORMATION);

			// Set return flag
			bResult=false;

			break;
		}

		// Test valid quantity
		if(pAcc->GetQty() <= 0)
		{
			// Format the text to inform the user
			sText.Format(IDS_VAL_QUANTITY, pAcc->GetQty(), pItem->GetProductName(), pAcc->GetMark());
			AfxMessageBox(sText, MB_ICONINFORMATION);

			// Set return flag
			bResult=false;
			break;
		}

	}


	return(bResult);
}


CString COD3Doc::createAccFileName(int iItemNum)
{
	CString		sPath, sOutputPath;
	COutputList	*pList=NULL;
	POSITION	pos;


	// Get the head position for the ouput file paths
	pos = m_pProjectSettings->m_tplOutputList.GetHeadPosition();

	while(pos)
	{
		// Get the next output path
		pList = m_pProjectSettings->m_tplOutputList.GetNext(pos);

		// Test the line for diagonal brace
		if(!pList->m_sPLine.CompareNoCase(_T("Diagonal_Brace")))
			break;
		else
			pList=NULL;
	}
	
	if(pList)
	{
		// Set the path and file name
		sPath.Format("%s\\%s_%i.acc",
							pList->m_sPath,
							m_pProjectHeader->m_sProjectName,
							iItemNum);
	}
	

	return(sPath);
}

void COD3Doc::OnExportD3() 
{
	CImportDet3		d3File;
	CImportD3Beam	oBeam;
	CImportD3Acc	oAcc;
	CBeamElement	*pBeamEle=NULL;
	CAccessoryElement	*pAcc=NULL;
	CBigIni			*fp=NULL;
	CString			sFileName, sText, sType, sGroup;
	POSITION		itemPos, elePos;
	CItem			*pItem=NULL;
	CElement		*pElement=NULL;
	int				iCount=0;
	CTime			date = CTime::GetCurrentTime();
	CString	sDefaultDir(_T(""));
	LPSTR	lpstrDefaultDir;
	DWORD	flags = OFN_OVERWRITEPROMPT|
					OFN_HIDEREADONLY|
     				OFN_PATHMUSTEXIST|
					OFN_SHAREWARN;


	lpstrDefaultDir = sDefaultDir.GetBuffer(1);

	CFileDialog dlgOpen(false, "d3", m_pProjectHeader->m_sProjectName, flags,
							"Ayrshire Detail 3 (*.d3)|*.d3||",
							AfxGetApp()->m_pMainWnd);

	// Set default directory
	dlgOpen.m_ofn.lpstrInitialDir = lpstrDefaultDir;


	// Open common dialog
	if (dlgOpen.DoModal() == IDOK)
	{
		sFileName = dlgOpen.GetPathName();

		// Create the D3 file for writing
		fp = new CBigIni(dlgOpen.GetPathName(), 1);

		// Get the head position for the beam items
		itemPos = m_tplItemList.GetHeadPosition();


		if(itemPos)
		{
			// Set header details
			d3File.SetJobNO(m_pProjectHeader->m_sProjectName);
			d3File.SetReleaseType("OD3_STREAMLINE");
			d3File.SetFile(dlgOpen.GetFileName());
			sText.LoadString(IDS_SOFTWARE_VERSION);
			d3File.SetVersionNo(sText);
			sText.Format("%i/%i/%i", date.GetDay(), date.GetMonth(), date.GetYear());
			d3File.SetModifiedDate(sText);

			// Write the d3 header details
			d3File.WriteD3Header(*fp);
		}

		while(itemPos)
		{
			// Get the next object
			pItem = m_tplItemList.GetNext(itemPos);

			sText = pItem->GetProfile();
			// Set the beam item data
			oBeam.SetProductName(sText.GetBuffer(1));

			// Set group and type
			setGroupType(sText, sType, sGroup);
			

			oBeam.SetSectionType(sType);
			oBeam.SetProductGroup(sGroup.GetBuffer(1));

			switch(pItem->GetType())
			{
			case 1:
				sText=_T("PURLIN");
				break;

			case 2:
				sText=_T("RAIL");
				break;

			case 3:
				sText=_T("SLEEVES");
				break;

			case 4:
				sText=_T("STOCK PURLIN");
				break;

			case 7:
				oBeam.SetSectionType("Swagebeam");
				oBeam.SetProductGroup("SWAGEBEAM");
				sText=_T("SWAGEBEAM");
				break;

			case 8:
				oBeam.SetSectionType("Press");
				oBeam.SetProductGroup("PRESS");
				sText=_T("PRESSED");
				break;
			}
			oBeam.SetProductType(sText.GetBuffer(1));

			oBeam.SetSectionSize(pItem->GetProfile());
			oBeam.SetDateToday();
			

			// Get the head position for elements
			elePos = pItem->m_tplElementList.GetHeadPosition();

			while(elePos)
			{
				// Get the next object
				pElement = pItem->m_tplElementList.GetNext(elePos);
				pBeamEle = (CBeamElement *)pElement;

				oBeam.SetMark(pElement->GetMark().GetBuffer(1));
				oBeam.SetQty(pElement->GetQty());
				oBeam.SetSlope(pBeamEle->GetEBSlope());
				oBeam.SetSPC(pBeamEle->GetSPCode());
				oBeam.SetLength(pBeamEle->GetLength());

				// Write to the d3 file
				oBeam.Write(*fp, iCount++);
			}
		}


		// Get the head position for the beam items
		itemPos = m_tplAccItemList.GetHeadPosition();
		iCount=0;

		// Accessories
		while(itemPos)
		{
			// Get the next object
			pItem = m_tplAccItemList.GetNext(itemPos);

			sText = pItem->GetSectionID();
			// Set group and type
			setGroupType(sText, sType, sGroup);

			// Set the beam item data
			oAcc.SetSectionType(sType.GetBuffer(1));
			oAcc.SetSectionSize(pItem->GetSectionID().GetBuffer(1));
			oAcc.SetProductName(pItem->GetProductName().GetBuffer(1));
			oAcc.SetProductType(_T("BRACING"));
			

			// Get the head position for elements
			elePos = pItem->m_tplElementList.GetHeadPosition();

			while(elePos)
			{
				// Get the next object
				pElement = pItem->m_tplElementList.GetNext(elePos);
				pAcc = (CAccessoryElement *)pElement;

				oAcc.SetMark(pAcc->GetMark().GetBuffer(1));
				oAcc.SetQty(pAcc->GetQty());
				oAcc.SetSleeveLength(pAcc->GetLength());
				oAcc.SetField1(pAcc->GetField1());
				oAcc.SetField2(pAcc->GetField2());
				oAcc.SetField3(pAcc->GetField3());
				oAcc.SetField4(pAcc->GetField4());
				oAcc.SetField5(pAcc->GetField5());

				// Write to the d3 file
				oAcc.Write(*fp, iCount++);
			}
		}

		delete fp;
	}

	return;
}

void COD3Doc::setGroupType(CString sSearch, CString &sType, CString &sGroup)
{

	if(sSearch.Find("1/", 0) == 0 || sSearch.Find("SBE1/", 0) == 0)
	{
		// Zeta 1
		sType = _T("ZETA1");
		sGroup = _T("Zeta 1");
	}
	else if(sSearch.Find("2/", 0) == 0 || sSearch.Find("SBE2/", 0) == 0)
	{
		// Zeta 2
		sType = _T("ZETA2");
		sGroup = _T("Zeta 2");
	}
	else if(sSearch.Find("Z/", 0) == 0 || sSearch.Find("SBEZ/", 0) == 0)
	{
		// Zed
		sType = _T("ZED");
		sGroup = _T("Zed");
	}
	else if(sSearch.Find("EB", 0) == 0 || sSearch.Find("SBEEB", 0) == 0)
	{
		// Eaves beam
		sType = _T("EAVES BEAM");
		sGroup = _T("Eaves beam");
	}
	else if(sSearch.Find("CS", 0) == 0 || sSearch.Find("CR", 0) == 0 || 
				sSearch.Find("UR", 0) == 0)
	{
		// ASF sections
		sType = _T("STUD");
		sGroup = _T("Stud");
	}
	else if(sSearch.Find("C", 0) == 0 || sSearch.Find("SBEC", 0) == 0)
	{
		// Cee sections
		sType = _T("CEE");
		sGroup = _T("Cee");
	}
	else if(sSearch.Find("3/", 0) == 0 || sSearch.Find("SBE3/", 0) == 0)
	{
		// Zeta 3
		sType = _T("ZETA3");
		sGroup = _T("Zeta 3");
	}
	else if(sSearch.Find("SB2", 0) == 0 || sSearch.Find("SB3", 0) == 0)
	{
		// Swagebeam
		sType = _T("SWAGEBEAM");
		sGroup = _T("Swagebeam");
	}


	return;
}

void COD3Doc::OnUpdateExportD3(CCmdUI* pCmdUI) 
{
	// Disable d3 export function in version 2.5.6
	pCmdUI->Enable(false);	
}

void COD3Doc::OnPrintSummary() 
{
	CPrintDialog	print(false);
	DOCINFO			docInfo;
	int				iTop = 100, iLeft = 100, iRight = 100, iBottom = 100;
	int				xMax,yMax, yPos=iTop, xPos=0, oldMap, iColMargin=A4_X/3;
	int				iWeightMargin = A4_X - (A4_X/3);
	int				iCompleteMargin=iWeightMargin+iLeft*2;
	CSize			oldWindow, oldView, txSz;
	CDC				dcMem, printerDC;
	CFont			*pOldFont=NULL, titleFont, headFont, detailFont;
	LOGFONT			lFont;
	CString			sText;
	POSITION		itemPos, elementPos;
	CItem			*pItem = NULL;
	CElement		*pElement;
	CBeamElement	*pBeam=NULL;
	CAccessoryElement	*pAcc=NULL;
	float			fWeight, fLength, fTotalWeight=0.0f, fGrandTotal=0.0f;
	int				iPageNum = 1;
	bool			bPrintBeam=false, bPrintAcc=false;


	// Open common print dialog
	if(print.DoModal()==IDOK)
	{
		// Get the printer device
		HDC dc = print.GetPrinterDC();

		// Attach printer DC to CDC object
		printerDC.Attach(dc);

		// Get device area
		yMax = printerDC.GetDeviceCaps(VERTRES);
		xMax = printerDC.GetDeviceCaps(HORZRES);

		// Scale view to suit
		oldMap = printerDC.SetMapMode(MM_ISOTROPIC);
		oldWindow = printerDC.SetWindowExt(A4_X, A4_Y);
		oldView = printerDC.SetViewportExt(xMax, yMax);

		// Clean struct
		ZeroMemory(&docInfo, sizeof(DOCINFO));

		// Set up printing structure
		docInfo.cbSize=sizeof(DOCINFO);
		docInfo.lpszDocName = "Summary Print";
		docInfo.lpszOutput = NULL;
		docInfo.fwType = NULL;

		// Start the document
		printerDC.StartDoc(&docInfo);
		// Start the page
		printerDC.StartPage();

// Commented out to use standard print
#if 0
		// Create fonts
		titleFont.CreatePointFont(210, "Arial", &printerDC);
		titleFont.GetLogFont(&lFont);
		titleFont.DeleteObject();
		lFont.lfWeight = FW_BOLD;
		lFont.lfUnderline = false;
		titleFont.CreateFontIndirect(&lFont);

		headFont.CreatePointFont(180, "Arial", &printerDC);
		headFont.GetLogFont(&lFont);
		headFont.DeleteObject();
		headFont.CreateFontIndirect(&lFont);

		detailFont.CreatePointFont(120, "Arial", &printerDC);
		detailFont.GetLogFont(&lFont);
		detailFont.DeleteObject();
		lFont.lfWeight = FW_NORMAL;
		detailFont.CreateFontIndirect(&lFont);

		// Print title
		pOldFont = printerDC.SelectObject(&titleFont);
		sText.LoadString(IDS_SUMMARYTITLE);
		// Get the text size
		txSz = printerDC.GetTextExtent(sText);

		printerDC.TextOut(iLeft/*(A4_X/2)-(txSz.cx/2)*/, yPos, sText);
		yPos += txSz.cy*2;
		
		// Release font
		printerDC.SelectObject(pOldFont);

		// Print headers
		pOldFont = printerDC.SelectObject(&headFont);
		// Get text size for height
		txSz = printerDC.GetTextExtent(sText);

		// Job number
		sText = _T("Job Number:");
		printerDC.TextOut(iLeft, yPos, sText);
		printerDC.TextOut(iColMargin, yPos, m_pProjectHeader->m_sProjectName);
		yPos += txSz.cy;

		// Customer
		sText = _T("Customer:");
		printerDC.TextOut(iLeft, yPos, sText);
		printerDC.TextOut(iColMargin, yPos, m_pProjectHeader->m_sCustomerName);
		yPos += txSz.cy;

		// Customer Order number
		sText = _T("Customer Ref:");
		printerDC.TextOut(iLeft, yPos, sText);
		printerDC.TextOut(iColMargin, yPos, m_pProjectHeader->m_sCustomerRef);
		yPos += txSz.cy;

		// Due date
		sText = _T("Due Date:");
		printerDC.TextOut(iLeft, yPos, sText);
		printerDC.TextOut(iColMargin, yPos, m_pProjectHeader->m_sDueDate);
		yPos += txSz.cy*4;

		// Release font
		printerDC.SelectObject(pOldFont);

		// Loop beams
		itemPos = m_tplItemList.GetHeadPosition();

		// Select detail font
		pOldFont = printerDC.SelectObject(&detailFont);

		if(itemPos)
		{
			// Output table headers
			printerDC.TextOut(iLeft, yPos, _T("Item"));
			printerDC.TextOut(iLeft*3, yPos, _T("Section"));
			txSz = printerDC.GetTextExtent(_T("Tonnage"));
			printerDC.TextOut(iWeightMargin-txSz.cx, yPos, _T("Tonnage"));
			printerDC.TextOut(iCompleteMargin, yPos, _T("Complete"));
			yPos += txSz.cy;

			// Set beams total printing
			bPrintBeam=true;
		}

		while(itemPos)
		{
			// Get the item object
			pItem = m_tplItemList.GetNext(itemPos);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);
			
			// Item number
			sText.Format("%i", pItem->GetItemID());
			printerDC.TextOut(iLeft, yPos, sText);

			// Send section name to printer
			printerDC.TextOut(iLeft*3, yPos, pItem->GetProductName());

			// Loop all elements
			elementPos = pItem->m_tplElementList.GetHeadPosition();

			// Clear weight
			fWeight = 0.0f;

			while(elementPos)
			{
				// Get the next element
				pElement = pItem->m_tplElementList.GetNext(elementPos);
				pBeam=(CBeamElement*)pElement;

				// Get length in metres
				fLength = (float)((pBeam->GetQty() * pBeam->GetLength())/1000.0f);

				// Calculate weight in tonnes
				fWeight += (float)((fLength * pItem->GetProductWeight())/1000.0f);
			}

			// Send weight to printer
			sText.Format("%.3f", fWeight);

			// Right align text
			txSz = printerDC.GetTextExtent(sText);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);

			// Send rectangle
			printerDC.Rectangle(iCompleteMargin, yPos, iCompleteMargin+iLeft*2, yPos+txSz.cy);

			printerDC.TextOut(iWeightMargin-txSz.cx, yPos, sText);
			yPos += txSz.cy;

			// Increment total weight
			fTotalWeight += fWeight;
		}

		if(bPrintBeam)
		{
			// Output total
			sText.Format("Beam Total %.3f", fTotalWeight);

			// Right align text
			txSz = printerDC.GetTextExtent(sText);
			yPos += txSz.cy;

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);

			printerDC.TextOut(iWeightMargin-txSz.cx, yPos, sText);
			yPos += txSz.cy*4;
		}


		// Store beam weight
		fGrandTotal = fTotalWeight;
		fTotalWeight = 0.0f;

		// Loop accessories
		itemPos = m_tplAccItemList.GetHeadPosition();

		if(itemPos)
		{
			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);

			// Output table headers
			printerDC.TextOut(iLeft, yPos, _T("Item"));
			printerDC.TextOut(iLeft*3, yPos, _T("Accessory"));
			txSz = printerDC.GetTextExtent(_T("Tonnage"));
			printerDC.TextOut(iWeightMargin-txSz.cx, yPos, _T("Tonnage"));
			printerDC.TextOut(iCompleteMargin, yPos, _T("Complete"));
			yPos += txSz.cy;

			// Set print totals
			bPrintAcc = true;
		}

		while(itemPos)
		{
			// Get the item object
			pItem = m_tplAccItemList.GetNext(itemPos);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);

			// Item number
			sText.Format("%i", pItem->GetItemID());
			printerDC.TextOut(iLeft, yPos, sText);

			// Send section name to printer
			printerDC.TextOut(iLeft*3, yPos, pItem->GetProductName());

			// Loop all elements
			elementPos = pItem->m_tplElementList.GetHeadPosition();

			// Clear weight
			fWeight = 0.0f;

			while(elementPos)
			{
				// Get the next element
				pElement = pItem->m_tplElementList.GetNext(elementPos);
				pAcc=(CAccessoryElement*)pElement;

				// Get length in metres
				fLength = (float)((pAcc->GetQty() * pAcc->GetLength())/1000.0f);

				// Calculate weight in tonnes
				fWeight += (float)((fLength * pItem->GetProductWeight())/1000.0f);
			}

			// Send weight to printer
			sText.Format("%.3f", fWeight);

			// Right align text
			txSz = printerDC.GetTextExtent(sText);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);

			// Send rectangle
			printerDC.Rectangle(iCompleteMargin, yPos, iCompleteMargin+iLeft*2, yPos+txSz.cy);

			printerDC.TextOut(iWeightMargin-txSz.cx, yPos, sText);
			yPos += txSz.cy;

			// Increment total weight
			fTotalWeight += fWeight;
		}

		// Store total weight
		fGrandTotal += fTotalWeight;

		if(bPrintAcc)
		{
			// Output total
			sText.Format("Accessory Total %.3f", fTotalWeight);

			// Right align text
			txSz = printerDC.GetTextExtent(sText);
			yPos += txSz.cy;

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);

			printerDC.TextOut(iWeightMargin-txSz.cx, yPos, sText);
		}

		yPos += txSz.cy*2;


		// Output total
		sText.Format("Job Total %.3f", fGrandTotal);

		// Right align text
		txSz = printerDC.GetTextExtent(sText);

		// Test page position
		testBounds(&printerDC, &yPos, &iPageNum);
		printerDC.TextOut(iWeightMargin-txSz.cx, yPos, sText);


		// Print footer
		sText.Format("Page - %i -", iPageNum);
		txSz = printerDC.GetTextExtent(sText);

		// Print footer
		printerDC.TextOut((A4_X/2)-(txSz.cx/2), A4_Y-100, sText);

		// Release font
		printerDC.SelectObject(pOldFont);

		printerDC.EndPage();
		printerDC.EndDoc();

// Standard print
#else
		int		iDataCols[6], iHeader[3];
		float	fTotalLen;


		// Create font
		detailFont.CreatePointFont(120, "Arial", &printerDC);
		detailFont.GetLogFont(&lFont);
		detailFont.DeleteObject();
		lFont.lfWeight = FW_NORMAL;
		detailFont.CreateFontIndirect(&lFont);

		// Select font
		pOldFont = printerDC.SelectObject(&detailFont);

		// Set header colums
		iHeader[0] = iLeft;
		iHeader[1] = iHeader[0] + 300;
		iHeader[2] = iHeader[1] + 400;

		// Set data column positions
		iDataCols[0] = iLeft;
		iDataCols[1] = iDataCols[0] + 800;
		iDataCols[2] = iDataCols[1] + 200;
		iDataCols[3] = iDataCols[2] + 200;
		iDataCols[4] = iDataCols[3] + 200;
		iDataCols[5] = iDataCols[4] + 200;

		// Get text size for height
		txSz = printerDC.GetTextExtent(_T("A"));

		// Job number
		sText = _T("Order NO.");
		printerDC.TextOut(iHeader[0], yPos, sText);
		printerDC.TextOut(iHeader[0], yPos+(txSz.cy*2), m_pProjectHeader->m_sProjectName);

		// Total tonnes
		sText = _T("Total Tonnes");
		printerDC.TextOut(iHeader[1], yPos, sText);
		sText.Format("%.3f", getTotalWeight());
		printerDC.TextOut(iHeader[1], yPos+(txSz.cy*2), sText);

		// Due date
		sText = _T("WC-COM");
		printerDC.TextOut(iHeader[2], yPos, sText);
		printerDC.TextOut(iHeader[2], yPos+(txSz.cy*2), m_pProjectHeader->m_sDueDate);
		yPos += txSz.cy*4;

		// Customer
		printerDC.TextOut(iHeader[0], yPos, m_pProjectHeader->m_sCustomerName);
		yPos += txSz.cy*4;

		// Print data headers

		// Product des
		sText = _T("Product Description");
		printerDC.TextOut(iDataCols[0], yPos, sText);

		// Metre
		sText = _T("Metre");
		printerDC.TextOut(iDataCols[1], yPos, sText);

		// Tonne
		sText = _T("Tonnes");
		printerDC.TextOut(iDataCols[2], yPos, sText);

		// Issued
		sText = _T("ISSD");
		printerDC.TextOut(iDataCols[3], yPos, sText);

		// Rolled
		sText = _T("ROLLD");
		printerDC.TextOut(iDataCols[4], yPos, sText);

		// Complete
		sText = _T("COMP");
		printerDC.TextOut(iDataCols[5], yPos, sText);
		yPos += txSz.cy*2;

		// Loop beams
		itemPos = m_tplItemList.GetHeadPosition();

		while(itemPos)
		{
			// Get the item object
			pItem = m_tplItemList.GetNext(itemPos);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);

			// Send section name to printer
			printerDC.TextOut(iDataCols[0], yPos, pItem->GetProductName());

			// Loop all elements
			elementPos = pItem->m_tplElementList.GetHeadPosition();

			// Clear
			fWeight = 0.0f;
			fTotalLen = 0.0f;

			while(elementPos)
			{
				// Get the next element
				pElement = pItem->m_tplElementList.GetNext(elementPos);
				pBeam=(CBeamElement*)pElement;

				// Get length in metres
				fLength = (float)((pBeam->GetQty() * pBeam->GetLength())/1000.0f);
				fTotalLen += fLength;

				// Calculate weight in tonnes
				fWeight += (float)((fLength * pItem->GetProductWeight())/1000.0f);
			}

			// Format string
			sText.Format("%.3f", fTotalLen);

			// Get the text size
			txSz = printerDC.GetTextExtent(sText);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);
			
			// Send to printer (right align)
			printerDC.TextOut((iDataCols[2]-txSz.cx)-10, yPos, sText);

			// Format string
			sText.Format("%.3f", fWeight);

			// Get the text size
			txSz = printerDC.GetTextExtent(sText);
			
			// Send to printer (right align)
			printerDC.TextOut((iDataCols[3]-txSz.cx)-10, yPos, sText);

			// Move to next line
			yPos += txSz.cy;

			// Increment total weight
			fTotalWeight += fWeight;
		}

		// Store beam weight
		fGrandTotal = fTotalWeight;
		fTotalWeight = 0.0f;


		// Loop accessories
		itemPos = m_tplAccItemList.GetHeadPosition();

		while(itemPos)
		{
			// Get the item object
			pItem = m_tplAccItemList.GetNext(itemPos);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);


			// Send section name to printer
			printerDC.TextOut(iDataCols[0], yPos, pItem->GetProductName());

			// Loop all elements
			elementPos = pItem->m_tplElementList.GetHeadPosition();

			// Clear weight
			fWeight = 0.0f;
			fTotalLen = 0.0f;

			while(elementPos)
			{
				// Get the next element
				pElement = pItem->m_tplElementList.GetNext(elementPos);
				pAcc=(CAccessoryElement*)pElement;

				// Get length in metres
				fLength = (float)((pAcc->GetQty() * pAcc->GetLength())/1000.0f);
				fTotalLen += fLength;

				// Calculate weight in tonnes
				fWeight += (float)((fLength * pItem->GetProductWeight())/1000.0f);
			}

			// Format string
			sText.Format("%.3f", fTotalLen);

			// Get the text size
			txSz = printerDC.GetTextExtent(sText);

			// Test page position
			testBounds(&printerDC, &yPos, &iPageNum);
			
			// Send to printer (right align)
			printerDC.TextOut((iDataCols[2]-txSz.cx)-10, yPos, sText);

			// Format string
			sText.Format("%.3f", fWeight);

			// Get the text size
			txSz = printerDC.GetTextExtent(sText);
			
			// Send to printer (right align)
			printerDC.TextOut((iDataCols[3]-txSz.cx)-10, yPos, sText);

			// Move to next line
			yPos += txSz.cy;

			// Increment total weight
			fTotalWeight += fWeight;
		}

		// Print footer
		sText.Format("Page - %i -", iPageNum);
		txSz = printerDC.GetTextExtent(sText);

		// Print footer
		printerDC.TextOut((A4_X/2)-(txSz.cx/2), A4_Y-100, sText);

		// Restore font
		printerDC.SelectObject(pOldFont);

		printerDC.EndPage();
		printerDC.EndDoc();

#endif

		// Restore fonts and mapping modes
		printerDC.SetMapMode(oldMap);
		printerDC.SetWindowExt(oldWindow);
		printerDC.SetViewportExt(oldView);

		// Release printer DC
		printerDC.Detach();
	}
	
}

void COD3Doc::OnUpdatePrintSummary(CCmdUI* pCmdUI) 
{

	// Enable if items are present
	if(m_tplAccItemList.GetCount() > 0 || m_tplItemList.GetCount() > 0)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
	
}

bool COD3Doc::testBounds(CDC *pDC, int *yPos, int *iPageNum)
{
	bool	bResult=false;

	if(*yPos >= (A4_Y-150))
	{
		CString	sText;
		CSize	sz;

		sText.Format("Page - %i -", *iPageNum);
		sz = pDC->GetTextExtent(sText);

		// Print footer
		pDC->TextOut((A4_X/2)-(sz.cx/2), A4_Y-100, sText);

		// Reset y position
		*yPos = 100;

		// Goto next page
		pDC->EndPage();
		pDC->StartPage();

		// Increment page number
		*iPageNum = *iPageNum + 1;

		bResult=true;
	}

	return(bResult);
}

void COD3Doc::OnPrintJobsheets() 
{
	POSITION		pos;
	CDC				printerDC;
	CPrintDialog	print(false);


	if(print.DoModal()==IDOK)
	{
		// Get the printer device
		HDC dc = print.GetPrinterDC();

		// Attach printer DC to CDC object
		printerDC.Attach(dc);

		// Set up lists for printing
		createJobLists();

		pos = m_tplJobSheet.GetHeadPosition();

		while(pos)
		{
			// Print job sheets
			printJobSheet(m_tplJobSheet.GetNext(pos), &printerDC);
		}

		// Release printer DC
		printerDC.Detach();
	}

	
	
}

void COD3Doc::OnUpdatePrintJobsheets(CCmdUI* pCmdUI) 
{
	// Enable if items are present
	if(m_tplAccItemList.GetCount() > 0 || m_tplItemList.GetCount() > 0)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
	
}

void COD3Doc::createJobLists()
{

	POSITION			posItem, posEle;
	CItem				*pItem=NULL;
	CElement			*pElement=NULL;
	CBeamElement		*pBeam=NULL;
	CAccessoryElement	*pAcc=NULL;
	CJobSheet			*pJobSheet=NULL;
	CJobSheetItem		*pJobItem=NULL;
	CDaoAccOffset		*daoOffset=NULL;
	CString				sText;
	int					iOffset;

	// Delete previous jobsheets
	posItem = m_tplJobSheet.GetHeadPosition();
	while(posItem)
		delete m_tplJobSheet.GetNext(posItem);

	m_tplJobSheet.RemoveAll();


	// Get the head position for the beams
	posItem = m_tplItemList.GetHeadPosition();

	while(posItem)
	{
		// Get the next object
		pItem = m_tplItemList.GetNext(posItem);

		// Create a job sheet
		pJobSheet = new CJobSheet();
		
		pJobSheet->setCustName(m_pProjectHeader->m_sCustomerName);
		pJobSheet->setCustRef(m_pProjectHeader->m_sCustomerRef);
		pJobSheet->setDate(m_pProjectHeader->m_sDueDate);
		pJobSheet->setItemNum(pItem->GetItemID());
		pJobSheet->setJobNumber(m_pProjectHeader->m_sProjectName);
		pJobSheet->setProdCode(pItem->GetProductCode());
		pJobSheet->setProdDes(pItem->GetProductName());
		pJobSheet->setWeight((float)(pItem->GetProductWeight()));

		// Add object to list
		m_tplJobSheet.AddTail(pJobSheet);


		// Get the head position for the elements
		posEle = pItem->m_tplElementList.GetHeadPosition();

		while(posEle)
		{
			// Get the next object
			pBeam = (CBeamElement*)pItem->m_tplElementList.GetNext(posEle);

			// Create and add new job item object into the list
			pJobSheet->newItem(pBeam->GetLength(), pBeam->GetQty(), pBeam->GetMark());

		}
	}


	// Get the head position for the accessories
	posItem = m_tplAccItemList.GetHeadPosition();

	if(m_pProjectSettings->m_ODDB_Open && posItem)
	{
		daoOffset = new CDaoAccOffset(m_pProjectSettings->m_pDB);
		daoOffset->Open();
	}

	while(posItem)
	{
		// Get the next object
		pItem = m_tplAccItemList.GetNext(posItem);

		// Create a job sheet
		pJobSheet = new CJobSheet();
		
		pJobSheet->setCustName(m_pProjectHeader->m_sCustomerName);
		pJobSheet->setCustRef(m_pProjectHeader->m_sCustomerRef);
		pJobSheet->setDate(m_pProjectHeader->m_sDueDate);
		pJobSheet->setItemNum(pItem->GetItemID());
		pJobSheet->setJobNumber(m_pProjectHeader->m_sProjectName);
		pJobSheet->setProdCode(pItem->GetProductCode());
		pJobSheet->setProdDes(pItem->GetProductName());
		pJobSheet->setWeight((float)(pItem->GetProductWeight()));

		// Add object to list
		m_tplJobSheet.AddTail(pJobSheet);

		// Set search criteria
		daoOffset->m_prod_code = pItem->GetProductCode();

		// Run query
		daoOffset->Requery();

		if(daoOffset->GetRecordCount())
		{
			// Set offset
			iOffset = (int)daoOffset->m_offset;
		}
		else
		{
			iOffset = 0;
		}

		
		// Get the head position for the elements
		posEle = pItem->m_tplElementList.GetHeadPosition();

		while(posEle)
		{
			// Get the next object
			pAcc = (CAccessoryElement *)pItem->m_tplElementList.GetNext(posEle);

			// Create and add new job item object into the list
			pJobItem = pJobSheet->newItem(pAcc->GetLength(), pAcc->GetQty(), pAcc->GetMark());

			// Set the cutting length
			pJobItem->setCuttingLength(pJobItem->getLength() + iOffset);

			// Set the remarks
			if(pItem->GetProductName().Find(_T("Double Diagonal")) > -1)
			{
				sText.Format("Cutting length = %i (inc. extra 100)", pJobItem->getCuttingLength());
			}
			else
			{
				sText.Format("Cutting length = %i", pJobItem->getCuttingLength());
			}

			// Set remarks
			pJobItem->setRemark(sText);
		}
	}

	// Close query
	if(daoOffset)
	{
		daoOffset->Close();
		delete daoOffset;
	}

}

void COD3Doc::printJobSheet(CJobSheet *pSheet, CDC *pDC)
{
	DOCINFO			docInfo;
	int				iTop = 100, iLeft = 100, iRight = 100, iBottom = 100;
	int				xMax,yMax, yPos=iTop, xPos=0, oldMap;
	int				iColMargin = A4_X/3;
	CSize			oldWindow, oldView, txSz;
	CString			sText;
	POSITION		posItem;
	CFont			*pOldFont=NULL, dataFont, tableFont;
	LOGFONT			lFont;
	int				iLineX[6], iCentres[5], iPageNum=1, yTest;;
	int				iOldBk, iSpace=10;
	float			fCollective=0.0f, fTotalWeight=0.0f;
	CBrush			*pBrush=NULL, recBrush;
	CJobSheetItem	*pItem=NULL;


	// Setup table positions
	iLineX[0] = iLeft;
	iLineX[1] = iLineX[0]+300;
	iLineX[2] = iLineX[1]+300;
	iLineX[3] = iLineX[2]+300;
	iLineX[4] = iLineX[3]+600;
	iLineX[5] = iLineX[4]+300;

	iCentres[0] = 250;
	iCentres[1] = iCentres[0]+300;
	iCentres[2] = iCentres[1]+300;
	iCentres[3] = iCentres[2]+450;
	iCentres[4] = iCentres[3]+450;

	// Set back drawing mode
	iOldBk = pDC->SetBkMode(TRANSPARENT);


	// Get device area
	yMax = pDC->GetDeviceCaps(VERTRES);
	xMax = pDC->GetDeviceCaps(HORZRES);

	// Scale view to suit
	oldMap = pDC->SetMapMode(MM_ISOTROPIC);
	oldWindow = pDC->SetWindowExt(A4_X, A4_Y);
	oldView = pDC->SetViewportExt(xMax, yMax);

	// Create font
	dataFont.CreatePointFont(120, "Arial", pDC);
	dataFont.GetLogFont(&lFont);
	dataFont.DeleteObject();
	lFont.lfWeight = FW_NORMAL;
	lFont.lfUnderline = false;
	dataFont.CreateFontIndirect(&lFont);

	tableFont.CreatePointFont(100, "Arial", pDC);
	tableFont.GetLogFont(&lFont);
	tableFont.DeleteObject();
	lFont.lfWeight = FW_NORMAL;
	lFont.lfUnderline = false;
	tableFont.CreateFontIndirect(&lFont);

	// Clean struct
	ZeroMemory(&docInfo, sizeof(DOCINFO));

	// Set up printing structure
	docInfo.cbSize=sizeof(DOCINFO);
	docInfo.lpszDocName = "Job Sheet";
	docInfo.lpszOutput = NULL;
	docInfo.fwType = NULL;

	// Start the document
	pDC->StartDoc(&docInfo);
	// Start the page
	pDC->StartPage();

	// Print job sheet headers
	pOldFont = pDC->SelectObject(&dataFont);

	sText = _T("OD3 Job Sheet");

	// Get text size for height
	txSz = pDC->GetTextExtent(sText);

	// Output title
	pDC->TextOut((A4_X/2)-(txSz.cx/2), yPos, sText);
	yPos += txSz.cy*2;

	// Job number
	sText = _T("Job Number:");
	pDC->TextOut(iLeft, yPos, sText);
	pDC->TextOut(iColMargin, yPos, pSheet->getJobNumber());
	yPos += txSz.cy;

	// Customer
	sText = _T("Customer:");
	pDC->TextOut(iLeft, yPos, sText);
	pDC->TextOut(iColMargin, yPos, pSheet->getCustName());
	yPos += txSz.cy;

	// Customer Order number
	sText = _T("Customer Ref:");
	pDC->TextOut(iLeft, yPos, sText);
	pDC->TextOut(iColMargin, yPos, pSheet->getCustRef());
	yPos += txSz.cy;

	// Due date
	sText = _T("Due Date:");
	pDC->TextOut(iLeft, yPos, sText);
	pDC->TextOut(iColMargin, yPos, pSheet->getDate());
	yPos += txSz.cy*2;

	// Item number
	sText.Format("Item Number %i", pSheet->getItemNum());
	pDC->TextOut(iLeft, yPos, sText);
	yPos += txSz.cy;

	// Item description
	sText.Format("Product %s - %s -", pSheet->getProdCode(), pSheet->getProdDes());
	pDC->TextOut(iLeft, yPos, sText);
	yPos += txSz.cy*2;

	// Create and use a brush to fill rectangles
	recBrush.CreateSolidBrush(RGB(220,220,220));
	pBrush = pDC->SelectObject(&recBrush);

	// Output table headers
	pDC->Rectangle(iLineX[0], yPos, iLineX[1], yPos+100);
	pDC->Rectangle(iLineX[1], yPos, iLineX[2], yPos+100);
	pDC->Rectangle(iLineX[2], yPos, iLineX[3], yPos+100);
	pDC->Rectangle(iLineX[3], yPos, iLineX[4], yPos+100);
	pDC->Rectangle(iLineX[4], yPos, iLineX[5], yPos+100);

	// Restore brush
	pDC->SelectObject(pBrush);


	sText = _T("Mark");
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(iCentres[0]-(txSz.cx/2), yPos+(txSz.cy/2), sText);

	sText = _T("Qty");
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(iCentres[1]-(txSz.cx/2), yPos+(txSz.cy/2), sText);

	sText = _T("Length (mm)");
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(iCentres[2]-(txSz.cx/2), yPos+(txSz.cy/2), sText);

	sText = _T("Remarks");
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(iCentres[3]-(txSz.cx/2), yPos+(txSz.cy/2), sText);

	sText = _T("Collective (m)");
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(iCentres[4]-(txSz.cx/2), yPos+(txSz.cy/2), sText);
	yPos+=100;

	// Restore font
	pDC->SelectObject(pOldFont);

	// Select table font
	pOldFont = pDC->SelectObject(&tableFont);

	// Get the head position for the items
	posItem = pSheet->m_tplItems.GetHeadPosition();

	while(posItem)
	{
		// Get next object
		pItem = pSheet->m_tplItems.GetNext(posItem);

		// Test page
		yTest=yPos+75;
		testBounds(pDC, &yTest, &iPageNum);
		if(yPos != 100)
			yPos=yTest-75;

		// Output cells
		pDC->Rectangle(iLineX[0], yPos, iLineX[1], yPos+75);
		pDC->Rectangle(iLineX[1], yPos, iLineX[2], yPos+75);
		pDC->Rectangle(iLineX[2], yPos, iLineX[3], yPos+75);
		pDC->Rectangle(iLineX[3], yPos, iLineX[4], yPos+75);
		pDC->Rectangle(iLineX[4], yPos, iLineX[5], yPos+75);
	

		// Output data
		pDC->TextOut(iLeft+iSpace, yPos+(txSz.cy/2), pItem->getMark());

		sText.Format("%i", pItem->getQty());
		txSz = pDC->GetTextExtent(sText);
		pDC->TextOut(((iLineX[2]-iSpace)-txSz.cx), yPos+(txSz.cy/2), sText);

		sText.Format("%i", pItem->getLength());
		txSz = pDC->GetTextExtent(sText);
		pDC->TextOut(((iLineX[3]-iSpace)-txSz.cx), yPos+(txSz.cy/2), sText); 
		
		pDC->TextOut(iLineX[3]+iSpace, yPos+(txSz.cy/2), pItem->getRemark());
		
		if(pItem->getCuttingLength() > 0)
		{
			fCollective += (float)pItem->getCuttingLength() * (float)pItem->getQty() / 1000.0f;
		}
		else
		{
			fCollective += (float)pItem->getLength() * (float)pItem->getQty() / 1000.0f;
		}

		sText.Format("%.3f", fCollective);
		txSz = pDC->GetTextExtent(sText);
		pDC->TextOut(((iLineX[5]-iSpace)-txSz.cx), yPos+(txSz.cy/2), sText);

		// Move to next cell position
		yPos+=75;

		if(pItem->getCuttingLength() > 0)
		{
			fTotalWeight += (pSheet->getWeight()/1000.0f) * (float)(pItem->getCuttingLength()/1000.0f) * (float)pItem->getQty();
		}
		else
		{
			// Accumulate total weight
			fTotalWeight += (pSheet->getWeight()/1000.0f) * (float)(pItem->getLength()/1000.0f) * (float)pItem->getQty();
		}
	}
	

	// Output totals
	pBrush = pDC->SelectObject(&recBrush);

	// Move down from data cells
	yPos+=txSz.cy*4;

	testBounds(pDC, &yTest, &iPageNum);

	// Output table headers
	pDC->Rectangle(iLineX[0], yPos, iLineX[1], yPos+100);
	pDC->Rectangle(iLineX[1], yPos, iLineX[2], yPos+100);

	// Restore brush
	pDC->SelectObject(pBrush);
	
	// Restore font
	pDC->SelectObject(pOldFont);
	// Select font
	pOldFont = pDC->SelectObject(&dataFont);

	testBounds(pDC, &yTest, &iPageNum);

	sText = _T("Total Tonnes");
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(iCentres[0]-(txSz.cx/2), yPos+(txSz.cy/2), sText);

	sText = _T("Total Metres");
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(iCentres[1]-(txSz.cx/2), yPos+(txSz.cy/2), sText);

	// Restore font
	pDC->SelectObject(pOldFont);
	// Select table font
	pOldFont = pDC->SelectObject(&tableFont);

	yPos+=100;

	// Test page
	yTest=yPos+75;
	testBounds(pDC, &yTest, &iPageNum);
	if(yPos != 100)
		yPos=yTest-75;

	// Output cells
	pDC->Rectangle(iLineX[0], yPos, iLineX[1], yPos+75);
	pDC->Rectangle(iLineX[1], yPos, iLineX[2], yPos+75);


	// Output data
	sText.Format("%.3f", fTotalWeight);
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(((iLineX[1]-iSpace)-txSz.cx), yPos+(txSz.cy/2), sText);

	sText.Format("%.3f", fCollective);
	txSz = pDC->GetTextExtent(sText);
	pDC->TextOut(((iLineX[2]-iSpace)-txSz.cx), yPos+(txSz.cy/2), sText);


	// Format page footer
	sText.Format("Page - %i -", iPageNum);
	txSz = pDC->GetTextExtent(sText);

	// Print footer
	pDC->TextOut((A4_X/2)-(txSz.cx/2), A4_Y-100, sText);

	// End last page
	pDC->EndPage();
	// Finish document printing
	pDC->EndDoc();


	// Restore fonts and mapping modes
	pDC->SelectObject(pOldFont);
	pDC->SetMapMode(oldMap);
	pDC->SetWindowExt(oldWindow);
	pDC->SetViewportExt(oldView);
	pDC->SetBkMode(iOldBk);

}

float COD3Doc::getTotalWeight()
{
	float				fTotalWeight = 0.0f;
	float				fWeight=0.0f, fLength=0.0f;
	CItem				*pItem=NULL;
	POSITION			itemPos, elementPos;
	CElement			*pElement=NULL;
	CAccessoryElement	*pAcc=NULL;
	CBeamElement		*pBeam=NULL;

	// Loop beams
	itemPos = m_tplItemList.GetHeadPosition();

	while(itemPos)
	{
		// Get the item object
		pItem = m_tplItemList.GetNext(itemPos);

		// Get the head position for the elements
		elementPos = pItem->m_tplElementList.GetHeadPosition();

		// Clear
		fWeight = 0.0f;

		while(elementPos)
		{
			// Get the next element
			pElement = pItem->m_tplElementList.GetNext(elementPos);
			pBeam=(CBeamElement*)pElement;

			// Get length in metres
			fLength = (float)((pBeam->GetQty() * pBeam->GetLength())/1000.0f);

			// Calculate weight in tonnes
			fWeight += (float)((fLength * pItem->GetProductWeight())/1000.0f);
		}

		// Store beam weight
		fTotalWeight += fWeight;
	}


	// Loop accessories
	itemPos = m_tplAccItemList.GetHeadPosition();

	while(itemPos)
	{
		// Get the item object
		pItem = m_tplAccItemList.GetNext(itemPos);

		// Get the head position for the elements
		elementPos = pItem->m_tplElementList.GetHeadPosition();

		// Clear
		fWeight = 0.0f;

		while(elementPos)
		{
			// Get the next element
			pElement = pItem->m_tplElementList.GetNext(elementPos);
			pAcc=(CAccessoryElement*)pElement;

			// Get length in metres
			fLength = (float)((pAcc->GetQty() * pAcc->GetLength())/1000.0f);

			// Calculate weight in tonnes
			fWeight += (float)((fLength * pItem->GetProductWeight())/1000.0f);
		}

		// Store beam weight
		fTotalWeight += fWeight;
	}


	return(fTotalWeight);
}

void COD3Doc::OnCoilSendjob() 
{
	CJobSheet			*pSheet;
	CJobSheetItem		*pItem;
	POSITION			listPos;
	float				fCollective,fTotalWeight;	
	CDaoCoilJobDetails	*pDetail=NULL;
	CDaoDatabase		db;
	CString				sPath = AfxGetApp()->GetProfileString(_T("Paths"), _T("CoilDB"), "");
	CWaitCursor			wait;

	if(sPath.GetLength() == 0)
		sPath = setCoilDBPath();
	
	try
	{
		// Open the coil planner database
		db.Open(sPath, false, false, _T(""));
	
		// Set up basic job lists for pre database send
		createJobLists();

		POSITION pos=m_tplJobSheet.GetHeadPosition();

		// Send job to database
		if( (pSheet=m_tplJobSheet.GetHead()))
		{
			CDaoCoilJob	pJob(&db);

			// Open recordset
			pJob.Open();

			// Add new record
			pJob.AddNew();

			// Update fields
			pJob.m_Customer_name = pSheet->getCustName();
			pJob.m_Job_Number= pSheet->getJobNumber();
			
			// Update database
			if(pJob.CanUpdate())							
				pJob.Update();
			
			// Close recordset
			pJob.Close();
		}


		while(pos)
		{
			pSheet = m_tplJobSheet.GetNext(pos);			

			listPos = pSheet->m_tplItems.GetHeadPosition();

			fCollective=fTotalWeight = 0.0f;
			while(listPos)
			{
				pItem = pSheet->m_tplItems.GetNext(listPos);

				if(pItem->getCuttingLength() > 0)
				{
					fCollective += (float)pItem->getCuttingLength() * (float)pItem->getQty() / 1000.0f;
					fTotalWeight += (pSheet->getWeight()/1000.0f) * (float)(pItem->getCuttingLength()/1000.0f) * (float)pItem->getQty();
				}
				else
				{
					fCollective += (float)pItem->getLength() * (float)pItem->getQty() / 1000.0f;
					// Accumulate total weight
					fTotalWeight += (pSheet->getWeight()/1000.0f) * (float)(pItem->getLength()/1000.0f) * (float)pItem->getQty();
				}			
			}
			
			pDetail = new CDaoCoilJobDetails(&db);

			// Open recordset
			pDetail->Open();

			// Add new record
			pDetail->AddNew();

			// Set fields
			//pDetail->m_Coil_Code;
			pDetail->m_Job_Number = pSheet->getJobNumber();
			pDetail->m_Metres = fCollective;
			pDetail->m_Section = pSheet->getProdDes();
			pDetail->m_Tonnage = fTotalWeight;

			if(pDetail->CanUpdate())
				pDetail->Update();

			// Close recordset
			pDetail->Close();

			delete pDetail;
		}
		
		// Close the database
		db.Close();

		// Inform success
		AfxMessageBox("Order Sent to coil planner", MB_OK|MB_ICONINFORMATION);
	}
	catch(CDaoException *e)
	{
		// Show recordset error
		CDaoErrorInfo	*info=e->m_pErrorInfo;

		if(info->m_lErrorCode==3022)
		{
			// Order exists in the database
			AfxMessageBox("This order is already in the coil planning database, the order has not been added", MB_ICONINFORMATION);
		}
		else
		{
			// Show error
			e->ReportError(MB_ICONINFORMATION);
		}

		// Remove exception
		e->Delete();
	}

	// Clear hourglass cursor
	wait.Restore();
		
}
	


void COD3Doc::OnUpdateCoilSendjob(CCmdUI* pCmdUI) 
{
	// Enable if items are present
	if(m_tplAccItemList.GetCount() > 0 || m_tplItemList.GetCount() > 0)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
	
}

void COD3Doc::OnCoilUpdatejob() 
{
	CDlgUpdateJobStatus	dlg(NULL, this);

	dlg.DoModal();
}

CString COD3Doc::setCoilDBPath()
{
	// Warn no database path
	AfxMessageBox(IDS_MISSINGCOILPATH, MB_ICONINFORMATION);

	DWORD	flags = OFN_OVERWRITEPROMPT|
					OFN_HIDEREADONLY|
     				OFN_PATHMUSTEXIST|
					OFN_SHAREWARN;

	CFileDialog findDB(true, "mdb", NULL, flags,
							"Microsoft Access Database (*.mdb)|*.mdb||",
							AfxGetApp()->m_pMainWnd);


	// Open file dialog
	if(findDB.DoModal() == IDOK)
	{
		// Set registry string
		AfxGetApp()->WriteProfileString(_T("Paths"), _T("CoilDB"), findDB.GetPathName().GetBuffer(findDB.GetPathName().GetLength()));
	}
	
	return(findDB.GetPathName());

	
}

void COD3Doc::OnCoilPrintlive() 
{
	

	CDC				printerDC;
	CPrintDialog	print(false);


	if(print.DoModal()==IDOK)
	{
		// Get the printer device
		HDC dc = print.GetPrinterDC();

		// Attach printer DC to CDC object
		printerDC.Attach(dc);

		// Prepare coil data from database
		setCoilDataList();

		// Perform printing
		printCoilPlanning(&printerDC);

		// Release printer DC
		printerDC.Detach();
	}
}

void COD3Doc::OnCoilExportlive() 
{
	COleVariant		VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    CApplication	objApp;
    CWorkbook		objBook;
    CWorkbooks		objBooks;
    CWorksheets		objSheets;
    CWorksheet		objSheet;
    CRange			rangeTitle, rangeSection, rangeQty;
	COleSafeArray	titleArr, sectionArr, qtyArr;
	DWORD			numElements[2];
	CDaoDatabase	db;
	CString			sPath = AfxGetApp()->GetProfileString(_T("Paths"), _T("CoilDB"), "");
	long			index[2];
	int				iRowCount=0;
	VARIANT			v;
	CString			sText;


	if(sPath.GetLength() == 0)
		sPath = setCoilDBPath();

	try
	{
		// Instantiate Excel and start a new workbook.
		if(!objApp.CreateDispatch("Excel.Application"))
		{
			// Could not start Excel 
			AfxThrowOleDispatchException(0, "Could not start Microsoft Excel", 0);
		}


		objBooks = objApp.GetWorkbooks();
		objBook = objBooks.Add(VOptional);
		objSheets = objBook.GetWorksheets();
		objSheet = objSheets.GetItem(COleVariant((short)1));

		// Set the title range for the titles
		rangeTitle = objSheet.GetRange(COleVariant(_T("A1")), COleVariant(_T("A1")));
		rangeTitle = rangeTitle.GetResize(COleVariant((short)1), COleVariant(short(2)));

		// Number of rows in the range
		numElements[0]= 1;  
		// Number of columns in the range
		numElements[1]= 2;   

		titleArr.Create(VT_BSTR, 2, numElements);

		index[0] = 0;
		index[1] = 0;
		VariantInit(&v);
		v.vt = VT_BSTR;
		sText = "Section";
		v.bstrVal = sText.AllocSysString();
		titleArr.PutElement(index, v.bstrVal);
		SysFreeString(v.bstrVal);
		VariantClear(&v);

		index[0] = 0;
		index[1] = 1;
		VariantInit(&v);
		v.vt = VT_BSTR;
		sText = "Required Quantity";
		v.bstrVal = sText.AllocSysString();
		titleArr.PutElement(index, v.bstrVal);
		SysFreeString(v.bstrVal);
		VariantClear(&v);
		
		
		// Set the range data
		rangeTitle.SetValue(COleVariant(titleArr));
		titleArr.Detach();

		// Open the coil planner database
		db.Open(sPath, false, false, _T(""));

		CDaoCoilSectionSum sectionSum(&db);

		// Open recordset
		sectionSum.Open();

		if(sectionSum.GetRecordCount() > 0)
		{
			// Number of rows in the range
			numElements[0] = sectionSum.GetRecordCount(); 
			// Set single column
			numElements[1] = 1; 

			// set range for section names
			rangeSection = objSheet.GetRange(COleVariant(_T("A2")), COleVariant(_T("A2")));
			rangeSection = rangeSection.GetResize(COleVariant(sectionSum.GetRecordCount()), COleVariant((short)1));

			// Set range for sum of weight
			rangeQty = objSheet.GetRange(COleVariant(_T("B2")), COleVariant(_T("B2")));
			rangeQty = rangeQty.GetResize(COleVariant(sectionSum.GetRecordCount()), COleVariant((short)1));

			// Create arrays
			sectionArr.Create(VT_BSTR, 2, numElements);
			qtyArr.Create(VT_R8, 2, numElements);

			// Loop data from db
			while(!sectionSum.IsEOF())
			{
				// Section information
				index[0] = iRowCount;
				index[1] = 0;
				VariantInit(&v);
				v.vt = VT_BSTR;
				v.bstrVal = sectionSum.m_Section.AllocSysString();
				sectionArr.PutElement(index, v.bstrVal);
				SysFreeString(v.bstrVal);
				VariantClear(&v);

				// Sum of tonnage			
				qtyArr.PutElement(index, &sectionSum.m_SumOfTonnage);

				// Goto next record
				sectionSum.MoveNext();
				iRowCount++;
			}
			
			// Close recordset
			sectionSum.Close();

			// Close connection
			db.Close();

			// Set range data
			rangeSection.SetValue(COleVariant(sectionArr));
			rangeQty.SetValue(COleVariant(qtyArr));

			// Clear arrays
			sectionArr.Detach();
			qtyArr.Detach();

		}

		// Return control of Excel to the user.
		objApp.SetVisible(TRUE);
		objApp.SetUserControl(TRUE);
	}
	catch(COleException *e)
	{
		// Report error
		e->ReportError(MB_OK|MB_ICONWARNING);
		// Remove exception
		e->Delete();
	}
	catch(COleDispatchException *e)
	{
		// Report error
		e->ReportError(MB_OK|MB_ICONWARNING);
		// Remove exception
		e->Delete();
	}
	catch(CDaoException *e)
	{
		// Report error
		e->ReportError(MB_OK|MB_ICONWARNING);
		// Remove exception
		e->Delete();
	}
	
}

void COD3Doc::setCoilDataList()
{
	CDaoDatabase		db;
	CString				sPath = AfxGetApp()->GetProfileString(_T("Paths"), _T("CoilDB"), "");
	CWaitCursor			wait;
	CJobSheet			*pJob=NULL;
	CJobSheetItem		*pJobItem=NULL;
	CString				sText;
	POSITION			posItem;

	// Delete previous jobsheets
	posItem = m_tplJobSheet.GetHeadPosition();
	while(posItem)
		delete m_tplJobSheet.GetNext(posItem);

	m_tplJobSheet.RemoveAll();

	if(sPath.GetLength() == 0)
		sPath = setCoilDBPath();
	
	try
	{
		// Open the coil planner database
		db.Open(sPath, false, false, _T(""));

		CDaoCoilLiveDuplicateSections	pDuplicate(&db);
		CDaoCoilLiveSingleSections		pSingle(&db);
		
		// Get all live duplicated sections
		pDuplicate.Open();

		if(!pDuplicate.IsEOF())
		{
			// Create new object
			pJob = new CJobSheet();

			// Set section type (group header)
			pJob->setProdDes(pDuplicate.m_Section);

			// Add to document
			m_tplJobSheet.AddTail(pJob);
		
			while(!pDuplicate.IsEOF())
			{	
				// Create jobitem object
				pJobItem = new CJobSheetItem();

				// Use mark as weight
				sText.Format("%.8f", pDuplicate.m_Tonnage);
				pJobItem->setMark(sText);
				
				// Use remark as job number 
				pJobItem->setRemark(pDuplicate.m_Job_Number);

				// Add to list
				pJob->m_tplItems.AddTail(pJobItem);

				// Get next entry
				pDuplicate.MoveNext();
			}
		}

		// Release recordset
		pDuplicate.Close();

		// Get all live single entry sections
		pSingle.Open();

		while(!pSingle.IsEOF())
		{
			pJob = new CJobSheet();

			pJob->setJobNumber(pSingle.m_Job_Number);
			pJob->setProdDes(pSingle.m_Section);
			pJob->setWeight((float)pSingle.m_Tonnage);

			// Add to document
			m_tplJobSheet.AddTail(pJob);

			// Get next entry
			pSingle.MoveNext();
		}

		// Release recordset
		pSingle.Close();


		// Close the database
		db.Close();
	}
	catch(CDaoException *e)
	{
		// Show error
		e->ReportError(MB_ICONINFORMATION);
		// Remove exception
		e->Delete();
	}

	// May want to sort by section
	// TODO CODE:


	// Clear hourglass cursor
	wait.Restore();
}

void COD3Doc::printCoilPlanning(CDC *pDC)
{
	DOCINFO			docInfo;
	int				iTop = 100, iLeft = 100, iRight = 100, iBottom = 100;
	int				xMax,yMax, yPos=iTop, xPos=0, oldMap;
	int				iColMargin = A4_X/3;
	CSize			oldWindow, oldView, txSz;
	CString			sText;
	POSITION		posJob, posItem;
	CFont			*pOldFont=NULL, dataFont;
	LOGFONT			lFont;
	int				iLineX[4], iPageNum=1;
	int				iOldBk, iSpace=10;
	CBrush			*pBrush=NULL, recBrush;
	CJobSheet		*pJob=NULL;
	CJobSheetItem	*pItem=NULL;
	CArray<float,float>		weightList;
	CArray<CString,CString>	orderList;
	float					fJobWeight, fWeight;
	int						i;

	weightList.SetSize(1);
	orderList.SetSize(1);


	// Setup table positions
	iLineX[0] = iLeft;
	iLineX[1] = iLineX[0]+300;
	iLineX[2] = iLineX[1]+300;
	iLineX[3] = iLineX[2]+300;

	// Set back drawing mode
	iOldBk = pDC->SetBkMode(TRANSPARENT);


	// Get device area
	yMax = pDC->GetDeviceCaps(VERTRES);
	xMax = pDC->GetDeviceCaps(HORZRES);

	// Scale view to suit
	oldMap = pDC->SetMapMode(MM_ISOTROPIC);
	oldWindow = pDC->SetWindowExt(A4_X, A4_Y);
	oldView = pDC->SetViewportExt(xMax, yMax);

	// Create font
	dataFont.CreatePointFont(120, "Arial", pDC);
	dataFont.GetLogFont(&lFont);
	dataFont.DeleteObject();
	lFont.lfWeight = FW_NORMAL;
	lFont.lfUnderline = false;
	dataFont.CreateFontIndirect(&lFont);

	// Create and use a brush to fill rectangles
	recBrush.CreateSolidBrush(RGB(220,220,220));

	// Clean struct
	ZeroMemory(&docInfo, sizeof(DOCINFO));

	// Set up printing structure
	docInfo.cbSize=sizeof(DOCINFO);
	docInfo.lpszDocName = "Coil Planning";
	docInfo.lpszOutput = NULL;
	docInfo.fwType = NULL;

	// Start the document
	pDC->StartDoc(&docInfo);
	// Start the page
	pDC->StartPage();

	// Set title
	sText = _T("OD3 Coil Planning");

	// Get text size for height
	txSz = pDC->GetTextExtent(sText);

	// Output title
	pDC->TextOut((A4_X/2)-(txSz.cx/2), yPos, sText);
	yPos += txSz.cy*2;


	// Get the head position
	posJob = m_tplJobSheet.GetHeadPosition();

	// Set font
	pOldFont = pDC->SelectObject(&dataFont);

	// Loop jobs
	while(posJob)
	{
		// Clean lists
		orderList.RemoveAll();
		orderList.FreeExtra();
		weightList.RemoveAll();
		weightList.FreeExtra();

		// Get next job object
		pJob = m_tplJobSheet.GetNext(posJob);

		// Get items in jobs (multiple jobs per section)
		posItem = pJob->m_tplItems.GetHeadPosition();

		fJobWeight=0.0f;

		if(posItem)
		{
			// Multiple jobs per section

			
			// Loop mutilple orders per section
			while(posItem)
			{
				// Get works order object
				pItem = pJob->m_tplItems.GetNext(posItem);

				// Mark is used to store weight
				fWeight=(float)atof(pItem->getMark());
				fJobWeight+=fWeight;
				weightList.Add(fWeight);

				// Remark is used to store job number
				orderList.Add(pItem->getRemark());
			}
		}
		else
		{
			// Single job for this section
			orderList.Add(pJob->getJobNumber());
			weightList.Add(pJob->getWeight());
			fJobWeight = pJob->getWeight();
		}


		// Select filled rectangle brush
		pBrush = pDC->SelectObject(&recBrush);

		// Output table header
		pDC->Rectangle(iLineX[0], yPos, A4_X, yPos+75);
		
		// Release brush
		pDC->SelectObject(pBrush);

		// Item description
		sText.Format("Section - %s -", pJob->getProdDes());
		pDC->TextOut(iLeft, yPos, sText);
		yPos += txSz.cy*2;

		// Write titles
		pDC->TextOut(iLeft+iSpace, yPos, "Order No.");

		txSz = pDC->GetTextExtent("Tonnage");
		pDC->TextOut(((iLineX[2]-iSpace)-txSz.cx), yPos, "Tonnage");
		yPos+=txSz.cy;


		for(i=0; i<orderList.GetSize(); i++)
		{			
			testBounds(pDC, &yPos, &iPageNum);

			// Output data
			pDC->TextOut(iLeft+iSpace, yPos, orderList.GetAt(i));
			sText.Format("%.3f", weightList.GetAt(i));
			txSz = pDC->GetTextExtent(sText);
			testBounds(pDC, &yPos, &iPageNum);
			pDC->TextOut(((iLineX[2]-iSpace)-txSz.cx), yPos, sText);
			yPos+=txSz.cy;
		}				

		// Output the total for the section
		yPos+=txSz.cy/2;
		sText.Format("%.3f", fJobWeight);
		txSz = pDC->GetTextExtent(sText);
		testBounds(pDC, &yPos, &iPageNum);
		pDC->TextOut(((iLineX[2]-iSpace)-txSz.cx), yPos, sText);

		// Move to next line
		yPos+=txSz.cy;

		
	}

	// Format page footer
	sText.Format("Page - %i -", iPageNum);
	txSz = pDC->GetTextExtent(sText);

	// Print footer
	pDC->TextOut((A4_X/2)-(txSz.cx/2), A4_Y-100, sText);

	// End last page
	pDC->EndPage();
	// Finish document printing
	pDC->EndDoc();

	// Release brush
	recBrush.DeleteObject();

	// Restore fonts and mapping modes
	pDC->SelectObject(pOldFont);
	pDC->SetMapMode(oldMap);
	pDC->SetWindowExt(oldWindow);
	pDC->SetViewportExt(oldView);
	pDC->SetBkMode(iOldBk);
}
