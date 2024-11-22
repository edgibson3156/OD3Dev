// BeamOps.cpp: implementation of the CBeamOps class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OD3.h"
#include "BeamOps.h"
#include "BeamDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL (CBeamOps, CObject, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBeamOps::CBeamOps()
{
	m_nSeqID		= 0;	//	incremental sequence number (irrespective of whether dim or punch)
	m_sOpType		= "";	//	type of operation (Generic|Dimension|Punch)
	m_sOperation	= "";	//	operation text as specified in OD3 database operation scripts or by user input
	m_bAbsolute		= true;	//	absolute|relative dimension indicator
	m_bPositive		= true;	//	positive|negative dimension indicator
	m_bMultiplied	= true;	//	multiply(true)|divide(false) dimension modification indicator
	m_nMultiplier	= 1;	//	value used a dimension modifier base on value of m_Multiplied
	m_nHit			= 0;
	m_bIsCSunk		= false;
}

CBeamOps::~CBeamOps()
{

}

void CBeamOps::Serialize(CArchive &ar)
{
		int nIsAbsolute;
		int nIsPositive;
		int nIsMultiplied;

	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		nIsAbsolute = (int)m_bAbsolute;
		nIsPositive = (int)m_bPositive;
		nIsMultiplied = (int)m_bMultiplied;

		ar << m_nSeqID;
		ar << m_sOpType;
		ar << m_sOperation;
		ar << nIsAbsolute;
		ar << nIsPositive;
		ar << nIsMultiplied;
		ar << m_nMultiplier;
		ar << m_sComment;
	}
	else
	{
		ar >> m_nSeqID;
		ar >> m_sOpType;
		ar >> m_sOperation;

		ar >> nIsAbsolute;
		m_bAbsolute = (nIsAbsolute != 0);

		ar >> nIsPositive;
		m_bPositive = (nIsPositive != 0);

		ar >> nIsMultiplied;
		m_bMultiplied = (nIsMultiplied != 0);

		ar >> m_nMultiplier;
		ar >> m_sComment;
	}
}

int	CBeamOps::GetPosition()
{
return 0;
}

long CBeamOps::GetPunch()
{
return 0;	
}

//////////////////////////////////////////////////////////////
// UpdateOps()	A functon to update an existing COpList object
//				with data collected from the BeamInput dialog
void CBeamOps::UpdateOps(CBeamOps* pCurrentOp, CBeamDlg* pBeamInputDlg)
{
/*
	pCurrentOp->m_nSeqID			= pBeamInputDlg->m_nItemID;	//	TEMP VALUE - FOR TESTING ONLY
	pCurrentOp->m_sOpType		= pBeamInputDlg->m_editMarkNo;	//	TEMP VALUE - FOR TESTING ONLY
	pCurrentOp->m_sOperation	= pBeamInputDlg->m_editMarkNo;	//	TEMP VALUE - FOR TESTING ONLY
	pCurrentOp->m_bAbsolute		= true;	//	TEMP VALUE - FOR TESTING ONLY
	pCurrentOp->m_bPositive		= true;	//	TEMP VALUE - FOR TESTING ONLY
	pCurrentOp->m_bMultiplied	= true;	//	TEMP VALUE - FOR TESTING ONLY
	pCurrentOp->m_nMultiplier	= 1;	//	TEMP VALUE - FOR TESTING ONLY
*/
}

