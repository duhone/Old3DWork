# Microsoft Developer Studio Project File - Name="cooktor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=cooktor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cooktor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cooktor.mak" CFG="cooktor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cooktor - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cooktor - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cooktor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOKTOR_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\include" /I "..\..\shared" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOKTOR_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 d3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"cooktor.dll"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOKTOR_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\shared" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOKTOR_EXPORTS" /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 d3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"cooktor.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "cooktor - Win32 Release"
# Name "cooktor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\shared\eb_property.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\CommonSrc\nvmesh.cpp
# End Source File
# Begin Source File

SOURCE=.\shader_cooktor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cooktor.h
# End Source File
# Begin Source File

SOURCE=..\..\shared\eb_effect.h
# End Source File
# Begin Source File

SOURCE=..\..\shared\eb_property.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\nvmesh.h
# End Source File
# Begin Source File

SOURCE=.\shader_cooktor.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\att_cube.nvp

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\att_cube.nvp

"att_cube.pso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm -d att_cube.nvp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\basic.nvp

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\basic.nvp

"basic.pso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm -d basic.nvp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\basic.nvv

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\basic.nvv

"basic.vso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm  basic.nvv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cooktor.nvv

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\cooktor.nvv

"cooktor.vso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm  cooktor.nvv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cooktorcube.nvv

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\cooktorcube.nvv

"cooktorcube.vso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm  cooktorcube.nvv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ctcubemap.nvv

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\ctcubemap.nvv

"ctcubemap.vso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm  ctcubemap.nvv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cubemap.nvv

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\cubemap.nvv

"cubemap.vso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm  cubemap.nvv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\phong.nvv

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\phong.nvv

"phong.vso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm  phong.nvv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\phongcube.nvv

!IF  "$(CFG)" == "cooktor - Win32 Release"

!ELSEIF  "$(CFG)" == "cooktor - Win32 Debug"

# Begin Custom Build
InputPath=.\phongcube.nvv

"phongcube.vso" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\nvasm  phongcube.nvv

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
