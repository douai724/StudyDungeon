/**
 * @file util.h
 * @author Green Alligators
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

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <windows.h>

extern bool isTestMode;

/**
 * @brief Get the app path object
 * @fn get the path of the application
 * @return std::filesystem::path The path to the executable
 */
std::filesystem::path getAppPath();


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

/**
 * @brief Prompts the user to enter [Yy] for yes and [Nn] for no
 * @return true for [Yy]
 * @return false for [Nn]
 */
bool yesNoPrompt();

/**
 * @brief Checks if name for deckfile meets naming requirements
 * @details Deck filenames should only contain [A-Za-z0-9] characters
 *
 * @param name
 * @return true
 * @return false
 */
bool isValidDeckFileName(std::string name);


/**
 * @brief hides or shows the cursor icon in the console
 *
 */
void ShowConsoleCursor(bool showflag);

#endif
