/**
 * @file main.cpp
 * @brief Main entry point for the Flashcard application.
 * @author Your Name
 * @date 2024-09-22
 */

#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "edit_flashcard.h"
#include "flashcard_scene.h"
#include "game_scene.h"
#include "gameloop.h"
#include "menu.h"
#include "test_scene.h"
#include "util.h"
#include <conio.h>
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>

/**
 * @class MainMenuScene
 * @brief Represents the main menu of the application.
 * 
 * This class manages the main menu interface, including the ASCII art logo
 * and navigation options to different parts of the application.
 */
class MainMenuScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Constructs a MainMenuScene object.
     * @param uiManager Reference to the UIManager for handling UI operations.
     * @param openFibonacciScene Function to open the Fibonacci sequence scene.
     * @param openBrowseDecks Function to open the deck browsing scene.
     * @param openEditDecks Function to open the deck editing scene.
     */
    MainMenuScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> openFibonacciScene,
                  std::function<void()> openBrowseDecks,
                  std::function<void()> openEditDecks);

    /**
     * @brief Creates the main menu with navigation options.
     * @param openFibonacciScene Function to open the Fibonacci sequence scene.
     * @param openBrowseDecks Function to open the deck browsing scene.
     * @param openEditDecks Function to open the deck editing scene.
     */
    void createMainMenu(std::function<void()> openFibonacciScene,
                        std::function<void()> openBrowseDecks,
                        std::function<void()> openEditDecks);

    /**
     * @brief Updates the scene state (currently empty).
     */
    void update() override;

    /**
     * @brief Renders the main menu scene.
     * @param window Shared pointer to the ConsoleWindow to render on.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handles user input for the main menu.
     */
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    ConsoleUI::AsciiArt m_asciiArt;    ///< ASCII art logo for the main menu.
};

/**
 * @brief Main function and entry point of the application.
 * @return 0 on successful execution, 1 on error.
 */
int main()
{
    try
    {
        ConsoleUI::UIManager uiManager;

        // Declare shared pointers for all scenes
        std::shared_ptr<MainMenuScene> mainMenuScene;
        std::shared_ptr<FibonacciScene> fibonacciScene;
        std::shared_ptr<FlashcardEdit::EditDeckScene> editDecksScene;
        std::shared_ptr<FlashcardApp::BrowseDecksScene> browseDecksScene;
        std::shared_ptr<FlashcardApp::FlashcardScene> flashcardScene;
        std::shared_ptr<FlashcardApp::ResultsScene> resultsScene;
        std::shared_ptr<GameScene> gameScene;

        // Create GameScene
        gameScene = std::make_shared<GameScene>(uiManager, [&]() { uiManager.setCurrentScene(mainMenuScene); });

        // Create ResultsScene
        resultsScene = std::make_shared<FlashcardApp::ResultsScene>(
            uiManager,
            std::vector<int>{0, 0, 0}, // Initial difficulty count
            [&]() { uiManager.setCurrentScene(mainMenuScene); },
            [&]() { uiManager.setCurrentScene(browseDecksScene); },
            [&]() { uiManager.setCurrentScene(gameScene); });

        // Lambda function to create BrowseDecksScene
        auto createBrowseDecksScene = [&]() {
            browseDecksScene = std::make_shared<FlashcardApp::BrowseDecksScene>(
                uiManager,
                [&]() { uiManager.setCurrentScene(mainMenuScene); },
                [&](const FlashCardDeck &deck) {
                    flashcardScene = std::make_shared<FlashcardApp::FlashcardScene>(
                        uiManager,
                        deck,
                        [&]() { uiManager.setCurrentScene(browseDecksScene); },
                        [&](const std::vector<int> &difficultyCount) {
                            resultsScene = std::make_shared<FlashcardApp::ResultsScene>(
                                uiManager,
                                difficultyCount,
                                [&]() { uiManager.setCurrentScene(mainMenuScene); },
                                [&]() { uiManager.setCurrentScene(browseDecksScene); },
                                [&]() { uiManager.setCurrentScene(gameScene); });
                            uiManager.setCurrentScene(resultsScene);
                        });
                    uiManager.setCurrentScene(flashcardScene);
                });
        };

        createBrowseDecksScene(); // Create initial BrowseDecksScene

        // Create editDecksScene
        editDecksScene = std::make_shared<FlashcardEdit::EditDeckScene>(
            uiManager,
            [&]() {
                createBrowseDecksScene();      // Reload BrowseDecksScene when going back from EditDeckScene
                mainMenuScene->createMainMenu( // Recreate main menu buttons
                    [&]() { uiManager.setCurrentScene(fibonacciScene); },
                    [&]() { uiManager.setCurrentScene(browseDecksScene); },
                    [&]() { uiManager.setCurrentScene(editDecksScene); });
                uiManager.setCurrentScene(mainMenuScene);
            },
            [&](FlashCardDeck &deck) {
                auto editFlashcardScene = std::make_shared<FlashcardEdit::EditFlashcardScene>(uiManager, deck, [&]() {
                    uiManager.setCurrentScene(editDecksScene);
                });
                uiManager.setCurrentScene(editFlashcardScene);
            });

        // Create FibonacciScene
        fibonacciScene =
            std::make_shared<FibonacciScene>(uiManager, [&]() { uiManager.setCurrentScene(mainMenuScene); });

        // Create MainMenuScene
        mainMenuScene = std::make_shared<MainMenuScene>(
            uiManager,
            [&]() { uiManager.setCurrentScene(fibonacciScene); },
            [&]() { uiManager.setCurrentScene(browseDecksScene); },
            [&]() { uiManager.setCurrentScene(editDecksScene); });

        // Set initial scene
        uiManager.setCurrentScene(mainMenuScene);

        // Main game loop
        bool running = true;
        while (running)
        {
            try
            {
                uiManager.update();
                uiManager.render();
                uiManager.handleInput();

                // Check for exit condition (e.g., a specific key press)
                if (_kbhit())
                {
                    int ch = _getch();
                    if (ch == _key_esc)
                    { // ESC key
                        running = false;
                    }
                }

                Sleep(10);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error in game loop: " << e.what() << std::endl;
            }
        }

        std::cout << "Exiting application..." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}