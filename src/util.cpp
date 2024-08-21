#include "util.h"

namespace fs = std::filesystem;

/**
 * @brief Get the app path object
 * @fn get the path of the application
 * @return std::filesystem::path The path to the executable
 */
std::filesystem::path get_app_path()
{
    // Buffer to store the path of the executable
    char exePath[MAX_PATH];

    // Get the path to the executable
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH) == 0)
    {
        std::cerr << "Failed to get exe path" << std::endl;
        // TODO deal with error
    }

    // Convert the path to the exe to a filesystem path object
    fs::path exeFsPath(exePath);
    // Get the directory of the exe
    fs::path exeDir = exeFsPath.parent_path();

    return exeDir;
};

/**
 * @brief Create a directory
 *
 * @param dir_path
 */
void create_dir(std::filesystem::path dir_path)
{
    // TODO: implement function
    std::cout << "Directory to be created" << dir_path << std::endl;
};


/**
 * @brief Displays an ascii art title
 *
 */
void splashScreen()
{
    system("cls");
    std::cout << "     _____ _             _       _____                                      " << std::endl;
    std::cout << "    / ____| |           | |     |  __ \\                                     " << std::endl;
    std::cout << "   | (___ | |_ _   _  __| |_   _| |  | |_   _ _ __   __ _  ___  ___  _ __   " << std::endl;
    std::cout << "    \\___ \\| __| | | |/ _` | | | | |  | | | | | '_ \\ / _` |/ _ \\/ _ \\| '_ \\  " << std::endl;
    std::cout << "    ____) | |_| |_| | (_| | |_| | |__| | |_| | | | | (_| |  __/ (_) | | | | " << std::endl;
    std::cout << "   |_____/ \\__|\\__,_|\\__,_|\\__, |_____/ \\__,_|_| |_|\\__, |\\___|\\___/|_| |_| " << std::endl;
    std::cout << "                            __/ |                    __/ |                  " << std::endl;
    std::cout << "                           |___/                    |___/                   " << std::endl;
    system("pause");
};
