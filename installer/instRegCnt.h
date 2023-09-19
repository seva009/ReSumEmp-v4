#include <Windows.h>
#include <iostream>

void SetCurrentValue(wchar_t* value, wchar_t* REGISTRY_ROOT, wchar_t* REGISTRY_PATH, wchar_t* REGISTRY_VALUE_NAME) {
    HKEY hKey; // Declare the hKey variable of type HKEY

    LONG result = RegCreateKeyExW((HKEY)REGISTRY_ROOT, REGISTRY_PATH, 0, NULL, 0, KEY_READ | KEY_WRITE, NULL, &hKey, NULL);
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to open or create registry key." << std::endl;
        return;
    }

    DWORD id = (DWORD)value; // Cast value to DWORD

    result = RegSetValueExW(hKey, REGISTRY_VALUE_NAME, 0, REG_DWORD, (BYTE*)&id, sizeof(DWORD));
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to save ID to the registry." << std::endl;
    }

    RegCloseKey(hKey);
}

int GetRegistryKeyValue( wchar_t* REGISTRY_ROOT, const std::wstring& keyPath, const std::wstring& valueName) {
    HKEY hKey;
    LONG result = RegOpenKeyExW((HKEY)REGISTRY_ROOT, keyPath.c_str(), 0, KEY_READ, &hKey);
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