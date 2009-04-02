!include "MUI2.nsh"

;--------------------------------
;General

;Name and file
Name "Marshmallow Duel: Percy's Return"
OutFile "mdpr-installer.exe"

;Default installation folder
InstallDir "$PROGRAMFILES\Marshmallow Duel: Percy's Return"

;Get installation folder from registry if available
InstallDirRegKey HKCU "Software\Marshmallow Duel: Percy's Return" ""

;Request application privileges for Windows Vista
RequestExecutionLevel user


;Interface Settings

!define MUI_ABORTWARNING


;Pages
!insertmacro MUI_PAGE_LICENSE "artistic-2_0.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;Languages
!insertmacro MUI_LANGUAGE "English"


;Installer Sections
Section "Game" SecGame
	SetOutPath "$INSTDIR"
	WriteRegStr HKCU "Software\Marshmallow Duel: Percy's Return" "" $INSTDIR
	File /r /x .svn /x *.db data
	File Release\mdpr.exe
	File dll\*.dll

	WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Server" SecServer
	SetOutPath "$INSTDIR"
	
	File dll\*.dll
	File /r /x .svn /x *.db data
	File Release\server.exe

	WriteRegStr HKCU "Software\Marshmallow Duel: Percy's Return" "" $INSTDIR

	WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

;Language strings
LangString DESC_SecGame ${LANG_ENGLISH} "The game."
LangString DESC_SecServer ${LANG_ENGLISH} "The server."

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT ${SecGame} $(DESC_SecGame)
!insertmacro MUI_DESCRIPTION_TEXT ${SecServer} $(DESC_SecServer)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
	Delete "$INSTDIR\*.*"

	RMDir "$INSTDIR"

	DeleteRegKey /ifempty HKCU "Software\Marshmallow Duel: Percy's Return"
SectionEnd