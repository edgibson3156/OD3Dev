// SysConfig.h: interface for the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSCONFIG_H__CF0E8FBF_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_)
#define AFX_SYSCONFIG_H__CF0E8FBF_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_

#include "Association.h"
#include "OutputList.h"
#include "Reports.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COD3Doc;

class CSysConfig : public CObject  
{
protected:
	DECLARE_SERIAL (CSysConfig)
	CSysConfig();

public:
	bool	AddAssociation(CString&,CString&);
	bool	DeleteAssociation(CString& sProduct,CString& sProductionLine);
	bool	AddOutputAss(CString&,CString&);
	bool	DeleteOutput(CString& sProductionLine, CString& sPath);
	bool	AddReportAss(CString&,CString&);
	bool	DeleteReport(CString& sProductionLine, CString& sPath);
	void	AutoDbConnect();
 	void	OnDbConnect();
	void	OnDbDisconnect();
	void	OnOpenSysconfig();
	virtual void Serialize(CArchive &ar);
	virtual ~CSysConfig();

public:
	CString	m_sDataSource;
	CString	m_sDBaseVersion;
	CString m_sProjectInputPath;
	CString m_sAutoFileInputPath;
	int		m_nProcessAll;
	int		m_nProcessAuto;
	CString m_sReportAutomatic;
	CString m_sReportNonAuto;

	COD3Doc*		m_pDoc;
	CDaoDatabase*	m_pDB;
	bool			m_ODDB_Open;

	// Member variables for list control
	CTypedPtrList<CObList, CAssociation*>	m_tplAssociationList;	// a list of product v production line associations
	CTypedPtrList<CObList, COutputList*>	m_tplOutputList;	// a list of path specifications for the storage of output files
	CTypedPtrList<CObList, CReports*>		m_tplReportList;	// a list of path specifications for the storage of report files
};

#endif // !defined(AFX_SYSCONFIG_H__CF0E8FBF_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_)
