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
	
			// Always include the grid base library.
			#pragma comment(lib, "gwizdu.lib")
			
			//Are we using the tabbed grid option.
			#ifdef USE_TABBED_GRID
				#pragma comment(lib, "gwtabdu.lib")
			#endif

			//Are we using the edit GCOS
			#ifdef USE_EDIT_GCOS
				#pragma comment(lib,  "edtgcodu.lib")
			#endif

			//Are we using the extended GCOS
			#ifdef USE_EXTENDED_GCOS
				#pragma comment(lib,  "extgcodu.lib")
			#endif

			//Are we using the OLE GCOS
			#ifdef USE_OLE_GCOS
				#pragma comment(lib,  "olegcodu.lib")
			#endif

			//Are we using the Hierarchy grid option
			#ifdef USE_TREE_GRID
				#ifdef USE_TABBED_GRID
					#pragma comment(lib, "gwhtu.lib")
				#else
					#pragma comment(lib, "gwhierdu.lib")
				#endif
			#endif

			//Are we using the drag and drop feature
			#ifdef USE_DRAG_DROP
				#pragma comment(lib,  "gwdragdu.lib")
			#endif

			//Are we using the ODBC map feature
			#ifdef USE_ODBC_MAP
				#pragma comment(lib,  "gwodbcdu.lib")
			#endif

			//Are we using the DAO map feature
			#ifdef USE_DAO_MAP
				#pragma comment(lib,  "gwdaodu.lib")
			#endif

			//Are we using the Reporting map feature
			#ifdef USE_GRID_REPORT
				#pragma comment(lib,  "gwrptdu.lib")
			#endif

