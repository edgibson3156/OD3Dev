// Association.cpp: implementation of the CAssociation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "Association.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CAssociation,CObject,0)

CAssociation::CAssociation()
{
	m_sRollSet = _T("");
	m_sLine = _T("");
}

CAssociation::~CAssociation()
{

}

//////////////////////////////////////////////////////////////
// SetAssociation() An access function to set product and 
//					production line data into an association object
//
void CAssociation::SetAssociation(LPCTSTR sRollSet, LPCTSTR sProductionLine)
{
	m_sRollSet	= (CString)sRollSet;				// ... set the product variable...
	m_sLine		= (CString)sProductionLine;		// ... set the production line variable ...
}

//////////////////////////////////////////////////////////////
// GetAssociation() An access function to get product and 
//					production line data from an association object
//
void CAssociation::GetAssociation(CString& sRollSet, CString& sProductionLine)
{
	sRollSet		= m_sRollSet;
	sProductionLine = m_sLine;
}

///////////////////////////////////////////////////////////////////
void CAssociation::Serialize(CArchive &ar)
{

	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_sRollSet;
		ar << m_sLine;
	}
	else
	{
		ar >> m_sRollSet;
		ar >> m_sLine;
	}
}
