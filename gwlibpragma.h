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
//Now, figure out which libs to include
#ifdef _AFXDLL                         //MFC as a DLL?
	#ifdef _GWEXTDLL						//Using GridWiz as an extension DLL
		#ifdef _UNICODE							//Unicode?
			#ifdef _DEBUG							//Debug Build?
				#include "gwlibDUDA.h"			
			#else									//Release Build
				#include "gwlibRUDA.h"
			#endif
		#else									//non Unicode
			#ifdef _DEBUG							//Debug Build?
				#include "gwlibDNDA.h"
			#else									//Release Build
				#include "gwlibRNDA.h"			
			#endif
		#endif									//Unicode
	#else                                   //Not Using GridWiz in a Extension DLL
		#ifdef _UNICODE							//Unicode?
			#ifdef _DEBUG							//Debug Build?
				#include "gwlibDUSA.h"
			#else									//Release Build
				#include "gwlibDUSA.h"
			#endif
		#else									//non Unicode
			#ifdef _DEBUG							//Debug Build?
				#include "gwlibDNSA.h"
			#else									//Release Build
				#include "gwlibRNSA.h"
			#endif									//Debug
		#endif									//Unicode
	#endif									//_GWEXTDLL
#else									//MFC is static
	#ifdef _UNICODE							//Unicode?
		#ifdef _DEBUG							//Debug Build?
			#include "gwlibDUSS.h"
		#else									//Release Build
			#include "gwlibRUSS.h"
		#endif
	#else									//non Unicode
		#ifdef _DEBUG							//Debug Build?
			#include "gwlibDNSS.h"
		#else									//Release Build
			#include "gwlibRNSS.h"
		#endif
	#endif
#endif
