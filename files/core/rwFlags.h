#include <fstream>
#include <string>
#include <math.h>

 //DONT USE THIS FUNC!!!
int getFlagLine(const std::string& flagName, const std::string& filePath) {
    std::ifstream flags(filePath);
    if (!flags) {
        std::ofstream flags(filePath);
        flags << flagName << '\n';
        flags << "&&" << '\n';
        flags << "1000" << '\n'; //sometime i fix it
    }
    std::string bufferL;
    int lineC = 1;
    int flagValue = -1;
    int flagLine;
    bool isHalfReached = false;
    if (flags) {
        while (std::getline(flags, bufferL)) {
            if (bufferL != "&&" && !isHalfReached) {
                if (bufferL == flagName) {
                    flagLine = lineC;
                }
                else {
                    lineC++;
                }
            }
            else {
                for(int i = 0; i < flagLine; i++) {
                   std::getline(flags, bufferL);
                }
                if (bufferL == "&&") {
                    break;
                }
                flagValue = stoi(bufferL);
                return flagValue;
                break;
            }
        }
    }
}

 //DONT USE THIS FUNC!!!
void setFlagValue(int flagValue, const std::string& flagName, const std::string& filePath) {
    std::fstream flags(filePath);
    std::string bufferL;
    int lineC = 1;
    int flagLine;
    bool isHalfReached = false;
    if (flags) {
        while (std::getline(flags, bufferL)) {
            if (bufferL != "&&" && !isHalfReached) {
                if (bufferL == flagName) {
                    flagLine = lineC;
                }
                else {
                    lineC++;
                }
            }
            else {
                for(int i = 1; i < flagLine; i++) {
                   std::getline(flags, bufferL);
                }
                if (bufferL == "&&") {
                    break;
                }
                for (int i = 0; i < 3; i++) {
                   flags << ' ';
                }
                flags << flagValue;
                break;
            
        }
    }
}
}

int rwFlags(char mode, std::string flagName, std::string filePath, int flagValue) {
    if (mode == 'r') {
        int flagValue = getFlagLine(flagName, filePath);
        return flagValue;
    }
    else if (mode == 'w') {
        setFlagValue(flagValue, flagName, filePath);
        return 0;
    }
    return -1;
}