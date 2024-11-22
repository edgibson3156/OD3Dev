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
//GridCellMap Macros

//GW_MACROS{{(DECLARE_GRIDCELL_MAP,"Declares the GCOMap function which is called during grid construction. This function is responsible for setting up the initial GCO mappings.")
#define DECLARE_GRIDCELL_MAP(class_name)												\
			virtual void GCOMap();
//}}GW_MACROS

//GW_MACROS{{(BEGIN_GRIDCELL_MAP,"Defines the first part of the GCOMap function which is called during grid construction. This function is responsible for setting up the initial GCO mappings.")
#define BEGIN_GRIDCELL_MAP(class_name) \
			void class_name::GCOMap() \
			{\
				POSITION pos = NULL; \
				CRuntimeClass* pRuntimeClass = NULL;  \
				int x = 0; \
				CRect* pRect;  \
				pRect = NULL;  \
				CString csClassName;	\
				m_nFixedRows = m_nFixedColumns = 0;                                                          
//}}GW_MACROS

//GW_MACROS{{(REGISTER,"Registers a GCO so that it can be referenced by name in subsequent calls to SetCellType, etc.")
#define REGISTER(GCOClass) \
		pos = RegisterGCO(RUNTIME_CLASS(GCOClass)); 
//}}GW_MACROS


//GW_MACROS{{(MAPGRID,"Sets the default cell type for the grid. Any un-mapped cells will default to this cell type. This macro can only be used between BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP.")
#ifdef _UNICODE	
#define MAPGRID(GCOClass) \
		m_runtimeGCODefault  =   RUNTIME_CLASS(GCOClass); \
		pos = RegisterGCO(m_runtimeGCODefault); 		  \
		if (m_pGWDataSource)							  \
		{															\
			CString csClassName;	\
			mbstowcs(csClassName.GetBufferSetLength(strlen(m_runtimeGCODefault->m_lpszClassName)),	\
					 m_runtimeGCODefault->m_lpszClassName,	\
					 strlen(m_runtimeGCODefault->m_lpszClassName));	\
			csClassName.ReleaseBuffer(-1);	\
			CGWGrid::SetDefaultCellType(csClassName);	\
		}
#else	
#define MAPGRID(GCOClass) \
		m_runtimeGCODefault  =   RUNTIME_CLASS(GCOClass); \
		pos = RegisterGCO(m_runtimeGCODefault); 		  \
		if (m_pGWDataSource)							  \
		{															\
			CGWGrid::SetDefaultCellType(m_runtimeGCODefault->m_lpszClassName);	\
		}
#endif	
//}}GW_MACROS
		

//GW_MACROS{{(MAPROW,"Sets the cell type for a set of rows in the grid. This macro can only be used between BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP.")
#ifdef _UNICODE	
#define MAPROW(nBeginRowNdx, nEndRowNdx, GCOClass)						\
			pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginRowNdx; x<=nEndRowNdx; x++)   					\
				m_mapRowToGCO.SetAt(x, pos);							\
			if (m_pGWDataSource)										\
			{															\
				CString csClassName;	\
				mbstowcs(csClassName.GetBufferSetLength(strlen(pRuntimeClass->m_lpszClassName)),	\
						 pRuntimeClass->m_lpszClassName,	\
						 strlen(pRuntimeClass->m_lpszClassName));	\
				csClassName.ReleaseBuffer(-1);	\
				SetRowCellType(nBeginRowNdx,nEndRowNdx,	csClassName);	\
			}
#else	
#define MAPROW(nBeginRowNdx, nEndRowNdx, GCOClass)						\
			pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginRowNdx; x<=nEndRowNdx; x++)   					\
				m_mapRowToGCO.SetAt(x, pos);							\
			if (m_pGWDataSource)										\
			{															\
				csClassName = pRuntimeClass->m_lpszClassName;	\
				SetRowCellType(nBeginRowNdx,nEndRowNdx,	csClassName);	\
			}
#endif	
//}}GW_MACROS
		
//GW_MACROS{{(MAPHROW,"Sets the cell type for a set of rows in the grid and also marks those rows as header rows. Header rows must begin at row 0 and cannot have non-fixed rows interspersed. This macro can only be used between BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP.")
#ifdef _UNICODE	
#define MAPHROW(nBeginRowNdx, nEndRowNdx, GCOClass)										 \
			pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
		    m_nFixedRows += nEndRowNdx - nBeginRowNdx + 1;				\
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginRowNdx; x<=nEndRowNdx; x++)   					\
				m_mapRowToGCO.SetAt(x, pos);							\
			if (m_pGWDataSource)										\
			{															\
				CString csClassName;	\
				mbstowcs(csClassName.GetBufferSetLength(strlen(pRuntimeClass->m_lpszClassName)),	\
						 pRuntimeClass->m_lpszClassName,	\
						 strlen(pRuntimeClass->m_lpszClassName));	\
				csClassName.ReleaseBuffer(-1);	\
				SetRowCellType(nBeginRowNdx,nEndRowNdx,	csClassName);	\
			}
#else	
#define MAPHROW(nBeginRowNdx, nEndRowNdx, GCOClass)										 \
			pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
		    m_nFixedRows += nEndRowNdx - nBeginRowNdx + 1;				\
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginRowNdx; x<=nEndRowNdx; x++)   					\
				m_mapRowToGCO.SetAt(x, pos);							\
			if (m_pGWDataSource)										\
			{															\
				csClassName = pRuntimeClass->m_lpszClassName;	\
				SetRowCellType(nBeginRowNdx,nEndRowNdx,	csClassName);	\
			}
#endif	
//}}GW_MACROS
					                                          				
//GW_MACROS{{(MAPCOL,"Sets the cell type for a set of columns in the grid. This macro can only be used between BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP.")
#ifdef _UNICODE	
#define MAPCOL(nBeginColNdx, nEndColNdx, GCOClass) 						\
		    pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginColNdx; x<=nEndColNdx; x++)   					\
				m_mapColToGCO.SetAt(x, pos);\
			if (m_pGWDataSource)										\
			{															\
				CString csClassName;	\
				mbstowcs(csClassName.GetBufferSetLength(strlen(pRuntimeClass->m_lpszClassName)),	\
						 pRuntimeClass->m_lpszClassName,	\
						 strlen(pRuntimeClass->m_lpszClassName));	\
				csClassName.ReleaseBuffer(-1);	\
				SetColCellType(nBeginColNdx,nEndColNdx,	csClassName);	\
			}
#else	
#define MAPCOL(nBeginColNdx, nEndColNdx, GCOClass) 						\
		    pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginColNdx; x<=nEndColNdx; x++)   					\
				m_mapColToGCO.SetAt(x, pos);\
			if (m_pGWDataSource)										\
			{															\
				csClassName = pRuntimeClass->m_lpszClassName;	\
				SetColCellType(nBeginColNdx,nEndColNdx,	csClassName);	\
			}
#endif	
//}}GW_MACROS

//GW_MACROS{{(MAPHCOL,"Sets the cell type for a set of columns in the grid and also marks those columns as header columns. Header columns must begin at column 0 and cannot have non-fixed columns interspersed. This macro can only be used between BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP.")
#ifdef _UNICODE	
#define MAPHCOL(nBeginColNdx, nEndColNdx, GCOClass) 					\
		    pRuntimeClass  =   RUNTIME_CLASS(GCOClass);         	    \
		    m_nFixedColumns += nEndColNdx - nBeginColNdx + 1;			\
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginColNdx; x<=nEndColNdx; x++)   					\
				m_mapColToGCO.SetAt(x, pos);\
			if (m_pGWDataSource)										\
			{															\
				CString csClassName;	\
				mbstowcs(csClassName.GetBufferSetLength(strlen(pRuntimeClass->m_lpszClassName)),	\
						 pRuntimeClass->m_lpszClassName,	\
						 strlen(pRuntimeClass->m_lpszClassName));	\
				csClassName.ReleaseBuffer(-1);	\
				SetColCellType(nBeginColNdx,nEndColNdx,	csClassName);	\
			}
#else
#define MAPHCOL(nBeginColNdx, nEndColNdx, GCOClass) 					\
		    pRuntimeClass  =   RUNTIME_CLASS(GCOClass);         	    \
		    m_nFixedColumns += nEndColNdx - nBeginColNdx + 1;			\
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginColNdx; x<=nEndColNdx; x++)   					\
				m_mapColToGCO.SetAt(x, pos);\
			if (m_pGWDataSource)										\
			{															\
				csClassName = pRuntimeClass->m_lpszClassName;	\
				SetColCellType(nBeginColNdx,nEndColNdx,	csClassName);	\
			}
#endif
//}}GW_MACROS

#define MAPTCOL(nBeginColNdx, nEndColNdx, GCOClass) 					\
		    pRuntimeClass  =   RUNTIME_CLASS(GCOClass);         	    \
			pos = RegisterGCO(pRuntimeClass);							\
			for (x=nBeginColNdx; x<=nEndColNdx; x++)   					\
				m_mapFixedColToGCO.SetAt(x, pos);
				
//GW_MACROS{{(MAPRANGE,"Sets the cell type for a set of cells in the grid. Please note that mapping cells by range is somewhat less efficient than mapping by row, column or sheet. This macro can only be used between BEGIN_GRIDCELL_MAP and END_GRIDCELL_MAP.")
#ifdef _UNICODE	
#define MAPRANGE(nTopRow, nLeftCol, nBottomRow, nRightCol, GCOClass) 	\
		    pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
			pos = RegisterGCO(pRuntimeClass);							\
			pRect = new CRect(nLeftCol, nTopRow, nRightCol, nBottomRow);    \
			m_arrayRanges.Add(pRect);			                        \
			m_arrayGCOPos.Add(pos);\
			if (m_pGWDataSource)										\
			{															\
				CString csClassName;	\
				mbstowcs(csClassName.GetBufferSetLength(strlen(pRuntimeClass->m_lpszClassName)),	\
						 pRuntimeClass->m_lpszClassName,	\
						 strlen(pRuntimeClass->m_lpszClassName));	\
				csClassName.ReleaseBuffer(-1);	\
				SetCellType(nTopRow, nLeftCol, nBottomRow, nRightCol, csClassName); \
			}
#else	
#define MAPRANGE(nTopRow, nLeftCol, nBottomRow, nRightCol, GCOClass) 	\
		    pRuntimeClass  =   RUNTIME_CLASS(GCOClass);          	    \
			pos = RegisterGCO(pRuntimeClass);							\
			pRect = new CRect(nLeftCol, nTopRow, nRightCol, nBottomRow);    \
			m_arrayRanges.Add(pRect);			                        \
			m_arrayGCOPos.Add(pos);\
			if (m_pGWDataSource)										\
			{															\
				csClassName = pRuntimeClass->m_lpszClassName;	\
				SetCellType(nTopRow, nLeftCol, nBottomRow, nRightCol, csClassName); \
			}
#endif	
//}}GW_MACROS
	
//GW_MACROS{{(END_GRIDCELL_MAP,"Define the last part of the GCOMap function which is called during grid construction. This function is responsible for setting up the initial GCO mappings.")
#define END_GRIDCELL_MAP()   \
			m_nHScrollPos = m_nMinColumn = m_nFixedColumns;  \
			m_nVScrollPos = m_nMinRow = m_nFixedRows;            \
		 }
//}}GW_MACROS



//GW_MACROS{{(IMPLEMENT_GW_CUSTOM_CONTROL,"Define the set of function which allows a GridWiz CGWGridCtrl based class to be used as a windows custom control.")
#ifdef _UNICODE
	#define IMPLEMENT_GW_CUSTOM_CONTROL(class_name) \
		class class_name##Exported : public class_name	\
	{	\
	public:	\
		class_name##Exported() { };	\
		BOOL RegisterControlClass(HINSTANCE hInstance = NULL);	\
	protected:	\
		virtual void PostNcDestroy();	\
		static LRESULT CALLBACK EXPORT WndProcHook(HWND, UINT, WPARAM, LPARAM);	\
		static WNDPROC lpfnSuperGrid;	\
		friend class class_name;	\
		afx_msg int OnNcCreate(LPCREATESTRUCT lpCreateStruct);	\
		DECLARE_MESSAGE_MAP();	\
	};	\
	LRESULT CALLBACK EXPORT	\
	class_name##Exported::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)	\
	{	\
		class_name##Exported* pGrid = new class_name##Exported();	\
		pGrid->Attach(hWnd);	\
		pGrid->m_pfnSuper = class_name##Exported::lpfnSuperGrid;	\
		::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc);	\
		return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam);	\
	}	\
	BEGIN_MESSAGE_MAP(class_name##Exported, class_name)	\
		ON_WM_NCCREATE()	\
	END_MESSAGE_MAP()	\
	int class_name##Exported::OnNcCreate(LPCREATESTRUCT lpCreateStruct)	\
	{	\
		return class_name::OnNcCreate(lpCreateStruct);	\
	}	\
	void class_name##Exported::PostNcDestroy()	\
	{	\
		delete this;	\
	}	\
	WNDPROC class_name##Exported::lpfnSuperGrid = NULL;	\
	BOOL class_name::RegisterControlClass(HINSTANCE hInstance)	\
	{	\
		WNDCLASS wcls;	\
		if (!hInstance)	\
			hInstance = AfxGetInstanceHandle();	\
		CString csClassName(RUNTIME_CLASS(class_name)->m_lpszClassName); \
		if (::GetClassInfo(hInstance, csClassName, &wcls))	\
		{	\
			return (wcls.lpfnWndProc == (WNDPROC)class_name##Exported::WndProcHook);	\
		}	\
		CString csEdit(_T("edit")); \
		VERIFY(::GetClassInfo(NULL, csEdit, &wcls));	\
		wcls.lpfnWndProc = class_name##Exported::WndProcHook;	\
		wcls.hInstance = hInstance;	\
	    mbstowcs((unsigned short *) wcls.lpszClassName,	\
				 RUNTIME_CLASS(class_name)->m_lpszClassName,	\
				 strlen(RUNTIME_CLASS(class_name)->m_lpszClassName));	\
	    wcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);	\
		return (AfxRegisterClass(&wcls) != 0);	\
	}

#else
	#ifdef _WIN32
		
		#define IMPLEMENT_GW_CUSTOM_CONTROL(class_name) \
			class class_name##Exported : public class_name	\
		{	\
		public:	\
			class_name##Exported() { };	\
			BOOL RegisterControlClass(HINSTANCE hInstance = NULL);	\
		protected:	\
			virtual void PostNcDestroy();	\
			static LRESULT CALLBACK EXPORT WndProcHook(HWND, UINT, WPARAM, LPARAM);	\
			static WNDPROC lpfnSuperGrid;	\
			friend class class_name;	\
			afx_msg int OnNcCreate(LPCREATESTRUCT lpCreateStruct);	\
			DECLARE_MESSAGE_MAP();	\
		};	\
		LRESULT CALLBACK EXPORT	\
		class_name##Exported::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)	\
		{	\
			class_name##Exported* pGrid = new class_name##Exported();	\
			pGrid->Attach(hWnd);	\
			pGrid->m_pfnSuper = class_name##Exported::lpfnSuperGrid;	\
			::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc);	\
			return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam);	\
		}	\
		BEGIN_MESSAGE_MAP(class_name##Exported, class_name)	\
			ON_WM_NCCREATE()	\
		END_MESSAGE_MAP()	\
		int class_name##Exported::OnNcCreate(LPCREATESTRUCT lpCreateStruct)	\
		{	\
			return class_name::OnNcCreate(lpCreateStruct);	\
		}	\
		void class_name##Exported::PostNcDestroy()	\
		{	\
			delete this;	\
		}	\
		WNDPROC class_name##Exported::lpfnSuperGrid = NULL;	\
		BOOL class_name::RegisterControlClass(HINSTANCE hInstance)	\
		{	\
			if (!hInstance)	\
				hInstance = AfxGetInstanceHandle();	\
			WNDCLASS wcls;	\
			if (::GetClassInfo(hInstance, RUNTIME_CLASS(class_name)->m_lpszClassName, &wcls))	\
			{	\
				return (wcls.lpfnWndProc == (WNDPROC)class_name##Exported::WndProcHook);	\
			}	\
			VERIFY(::GetClassInfo(NULL, "edit", &wcls));	\
			wcls.lpfnWndProc = class_name##Exported::WndProcHook;	\
			wcls.hInstance = hInstance;	\
			wcls.lpszClassName = RUNTIME_CLASS(class_name)->m_lpszClassName;	\
			wcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);	\
			return (AfxRegisterClass(&wcls) != 0);	\
		}	

    #else
	
		#define IMPLEMENT_GW_CUSTOM_CONTROL(class_name) \
			class class_name##Exported : public class_name	\
		{	\
		public:	\
			class_name##Exported(HWND hWnd) { VERIFY(Attach(hWnd));} \
			BOOL RegisterControlClass(HINSTANCE hInstance = NULL);	\
		protected:	\
			virtual void PostNcDestroy();	\
			static LRESULT CALLBACK EXPORT WndProcHook(HWND, UINT, WPARAM, LPARAM);	\
			virtual WNDPROC* GetSuperWndProcAddr(); \
			static WNDPROC lpfnSuperGrid;	\
			friend class class_name;	\
			afx_msg int OnNcCreate(LPCREATESTRUCT lpCreateStruct);	\
			DECLARE_MESSAGE_MAP();	\
		};	\
		LRESULT CALLBACK EXPORT	\
		class_name##Exported::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)	\
		{	\
			class_name##Exported* pGrid = new class_name##Exported(hWnd);	\
			::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc);	\
			return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam);	\
		}	\
		BEGIN_MESSAGE_MAP(class_name##Exported, class_name)	\
			ON_WM_NCCREATE()	\
		END_MESSAGE_MAP()	\
		int class_name##Exported::OnNcCreate(LPCREATESTRUCT lpCreateStruct)	\
		{	\
			return class_name::OnNcCreate(lpCreateStruct);	\
		}	\
		void class_name##Exported::PostNcDestroy()	\
		{	\
			delete this;	\
		}	\
		WNDPROC class_name##Exported::lpfnSuperGrid = NULL;	\
		WNDPROC* class_name##Exported::GetSuperWndProcAddr() \
		{ \
			return &lpfnSuperGrid; \
		} \
		BOOL class_name::RegisterControlClass(HINSTANCE hInstance)	\
		{	\
			WNDCLASS wcls;	\
			if (!hInstance)	\
				hInstance = AfxGetInstanceHandle();	\
			if (::GetClassInfo(hInstance, RUNTIME_CLASS(class_name)->m_lpszClassName, &wcls))	\
			{	\
				return (wcls.lpfnWndProc == (WNDPROC)class_name##Exported::WndProcHook);	\
			}	\
			VERIFY(::GetClassInfo(NULL, "edit", &wcls));	\
			wcls.lpfnWndProc = class_name##Exported::WndProcHook;	\
			wcls.hInstance = hInstance;	\
			wcls.lpszClassName = RUNTIME_CLASS(class_name)->m_lpszClassName;	\
			wcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);	\
			return (RegisterClass(&wcls) != 0);	\
		}	
	
	#endif
#endif
//}}GW_MACROS

//GW_MACROS{{(DECLARE_GW_CUSTOM_CONTROL,"Declare the function which allows a GridWiz CGWGridCtrl based class to be used as a windows custom control.")
#define	DECLARE_GW_CUSTOM_CONTROL() \
	static BOOL RegisterControlClass(HINSTANCE hInstance);
//}}GW_MACROS

//GW_MACROS{{(REGISTER_GW_CUSTOM_CONTROL,"Calls the function which registers the window class for you CGWGridCtrl derived grid class. This must be called at least once before the dialog containing the grid class is invoked.")
#define	REGISTER_GW_CUSTOM_CONTROL(class_name, hInstance) \
	class_name::RegisterControlClass(hInstance);
//}}GW_MACROS


#ifdef _WIN32
#define	ON_GRIDWIZ_CONTROL_NOTIFICATIONS() \
	ON_CONTROL_RANGE(CBN_EDITUPDATE, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnEditUpdateFloatingDDL) \
	ON_CONTROL_RANGE(CBN_SELENDOK, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnSelEndOKFloatingDDL) \
	ON_CONTROL_RANGE(CBN_DROPDOWN, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnDropDownFloatingDDL) \
	ON_CONTROL_RANGE(CBN_CLOSEUP, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnCloseUpFloatingDDL) \
	ON_CONTROL_RANGE(EN_CHANGE, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnGridEditChange) \
	ON_CONTROL_RANGE(BN_CLICKED, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnFloatingButtonClick) \
	ON_CONTROL_RANGE(BN_DOUBLECLICKED, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnFloatingButtonDblClick) \
	ON_CONTROL_RANGE(LBN_SELCHANGE, IDC_GW_FLOATING_CTRL_FIRST, IDC_GW_FLOATING_CTRL_LAST, OnSelChangeFloatingListBox) \
	ON_BN_CLICKED(IDC_GW_FLOATING_ACCEPT, OnAcceptButtonClick) \
	ON_BN_DOUBLECLICKED(IDC_GW_FLOATING_ACCEPT, OnAcceptButtonDblClick) \
	ON_BN_CLICKED(IDC_GW_FLOATING_DELETE, OnRejectButtonClick) \
	ON_BN_DOUBLECLICKED(IDC_GW_FLOATING_DELETE, OnRejectButtonDblClick) \
	ON_LBN_SELCHANGE(IDC_GW_FLOATING_LISTBOX, OnSelChangeFloatingListBox)
#else
#define	ON_GRIDWIZ_CONTROL_NOTIFICATIONS() \
	ON_CBN_EDITUPDATE(IDC_GW_FLOATING_COMBO_BOX, OnEditUpdateFloatingDDL) \
	ON_CBN_SELENDOK(IDC_GW_FLOATING_COMBO_BOX, OnSelEndOKFloatingDDL) \
	ON_CBN_DROPDOWN(IDC_GW_FLOATING_COMBO_BOX, OnDropDownFloatingDDL) \
	ON_CBN_CLOSEUP(IDC_GW_FLOATING_COMBO_BOX, OnCloseUpFloatingDDL) \
	ON_EN_CHANGE(IDC_GW_FLOATING_EDIT_CTRL, OnGridEditChange) \
	ON_BN_CLICKED(IDC_GW_FLOATING_BUTTON, OnFloatingButtonClick) \
	ON_BN_DOUBLECLICKED(IDC_GW_FLOATING_BUTTON, OnFloatingButtonDblClick) \
	ON_BN_CLICKED(IDC_GW_FLOATING_ACCEPT, OnAcceptButtonClick) \
	ON_BN_DOUBLECLICKED(IDC_GW_FLOATING_ACCEPT, OnAcceptButtonDblClick) \
	ON_BN_CLICKED(IDC_GW_FLOATING_DELETE, OnRejectButtonClick) \
	ON_BN_DOUBLECLICKED(IDC_GW_FLOATING_DELETE, OnRejectButtonDblClick) \
	ON_LBN_SELCHANGE(IDC_GW_FLOATING_LISTBOX, OnSelChangeFloatingListBox)
#endif


#ifdef _WIN32
#define	DECLARE_GRIDWIZ_CONTROL_NOTIFICATIONS() \
	afx_msg void OnAcceptButtonClick(); \
	afx_msg void OnAcceptButtonDblClick(); \
	afx_msg void OnRejectButtonClick(); \
	afx_msg void OnRejectButtonDblClick(); \
	afx_msg void OnFloatingButtonClick(UINT nID) {OnFloatingButtonClick();} \
	afx_msg void OnFloatingButtonDblClick(UINT nID) {OnFloatingButtonDblClick();} \
	afx_msg void OnSelChangeFloatingListBox(UINT nID){OnSelChangeFloatingListBox();} \
	afx_msg void OnEditUpdateFloatingDDL(UINT nID){OnEditUpdateFloatingDDL();} \
	afx_msg void OnSelEndOKFloatingDDL(UINT nID){OnSelEndOKFloatingDDL();} \
	afx_msg void OnDropDownFloatingDDL(UINT nID){OnDropDownFloatingDDL();} \
	afx_msg void OnCloseUpFloatingDDL(UINT nID){OnCloseUpFloatingDDL();} \
	afx_msg  void OnGridEditChange(UINT nID){OnGridEditChange();}\
	afx_msg  void OnFloatingButtonClick(); \
	afx_msg  void OnFloatingButtonDblClick(); \
	afx_msg  void OnSelChangeFloatingListBox(); \
	afx_msg  void OnSelEndOKFloatingDDL(); \
	afx_msg  void OnEditUpdateFloatingDDL(); \
	afx_msg  void OnDropDownFloatingDDL(); \
	afx_msg  void OnCloseUpFloatingDDL(); \
	afx_msg  void OnGridEditChange();
#else
#define	DECLARE_GRIDWIZ_CONTROL_NOTIFICATIONS() \
	afx_msg void OnAcceptButtonClick(); \
	afx_msg void OnAcceptButtonDblClick(); \
	afx_msg void OnRejectButtonClick(); \
	afx_msg void OnRejectButtonDblClick(); \
	afx_msg void OnFloatingButtonClick(); \
	afx_msg void OnFloatingButtonDblClick(); \
	afx_msg void OnSelChangeFloatingListBox(); \
	afx_msg void OnEditUpdateFloatingDDL(); \
	afx_msg void OnSelEndOKFloatingDDL(); \
	afx_msg void OnDropDownFloatingDDL(); \
	afx_msg void OnCloseUpFloatingDDL(); \
	afx_msg void OnGridEditChange();
#endif
