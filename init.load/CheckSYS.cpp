#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> files = {
    "C:\\Bootstrap\\core\\core.exe",
    "C:\\Bootstrap\\core\\conf.ecff",
    "C:\\Bootstrap\\idl\\IDLcore.exe",
    "C:\\Bootstrap\\idl\\callBSoD.exe",
    "C:\\Bootstrap\\idl\\CheckSYS.exe",
    "C:\\Bootstrap\\.restore\\core\\core.exe",
    "C:\\Bootstrap\\.restore\\core\\conf.ecff",
    "C:\\Bootstrap\\.restore\\idl\\IDLcore.exe",
    "C:\\Bootstrap\\.restore\\idl\\callBSoD.exe",
    "C:\\Bootstrap\\.restore\\idl\\CheckSYS.exe",
};

int CheckSYS(std::string path)
{
    std::ifstream file(path);
    if (file)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    int err[files.size()];
    for (int i = 0; i < files.size(); i++)
    {
        err[i] = CheckSYS(files[i]);
    }
    for (int i = 0; i < files.size(); i++)
    {
        if (err[i] == 1)
        {
            std::cout << "1" << std::endl;
        }
    }
    std::cout << "0" << std::endl;
}