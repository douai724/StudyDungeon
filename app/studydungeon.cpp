#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "edit_flashcard.h"
#include "flashcard_scene.h"
#include "game_scene.h"
#include "gameloop.h"
#include "howto_scene.h"
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


class MainMenuScene : public ConsoleUI::Scene
{
public:
    MainMenuScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> openFibonacciScene,
                  std::function<void()> openHowToScene,
                  std::function<void()> openBrowseDecks,
                  std::function<void()> openEditDecks)
        : m_uiManager(uiManager)
    {
        createMainMenu(openFibonacciScene, openHowToScene, openBrowseDecks, openEditDecks);

        // Create ASCII art
        m_asciiArt = m_uiManager.createAsciiArt(R"(

 (`-').->(`-')                _(`-')                   _(`-')              <-. (`-')_            (`-')  _           <-. (`-')_
 ( OO)_  ( OO).->       .->  ( (OO ).->     .->       ( (OO ).->     .->      \( OO) )    .->    ( OO).-/     .->      \( OO) )
(_)--\_) /    '._  ,--.(,--.  \    .'_  ,--.'  ,-.     \    .'_ ,--.(,--.  ,--./ ,--/  ,---(`-')(,------.(`-')----. ,--./ ,--/
/    _ / |'--...__)|  | |(`-')'`'-..__)(`-')'.'  /     '`'-..__)|  | |(`-')|   \ |  | '  .-(OO ) |  .---'( OO).-.  '|   \ |  |
\_..`--. `--.  .--'|  | |(OO )|  |  ' |(OO \    /      |  |  ' ||  | |(OO )|  . '|  |)|  | .-, \(|  '--. ( _) | |  ||  . '|  |)
.-._)   \   |  |   |  | | |  \|  |  / : |  /   /)      |  |  / :|  | | |  \|  |\    | |  | '.(_/ |  .--'  \|  |)|  ||  |\    |
\       /   |  |   \  '-'(_ .'|  '-'  / `-/   /`       |  '-'  /\  '-'(_ .'|  | \   | |  '-'  |  |  `---.  '  '-'  '|  | \   |
 `-----'    `--'    `-----'   `------'    `--'         `------'  `-----'   `--'  `--'  `-----'   `------'   `-----' `--'  `--'

        )");
    }

    void createMainMenu(std::function<void()> openFibonacciScene,
                        std::function<void()> openHowToScene,
                        std::function<void()> openBrowseDecks,
                        std::function<void()> openEditDecks)

    {
        auto &menu = m_uiManager.createMenu("main", false);
        menu.addButton("Begin Study", openBrowseDecks);
        menu.addButton("Edit Decks", openEditDecks);
        menu.addButton("How To Play", openHowToScene);
        menu.addButton("Fibonacci Sequence", openFibonacciScene);
        menu.addButton("Exit", []() {
            clearScreen();
            exit(0);
        });
    }

    void update() override
    {
    }

    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override
    {
        window->clear();
        window->drawBorder();

        int artX = (window->getSize().X - m_asciiArt.getWidth()) / 2;
        window->drawAsciiArt(m_asciiArt.getArt(), artX, 2);

        // Calculate total width of menu buttons
        auto &menu = m_uiManager.getMenu("main");
        int totalMenuWidth = 0;
        for (size_t i = 0; i < menu.getButtonCount(); ++i)
        {
            totalMenuWidth += menu.getButtonWidth(i) + 1; // Add 1 for spacing between buttons
        }
        totalMenuWidth -= 1;

        // Calculate starting X position for centered menu
        int menuX = (window->getSize().X - totalMenuWidth) / 2;
        int menuY = m_asciiArt.getHeight() + 5;

        menu.draw(menuX, menuY);
    }

    void handleInput() override
    {
        m_uiManager.getMenu("main").handleInput();
    }

private:
    ConsoleUI::UIManager &m_uiManager;
    ConsoleUI::AsciiArt m_asciiArt;
};

int main()
{
    // Game settings
    int session_start{};
    int fc_hand_limit{15};
    enableVirtualTerminal();
    try
    {
        ConsoleUI::UIManager uiManager;

        std::shared_ptr<MainMenuScene> mainMenuScene;
        std::shared_ptr<FibonacciScene> fibonacciScene;
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
            [&]() { uiManager.setCurrentScene(mainMenuScene); },
            [&]() { uiManager.setCurrentScene(browseDecksScene); },
            [&]() { uiManager.setCurrentScene(gameScene); });

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
                    [&]() { uiManager.setCurrentScene(howToScene); },
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


        // Create HowToScene
        howToScene = std::make_shared<HowToScene>(uiManager, [&]() { uiManager.setCurrentScene(mainMenuScene); });
        // Create FibonacciScene
        fibonacciScene =
            std::make_shared<FibonacciScene>(uiManager, [&]() { uiManager.setCurrentScene(mainMenuScene); });


        // Create MainMenuScene
        mainMenuScene = std::make_shared<MainMenuScene>(
            uiManager,
            [&]() { uiManager.setCurrentScene(fibonacciScene); },
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
