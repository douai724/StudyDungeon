#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "flashcard_scene.h" // Include the new flashcard scenes
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

class MainMenuScene : public ConsoleUI::Scene
{
public:
    MainMenuScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> openFibonacciScene,
                  std::function<void()> openEditDecks,
                  std::function<void()> openBrowseDecks)
        : m_uiManager(uiManager)
    {
        auto &menu = m_uiManager.createMenu("main", false);
        menu.addButton("Browse Decks", openBrowseDecks);
        menu.addButton("Edit Decks", openEditDecks);
        menu.addButton("Fibonacci Sequence", openFibonacciScene);
        menu.addButton("Exit", []() {
            clearScreen();
            exit(0);
        });

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
    try
    {


        ConsoleUI::UIManager uiManager;

        std::shared_ptr<MainMenuScene> mainMenuScene;
        std::shared_ptr<FibonacciScene> fibonacciScene;
        std::shared_ptr<FlashcardApp::EditDecksScene> editDecksScene;
        std::shared_ptr<FlashcardApp::BrowseDecksScene> browseDecksScene;
        std::shared_ptr<FlashcardApp::FlashcardScene> flashcardScene;
        std::shared_ptr<FlashcardApp::ResultsScene> resultsScene;

        // Create ResultsScene
        resultsScene = std::make_shared<FlashcardApp::ResultsScene>(
            uiManager,
            std::vector<int>{0, 0, 0}, // Initial difficulty count
            [&]() { uiManager.setCurrentScene(mainMenuScene); },
            [&]() { uiManager.setCurrentScene(browseDecksScene); });

        // Create BrowseDecksScene
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
                            [&]() { uiManager.setCurrentScene(browseDecksScene); });
                        uiManager.setCurrentScene(resultsScene);
                    });
                uiManager.setCurrentScene(flashcardScene);
            });

        // Create editDecksScene
        editDecksScene = std::make_shared<FlashcardApp::EditDecksScene>(
            uiManager,
            [&]() { uiManager.setCurrentScene(mainMenuScene); },
            [&](const FlashCardDeck &deck) {
                // this needs to become the editScene
                flashcardScene = std::make_shared<FlashcardApp::FlashcardScene>(
                    uiManager,
                    deck,
                    [&]() { uiManager.setCurrentScene(editDecksScene); },
                    [&](const std::vector<int> &difficultyCount) {
                        resultsScene = std::make_shared<FlashcardApp::ResultsScene>(
                            uiManager,
                            difficultyCount,
                            [&]() { uiManager.setCurrentScene(mainMenuScene); },
                            [&]() { uiManager.setCurrentScene(editDecksScene); });
                        uiManager.setCurrentScene(resultsScene);
                    });
                // replace with editScene
                uiManager.setCurrentScene(flashcardScene);
            });

        // Create FibonacciScene
        fibonacciScene =
            std::make_shared<FibonacciScene>(uiManager, [&]() { uiManager.setCurrentScene(mainMenuScene); });

        // Create MainMenuScene
        mainMenuScene = std::make_shared<MainMenuScene>(
            uiManager,
            [&]() { uiManager.setCurrentScene(fibonacciScene); },
            [&]() { uiManager.setCurrentScene(editDecksScene); },
            [&]() { uiManager.setCurrentScene(browseDecksScene); });

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
                    if (ch == 27)
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
