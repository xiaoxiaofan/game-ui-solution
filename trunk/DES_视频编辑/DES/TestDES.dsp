# Microsoft Developer Studio Project File - Name="TestDES" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestDES - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestDES.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestDES.mak" CFG="TestDES - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestDES - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestDES - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestDES - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmbase.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestDES - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmiids.lib Strmbasd.lib Msvcrtd.lib Winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestDES - Win32 Release"
# Name "TestDES - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CHelpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHelpDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestDES.cpp
# End Source File
# Begin Source File

SOURCE=.\TestDES.h
# End Source File
# Begin Source File

SOURCE=.\TestDESDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TestDESDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\res\TestDES.ico
# End Source File
# Begin Source File

SOURCE=.\TestDES.rc
# End Source File
# Begin Source File

SOURCE=.\res\TestDES.rc2
# End Source File
# End Group
# Begin Group "DES Wrapper"

# PROP Default_Filter ""
# Begin Group "DES Basic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDESBaseObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESBaseObject.h
# End Source File
# Begin Source File

SOURCE=.\CDESMediaDetector.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESMediaDetector.h
# End Source File
# Begin Source File

SOURCE=.\CDESPropertySetter.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESPropertySetter.h
# End Source File
# Begin Source File

SOURCE=.\CDESRenderEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESRenderEngine.h
# End Source File
# Begin Source File

SOURCE=.\CDESTimeLine.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESTimeLine.h
# End Source File
# Begin Source File

SOURCE=.\CDESXml.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESXml.h
# End Source File
# End Group
# Begin Group "Components"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDESComposition.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESComposition.h
# End Source File
# Begin Source File

SOURCE=.\CDESEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESEffect.h
# End Source File
# Begin Source File

SOURCE=.\CDESGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESGroup.h
# End Source File
# Begin Source File

SOURCE=.\CDESSource.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESSource.h
# End Source File
# Begin Source File

SOURCE=.\CDESTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESTrack.h
# End Source File
# Begin Source File

SOURCE=.\CDESTransition.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESTransition.h
# End Source File
# End Group
# Begin Group "Common Interfaces"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDESBaseInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESBaseInterface.h
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineEffectable.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineEffectable.h
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineSplittable.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineSplittable.h
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineTransable.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineTransable.h
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineVirtualTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESIAMTimelineVirtualTrack.h
# End Source File
# End Group
# End Group
# Begin Group "DES Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDESGuid.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESGuid.h
# End Source File
# Begin Source File

SOURCE=.\CDESSourceNode.cpp
# End Source File
# Begin Source File

SOURCE=.\CDESSourceNode.h
# End Source File
# Begin Source File

SOURCE=.\UDESUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\UDESUtils.h
# End Source File
# End Group
# Begin Group "Msi Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StWaitCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\StWaitCursor.h
# End Source File
# End Group
# End Target
# End Project
