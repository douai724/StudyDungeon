/**
 * @file flashcard_scene.cpp
 * @author Green Alligators
 * @brief Functions used for the flashcard study scene
 * @version 1.0.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "flashcard_scene.h"


namespace FlashcardApp
{

BrowseDecksScene::BrowseDecksScene(ConsoleUI::UIManager &uiManager,
                                   std::function<void()> goBack,
                                   std::function<void(const FlashCardDeck &)> openDeck,
                                   StudySettings &studySettings)
    : m_uiManager(uiManager), m_goBack(goBack), m_openDeck(openDeck), m_currentPage(0), m_maxCardsPerPage(0),
      m_settings(studySettings)
{
    //m_uiManager.clearAllMenus(); // Clear all menus before creating new ones
    loadDecks();
}

void BrowseDecksScene::loadDecks()
{
    m_decks = loadFlashCardDecks(m_settings.getDeckDir());
    m_selectedDeckIndex = 0;
    m_currentPage = 0;
    m_needsRedraw = true;
}

void BrowseDecksScene::drawBookshelf(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    std::vector<std::string> bookshelfOptions =
        {"book1", "book2", "book3", "book4", "book5", "book6", "book7", "book8", "book9"};

    std::string selectedBookshelf;
    if (m_decks.empty() || m_selectedDeckIndex == 0)
    {
        selectedBookshelf = "bookfull";
    }
    else
    {
        if (bookshelfOptions.size() > 1 && m_paging)
        {
            do
            {
                bookshelfIndex = rand() % bookshelfOptions.size();
            } while (bookshelfIndex == m_prevBookshelfIndex);
        }

        m_prevBookshelfIndex = bookshelfIndex;
        selectedBookshelf = bookshelfOptions[bookshelfIndex];
    }

    window->drawAsciiArt(selectedBookshelf,
                         4,
                         (window->getSize().Y - static_cast<int>(window->getAsciiArtByName("book1")->getHeight())) - 3);
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
        loadDecks();
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
    for (size_t i = 0; i < m_decks.size(); ++i)
    {
        std::string deckText = (i == m_selectedDeckIndex ? "> " : "  ") + m_decks[i].name;
        window->drawText(deckText, 2, deckListY + static_cast<int>(i));
    }

    drawBookshelf(window);

    // Draw selected deck contents with paging
    if (!m_decks.empty())
    {
        const auto &selectedDeck = m_decks[m_selectedDeckIndex];
        int cardListX = window->getSize().X / 2;
        int cardListY = 5;
        m_maxCardsPerPage = (window->getSize().Y - cardListY - 5) / 5; // 5 lines per card, leave space for instructions
        size_t totalPages = (selectedDeck.cards.size() + m_maxCardsPerPage - 1) / m_maxCardsPerPage;

        window->drawText("Deck Contents (Page " + std::to_string(m_currentPage + 1) + "/" + std::to_string(totalPages) +
                             "):",
                         cardListX,
                         cardListY - 1);

        for (size_t i = m_currentPage * m_maxCardsPerPage;
             i < min(selectedDeck.cards.size(), (m_currentPage + 1) * m_maxCardsPerPage);
             ++i)
        {
            const auto &card = selectedDeck.cards[i];
            int yOffset = cardListY + static_cast<int>(i % m_maxCardsPerPage) * 5;

            // Truncate question and answer to fit within the available space
            std::string truncatedQuestion = card.question.substr(0, window->getSize().X - cardListX - 5);
            std::string truncatedAnswer = card.answer.substr(0, window->getSize().X - cardListX - 5);

            window->drawText("Q: " + truncatedQuestion, cardListX, yOffset);
            window->drawText("A: " + truncatedAnswer, cardListX, yOffset + 1);
            window->drawText("D: " + cardDifficultyToStr(card.difficulty), cardListX, yOffset + 2);
            window->drawText("---", cardListX, yOffset + 3);
        }

        window->drawText("Use Left/Right arrows to change pages", cardListX + cardListX / 2, window->getSize().Y - 3);
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

        if (key == key::arrow_prefix || key == key::numlock)
        {                   // Arrow key prefix
            key = _getch(); // Get the actual arrow key code
            switch (key)
            {
            case key::key_up: // Up arrow
                if (m_selectedDeckIndex > 0)
                {
                    m_selectedDeckIndex--;
                    m_needsRedraw = true;
                    m_paging = true;
                }

                m_currentPage = 0;
                break;
            case key::key_down: // Down arrow
                if (m_selectedDeckIndex < m_decks.size() - 1)
                {
                    m_selectedDeckIndex++;
                    m_needsRedraw = true;
                    m_paging = true;
                }

                m_currentPage = 0;
                break;
            case key::key_left: // Left arrow
                if (m_currentPage > 0 && std::chrono::steady_clock::now() - m_lastPageChangeTime >= m_pageChangeDelay)
                {
                    m_currentPage--;
                    m_needsRedraw = true;
                    m_lastPageChangeTime = std::chrono::steady_clock::now();
                    m_paging = false;
                }
                break;
            case key::key_right: // Right arrow
                if (!m_decks.empty() && std::chrono::steady_clock::now() - m_lastPageChangeTime >= m_pageChangeDelay)
                {
                    const auto &selectedDeck = m_decks[m_selectedDeckIndex];
                    int totalPages =
                        (static_cast<int>(selectedDeck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;
                    if (m_currentPage < totalPages - 1)
                    {
                        m_currentPage++;
                        m_needsRedraw = true;
                        m_lastPageChangeTime = std::chrono::steady_clock::now();
                        m_paging = false;
                    }
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
            case key::key_enter: // Enter
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
            case key::key_esc:
                for (auto &scene : m_uiManager.getScenes())
                {
                    scene->setStaticDrawn(false);
                }
                m_needsRedraw = true;
                m_goBack();
                break;
            default:
                inputHandled = false;
            }
        }
    }
}


/* -------EDIT -------------*/

FlashcardScene::FlashcardScene(ConsoleUI::UIManager &uiManager,
                               const FlashCardDeck &deck,
                               std::function<void()> goBack,
                               std::function<void()> goToDeckSelection,
                               std::function<void(const std::vector<int> &, int, bool)> showResults,
                               StudySettings &studySettings)
    : m_uiManager(uiManager), m_deck(deck), m_goBack(goBack), m_showResults(showResults), m_needsRedraw(true),
      m_currentCardIndex(0), m_showAnswer(false), m_settings(studySettings), m_lastAnswerDisplayed(false), m_score(0)
{

    m_uiManager.clearMenu("difficulty");
    m_settings.startSession();
    // Menu for the card difficulty
    auto &menu = m_uiManager.createMenu("difficulty", true);
    menu.addButton("Easy", [this]() { selectDifficulty(EASY); });
    menu.addButton("Medium", [this]() { selectDifficulty(MEDIUM); });
    menu.addButton("Hard", [this]() { selectDifficulty(HARD); });

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
    std::shuffle(unseenCards.begin(), unseenCards.end(), std::default_random_engine());
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

    std::mt19937 m_rng{std::random_device{}()};
    // Shuffle seen cards based on probability distribution
    std::vector<size_t> shuffledSeenCards;
    for (size_t i = 0; i < seenCards.size(); ++i)
    {
        shuffledSeenCards.push_back(seenCards[dist(m_rng)]);
    }

    // Append seen cards to the card order
    m_cardOrder.insert(m_cardOrder.end(), shuffledSeenCards.begin(), shuffledSeenCards.end());

    // Limit the number of cards to study
    if (m_cardOrder.size() > numCardsToStudy)
    {
        m_cardOrder.resize(numCardsToStudy);
    }
}

void FlashcardScene::update()
{
    m_uiManager.getWindow()->drawText(steadyClockToString(m_settings.getSessionStart()),
                                      2,
                                      m_uiManager.getWindow()->getSize().Y - 5);
    if (timeComplete(m_studySetting.getSessionStart(), m_settings.getStudyDurationMin() * 60))
    {
        for (auto &scene : m_uiManager.getScenes())
        {
            scene->setStaticDrawn(false);
        }
        endSession(true);
    }
    Sleep(10);
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
    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        m_staticDrawn = true;
        m_needsRedraw = true;
    }

    int textBoxWidth = 44;
    int questionBoxHeight = 9;
    int answerBoxHeight = 7;

    if (m_currentCardIndex < m_cardOrder.size())
    {
        const auto &card = m_deck.cards[m_cardOrder[m_currentCardIndex]];

        if (m_needsRedraw)
        {
            // Clear the question area
            for (int i = 6; i < 6 + questionBoxHeight; ++i)
            {
                window->drawText(std::string(textBoxWidth, ' '), (window->getSize().X - textBoxWidth) / 2, i);
            }

            // Draw the question box and text
            window->drawBox((window->getSize().X - textBoxWidth) / 2, 6, textBoxWidth, questionBoxHeight);
            window->drawCenteredText("Question:", 4);
            window->drawWrappedText(card.question, (window->getSize().X - textBoxWidth) / 2 + 2, 8, textBoxWidth - 4);
            window->drawCenteredText("Press SPACE to interact", window->getSize().Y * 4 / 5);

            m_needsRedraw = false;
        }

        if (m_showAnswer && m_lastAnswerDisplayed)
        {
            // Clear the answer area
            for (int i = window->getSize().Y / 2 - answerBoxHeight / 2;
                 i < window->getSize().Y / 2 + answerBoxHeight / 2 + 2;
                 ++i)
            {
                window->drawText(std::string(textBoxWidth, ' '), (window->getSize().X - textBoxWidth) / 2, i);
            }

            // Draw the answer box and text
            window->drawBox((window->getSize().X - textBoxWidth) / 2,
                            window->getSize().Y / 2 - answerBoxHeight / 2 + 2,
                            textBoxWidth,
                            answerBoxHeight);
            window->drawCenteredText("Answer:", window->getSize().Y / 2 - 3);
            window->drawWrappedText(card.answer,
                                    (window->getSize().X - textBoxWidth) / 2 + 2,
                                    window->getSize().Y / 2 - answerBoxHeight / 2 + 4,
                                    textBoxWidth - 4);

            auto &menu = m_uiManager.getMenu("difficulty");
            size_t totalWidth = 0;
            for (size_t i = 0; i < menu.getButtonCount(); ++i)
            {
                totalWidth += menu.getButtonWidth(i) + 2;
            }
            totalWidth -= 2;
            int menuX = (window->getSize().X - static_cast<int>(totalWidth)) / 2;
            menu.draw(menuX, window->getSize().Y * 2 / 3 + 2);
            m_lastAnswerDisplayed = false;
        }
        else
        {
            // Clear the answer area
            for (int i = (window->getSize().Y * 2 / 3); i < (window->getSize().Y * 2 / 3) + 2; ++i)
            {
                window->drawText(std::string(window->getSize().X - 4, ' '), 2, i);
            }
        }

        int min_remaining = timeRemainingMins(m_settings.getSessionStart(), m_settings.getStudyDurationMin());
        window->drawText("Time remaining: " + std::to_string(min_remaining) + "min", 2, window->getSize().Y - 4);
        window->drawText(steadyClockToString(m_settings.getSessionStart()), 2, window->getSize().Y - 5);

        std::string progress =
            "Card " + std::to_string(m_currentCardIndex + 1) + " of " + std::to_string(m_cardOrder.size());
        window->drawText(progress, 2, window->getSize().Y - 3);
        m_lastAnswerDisplayed = false;
    }
    else
    {
        window->drawCenteredText("All cards reviewed!", window->getSize().Y / 2);
    }
}


void FlashcardScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();
        bool inputHandled = true;

        if (key == key::arrow_prefix || key == key::numlock)
        {                   // Arrow key prefix
            key = _getch(); // Get the actual arrow key code
            if (m_showAnswer)
            {
                auto &menu = m_uiManager.getMenu("difficulty");
                switch (key)
                {
                case key::key_left: // Left arrow
                    m_lastAnswerDisplayed = true;
                    menu.selectPreviousButton();
                    break;
                case key::key_right: // Right arrow
                    m_lastAnswerDisplayed = true;
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
            case key::key_space: // Spacebar

                if (m_showAnswer)
                {
                    auto &menu = m_uiManager.getMenu("difficulty");
                    menu.activateSelectedButton();
                }
                else
                {
                    m_showAnswer = true;
                    m_lastAnswerDisplayed = true;
                    m_needsRedraw = true;
                }
                break;
            case key::key_esc: // Escape key
                for (auto &scene : m_uiManager.getScenes())
                {
                    scene->setStaticDrawn(false);
                }
                endSession(false);
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

int easyStreak = 0;
void FlashcardScene::selectDifficulty(CardDifficulty difficulty)
{
    m_difficultyCount[difficulty - 1]++;
    switch (difficulty)
    {
    case EASY:
        m_score += 20;
        easyStreak++;
        if (easyStreak >= 3)
        {
            m_score += 10; // Bonus for 3+ Easy cards in a row
        }
        break;
    case MEDIUM:
        m_score += 10;
        easyStreak = 0; // Reset easy streak
        break;
    case HARD:
        m_score += 5;
        easyStreak = 0;
        break;
    }

    for (auto &scene : m_uiManager.getScenes())
    {
        scene->setStaticDrawn(false);
    }
    updateCardDifficulty(m_cardOrder[m_currentCardIndex], difficulty);
    nextCard();
}

void FlashcardScene::updateCardDifficulty(size_t cardIndex, CardDifficulty difficulty)
{
    auto &card = m_deck.cards[cardIndex];
    card.difficulty = difficulty;
    card.n_times_answered++;
}

void FlashcardScene::nextCard()
{
    m_currentCardIndex++;
    m_showAnswer = false;
    m_lastAnswerDisplayed = false;
    m_needsRedraw = true;
    if (m_currentCardIndex >= m_cardOrder.size())
    {
        endSession(true); // Pass true if the session is completed
    }
}

void FlashcardScene::endSession(bool sessionCompleted)
{
    saveUpdatedDeck();
    m_showResults(m_difficultyCount, m_score, sessionCompleted);
}

void FlashcardScene::saveUpdatedDeck()
{
    writeFlashCardDeckWithChecks(m_deck, m_deck.filename, true);
    m_decksNeedReload = true;
}


ResultsScene::ResultsScene(ConsoleUI::UIManager &uiManager,
                           const std::vector<int> &difficultyCount,
                           int score,
                           std::function<void()> goToMainMenu,
                           std::function<void()> goToDeckSelection,
                           std::function<void()> goToGame,
                           bool sessionComplete)
    : m_uiManager(uiManager), m_difficultyCount(difficultyCount), m_goToMainMenu(goToMainMenu),
      m_goToDeckSelection(goToDeckSelection), m_goToGame(goToGame), m_needsRedraw(true),
      m_sessionComplete(sessionComplete), m_score(score)
{
    m_uiManager.clearMenu("results");
    auto &menu = m_uiManager.createMenu("results", false);
    menu.addButton("     Start game?     ", m_goToGame);
    menu.addButton("   Study New Deck?   ", m_goToDeckSelection);
    menu.addButton("  Back to Main Menu  ", m_goToMainMenu);

    m_uiManager.clearMenu("session skipped");
    auto &menu2 = m_uiManager.createMenu("session skipped", false);
    menu2.addButton("   Study New Deck?   ", m_goToDeckSelection);
    menu2.addButton("  Back to Main Menu  ", m_goToMainMenu);

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
    int windowX = static_cast<int>(window->getSize().X);
    int windowY = static_cast<int>(window->getSize().Y);

    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        m_staticDrawn = true;

        // Clear the text areas
        window->drawText(std::string(phrase.length(), ' '),
                         (windowX - static_cast<int>(phrase.length())) / 2,
                         windowY / 2 - 4);
        window->drawText(std::string(20, ' '), (windowX - 20) / 2, windowY / 2 - 2);
        window->drawText(std::string(20, ' '), (windowX - 20) / 2, windowY / 2);
        window->drawText(std::string(20, ' '), (windowX - 20) / 2, windowY / 2 + 2);
        window->drawText(std::string(20, ' '), (windowX - 20) / 2, windowY / 2 + 4);

        window->drawAsciiArt("dragon",
                             windowX / 2 - (static_cast<int>(window->getAsciiArtByName("dragon")->getWidth()) / 2),
                             windowY / 2 - (static_cast<int>(window->getAsciiArtByName("dragon")->getHeight()) / 2));
        window->drawCenteredText(phrase, windowY / 2 - 4);

        std::string easyText = "\033[32mEasy: " + std::to_string(m_difficultyCount[EASY - 1]) + "\033[0m";
        std::string mediumText = "\033[33mMedium: " + std::to_string(m_difficultyCount[MEDIUM - 1]) + "\033[0m";
        std::string hardText = "\033[31mHard: " + std::to_string(m_difficultyCount[HARD - 1]) + "\033[0m";

        window->drawText(easyText, windowX / 2 - (static_cast<int>(easyText.length() - 7) / 2), windowY / 2 - 2);
        window->drawText(mediumText, windowX / 2 - (static_cast<int>(mediumText.length() - 7) / 2), windowY / 2);
        window->drawText(hardText, windowX / 2 - (static_cast<int>(hardText.length() - 7) / 2), windowY / 2 + 2);

        std::string scoreText = std::to_string(m_score) + "\033[0m";

        // Color the score based on easy and hard counts
        if (m_difficultyCount[EASY - 1] > m_difficultyCount[HARD - 1])
        {
            window->drawText("\033[35mScore: " + scoreText,
                             windowX / 2 - (static_cast<int>(scoreText.length() + 5) / 2),
                             windowY / 2 + 4);
        }
        else if (m_difficultyCount[HARD - 1] > m_difficultyCount[EASY - 1])
        {
            window->drawText("\033[33mScore: " + scoreText,
                             windowX / 2 - (static_cast<int>(scoreText.length() + 5) / 2),
                             windowY / 2 + 4);
        }
        else
        {
            window->drawText("\033[36mScore: " + scoreText,
                             windowX / 2 - (static_cast<int>(scoreText.length() + 5) / 2),
                             windowY / 2 + 4);
        }
    }

    if (!m_needsRedraw)
        return;


    if (m_sessionComplete)
    {
        auto &menu = m_uiManager.getMenu("results");
        // Calculate total width manually
        size_t maxWidth = 0;
        for (size_t i = 0; i < menu.getButtonCount(); ++i)
        {
            maxWidth = max(menu.getButtonWidth(i), maxWidth);
        }
        int menuX = (windowX - static_cast<int>(maxWidth)) / 2;
        menu.draw(menuX, windowY * 3 / 4);
    }
    else
    {
        auto &menu = m_uiManager.getMenu("session skipped");
        // Calculate total width manually
        size_t maxWidth = 0;
        for (size_t i = 0; i < menu.getButtonCount(); ++i)
        {
            maxWidth = max(menu.getButtonWidth(i), maxWidth);
        }
        int menuX = (windowX - static_cast<int>(maxWidth)) / 2;
        menu.draw(menuX, windowY * 3 / 4);
    }

    m_needsRedraw = false;
}

void ResultsScene::handleInput()
{
    if (_kbhit())
    {
        if (m_sessionComplete)
        {
            m_uiManager.getMenu("results").handleInput();
            m_needsRedraw = true;
        }
        else
        {
            m_uiManager.getMenu("session skipped").handleInput();
            m_needsRedraw = true;
        }
    }
}

} // namespace FlashcardApp
