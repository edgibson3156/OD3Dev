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
///////////////////////////////////////////////////////
//stdgrid.h   -    Precompiled headers for GridWiz
#pragma warning(disable : 4100)

#ifdef _WIN32
#include <afxtempl.h>
#include <afxole.h>
#endif
#if _MFC_VER >= 0x0600
	#include <oledb.h>
	#include <msdaosp.h>
	#include <msdatsrc.h>
#endif

#if _MFC_VER >= 0x0420
#define _GW_ADO15
#endif
//#pragma warning(disable: 4189)
//This is the standard grif stuff, its included in all projects
#include "gridres.h"
#include "gcomacro.h"
#include "gwizmisc.h"
#include "settings.h"
#include "gwdata.h"
#include "grid.h"
#include "gridctrl.h"
#include "gridview.h"
#include "gridrpt.h"
#include "gridpop.h"
#include "gwdib.h"
#include "gwizgco.h"  
#include "cellmap.h"

//Are we using oledb data binding.
#if _MFC_VER >= 0x0600
	#include "gwrowset.h"
#endif




//Are we using the tabbed grid option.
#ifdef USE_TABBED_GRID
	#include "stdtab.h"
#endif

//Are we using the edit GCOS
#ifdef USE_EDIT_GCOS
	#include "editgco.h"
#endif

//Are we using the extended GCOS
#ifdef USE_EXTENDED_GCOS
	#include "extgco.h"
#endif

//Are we using the OLE GCOS
#ifdef USE_OLE_GCOS
	#include "olegco.h"
#endif

//Are we using the Hierarchy grid option
#ifdef USE_TREE_GRID
	#include "stdhier.h"
#endif

//Are we using the drag and drop feature
#ifdef USE_DRAG_DROP
	#include "dragdrop.h"
#endif

//Are we using the ODBC map feature
#ifdef USE_ODBC_MAP
	#include "odbcmap.h"
#endif

//Are we using the DAO map feature
#ifdef USE_DAO_MAP
	#include "daomap.h"
#endif

//Are we using the DAO map feature
#ifdef USE_GRID_REPORT
	#include "stdrpt.h"
#endif

//Are we using the grid-objects Ole Control class 
#ifdef USE_GWOLECONTROL
	#include "gwolecontrol.h"
#endif
#ifdef LIB_BUILD
#ifdef USE_GRID_OBJECTS
	#include "gridobjects.h"
#endif
#endif

//Are we using the tree-objects Ole Control Class
#ifdef USE_GWOLETREECONTROL
	#include "gwolecontrol.h"
	#include "gwoletreecontrol.h"
#endif

#ifdef LIB_BUILD
#ifdef USE_TREE_OBJECTS
	#include "treeobjects.h"
#endif
#endif

#ifndef NO_LIB_PRAGMA
	//Now, figure out which libs to include
	#ifdef _AFXDLL                         //MFC as a DLL?

		#ifdef _GWEXTDLL						//Using GridWiz as an extension DLL

			#ifdef _UNICODE							//Unicode?
				
				#ifdef _DEBUG							//Debug Build?

					// Always include the grid base library.
					#pragma comment(lib, "gwext40du.lib")
					
					//Are we using the tabbed grid option.
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "gwtab40du.lib")
					#endif

					//Are we using the edit GCOS
					#ifdef USE_EDIT_GCOS
						#pragma comment(lib,  "gweg40du.lib")
					#endif

					//Are we using the extended GCOS
					#ifdef USE_EXTENDED_GCOS
						#pragma comment(lib,  "gwxg40du.lib")
					#endif

					//Are we using the OLE GCOS
					#ifdef USE_OLE_GCOS
						#pragma comment(lib,  "gwog40du.lib")
					#endif

					//Are we using the Hierarchy grid option
					#ifdef USE_TREE_GRID
						#ifdef USE_TABBED_GRID
							#pragma comment(lib, "gwht40du.lib")
						#else
							#pragma comment(lib, "gwhr40du.lib")
						#endif
					#endif

					//Are we using the drag and drop feature
					#ifdef USE_DRAG_DROP
						#pragma comment(lib,  "gwdd40du.lib")
					#endif

					//Are we using the ODBC map feature
					#ifdef USE_ODBC_MAP
						#pragma comment(lib,  "gwodb40du.lib")
					#endif

					//Are we using the DAO map feature
					#ifdef USE_DAO_MAP
						#pragma comment(lib,  "gwdao40du.lib")
					#endif

					//Are we using the Reporting map feature
					#ifdef USE_GRID_REPORT
						#pragma comment(lib,  "gwrpt40du.lib")
					#endif


				#else									//Release Build

					// Always include the grid base library.
					#pragma comment(lib, "gwext40u.lib")
					
					//Are we using the tabbed grid option.
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "gwtab40u.lib")
					#endif

					//Are we using the edit GCOS
					#ifdef USE_EDIT_GCOS
						#pragma comment(lib,  "gweg40u.lib")
					#endif

					//Are we using the extended GCOS
					#ifdef USE_EXTENDED_GCOS
						#pragma comment(lib,  "gwxg40u.lib")
					#endif

					//Are we using the OLE GCOS
					#ifdef USE_OLE_GCOS
						#pragma comment(lib,  "gwog40u.lib")
					#endif

					//Are we using the Hierarchy grid option
					#ifdef USE_TREE_GRID
						#ifdef USE_TABBED_GRID
							#pragma comment(lib, "gwht40u.lib")
						#else
							#pragma comment(lib, "gwhr40u.lib")
						#endif
					#endif

					//Are we using the drag and drop feature
					#ifdef USE_DRAG_DROP
						#pragma comment(lib,  "gwdd40u.lib")
					#endif

					//Are we using the ODBC map feature
					#ifdef USE_ODBC_MAP
						#pragma comment(lib,  "gwodb40u.lib")
					#endif

					//Are we using the DAO map feature
					#ifdef USE_DAO_MAP
						#pragma comment(lib,  "gwdao40u.lib")
					#endif

					//Are we using the Reporting map feature
					#ifdef USE_GRID_REPORT
						#pragma comment(lib,  "gwrpt40u.lib")
					#endif

				
				#endif
			#else									//non Unicode
				#ifdef _DEBUG							//Debug Build?

					// Always include the grid base library.
					#pragma comment(lib, "gwext40d.lib")
					
					//Are we using the tabbed grid option.
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "gwtab40d.lib")
					#endif

					//Are we using the edit GCOS
					#ifdef USE_EDIT_GCOS
						#pragma comment(lib,  "gweg40d.lib")
					#endif

					//Are we using the extended GCOS
					#ifdef USE_EXTENDED_GCOS
						#pragma comment(lib,  "gwxg40d.lib")
					#endif

					//Are we using the OLE GCOS
					#ifdef USE_OLE_GCOS
						#pragma comment(lib,  "gwog40d.lib")
					#endif

					//Are we using the Hierarchy grid option
					#ifdef USE_TREE_GRID
						#ifdef USE_TABBED_GRID
							#pragma comment(lib, "gwht40d.lib")
						#else
							#pragma comment(lib, "gwhr40d.lib")
						#endif
					#endif

					//Are we using the drag and drop feature
					#ifdef USE_DRAG_DROP
						#pragma comment(lib,  "gwdd40d.lib")
					#endif

					//Are we using the ODBC map feature
					#ifdef USE_ODBC_MAP
						#pragma comment(lib,  "gwodb40d.lib")
					#endif

					//Are we using the DAO map feature
					#ifdef USE_DAO_MAP
						#pragma comment(lib,  "gwdao40d.lib")
					#endif

					//Are we using the Reporting map feature
					#ifdef USE_GRID_REPORT
						#pragma comment(lib,  "gwrpt40d.lib")
					#endif


				#else									//Release Build

					// Always include the grid base library.
					#pragma comment(lib, "gwext40.lib")
					
					//Are we using the tabbed grid option.
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "gwtab40.lib")
					#endif

					//Are we using the edit GCOS
					#ifdef USE_EDIT_GCOS
						#pragma comment(lib,  "gweg40.lib")
					#endif

					//Are we using the extended GCOS
					#ifdef USE_EXTENDED_GCOS
						#pragma comment(lib,  "gwxg40.lib")
					#endif

					//Are we using the OLE GCOS
					#ifdef USE_OLE_GCOS
						#pragma comment(lib,  "gwog40.lib")
					#endif

					//Are we using the Hierarchy grid option
					#ifdef USE_TREE_GRID
						#ifdef USE_TABBED_GRID
							#pragma comment(lib, "gwht40.lib")
						#else
							#pragma comment(lib, "gwhr40.lib")
						#endif
					#endif

					//Are we using the drag and drop feature
					#ifdef USE_DRAG_DROP
						#pragma comment(lib,  "gwdd40.lib")
					#endif

					//Are we using the ODBC map feature
					#ifdef USE_ODBC_MAP
						#pragma comment(lib,  "gwodb40.lib")
					#endif

					//Are we using the DAO map feature
					#ifdef USE_DAO_MAP
						#pragma comment(lib,  "gwdao40.lib")
					#endif

					//Are we using the Reporting map feature
					#ifdef USE_GRID_REPORT
						#pragma comment(lib,  "gwrpt40.lib")
					#endif

				
				#endif

			#endif									//Unicode

		#else                                   //Not Using GridWiz in a Extension DLL

			#ifdef _UNICODE							//Unicode?
				
				#ifdef _DEBUG							//Debug Build?

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

				#else									//Release Build

					// Always include the grid base library.
					#pragma comment(lib, "agwizu.lib")
					
					//Are we using the tabbed grid option.
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "agwtabu.lib")
					#endif

					//Are we using the edit GCOS
					#ifdef USE_EDIT_GCOS
						#pragma comment(lib,  "aedtgcou.lib")
					#endif

					//Are we using the extended GCOS
					#ifdef USE_EXTENDED_GCOS
						#pragma comment(lib,  "aextgcou.lib")
					#endif

					//Are we using the OLE GCOS
					#ifdef USE_OLE_GCOS
						#pragma comment(lib,  "aolegcou.lib")
					#endif

					//Are we using the Hierarchy grid option
					#ifdef USE_TREE_GRID
						#ifdef USE_TABBED_GRID
							#pragma comment(lib, "agwhtu.lib")
						#else
							#pragma comment(lib, "agwhieru.lib")
						#endif
					#endif

					//Are we using the drag and drop feature
					#ifdef USE_DRAG_DROP
						#pragma comment(lib,  "agwdragu.lib")
					#endif

					//Are we using the ODBC map feature
					#ifdef USE_ODBC_MAP
						#pragma comment(lib,  "agwodbcu.lib")
					#endif

					//Are we using the DAO map feature
					#ifdef USE_DAO_MAP
						#pragma comment(lib,  "agwdaou.lib")
					#endif

					//Are we using the Reporting map feature
					#ifdef USE_GRID_REPORT
						#pragma comment(lib,  "agwrptu.lib")
					#endif

				
					//Are we using the grid-objects Ole Control Class
					#ifdef USE_GRID_OBJECTS
						#pragma comment(lib, "gridobjectsu.lib")
					#endif
					#ifdef USE_GWOLECONTROL
						#pragma comment(lib, "gwolecontrolu.lib")
					#endif

					//Are we using the tree-objects Ole Control Class
					#ifdef USE_TREE_OBJECTS
						#pragma comment(lib, "gridobjectsu.lib")
						#pragma comment(lib, "treeobjectsu.lib")
					#endif
					//Are we using the tree-objects Ole Control Class
					#ifdef USE_CGWOLETREECONTROL
						#pragma comment(lib, "gwoletreecontolu.lib")
					#endif

				#endif
			#else									//non Unicode
				#ifdef _DEBUG							//Debug Build?

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

				#else									//Release Build

					// Always include the grid base library.
					#pragma comment(lib, "agwiz.lib")
					
					//Are we using the tabbed grid option.
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "agwtab.lib")
					#endif

					//Are we using the edit GCOS
					#ifdef USE_EDIT_GCOS
						#pragma comment(lib,  "aedtgco.lib")
					#endif

					//Are we using the extended GCOS
					#ifdef USE_EXTENDED_GCOS
						#pragma comment(lib,  "aextgco.lib")
					#endif

					//Are we using the OLE GCOS
					#ifdef USE_OLE_GCOS
						#pragma comment(lib,  "aolegco.lib")
					#endif

					//Are we using the Hierarchy grid option
					#ifdef USE_TREE_GRID
						#ifdef USE_TABBED_GRID
							#pragma comment(lib, "agwht.lib")
						#else
							#pragma comment(lib, "agwhier.lib")
						#endif
					#endif

					//Are we using the drag and drop feature
					#ifdef USE_DRAG_DROP
						#pragma comment(lib,  "agwdrag.lib")
					#endif

					//Are we using the ODBC map feature
					#ifdef USE_ODBC_MAP
						#pragma comment(lib,  "agwodbc.lib")
					#endif

					//Are we using the DAO map feature
					#ifdef USE_DAO_MAP
						#pragma comment(lib,  "agwdao.lib")
					#endif

					//Are we using the Reporting map feature
					#ifdef USE_GRID_REPORT
						#pragma comment(lib,  "agwrpt.lib")
					#endif

				
				
					//Are we using the grid-objects Ole Control Class
					#ifdef USE_GRID_OBJECTS
						#pragma comment(lib, "gridobjects.lib")
					#endif
					#ifdef USE_GWOLECONTROL
						#pragma comment(lib, "gwolecontrol.lib")
					#endif

					//Are we using the tree-objects Ole Control Class
					#ifdef USE_TREE_OBJECTS
						#pragma comment(lib, "gridobjects.lib")
						#pragma comment(lib, "treeobjects.lib")
					#endif
					//Are we using the tree-objects Ole Control Class
					#ifdef USE_CGWOLETREECONTROL
						#pragma comment(lib, "gwoletreecontol.lib")
					#endif
				
				#endif									//Debug

			#endif									//Unicode
		
		#endif									//_GWEXTDLL

	#else									//MFC is static

		#ifdef _UNICODE							//Unicode?
			
			#ifdef _DEBUG							//Debug Build?

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

			#else									//Release Build

				// Always include the grid base library.
				#pragma comment(lib, "gwizu.lib")
				
				//Are we using the tabbed grid option.
				#ifdef USE_TABBED_GRID
					#pragma comment(lib, "gwtabu.lib")
				#endif

				//Are we using the edit GCOS
				#ifdef USE_EDIT_GCOS
					#pragma comment(lib,  "edtgcou.lib")
				#endif

				//Are we using the extended GCOS
				#ifdef USE_EXTENDED_GCOS
					#pragma comment(lib,  "extgcou.lib")
				#endif

				//Are we using the OLE GCOS
				#ifdef USE_OLE_GCOS
					#pragma comment(lib,  "olegcou.lib")
				#endif

				//Are we using the Hierarchy grid option
				#ifdef USE_TREE_GRID
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "gwhtu.lib")
					#else
						#pragma comment(lib, "gwhieru.lib")
					#endif
				#endif

				//Are we using the drag and drop feature
				#ifdef USE_DRAG_DROP
					#pragma comment(lib,  "gwdragu.lib")
				#endif

				//Are we using the ODBC map feature
				#ifdef USE_ODBC_MAP
					#pragma comment(lib,  "gwodbcu.lib")
				#endif

				//Are we using the DAO map feature
				#ifdef USE_DAO_MAP
					#pragma comment(lib,  "gwdaou.lib")
				#endif

				//Are we using the Reporting map feature
				#ifdef USE_GRID_REPORT
					#pragma comment(lib,  "gwrptu.lib")
				#endif

			#endif

		#else									//non Unicode

			
			#ifdef _DEBUG							//Debug Build?

				// Always include the grid base library.
				#pragma comment(lib, "gwizd.lib")
				
				//Are we using the tabbed grid option.
				#ifdef USE_TABBED_GRID
					#pragma comment(lib, "gwtabd.lib")
				#endif

				//Are we using the edit GCOS
				#ifdef USE_EDIT_GCOS
					#pragma comment(lib,  "edtgcod.lib")
				#endif

				//Are we using the extended GCOS
				#ifdef USE_EXTENDED_GCOS
					#pragma comment(lib,  "extgcod.lib")
				#endif

				//Are we using the OLE GCOS
				#ifdef USE_OLE_GCOS
					#pragma comment(lib,  "olegcod.lib")
				#endif

				//Are we using the Hierarchy grid option
				#ifdef USE_TREE_GRID
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "gwhtd.lib")
					#else
						#pragma comment(lib, "gwhierd.lib")
					#endif
				#endif

				//Are we using the drag and drop feature
				#ifdef USE_DRAG_DROP
					#pragma comment(lib,  "gwdragd.lib")
				#endif

				//Are we using the ODBC map feature
				#ifdef USE_ODBC_MAP
					#pragma comment(lib,  "gwodbcd.lib")
				#endif

				//Are we using the DAO map feature
				#ifdef USE_DAO_MAP
					#pragma comment(lib,  "gwdaod.lib")
				#endif

				//Are we using the Reporting map feature
				#ifdef USE_GRID_REPORT
					#pragma comment(lib,  "gwrptd.lib")
				#endif

			#else									//Release Build

				// Always include the grid base library.
				#pragma comment(lib, "gwiz.lib")
				
				//Are we using the tabbed grid option.
				#ifdef USE_TABBED_GRID
					#pragma comment(lib, "gwtab.lib")
				#endif

				//Are we using the edit GCOS
				#ifdef USE_EDIT_GCOS
					#pragma comment(lib,  "edtgco.lib")
				#endif

				//Are we using the extended GCOS
				#ifdef USE_EXTENDED_GCOS
					#pragma comment(lib,  "extgco.lib")
				#endif

				//Are we using the OLE GCOS
				#ifdef USE_OLE_GCOS
					#pragma comment(lib,  "olegco.lib")
				#endif

				//Are we using the Hierarchy grid option
				#ifdef USE_TREE_GRID
					#ifdef USE_TABBED_GRID
						#pragma comment(lib, "gwht.lib")
					#else
						#pragma comment(lib, "gwhier.lib")
					#endif
				#endif

				//Are we using the drag and drop feature
				#ifdef USE_DRAG_DROP
					#pragma comment(lib,  "gwdrag.lib")
				#endif

				//Are we using the ODBC map feature
				#ifdef USE_ODBC_MAP
					#pragma comment(lib,  "gwodbc.lib")
				#endif

				//Are we using the DAO map feature
				#ifdef USE_DAO_MAP
					#pragma comment(lib,  "gwdao.lib")
				#endif

				//Are we using the Reporting map feature
				#ifdef USE_GRID_REPORT
					#pragma comment(lib,  "gwrpt.lib")
				#endif		

			#endif

		#endif

	#endif
#endif // NO_LIB_PRAGMA