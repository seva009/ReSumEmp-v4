#include <fstream>
#include <string>
#include <iostream>

std::string discLetters[26]  = {"C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

std::string downloadFile() {
    while (true) {
        for (int i = 0; i < 26; i++) {
            std::string path = discLetters[i] + ":/cfg.ecff";
            std::fstream cfg(path);
            if (cfg) {
                return path;
            }
        }
    }
}