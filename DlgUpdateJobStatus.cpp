// DlgUpdateJobStatus.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "DlgUpdateJobStatus.h"
#include "DaoCoilGetByOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUpdateJobStatus dialog


CDlgUpdateJobStatus::CDlgUpdateJobStatus(CWnd* pParent /*=NULL*/, COD3Doc *pDoc)
	: CDialog(CDlgUpdateJobStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUpdateJobStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pDoc = pDoc;
}


void CDlgUpdateJobStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUpdateJobStatus)
	DDX_Control(pDX, IDC_COIL_ORDERNUM, m_orderNumLab);
	DDX_Control(pDX, IDC_COIL_JOBNUM, m_jobNum);
	DDX_Control(pDX, IDC_COIL_JOBLIST, m_jobList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUpdateJobStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgUpdateJobStatus)
	ON_BN_CLICKED(IDC_COIL_JOBSERACH, OnCoilJobserach)
	ON_NOTIFY(LVN_KEYDOWN, IDC_COIL_JOBLIST, OnKeydownCoilJoblist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUpdateJobStatus message handlers

BOOL CDlgUpdateJobStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();

	DWORD	dwNewStyle;
	CRect	rect;
	int		iCheck=25;

	dwNewStyle = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT;

	// Get the size of the list control
	m_jobList.GetClientRect(&rect);
	// Set list control style
	m_jobList.SetExtendedStyle(dwNewStyle);

	// Insert columns
	m_jobList.InsertColumn(0,"",LVCFMT_LEFT, iCheck, -1);
	m_jobList.InsertColumn(1,"Section",LVCFMT_LEFT, (rect.Width()-iCheck)-(rect.Width()/3),-1);
	m_jobList.InsertColumn(3,"Tonnage",LVCFMT_LEFT, rect.Width()-(rect.Width()-rect.Width()/3),-1);
	m_jobList.InsertColumn(4,"ID",LVCFMT_LEFT, 0,-1);

	m_orderNumLab.SetWindowText("No order selected");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgUpdateJobStatus::OnCoilJobserach() 
{
	CDaoDatabase	db;
	CString			sText, sOrderNum, sPath = AfxGetApp()->GetProfileString(_T("Paths"), _T("CoilDB"), "");	
	LVITEM			item;

	// Get the job number
	m_jobNum.GetWindowText(sOrderNum);

	if(sPath.GetLength() == 0)
		sPath = m_pDoc->setCoilDBPath();
	
	if(sOrderNum.GetLength() > 0)
	{
		try
		{
			// Clear list
			m_jobList.DeleteAllItems();

			// Open the coil planner database
			db.Open(sPath, false, false, _T(""));

			CDaoCoilGetByOrder	orders(&db);

			// Set search criteria
			orders.m_SearchOrder = sOrderNum;			

			// Open recordset
			orders.Open();

			if(orders.GetRecordCount() > 0)
				m_orderNumLab.SetWindowText(sOrderNum);
			else
				m_orderNumLab.SetWindowText("No order selected");

			item.mask = LVIF_TEXT;
		
			while(!orders.IsEOF())
			{
				// Dont insert completed items
				if(orders.m_Complete != 1)
				{									
					// Insert new item (complete field)
					item.iItem = m_jobList.InsertItem(0, "");
					
					// Section name
					item.iSubItem = 1;
					item.pszText = orders.m_Section.GetBuffer(orders.m_Section.GetLength());
					// Update item
					m_jobList.SetItem(&item);

					// Tonnage
					item.iSubItem = 2;
					sText.Format("%.3f", orders.m_Tonnage);
					item.pszText = sText.GetBuffer(sText.GetLength());
					// Update item
					m_jobList.SetItem(&item);

					// ID
					item.iSubItem = 3;
					item.pszText = orders.m_ID.GetBuffer(orders.m_ID.GetLength());
					// Update item
					m_jobList.SetItem(&item);
				}

				// Goto next record
				orders.MoveNext();
			}

			// Close recordset
			orders.Close();

			// Close connection
			db.Close();
		}
		catch(CDaoException *e)
		{
			// Show error
			e->ReportError(MB_ICONINFORMATION);
			// Remove exception
			e->Delete();
		}
	}
}

void CDlgUpdateJobStatus::OnOK() 
{
	int				i;
	CString			sID, sSQL, sPath = AfxGetApp()->GetProfileString(_T("Paths"), _T("CoilDB"), "");
	CDaoDatabase	db;

	if(sPath.GetLength() == 0)
		sPath = m_pDoc->setCoilDBPath();

	try
	{
		// Open the coil planner database
		db.Open(sPath, false, false, _T(""));
		
		for(i=0; i<m_jobList.GetItemCount(); i++)
		{		
			if(m_jobList.GetCheck(i))
			{
				// Item checked for update
				sID = m_jobList.GetItemText(i, 3);

				// Set SQL string
				sSQL.Format("UPDATE TBL_Job_Details SET TBL_Job_Details.Complete=Yes WHERE TBL_Job_Details.ID=%s",sID);

				// Send command
				db.Execute(sSQL, dbFailOnError);
			}
		}

		// Close database
		db.Close();
		
		CDialog::OnOK();
	}
	catch(CDaoException *e)
	{
		// Show error
		e->ReportError(MB_ICONINFORMATION);
		// Remove exception
		e->Delete();

		if(db.IsOpen())
			db.Close();
	}

	
}

BOOL CDlgUpdateJobStatus::PreTranslateMessage(MSG* pMsg) 
{

	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			if(GetFocus()->m_hWnd == m_jobNum.GetSafeHwnd())			
				OnCoilJobserach();
			
			return(FALSE);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgUpdateJobStatus::OnKeydownCoilJoblist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	int			i;

	if(pLVKeyDow->flags & VK_CONTROL)
	{
		if(pLVKeyDow->wVKey == 'a' || pLVKeyDow->wVKey == 'A')
		{
			// Select all
			for(i=0; i<m_jobList.GetItemCount(); i++)			
				m_jobList.SetCheck(i, true);
		}
	}
	*pResult = 0;
}
