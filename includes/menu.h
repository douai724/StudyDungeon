#pragma once


/**
 * DISPLAY FUNCTIONS
 */

// Display the main menu. This is the menu that the user will see when they first launch the game.
void displayMainMenu();

// Display the configuration menu. This is the menu that the user will see when they are configuring the game.
void displayConfigMenu();

// Display the flashcard menu. This is the menu that the user will see when they are studying the flashcards.
void displayFlashcardMenu();

// Display the game menu. This is the menu that the user will see when they are playing the game.
void displayGameMenu();

// Displays for when the user wins or loses the game in phase 2 (initial implementation)
void displayGameOverScreen(); 

/**
 * INPUT FUNCTIONS
 */

/**
 * For user input, allows us to set a max range for a particular config function. This function will 
 * return the user's choice as an integer.
 * @param min The minimum value the user can input.
 * @param max The maximum value the user can input.
 * @return The user's choice as an integer.
 */
int getMainMenuChoice(int min, int max);

// used for clearing any remaining characters in the input.
void clearInputBuffer();


/**
 * SCREEN FUNCTIONS
 */

// Clears the screen. This is used to clear the screen after the user has made a choice. (dont know if we need this)
void clearScreen();


/**
 * MENU NAVIGATION FUNCTIONS
 */

// This function will navigate the user to the configuration menu.
void navigateToConfigMenu();

// This function will navigate the user to the flashcard menu.
void navigateToFlashcardMenu();

// This function will navigate the user to the game menu.
void navigateToGameMenu();

/**
 * UTILITY FUNCTIONS
 */

/**
 * displays error and error type. (will prolly be better in utilities)
 * @param message The message to display to the user.
 */
void displayError(const char* message);

/**
 * CONFIG FUNCTIONS
 */

//TODO

/**
 * FLASHCARD FUNCTIONS
 */

//TODO

/**
 * GAME FUNCTIONS
 */

//TODO

/**
 * ASCII FUNCTIONS
 */

// Display ASCII art above the menu when launching the game. My idea is that the menu changes 
// below but the ASCII art stays the same. At least for now.
void displaySplashScreen();

// Displays for when the user wins or loses the game in phase 2 (initial implementation)
void displayGameOverScreen(); 

// Display ASCII art for the reward level. This will be displayed when the user wins the game.
// Each reward level will have a different ASCII art.
void displayRewardArt(int rewardLevel);

