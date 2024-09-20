/**
 * @file flashcard_scene.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "flashcard_scene.h"
#include "edit_flashcard.h"
#include <algorithm>
#include <conio.h>
#include <numeric>
#include <random>
#include <sstream>

namespace FlashcardApp
{

BrowseDecksScene::BrowseDecksScene(ConsoleUI::UIManager &uiManager,
                                   std::function<void()> goBack,
                                   std::function<void(const FlashCardDeck &)> openDeck)
    : m_uiManager(uiManager), m_goBack(goBack), m_openDeck(openDeck), m_currentPage(0), m_maxCardsPerPage(0)
{
    m_uiManager.clearAllMenus(); // Clear all menus before creating new ones
    loadDecks();
}

void BrowseDecksScene::loadDecks()
{
    m_decks = loadFlashCardDecks("Decks/");
    m_selectedDeckIndex = 0;
    m_currentPage = 0;
    m_needsRedraw = true;
}

void BrowseDecksScene::update()
{
    // No continuous updates needed
}

void BrowseDecksScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_needsRedraw)
        return;

    window->clear();
    window->drawBorder();
    window->drawCenteredText("Browse Decks", 2);

    // Draw deck list
    int deckListY = 4;
    for (size_t i = 0; i < m_decks.size(); ++i)
    {
        std::string deckText = (i == m_selectedDeckIndex ? "> " : "  ") + m_decks[i].name;
        window->drawText(deckText, 2, deckListY + static_cast<int>(i));
    }

    // Draw selected deck contents with paging
    if (!m_decks.empty())
    {
        const auto &selectedDeck = m_decks[m_selectedDeckIndex];
        int cardListX = window->getSize().X / 2;
        int cardListY = 4;
        m_maxCardsPerPage = (window->getSize().Y - cardListY - 5) / 5; // 5 lines per card, leave space for instructions
        int totalPages = (static_cast<int>(selectedDeck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;

        window->drawText("Deck Contents (Page " + std::to_string(m_currentPage + 1) + "/" + std::to_string(totalPages) +
                             "):",
                         cardListX,
                         cardListY - 1);

        for (size_t i = m_currentPage * m_maxCardsPerPage;
             i < min(selectedDeck.cards.size(), (m_currentPage + 1) * m_maxCardsPerPage);
             ++i)
        {
            const auto &card = selectedDeck.cards[i];
            int yOffset = cardListY + (i % m_maxCardsPerPage) * 5;
            drawWrappedText(window, "Q: " + card.question, cardListX, yOffset, window->getSize().X - cardListX - 2);
            drawWrappedText(window, "A: " + card.answer, cardListX, yOffset + 1, window->getSize().X - cardListX - 2);
            window->drawText("D: " + cardDifficultyToStr(card.difficulty), cardListX, yOffset + 2);
            window->drawText("Times answered: " + std::to_string(card.n_times_answered), cardListX + 20, yOffset + 2);
            window->drawText("---", cardListX + 20, yOffset + 3);
        }

        window->drawText("Use Left/Right arrows to change pages", cardListX, window->getSize().Y - 3);
    }

    // Draw instructions
    window->drawText("Up/Down to navigate, Enter to select, Escape to go back", 2, window->getSize().Y - 2);

    m_needsRedraw = false;
}

void BrowseDecksScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();
        bool inputHandled = true;

        if (key == _arrow_prefix || key == _numlock)
        {                   // Arrow key prefix
            key = _getch(); // Get the actual arrow key code
            switch (key)
            {
            case _key_up: // Up arrow
                if (m_selectedDeckIndex > 0)
                    m_selectedDeckIndex--;
                break;
            case _key_down: // Down arrow
                if (m_selectedDeckIndex < m_decks.size() - 1)
                    m_selectedDeckIndex++;
                break;
            case _key_left: // Left arrow
                if (m_currentPage > 0)
                    m_currentPage--;
                break;
            case _key_right: // Right arrow
                if (!m_decks.empty())
                {
                    const auto &selectedDeck = m_decks[m_selectedDeckIndex];
                    int totalPages =
                        (static_cast<int>(selectedDeck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;
                    if (m_currentPage < totalPages - 1)
                        m_currentPage++;
                }
                break;
            default:
                inputHandled = false;
            }
        }
        else
        {
            switch (key)
            {
            case _key_enter: // Enter
                if (!m_decks.empty())
                {
                    m_openDeck(m_decks[m_selectedDeckIndex]);
                }
                break;
            case _key_esc:
                m_goBack();
                break;
            default:
                inputHandled = false;
            }
        }

        if (inputHandled)
        {
            m_needsRedraw = true;
        }
    }
}

// Helper function to draw wrapped text
void BrowseDecksScene::drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                                       const std::string &text,
                                       int x,
                                       int y,
                                       int width)
{
    std::istringstream words(text);
    std::string word;
    std::string line;
    int currentY = y;

    while (words >> word)
    {
        if (line.length() + word.length() + 1 > width)
        {
            window->drawText(line, x, currentY++);
            line = word + " ";
        }
        else
        {
            line += word + " ";
        }
    }

    if (!line.empty())
    {
        window->drawText(line, x, currentY);
    }
}

/* -------EDIT -------------*/


/* ---------------- */

FlashcardScene::FlashcardScene(ConsoleUI::UIManager &uiManager,
                               const FlashCardDeck &deck,
                               std::function<void()> goBack,
                               std::function<void(const std::vector<int> &)> showResults)
    : m_uiManager(uiManager), m_deck(deck), m_goBack(goBack), m_showResults(showResults), m_needsRedraw(true),
      m_currentCardIndex(0), m_showAnswer(false)
{

    m_uiManager.clearMenu("difficulty");

    // Menu for the card difficulty
    auto &menu = m_uiManager.createMenu("difficulty", true);
    menu.addButton("Easy", [this]() { selectDifficulty(0); });
    menu.addButton("Medium", [this]() { selectDifficulty(1); });
    menu.addButton("Hard", [this]() { selectDifficulty(2); });

    // Initialize card order
    m_cardOrder.resize(m_deck.cards.size());
    std::iota(m_cardOrder.begin(), m_cardOrder.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_cardOrder.begin(), m_cardOrder.end(), g);
}

void FlashcardScene::update()
{
    // No continuous updates needed
}

void FlashcardScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_needsRedraw)
        return;

    window->clear();
    window->drawBorder();

    if (m_currentCardIndex < m_cardOrder.size())
    {
        const auto &card = m_deck.cards[m_cardOrder[m_currentCardIndex]];
        window->drawCenteredText("Question:", 4);
        drawWrappedText(window, card.question, 2, 6, window->getSize().X - 4);

        if (m_showAnswer)
        {
            window->drawCenteredText("Answer:", window->getSize().Y / 2 - 1);
            drawWrappedText(window, card.answer, 2, window->getSize().Y / 2 + 1, window->getSize().X - 4);
            auto &menu = m_uiManager.getMenu("difficulty");

            // Calculate total width manually
            int totalWidth = 0;
            for (size_t i = 0; i < menu.getButtonCount(); ++i)
            {
                totalWidth += menu.getButtonWidth(i) + 1; // Add 1 for spacing
            }
            totalWidth -= 1; // Remove extra spacing after last button
            int menuX = (window->getSize().X - totalWidth) / 2;
            menu.draw(menuX, window->getSize().Y * 2 / 3);
            window->drawText("Use arrow keys to select difficulty, Enter to confirm", 2, window->getSize().Y - 2);
        }
        else
        {
            window->drawCenteredText("Press SPACE to show answer", window->getSize().Y * 2 / 3);
        }

        std::string progress =
            "Card " + std::to_string(m_currentCardIndex + 1) + " of " + std::to_string(m_cardOrder.size());
        window->drawText(progress, 2, window->getSize().Y - 3);
    }
    else
    {
        window->drawCenteredText("All cards reviewed!", window->getSize().Y / 2);
    }

    m_needsRedraw = false;
}

void FlashcardScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();
        bool inputHandled = true;

        if (key == _arrow_prefix || key == _numlock)
        {                   // Arrow key prefix
            key = _getch(); // Get the actual arrow key code
            if (m_showAnswer)
            {
                auto &menu = m_uiManager.getMenu("difficulty");
                switch (key)
                {
                case _key_left: // Left arrow
                    menu.selectPreviousButton();
                    break;
                case _key_right: // Right arrow
                    menu.selectNextButton();
                    break;
                default:
                    inputHandled = false;
                }
            }
            else
            {
                inputHandled = false;
            }
        }
        else
        {
            switch (key)
            {
            case _key_space: // Spacebar
                if (!m_showAnswer)
                {
                    m_showAnswer = true;
                }
                break;
            case _key_enter: // Enter
                if (m_showAnswer)
                {
                    auto &menu = m_uiManager.getMenu("difficulty");
                    menu.activateSelectedButton();
                }
                break;
            case _key_esc: // Escape key
                endSession();
                break;
            default:
                inputHandled = false;
            }
        }

        if (inputHandled)
        {
            m_needsRedraw = true;
        }
    }
}

void FlashcardScene::selectDifficulty(int difficulty)
{
    m_difficultyCount[difficulty]++;
    nextCard();
}

void FlashcardScene::nextCard()
{
    m_currentCardIndex++;
    m_showAnswer = false;
    m_needsRedraw = true;
    if (m_currentCardIndex >= m_cardOrder.size())
    {
        endSession();
    }
}

void FlashcardScene::endSession()
{
    m_showResults(m_difficultyCount);
}

// Helper function to draw wrapped text
void FlashcardScene::drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                                     const std::string &text,
                                     int x,
                                     int y,
                                     int width)
{
    std::istringstream words(text);
    std::string word;
    std::string line;
    int currentY = y;

    while (words >> word)
    {
        if (line.length() + word.length() + 1 > width)
        {
            window->drawText(line, x, currentY++);
            line = word + " ";
        }
        else
        {
            line += word + " ";
        }
    }

    if (!line.empty())
    {
        window->drawText(line, x, currentY);
    }
}

ResultsScene::ResultsScene(ConsoleUI::UIManager &uiManager,
                           const std::vector<int> &difficultyCount,
                           std::function<void()> goToMainMenu,
                           std::function<void()> goToDeckSelection,
                           std::function<void()> goToGame)
    : m_uiManager(uiManager), m_difficultyCount(difficultyCount), m_goToMainMenu(goToMainMenu),
      m_goToDeckSelection(goToDeckSelection), m_goToGame(goToGame), m_needsRedraw(true)
{
    m_uiManager.clearMenu("results");
    auto &menu = m_uiManager.createMenu("results", false);
    menu.addButton("Main Menu", m_goToMainMenu);
    menu.addButton("Deck Selection", m_goToDeckSelection);
    menu.addButton("Start game", m_goToGame);
}

void ResultsScene::update()
{
    // No continuous updates needed
}

void ResultsScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_needsRedraw)
        return;

    window->clear();
    window->drawBorder();
    window->drawCenteredText("Results", 2);

    window->drawCenteredText("Easy: " + std::to_string(m_difficultyCount[0]), window->getSize().Y / 2 - 2);
    window->drawCenteredText("Medium: " + std::to_string(m_difficultyCount[1]), window->getSize().Y / 2);
    window->drawCenteredText("Hard: " + std::to_string(m_difficultyCount[2]), window->getSize().Y / 2 + 2);

    auto &menu = m_uiManager.getMenu("results");
    // Calculate total width manually
    int totalWidth = 0;
    for (size_t i = 0; i < menu.getButtonCount(); ++i)
    {
        totalWidth += menu.getButtonWidth(i) + 1; // Add 1 for spacing
    }
    totalWidth -= 1; // Remove extra spacing after last button
    int menuX = (window->getSize().X - totalWidth) / 2;
    menu.draw(menuX, window->getSize().Y * 3 / 4);

    m_needsRedraw = false;
}

void ResultsScene::handleInput()
{
    if (_kbhit())
    {
        m_uiManager.getMenu("results").handleInput();
        m_needsRedraw = true;
    }
}

} // namespace FlashcardApp
