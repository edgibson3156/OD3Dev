// ImportAswFile.cpp: implementation of the CImportAswFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "od3.h"
#include "item.h"
#include "ImportAswFile.h"
#include "DlgNewProject.h"
#include "DlgItemList.h"
#include "DlgListAcc.h"
#include "DlgWernik.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Defined in OD3.cpp
extern CDlgListAcc dlgAcc;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction											//
//////////////////////////////////////////////////////////////////////

CImportAswFile::CImportAswFile(COD3Doc *document)
{
	// Clear members
	m_iMarkSplitInc=m_iBeamCount=m_iPosBeam=m_iPosAcc = 0;
	m_iMarkSplit=m_fullLength=m_startOffset=m_beamRemain = 0;

	// Set current document
	m_pDoc = document;

	// Load test strings 
	m_sCname.LoadString(IDS_SD_CUSTNAME);
	m_sOrder.LoadString(IDS_SD_ORDERNUM);
	m_sCount.LoadString(IDS_SD_BEAMCOUNT);
	m_sBeam.LoadString(IDS_SD_BEAM);

	m_sMark.LoadString(IDS_SD_MARK);
	m_sLenPunch.LoadString(IDS_SD_LEN_PUNCH);
	m_sLenNoPunch.LoadString(IDS_SD_LEN_NOPUNCH);
	m_sBeamType.LoadString(IDS_SD_BEAM_TYPE);
	m_sQuantity.LoadString(IDS_SD_QUANTITY);
	m_sComment.LoadString(IDS_SD_COMMENTS);

	m_sRound.LoadString(IDS_SD_HOLE_ROUND);
	m_sSquare.LoadString(IDS_SD_HOLE_SQUARE);
	m_sFlange.LoadString(IDS_SD_HOLE_FLANGE);
	m_sFour.LoadString(IDS_SD_HOLE_ALL4);
	m_sTop.LoadString(IDS_SD_HOLE_TOP);
	m_sBottom.LoadString(IDS_SD_HOLE_BOTTOM);
	m_sTopFlange.LoadString(IDS_SD_HOLE_TOPFLANGE);
	m_sBottomFlange.LoadString(IDS_SD_HOLE_BOTTOMFLANGE);
	m_sCutMark.LoadString(IDS_SD_CUTMARK);

	m_sAccessory.LoadString(IDS_SD_ACC);

}
CImportAswFile::~CImportAswFile()
{
	CImpAswData		*walker=NULL;
	CImpAswDataAcc	*acc=NULL;
	POSITION		pos;

	// Get the head pos
	pos = m_tplDataList.GetHeadPosition();

	// Loop through entire linked list
	while(pos)
	{
		// Get data pointer
		walker=m_tplDataList.GetNext(pos);
		// Free memory
		delete walker;
	}

	// Clean pointer list
	m_tplDataList.RemoveAll();


	// Get the head pos for the accessories
	pos = m_tplDataAcc.GetHeadPosition();

	// Loop through entire linked list
	while(pos)
	{
		// Get data pointer
		acc=m_tplDataAcc.GetNext(pos);
		// Free memory
		delete acc;
	}

	// Clean pointer list
	m_tplDataAcc.RemoveAll();

	// Remove strings
	m_sMarkSplit.RemoveAll();
}



CImpAswData::CImpAswData()
{
	m_iPunchCount=m_iQuantity=m_iLength = 0;
}
CImpAswData::~CImpAswData()
{
	CImpAswDataHole	*hole=NULL;
	POSITION		pos;

	// Get the head pos for the holes
	pos = m_tplDataHoles.GetHeadPosition();

	// Loop through entire linked list
	while(pos)
	{
		// Get data pointer
		hole=m_tplDataHoles.GetNext(pos);
		// Free memory
		delete hole;
	}

	// Clean pointer list
	m_tplDataHoles.RemoveAll();
}



CImpAswDataHole::CImpAswDataHole()
{
	m_iPos=0;
}
CImpAswDataHole::~CImpAswDataHole()
{
}

CImpAswDataAcc::CImpAswDataAcc()
{
	m_iQuantity=0;
}
CImpAswDataAcc::~CImpAswDataAcc()
{
}

//////////////////////////////////////////////////////////////////////
//																	//
//////////////////////////////////////////////////////////////////////


bool CImportAswFile::importFile()
{
	bool result=false;
	CString	sDefaultDir(_T("")), sPathName(_T(""));
	LPSTR	lpstrDefaultDir;
	DWORD	flags = OFN_FILEMUSTEXIST|
					OFN_HIDEREADONLY|
     				OFN_PATHMUSTEXIST|
					OFN_SHAREWARN;



	sDefaultDir = m_pDoc->m_pProjectSettings->m_sAutoFileInputPath;
	lpstrDefaultDir = sDefaultDir.GetBuffer(1);

	CFileDialog dlgOpen(true, "TXT", NULL, flags,
							"SwageDetail file (*.asw)|*.asw||",
							AfxGetApp()->m_pMainWnd);

	// Set default directory
	dlgOpen.m_ofn.lpstrInitialDir = lpstrDefaultDir;

	// Open common dialog
	if (dlgOpen.DoModal() == IDOK)
	{	
		CWaitCursor	wait;

		// Get file path
		sPathName = dlgOpen.GetPathName();

		
		try
		{
			CStdioFile aswImport( sPathName, CFile::modeRead|
								CFile::modeNoTruncate|
								CFile::modeRead|
								CFile::shareDenyNone);


			// Read the asw file
			if((result=fileRead(&aswImport)))
			{
				// Loop imported data and create document items
				createDocItems();
			}
			
			// Close the file pointer
			aswImport.Close();

			// Test for accessories
			if(m_iPosAcc)
			{
				// Display Asw accessory list dialog
				
				POSITION		accPos;
				LVITEM			lvItem;
				CString			itemText;
				CImpAswDataAcc	*data=NULL;


				// Get the head position for the acc
				accPos = m_tplDataAcc.GetHeadPosition();

				while(accPos)
				{
					// Get data pointer
					data = m_tplDataAcc.GetAt(accPos);
					

					// Store data in the list control

					// Set list control data structure
					lvItem.mask = LVIF_TEXT;
					lvItem.iItem = dlgAcc.m_accList.GetItemCount();

					// Product name
					lvItem.iSubItem = 0;
					lvItem.pszText = data->m_sProduct.GetBuffer(itemText.GetLength());
					dlgAcc.m_accList.InsertItem(&lvItem);
							
					// Quantity
					lvItem.iSubItem = 1;
					itemText.Format("%i", data->m_iQuantity);
					lvItem.pszText = itemText.GetBuffer(itemText.GetLength());
					dlgAcc.m_accList.SetItem(&lvItem);

					// Get next acc
					data = m_tplDataAcc.GetNext(accPos);
				}

				// Set the job description header for printing
				dlgAcc.m_sJobDetails.Format(IDS_SD_PRINTTITLE, m_sCustName, m_sOrderNum);

				// Open dialog
				dlgAcc.ShowWindow(SW_SHOW);
			}
		}
		catch(CFileException *e)
		{
			// Report file exception
			e->ReportError(MB_ICONWARNING);	
			// Remove exception and continue app
			e->Delete();
		}

		// Remove hourglass cursor
		wait.Restore();
	}


	return(result);
}

bool CImportAswFile::fileRead(CStdioFile *file)
{
	bool	result=false;
	int		eof=0, i;
	CString	lineBuf, testStr;


	if(isSwageFile(file))
	{
		// Loop to store user data
		while(!eof)
		{
			// Read string data
			eof = !file->ReadString(lineBuf);

			// Store user data
			if(storeUserData(lineBuf, eof, file))
				break;
		}

		// Loop through all beams
		for(i=0; i<m_iBeamCount; i++)
		{
			// Store beam, element and hole data
			storeBeamData(file);
		}
		// File has been read
		result = true;
	}

	return(result);
}

int CImportAswFile::isSwageFile(CStdioFile *file)
{
	int	result=false;
	CString	lineBuf, testStr,testStr2;

	// Test if correct file type
	file->ReadString(lineBuf);

	testStr.LoadString(IDS_SD_TYPE);
	testStr2.LoadString(IDS_SD_TYPE2);

	if(!lineBuf.CompareNoCase(testStr) || !lineBuf.CompareNoCase(testStr2))
		result=true;


	return(result);
}

bool CImportAswFile::storeUserData(CString lineData, int eof, CStdioFile *file)
{
	int		iCount, iPos;
	bool	done=false;


	// Test for end of file and string length
	if(!eof && lineData.GetLength())
	{
		// Test string
		if(lineData.Find(m_sBeam) == 0)
		{
			// Store file pos
			m_iPosBeam = file->GetPosition();
			// Got all of the user information
			done=true;
		}
		else if(lineData.Find(m_sCname) != -1)
		{
			// Store customer name
			m_sCustName = lineData.Mid(m_sCname.GetLength()+1, lineData.GetLength());
		}
		else if((iCount=lineData.Find(m_sOrder)) != -1)
		{
			// Store customer order number
			m_sOrderNum = lineData.Mid(iCount+m_sOrder.GetLength()+1);

			// Remove full stop
			if((iPos=m_sOrderNum.Find(_T('.'))) !=-1)
			{
				if(iPos==m_sOrderNum.GetLength()-1)
					m_sOrderNum.Delete(iPos,1);
			}
		}
		else if(lineData.Find(m_sCount) != -1)
		{
			// Store beam entry count
			iCount=lineData.Find("beam");
			m_iBeamCount = atoi(lineData.Left(iCount-1));
		}
	}


	return(done);
}

bool CImportAswFile::storeBeamData(CStdioFile *file)
{
	CImpAswData		*beamData=NULL, *newBeam=NULL;
	CImpAswDataAcc	*accData=NULL;
	bool			done=false;
	int				eof,iPos,markCount=0;
	CString			lineData,tmp,tmp2;
	CString			prevProduct;
	int				flag;


	// Read string data
	eof=!file->ReadString(lineData);

	// Create new class instance
	beamData = new CImpAswData;

	// Clear sub beam variables
	m_fullLength=m_startOffset=m_beamRemain = 0;
	m_iMarkSplit=m_iMarkSplitInc = 0;

	// Delete split mark numbers
	m_sMarkSplit.RemoveAll();
	m_sMarkSplit.FreeExtra();
	m_sStoreFirstMark.Empty();

	// Loop beam data
	while(!eof)
	{
		// Perform string tests
		if((iPos=lineData.Find(m_sMark)) != -1)
		{
			// Extract mark number
			tmp = lineData.Mid(m_sMark.GetLength()+1);
			// Remove full stop
			if((iPos=tmp.Find(_T('.'))) !=-1)
			{
				if(iPos==tmp.GetLength()-1)
					tmp.Delete(iPos,1);
			}

			// Store mark
			beamData->m_sMark = tmp;
			// Strip any underscores found in the mark number
			beamData->m_sMark.Replace(_T("_"), _T("#"));

		}
		else if(storeBeamLength(lineData, beamData));

		else if(storeMatName(lineData, beamData));

		else if(storeQuantity(lineData, beamData));
		
		/****************** HOLES **************************************/
		else if((newBeam=storeHoles(lineData, beamData, file, &flag)))
		{
			// New beam created, modifiy current pointer
			if(flag != 1)
			{
				beamData = newBeam;
			}
		}
		/***************************************************************/
		else if(lineData.Find(m_sBeam) == 0)
		{
			// Next beam leave current loop
			break;
		}
		else if(lineData.Find(m_sAccessory)==0)
		{
			// Store the file pos
			m_iPosAcc = file->GetPosition();

			// Loop and store accessories
			while(!eof)
			{
				// Extract data
				eof=!file->ReadString(lineData);
				
				if(lineData.GetLength())
				{
					// Create new instance
					accData = new CImpAswDataAcc;

					// Extract the quantity
					iPos = lineData.Find(" off ");
					tmp = lineData.Mid(0, iPos);
					accData->m_iQuantity = atoi(tmp);

					// Extract the description
					tmp = lineData.Mid(iPos+5);

					accData->m_sProduct = tmp;

					// Add pointer to the linked list
					m_tplDataAcc.AddTail(accData);
					
				}
				else
				{
					// No more accessories
					break;
				}
			}
		}
		else if(lineData.Find(m_sComment) == 0)
		{
			// Loop now until end of file
			while(!eof)
			{
				eof=!file->ReadString(lineData);

				// Dont add last line
				if(lineData.Find("ends here") == -1 && lineData.GetLength())
				{
					lineData+=_T("\n");
					m_sOrderComment+=lineData;
				}
			}
			break;
		}
		// Read string data
		eof=!file->ReadString(lineData);
	}

	// Add class instance into pointer
	m_tplDataList.AddTail(beamData);



	return(done);
}

void CImportAswFile::createHole(CString data, CString punch, CImpAswData *pBeam)
{
	CImpAswDataHole *beamHole = new CImpAswDataHole;
	CString			tmp;
	int				iPos;
	
	// Extract the position
	iPos = data.Find(_T("at"));
	tmp = data.Mid(iPos+3);

	// Set member variables
	beamHole->m_sPunchCode = punch;
	beamHole->m_iPos = atoi(tmp);

	if(m_startOffset > 0)
	{
		// Creating sub beams, offset the current hole pos
		beamHole->m_iPos -= m_startOffset;
	}


	// Add data to list
	pBeam->m_tplDataHoles.AddTail(beamHole);


	return;
}

void CImportAswFile::createDocItems()
{
	CDlgNewProject	newProj;
	CImpAswData		*walker=NULL;
	CItem			*pItem=NULL;
	char			buf[250];
	int				itemID=1;
	POSITION		pos;
	CDlgItemList	ImportDlg;
	CDaoDatabase	*pDB = m_pDoc->m_pProjectSettings->m_pDB;
	CDaoProductCode	*prodCode = new CDaoProductCode(pDB);
	CDlgWernik		dlgWernik;
	CString			sProduct;



	// Set user data
	newProj.m_editCustomerName = m_sCustName;
	newProj.m_editCustomerRef = m_sOrderNum;
	newProj.m_editComments = m_sOrderComment;
	
	// Create dialog
	newProj.DoModal();

	
	// Setup the data captured from dialog
	m_pDoc->m_pProjectHeader->m_nProjectType		= newProj.m_radioProjectType;
	m_pDoc->m_pProjectHeader->m_sProjectName		= newProj.m_editProjectName;
	m_pDoc->m_pProjectHeader->m_sCustomerName		= newProj.m_editCustomerName;
	m_pDoc->m_pProjectHeader->m_sCustomerRef		= newProj.m_editCustomerRef;	
	m_pDoc->m_pProjectHeader->m_sJobDestination		= newProj.m_editJobDestination;
	m_pDoc->m_pProjectHeader->m_sComments			= newProj.m_editComments;


	// Confirm Wernik
	m_iIsWernik = dlgWernik.DoModal();


	// Loop all beams

	// Get the start of the imported data
	pos = m_tplDataList.GetHeadPosition();

	while(pos)
	{
		walker = m_tplDataList.GetAt(pos);

		// Set parameters to filter recordset
		prodCode->m_Type_Ident = "007";//sType;

		if(isWernik())
			sProduct = walker->m_sProduct + _T("W");
		else
			sProduct = walker->m_sProduct;

		prodCode->m_Product_Name_Ident = sProduct;
		// Open the record set
		prodCode->Open();

		// Test if the item is already present in the document
		if(!(pItem=testDuplicate(prodCode)))
		{
			// Create new item
			pItem = m_pDoc->CreateItem(itemID);

			// Set up Item data
			pItem->SetItemID(itemID);
			pItem->SetBeam(true);
			pItem->SetType(1);
			pItem->SetProductCode(prodCode->m_ProductCode);
			pItem->SetProductName(prodCode->m_Aviion_Desc);
			pItem->SetProfile(prodCode->m_ProductName);
			pItem->SetSectionID(prodCode->m_Section_ID);
			pItem->SetProductWeight(prodCode->m_Weight);

			pItem->SetGauge(0);
			pItem->SetDepth(0);
			pItem->SetTopFlange(0);
			pItem->SetTopFlangeSlope(0);
			pItem->SetTopFlangeLip(0);
			pItem->SetBottomFlange(0);
			pItem->SetBottomFlangeSlope(0);
			pItem->SetBottomFlangeLip(0);
			pItem->SetDimC(0);
			pItem->SetDimF(0);

			itemID++;
		}

		// Add element to item
		addElement(pItem, walker);

		// Get next beam
		m_tplDataList.GetNext(pos);
		
		// Close record set
		prodCode->Close();
	}

	// Document modified
	m_pDoc->SetModifiedFlag();
	m_pDoc->SetTitle(NULL);

	// Convert import filename to document filename
	if(m_pDoc->m_pProjectSettings->m_sProjectInputPath.GetLength())
	{
		strcpy(buf, m_pDoc->m_pProjectSettings->m_sProjectInputPath);
		strcat(buf, "\\");
	}
	else
		strcpy(buf, "C:\\");

	strcat(buf, m_pDoc->m_pProjectHeader->m_sProjectName);
	strcat(buf, ".od3");
	m_pDoc->SetPathName(buf, false);

	m_pDoc->UpdateAllViews(NULL,NULL,NULL);

	// Restore mirror line associations
	m_pDoc->storeMirrorAsso();

	// Set current document pointer
	ImportDlg.m_pDoc = m_pDoc;
	ImportDlg.DoModal();

	return;
}

CItem *CImportAswFile::testDuplicate(CDaoProductCode *code)
{
	CItem		*pItem=NULL;
	POSITION	pos;
	CString		sListedCode;
	bool		found	= false;


	// Any items ?
	if(m_pDoc->m_tplItemList.GetCount() > 0)
	{
		// Get head pointer
		pos = m_pDoc->m_tplItemList.GetHeadPosition();

		// Loop all items in document
		while(pos)
		{
			// Get current item
			pItem = m_pDoc->m_tplItemList.GetAt(pos);
			sListedCode = pItem->GetProductCode();

			// Compare items
			if(sListedCode == code->m_ProductCode)
			{
				// Match
				found=true;
				break;
			}
			
			// Get the next item from the document
			pItem = m_pDoc->m_tplItemList.GetNext(pos);
		}
	}


	if(!found)
		return(NULL);
	else
		return(pItem);

}

void CImportAswFile::addElement(CItem *pItem, CImpAswData *data)
{
	CString			sSection, sComment;
	CBeamElement	*pBeam = new CBeamElement;


	// Set data
	pBeam->m_pItem = pItem;
	pBeam->SetMark(data->m_sMark);
	pBeam->SetQty(data->m_iQuantity);
	
	// Not required for line 3
	pBeam->SetBundle(0);
	pBeam->SetComment("");

	pBeam->SetLength(data->m_iLength);
	pBeam->SetMemberType(1);
	pBeam->SetOHang1(0);
	pBeam->SetOHang2(0);
	pBeam->SetSPCode(_T("NON"));
	pBeam->SetSpan1(0);
	pBeam->SetSpan2(0);
	pBeam->SetSpan3(0);	
	pBeam->SetCol1(0);
	pBeam->SetCol2(0);
	pBeam->SetEBSlope(0);
	
	// add non-standard holes
	addHoles(pBeam, data);

	pItem->CreateOrderedBeamList(pBeam);
	pItem->ResetBeamCounter();


	return;
}



void CImportAswFile::addHoles(CBeamElement *pElement, CImpAswData *data)
{
	CString			szOperation;
	CString			szOpType;
	long			nScriptID = 10;
	int				nOpSeq=0, seq;
	CBeamOps		*pBeamOp=NULL;
	POSITION		holePos;
	CImpAswDataHole	*holes=NULL;

	// Get the head position for the holes
	holePos = data->m_tplDataHoles.GetHeadPosition();

	while(holePos)
	{
		// Get hole data
		holes = data->m_tplDataHoles.GetAt(holePos);

		// Loop and set dim and punch data
		for (seq=0; seq<2; seq++)
		{
			// Move sequence
			nOpSeq++;

			if(seq == 0)
			{
				szOpType = _T("Dim");
				szOperation.Format("%i", holes->m_iPos);
			}
			else
			{
				szOpType = _T("Punch");

				if(isWernik())
					szOperation = holes->m_sPunchCode + _T("W");
				else
					szOperation = holes->m_sPunchCode;
			}

			// Create new instance
			pBeamOp = new CBeamOps();

			// Set data
			pBeamOp->SetOpSeqID(nOpSeq);
			pBeamOp->SetOpType(szOpType);
			pBeamOp->SetAbsolute(true);
			pBeamOp->SetPositive(true);
			pBeamOp->SetMultiplied(true);
			pBeamOp->SetMultiplier(1);
			pBeamOp->SetOperation(szOperation);


			if(seq==1)
			{
				pBeamOp->SetComment("");
				pBeamOp->SetCSunk(false);
			}

			pBeamOp->SetScriptID(nScriptID);

			pElement->m_tplAddList.AddTail(pBeamOp);
		}

		// Get the next hole
		data->m_tplDataHoles.GetNext(holePos);
	}

	
	return;
}

int CImportAswFile::storeBeamLength(CString lineData, CImpAswData *beamData)
{
	int iPos, iPos2, res=0;

	if( (iPos=lineData.Find(m_sLenPunch) != -1) ||
					(iPos=lineData.Find(m_sLenNoPunch) != -1))
	{
		// Punched
		if((iPos=lineData.Find(m_sLenPunch)) != -1)
		{
			// Extract length for punched beam
			iPos2 = lineData.Find(_T(" is"))+3;
			beamData->m_iLength = atoi(lineData.Mid(iPos2, iPos-iPos2));

			// Extract punch count
			beamData->m_iPunchCount = atoi(lineData.Mid(iPos+m_sLenPunch.GetLength()));
		}
		else
		{
			// Extract length for unpunched beam
			iPos=lineData.Find("long ");
			iPos2 = lineData.Find(_T(" is"))+3;
			beamData->m_iLength = atoi(lineData.Mid(iPos2, iPos-iPos2));
		}

		res=1;
	}


	return(res);
}

int CImportAswFile::storeMatName(CString lineData, CImpAswData *beamData)
{
	int		iPos, iPos2, res=0;;
	CString	tmp;


	if((iPos=lineData.Find(m_sBeamType)) != -1)
	{
		// Extract beam type
		iPos2 = lineData.Find(_T(" x "));
		beamData->m_sProduct = lineData.Mid(m_sBeamType.GetLength()+1, iPos2-m_sBeamType.GetLength()-1);

		// Extract beam thickness
		if((iPos = lineData.Find( _T("mm"))) != -1)
		{
			beamData->m_sProduct += lineData.Mid(iPos2+3, (iPos-iPos2)-3);
		}

		// Source added to combat bug in SwageDetail //////////
		if(iPos==-1)
		{
			iPos=lineData.Find(_T("material"));
			tmp = lineData.Mid(iPos2+3, (iPos-iPos2)-5);
			beamData->m_sProduct += tmp;
		}
		///////////////////////////////////////////////////////

		// Test for a decimal point
		if((iPos=beamData->m_sProduct.Find('.')) != -1)
		{
			// Remove the decimal point
			beamData->m_sProduct.Remove('.');
		}
		else
		{
			// Append zero to the end
			beamData->m_sProduct += _T("0");
		}

		res=1;
	}


	return(res);
}

int CImportAswFile::storeQuantity(CString lineData, CImpAswData *beamData)
{
	int	iPos,res=0;

	if((iPos=lineData.Find(m_sQuantity)) != -1)
	{
		// Extract beam quantity
		beamData->m_iQuantity = atoi(lineData);

		res=1;
	}


	return(res);
}

CImpAswData *CImportAswFile::storeHoles(CString lineData, CImpAswData *beamData, CStdioFile *file, int *res)
{
	int			markCount=0, iPos;
	int			cutPos, shortCount=1;
	CString		prevProduct, tmp;
	CImpAswData	*newbeamData=NULL;
	int			prevQuantity;
	

	// Set return flag
	*res=0;

	if(lineData.GetLength())
	{
		// Test for end of short beam
		if(lineData.Find(m_sCutMark) > -1)
		{
			// Store lengths and split mark number
			if(m_fullLength == 0)
			{
				// Store beam full length
				m_fullLength = beamData->m_iLength;

				// Split mark number
				splitMark(beamData->m_sMark);
			}

			// Extract cutting mark position
			iPos=lineData.Find(" at ");
			cutPos = atoi(lineData.Mid(iPos+4));
			
			// Store in data struct
			beamData->m_iLength = cutPos-m_startOffset;

			// Calculate remaining length
			m_beamRemain = m_fullLength-cutPos;

			// Calculate false start pos
			m_startOffset = cutPos;

			// Add class instance into pointer
			m_tplDataList.AddTail(beamData);

			// Store current information
			prevProduct = beamData->m_sProduct;
			prevQuantity = beamData->m_iQuantity;

			// Create new instance
			newbeamData = new CImpAswData;

			// Store data
			//beamData->m_iPunchCount = 0;
			newbeamData->m_iQuantity = prevQuantity;
			newbeamData->m_sProduct = prevProduct;

			if(m_iMarkSplit > 0)
			{
				// Change current mark numbers
				if(m_iMarkSplitInc==0)
					beamData->m_sMark = m_sMarkSplit.GetAt(0);

				// Perform pointer memory boundary test
				if(m_sMarkSplit.GetSize() < m_iMarkSplitInc)
				{
					// Attempting to read past limits
					newbeamData->m_sMark = _T("SCR");
				}
				else
				{
					newbeamData->m_sMark = m_sMarkSplit.GetAt(++m_iMarkSplitInc);
				}
			}
			else
			{
				// Store first mark
				if(m_iMarkSplitInc == 0)
					m_sStoreFirstMark = beamData->m_sMark;

				// No split character found append value to marks
				tmp.Format("%s_%i", m_sStoreFirstMark.GetBuffer(m_sStoreFirstMark.GetLength()), m_iMarkSplitInc);
				beamData->m_sMark = tmp;

				tmp.Format("%s_%i",m_sStoreFirstMark.GetBuffer(m_sStoreFirstMark.GetLength()), ++m_iMarkSplitInc);
				newbeamData->m_sMark = tmp;
			}
			
			newbeamData->m_iLength = m_beamRemain;
		}
		// Add holes to current beam
		else if(lineData.Find(m_sRound) == 0)
		{
			createHole(lineData, _T("SR"), beamData);
			*res=1;
		}
		else if(lineData.Find(m_sSquare) == 0)
		{
			createHole(lineData, _T("SS"), beamData);
			*res=1;
		}
		else if(lineData.Find(m_sFlange) == 0)
		{
			createHole(lineData, _T("SF"), beamData);
			*res=1;
		}
		else if(lineData.Find(m_sFour) == 0)
		{
			createHole(lineData, _T("SX"), beamData);
			*res=1;
		}
		else if(lineData.Find(m_sTop) == 0)
		{
			createHole(lineData, _T("ST"), beamData);
			*res=1;
		}
		else if(lineData.Find(m_sBottom) == 0)
		{
			createHole(lineData, _T("SB"), beamData);
			*res=1;
		}
		else if(lineData.Find(m_sTopFlange) == 0)
		{
			createHole(lineData, _T("SU"), beamData);
			*res=1;
		}
		else if(lineData.Find(m_sBottomFlange) == 0)
		{
			createHole(lineData, _T("SD"), beamData);
			*res=1;
		}
	}


	return(newbeamData);
}

void CImportAswFile::splitMark(CString mark)
{
	bool	res=false;
	int		iPos, markCount=1, shortCount;
	int		markPos[30], i, endPos, inc=0;
	CString	str, strTmp;


	if((iPos = mark.Find("|")) > -1)
	{	
		// Clean count
		shortCount = 1;

		// Clean array
		memset(markPos, 0, sizeof(markPos));

		markPos[markCount++] = iPos+1;
		// Count seperation marks
		while(iPos > 0)
		{
			iPos=markPos[markCount] = mark.Find("|", markPos[markCount-1]+1)+1;
			markCount++;
		}

		// Break up string and store marks
		for(i=0; i<markCount-1; i++)
		{
			if(markPos[i+1] == 0)
				endPos = mark.GetLength()+1 - markPos[i];
			else
				endPos = markPos[i+1]-markPos[i];

			str = mark.Mid(markPos[i], endPos-1);
			
			// Add to string array
			m_sMarkSplit.Add(str);
		}

		// Store mark count
		m_iMarkSplit = markCount-1;

		// Test the split marks for duplications
		for(i=0; i<m_iMarkSplit; i++)
		{
			inc=1;
			// Get the current mark selection
			str = m_sMarkSplit.GetAt(i);

			// Dont read past array pointer boundaries
			if(i < m_iMarkSplit-1)
			{
				// Get the string for testing
				strTmp = m_sMarkSplit.GetAt(i+1);

				// Loop until mark variance
				while(str==strTmp && inc<(m_iMarkSplit-i))
				{
					// Append the incrementor value to the string
					strTmp.Format("%s_%i", str, inc);
					// Remove old string
					m_sMarkSplit.RemoveAt(inc+i, 1);
					// Free memory
					m_sMarkSplit.FreeExtra();
					// Store new mark string
					m_sMarkSplit.InsertAt(inc+i, strTmp);

					// Move to next position
					inc++;

					// Dont read past array pointer boundaries
					if(inc<m_iMarkSplit-i)
						strTmp = m_sMarkSplit.GetAt(inc+i);
				}

				// Append a zero to the first match
				if(inc > 1)
				{
					str=m_sMarkSplit.GetAt(i);
					// Remove old string
					m_sMarkSplit.RemoveAt(i, 1);
					// Free memory
					m_sMarkSplit.FreeExtra();
					// Store new mark string
					m_sMarkSplit.InsertAt(i, str+=_T("_0"));
				}
			}
		}
	}


	return;
}
