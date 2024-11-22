// ProductMods.h: interface for the CProductMods class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCTMODS_H__D34D0111_E8F9_4BCC_B15F_A66C9E9BCB7E__INCLUDED_)
#define AFX_PRODUCTMODS_H__D34D0111_E8F9_4BCC_B15F_A66C9E9BCB7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProductMods  
{
public:
	CString m_lineDes[12];
	bool	m_line1[12];
	bool	m_line2[12];
	bool	m_line3[12];

	bool	fileOK;
	bool	warn;

	CProductMods();
	virtual ~CProductMods();

protected:
	void loadStdFile(void);
};

#endif // !defined(AFX_PRODUCTMODS_H__D34D0111_E8F9_4BCC_B15F_A66C9E9BCB7E__INCLUDED_)
