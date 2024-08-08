#include "util.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem> // C++17 standard header file name
namespace fs = std::filesystem;

/**
 * @brief Get the app path object
 * 
 * @return std::filesystem::path 
 */
std::filesystem::path get_app_path()
{
    // Buffer to store the path of the executable
    char exePath[MAX_PATH];

    // Get the path to the executable
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH) == 0) {
        std::cerr << "Failed to get exe path" << std::endl;
        // TODO deal with error
    }

    // Convert the path to the exe to a filesystem path object
    fs::path exeFsPath(exePath);
    // Get the directory of the exe
    fs::path exeDir = exeFsPath.parent_path();

    return exeDir;
};
