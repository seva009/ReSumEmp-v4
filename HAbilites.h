#include <fstream>

bool hAblities() {
    std::ifstream file;
    file.open("C:\\Windows\\System32\\cmd.exe", std::ios::binary); 
    if (!file.is_open()) {
        return false;
    }
    return true;
}