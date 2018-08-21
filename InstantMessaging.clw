; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatRoomServerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "instantmessaging.h"
LastPage=0

ClassCount=26
Class1=CAdvButton
Class2=CAdvComboBox
Class3=CCanvasStatic
Class4=CChatDlg
Class5=CChatRoomClientDlg
Class6=CChatRoomClientSocket
Class7=CChatRoomServerDlg
Class8=CChatRoomServerSocket
Class9=CDialogSetting
Class10=CFriendsListCtrl
Class11=CInstantMessagingApp
Class12=CAboutDlg
Class13=CInstantMessagingDlg
Class14=CListeningSocket
Class15=CReceiveFilesSocket
Class16=CSendFilesClientDlg
Class17=CSendFilesClientThread
Class18=CSendFilesReceiveUsersDlg
Class19=CSendFilesServerDlg
Class20=CSendFilesServerSocket
Class21=CSendFilesServerThread
Class22=CSendFilesSocket
Class23=CWhiteBoardClientDlg
Class24=CWhiteBoardServerDlg
Class25=CWhiteBoardClientSocket
Class26=CWhiteBoardServerSocket

ResourceCount=14
Resource1=IDD_WHITEBOARD_SERVER
Resource2=IDD_DIALOG_BG
Resource3=IDD_WHITEBOARD_CLIENT
Resource4=IDD_SENDFILES_SERVER
Resource5=IDD_CHATROOM_CLIENT
Resource6=IDD_CHAT
Resource7=IDD_CHATROOM_SERVER
Resource8=IDD_INSTANTMESSAGING_DIALOG
Resource9=IDD_SENDFILES_CLIENT
Resource10=IDD_SENDFILES_USER
Resource11=IDD_ABOUTBOX
Resource12=IDR_MENU1
Resource13=IDD_SETTING
Resource14=IDR_MENU2

[CLS:CAdvButton]
Type=0
BaseClass=CButton
HeaderFile=AdvButton.h
ImplementationFile=AdvButton.cpp

[CLS:CAdvComboBox]
Type=0
BaseClass=CComboBoxEx
HeaderFile=AdvComboBox.h
ImplementationFile=AdvComboBox.cpp

[CLS:CCanvasStatic]
Type=0
BaseClass=CStatic
HeaderFile=CanvasStatic.h
ImplementationFile=CanvasStatic.cpp

[CLS:CChatDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatDlg.h
ImplementationFile=ChatDlg.cpp
LastObject=CChatDlg

[CLS:CChatRoomClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatRoomClientDlg.h
ImplementationFile=ChatRoomClientDlg.cpp

[CLS:CChatRoomClientSocket]
Type=0
BaseClass=CSocket
HeaderFile=ChatRoomClientSocket.h
ImplementationFile=ChatRoomClientSocket.cpp

[CLS:CChatRoomServerDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatRoomServerDlg.h
ImplementationFile=ChatRoomServerDlg.cpp
LastObject=IDB_ADDFRIENDS

[CLS:CChatRoomServerSocket]
Type=0
BaseClass=CSocket
HeaderFile=ChatRoomServerSocket.h
ImplementationFile=ChatRoomServerSocket.cpp

[CLS:CDialogSetting]
Type=0
BaseClass=CDialog
HeaderFile=DialogSetting.h
ImplementationFile=DialogSetting.cpp
LastObject=CDialogSetting

[CLS:CFriendsListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=FriendsListCtrl.h
ImplementationFile=FriendsListCtrl.cpp

[CLS:CInstantMessagingApp]
Type=0
BaseClass=CWinApp
HeaderFile=InstantMessaging.h
ImplementationFile=InstantMessaging.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=InstantMessagingDlg.cpp
ImplementationFile=InstantMessagingDlg.cpp
LastObject=CAboutDlg

[CLS:CInstantMessagingDlg]
Type=0
BaseClass=CDialog
HeaderFile=InstantMessagingDlg.h
ImplementationFile=InstantMessagingDlg.cpp
LastObject=CInstantMessagingDlg

[CLS:CListeningSocket]
Type=0
BaseClass=CSocket
HeaderFile=ListeningSocket.h
ImplementationFile=ListeningSocket.cpp

[CLS:CReceiveFilesSocket]
Type=0
BaseClass=CSocket
HeaderFile=ReceiveFilesSocket.h
ImplementationFile=ReceiveFilesSocket.cpp

[CLS:CSendFilesClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=SendFilesClientDlg.h
ImplementationFile=SendFilesClientDlg.cpp

[CLS:CSendFilesClientThread]
Type=0
BaseClass=CWinThread
HeaderFile=SendFilesClientThread.h
ImplementationFile=SendFilesClientThread.cpp

[CLS:CSendFilesReceiveUsersDlg]
Type=0
BaseClass=CDialog
HeaderFile=SendFilesReceiveUsersDlg.h
ImplementationFile=SendFilesReceiveUsersDlg.cpp

[CLS:CSendFilesServerDlg]
Type=0
BaseClass=CDialog
HeaderFile=SendFilesServerDlg.h
ImplementationFile=SendFilesServerDlg.cpp

[CLS:CSendFilesServerSocket]
Type=0
BaseClass=CSocket
HeaderFile=SendFilesServerSocket.h
ImplementationFile=SendFilesServerSocket.cpp
LastObject=IDM_VIDEOCHAT

[CLS:CSendFilesServerThread]
Type=0
BaseClass=CWinThread
HeaderFile=SendFilesServerThread.h
ImplementationFile=SendFilesServerThread.cpp

[CLS:CSendFilesSocket]
Type=0
BaseClass=CSocket
HeaderFile=SendFilesSocket.h
ImplementationFile=SendFilesSocket.cpp

[CLS:CWhiteBoardClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=WhiteBoardClientDlg.h
ImplementationFile=WhiteBoardClientDlg.cpp

[CLS:CWhiteBoardClientSocket]
Type=0
BaseClass=CSocket
HeaderFile=WhiteBoardClientSocket.h
ImplementationFile=WhiteBoardClientSocket.cpp

[CLS:CWhiteBoardServerDlg]
Type=0
BaseClass=CDialog
HeaderFile=WhiteBoardServerDlg.h
ImplementationFile=WhiteBoardServerDlg.cpp
LastObject=CWhiteBoardServerDlg

[CLS:CWhiteBoardServerSocket]
Type=0
BaseClass=CSocket
HeaderFile=WhiteBoardServerSocket.h
ImplementationFile=WhiteBoardServerSocket.cpp

[DLG:IDD_CHAT]
Type=1
Class=CChatDlg
ControlCount=9
Control1=IDC_RICHTEXT_SEND,{3B7C8860-D78F-101B-B9B5-04021C009402},1342242816
Control2=IDB_SEND,button,1342242816
Control3=IDB_LOADFILE,button,1342242816
Control4=IDC_SAVEFILE,button,1342242819
Control5=IDB_CLOSE,button,1342242816
Control6=IDC_RICHTEXT_RECEIVED,{3B7C8860-D78F-101B-B9B5-04021C009402},1342242816
Control7=IDS_FACE,static,1342177294
Control8=IDS_NICKNAME,static,1342308364
Control9=IDS_IP,static,1342308364

[DLG:IDD_CHATROOM_CLIENT]
Type=1
Class=CChatRoomClientDlg
ControlCount=5
Control1=IDE_SEND,edit,1352732740
Control2=IDB_CLOSE,button,1342242816
Control3=IDB_SEND,button,1342242816
Control4=IDE_RECEIVED,edit,1352734788
Control5=IDC_LIST_INCHAT,SysListView32,1350647809

[DLG:IDD_CHATROOM_SERVER]
Type=1
Class=CChatRoomServerDlg
ControlCount=8
Control1=IDE_SEND,edit,1352732740
Control2=IDB_COLSE,button,1342242816
Control3=IDB_SEND,button,1342242816
Control4=IDE_RECEIVED,edit,1352734788
Control5=IDC_LIST_INCHAT,SysListView32,1350647809
Control6=IDB_ADDFRIENDS,button,1342242816
Control7=IDB_DELFRIENDS,button,1342242816
Control8=IDC_LIST_OUTOFCHAT,SysListView32,1350647809

[DLG:IDD_SETTING]
Type=1
Class=CDialogSetting
ControlCount=9
Control1=IDC_EDIT_NICKNAME,edit,1350631552
Control2=IDC_COMBOBOXEX_FACE,ComboBoxEx32,1344340227
Control3=IDC_HOTKEY,msctls_hotkey32,1350631424
Control4=IDB_SAVE,button,1342242816
Control5=IDB_CANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CHECK_AUTOADDFRIENDS,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SENDFILES_CLIENT]
Type=1
Class=CSendFilesClientDlg
ControlCount=2
Control1=IDC_LIST_RECEIVE,SysListView32,1350631433
Control2=IDB_DELETE,button,1342242816

[DLG:IDD_SENDFILES_USER]
Type=1
Class=CSendFilesReceiveUsersDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242817
Control3=IDC_LIST_USER,SysListView32,1350647809

[DLG:IDD_SENDFILES_SERVER]
Type=1
Class=CSendFilesServerDlg
ControlCount=3
Control1=IDC_LIST_SEND,SysListView32,1350631433
Control2=IDB_DELETE,button,1342242816
Control3=IDB_ADD,button,1342242816

[DLG:IDD_WHITEBOARD_CLIENT]
Type=1
Class=CWhiteBoardClientDlg
ControlCount=14
Control1=IDS_CANVAS,static,1342177543
Control2=IDB_ERASER,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDB_PENCIL,button,1342242816
Control5=IDB_LINE,button,1342242816
Control6=IDB_RECTANGLE_EMPTY,button,1342242816
Control7=IDB_RECTANGLE,button,1342242816
Control8=IDB_ELLIPSE_EMPTY,button,1342242816
Control9=IDB_ELLIPSE,button,1342242816
Control10=IDS_COLOR,static,1342178055
Control11=IDB_WIDTH_2,button,1342242816
Control12=IDB_WIDTH_1,button,1342242816
Control13=IDB_WIDTH_3,button,1342242816
Control14=IDB_WIDTH_4,button,1342242816

[DLG:IDD_WHITEBOARD_SERVER]
Type=1
Class=CWhiteBoardServerDlg
ControlCount=18
Control1=IDC_LIST_INWHITEBOARD,SysListView32,1350647809
Control2=IDC_LIST_OUTOFWHITEBOARD,SysListView32,1350647809
Control3=IDB_ADDFRIENDS,button,1342242816
Control4=IDB_DELFRIENDS,button,1342242816
Control5=IDS_CANVAS,static,1342177543
Control6=IDB_ERASER,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDB_PENCIL,button,1342242816
Control9=IDB_LINE,button,1342242816
Control10=IDB_RECTANGLE_EMPTY,button,1342242816
Control11=IDB_RECTANGLE,button,1342242816
Control12=IDB_ELLIPSE_EMPTY,button,1342242816
Control13=IDB_ELLIPSE,button,1342242816
Control14=IDS_COLOR,static,1342178055
Control15=IDB_WIDTH_2,button,1342242816
Control16=IDB_WIDTH_1,button,1342242816
Control17=IDB_WIDTH_3,button,1342242816
Control18=IDB_WIDTH_4,button,1342242816

[DLG:IDD_DIALOG_BG]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDM_SETTING
Command2=IDM_CHATROOM
Command3=IDM_SENDFILES
Command4=IDM_RECEIVEFILES
Command5=IDM_WHITEBOARD
Command6=IDM_STATE
Command7=IDM_EXIT
CommandCount=7

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=IDM_SENDMESSAGE
Command2=IDM_DELETEUSER
CommandCount=2

[DLG:IDD_INSTANTMESSAGING_DIALOG]
Type=1
Class=CInstantMessagingDlg
ControlCount=12
Control1=IDC_LIST_FRIENDS,SysListView32,1350648845
Control2=IDC_COMBO_STATE,combobox,1344339971
Control3=IDC_COMBO_FRIEND,combobox,1344340226
Control4=IDC_EDIT_NICKNAME,edit,1350633600
Control5=IDC_STATIC_FACE,static,1350566414
Control6=IDC_BTN_ADDFRIEND,button,1342177280
Control7=IDC_BTN_CHATROOM,button,1342177280
Control8=IDC_BTN_SENDFILES,button,1342177280
Control9=IDC_BTN_WHITEBOARD,button,1342177280
Control10=IDC_COMBO_IP,combobox,1344340227
Control11=IDB_ADD_SECTION,button,1342242816
Control12=IDC_STATIC,static,1342177294

