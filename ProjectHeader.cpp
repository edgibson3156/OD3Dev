// ProjectHeader.cpp: implementation of the CProjectHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "ProjectHeader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CProjectHeader,CObject,0);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProjectHeader::CProjectHeader()
{
	int		m_nProjectType		= 1;	// default to 1=Build single order. 
	CString m_sProjectName		= _T(""); 
	CTime	m_nCreateDate		= GetCurrentTime();

//	VHF TODO: Add a function to get user name - ? log-on dialog at startup ?
	CString	m_sUserName			= _T("");

//	TODO: Add a function to get application version - system call to version info resource.
	CString	m_sAppVersion;

	CString	m_sCustomerName		= _T("");
	CString	m_sCustomerRef		= _T("");
	CString m_sDueDate			= _T("");
//	CTime	m_nDueDate			= GetCurrentTime();		// i.e. planned delivery date.
	CString m_sJobDestination	= _T("");
}

CProjectHeader::~CProjectHeader()
{

}

void CProjectHeader::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_nProjectType;
		ar << m_sProjectName; 
		ar << m_nCreateDate;
		ar << m_sUserName;
		ar << m_sAppVersion;
		ar << m_sCustomerName;
		ar << m_sCustomerRef;
		ar << m_sComments;
		ar << m_sDueDate;
		ar << m_sJobDestination;
	}
	else
	{
		ar >> m_nProjectType;
		ar >> m_sProjectName; 
		ar >> m_nCreateDate;
		ar >> m_sUserName;
		ar >> m_sAppVersion;
		ar >> m_sCustomerName;
		ar >> m_sCustomerRef;
		ar >> m_sComments;
		ar >> m_sDueDate;
		ar >> m_sJobDestination;
	}
}

