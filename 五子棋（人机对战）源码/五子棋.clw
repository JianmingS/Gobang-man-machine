; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "五子棋.h"

ClassCount=4
Class1=CMyApp
Class2=CMyDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG1
Class4=CSettingDlg
Resource4=IDD_MY_DIALOG

[CLS:CMyApp]
Type=0
HeaderFile=五子棋.h
ImplementationFile=五子棋.cpp
Filter=N

[CLS:CMyDlg]
Type=0
HeaderFile=五子棋Dlg.h
ImplementationFile=五子棋Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMyDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=五子棋Dlg.h
ImplementationFile=五子棋Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=4
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON3,button,1342242816
Control3=IDC_BUTTON4,button,1342242816
Control4=IDC_BUTTON2,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CSettingDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289

[CLS:CSettingDlg]
Type=0
HeaderFile=SettingDlg.h
ImplementationFile=SettingDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO1
VirtualFilter=dWC

