// BeamOps.h: interface for the CBeamOps class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEAMOPS_H__E54C5C64_27BF_11D3_A15C_0060082A2F7E__INCLUDED_)
#define AFX_BEAMOPS_H__E54C5C64_27BF_11D3_A15C_0060082A2F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "BeamDlg.h"
class CBeamDlg;

class CBeamOps : public CObject  
{
	DECLARE_SERIAL(CBeamOps)

private:
	long		m_nScriptID;	//  database reference for SPC script for specific section/line setup
	long		m_nSeqID;		//	incremental sequence number (irrespective of whether dim or punch)
	CString		m_sOpType;		//	type of operation (Generic|Dimension|Punch)
	CString		m_sOperation;	//	operation text as specified in OD3 database operation scripts or by user input
	CString		m_sComment;		//	comment attached to an additional hole in 'd3' beam
	bool		m_bAbsolute;	//	absolute|relative dimension indicator
	bool		m_bPositive;	//	positive|negative dimension indicator
	bool		m_bMultiplied;	//	multiply(true)|divide(false) dimension modification indicator
	int			m_nMultiplier;	//	value used a dimension modifier base on value of m_Multiplied
	int			m_nHit;			//	Hit No. = row location of op' in Beam Dialog Grid (volatile)
//	int			m_nCol;			//  column location of op' in Beam Dialog Grid (volatile)
	bool		m_bIsCSunk;		//	contersunk hole indicator

public:
	CBeamOps();
	void	UpdateOps(CBeamOps*, CBeamDlg*);
	virtual ~CBeamOps();
	virtual void Serialize(CArchive &ar);
	int		GetPosition();
	long	GetPunch();

	void	SetScriptID(long nScriptID){m_nScriptID = nScriptID;};
	long	GetScriptID(){return m_nScriptID;};

	void	SetOpSeqID(int nSeqID){m_nSeqID = nSeqID;};
	long	GetOpSeqID(){return m_nSeqID;};

	void	SetOpType(LPCTSTR sOpType){m_sOpType = sOpType;};
	CString	GetOpType(){return m_sOpType;};

	void	SetComment(LPCTSTR sComment){m_sComment = sComment;};
	CString	GetComment(){return m_sComment;};

	void	SetOperation(LPCTSTR sOperation){m_sOperation = sOperation;};
	CString	GetOperation(){return m_sOperation;};

	void	SetAbsolute(bool bAbsolute){m_bAbsolute = bAbsolute;};
	bool	GetAbsolute(){return m_bAbsolute;};

	void	SetPositive(bool bPositive){m_bPositive = bPositive;};
	bool	GetPositive(){return m_bPositive;};

	void	SetMultiplied(bool bMultiplied){m_bMultiplied = bMultiplied;};
	bool	GetMultiplied(){return m_bMultiplied;}
	;
	void	SetMultiplier(int nMultiplier){m_nMultiplier = nMultiplier;};
	int		GetMultiplier(){return m_nMultiplier;};

	void	SetXtraHoleHit(int nRowNdx){m_nHit = nRowNdx;};
	int		GetXtraHoleHit(){return m_nHit;};

	void	SetCSunk(bool bIsCsk){m_bIsCSunk = bIsCsk;};
	bool	GetCSunk(){return m_bIsCSunk;};
};


#endif // !defined(AFX_BEAMOPS_H__E54C5C64_27BF_11D3_A15C_0060082A2F7E__INCLUDED_)
