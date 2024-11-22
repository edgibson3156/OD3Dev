// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers
void CListCtrlEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	//for this notification, the structure is actually a
	// NMLVCUSTOMDRAW that tells you what's going on with the custom
	// draw action. So, we'll need to cast the generic pNMHDR pointer.
	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;

//	int iRow,iCol;// = lplvcd->nmcd.dwItemSpec;

	switch(lplvcd->nmcd.dwDrawStage)
	{
		// First stage (for the whole control
		case  CDDS_PREPAINT: 
			{		
				*pResult = CDRF_NOTIFYITEMDRAW;
			}
			break;

		// Stage three (called for each subitem of the focused item
		case CDDS_ITEMPREPAINT | CDDS_SUBITEM: 
			{
				*pResult = CDRF_NOTIFYSUBITEMDRAW | CDRF_NOTIFYPOSTPAINT;
			}
			break;

		// Stage four (called for each subitem of the focused item
		case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM: 
			{
				*pResult = CDRF_SKIPDEFAULT;	
			}
			break;
		
		default:
			if( lplvcd->nmcd.uItemState & CDIS_SELECTED )
			{
				// White text
				lplvcd->clrText=RGB(255,255,255);
				// Light blue background
				lplvcd->clrTextBk = RGB(0, 0, 190);
				*pResult = CDRF_NEWFONT;
			}
			else			
				*pResult = CDRF_DODEFAULT;

			lplvcd->nmcd.uItemState = CDIS_DEFAULT;
			break;
		}

	return;
}


void CListCtrlEx::RepaintSelectedItems()
{
	CRect rcBounds, rcLabel;

	// Invalidate focused item so it can repaint 
	int nItem = GetNextItem(-1, LVNI_FOCUSED);

	if(nItem != -1)
	{
		GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
		GetItemRect(nItem, rcLabel, LVIR_LABEL);
		rcBounds.left = rcLabel.left;

		InvalidateRect(rcBounds, FALSE);
	}

	// Invalidate selected items depending on LVS_SHOWSELALWAYS
	if(!(GetStyle() & LVS_SHOWSELALWAYS))
	{
		for(nItem = GetNextItem(-1, LVNI_SELECTED);
			nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))
		{
			GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
			GetItemRect(nItem, rcLabel, LVIR_LABEL);
			rcBounds.left = rcLabel.left;

			InvalidateRect(rcBounds, FALSE);
		}
	}

	UpdateWindow();
}


void CListCtrlEx::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here

	// check if we are losing focus to label edit box
	if(pNewWnd != NULL && pNewWnd->GetParent() == this)
		return;

	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
		RepaintSelectedItems();

}

void CListCtrlEx::OnSetFocus(CWnd* pOldWnd) 
{
	CListCtrl::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	// check if we are getting focus from label edit box
	if(pOldWnd!=NULL && pOldWnd->GetParent()==this)
		return;

	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		RepaintSelectedItems();

}
