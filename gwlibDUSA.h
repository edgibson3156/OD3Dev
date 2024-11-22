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
				#pragma comment(lib, "agwizdu.lib")
				
				//Are we using the tabbed grid option.
				#ifdef USE_TABBED_GRID
					#pragma comment(lib, "agwtabdu.lib")
				#endif

				//Are we using the edit GCOS
				#ifdef USE_EDIT_GCOS
					#pragma comment(lib,  "aedtgcodu.lib")
				#endif

				//Are we using the extended GCOS
				#ifdef USE_EXTENDED_GCOS
					#pragma comment(lib,  "aextgcodu.lib")
				#endif

				//Are we using the OLE GCOS
				#ifdef USE_OLE_GCOS
					#pragma comment(lib,  "aolegcodu.lib")
				#endif

				//Are we using the Hierarchy grid option
				#ifdef USE_TREE_GRID
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "agwhtdu.lib")
					#else
						#pragma comment(lib, "agwhierdu.lib")
					#endif
				#endif

				//Are we using the drag and drop feature
				#ifdef USE_DRAG_DROP
					#pragma comment(lib,  "agwdragdu.lib")
				#endif

				//Are we using the ODBC map feature
				#ifdef USE_ODBC_MAP
					#pragma comment(lib,  "agwodbcdu.lib")
				#endif

				//Are we using the DAO map feature
				#ifdef USE_DAO_MAP
					#pragma comment(lib,  "agwdaodu.lib")
				#endif

				//Are we using the Reporting map feature
				#ifdef USE_GRID_REPORT
					#pragma comment(lib,  "agwrptdu.lib")
				#endif

				//Are we using the grid-objects Ole Control Class
				#ifdef USE_GRID_OBJECTS
					#pragma comment(lib, "gridobjectsdu.lib")
				#endif
				#ifdef USE_GWOLECONTROL
					#pragma comment(lib, "gwolecontroldu.lib")
				#endif

				//Are we using the tree-objects Ole Control Class
				#ifdef USE_TREE_OBJECTS
					#pragma comment(lib, "gridobjectsdu.lib")
					#pragma comment(lib, "treeobjectsdu.lib")
				#endif
				//Are we using the tree-objects Ole Control Class
				#ifdef USE_CGWOLETREECONTROL
					#pragma comment(lib, "gwoletreecontoldu.lib")
				#endif

