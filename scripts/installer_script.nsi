Outfile "..\build\StemifyInstaller.exe"
RequestExecutionLevel admin


InstallDir $PROGRAMFILES\Stemify

Var DotNet6Installed

Page directory
Page instfiles



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
    CreateShortCut "$INSTDIR\Stemify.lnk" "$INSTDIR\SpleeterUI.exe"
    StrCmp $DotNet6Installed 1 DotNet6Installed
    ExecWait 'dotnet-runtime-6.0.x-win-x64.exe /install /passive'
DotNet6Installed:

    File /r "..\build\SpleeterUI\Debug\"
    File /r "..\SpleeterLib\deps\spleeterpp\build\tensorflow\lib\tensorflow.dll"

SectionEnd

