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
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>
#include <random>

/** used to toggle between simulated input (true) and user input (false) */
extern bool isTestMode;

// Defines the character code recieved by getch on key press
/** key code for enter */
const int _key_enter{13};
/** key code for backspace */
const int _key_backspace{8};
/** key code for escape */
const int _key_esc{27};
/** key code for space */
const int _key_space{32};
/** key code for if an arrow has been pressed */
const int _arrow_prefix{224};
/** key code for if an arrow is pressed but numlock is on */
const int _numlock{0};
/** key code for up arrow */
const int _key_up{72};
/** key code for down arrow */
const int _key_down{80};
/** key code for down arrow */
const int _key_left{75};
/** key code for right arrow */
const int _key_right{77};


/** escape sequence for virtual terminal sequences */
const std::string _ESC{"\x1b"};
// const std::string _ESC {"\033"}; // ansi escape code

/**
 * @brief enables the virtual terminal processing mode
 * @details sets the ENABLE_VIRTUAL_TERMINAL_PROCESSING flag so that virtual terminal sequences
 * will be interpreted by the console to display colour and formatting
 *
 */
bool enableVirtualTerminal();


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

/**
 * @brief Reads in a file of 256bit colour values and wraps the ANSI escape sequences around each
 *
 * @param filename
 * @return std::string A string with the ANSI escape sequences embedded
 */
std::string convertFileToANSI(std::string filename);

std::vector<std::string> convertAsciiArtToLines(const std::string &asciiArt);

std::string getRandomPositiveQuote();

std::string getRandomEncouragingQuote();

std::string getRandomPhrase();


#endif
