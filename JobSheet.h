// JobSheet.h: interface for the CJobSheet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOBSHEET_H__A9BC7147_CED4_4080_AB84_9FD377CD8F34__INCLUDED_)
#define AFX_JOBSHEET_H__A9BC7147_CED4_4080_AB84_9FD377CD8F34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "JobSheetItem.h"

class CJobSheet : public CObject  
{
public:
	CJobSheet();
	virtual ~CJobSheet();

private:
	CString	m_sJobNum;
	CString	m_sCustRef;
	CString	m_sCustName;
	CString	m_sProductCode;
	CString	m_sProductDes;
	CString	m_sDate;

	int		m_iItemNum;
	float	m_fWeight;

public:
	CJobSheetItem*	newItem(int iLen, int iQty, CString sMark);

	void	setJobNumber(CString sNum){m_sJobNum = sNum;};
	CString getJobNumber(void){return(m_sJobNum);};

	void	setCustRef(CString sRef){m_sCustRef = sRef;};
	CString getCustRef(void){return(m_sCustRef);};

	void	setCustName(CString sName){m_sCustName = sName;};
	CString getCustName(void){return(m_sCustName);};

	void	setProdCode(CString sProd){m_sProductCode = sProd;};
	CString getProdCode(void){return(m_sProductCode);};

	void	setProdDes(CString sDes){m_sProductDes = sDes;};
	CString getProdDes(void){return(m_sProductDes);};

	void	setDate(CString sDate){m_sDate = sDate;};
	CString getDate(void){return(m_sDate);};

	void	setItemNum(int iNum){m_iItemNum = iNum;};
	int		getItemNum(void){return(m_iItemNum);};

	void	setWeight(float fWeight){m_fWeight = fWeight;};
	float	getWeight(void){return(m_fWeight);};


	CTypedPtrList<CObList, CJobSheetItem*>	m_tplItems;	// List of items in the job sheet

};

#endif // !defined(AFX_JOBSHEET_H__A9BC7147_CED4_4080_AB84_9FD377CD8F34__INCLUDED_)
