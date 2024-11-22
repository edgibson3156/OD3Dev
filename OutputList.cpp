// OutputList.cpp: implementation of the COutputList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "OutputList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL (COutputList, CObject, 0)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COutputList::COutputList()
{
	m_sPLine = _T("");
	m_sPath = _T("");
}

COutputList::~COutputList()
{

}

//////////////////////////////////////////////////////////////////////
// SET OUTPUT
void COutputList::SetOutput(LPCTSTR sPLine,LPCTSTR sPath)
{
	m_sPLine = sPLine;	// set the production line variable
	m_sPath = sPath;	// set the product variable
}

//////////////////////////////////////////////////////////////////////
// GET OUTPUT
void COutputList::GetOutput(CString& sPLine,CString& sPath)
{
	sPLine = m_sPLine;
	sPath = m_sPath;
}

//////////////////////////////////////////////////////////////////////
// SERIALIZE
void COutputList::Serialize(CArchive &ar)
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