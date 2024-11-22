// JobSheetItem.h: interface for the CJobSheetItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOBSHEETITEM_H__F159DBA4_AC07_49CB_98B5_054CCBD7A8EE__INCLUDED_)
#define AFX_JOBSHEETITEM_H__F159DBA4_AC07_49CB_98B5_054CCBD7A8EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CJobSheetItem : public CObject  
{
public:
	CJobSheetItem();
	virtual ~CJobSheetItem();

private:
	CString	m_sMark;
	CString	m_sRemarks;
	int		m_iQty;
	int		m_iLength;
	int		m_iCuttingLength;

public:

	void	setMark(CString sMark){m_sMark = sMark;};
	CString getMark(void){return(m_sMark);};

	void	setRemark(CString sText){m_sRemarks = sText;};
	CString getRemark(void){return(m_sRemarks);};

	void	setQty(int iQty){m_iQty = iQty;};
	int		getQty(void){return(m_iQty);};

	void	setLength(int iLength){m_iLength = iLength;};
	int		getLength(void){return(m_iLength);};

	void	setCuttingLength(int iLength){m_iCuttingLength = iLength;};
	int		getCuttingLength(void){return(m_iCuttingLength);};

};

#endif // !defined(AFX_JOBSHEETITEM_H__F159DBA4_AC07_49CB_98B5_054CCBD7A8EE__INCLUDED_)
