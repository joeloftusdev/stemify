!include "MUI2.nsh"

Outfile "..\build\StemifyInstaller.exe"
RequestExecutionLevel admin

InstallDir $PROGRAMFILES\Stemify

Var DotNet6Installed

!define MUI_ICON "..\build\SpleeterUI\Debug\icon.ico"
Name "Stemify"
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "CheckDotNet6"
    ReadRegDWORD $DotNet6Installed HKLM "SOFTWARE\Microsoft\NET Framework Setup\NDP\v6.0" "Install"

    StrCmp $DotNet6Installed 1 DotNet6Installed
    StrCpy $DotNet6Installed 0
    Goto EndDotNet6Check
DotNet6Installed:
    StrCpy $DotNet6Installed 1
EndDotNet6Check:
SectionEnd

Section "MainSection"
    CreateDirectory $PROGRAMFILES\Stemify
    SetOutPath $INSTDIR
    CreateShortCut "$INSTDIR\Stemify.lnk" "$INSTDIR\SpleeterUI.exe" "" "$INSTDIR\icon.ico"
    CreateShortCut "$DESKTOP\Stemify.lnk" "$INSTDIR\SpleeterUI.exe" "" "$INSTDIR\icon.ico"

    StrCmp $DotNet6Installed 1 DotNet6Installed
    ExecWait 'dotnet-runtime-6.0.x-win-x64.exe /install /passive'
DotNet6Installed:

    File /r "..\build\SpleeterUI\Debug\"
    File /r "..\SpleeterLib\deps\spleeterpp\build\tensorflow\lib\tensorflow.dll"

SectionEnd
