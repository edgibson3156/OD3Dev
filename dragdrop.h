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
//dragdrop.h     Header file for Gridwiz OLE drag and drop classes
#ifndef __DRAGDROP_H__
#define __DRAGDROP_H__ 

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
	#ifdef _GWEXTDLL
		#undef GW_EXT_CLASS
		#define GW_EXT_CLASS AFX_EXT_CLASS
	#endif	
#else //_WIN32
//	#ifdef _GWEXTDLL                           //Drag drop is no longer part of the extension DLL
//		#undef AFXAPP_DATA
//		#define AFXAPP_DATA AFXAPI_DATA
//	#endif //_WIN32
#endif

class CGWGrid;

class GW_EXT_CLASS CGWOleDropSource : public COleDropSource
{ 
//GW_INTERNAL_CLASS{{(CGWOleDropSource)
/*
*/
//}}GW_CLASS	


public:
//Construction
//GW_MEMBERS{{(CGWOleDropSource,"Construction")
    CGWOleDropSource();					//Default contructor.
    virtual ~CGWOleDropSource();		//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWOleDropSource,"Data Members")
    CGWGrid* m_pGrid;					//Keeps track of the grid to which a COleDropTarget will be assigned.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWOleDropSource,"Overriden Virtual Functions")
	virtual SCODE GiveFeedback(DROPEFFECT dropEffect);
//}}GW_MEMBERS

};



class GW_EXT_CLASS CGWOleActive : public CGWOleSwitch
{ 
//GW_INTERNAL_CLASS{{(CGWOleActive)
/*
*/
//}}GW_CLASS	
public:
//Construction
//GW_MEMBERS{{(CGWOleActive,"Construction")
    CGWOleActive();					//Default contructor.
    virtual ~CGWOleActive();		//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWOleActive,"Data Members")
    CGWGrid* m_pGrid;					//Keeps track of the grid to which a COleDropTarget will be assigned.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWOleActive,"Operations")
	virtual void DestroyOleObjects();				//Cleans up the COleDropTarget.
    static void EnableDragAndDrop(CGWGrid* pGrid);	//Creates and enables the COleDropTarget
	virtual BOOL DoDragDrop(CPoint point);			//Invokes the DoDragDrop of the COleDropTarget.
//}}GW_MEMBERS

};


#ifdef __AFXOLE_H__
class GW_EXT_CLASS CGWDropTarget : public COleDropTarget
{
//GW_INTERNAL_CLASS{{(CGWDropTarget)
/*
*/
//}}GW_CLASS	
public:
//Construction
//GW_MEMBERS{{(CGWDropTarget,"Construction")
    CGWDropTarget();				//Default contructor.
	virtual ~CGWDropTarget();		//Destructor.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWDropTarget,"Data Members")
	CGWGrid*  m_pGrid; 				//Pointer to the grid object which owns this COleDropTarget object.
	CRect 	m_rectTrackerRect;		//The rectangle used to display drag and drop target 
	CBrush  m_RubberBandBrush;		//CBrusg object used to represent the new location of the data.
	CString m_csClipBuffer;			//The text which is retrieved when OnDragEnter is called.
	int 	m_nNumDragRows;			//Holds the number of rows being dragged.
	int     m_nNumDragCols;			//Holds the number of columns being dragged.
	BOOL    m_bRubberBandVisible;	//Specifies whether the rubber band rect is current displayed.
	BOOL    m_bOrigGrid;			//Tells us whether this is the originating grid.
	int		m_ScrollCount;			//Count of scroll messages. We skip the first few so that scrolling does not ocurr immediately.
//}}GW_MEMBERS

protected:
	//Determine the size and location of the recttracker rectangle for a drag and drop operation
//GW_MEMBERS{{(CGWDropTarget,"Operations")
	virtual CRect GetDropTrackerRect(COleDataObject* pDataObject, CPoint point);		//Determines how large to draw the rubber band rectangle
	virtual void DrawRubberBand(CRect rectTrackerRect);									//Uses a pattern brush to draw a rectangle around the potential location of the data.
//}}GW_MEMBERS

//GW_MEMBERS{{(CGWDropTarget,"Overrideables")
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);	//Called by the framework when the mouse is dragged over the target window.		
	virtual void OnDragLeave(CWnd* pWnd);																		//Called by the framework when the mouse leaves the target window.		
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);		//Called by the framework when the mouse moves over the target window.		
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);			//Called by the framework when the user drops onto the target window.		
#ifdef _WIN32	
	virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);								//Called by the framework when the mouse is dragged over the scrolling area of the target window.		
#else
	virtual BOOL OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);										//Called by the framework when the mouse is dragged over the scrolling area of the target window.		
#endif
//}}GW_MEMBERS

};
#endif   //__AFXOLE_H__

#ifndef _WIN32
	#ifdef _GWEXTDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA NEAR
	#endif
#endif
#undef GW_EXT_CLASS


#endif  //__GWIZMISC_H__
