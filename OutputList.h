// OutputList.h: interface for the COutputList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTLIST_H__85AF8F41_2AEC_11D3_A15C_0060082A2F7E__INCLUDED_)
#define AFX_OUTPUTLIST_H__85AF8F41_2AEC_11D3_A15C_0060082A2F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COutputList : public CObject  
{
DECLARE_SERIAL (COutputList)

public:
	COutputList();
	virtual ~COutputList();

	virtual void Serialize(CArchive &ar);
	void	SetOutput(LPCTSTR,LPCTSTR);
	void	GetOutput(CString&,CString&);

	CString m_sPLine;
	CString m_sPath;
};

#endif // !defined(AFX_OUTPUTLIST_H__85AF8F41_2AEC_11D3_A15C_0060082A2F7E__INCLUDED_)
