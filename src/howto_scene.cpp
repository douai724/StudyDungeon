/**
 * @file howto_scene.cpp
 * @author Green Alligators
 * @brief Defines the UI scene for the howto scene explaining how the program works
 * @version 1.0.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "howto_scene.h"


HowToScene::HowToScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack)
    : m_uiManager(uiManager), m_goBack(goBack)
{
    auto &menu = m_uiManager.createMenu("howto", true); // Horizontal menu
    menu.addButton("Back", [this]() { m_goBack(); });
}

void HowToScene::init()
{
    // No need for init
}

void HowToScene::update()
{
    // No continuous updates needed for this scene
}

void HowToScene::setStaticDrawn(bool staticDrawn)
{
    m_staticDrawn = staticDrawn;
}


void HowToScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    window->clear();
    window->drawBorder();
    window->drawCenteredText("How to Play", 2);

    const std::string howto_text = R"(StudyDungeon is a Flashcard program to aid in study
Flashcard decks are stored in `Decks/` and are loaded in upon lauching the program.

Once inside the program, you can start a study session by selecting _Begin Study_.
This will then allow you to choose your starting deck to revise flashcards from.
Alternatively, you can add, edit, or remove decks through the _Edit Decks_ menu.


A study session has 2 phases:

1. Flashcard revision
   - You will go through as many rounds of flashcard revision as you like.
     Each card that you answer correctly will influence the cards available to you in
     the study break card duel game.
2. Study Break Card Duel
   - A card duel game to play as a study break. The more cards you answer correctly from
     the flashcard revision, the better your playing cards will be in the card duel.)";

    std::istringstream stream(howto_text);
    std::string line;
    int y_start{4};
    const int x_start = window->getSize().X / 2 - 45; // longest line above is ~90 characters, so center by /2
    while (std::getline(stream, line))
    {
        window->drawText(line, x_start, y_start);
        y_start++;
    }
    window->drawText("Editing disclaimers:", 3, window->getSize().Y - 12);
    window->drawWrappedText("- when adding/editing text for a flashcard, you are limited to 90 characters",
                            3,
                            window->getSize().Y - 10,
                            40);
    window->drawWrappedText("- when adding/renaming text for a deck, you are limited to 30 characters",
                            3,
                            window->getSize().Y - 7,
                            40);

    window->drawText("Credits:", window->getSize().X - 30, window->getSize().Y - 12);
    window->drawWrappedText("Ascii art from: https://www.asciiart.eu/",
                            window->getSize().X - 30,
                            window->getSize().Y - 10,
                            27);
    window->drawWrappedText("Pixel art by: ", window->getSize().X - 30, window->getSize().Y - 8, 27);


    window->drawCenteredText("Playing the Game", window->getSize().Y / 2 - 2);


    // Draw the menu at the bottom center of the screen
    auto windowSize = window->getSize();
    m_uiManager.getMenu("howto").draw((windowSize.X) / 2 - 4, windowSize.Y - 7); // Adjust 30 based on your menu width
    window->drawText("Press ENTER to go back", windowSize.X / 2 - 11, windowSize.Y - 5);
}

void HowToScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();

        if (key == key::key_esc)
        {
            m_goBack();
        }
    }

    m_uiManager.getMenu("howto").handleInput();
}
