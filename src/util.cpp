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
 * @brief starts a countdown timer for a specified number of minutes
 *
 * @param minutes
 */
void timer(int minutes)
{
    // TODO: implement function
}

void clearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }
