/**
 * @file util.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "util.h"


namespace fs = std::filesystem;
bool isTestMode = false;

bool enableVirtualTerminal()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return false;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return false;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
        return false;
    return true;
}

/**
 * @brief Get the app path object
 * @fn get the path of the application
 * @return std::filesystem::path The path to the executable
 */
std::filesystem::path getAppPath()
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


bool timeComplete(const std::chrono::time_point<std::chrono::steady_clock> &start_time, const int &duration_secs)
{
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
    return elapsed_time.count() >= duration_secs;
}

int timeRemainingMins(const std::chrono::time_point<std::chrono::steady_clock> &start_time, const int &duration_mins)
{
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::minutes>(current_time - start_time);
    return duration_mins - elapsed_time.count();
}

// Function to convert time_point to a string showing seconds since start
std::string steadyClockToString(const std::chrono::steady_clock::time_point &start_time)
{
    // Get the current time from steady_clock
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();

    // Calculate the duration since the start time in seconds
    int duration_since_start = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);

    // Convert the duration to a string
    std::stringstream ss;
    ss << duration_since_start.count() << " seconds since start";

    return ss.str();
}

void pause()
{
    std::string line;
    std::cout << "Press ENTER to continue..." << std::endl;
    if (!isTestMode)
    {
        std::getline(std::cin, line); // Wait for user input in production
    }
    else
    {
        std::cout << "[Simulated ENTER]" << std::endl; // Simulate "ENTER" press in test mode
    }
}

void clearScreen()
{
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
        return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
        return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

bool yesNoPrompt()
{
    std::string input{};

    while (true)
    {

        std::cout << "Press Y/N to continue...\n" << std::endl;
        std::getline(std::cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        // std::cout << "Input now: " << input << std::endl;
        if (input == "Y")
        {
            return true;
        }
        else if (input == "N")
        {
            return false;
        }
    }
}


bool isValidDeckFileName(std::string name)
{
    int max_length{20};
    if (name == "")
    {
        std::cout << "Name must not be empty" << std::endl;
        return false;
    }
    if (name.length() > max_length)
    {
        std::cout << "'" << name << "' exceeds maximum length of " << max_length << " characters." << std::endl;
        return false;
    }

    // check to see if ASCII value is outside of alphanumeric range
    for (char c : name)
    {
        if (!(('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || (('a' <= c && c <= 'z'))))
        {
            std::cout << "'" << name << "' contains non-alphanumeric characters" << std::endl;
            return false;
        }
    }
    return true;
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

std::string convertFileToANSI(std::string filename)
{
    fs::path path = getAppPath().append("artwork").append(filename);
    std::cout << path << std::endl;
    std::ifstream inputBuffer{path};
    std::string inputLine{};
    std::string img = "";

    while (std::getline(inputBuffer, inputLine))
    {
        std::string curr;
        std::vector<std::string> row;
        std::stringstream ss;
        ss << inputLine;

        while (ss >> curr)
        {
            img += _ESC + "[48;5;" + curr + "m  " + _ESC + "[0m";
        }
        img += "\n";
    }
    return img;
}

std::vector<std::string> convertAsciiArtToLines(const std::string &asciiArt)
{
    std::vector<std::string> lines;
    std::istringstream iss(asciiArt);
    std::string line;

    while (std::getline(iss, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::string getRandomPositiveQuote()
{
    std::vector<std::pair<std::string, int>> phrases = {{"You're on fire!", 20},
                                                        {"Brilliant work!", 20},
                                                        {"Nailed it!", 15},
                                                        {"You're a pro!", 15},
                                                        {"Impressive!", 10},
                                                        {"You're crushing it", 8},
                                                        {"Stellar job!", 6},
                                                        {"You're a genius!", 4},
                                                        {"Unstoppable!", 2}};

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> weights;
    for (const auto &pair : phrases)
    {
        weights.push_back(pair.second);
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());

    return phrases[dist(gen)].first;
}

std::string getRandomEncouragingQuote()
{
    std::vector<std::pair<std::string, int>> phrases = {{"Keep going!", 20},
                                                        {"Don't give up!", 20},
                                                        {"You can do it!", 15},
                                                        {"Stay strong!", 15},
                                                        {"Almost there!", 10},
                                                        {"Believe in you!", 8},
                                                        {"Take a breath!", 6},
                                                        {"Progress counts!", 4},
                                                        {"Every try helps!", 2}};

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> weights;
    for (const auto &pair : phrases)
    {
        weights.push_back(pair.second);
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());

    return phrases[dist(gen)].first;
}

std::string getRandomPhrase()
{
    std::vector<std::pair<std::string, int>> phrases = {{"Farewell, friend", 20},
                                                        {"Until next time", 20},
                                                        {"You got this!", 15},
                                                        {"Safe travels", 15},
                                                        {"Go away now", 10},
                                                        {"Patience rewards", 8},
                                                        {"Where am I?", 6},
                                                        {"blah blah blah", 4},
                                                        {"I hate my job", 2}};

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> weights;
    for (const auto &pair : phrases)
    {
        weights.push_back(pair.second);
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());

    return phrases[dist(gen)].first;
}
