// SysTemplate.h: interface for the CSysTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMPLATE_H__1B4B6D41_2B37_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_SYSTEMPLATE_H__1B4B6D41_2B37_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSysTemplate : public CObject  
{
protected:
	DECLARE_SERIAL (CSysTemplate)
	CSysTemplate();

public:
	void	LoadTemplate();
	virtual ~CSysTemplate();
	virtual void Serialize(CArchive &ar);

public:
	CString	m_sDataSource;
	CString	m_sDBaseVersion;
	CString m_sProjectInputPath;
	CString m_sAutoFileInputPath;
	int		m_nProcessAll;
	int		m_nProcessAuto;
	CString m_sReportAutomatic;
	CString m_sReportNonAuto;

	// Member variables for list control
	CTypedPtrList<CObList, CAssociation*> m_tplAssociationList;	// a list of product v production line associations
	CTypedPtrList<CObList, COutputList*> m_tplOutputList;
};

#endif // !defined(AFX_SYSTEMPLATE_H__1B4B6D41_2B37_11D3_88B5_006008E6ADB9__INCLUDED_)
