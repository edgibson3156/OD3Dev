/////////////////////////////////////////////////////////////////////////////
//  GRIDWIZ 
//  Copyright (c) 1994-1999 McRae Software International, Inc.
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

#include "gwocxcell.h"

#define REGISTER_OLE_GCOS() \
		CGWGrid::RegisterGCO(RUNTIME_CLASS(CGWOCXCell));	
