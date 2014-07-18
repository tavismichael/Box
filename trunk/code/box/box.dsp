# Microsoft Developer Studio Project File - Name="box" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=box - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "box.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "box.mak" CFG="box - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "box - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "box - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "box - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "box - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /TP /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 USkin.lib /nologo /subsystem:windows /debug /machine:I386 /out:"lib/box.exe" /pdbtype:sept /libpath:"lib"

!ENDIF 

# Begin Target

# Name "box - Win32 Release"
# Name "box - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\box.cpp
# End Source File
# Begin Source File

SOURCE=.\box.rc
# End Source File
# Begin Source File

SOURCE=.\boxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\box.h
# End Source File
# Begin Source File

SOURCE=.\boxDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\box.ico
# End Source File
# Begin Source File

SOURCE=.\res\box.rc2
# End Source File
# End Group
# Begin Group "Analyse"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Analyse\Analyse.cpp
# End Source File
# Begin Source File

SOURCE=.\Analyse\Analyse.h
# End Source File
# Begin Source File

SOURCE=.\Analyse\EditKeyFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Analyse\EditKeyFile.h
# End Source File
# Begin Source File

SOURCE=.\Analyse\SystemSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Analyse\SystemSet.h
# End Source File
# End Group
# Begin Group "excel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\excel\excel9.cpp
# End Source File
# Begin Source File

SOURCE=.\excel\excel9.h
# End Source File
# End Group
# Begin Group "Log"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Log\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\Log\Log.h
# End Source File
# End Group
# Begin Group "xml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\xml\XMLBase.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\XMLBase.h
# End Source File
# Begin Source File

SOURCE=.\xml\xmlParser.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xmlParser.h
# End Source File
# End Group
# Begin Group "GA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GA\ga\ga.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA1DArrayGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA1DArrayGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA1DBinStrGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA1DBinStrGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA2DArrayGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA2DArrayGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA2DBinStrGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA2DBinStrGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA3DArrayGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA3DArrayGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA3DBinStrGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GA3DBinStrGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAAllele.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAAllele.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAArray.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GABaseGA.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GABaseGA.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GABin2DecGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GABin2DecGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gabincvt.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gabincvt.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GABinStr.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GABinStr.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gaconfig.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GADCrowdingGA.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GADCrowdingGA.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GADemeGA.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GADemeGA.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gaerror.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gaerror.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAEvalData.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gaid.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAIncGA.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAIncGA.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAList.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAList.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAListBASE.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAListBASE.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAListGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAListGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAMask.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GANode.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAParameter.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAPopulation.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAPopulation.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\garandom.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\garandom.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GARealGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GARealGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAScaling.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAScaling.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GASelector.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GASelector.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GASimpleGA.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GASimpleGA.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GASStateGA.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GASStateGA.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAStatistics.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAStringGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GAStringGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GATree.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GATree.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GATreeBASE.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GATreeBASE.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GATreeGenome.cpp
# End Source File
# Begin Source File

SOURCE=.\GA\ga\GATreeGenome.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gatypes.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\gaversion.h
# End Source File
# Begin Source File

SOURCE=.\GA\ga\std_stream.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
