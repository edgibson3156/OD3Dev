// BigIni.cpp: implementation of the CBigIni class.
//
//	Functions package for large ( >64k ) ini files.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "BigIni.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBigIni::CBigIni(LPCTSTR lpszFileName )
{
	this->m_szBuffer 		= _T("");
	this->m_szSection 		= _T("");
	this->m_lSectionOffset 	= 0;
	this->m_szFileName 		= lpszFileName;
	this->m_f 				= NULL;

	CFile f;
	CFileException e;

	// Set testing flag
	m_bAttempted=false;
  //open file
	if( !f.Open( this->m_szFileName, CFile::modeRead, &e ) )
	{
		if( e.m_cause == CFileException::fileNotFound )
		{
			AfxMessageBox("File not found");
			return;
		}
		else
		{
			return;
		}
	}

}
CBigIni::CBigIni(LPCTSTR lpszFileName, int flag)
{
	this->m_szBuffer 		= _T("");
	this->m_szSection 		= _T("");
	this->m_lSectionOffset 	= 0;
	this->m_szFileName 		= lpszFileName;
	this->m_f 				= NULL;

	CFile f;
	CFileException e;

	// Set testing flag
	m_bAttempted=false;

  //open file
	if( !f.Open( this->m_szFileName, CFile::modeCreate|CFile::modeWrite, &e ) )
	{
		if( e.m_cause == CFileException::fileNotFound )
		{
			AfxMessageBox("File not created");
			return;
		}
		else
		{
			return;
		}
	}

}

CBigIni::~CBigIni()
{
  //close file
	if( m_f != NULL )
		{
		m_f->Close();
		delete m_f;
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	CBigIni::GetPrivateProfileString()
//
//	Design:
//	
//		seek to section
//		if section found
//			seek to entry
//			if entry found
//				return result
//
//		return default
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CBigIni::GetPrivateProfileString( CString& szSection, 
							 		  CString& szEntry, 
							 		  CString& szDefault, 
							 		  CString& szReturnBuffer )
{
	//seek to section
	BOOL fSection = SeekToSection( szSection );
	if( fSection == TRUE )
	{
		//if section found, seek to entry	
		BOOL fEntry = SeekToEntry( szEntry );
		if( fEntry == TRUE )
		{
	   	  //if entry found, return result 
			szReturnBuffer = m_szBuffer;
			return szReturnBuffer.GetLength();
		}
	}
	
	//return default
	szReturnBuffer = szDefault;
	return szReturnBuffer.GetLength();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	CBigIni::GetPrivateProfileInt()
//
//	Design:
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CBigIni::GetPrivateProfileInt( CString& szSection, 
								   CString& szEntry, 
								   int iDefault )
{
	CString szBuffer = _T("");
	CString szDefault = _T("");
	
	szDefault.Format( "%i", iDefault );
    this->GetPrivateProfileString( szSection, szEntry, szDefault, szBuffer );
    
    return atoi( (const char*)szBuffer );
}								   

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	SeekToSection()
//
//	Design:
//	
//		if current section == section 
//			return true
//			
//		open file
//		scan for section token
//		if section token found
//			set section details for use later
//			return true
//			
//		return false			
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CBigIni::SeekToSection( CString& szSection )
{
  //if current section == section, return true
	if( this->m_szSection == szSection )
		return TRUE;

  //open file
	if( this->m_f == NULL )
	{
		this->m_f = new CStdioFile();
		CFileStatus fState;
		CFileException e;

		// Only try this once
		if(!m_bAttempted)
		{
			m_bAttempted=true;

			// Get the file state
			CFile::GetStatus(m_szFileName, fState);
			
			// Test for read only
			if(fState.m_attribute & CFile::readOnly)
			{
				try
				{
					// Set the attribute field
					fState.m_attribute = CFile::normal;
					// Attempt to convert to normal attributes
					CFile::SetStatus(m_szFileName, fState);
				}
				catch(CFileException *fe)
				{
					// Delete exception and continue
					fe->Delete();
				}

				// Retest file
				CFile::GetStatus(m_szFileName, fState);
				if(fState.m_attribute & CFile::readOnly)
				{
					// Warn user the import will fail
					AfxMessageBox("Can not import read only D3 files, OD3 has attempted to change to all access but has failed.\nPlease remove read only properties manually",MB_ICONWARNING);
				}
			}
		}

		
		if( !this->m_f->Open( this->m_szFileName, CFile::modeReadWrite, &e ) )
		{
			delete this->m_f;
			this->m_f = NULL;
			return FALSE;
		}
	}

  //scan for section token
	char szBuffer[1024];
	CString szSectionKey = "[";
	szSectionKey += szSection;
	szSectionKey += "]";

  //start from current section offset
  //note that this assumes that details are sorted as follows
  //document... beam 0,1,2 ... accessory 0,1,2...
	this->m_f->Seek( this->m_lSectionOffset, CFile::begin );

	while( this->m_f->ReadString( szBuffer, sizeof( szBuffer )-1 ) != NULL )
	{
		this->m_szBuffer = szBuffer;

	  //if section token found
	  	if( this->m_szBuffer.Left( szSectionKey.GetLength() ) == szSectionKey )
	  	{
		  //set section details for use later
		  	this->m_szSection = szSection;
		  	this->m_lSectionOffset = this->m_f->GetPosition();
		  	return TRUE;
	  	}
	}				
		
	return FALSE;		
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	SeekToEntry()
//
//	Design:
//
//		check open file
//
//		seek to section
//		
//		scan for entry token
//		if entry token found
//			return true
//			
//		return flase
//	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CBigIni::SeekToEntry( CString& szEntry )
{
  //check open file	
	if( m_f == NULL )
		return FALSE;

  //seek to section
	this->m_f->Seek( this->m_lSectionOffset, CFile::begin );

	char szBuffer[1024];
	CString szBufStr = _T("");
	CString szEntryKey = szEntry += "=";

  //scan for entry token
	while( this->m_f->ReadString( szBuffer, sizeof( szBuffer )-1 ) != NULL )
	{
		this->m_szBuffer = szBuffer;

	  //if entry token found
	  	if( this->m_szBuffer.Left( szEntryKey.GetLength() ) == szEntryKey )
	  	{
			int iBufferLength = this->m_szBuffer.GetLength();
			int iEntryKeyLength = szEntryKey.GetLength();
			
			this->m_szBuffer = m_szBuffer.Right( iBufferLength - iEntryKeyLength );
			
		  //loose white space and \n	
			while( this->m_szBuffer.Right( 1 ) == "\n"  ||
				   this->m_szBuffer.Right( 1 ) == " " )	
			{
				int iLength = this->m_szBuffer.GetLength();
				this->m_szBuffer = this->m_szBuffer.Left( iLength -1 );
			}
		  	
		  	return TRUE;
	  	}

	  //check for next section
	  	if( this->m_szBuffer.Left( 1 ) == "[" )
	  		return FALSE;
	}				
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Procedure:	CBigIni::WritePrivateProfileString()
//
//	Design:
//  		note; this routine only appends lines!
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CBigIni::WritePrivateProfileString( CString& szSection, 
										 CString& szEntry, 
										 CString& szString )
{
	CString szLine = _T("");

  //open file
	if( this->m_f == NULL )
	{
		this->m_f = new CStdioFile();
		CFileException e;

		if( !this->m_f->Open( this->m_szFileName, CFile::modeReadWrite, &e ) )
		{
			delete this->m_f;
			this->m_f = NULL;
			return FALSE;
		}
	}
	
	if( this->m_szSection != szSection )
	{
		szLine = "\n";
		szLine += "[";
		szLine += szSection;
		szLine += "]";
		szLine += "\n";

		this->m_szSection = szSection;
		this->m_f->WriteString( szLine );
	}
		
	szLine = szEntry;
	szLine += "=";
	szLine += szString;
	szLine += "\n";

	this->m_szSection = szSection;
	this->m_f->WriteString( szLine );

	return TRUE;
}										
