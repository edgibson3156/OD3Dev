# Microsoft Developer Studio Project File - Name="OD3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OD3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OD3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OD3.mak" CFG="OD3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OD3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OD3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OD3 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /incremental:yes /machine:I386

!ELSEIF  "$(CFG)" == "OD3 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "OD3 - Win32 Release"
# Name "OD3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccOps.cpp
# End Source File
# Begin Source File

SOURCE=.\Association.cpp
# End Source File
# Begin Source File

SOURCE=.\AssociationPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BeamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BeamOps.cpp
# End Source File
# Begin Source File

SOURCE=.\BigIni.cpp
# End Source File
# Begin Source File

SOURCE=.\CeeSectFail.cpp
# End Source File
# Begin Source File

SOURCE=.\CeeSection.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\D3splitter.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoAccOffset.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoCoilGetByOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoCoilJob.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoCoilJobDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoCoilLiveDuplicateSections.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoCoilLiveSingleSections.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoCoilSectionSum.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoCustomerSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoDimValue.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoEavesBySlope.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoGetIgnore.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoGroupSelection.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoImportedHoles.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoProductCode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAccessories.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgListAcc.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewProject.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProjectOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpdateJobStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWernik.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWhatsNew.cpp
# End Source File
# Begin Source File

SOURCE=.\Element.cpp
# End Source File
# Begin Source File

SOURCE=.\excel9.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderBrowse.cpp
# End Source File
# Begin Source File

SOURCE=.\Hole.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportAswFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportD3Acc.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportD3Beam.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDet3.cpp
# End Source File
# Begin Source File

SOURCE=.\InputPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\JobSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\JobSheetItem.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\Line1.cpp
# End Source File
# Begin Source File

SOURCE=.\Line2.cpp
# End Source File
# Begin Source File

SOURCE=.\Line3.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ListViewEx.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ManualInputPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc.cpp
# End Source File
# Begin Source File

SOURCE=.\OD3.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\OD3.hpj

!IF  "$(CFG)" == "OD3 - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__OD3_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=OD3
InputPath=.\hlp\OD3.hpj
InputName=OD3

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "OD3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__OD3_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=OD3
InputPath=.\hlp\OD3.hpj
InputName=OD3

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OD3.odl
# End Source File
# Begin Source File

SOURCE=.\OD3.rc
# End Source File
# Begin Source File

SOURCE=.\OD3Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\od3gridctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\OD3View.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputList.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PartCodes.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessingPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ProductData.cpp
# End Source File
# Begin Source File

SOURCE=.\ProductionLine.cpp
# End Source File
# Begin Source File

SOURCE=.\ProductMods.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileList.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\PunchValue.cpp
# End Source File
# Begin Source File

SOURCE=.\Reports.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Scripts.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectByGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectByProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectBySection.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectGroupSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectNameSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectProductByName.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectSectionSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SpcScript.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashThread.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\SysTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\ValidationMask.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccOps.h
# End Source File
# Begin Source File

SOURCE=.\Association.h
# End Source File
# Begin Source File

SOURCE=.\AssociationPage.h
# End Source File
# Begin Source File

SOURCE=.\BeamDlg.h
# End Source File
# Begin Source File

SOURCE=.\BeamOps.h
# End Source File
# Begin Source File

SOURCE=.\BigIni.h
# End Source File
# Begin Source File

SOURCE=.\CeeSectFail.h
# End Source File
# Begin Source File

SOURCE=.\CeeSection.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\D3splitter.h
# End Source File
# Begin Source File

SOURCE=.\DaoAccOffset.h
# End Source File
# Begin Source File

SOURCE=.\DaoCoilGetByOrder.h
# End Source File
# Begin Source File

SOURCE=.\DaoCoilJob.h
# End Source File
# Begin Source File

SOURCE=.\DaoCoilJobDetails.h
# End Source File
# Begin Source File

SOURCE=.\DaoCoilLiveDuplicateSections.h
# End Source File
# Begin Source File

SOURCE=.\DaoCoilLiveSingleSections.h
# End Source File
# Begin Source File

SOURCE=.\DaoCoilSectionSum.h
# End Source File
# Begin Source File

SOURCE=.\DaoCustomerSet.h
# End Source File
# Begin Source File

SOURCE=.\DaoDimValue.h
# End Source File
# Begin Source File

SOURCE=.\DaoEavesBySlope.h
# End Source File
# Begin Source File

SOURCE=.\DaoGetIgnore.h
# End Source File
# Begin Source File

SOURCE=.\DaoGroupSelection.h
# End Source File
# Begin Source File

SOURCE=.\DaoImportedHoles.h
# End Source File
# Begin Source File

SOURCE=.\DaoProductCode.h
# End Source File
# Begin Source File

SOURCE=.\DlgAccessories.h
# End Source File
# Begin Source File

SOURCE=.\DlgItemList.h
# End Source File
# Begin Source File

SOURCE=.\DlgListAcc.h
# End Source File
# Begin Source File

SOURCE=.\DlgMessage.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewProject.h
# End Source File
# Begin Source File

SOURCE=.\DlgProjectOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgSplitter.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpdateJobStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgWernik.h
# End Source File
# Begin Source File

SOURCE=.\DlgWhatsNew.h
# End Source File
# Begin Source File

SOURCE=.\Element.h
# End Source File
# Begin Source File

SOURCE=.\excel9.h
# End Source File
# Begin Source File

SOURCE=.\FolderBrowse.h
# End Source File
# Begin Source File

SOURCE=.\Hole.h
# End Source File
# Begin Source File

SOURCE=.\ImportAswFile.h
# End Source File
# Begin Source File

SOURCE=.\ImportD3Acc.h
# End Source File
# Begin Source File

SOURCE=.\ImportD3Beam.h
# End Source File
# Begin Source File

SOURCE=.\ImportDet3.h
# End Source File
# Begin Source File

SOURCE=.\InputPage.h
# End Source File
# Begin Source File

SOURCE=.\Item.h
# End Source File
# Begin Source File

SOURCE=.\JobSheet.h
# End Source File
# Begin Source File

SOURCE=.\JobSheetItem.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\Line1.h
# End Source File
# Begin Source File

SOURCE=.\Line2.h
# End Source File
# Begin Source File

SOURCE=.\Line3.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\ListViewEx.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ManualInputPage.h
# End Source File
# Begin Source File

SOURCE=.\Misc.h
# End Source File
# Begin Source File

SOURCE=.\OD3.h
# End Source File
# Begin Source File

SOURCE=.\OD3Doc.h
# End Source File
# Begin Source File

SOURCE=.\od3gridctrl.h
# End Source File
# Begin Source File

SOURCE=.\OD3View.h
# End Source File
# Begin Source File

SOURCE=.\OutputList.h
# End Source File
# Begin Source File

SOURCE=.\OutputPage.h
# End Source File
# Begin Source File

SOURCE=.\PartCodes.h
# End Source File
# Begin Source File

SOURCE=.\ProcessingPage.h
# End Source File
# Begin Source File

SOURCE=.\ProductData.h
# End Source File
# Begin Source File

SOURCE=.\ProductionLine.h
# End Source File
# Begin Source File

SOURCE=.\ProductMods.h
# End Source File
# Begin Source File

SOURCE=.\ProfileList.h
# End Source File
# Begin Source File

SOURCE=.\ProjectHeader.h
# End Source File
# Begin Source File

SOURCE=.\PunchValue.h
# End Source File
# Begin Source File

SOURCE=.\Reports.h
# End Source File
# Begin Source File

SOURCE=.\ReportsPage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "OD3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=OD3
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "OD3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=OD3
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Scripts.h
# End Source File
# Begin Source File

SOURCE=.\SelectByGroup.h
# End Source File
# Begin Source File

SOURCE=.\SelectByProfile.h
# End Source File
# Begin Source File

SOURCE=.\SelectBySection.h
# End Source File
# Begin Source File

SOURCE=.\SelectGroupSet.h
# End Source File
# Begin Source File

SOURCE=.\SelectNameSet.h
# End Source File
# Begin Source File

SOURCE=.\SelectProductByName.h
# End Source File
# Begin Source File

SOURCE=.\SelectSectionSet.h
# End Source File
# Begin Source File

SOURCE=.\SpcScript.h
# End Source File
# Begin Source File

SOURCE=.\SplashDlg.h
# End Source File
# Begin Source File

SOURCE=.\SplashThread.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysConfig.h
# End Source File
# Begin Source File

SOURCE=.\SysTemplate.h
# End Source File
# Begin Source File

SOURCE=.\ValidationMask.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AccNoSel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AccSelec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\beam.bmp
# End Source File
# Begin Source File

SOURCE=.\res\beam_sel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BlueA.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmtreebi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmtreedo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmtreefi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\child.bmp
# End Source File
# Begin Source File

SOURCE=.\res\file_clo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\link_two.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainTool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OD3.ico
# End Source File
# Begin Source File

SOURCE=.\res\OD3.rc2
# End Source File
# Begin Source File

SOURCE=.\res\OD3Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\print_se.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Question.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\OD3.cnt

!IF  "$(CFG)" == "OD3 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\OD3.cnt
InputName=OD3

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "OD3 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\OD3.cnt
InputName=OD3

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\OD3.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section OD3 : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section OD3 : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section OD3 : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section OD3 : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section OD3 : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
