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
#endif

#include "gwizgco.h"  


#define REGISTER_STANDARD_GCOS() \
		RegisterGCO(RUNTIME_CLASS(CGWGridCellObject));	\
		RegisterGCO(RUNTIME_CLASS(CGWHeaderCell));	