/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1998 McRae Software International, Inc.
//
//	Warning:  This computer program and source code  is  protected by copyright law and
//	international treaties and is the property of McRae Software International, Inc.
//  Unauthorized reproduction or distribution of this program
//	or source,  may result in severe civil and criminal penalties, and will be prosecuted 
//	to the maximum extent possible under law.
/////////////////////////////////////////////////////////////////////////////
//gwdib.h     Header file for GridWiz built in GridCellObjects
#ifndef __GWDIB_H__
#define __GWDIB_H__ 



#ifdef _MAC
#undef AFX_EXT_API
#undef AFX_EXT_CLASS
#define AFX_EXT_API
#define AFX_EXT_CLASS
#endif

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

#define GW_EXT_CLASS

#ifdef _WIN32
	#ifdef _GWDLLIMP
		#undef GW_EXT_CLASS
		#define GW_EXT_CLASS __declspec(dllimport)
	#else
		#ifdef _GWEXTDLL
			#undef GW_EXT_CLASS
			#define GW_EXT_CLASS AFX_EXT_CLASS
		#endif	
	#endif
#else //_WIN32
	#ifdef _GWEXTDLL
		#undef AFXAPP_DATA
		#define AFXAPP_DATA AFXAPI_DATA
	#endif //_WIN32
#endif

class GW_EXT_CLASS CGWDIB 
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWDIB,"Construction")
    CGWDIB();		//Default Constructor.
    ~CGWDIB();		//Default Destructor.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWDIB,"Operations")
	void DestroyBitmap();												//Destroy bitmap by freeing all data.
    BOOL Create(CDC* pDC, CBitmap* pBitmap);							//Create the bitmap from a MFC bitmap.
    virtual BOOL LoadFromFile(CFile *pFile);							//Create the bitmap from a DIB file.
	virtual void Stretch(CDC *pDC, int x, int y, int cx, int cy);		//Stretch the bitmap to the DC.
	inline DWORD GetNumClrEntries();									//Retrieve the number of color entries in the bitmap.
    inline RGBQUAD* GetClrTabAddress()									//Retrieve the address of the color table stored within the DIB.
		{
			return (RGBQUAD*) m_pBitmapInfo + sizeof(BITMAPINFOHEADER);
		}
    inline int GetHeight()												//Retrieve the height of the bitmap.
        {
			return (int) m_pBitmapInfo->bmiHeader.biHeight;
		}
    inline int GetWidth()												//Retrieve the width of the bitmap.
        {
			return (int) m_pBitmapInfo->bmiHeader.biWidth;
		}
//}}GW_MEMBERS	

public:
//GW_MEMBERS{{(CGWDIB,"Data Members")
    LPBITMAPFILEHEADER m_pBitmapFileHeader;								//Address of the Bitmap file header.
    LPBITMAPINFOHEADER m_pBitmapInfoHeader;								//Address of the Bitmap Info header
    LPBITMAPINFO	   m_pBitmapInfo;									//Address of the Bitmap Info structure.
    LPBYTE 			   m_pBitmapBits;									//Address of the Bitmap bits.
    LPBYTE 			   m_pBitmapBuffer;									//Address of the Bitmap structure.
//}}GW_MEMBERS	

};

inline DWORD CGWDIB::GetNumClrEntries()
{   
	DWORD dwNumColors;
	switch (m_pBitmapInfoHeader->biBitCount) 
    {
    case 1:
        dwNumColors = 2;
        break;
    case 4:
        dwNumColors = 16;
        break;
    case 8:
    case 24:
        dwNumColors = 256;
        break;
    default:
        dwNumColors = 0;
        break;
	}

    if (m_pBitmapInfoHeader->biClrUsed != 0) 
        dwNumColors = m_pBitmapInfoHeader->biClrUsed;
  	return dwNumColors;
}

class GW_EXT_CLASS CGWDIBPal : public CPalette
{
//GW_INTERNAL_CLASS{{()
/*
*/
//}}GW_CLASS
public:
//GW_MEMBERS{{(CGWDIBPal,"Construction")
    CGWDIBPal();		//Default Constructor.
    ~CGWDIBPal();		//Default Destructor.
//}}GW_MEMBERS	

//GW_MEMBERS{{(CGWDIBPal,"Operations")
   BOOL Create(CGWDIB *pGWDIB);			//Creates the palette for a DIB bitmap.
//}}GW_MEMBERS	
};

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS


#endif // __GWDIB_H__
