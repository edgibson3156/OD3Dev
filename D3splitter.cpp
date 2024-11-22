// D3splitter.cpp: implementation of the CD3splitter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "od3.h"
#include "D3splitter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CD3splitter::CD3splitter()
{
	// Set to pass
	m_fileOK = true;

	// Open and read the configuration file
	if(!openConfigFile())
	{
		AfxMessageBox("Failed to read D3 config file");
		// Set to fail
		m_fileOK = false;
	}
}

CD3splitter::~CD3splitter()
{
	POSITION	pos;
	CImportD3Beam	*pBeam=NULL;
	CImportD3Acc	*pAcc=NULL;

	m_sPtrIrvine.RemoveAll();
	m_sPtrWarley.RemoveAll();

	// Remove the Warley list (beams)
	pos = m_tplWarleyBeam.GetHeadPosition();
	while(pos)
	{
		pBeam = m_tplWarleyBeam.GetNext(pos);
		delete(pBeam);
	}
	m_tplWarleyBeam.RemoveAll();

	// Remove the Irvine list (beams)
	pos = m_tplIrvineBeam.GetHeadPosition();
	while(pos)
	{
		pBeam = m_tplIrvineBeam.GetNext(pos);
		delete(pBeam);
	}
	m_tplIrvineBeam.RemoveAll();

	// Remove the Warley list (accessories)
	pos = m_tplWarleyAcc.GetHeadPosition();
	while(pos)
	{
		pAcc = m_tplWarleyAcc.GetNext(pos);
		delete(pAcc);
	}
	m_tplWarleyAcc.RemoveAll();

	// Remove the Irvine list (accessories)
	pos = m_tplIrvineAcc.GetHeadPosition();
	while(pos)
	{
		pAcc = m_tplIrvineAcc.GetNext(pos);
		delete(pAcc);
	}
	m_tplIrvineAcc.RemoveAll();

	// Remove the other list (accessories)
	pos = m_tplOtherAcc.GetHeadPosition();
	while(pos)
	{
		pAcc = m_tplOtherAcc.GetNext(pos);
		delete(pAcc);
	}
	m_tplOtherAcc.RemoveAll();
}

bool CD3splitter::openConfigFile()
{
	CString	path;
	bool	result=true;

	// Get the exe path
	path=getenv("OD3_HOME");

	// Append the file name
	path += _T("D3Config.txt");


	try
	{
		CStdioFile	file(path, CFile::modeRead);

		// Read the file contents
		readD3Contents(&file);

		// Close the file pointer
		file.Close();
	}
	catch(CFileException *e)
	{
		// Report error
		e->ReportError(MB_ICONINFORMATION);
		// Delete file exception
		e->Delete();
		// Failed
		result = false;
	}

	return(result);
}

void CD3splitter::readD3Contents(CStdioFile *file)
{
	CString	lineData;
	int		eof=0, site=1;

	// Loop until end of file
	while(!eof)
	{
		// Read the next line in the file
		eof = !file->ReadString(lineData);

		if(lineData.GetLength() && (lineData.Find("//") == -1))
		{
			if(!lineData.CompareNoCase("$SITE$"))
			{
				// Read next line (site name)
				eof = !file->ReadString(lineData);

				if(!lineData.CompareNoCase("WARLEY"))
					site = 2;

				// Store the code in the appropriate address
				storeCodes(file, site);
			}
		}
	}

	return;
}

void CD3splitter::storeCodes(CStdioFile *file, int site)
{
	CString	lineData;
	int		eof=0;

	// Loop until end of file
	while(!eof)
	{
		// Read the next line in the file
		eof = !file->ReadString(lineData);

		if(!lineData.CompareNoCase("$END$"))
			break;

		switch(site)
		{
		case 1:
			// IRVINE
			m_sPtrIrvine.Add(lineData);
			break;

		case 2:
			// WARLEY
			m_sPtrWarley.Add(lineData);
			break;
		}
	}

	return;
}

bool CD3splitter::splitD3File(CImportDet3 *import)
{
	POSITION		pos;
	CImportD3Beam	*beam=NULL;
	CImportD3Acc	*acc=NULL;
	int				index=0;
	CBigIni			ini(_T("C:\\test.d3"), 1);


	// Get the head position in the list (beams)
	pos = import->m_tplBeamList.GetHeadPosition();


	// Loop until no more entries
	while(pos)
	{
		// Get the first imported product
		beam = import->m_tplBeamList.GetNext(pos);

		switch(testName(beam->GetProductName()))
		{
		case 0:
			// DAVENTRY or not found
			// Continue as normal allow this product to be added to the document
			break;
		case 1:
			// IRVINE
			// Move this product from the imported list to the irvine list
			moveImportedData(1, beam, import);
			break;

		case 2:
			// WARLEY
			// Move this product from the imported list to the warley list
			moveImportedData(2, beam, import);
			break;
		}
	}
	
	// Get the head position in the list (accessories)
	pos = import->m_tplAccessoryList.GetHeadPosition();

	index = 0;
	// Loop until no more entries
	while(pos)
	{
		// Get the first imported product
		acc = import->m_tplAccessoryList.GetNext(pos);

		switch(testName(acc->GetProductName()))
		{
		case 0:
			// Others (Daventry)
			moveImportedData(0, acc, import);
			break;

		case 1:
			// IRVINE
			// Move this product from the imported list to the irvine list
			moveImportedData(1, acc, import);
			break;

		case 2:
			// WARLEY	
			// Move this product from the imported list to the warley list
			moveImportedData(2, acc, import);
			break;
		}
	}

	
	return(true);
}

int CD3splitter::testName(CString name)
{
	int i, result=0;


	// Loop through sites and products
	for(i=0; i<m_sPtrIrvine.GetSize(); i++)
	{
		CString h = m_sPtrIrvine.GetAt(i);
		if(!m_sPtrIrvine.GetAt(i).CompareNoCase(name.Mid(0,5)))
		{
			result = 1;
			break;
		}
	}

	if(!result)
	{
		for(i=0; i<m_sPtrWarley.GetSize(); i++)
		{
			if(!m_sPtrWarley.GetAt(i).CompareNoCase(name.Mid(0,5)))
			{
				result = 2;
				break;
			}
		}
	}

	return(result);
}

void CD3splitter::moveImportedData(int site, CImportD3Beam *beam, CImportDet3 *import)
{
	POSITION		pos;
	bool			found=false;

	// Count items in list
	if(import->m_tplBeamList.GetCount()==1)
	{
		// Only one item, remove it from the list
		import->m_tplBeamList.RemoveAt(import->m_tplBeamList.GetHeadPosition());
		// Set flag
		found = true;
	}
	else if(import->m_tplBeamList.GetCount() > 1)
	{
		// Get the first list position
		pos = import->m_tplBeamList.GetHeadPosition();

		while(pos)
		{
			// Beam pointer found?
			if(import->m_tplBeamList.GetAt(pos) == beam)
			{
				// Remove the beam from the list
				import->m_tplBeamList.RemoveAt(pos);
				// Set flag
				found = true;
				break;
			}
			
			// Get the next position
			import->m_tplBeamList.GetNext(pos);

			// Is NULL
			if(!pos)
			{
				// Remove the last pointer in the list
				import->m_tplBeamList.RemoveAt(import->m_tplBeamList.GetTailPosition());
				// Set flag
				found = true;
				break;
			}
		}
	}

	// Beam been found?
	if(found)
	{
		switch(site)
		{
		case 1:
			// IRVINE
			// Add the pointer to the Irvine list
			m_tplIrvineBeam.AddTail(beam);
			break;

		case 2:
			// WARLEY
			// Add the pointer to the Warley list
			m_tplWarleyBeam.AddTail(beam);
			break;
		}
	}


	return;
}
void CD3splitter::moveImportedData(int site, CImportD3Acc *acc, CImportDet3 *import)
{
	POSITION		pos;
	bool			found=false;

	// Count items in list
	if(import->m_tplAccessoryList.GetCount()==1)
	{
		// Only one item, remove it from the list
		import->m_tplAccessoryList.RemoveAt(import->m_tplAccessoryList.GetHeadPosition());
		// Set flag
		found = true;
	}
	else if(import->m_tplAccessoryList.GetCount() > 1)
	{
		// Get the first list position
		pos = import->m_tplAccessoryList.GetHeadPosition();

		while(pos)
		{
			// Beam pointer found?
			if(import->m_tplAccessoryList.GetAt(pos) == acc)
			{
				// Remove the beam from the list
				import->m_tplAccessoryList.RemoveAt(pos);
				// Set flag
				found = true;
				break;
			}
			
			// Get the next position
			import->m_tplAccessoryList.GetNext(pos);

			// Is NULL
			if(!pos)
			{
				// Remove the last pointer in the list
				import->m_tplAccessoryList.RemoveAt(import->m_tplAccessoryList.GetTailPosition());
				// Set flag
				found = true;
				break;
			}
		}
	}

	// Accessory been found?
	if(found)
	{
		switch(site)
		{
		case 1:
			// IRVINE
			// Add the pointer to the Irvine list
			m_tplIrvineAcc.AddTail(acc);
			break;

		case 2:
			// WARLEY
			// Add the pointer to the Warley list
			m_tplWarleyAcc.AddTail(acc);
			break;

		default:
			// Others (Daventry)
			// Add the pointer to the others list
			m_tplOtherAcc.AddTail(acc);
			break;
		}
	}


	return;
}

// Test linked list pointer counts
bool CD3splitter::dialogRequired()
{
	if(m_tplIrvineBeam.GetCount() ||
		m_tplWarleyBeam.GetCount() ||
		m_tplIrvineAcc.GetCount() ||
		m_tplWarleyAcc.GetCount() ||
		m_tplOtherAcc.GetCount() )
		return(true);
	else
		return(false);
}
