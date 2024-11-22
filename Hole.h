// Hole.h: interface for the CHole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOLE_H__45226043_31EC_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_HOLE_H__45226043_31EC_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHole : public CObject  
{
private:
	int		m_nPositionX;
	int		m_nPositionY;	// not yet required -  for future development
	long	m_nBinaryPunch;
	CString m_sPunchGroup;

public:
	CHole();
	virtual ~CHole();

	void SetPosX(int nPosX){m_nPositionX = nPosX;};
	int GetPosX(){return m_nPositionX;};

	void SetPosY(int nPosY){m_nPositionY = nPosY;};
	int GetPosY(){return m_nPositionY;};

	void SetPunch(long nPunch){m_nBinaryPunch = nPunch;};
	long GetPunch(){return m_nBinaryPunch;};

	void SetPunchGroup(LPCTSTR sPunch){m_sPunchGroup = sPunch;};
	CString GetPunchGroup(){return m_sPunchGroup;};

};

#endif // !defined(AFX_HOLE_H__45226043_31EC_11D3_88B5_006008E6ADB9__INCLUDED_)
