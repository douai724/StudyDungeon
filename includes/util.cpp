#include <windows.h>
#include <iostream>
#include <string>


std::string get_app_path(){
 char path[MAX_PATH];

    // This will return the path of the executable, can take this and build relative paths
    // for where the deck files whould be
    if(GetModuleFileName(NULL, path, MAX_PATH)){
        //std::cout << "Program path: " << path << std::endl;
    } else {
        std::cerr << "Error getting path." << std::endl;

    }
    //TODO subsstring to remove program name
    return path;

    // remove app name
    // return path
}
// printf("MAX_PATH: %d\n", MAX_PATH);
//     TCHAR buffer[MAX_PATH];
//     DWORD length = GetCurrentDirectory(MAX_PATH, buffer);
//     if(length == 0){
//         printf("Error\n");
//     } else {
//         printf("Current directory: %s\n", buffer);
//     }