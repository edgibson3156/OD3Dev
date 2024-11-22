// CeeSection.h: interface for the CCeeSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CEESECTION_H__41321210_4075_429E_871D_6B95E5348902__INCLUDED_)
#define AFX_CEESECTION_H__41321210_4075_429E_871D_6B95E5348902__INCLUDED_

#include "OD3Doc.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PUNCHFAULT 100
#define COMMENTFAULT 101
#define CEEPUNCHCOUNT 14

struct HOLES
{
	int		iiD;
	
	CString	punch;
	CString	comment;
	CString mark;
	CString holeText;
};

struct SORTEDHOLES
{
	int		count;
	
	CString			D3Text;
	CString			punch;
	CStringArray	comment;
	CStringArray	mark;
};

class CCeeSection  
{
public:
	CCeeSection(COD3Doc *document);

	bool performTest(CItem *pItem);
	bool ceeTest(CItem *pItem);
	
	virtual ~CCeeSection();

protected:
	CString getValidComment(int index);
	void	cleanMemory(void);
	int		isDuplicated(int iID, CString mark, int flag);
	void	addDataToList(int iID, CString mark, int flag, CString sError);
	bool	testCommentsByPunch(void);
	void	sortCommentByPunch(CString punchCode, CString comment, CString mark, bool *quit, int lineNum, CString D3Text);

	COD3Doc		*m_pDoc;
	CTypedPtrList<CPtrList, HOLES*> m_punchCodes;
	SORTEDHOLES	sHoles[CEEPUNCHCOUNT];
	CItem		*m_pCitem;
};

#endif // !defined(AFX_CEESECTION_H__41321210_4075_429E_871D_6B95E5348902__INCLUDED_)
