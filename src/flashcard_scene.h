/**
 * @file flashcard_scene.h
 * @author Green ALligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "deck.h"
#include "menu.h"
#include "settings_scene.h"
#include <chrono>
#include <functional>
#include <memory>
#include <random>
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
                     std::function<void(const FlashCardDeck &)> openDeck);

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

private:
    ConsoleUI::UIManager &m_uiManager;                     ///< Reference to the UI manager.
    std::vector<FlashCardDeck> m_decks;                    ///< Vector of loaded flashcard decks.
    size_t m_selectedDeckIndex = 0;                        ///< Index of the currently selected deck.
    std::function<void()> m_goBack;                        ///< Function to call when going back.
    std::function<void(const FlashCardDeck &)> m_openDeck; ///< Function to call when opening a deck.
    bool m_needsRedraw = true;                             ///< Flag indicating if the scene needs to be redrawn.
    int m_currentPage = 0;                                 ///< Current page number when viewing deck contents.
    int m_maxCardsPerPage = 0;                             ///< Maximum number of cards that can be displayed per page.
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
                   std::function<void(const std::vector<int> &)> showResults,
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

private:
    /**
     * @brief Record the selected difficulty for the current flashcard.
     *
     * @param difficulty The difficulty level selected by the user (0: Easy, 1: Medium, 2: Hard).
     */
    void selectDifficulty(int difficulty);

    void updateCardDifficulty(int cardIndex, CardDifficulty difficulty);
    void saveUpdatedDeck();
    void initializeCardOrder();
    // int flashcard_limit = 10;
    bool empty = false;
    StudySettings m_settings;


    /**
     * @brief Move to the next flashcard in the deck.
     */
    void nextCard();

    /**
     * @brief End the current study session and show results.
     */
    void endSession();

    ConsoleUI::UIManager &m_uiManager;              ///< Reference to the UI manager.
    FlashCardDeck m_deck;                           ///< The flashcard deck being studied.
    std::vector<size_t> m_cardOrder;                ///< Randomized order of flashcards for the session.
    size_t m_currentCardIndex = 0;                  ///< Index of the current flashcard being shown.
    bool m_showAnswer = false;                      ///< Flag indicating whether the answer is currently visible.
    std::vector<int> m_difficultyCount = {0, 0, 0}; ///< Count of cards rated as Easy, Medium, Hard.
    std::function<void()> m_goBack;                 ///< Function to call when going back.
    std::function<void(const std::vector<int> &)> m_showResults; ///< Function to call when showing results.
    bool m_needsRedraw;                                          ///< Flag indicating if the scene needs to be redrawn.
    StudySettings m_studySetting;
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
                 std::function<void()> goToMainMenu,
                 std::function<void()> goToDeckSelection,
                 std::function<void()> goToGame);
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

private:
    ConsoleUI::UIManager &m_uiManager;         ///< Reference to the UI manager.
    std::vector<int> m_difficultyCount;        ///< Count of cards rated as Easy, Medium, Hard.
    std::function<void()> m_goToMainMenu;      ///< Function to call when returning to the main menu.
    std::function<void()> m_goToDeckSelection; ///< Function to call when going to deck selection.
    std::function<void()> m_goToGame;          ///< Function to call when starting a new game.
    bool m_needsRedraw;                        ///< Flag indicating if the scene needs to be redrawn.
};

} // namespace FlashcardApp
