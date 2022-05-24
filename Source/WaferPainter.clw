; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COptionDlg
LastTemplate=CDocument
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WaferPainter.h"
LastPage=0

ClassCount=11
Class1=CWaferPainterApp
Class2=CWaferPainterDoc
Class3=CWaferPainterView
Class4=CMainFrame

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_WAFERPTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_WAFERPTYPE (English (U.S.))
Resource5=IDR_MAINFRAME (English (U.S.))
Class7=CContourView
Resource6=IDR_CONTOURTYPE (English (U.S.))
Class8=COptionDlg
Class9=CContourDoc
Resource7=IDD_ABOUTBOX (English (U.S.))
Class10=C3DContourView
Class11=C3DContourDoc
Resource8=IDR_3DCONTOURTYPE (English (U.S.))
Resource9=IDD_DIALOG_OPTION (English (U.S.))

[CLS:CWaferPainterApp]
Type=0
HeaderFile=WaferPainter.h
ImplementationFile=WaferPainter.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_INTEROPTION

[CLS:CWaferPainterDoc]
Type=0
HeaderFile=WaferPainterDoc.h
ImplementationFile=WaferPainterDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_3DCONTOUR

[CLS:CWaferPainterView]
Type=0
HeaderFile=WaferPainterView.h
ImplementationFile=WaferPainterView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=WaferPainter.cpp
ImplementationFile=WaferPainter.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=8
Command8=ID_APP_ABOUT

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_WAFERPTYPE]
Type=1
Class=CWaferPainterView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[MNU:IDR_WAFERPTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_2DCONTOUR
Command18=ID_3DCONTOUR
Command19=ID_INTEROPTION
Command20=ID_WINDOW_NEW
Command21=ID_WINDOW_CASCADE
Command22=ID_WINDOW_TILE_HORZ
Command23=ID_WINDOW_ARRANGE
Command24=ID_APP_ABOUT
CommandCount=24

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_2DCONTOUR
Command8=ID_3DCONTOUR
Command9=ID_FILE_PRINT
Command10=ID_APP_ABOUT
CommandCount=10

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_INTEROPTION
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CContourView]
Type=0
HeaderFile=ContourView.h
ImplementationFile=ContourView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=ID_APP_ABOUT

[DLG:IDD_DIALOG_OPTION (English (U.S.))]
Type=1
Class=COptionDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO_DIAMETER,button,1342308361
Control5=IDC_RADIO_DIAMETER2,button,1342177289
Control6=IDC_STATIC,button,1342177287
Control7=IDC_RADIO_INTERPOLATER,button,1342308361
Control8=IDC_RADIO_INTERPOLATER2,button,1342177289

[CLS:COptionDlg]
Type=0
HeaderFile=OptionDlg.h
ImplementationFile=OptionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO_INTERPOLATER

[CLS:CContourDoc]
Type=0
HeaderFile=ContourDoc.h
ImplementationFile=ContourDoc.cpp
BaseClass=CDocument
Filter=N
LastObject=CContourDoc

[MNU:IDR_CONTOURTYPE (English (U.S.))]
Type=1
Class=CContourView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_SHOWVALUES
Command18=ID_SHOWLEGEND
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_APP_ABOUT
CommandCount=23

[CLS:C3DContourView]
Type=0
HeaderFile=3DContourView.h
ImplementationFile=3DContourView.cpp
BaseClass=CGLSurfaceView
Filter=C
LastObject=ID_SHOWAXIS
VirtualFilter=VWC

[CLS:C3DContourDoc]
Type=0
HeaderFile=3DContourDoc.h
ImplementationFile=3DContourDoc.cpp
BaseClass=CDocument
Filter=N

[MNU:IDR_3DCONTOURTYPE (English (U.S.))]
Type=1
Class=C3DContourView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_SHOWLEGEND
Command18=ID_SHOWWALL
Command19=ID_SHOWBOUNDARY
Command20=ID_CULLFACE
Command21=ID_SMOOTH
Command22=ID_FLAT
Command23=ID_BGCOLOR
Command24=ID_WINDOW_NEW
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
Command28=ID_APP_ABOUT
CommandCount=28

