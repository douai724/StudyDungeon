/**
 * @file flashcard_scene.h
 * @author Green Alligators
 * @brief Classes and functions used in the study session UI scene for reviewing flashcards
 * @version 1.0.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "artwork.h"
#include "deck.h"
#include "edit_flashcard.h"
#include "menu.h"
#include "settings_scene.h"
#include "util.h"
#include <algorithm>
#include <chrono>
#include <conio.h>
#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <sstream>
#include <vector>

namespace FlashcardApp
{

/**
 * @class BrowseDecksScene
 * @brief A scene for browsing and selecting flashcard decks.
 *
 * This class represents a user interface scene that allows users to browse
 * through available flashcard decks, view their contents, and select a deck
 * to study or edit.
 */
class BrowseDecksScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new BrowseDecksScene object.
     *
     * @param uiManager The UI manager responsible for handling the user interface.
     * @param goBack A function to be called when the user wants to go back to the previous scene.
     * @param openDeck A function to be called when the user selects a deck to open.
     */
    BrowseDecksScene(ConsoleUI::UIManager &uiManager,
                     std::function<void()> goBack,
                     std::function<void(const FlashCardDeck &)> openDeck,
                     StudySettings &settings);

    /**
     * @brief Initialize the scene.
     *
     * This function is called when the Scene changes to another.
     * Currently, it doesn't perform any actions as the scene doesn't require initialization.
     */
    void init() override;

    /**
     * @brief Update the scene state.
     *
     * This function is called every frame to update the scene's state.
     * Currently, it doesn't perform any actions as the scene doesn't require continuous updates.
     */
    void update() override;

    /**
     * @brief Render the scene to the console window.
     *
     * @param window The console window to render the scene onto.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handle user input for the scene.
     *
     * This function processes keyboard input to navigate through decks,
     * change pages, select a deck, or go back to the previous scene.
     */
    void handleInput() override;


    /**
     * @brief Load available flashcard decks from storage.
     *
     * This function reads flashcard decks from the "Decks/" directory and
     * populates the m_decks vector with the loaded decks.
     */
    void loadDecks();

    /**
     * @brief Sets the static drawn state of the scene.
     * @param staticDrawn Boolean indicating whether the static elements have been drawn.
     */
    void setStaticDrawn(bool staticDrawn) override;

    void setDecksNeedReload(bool needReload)
    {
        m_decksNeedReload = needReload;
    }

    void drawBookshelf(std::shared_ptr<ConsoleUI::ConsoleWindow> window);

    std::vector<FlashCardDeck> m_decks; ///< Vector of loaded flashcard decks.
    size_t m_selectedDeckIndex = 0;     ///< Index of the currently selected deck.
    int m_currentPage = 0;              ///< Current page number when viewing deck contents.


private:
    ConsoleUI::UIManager &m_uiManager;                     ///< Reference to the UI manager.
    std::function<void()> m_goBack;                        ///< Function to call when going back.
    std::function<void(const FlashCardDeck &)> m_openDeck; ///< Function to call when opening a deck.
    bool m_needsRedraw = true;                             ///< Flag indicating if the scene needs to be redrawn.
    int m_maxCardsPerPage = 0;                             ///< Maximum number of cards that can be displayed per page.

    bool m_staticDrawn = false;
    bool m_decksNeedReload = false;
    std::chrono::steady_clock::time_point m_lastPageChangeTime;
    const std::chrono::milliseconds m_pageChangeDelay{200};
    StudySettings m_settings;

    bool m_paging = false;
    int m_prevBookshelfIndex = -1;
    int bookshelfIndex = 0;
};

/**
 * @class FlashcardScene
 * @brief A scene for studying flashcards from a selected deck.
 *
 * This class represents a user interface scene that allows users to go through
 * flashcards in a selected deck, view questions and answers, and rate the
 * difficulty of each card.
 */
class FlashcardScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new FlashcardScene object.
     *
     * @param uiManager The UI manager responsible for handling the user interface.
     * @param deck The flashcard deck to study.
     * @param goBack A function to be called when the user wants to go back to the previous scene.
     * @param showResults A function to be called when the study session ends, passing difficulty counts.
     */
    FlashcardScene(ConsoleUI::UIManager &uiManager,
                   const FlashCardDeck &deck,
                   std::function<void()> goBack,
                   std::function<void()> goToDeckSelection,
                   std::function<void(const std::vector<int> &, int, bool)> showResults,
                   StudySettings &studySettings);
    /**
     * @brief Initialize the scene.
     *
     * This function is called when the Scene changes to another.
     * Currently, it doesn't perform any actions as the scene doesn't require initialization.
     */
    void init() override;

    /**
     * @brief Update the scene state.
     *
     * This function is called every frame to update the scene's state.
     * Currently, it doesn't perform any actions as the scene doesn't require continuous updates.
     */

    void update() override;

    /**
     * @brief Render the scene to the console window.
     *
     * @param window The console window to render the scene onto.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handle user input for the scene.
     *
     * This function processes keyboard input to show answers, select difficulty,
     * and navigate through flashcards.
     */
    void handleInput() override;

    /**
     * @brief Sets the static drawn state of the scene.
     * @param staticDrawn Boolean indicating whether the static elements have been drawn.
     */
    void setStaticDrawn(bool staticDrawn) override;

    void setDecksNeedReload(bool needReload)
    {
        m_decksNeedReload = needReload;
    }
    void updateCardDifficulty(size_t cardIndex, CardDifficulty difficulty);
    void initializeCardOrder();

    /**
     * @brief Move to the next flashcard in the deck.
     */
    void nextCard();


    std::vector<size_t> m_cardOrder; ///< Randomized order of flashcards for the session.
    FlashCardDeck m_deck;            ///< The flashcard deck being studied.
    size_t m_currentCardIndex = 0;   ///< Index of the current flashcard being shown.
    bool m_showAnswer = false;       ///< Flag indicating whether the answer is currently visible.
    bool m_lastAnswerDisplayed;


private:
    /**
     * @brief Record the selected difficulty for the current flashcard.
     *
     * @param difficulty The difficulty level selected by the user (1: Easy, 2: Medium, 3: Hard).
     */
    void selectDifficulty(CardDifficulty difficulty);


    void saveUpdatedDeck();
    // int flashcard_limit = 10;
    bool empty = false;
    StudySettings m_settings;

    bool m_decksNeedReload = false;


    /**
     * @brief End the current study session and show results.
     */
    void endSession(bool sessionComplete);

    ConsoleUI::UIManager &m_uiManager;              ///< Reference to the UI manager.
    std::vector<int> m_difficultyCount = {0, 0, 0}; ///< Count of cards rated as Easy, Medium, Hard.
    std::function<void()> m_goBack;                 ///< Function to call when going back.
    std::function<void(const std::vector<int> &, int, bool)> m_showResults; ///< Function to call when showing results.
    bool m_needsRedraw; ///< Flag indicating if the scene needs to be redrawn.

    bool m_staticDrawn = false;   ///< Flag indicating if the static elements have been drawn.
    StudySettings m_studySetting; ///< study session settings

    std::string m_lastQuestionDisplayed; ///< The last question displayed
    bool m_answerDrawn;                  ///< has the answer been drawn
    int m_score;                         ///< score of the flashcards
};

/**
 * @class ResultsScene
 * @brief A scene for displaying the results of a flashcard study session.
 *
 * This class represents a user interface scene that shows the user their
 * performance in a completed flashcard study session, displaying the number
 * of cards rated as Easy, Medium, and Hard. It also provides options for
 * the user to navigate to other parts of the application.
 */
class ResultsScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new ResultsScene object.
     *
     * @param uiManager The UI manager responsible for handling the user interface.
     * @param difficultyCount A vector containing the count of cards rated as Easy, Medium, and Hard.
     * @param goToMainMenu A function to be called when the user wants to return to the main menu.
     * @param goToDeckSelection A function to be called when the user wants to select a new deck.
     * @param goToGame A function to be called when the user wants to start a new study session.
     */
    ResultsScene(ConsoleUI::UIManager &uiManager,
                 const std::vector<int> &difficultyCount,
                 int score,
                 std::function<void()> goToMainMenu,
                 std::function<void()> goToDeckSelection,
                 std::function<void()> goToGame,
                 bool sessionComplete);
    void init() override;

    /**
     * @brief Update the scene state.
     *
     * This function is called every frame to update the scene's state.
     * Currently, it doesn't perform any actions as the scene doesn't require continuous updates.
     */
    void update() override;

    /**
     * @brief Render the scene to the console window.
     *
     * @param window The console window to render the scene onto.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handle user input for the scene.
     *
     * This function processes keyboard input to navigate through the available options
     * (Main Menu, Deck Selection, Start Game).
     */
    void handleInput() override;

    /**
     * @brief Sets the static drawn state of the scene.
     * @param staticDrawn Boolean indicating whether the static elements have been drawn.
     */
    void setStaticDrawn(bool staticDrawn) override;

private:
    ConsoleUI::UIManager &m_uiManager;         ///< Reference to the UI manager.
    std::vector<int> m_difficultyCount;        ///< Count of cards rated as Easy, Medium, Hard.
    std::function<void()> m_goToMainMenu;      ///< Function to call when returning to the main menu.
    std::function<void()> m_goToDeckSelection; ///< Function to call when going to deck selection.
    std::function<void()> m_goToGame;          ///< Function to call when starting a new game.
    bool m_needsRedraw;                        ///< Flag indicating if the scene needs to be redrawn.
    std::string phrase;

    bool m_staticDrawn = false; ///< Flag indicating if the static elements have been drawn.
    bool m_sessionComplete;     ///< Has the study session completed
    int m_score;                ///< Score based on difficulty of cards
};

} // namespace FlashcardApp
