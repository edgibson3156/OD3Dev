// Reports.h: interface for the CReports class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTS_H__A568C125_3902_11D3_A15E_0060082A2F7E__INCLUDED_)
#define AFX_REPORTS_H__A568C125_3902_11D3_A15E_0060082A2F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReports : public CObject  
{
	DECLARE_SERIAL (CReports)
public:
	CReports();
	virtual ~CReports();

	virtual void Serialize(CArchive &ar);
	void	SetOutput(LPCTSTR,LPCTSTR);
	void	GetOutput(CString&,CString&);

	CString m_sPLine;
	CString m_sPath;

};

#endif // !defined(AFX_REPORTS_H__A568C125_3902_11D3_A15E_0060082A2F7E__INCLUDED_)
