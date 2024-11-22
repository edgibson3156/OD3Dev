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
				#pragma comment(lib, "agwizd.lib")
				
				//Are we using the tabbed grid option.
				#ifdef USE_TABBED_GRID
					#pragma comment(lib, "agwtabd.lib")
				#endif

				//Are we using the edit GCOS
				#ifdef USE_EDIT_GCOS
					#pragma comment(lib,  "aedtgcod.lib")
				#endif

				//Are we using the extended GCOS
				#ifdef USE_EXTENDED_GCOS
					#pragma comment(lib,  "aextgcod.lib")
				#endif

				//Are we using the OLE GCOS
				#ifdef USE_OLE_GCOS
					#pragma comment(lib,  "aolegcod.lib")
				#endif

				//Are we using the Hierarchy grid option
				#ifdef USE_TREE_GRID
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "agwhtd.lib")
					#else
						#pragma comment(lib, "agwhierd.lib")
					#endif
				#endif

				//Are we using the drag and drop feature
				#ifdef USE_DRAG_DROP
					#pragma comment(lib,  "agwdragd.lib")
				#endif

				//Are we using the ODBC map feature
				#ifdef USE_ODBC_MAP
					#pragma comment(lib,  "agwodbcd.lib")
				#endif

				//Are we using the DAO map feature
				#ifdef USE_DAO_MAP
					#pragma comment(lib,  "agwdaod.lib")
				#endif

				//Are we using the Reporting map feature
				#ifdef USE_GRID_REPORT
					#pragma comment(lib,  "agwrptd.lib")
				#endif
			
			
				//Are we using the grid-objects Ole Control Class
				#ifdef USE_GRID_OBJECTS
					#pragma comment(lib, "gridobjectsd.lib")
				#endif
				#ifdef USE_GWOLECONTROL
					#pragma comment(lib, "gwolecontrold.lib")
				#endif

				//Are we using the tree-objects Ole Control Class
				#ifdef USE_TREE_OBJECTS
					#pragma comment(lib, "gridobjectsd.lib")
					#pragma comment(lib, "treeobjectsd.lib")
				#endif
				#ifdef USE_CGWOLETREECONTROL
					#pragma comment(lib, "gwoletreecontold.lib")
				#endif

