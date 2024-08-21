#include "artwork.h"

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
