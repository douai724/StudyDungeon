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
    //m_uiManager.clearAllMenus(); // Clear all menus before creating new ones
    loadDecks();
}

void BrowseDecksScene::loadDecks()
{
    m_decks = loadFlashCardDecks("Decks/");
    m_selectedDeckIndex = 0;
    m_currentPage = 0;
    m_needsRedraw = true;
}

void BrowseDecksScene::init()
{
    // No init needed
}


void BrowseDecksScene::update()
{
    // No continuous updates needed
}

void BrowseDecksScene::setStaticDrawn(bool staticDrawn)
{
    m_staticDrawn = staticDrawn;
}

void BrowseDecksScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        window->drawCenteredText("Browse Decks", 2);
        window->drawText("Use Up/Down to navigate, Enter to select, Escape to go back", 2, window->getSize().Y - 2);
        m_staticDrawn = true;
    }

    if (m_decksNeedReload)
    {
        loadDecks();
        m_needsRedraw = true;
        m_staticDrawn = false;
        m_decksNeedReload = false;
    }

    if (!m_needsRedraw)
        return;

    // Clear the deck list area
    for (int i = 4; i < window->getSize().Y - 2; ++i)
    {
        window->drawText(std::string(window->getSize().X - 4, ' '), 2, i);
    }

    // Draw deck list
    int deckListY = 4;
    window->drawText("Choose a deck below to begin.", 2, deckListY);
    int y_offset = 2; // number of lines before the deck names print
    for (size_t i = 0; i < m_decks.size(); ++i)
    {
        std::string deckText = (i == m_selectedDeckIndex ? "> " : "  ") + m_decks[i].name;
        window->drawText(deckText, 2, deckListY + static_cast<int>(i) + y_offset);
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
            window->drawWrappedText("Q: " + card.question, cardListX, yOffset, window->getSize().X - cardListX - 2);
            window->drawWrappedText("A: " + card.answer, cardListX, yOffset + 1, window->getSize().X - cardListX - 2);
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
                m_currentPage = 0;
                break;
            case _key_down: // Down arrow
                if (m_selectedDeckIndex < m_decks.size() - 1)
                    m_selectedDeckIndex++;
                m_currentPage = 0;
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
                    const auto &selectedDeck = m_decks[m_selectedDeckIndex];
                    if (selectedDeck.cards.empty())
                    {
                        // Display error message if the selected deck is empty
                        m_uiManager.getWindow()->clear();
                        m_uiManager.getWindow()->drawBorder();
                        m_uiManager.getWindow()->drawBox((m_uiManager.getWindow()->getSize().X / 2) - 20,
                                                         (m_uiManager.getWindow()->getSize().Y / 2) - 2,
                                                         40,
                                                         5);
                        m_uiManager.getWindow()->drawCenteredText("Error: Cannot study empty deck.",
                                                                  m_uiManager.getWindow()->getSize().Y / 2);
                        Sleep(1000);
                        m_needsRedraw = true;
                    }
                    else
                    {
                        m_openDeck(selectedDeck);
                    }
                }
                break;
            case _key_esc:
                for (auto &scene : m_uiManager.getScenes())
                {
                    scene->setStaticDrawn(false);
                }
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


/* -------EDIT -------------*/

FlashcardScene::FlashcardScene(ConsoleUI::UIManager &uiManager,
                               const FlashCardDeck &deck,
                               std::function<void()> goBack,
                               std::function<void()> goToDeckSelection,
                               std::function<void(const std::vector<int> &)> showResults,
                               StudySettings &studySettings)
    : m_uiManager(uiManager), m_deck(deck), m_goBack(goBack), m_showResults(showResults), m_needsRedraw(true),
      m_currentCardIndex(0), m_showAnswer(false), m_settings(studySettings)
{

    m_uiManager.clearMenu("difficulty");

    // Menu for the card difficulty
    auto &menu = m_uiManager.createMenu("difficulty", true);
    menu.addButton("Easy", [this]() { selectDifficulty(1); });
    menu.addButton("Medium", [this]() { selectDifficulty(2); });
    menu.addButton("Hard", [this]() { selectDifficulty(3); });

    initializeCardOrder();
}

void FlashcardScene::initializeCardOrder()
{
    size_t numCardsToStudy = min(m_deck.cards.size(), m_settings.getFlashCardLimit());
    m_cardOrder.clear();

    // Separate seen and unseen cards
    std::vector<size_t> unseenCards;
    std::vector<size_t> seenCards;
    for (size_t i = 0; i < numCardsToStudy; ++i)
    {
        if (m_deck.cards[i].n_times_answered == 0)
        {
            unseenCards.push_back(i);
        }
        else
        {
            seenCards.push_back(i);
        }
    }

    // Prioritize unseen cards
    m_cardOrder = unseenCards;

    // Calculate weights for seen cards
    std::vector<double> weights(seenCards.size());
    for (size_t i = 0; i < seenCards.size(); ++i)
    {
        const auto &card = m_deck.cards[seenCards[i]];
        weights[i] = (4 - card.difficulty) * (1 + log(card.n_times_answered + 1));
    }

    // Normalize weights to create probability distribution
    double sum = std::accumulate(weights.begin(), weights.end(), 0.0);
    for (auto &weight : weights)
    {
        weight /= sum;
    }

    // Create discrete_distribution based on weights
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    // Shuffle seen cards based on probability distribution
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(seenCards.begin(), seenCards.end(), std::default_random_engine(g));
    std::sort(seenCards.begin(), seenCards.end(), [&](size_t a, size_t b) { return weights[a] > weights[b]; });

    // Append seen cards to the card order
    m_cardOrder.insert(m_cardOrder.end(), seenCards.begin(), seenCards.end());
}

void FlashcardScene::update()
{
    // No continuous updates needed
}

void FlashcardScene::init()
{
    // No init needed
}

void FlashcardScene::setStaticDrawn(bool staticDrawn)
{
    m_staticDrawn = staticDrawn;
}

void FlashcardScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    m_settings.startSession();
    if (!m_needsRedraw)
        return;

    window->clear();
    window->drawBorder();
    window->drawBox((window->getSize().X / 2) - 22, 6, 44, 7);

    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        m_staticDrawn = true;
    }

    if (!m_needsRedraw)
        return;

    int textBoxSize = 40;
    // Clear the question area
    for (int i = 7; i < 14; ++i)
    {
        window->drawText(std::string(window->getSize().X - 4, ' '), 2, i);
    }

    if (m_currentCardIndex < m_cardOrder.size())
    {
        const auto &card = m_deck.cards[m_cardOrder[m_currentCardIndex]];
        window->drawCenteredText("Question:", 4);
        window->drawWrappedText(card.question, (window->getSize().X / 2) - 20, 8, 40);
        window->drawText("Time remaining: " + std::to_string(m_settings.getStudyDurationMin()) + "min",
                         2,
                         window->getSize().Y - 4);

        if (m_showAnswer)
        {
            // Clear the answer area
            for (int i = (window->getSize().Y / 2); i < (window->getSize().Y / 2) + 7; ++i)
            {
                window->drawText(std::string(window->getSize().X - 4, ' '), 2, i);
            }
            window->drawCenteredText("Answer:", window->getSize().Y / 2 - 3);
            window->drawWrappedText(card.answer,
                                    (window->getSize().X / 2 - (textBoxSize / 2)),
                                    window->getSize().Y / 2,
                                    textBoxSize);

            auto &menu = m_uiManager.getMenu("difficulty");

            // Calculate total width manually
            int totalWidth = 0;
            for (size_t i = 0; i < menu.getButtonCount(); ++i)
            {
                totalWidth += menu.getButtonWidth(i) + 2;
            }
            totalWidth -= 2; // Remove extra spacing after last button
            int menuX = (window->getSize().X - totalWidth) / 2;
            menu.draw(menuX, window->getSize().Y * 2 / 3 + 2); // Move the buttons down by 2 lines
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
                for (auto &scene : m_uiManager.getScenes())
                {
                    scene->setStaticDrawn(false);
                }
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
    m_difficultyCount[difficulty - 1]++;
    updateCardDifficulty(m_cardOrder[m_currentCardIndex], static_cast<CardDifficulty>(difficulty));

    for (auto &scene : m_uiManager.getScenes())
    {
        scene->setStaticDrawn(false);
    }


    nextCard();
}

void FlashcardScene::updateCardDifficulty(int cardIndex, CardDifficulty difficulty)
{
    auto &card = m_deck.cards[cardIndex];
    card.difficulty = difficulty;
    card.n_times_answered++;
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
    saveUpdatedDeck();
    m_showResults(m_difficultyCount);
}

void FlashcardScene::saveUpdatedDeck()
{
    writeFlashCardDeckWithChecks(m_deck, m_deck.filename, true);
    m_decksNeedReload = true;
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
    menu.addButton("     Start game?     ", m_goToGame);
    menu.addButton("   Study New Deck?   ", m_goToDeckSelection);
    menu.addButton("  Back to Main Menu  ", m_goToMainMenu);

    if (m_difficultyCount[EASY - 1] > m_difficultyCount[HARD - 1])
    {
        phrase = getRandomPositiveQuote();
    }
    else if (m_difficultyCount[HARD - 1] > m_difficultyCount[EASY - 1])
    {
        phrase = getRandomEncouragingQuote();
    }
    else
    {
        phrase = getRandomEncouragingQuote();
    }
}

void ResultsScene::init()
{
    // No init needed
}

void ResultsScene::update()
{
    // No continuous updates needed
}

void ResultsScene::setStaticDrawn(bool staticDrawn)
{
    m_staticDrawn = staticDrawn;
}

void ResultsScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        m_staticDrawn = true;
    }

    if (!m_needsRedraw)
        return;

    // Clear the results area
    for (int i = window->getSize().Y / 2 - 4; i < window->getSize().Y * 3 / 4; ++i)
    {
        window->drawText(std::string(window->getSize().X - 2, ' '), 1, i);
    }

    window->drawCenteredText(phrase, window->getSize().Y / 2 - 4);
    window->drawCenteredText("Easy: " + std::to_string(m_difficultyCount[EASY - 1]), window->getSize().Y / 2 - 2);
    window->drawCenteredText("Medium: " + std::to_string(m_difficultyCount[MEDIUM - 1]), window->getSize().Y / 2);
    window->drawCenteredText("Hard: " + std::to_string(m_difficultyCount[HARD - 1]), window->getSize().Y / 2 + 2);

    auto &menu = m_uiManager.getMenu("results");
    // Calculate total width manually
    int maxWidth = 0;
    for (size_t i = 0; i < menu.getButtonCount(); ++i)
    {
        maxWidth = max(menu.getButtonWidth(i), maxWidth);
    }
    int menuX = (window->getSize().X - maxWidth) / 2;
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
