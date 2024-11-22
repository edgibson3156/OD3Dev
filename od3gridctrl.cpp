////////////////////////////////////////////////////////////////////////////
// od3gridctrl.cpp : implementation of the COD3GridCtrl class
//
#include "stdafx.h"
#include "OD3.h"
#include "od3gridctrl.h"
#include "gwizgco.h"


#ifdef _GWEXTDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif


//Insert your include files here  (Important if using GridWiz as an extension DLL)


#ifdef _GWEXTDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

/////////////////////////////////////////////////////////////////////////////
// COD3GridCtrl
IMPLEMENT_DYNCREATE(COD3GridCtrl, CGWGridCtrl)
IMPLEMENT_GW_CUSTOM_CONTROL(COD3GridCtrl)

BEGIN_MESSAGE_MAP(COD3GridCtrl, CGWGridCtrl)
	//{{AFX_MSG_MAP(COD3GridCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_GRIDCELL_MAP(COD3GridCtrl)

	MAPHCOL(0, 0, CGWHeaderCell)
	MAPHROW(0, 0, CGWHeaderCell)
	MAPGRID(CGWEditCell)
	END_GRIDCELL_MAP()

/////////////////////////////////////////////////////////////////////////////
// COD3GridCtrl construction/destruction

COD3GridCtrl::COD3GridCtrl()
{
	GCOMap();
	Initialize();	
}

COD3GridCtrl::~COD3GridCtrl()
{
}

void COD3GridCtrl::Initialize()
{                              
	//Do not modify or delete the following block of macros including the comments.
	//For use with GridWiz Wizard.
    
	//{COD3GridCtrl::Initialize}  
	GW_INITIALIZATIONFILE(_T(""));
	GW_ADDROW(0);
	GW_AUTOSIZECOLUMNS(TRUE);
	GW_GRIDSTYLE(GS_NORMAL | GS_MULTIPLE);
	GW_BACKCOLOR(16777215);
	GW_BORDER(TRUE);
	GW_COLS(NCOLS-1);
	GW_COLSELECT(FALSE);
	GW_COLSIZE(TRUE);
	GW_COLUMNWIDTH(12);
	GW_DISABLENOSCROLL(SB_VERT);
	GW_DRAGANDDROP(FALSE);
	GW_FIXEDCELLCOLOR(12632256);
	GW_FOCUSRECT(TRUE);
	GW_FONTBOLD(FALSE);
	GW_FONTFACENAME(_T("Arial"));
	GW_FONTITALIC(FALSE);
	GW_FONTPOINTSIZE(10);
	GW_GRIDLINECOLOR(8421504);
	GW_GRIDLINES(TRUE);
	GW_HIGHLIGHTSELECTION(TRUE);
	GW_PENWIDTH(1);
	GW_PRINTCAPTION(_T("GridView Print Caption"));
	GW_RECORDSETENABLE(FALSE);
	GW_ROWCOLUNITS(CHARS);
	GW_ROWHEIGHT(DEFAULT_TO_FONT);
	GW_ROWS( NROWS-1 );
	GW_ROWSELECT(TRUE);
	GW_ROWSIZE(FALSE);
	GW_SCROLLBARS(SB_BOTH);
	GW_SHOWCURRENTCELL(TRUE);
	GW_SIZINGREGIONWIDTH(6);
	GW_SYNCHRONIZEPANES(FALSE);
	GW_TEXTCOLOR(0);
	GW_THUMBSCROLL(FALSE);
	//{COD3GridCtrl::Initialize End}    
#if 0
    int nWidth = ::GetSystemMetrics(SM_CXHTHUMB);

	for (int x = 0; x <m_nFixedColumns; x++)
	{
		SetColWidth(x, (float) nWidth*2, FALSE, PIXELS);
	}
	UpdateGridSettings(&m_GridGlobalSettings);*/
#endif
	m_bSendCommandsToParent = FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// COD3GridCtrl::GridOnInitialUpdate
//
// virtual void GridOnInitialUpdate();
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Remarks
//		This virtual function is called as part of the document creation process and also when 
// 	splitter panes are added to the view. This function will initially create the font and then
// 	save the default cursor handle.	If a splitter frame is being openned, It will copy 
// 	its display characteristics from the view at location 0,0. If you override this function,
// 	be sure to call this also.
////////////////////////////////////////////////////////////////////////////////////////////////////
void COD3GridCtrl::GridOnInitialUpdate()
{
	//There are three choices when hooking the grid to data. You will use only one of these
	//mechanisms. 

	//(1) Use the internal data structure possibly coupled with a initialization file. If you
	//use this method, the grid will automatically store changes. You may need to load and 
	//unload the grid using functions like OnSetCellText() and OnGetCellText().
	AttachInternalDataSource();		  // (Default)

	//(2) Attach to a CGWDataSource object which is stored eleswhere. This GWDataSource can
	//be based on an ODBC recordset, a DAO recordset or a simple CCellDatamap. You can still
	//use a initialization file. Using this method, you can also serialize the data source 
	//to a file if you want.
	//AttachDataSource(&GetDocument()->m_MyDataSource);    //You create the datasource and attach 
														   //it to the grid using this function. 

	//(3) Don't attach to any data source at all. This will place the grid in "virtual" mode.
	//You will need to Override functions like OnGetCellText() and OnSetCellText() and 
	//store and retrieve the data yourself. 
    
	
	//Calling the base class implementation. This is necessary to realize all
	//default property settings like fonts, colors, scrollbars, etc.
	CGWGridCtrl::GridOnInitialUpdate(); 

	////////////////////////////////////////////////////////////////////////////////
	//For performance reasons, place your initial sheet/row/col/range/cell property
	//settings here. By placing your property setting function calls here, you can 
	//avoid refreshing the grid needlessly!
	//Start property settings
		//Place property setting function calls here, if any.
//		this->
	this->SetNumRows(NROWS);
	this->SetNumColumns(NCOLS);
	

	int nBegRowNdx = 0;
	int nEndRowNdx = NROWS-1;
	int nBegColNdx = 0;
	int nEndColNdx = NCOLS-1;
	int nRow;
	int nCol;
	int nFontPointSize, nMaxLen, nSheet; 

	nSheet = CURRENT_SHEET;

	// Set header text and background colour
	this->SetRowTextColor(0, 0, RGB(255,255,255), nSheet);
	this->SetRowBackColor(0, 0, RGB(170,170,200), nSheet);

	this->SetColTextColor(0, 0, RGB(255,255,255), nSheet);
	this->SetColBackColor(0, 0, RGB(170,170,200), nSheet);

	// Set punch data text colour
	this->SetColTextColor(2, 2, RGB(0,0,255), nSheet);


	//set column headers
	nFontPointSize = 8;
	nMaxLen = 12;
//	this->SetRowMaxTextLength(nBegRowNdx, nBegRowNdx, nMaxLen, nSheet); 
	this->SetTextAlignment(nBegRowNdx, nBegColNdx+1, nBegRowNdx, nEndColNdx, 1, 1, FALSE, nSheet);
	this->SetRowFontPointSize(nBegRowNdx, nBegRowNdx, nFontPointSize, nSheet);
	for(nCol=1; nCol<=NCOLS-1; ++nCol)
	{
		CString csCol;
		CString csCellText;
		csCol.Format("%d",nCol),
		csCellText = _T(" Op.");
		csCellText += csCol;
		LPTSTR lpszCellText = csCellText.GetBuffer(1);

		if(nCol==6)
			SetCellText(nBegRowNdx, nCol, "Comment", nSheet);
		else
			SetCellText(nBegRowNdx,nCol,lpszCellText, nSheet);
	}	

	
	//set row headers
	nFontPointSize = 8;
	this->SetColMaxTextLength(nBegColNdx, nBegColNdx, nMaxLen, nSheet); 
	this->SetTextAlignment(nBegRowNdx+1, nBegColNdx, nEndRowNdx, nBegColNdx, 1, 1, FALSE, nSheet);
	this->SetColFontPointSize(nBegColNdx, nBegColNdx, nFontPointSize, nSheet);
	for(nRow=1;nRow<=NROWS;++nRow)
	{
		CString csRow;
		CString csCellText;
		csRow.Format("%d",nRow),
		csCellText = _T(" Hit ");
		csCellText += csRow;
		LPTSTR lpszCellText = csCellText.GetBuffer(1);
		this->SetCellText(nRow,nBegColNdx,lpszCellText, nSheet);
	}	

	// force uppercase characters
//	CString csInputMask = ">";
//  SetInputMask(nBegRowNdx+1, nBegColNdx+1, nEndRowNdx, nEndColNdx, csInputMask, nSheet);  

	// set up 'cell' context menu (right button click)
	CGWContextMenu* pMenu = new CGWContextMenu(_T("GridCM"), this->m_pGWDataSource);
	pMenu->AppendMenu(MF_STRING, ID_EDIT_COPY, _T("Copy"));
	pMenu->AppendMenu(MF_STRING, ID_EDIT_CUT, _T("Cut"));
	pMenu->AppendMenu(MF_STRING, ID_EDIT_PASTE, _T("Paste"));
	pMenu->AppendMenu(MF_STRING, ID_EDIT_CLEAR, _T("Clear"));
	this->OnRegisterContextMenu(pMenu);
	this->SetContextMenu(pMenu, FALSE, 0); 


	// set up 'header' context menu (right button click)
	CGWContextMenu* pHeaderMenu = new CGWContextMenu(_T("HeadingCM"), this->m_pGWDataSource);
	pHeaderMenu->AppendMenu(MF_STRING, ID_EDIT_COPY, _T("Copy"));
	pHeaderMenu->AppendMenu(MF_STRING, ID_EDIT_CUT, _T("Cut"));
	pHeaderMenu->AppendMenu(MF_STRING, ID_EDIT_PASTE, _T("Paste"));
	pHeaderMenu->AppendMenu(MF_STRING, ID_EDIT_CLEAR, _T("Clear"));
	pHeaderMenu->AppendMenu(MF_SEPARATOR, 0);
	pHeaderMenu->AppendMenu(MF_STRING, ID_GW_SORT_ASCENDING, _T("Ascending"));
	pHeaderMenu->AppendMenu(MF_STRING, ID_GW_SORT_DESCENDING, _T("Descending"));
	pHeaderMenu->AppendMenu(MF_SEPARATOR, 0);
//	pHeaderMenu->AppendMenu(MF_STRING, ID_MY_COMMAND, _T("My Command"));
	this->OnRegisterContextMenu(pHeaderMenu);
	this->SetRowContextMenu(0,0,pHeaderMenu, 0);
	

	//End property settings
	////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////
	//Finally, activate the sheet. This will cause the initial grid to be rendered
	//and any predefined SQL or database requests to be processed. This should be 
	//the last thing done in this function.
	ActivateSheet(0);
}


void COD3GridCtrl::InitializeColWidths()
{
	CGWGridCtrl::InitializeColWidths();
}


void COD3GridCtrl::OnCellSelChange(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, int nItemCount, CString* pSelection, void* pExtraData, int* pItems, BOOL& bSendExtraData)
{
	CGWGrid::OnCellSelChange(nRowNdx, nColNdx, pGCO, nItemCount, pSelection, pExtraData, pItems, bSendExtraData);
}




void COD3GridCtrl::OnCopyRow(UINT nBegRowNdx, UINT nEndRowNdx, UINT nInsertBefore, int nSheet)
{
	CGWGridCtrl::OnCopyRow(nBegRowNdx, nEndRowNdx, nInsertBefore, nSheet);
}


void COD3GridCtrl::OnDeleteRow(int nRowNdx, int nCount, int nSheet)
{
	CGWGridCtrl::OnDeleteRow(nRowNdx, nCount, nSheet);
}


void COD3GridCtrl::OnGetCellContextMenu(int nRowNdx, int nColNdx, CString csContextMenuName, CMenu*& pContextMenu)
{
	//TODO: Implement code to handle this event. Assign a popup menu to pContextMenu.
}


void COD3GridCtrl::OnGetCellText(int nRowNdx, int nColNdx, CString& csCellText)
{
	CGWGridCtrl::OnGetCellText(nRowNdx,  nColNdx, csCellText);
}


void COD3GridCtrl::OnSetCellText(int nRowNdx, int nColNdx, CString& csCellText)
{
	// 1. capture the string
	// 2. get the first character
	// 3. check for illegal entries
	// 4. check for dimension op.
	// 5. check for punch op.

	char* m_psz = csCellText.GetBuffer(1);
//	int nBegColNdx = 1;
	int nSheetNdx = CURRENT_SHEET;
	int wRowNdx = nRowNdx;
	int wColNdx = NCOLS-1;
	UINT nFlags = 0;
	UINT bScrollToTop = 0;
	UINT bScrollToLeft = 0;
	BOOL bErase = FALSE;
	CString csErrMessage = "Illegal entry";
	bool bErr = false;

	// check for illegal entries
	if(csCellText != _T("") && csCellText.Left(4) != _T(" Op.") && csCellText.Left(4) != _T(" Hit"))
	{
		if(*m_psz >90)
		{
			if(*m_psz > 96 && *m_psz < 123 && csCellText.GetLength()==1)
			{
				*m_psz -= 32;
				csCellText = (CString)m_psz;
			}
			else
			{
				bErr = true;
			}
//		SetCurCell(nRowNdx, nColNdx, nFlags, bScrollToTop, bScrollToLeft); 
//		InvalidateCell(nRowNdx, nColNdx, bErase); 
//		csCellText = _T("");
//		CGWGridCtrl::OnSetCellText(nRowNdx, nColNdx, csCellText);
//		return;
		}
		else if(*m_psz < 48)
		{
			switch (*m_psz)
			{
			case 42:
				// we've got a multiplier!!
				break;
			case 43:
				// its relative and its positive
				break;
			case 45:
				// its relative and its negative
				break;
			case 47:
				// we've got a divisor!!
				break;
			case 35:
				//	its a hash punch code  - so set focus to last col in this row
				//	if user pressed the tab key then set next cell will be set to first col of next row	*/ 
				if(IsRowHidden(nRowNdx+1, nSheetNdx)){bScrollToTop = TRUE;}
				SetCurCell(wRowNdx, wColNdx, nFlags, bScrollToTop, bScrollToLeft); 
				break;
			case -40:
				//	its an SBE D3 import code  - so set focus to last col in this row
				//	if user pressed the tab key then set next cell will be set to first col of next row	*/ 
				if(IsRowHidden(nRowNdx+1, nSheetNdx)){bScrollToTop = TRUE;}
				SetCurCell(wRowNdx, wColNdx, nFlags, bScrollToTop, bScrollToLeft); 
				break;
			default:
				bErr = true;
				break;
			}
		}
		// check for dimension op.
		else if (*m_psz >47 && *m_psz <58)
		{
			// we've got legal dimension input
		}
			// check for punch op.
		else if (*m_psz >64 && *m_psz <91)
		{
			// we've got an 'alpha' puncnh code
			if(IsRowHidden(nRowNdx+1, nSheetNdx)){bScrollToTop = TRUE;}
			SetCurCell(wRowNdx, wColNdx, nFlags, bScrollToTop, bScrollToLeft);
		}
		else
		{
			// we've got an illegal operation
			bErr = true;
		}

		if (bErr)
		{
			AfxMessageBox(csErrMessage);
			--nColNdx;
		}
	}
	InvalidateCell(nRowNdx, nColNdx, bErase); 
	CGWGridCtrl::OnSetCellText(nRowNdx, nColNdx, csCellText);
	bErr = false;
}

///////////////////////////////////////////////////////////////////////////////////
//
void COD3GridCtrl::RefreshGrid()
{
	int nSheet = CURRENT_SHEET;
		
	BOOL bErase = FALSE;
	int nBegRowNdx = 1;
	int nBegColNdx = 1;
	int nEndRowNdx = NROWS-1;
	int nEndColNdx = NCOLS-1;
	int nRowNdx;
	int nColNdx;
	int nFlags = 0;
	UINT	bScrollToTop = TRUE;
	UINT	bScrollToLeft = FALSE;
	LPSTR	lpszCellText = "";
	CRect	rect;
	float	width;

	// Get the size of the grid
	this->GetClientRect(&rect);
	// Calculate equal widths
	width = (float)rect.Width()/NCOLS;

	SetColWidth(0, 40, FALSE, PIXELS);

	for (nRowNdx =  nBegRowNdx; nRowNdx < (nEndRowNdx +1); ++nRowNdx)
	{
		for (nColNdx =  nBegColNdx; nColNdx < (nEndColNdx +1); ++nColNdx)
		{
			SetCellText(nRowNdx, nColNdx, lpszCellText, nSheet);
			
			if(nColNdx==2)
				SetColWidth(nColNdx, width*3+50, FALSE, PIXELS);
			else if(nColNdx==1 || nColNdx==6)
				SetColWidth(nColNdx, 50, FALSE, PIXELS);
			else
				SetColWidth(nColNdx, (width/3)+6, FALSE, PIXELS);	
		}
	}

	CGWGrid::InvalidateRange(nBegRowNdx, nBegColNdx, nEndRowNdx, nEndColNdx, bErase);	
//	UpdateGridSettings(&m_GridGlobalSettings); 
}

void COD3GridCtrl::OnCellDeactivate(int nRowNdx, int nColNdx, CGWGridCellObject* pGCO, CWnd* pFloatingCtrl, LPDISPATCH pIDispatch)
{

	//TODO: Implement code to handle this event.
//	AfxMessageBox("Trapping cell de-activation");
}

