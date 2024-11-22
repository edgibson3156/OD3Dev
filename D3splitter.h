// D3splitter.h: interface for the CD3splitter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3SPLITTER_H__3D70956A_5DC2_48C0_82E0_CB26E594A407__INCLUDED_)
#define AFX_D3SPLITTER_H__3D70956A_5DC2_48C0_82E0_CB26E594A407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImportDet3.h"

class CD3splitter : public CObject  
{
public:
	bool dialogRequired(void);
	CD3splitter();
	virtual ~CD3splitter();

	
	bool FileOK(void){return(m_fileOK);}
	bool splitD3File(CImportDet3 *import);

	CTypedPtrList<CObList, CImportD3Beam*> m_tplIrvineBeam;		// a list of all the Irvine beams in the file
	CTypedPtrList<CObList, CImportD3Beam*> m_tplWarleyBeam;		// a list of all the Warley beams in the file

	CTypedPtrList<CObList, CImportD3Acc*> m_tplIrvineAcc;		// a list of all the Irvine accessories in the file
	CTypedPtrList<CObList, CImportD3Acc*> m_tplWarleyAcc;		// a list of all the Warley accessories in the file
	CTypedPtrList<CObList, CImportD3Acc*> m_tplOtherAcc;		// a list of all the other (Daventry) accessories in the file

protected:
	void moveImportedData(int site, CImportD3Beam *beam, CImportDet3 *import);
	void moveImportedData(int site, CImportD3Acc *acc, CImportDet3 *import);
	int	 testName(CString name);
	void storeCodes(CStdioFile *file, int site);
	void readD3Contents(CStdioFile *file);
	bool openConfigFile(void);

	bool m_fileOK;				// File loaded into class
	
	CStringArray m_sPtrIrvine;	// Product codes for Irvine site
	CStringArray m_sPtrWarley;	// Product codes for Warley site
};

#endif // !defined(AFX_D3SPLITTER_H__3D70956A_5DC2_48C0_82E0_CB26E594A407__INCLUDED_)
