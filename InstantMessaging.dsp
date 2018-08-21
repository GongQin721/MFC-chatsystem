# Microsoft Developer Studio Project File - Name="InstantMessaging" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=InstantMessaging - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "InstantMessaging.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "InstantMessaging.mak" CFG="InstantMessaging - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InstantMessaging - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "InstantMessaging - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "InstantMessaging - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "InstantMessaging - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "InstantMessaging - Win32 Release"
# Name "InstantMessaging - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DialogSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\InstantMessaging.cpp
# End Source File
# Begin Source File

SOURCE=.\InstantMessaging.rc
# End Source File
# Begin Source File

SOURCE=.\InstantMessagingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ListeningSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DialogSetting.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\InstantMessaging.h
# End Source File
# Begin Source File

SOURCE=.\InstantMessagingDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListeningSocket.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\zconf.h
# End Source File
# Begin Source File

SOURCE=.\zlib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\addfriend_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\addfriend_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\addfriend_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\addfriend_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\addfriend_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\addfriend_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\addfriend_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\addfriend_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bitmap84.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bitmap86.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\bitmap86.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp167.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp168.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp169.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp170.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp171.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp172.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp173.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp174.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp175.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp176.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp177.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp178.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp179.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp180.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp181.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp182.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp183.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp184.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp185.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp186.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp187.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp188.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp189.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp190.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp191.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp192.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp193.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp194.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp195.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp196.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp197.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp198.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp199.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp200.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp201.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp202.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp203.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp204.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp205.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp206.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp207.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp208.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp209.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp210.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp211.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp212.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp213.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp214.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp215.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp216.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp217.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp218.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp219.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp220.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp221.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp222.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp223.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp224.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp225.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp226.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp227.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp228.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp229.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp230.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp231.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp232.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp233.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp234.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp235.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp236.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp237.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp238.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp239.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp240.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp241.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp242.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp243.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp244.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp245.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp246.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp247.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp248.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Face\bmp249.bmp
# End Source File
# Begin Source File

SOURCE=.\res\camera.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\chatroom_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\chatroom_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\chatroom_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\chatroom_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor.cur
# End Source File
# Begin Source File

SOURCE=".\res\damotouicon (1).ico"
# End Source File
# Begin Source File

SOURCE=.\res\delete.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\delfriend_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\delfriend_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\delfriend_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChatRoom\delfriend_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_empty_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_empty_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_empty_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_empty_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\ellipse_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\eraser_1.cur
# End Source File
# Begin Source File

SOURCE=.\res\eraser_2.cur
# End Source File
# Begin Source File

SOURCE=.\res\eraser_3.cur
# End Source File
# Begin Source File

SOURCE=.\res\eraser_4.cur
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\eraser_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\eraser_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\eraser_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\eraser_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InstantMessaging.ico
# End Source File
# Begin Source File

SOURCE=.\res\InstantMessaging.rc2
# End Source File
# Begin Source File

SOURCE=.\res\InstantMessaging_offline.ico
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\line_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\line_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\line_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\line_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mike.ico
# End Source File
# Begin Source File

SOURCE=.\res\offline.ico
# End Source File
# Begin Source File

SOURCE=.\res\pencil.cur
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\pencil_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\pencil_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\pencil_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\pencil_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_empty_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_empty_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_empty_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_empty_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\rectangle_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sendfiles_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sendfiles_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sendfiles_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sendfiles_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sharescreen_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sharescreen_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sharescreen_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\sharescreen_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trump.ico
# End Source File
# Begin Source File

SOURCE=.\res\Button\whiteboard_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\whiteboard_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\whiteboard_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Button\whiteboard_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_1_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_1_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_1_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_1_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_2_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_2_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_2_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_2_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_3_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_3_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_3_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_3_normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_4_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_4_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_4_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WhiteBoard\width_4_normal.bmp
# End Source File
# End Group
# Begin Group "Chat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatDlg.h
# End Source File
# End Group
# Begin Group "RichText"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\oleobject.cpp
# End Source File
# Begin Source File

SOURCE=.\oleobject.h
# End Source File
# Begin Source File

SOURCE=.\oleobjects.cpp
# End Source File
# Begin Source File

SOURCE=.\oleobjects.h
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\richtext.cpp
# End Source File
# Begin Source File

SOURCE=.\richtext.h
# End Source File
# End Group
# Begin Group "ChatRoom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChatRoomClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatRoomClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChatRoomClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatRoomClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\ChatRoomServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatRoomServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChatRoomServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatRoomServerSocket.h
# End Source File
# End Group
# Begin Group "AdvButton"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AdvButton.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvButton.h
# End Source File
# End Group
# Begin Group "FriendsListCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FriendsListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FriendsListCtrl.h
# End Source File
# End Group
# Begin Group "SendFiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ReceiveFilesSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ReceiveFilesSocket.h
# End Source File
# Begin Source File

SOURCE=.\SendFilesClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFilesClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\SendFilesClientThread.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFilesClientThread.h
# End Source File
# Begin Source File

SOURCE=.\SendFilesReceiveUsersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFilesReceiveUsersDlg.h
# End Source File
# Begin Source File

SOURCE=.\SendFilesServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFilesServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\SendFilesServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFilesServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\SendFilesServerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFilesServerThread.h
# End Source File
# Begin Source File

SOURCE=.\SendFilesSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFilesSocket.h
# End Source File
# End Group
# Begin Group "WhiteBoard"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WhiteBoardClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WhiteBoardClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\WhiteBoardClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\WhiteBoardClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\WhiteBoardServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WhiteBoardServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\WhiteBoardServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\WhiteBoardServerSocket.h
# End Source File
# End Group
# Begin Group "CanvasStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CanvasStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\CanvasStatic.h
# End Source File
# End Group
# End Target
# End Project
# Section InstantMessaging : {859321D0-3FD1-11CF-8981-00AA00688B10}
# 	2:5:Class:COLEObjects
# 	2:10:HeaderFile:oleobjects.h
# 	2:8:ImplFile:oleobjects.cpp
# End Section
# Section InstantMessaging : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section InstantMessaging : {3B7C8860-D78F-101B-B9B5-04021C009402}
# 	2:21:DefaultSinkHeaderFile:richtext.h
# 	2:16:DefaultSinkClass:CRichText
# End Section
# Section InstantMessaging : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section InstantMessaging : {ED117630-4090-11CF-8981-00AA00688B10}
# 	2:5:Class:COLEObject
# 	2:10:HeaderFile:oleobject.h
# 	2:8:ImplFile:oleobject.cpp
# End Section
# Section InstantMessaging : {E9A5593C-CAB0-11D1-8C0B-0000F8754DA1}
# 	2:5:Class:CRichText
# 	2:10:HeaderFile:richtext.h
# 	2:8:ImplFile:richtext.cpp
# End Section
