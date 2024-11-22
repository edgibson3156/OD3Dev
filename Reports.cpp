	// Reports.cpp: implementation of the CReports class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "Reports.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL (CReports, CObject, 0)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReports::CReports()
{
	m_sPLine = _T("");
	m_sPath = _T("");
}

CReports::~CReports()
{

}

//////////////////////////////////////////////////////////////////////
// SET OUTPUT
void CReports::SetOutput(LPCTSTR sPLine,LPCTSTR sPath)
{
	m_sPLine = sPLine;	// set the production line variable
	m_sPath = sPath;	// set the product variable
}

//////////////////////////////////////////////////////////////////////
// GET OUTPUT
void CReports::GetOutput(CString& sPLine,CString& sPath)
{
	sPLine = m_sPLine;
	sPath = m_sPath;
}

//////////////////////////////////////////////////////////////////////
// SERIALIZE
void CReports::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_sPLine;
		ar << m_sPath;
	}
	else
	{
		ar >> m_sPLine;
		ar >> m_sPath;	
	}
}