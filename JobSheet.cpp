
// JobSheet.cpp: implementation of the CJobSheet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "od3.h"
#include "JobSheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJobSheet::CJobSheet()
{
	m_fWeight = 0.0f;
	m_iItemNum = 0;
}

CJobSheet::~CJobSheet()
{
	POSITION pos = m_tplItems.GetHeadPosition();

	while(pos)
		delete m_tplItems.GetNext(pos);

	m_tplItems.RemoveAll();
}

CJobSheetItem* CJobSheet::newItem(int iLen, int iQty, CString sMark)
{
	// Create new object
	CJobSheetItem *pItem= new CJobSheetItem;
	int	iCutLength = 0;

	// Calculate the cutting length

	// Set data
	pItem->setLength(iLen);
	pItem->setCuttingLength(iCutLength);
	pItem->setQty(iQty);
	pItem->setMark(sMark);

	// Add to list pointer
	m_tplItems.AddTail(pItem);


	return(pItem);
}
