// ProductMods.cpp: implementation of the CProductMods class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "od3.h"
#include "ProductMods.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProductMods::CProductMods()
{
	// Clean arrays
	memset(m_line1, 0, sizeof(m_line1));
	memset(m_line2, 0, sizeof(m_line1));
	memset(m_line3, 0, sizeof(m_line1));

	// User warning suppression
	warn = true;

	loadStdFile();
}

CProductMods::~CProductMods()
{

}

void CProductMods::loadStdFile()
{
	CString	lineData;
	int		next=1, stage=1, count=0;
	CString	path;
	char	*buffer;


	// File flag
	fileOK = false;

	if((buffer=getenv("OD3_HOME")))
	{
		// Set the string
		path = buffer;
				
		// Append the file name
		path += _T("products.txt");

		try
		{
			CStdioFile	file(path, CFile::modeRead);

			do
			{
				next = file.ReadString(lineData);

				if(lineData.Left(2).CompareNoCase("//"))
				{
					if(!lineData.Compare(_T("$$SECTIONS$$")))
					{
						while(stage)
						{
							stage = file.ReadString(lineData);

							if(!lineData.CompareNoCase("$$END$$"))
							{
								// End of line product selection
								stage=0;
							}
							else
							{
								// Not commented out in file
								m_lineDes[count] = lineData;
							}
							count++;
						}
					}

					// Relevent data so process it
					if(!lineData.Compare(_T("$$LINE_1$$")))
					{
						stage=1;
						count=0;
						while(stage)
						{
							stage = file.ReadString(lineData);
							if(lineData.Left(2).CompareNoCase("//") && 
								lineData.Left(2).CompareNoCase("$$"))
							{
								// Not commented out in file
								m_line1[count] = true;
							}
							else if(!lineData.CompareNoCase("$$END$$"))
							{
								// End of line product selection
								stage=0;
							}
							count++;
						}
					}

					else if(!lineData.Compare(_T("$$LINE_2$$")))
					{	
						stage=1;
						count=0;
						while(stage)
						{
							stage = file.ReadString(lineData);
							if(lineData.Left(2).CompareNoCase("//") && 
								lineData.Left(2).CompareNoCase("$$"))
							{
								// Not commented out in file
								m_line2[count] = true;
							}
							else if(!lineData.CompareNoCase("$$END$$"))
							{
								// End of line product selection
								stage = 0;
							}
							count++;
						}
					}
					else if(!lineData.Compare(_T("$$LINE_3$$")))
					{	
						stage=1;
						count=0;
						while(stage)
						{
							stage = file.ReadString(lineData);
							if(lineData.Left(2).CompareNoCase("//") && 
								lineData.Left(2).CompareNoCase("$$"))
							{
								// Not commented out in file
								m_line3[count] = true;
							}
							else if(!lineData.CompareNoCase("$$END$$"))
							{
								// End of line product selection
								stage = 0;
							}
							count++;
						}
					}
				}
			}
			while(next);

			// Release file pointer
			file.Close();
			// File flag
			fileOK = true;
		}
		catch(CFileException *e)
		{
			// Delete exception
			e->Delete();
		}
	}

	return;
}
