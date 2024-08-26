/**
 * @file util.h
 * @author Green Aligators
 * @brief Contains useful helper functions
 * @version 0.1
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef UTIL_H
#define UTIL_H
#include <filesystem>
#include <iostream>
#include <string>
#include <windows.h>


/**
 * @brief Get the app path object
 * @fn get the path of the application
 * @return std::filesystem::path The path to the executable
 */
std::filesystem::path get_app_path();

/**
 * @brief starts a countdown timer for a specified number of minutes
 *
 * @param minutes
 */
void timer(int minutes);

/**
 * @brief An alternative to system('pause')
 * @details implementation based on from https://thelinuxcode.com/system-pause-c/
 *
 */
void pause();

/*
 * @brief Clears the screen.
 *
 * @details Credit: SirEnder125 on cplusplus.com
 *
 */
void clearScreen();


#endif
