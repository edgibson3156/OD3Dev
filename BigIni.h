// BigIni.h: interface for the CBigIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIGINI_H__C32195C5_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_BIGINI_H__C32195C5_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBigIni : public CObject  
{
private:
	CStdioFile*	m_f;
	CString		m_szBuffer;
	CString		m_szSection;
	CString		m_szFileName;
	long		m_lSectionOffset;
	bool		m_bAttempted;
		
public:
	CBigIni( LPCTSTR lpszFileName );
	CBigIni( LPCTSTR lpszFileName, int flag);
	virtual ~CBigIni();

	//    char huge* GetNextString( void );
    char* GetNextString( void );

	bool WritePrivateProfileString( CString& lpszSection, 
									CString& lpszEntry, 
									CString& lpszString );
		
	int GetPrivateProfileString( CString& szSection, 
								 CString& szEntry, 
								 CString& szDefault, 
								 CString& szReturnBuffer );
		
	int GetPrivateProfileInt( CString& lpszSection, 
							  CString& lpszEntry , 
							  int iDefault );

private:
	bool SeekToSection(CString& szSection);
	bool SeekToEntry(CString& szEntry);

};

#endif // !defined(AFX_BIGINI_H__C32195C5_2BA6_11D3_88B5_006008E6ADB9__INCLUDED_)
