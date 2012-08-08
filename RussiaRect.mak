# Microsoft Developer Studio Generated NMAKE File, Based on RussiaRect.dsp
!IF "$(CFG)" == ""
CFG=RussiaRect - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RussiaRect - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RussiaRect - Win32 Release" && "$(CFG)" != "RussiaRect - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RussiaRect.mak" CFG="RussiaRect - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RussiaRect - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RussiaRect - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RussiaRect - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\RussiaRect.exe"


CLEAN :
	-@erase "$(INTDIR)\ConnectDlg.obj"
	-@erase "$(INTDIR)\GameExitDlg.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RussiaRect.obj"
	-@erase "$(INTDIR)\RussiaRect.pch"
	-@erase "$(INTDIR)\RussiaRect.res"
	-@erase "$(INTDIR)\RussiaRectDoc.obj"
	-@erase "$(INTDIR)\RussiaRectView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UserHelp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\RussiaRect.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\RussiaRect.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\RussiaRect.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RussiaRect.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\RussiaRect.pdb" /machine:I386 /out:"$(OUTDIR)\RussiaRect.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ConnectDlg.obj" \
	"$(INTDIR)\GameExitDlg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RussiaRect.obj" \
	"$(INTDIR)\RussiaRectDoc.obj" \
	"$(INTDIR)\RussiaRectView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UserHelp.obj" \
	"$(INTDIR)\RussiaRect.res"

"$(OUTDIR)\RussiaRect.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RussiaRect - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\RussiaRect.exe"


CLEAN :
	-@erase "$(INTDIR)\ConnectDlg.obj"
	-@erase "$(INTDIR)\GameExitDlg.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RussiaRect.obj"
	-@erase "$(INTDIR)\RussiaRect.pch"
	-@erase "$(INTDIR)\RussiaRect.res"
	-@erase "$(INTDIR)\RussiaRectDoc.obj"
	-@erase "$(INTDIR)\RussiaRectView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UserHelp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\RussiaRect.exe"
	-@erase "$(OUTDIR)\RussiaRect.ilk"
	-@erase "$(OUTDIR)\RussiaRect.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\RussiaRect.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\RussiaRect.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RussiaRect.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\RussiaRect.pdb" /debug /machine:I386 /out:"$(OUTDIR)\RussiaRect.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ConnectDlg.obj" \
	"$(INTDIR)\GameExitDlg.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RussiaRect.obj" \
	"$(INTDIR)\RussiaRectDoc.obj" \
	"$(INTDIR)\RussiaRectView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UserHelp.obj" \
	"$(INTDIR)\RussiaRect.res"

"$(OUTDIR)\RussiaRect.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("RussiaRect.dep")
!INCLUDE "RussiaRect.dep"
!ELSE 
!MESSAGE Warning: cannot find "RussiaRect.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "RussiaRect - Win32 Release" || "$(CFG)" == "RussiaRect - Win32 Debug"
SOURCE=.\ConnectDlg.cpp

"$(INTDIR)\ConnectDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RussiaRect.pch"


SOURCE=.\GameExitDlg.cpp

"$(INTDIR)\GameExitDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RussiaRect.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RussiaRect.pch"


SOURCE=.\RussiaRect.cpp

"$(INTDIR)\RussiaRect.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RussiaRect.pch"


SOURCE=.\RussiaRect.rc

"$(INTDIR)\RussiaRect.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\RussiaRectDoc.cpp

"$(INTDIR)\RussiaRectDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RussiaRect.pch"


SOURCE=.\RussiaRectView.cpp

"$(INTDIR)\RussiaRectView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RussiaRect.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "RussiaRect - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\RussiaRect.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RussiaRect.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RussiaRect - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\RussiaRect.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RussiaRect.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\UserHelp.cpp

"$(INTDIR)\UserHelp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RussiaRect.pch"



!ENDIF 

