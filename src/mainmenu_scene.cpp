/**
 * @file mainmenu_scene.cpp
 * @author Green Alligators
 * @brief Class and functions for the main menu scene
 * @version 1.0.0
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mainmenu_scene.h"


void MainMenuScene::setStaticDrawn(bool staticDrawn)
{
    m_staticDrawn = staticDrawn;
}

MainMenuScene::MainMenuScene(ConsoleUI::UIManager &uiManager,
                             std::function<void()> openSettingsScene,
                             std::function<void()> openHowToScene,
                             std::function<void()> openBrowseDecks,
                             std::function<void()> openEditDecks)
    : m_uiManager(uiManager), m_needsRedraw(true)
{
    createMainMenu(openSettingsScene, openHowToScene, openBrowseDecks, openEditDecks);

    ConsoleUI::ANSIArt title = ConsoleUI::ANSIArt(readInANSICodes("STUDY_DUNGEON.txt"), "title", 0, 0);
    m_uiManager.getWindow()->addANSIArt(title);

    ConsoleUI::ANSIArt card = ConsoleUI::ANSIArt(readInANSICodes("CARD.txt"), "card", 0, 0);
    m_uiManager.getWindow()->addANSIArt(card);

    ConsoleUI::ANSIArt cardSelected = ConsoleUI::ANSIArt(readInANSICodes("CARD_SELECTED.txt"), "cardSelected", 0, 0);
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


    std::vector<std::string> shelfFull = convertAsciiArtToLines(bookshelfFull);
    std::vector<std::string> shelf1 = convertAsciiArtToLines(bookshelf1);
    std::vector<std::string> shelf2 = convertAsciiArtToLines(bookshelf2);
    std::vector<std::string> shelf3 = convertAsciiArtToLines(bookshelf3);
    std::vector<std::string> shelf4 = convertAsciiArtToLines(bookshelf4);
    std::vector<std::string> shelf5 = convertAsciiArtToLines(bookshelf5);
    std::vector<std::string> shelf6 = convertAsciiArtToLines(bookshelf6);
    std::vector<std::string> shelf7 = convertAsciiArtToLines(bookshelf7);
    std::vector<std::string> shelf8 = convertAsciiArtToLines(bookshelf8);
    std::vector<std::string> shelf9 = convertAsciiArtToLines(bookshelf9);
    std::vector<std::string> dragonLines = convertAsciiArtToLines(dragon);
    std::vector<std::string> carLines = convertAsciiArtToLines(car);


    ConsoleUI::AsciiArt artShelfFull("bookfull", shelfFull, 0, 0);
    ConsoleUI::AsciiArt artShelf1("book1", shelf1, 0, 0);
    ConsoleUI::AsciiArt artShelf2("book2", shelf2, 0, 0);
    ConsoleUI::AsciiArt artShelf3("book3", shelf3, 0, 0);
    ConsoleUI::AsciiArt artShelf4("book4", shelf4, 0, 0);
    ConsoleUI::AsciiArt artShelf5("book5", shelf5, 0, 0);
    ConsoleUI::AsciiArt artShelf6("book6", shelf6, 0, 0);
    ConsoleUI::AsciiArt artShelf7("book7", shelf7, 0, 0);
    ConsoleUI::AsciiArt artShelf8("book8", shelf8, 0, 0);
    ConsoleUI::AsciiArt artShelf9("book9", shelf9, 0, 0);
    ConsoleUI::AsciiArt artDragon("dragon", dragonLines, 0, 0);
    ConsoleUI::AsciiArt artCar("car", carLines, 0, 0);

    uiManager.getWindow()->addAsciiArt(artShelfFull);
    uiManager.getWindow()->addAsciiArt(artShelf1);
    uiManager.getWindow()->addAsciiArt(artShelf2);
    uiManager.getWindow()->addAsciiArt(artShelf3);
    uiManager.getWindow()->addAsciiArt(artShelf4);
    uiManager.getWindow()->addAsciiArt(artShelf5);
    uiManager.getWindow()->addAsciiArt(artShelf6);
    uiManager.getWindow()->addAsciiArt(artShelf7);
    uiManager.getWindow()->addAsciiArt(artShelf8);
    uiManager.getWindow()->addAsciiArt(artShelf9);
    uiManager.getWindow()->addAsciiArt(artDragon);
    uiManager.getWindow()->addAsciiArt(artCar);

    std::vector<std::string> librarianLines = convertAsciiArtToLines(librarian);
    std::vector<std::string> librarianPointingLines = convertAsciiArtToLines(librarianPointing);
    ConsoleUI::AsciiArt librarianArt("lib1", librarianLines, 0, 0);
    ConsoleUI::AsciiArt librarianArt2("lib2", librarianPointingLines, 0, 0);


    uiManager.getWindow()->addAsciiArt(librarianArt);
    uiManager.getWindow()->addAsciiArt(librarianArt2);
}

void MainMenuScene::createMainMenu(std::function<void()> openSettingsScene,
                                   std::function<void()> openHowToScene,
                                   std::function<void()> openBrowseDecks,
                                   std::function<void()> openEditDecks)

{
    m_uiManager.clearMenu("main");
    auto &menu = m_uiManager.createMenu("main", false);
    menu.addButton("   Begin Study   ", openBrowseDecks);
    menu.addButton("    Edit Decks   ", openEditDecks);
    menu.addButton("     Settings    ", openSettingsScene);
    menu.addButton("  About Program  ", openHowToScene);
    menu.addButton("   Exit Program  ", []() {
        clearScreen();
        exit(0);
    });
}

void MainMenuScene::init()
{
}

void MainMenuScene::update()
{
}

void MainMenuScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        COORD size = window->getSize();

        // Draw the ASCII art
        int otherMenuArtX =
            ((window->getSize().X - static_cast<int>(window->getAsciiArtByName("other_menu")->getWidth())) / 2) - 5;
        int otherMenuArtY =
            (window->getSize().Y - 2) - static_cast<int>(window->getAsciiArtByName("other_menu")->getHeight());

        window->drawAsciiArt("other_menu", otherMenuArtX, otherMenuArtY);
        window->drawAsciiArt("car", window->getSize().X - 35, window->getSize().Y - 5);
        window->drawANSIArt("title", (size.X - (window->getANSIArtByName("title")->getWidth() * 2)) / 2, 5);


        m_staticDrawn = true;
    }

    if (!m_needsRedraw)
    {
        return;
    }

    // Clear only the menu area
    auto &menu = m_uiManager.getMenu("main");
    int menuX = (window->getSize().X - static_cast<int>(menu.getMaxWidth())) / 2;
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

void MainMenuScene::handleInput()
{
    m_uiManager.getMenu("main").handleInput();
    m_needsRedraw = true;
}
