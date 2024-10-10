#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "edit_flashcard.h"
#include "flashcard_scene.h"
#include "game_scene.h"
#include "gameloop.h"
#include "howto_scene.h"
#include "mainmenu_scene.h"
#include "menu.h"
#include "settings_scene.h"
#include "util.h"
#include <conio.h>
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>


int main()
{
    // Game settings
    StudySettings studySettings;
    enableVirtualTerminal();
    ShowConsoleCursor(false);
    try
    {
        ConsoleUI::UIManager uiManager;

        std::shared_ptr<MainMenuScene> mainMenuScene;
        std::shared_ptr<SettingsScene> settingsScene;
        std::shared_ptr<HowToScene> howToScene;
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
            0,
            [&]() { uiManager.setCurrentScene(mainMenuScene); },
            [&]() { uiManager.setCurrentScene(browseDecksScene); },
            [&]() { uiManager.setCurrentScene(gameScene); },
            false); // Pass false for the initial ResultsScene

        // Create BrowseDecksScene
        auto createBrowseDecksScene = [&]() {
            browseDecksScene = std::make_shared<FlashcardApp::BrowseDecksScene>(
                uiManager,
                [&]() { uiManager.setCurrentScene(mainMenuScene); },
                [&](const FlashCardDeck &deck) {
                    flashcardScene = std::make_shared<FlashcardApp::FlashcardScene>(
                        uiManager,
                        deck,
                        [&]() { uiManager.setCurrentScene(browseDecksScene); },
                        [&]() { uiManager.setCurrentScene(browseDecksScene); },
                        [&](const std::vector<int> &difficultyCount, int score, bool sessionComplete) {
                            resultsScene = std::make_shared<FlashcardApp::ResultsScene>(
                                uiManager,
                                difficultyCount,
                                score,
                                [&]() { uiManager.setCurrentScene(mainMenuScene); },
                                [&]() { uiManager.setCurrentScene(browseDecksScene); },
                                [&]() { uiManager.setCurrentScene(gameScene); },
                                sessionComplete); // Pass the sessionCompleted value
                            uiManager.setCurrentScene(resultsScene);
                        },
                        studySettings);
                    flashcardScene->setStaticDrawn(false);
                    uiManager.setCurrentScene(flashcardScene);
                },
                studySettings);
            browseDecksScene->setStaticDrawn(false);
        };

        createBrowseDecksScene(); // Create initial BrowseDecksScene

        // Create editDecksScene
        editDecksScene = std::make_shared<FlashcardEdit::EditDeckScene>(
            uiManager,
            [&]() {
                createBrowseDecksScene();      // Reload BrowseDecksScene when going back from EditDeckScene
                mainMenuScene->createMainMenu( // Recreate main menu buttons
                    [&]() { uiManager.setCurrentScene(settingsScene); },
                    [&]() { uiManager.setCurrentScene(howToScene); },
                    [&]() { uiManager.setCurrentScene(browseDecksScene); },
                    [&]() { uiManager.setCurrentScene(editDecksScene); });
                uiManager.setCurrentScene(mainMenuScene);
            },
            [&](FlashCardDeck &deck) {
                auto editFlashcardScene = std::make_shared<FlashcardEdit::EditFlashcardScene>(
                    uiManager,
                    deck,
                    [&]() { uiManager.setCurrentScene(editDecksScene); },
                    studySettings);
                editFlashcardScene->setStaticDrawn(false); // Add this line
                uiManager.setCurrentScene(editFlashcardScene);
            },
            studySettings);

        // Create HowToScene
        howToScene = std::make_shared<HowToScene>(uiManager, [&]() { uiManager.setCurrentScene(mainMenuScene); });
        // Create SettingsScene
        settingsScene = std::make_shared<SettingsScene>(
            uiManager,
            [&]() { uiManager.setCurrentScene(mainMenuScene); },
            studySettings);


        // Create MainMenuScene
        mainMenuScene = std::make_shared<MainMenuScene>(
            uiManager,
            [&]() { uiManager.setCurrentScene(settingsScene); },
            [&]() { uiManager.setCurrentScene(howToScene); },
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
                uiManager.checkWindowResize();

                // // Check for exit condition (e.g., a specific key press)
                // if (_kbhit())
                // {
                //     int ch = _getch();
                //     if (ch == key::key_esc)
                //     { // ESC key
                //         running = false;
                //     }
                // }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error in game loop: " << e.what() << std::endl;
            }
        }

        //std::cout << "Exiting application..." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
