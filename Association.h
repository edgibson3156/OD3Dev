// Association.h: interface for the CAssociation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSOCIATION_H__353F5B41_1CD6_11D3_A15C_0060082A2F7E__INCLUDED_)
#define AFX_ASSOCIATION_H__353F5B41_1CD6_11D3_A15C_0060082A2F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAssociation : public CObject  
{
DECLARE_SERIAL (CAssociation)

private:
	CString m_sRollSet;
	CString m_sLine;

public:
	CAssociation();
	void SetAssociation(LPCTSTR,LPCTSTR);
	void GetAssociation(CString&,CString&);
	CString GetMill(void){return m_sLine;}
	CString GetRollSet(void){return m_sRollSet;}

	void SetMill(CString line){m_sLine=line;}
	void SetRollSet(CString mill){m_sRollSet=mill;}

	virtual ~CAssociation();
	virtual void Serialize(CArchive &ar);

};

#endif // !defined(AFX_ASSOCIATION_H__353F5B41_1CD6_11D3_A15C_0060082A2F7E__INCLUDED_)
