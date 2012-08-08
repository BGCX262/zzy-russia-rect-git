; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RussiaRect.h"
LastPage=0

ClassCount=8
Class1=CRussiaRectApp
Class2=CRussiaRectDoc
Class3=CRussiaRectView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_DIALOG2
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=CConnectDlg
Resource3=IDD_ABOUTBOX
Class7=CUserHelp
Resource4=IDD_DIALOG1
Class8=CGameExitDlg
Resource5=IDD_DIALOG3

[CLS:CRussiaRectApp]
Type=0
HeaderFile=RussiaRect.h
ImplementationFile=RussiaRect.cpp
Filter=N

[CLS:CRussiaRectDoc]
Type=0
HeaderFile=RussiaRectDoc.h
ImplementationFile=RussiaRectDoc.cpp
Filter=N

[CLS:CRussiaRectView]
Type=0
HeaderFile=RussiaRectView.h
ImplementationFile=RussiaRectView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CRussiaRectView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDM_Connect
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=RussiaRect.cpp
ImplementationFile=RussiaRect.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_OnePlayer
Command2=IDM_TwoPlayers
Command3=IDM_GameExit
Command4=IDM_Connect
Command5=IDM_Request
Command6=IDM_ShowIP
Command7=IDM_GameStart
Command8=IDM_GamePause
Command9=IDM_GameEnd
Command10=IDM_GRID
Command11=IDM_NOGRID
Command12=IDM_ONMUSIC1
Command13=IDM_ONMUSIC2
Command14=IDM_ONMUSIC3
Command15=IDM_ONMUSIC4
Command16=IDM_ONMUSIC5
Command17=IDM_MUSIC_OFF
Command18=IDM_LEVEL_1
Command19=IDM_LEVEL_2
Command20=IDM_LEVEL_3
Command21=IDM_LEVEL_4
Command22=IDM_LEVEL_5
Command23=ID_APP_ABOUT
Command24=IDM_UserHelp
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_GameStart
Command2=IDM_GamePause
Command3=IDM_GameEnd
Command4=IDM_Connect
Command5=IDM_Request
Command6=IDM_ShowIP
Command7=IDM_UserHelp
Command8=IDM_GameExit
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=CConnectDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342178055
Control4=IDC_RADIO1,button,1342308361
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_STATIC,static,1342308352
Control7=IDC_IP_HOST,SysIPAddress32,1342242816
Control8=IDM_ShowIP,button,1342242816

[CLS:CConnectDlg]
Type=0
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=CUserHelp
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342178055
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[CLS:CUserHelp]
Type=0
HeaderFile=UserHelp.h
ImplementationFile=UserHelp.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserHelp

[DLG:IDD_DIALOG3]
Type=1
Class=CGameExitDlg
ControlCount=3
Control1=ID_APP_EXIT,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342194439

[CLS:CGameExitDlg]
Type=0
HeaderFile=GameExitDlg.h
ImplementationFile=GameExitDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGameExitDlg

