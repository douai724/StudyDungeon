/**
 * @file util.h
 * @author Green Alligators
 * @brief Contains useful helper functions
 * @version @PROJECT_VERSION@
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

/** used to toggle between simulated input (true) and user input (false) */
extern bool isTestMode;

namespace key
{
// Defines the character code recieved by getch on key press
/** key code for enter */
const int key_enter{13};
/** key code for backspace */
const int key_backspace{8};
/** key code for escape */
const int key_esc{27};
/** key code for space */
const int key_space{32};
/** key code for if an arrow has been pressed */
const int arrow_prefix{224};
/** key code for if an arrow is pressed but numlock is on */
const int numlock{0};
/** key code for up arrow */
const int key_up{72};
/** key code for down arrow */
const int key_down{80};
/** key code for down arrow */
const int key_left{75};
/** key code for right arrow */
const int key_right{77};


/** escape sequence for virtual terminal sequences */
const std::string ESC{"\x1b"};
// const std::string ESC {"\033"}; // ansi escape code
} // namespace key
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
 * @brief Determines if the number of seconds has elapased since a start time
 *
 * @param start_time the time to count number of seconds from
 * @param duration_secs time period to check has elapsed
 * @return true for the duration having passed since the start time, otherwise false.
 */
bool timeComplete(const std::chrono::time_point<std::chrono::steady_clock> &start_time, const int &duration_secs);


int timeRemainingMins(const std::chrono::time_point<std::chrono::steady_clock> &start_time, const int &duration_mins);

std::string steadyClockToString(const std::chrono::steady_clock::time_point &start_time);

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
bool isValidDeckFileName(const std::string &name);


/**
 * @brief hides or shows the cursor icon in the console
 *
 */
void ShowConsoleCursor(bool showflag);

std::vector<std::vector<int>> readInANSICodes(std::string filename);

std::vector<std::string> convertAsciiArtToLines(const std::string &asciiArt);

std::string getRandomPositiveQuote();

std::string getRandomEncouragingQuote();

std::string getRandomPhrase();


#endif
