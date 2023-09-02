#include <fstream>
#include <string>
#include <iostream>

#include <stdio.h>
#include "curl/curl.h"

std::string discLetters[26]  = {"C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

std::string trueDownloadFile(const char *url = "...", const bool createCustomFilename = false) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char outfilename[FILENAME_MAX] = "C:\\Bootstrap\\cfg.ecff";
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return outfilename;
}

std::string downloadFile(const bool trueDownload = false) {
    if (trueDownload) {
        return trueDownloadFile();
    }
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


