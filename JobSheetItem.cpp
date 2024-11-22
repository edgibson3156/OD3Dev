// JobSheetItem.cpp: implementation of the CJobSheetItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "od3.h"
#include "JobSheetItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJobSheetItem::CJobSheetItem()
{
	m_iCuttingLength = 0;
	m_iLength = 0;
	m_iQty = 0;
}

CJobSheetItem::~CJobSheetItem()
{

}
