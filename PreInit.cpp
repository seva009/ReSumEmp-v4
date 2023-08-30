#include <iostream>
#include <windows.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        SHELLEXECUTEINFO shInfo = { sizeof(SHELLEXECUTEINFO) };
        shInfo.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_FLAG_DDEWAIT;
        shInfo.lpVerb = "runas";
        shInfo.lpFile = argv[0];
        shInfo.lpParameters = "parameters";
        shInfo.nShow = SW_SHOW;

        if (!ShellExecuteEx(&shInfo)) {
            std::cout << "fail";
            return 1;
        }
    }
    return 0;
}
