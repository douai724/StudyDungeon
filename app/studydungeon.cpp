#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "edit_flashcard.h"
#include "flashcard_scene.h"
#include "game_scene.h"
#include "gameloop.h"
#include "howto_scene.h"
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


class MainMenuScene : public ConsoleUI::Scene
{
public:
    void Scene::setStaticDrawn(bool staticDrawn) override
    {
        m_staticDrawn = staticDrawn;
    }

    MainMenuScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> openSettingsScene,
                  std::function<void()> openHowToScene,
                  std::function<void()> openBrowseDecks,
                  std::function<void()> openEditDecks)
        : m_uiManager(uiManager), m_needsRedraw(true)
    {
        createMainMenu(openSettingsScene, openHowToScene, openBrowseDecks, openEditDecks);

        // Create ASCII art and add it to the console window
        std::string asciiArtString = R"(
(`-').->(`-')                _(`-')                   _(`-')              <-. (`-')_            (`-')  _           <-. (`-')_
( OO)_  ( OO).->       .->  ( (OO ).->     .->       ( (OO ).->     .->      \( OO) )    .->    ( OO).-/     .->      \( OO) )
(_)--\_) /    '._  ,--.(,--.  \    .'_  ,--.'  ,-.     \    .'_ ,--.(,--.  ,--./ ,--/  ,---(`-')(,------.(`-')----. ,--./ ,--/
/    _ / |'--...__)|  | |(`-')'`'-..__)(`-')'.'  /     '`'-..__)|  | |(`-')|   \ |  | '  .-(OO ) |  .---'( OO).-.  '|   \ |  |
\_..`--. `--.  .--'|  | |(OO )|  |  ' |(OO \    /      |  |  ' ||  | |(OO )|  . '|  |)|  | .-, \(|  '--. ( _) | |  ||  . '|  |)
.-._)   \   |  |   |  | | |  \|  |  / : |  /   /)      |  |  / :|  | | |  \|  |\    | |  | '.(_/ |  .--'  \|  |)|  ||  |\    |
\       /   |  |   \  '-'(_ .'|  '-'  / `-/   /`       |  '-'  /\  '-'(_ .'|  | \   | |  '-'  |  |  `---.  '  '-'  '|  | \   |
`-----'    `--'    `-----'   `------'    `--'         `------'  `-----'   `--'  `--'  `-----'   `------'   `-----' `--'  `--'
)";
        std::string asciiArtString2 = R"(
                                     /|
                                    |\|
                                    |||
                                    |||
                                    |||
                                    |||
                                    |||
                                    |||
                                 ~-[{o}]-~
                                    |/|
             ___                    |/|
            ///~`     |\\_          `0'         =\\\\         . .
           ,  |='  ,))\_| ~-_                    _)  \      _/_/|
          / ,' ,;((((((    ~ \                  `~~~\-~-_ /~ (_/\
        /' -~/~)))))))'\_   _/'                      \_  /'  D   |
       (       (((((( ~-/ ~-/                          ~-;  /    \--_
        ~~--|   ))''    ')  `                            `~~\_    \  )
            :        (_  ~\           ,                    /~~-      /
             \        \_   )--__  /(_/)                   |    )    )|
     _       |_     \__/~-__    ~~   ,'      /,_;,   __--(   _/      |
    ~\`\    /' ~~~----|     ~~~~~~~~'        \-  ((~~    __-~        |
    ()  `\`\_(_     _-~~-\                      ``~~ ~~~~~~   \_     /
          ----'   /      \                                   )      )
           ;`~--'        :                                _-    ,;;(
           |    `\       |                             _-~    ,;;;;)
           |    /'`\     ;                          _-~          _/
          /~   /    |    )                         /;;;''  ,;;:-~
         |    /     / | /                         |;;'   ,''
         /   /     |  \\|                         |   ,;(
       _/  /'       \  \_)                   .---__\_    \,--.______
      ( )|'         (~-_|                   (;;'  ;;;~~~/' `;;|  `;;\
       ) `\_         |-_;;--__               ~~~----__/'    /'______/
       `----'       (   `~--_ ~~~;;------------~~~~~ ;;;'_/'
                    `~~~~~~~~'~~~-----....___;;;____---~~
    )";

        ConsoleUI::ANSIArt title = ConsoleUI::ANSIArt(readInANSICodes("STUDY_DUNGEON.txt"), "title", 0, 0);
        m_uiManager.getWindow()->addANSIArt(title);

        ConsoleUI::ANSIArt card = ConsoleUI::ANSIArt(readInANSICodes("CARD.txt"), "card", 0, 0);
        m_uiManager.getWindow()->addANSIArt(card);

        ConsoleUI::ANSIArt cardSelected =
            ConsoleUI::ANSIArt(readInANSICodes("CARD_SELECTED.txt"), "cardSelected", 0, 0);
        m_uiManager.getWindow()->addANSIArt(cardSelected);

        ConsoleUI::ANSIArt heart = ConsoleUI::ANSIArt(readInANSICodes("HEART.txt"), "heart", 0, 0);
        m_uiManager.getWindow()->addANSIArt(heart);

        ConsoleUI::ANSIArt heartEmpty = ConsoleUI::ANSIArt(readInANSICodes("HEART_EMPTY.txt"), "heartEmpty", 0, 0);
        m_uiManager.getWindow()->addANSIArt(heartEmpty);

        ConsoleUI::ANSIArt frog = ConsoleUI::ANSIArt(readInANSICodes("SLIME.txt"), "frog", 0, 0);
        m_uiManager.getWindow()->addANSIArt(frog);

        std::vector<std::string> artLines = convertAsciiArtToLines(asciiArtString);
        std::vector<std::string> artLines2 = convertAsciiArtToLines(asciiArtString2);
        ConsoleUI::AsciiArt asciiArt("main_menu", artLines, 0, 0);
        ConsoleUI::AsciiArt asciiArt2("other_menu", artLines2, 0, 0);
        m_uiManager.getWindow()->addAsciiArt(asciiArt);
        m_uiManager.getWindow()->addAsciiArt(asciiArt2);
    }

    void createMainMenu(std::function<void()> openSettingsScene,
                        std::function<void()> openHowToScene,
                        std::function<void()> openBrowseDecks,
                        std::function<void()> openEditDecks)

    {
        m_uiManager.clearMenu("main");
        auto &menu = m_uiManager.createMenu("main", false);
        menu.addButton("   Begin Study   ", openBrowseDecks);
        menu.addButton("   Edit Decks    ", openEditDecks);
        menu.addButton("   How To Play   ", openHowToScene);
        menu.addButton("    Settings     ", openSettingsScene);
        menu.addButton("      Exit       ", []() {
            clearScreen();
            exit(0);
        });
    }

    void init() override
    {
    }

    void update() override
    {
    }

    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override
    {
        if (!m_staticDrawn)
        {
            window->clear();
            window->drawBorder();

            // Draw the ASCII art
            int otherMenuArtX =
                ((window->getSize().X - static_cast<int>(window->getAsciiArtByName("other_menu")->getWidth())) / 2) - 3;
            int otherMenuArtY =
                window->getSize().Y - static_cast<int>(window->getAsciiArtByName("other_menu")->getHeight());
            int mainMenuArtX =
                (window->getSize().X - static_cast<int>(window->getANSIArtByName("title")->getWidth())) / 8;
            int mainMenuArtY = 10;

            window->drawAsciiArt("other_menu", otherMenuArtX, otherMenuArtY);
            //window->drawAsciiArt("main_menu", mainMenuArtX, mainMenuArtY);
            window->drawANSIArt("title", mainMenuArtX, mainMenuArtY - 10);

            m_staticDrawn = true;
        }

        if (!m_needsRedraw)
        {
            return;
        }

        // Clear only the menu area
        auto &menu = m_uiManager.getMenu("main");
        int menuX = (window->getSize().X - static_cast<int>(menu.getMaxWidth()) / 2);
        int menuY = 20;
        size_t menuWidth = menu.getMaxWidth() - 1;
        size_t menuHeight = menu.getButtonCount();

        // Draw a filled box to clear the menu area
        for (int i = menuY - 1; i < menuY + static_cast<int>(menuHeight) + 1; ++i)
        {
            window->drawText(std::string(menuWidth + 2, ' '), menuX - 1, i);
        }

        // Draw the menu
        menu.draw(menuX, menuY);

        m_needsRedraw = false;
    }

    void handleInput() override
    {
        m_uiManager.getMenu("main").handleInput();
        m_needsRedraw = true;
    }

private:
    ConsoleUI::UIManager &m_uiManager;
    bool m_needsRedraw;
    bool m_staticDrawn = false;
};

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
                        [&]() { uiManager.setCurrentScene(browseDecksScene); },
                        [&](const std::vector<int> &difficultyCount) {
                            resultsScene = std::make_shared<FlashcardApp::ResultsScene>(
                                uiManager,
                                difficultyCount,
                                [&]() { uiManager.setCurrentScene(mainMenuScene); },
                                [&]() { uiManager.setCurrentScene(browseDecksScene); },
                                [&]() { uiManager.setCurrentScene(gameScene); });
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
                //     if (ch == _key_esc)
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
