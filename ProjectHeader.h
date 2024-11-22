// ProjectHeader.h: interface for the CProjectHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTHEADER_H__CF0E8FBE_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_)
#define AFX_PROJECTHEADER_H__CF0E8FBE_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProjectHeader : public CObject  
{
	DECLARE_SERIAL(CProjectHeader)
public:
	CProjectHeader();
	virtual ~CProjectHeader();
	virtual void Serialize(CArchive &ar);

	int		m_nProjectType;	// 1=Build single order, 2=Build multiple orders, 3=Integrated processing. 
	CString m_sProjectName;	//	will be used to create *.od3 filename 
	CTime	m_nCreateDate;	// i.e. date file created (or modified ??).
	CString	m_sUserName;
	CString	m_sAppVersion;
	CString	m_sCustomerName;
	CString	m_sCustomerRef;
	CString	m_sDueDate;		// i.e. planned delivery date.
	CTime	m_nDueDate;		// i.e. planned delivery date.
	CString m_sJobDestination;
	CString m_sComments;		// Det3 field sometimes used by customers for free text
	// NB: Not included in serialization at 11/11/99 (release 21)
};

#endif // !defined(AFX_PROJECTHEADER_H__CF0E8FBE_0DC6_11D3_88B4_006008E6ADB9__INCLUDED_)
