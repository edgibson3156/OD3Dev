// FolderBrowse.cpp: implementation of the CFolderBrowse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "od3.h"
#include "FolderBrowse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFolderBrowse::CFolderBrowse()
{

}

CFolderBrowse::~CFolderBrowse()
{

}

CString CFolderBrowse::getFolder()
{
	BROWSEINFO		bInfo;
	char			buffer[260] = {'\0'};
	CString			path;

	bInfo.hwndOwner = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	bInfo.pidlRoot = NULL;
	bInfo.pszDisplayName = buffer;
	bInfo.lpfn = NULL;
	bInfo.lpszTitle = _T("Select you custom directory.");
	bInfo.ulFlags = BIF_RETURNFSANCESTORS;


	// Get the folder then retrieve the path
	SHGetPathFromIDList(SHBrowseForFolder(&bInfo), buffer);

	// Set return path
	path = buffer;


	return(path);
}
