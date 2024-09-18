#pragma once

#ifndef FLASHCARD_SCENE
#define FLASHCARD_SCENE

#include "deck.h"
#include "menu.h"
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
 * @brief Defines the Scene for browsing the card decks
 * @details This scene shows which decks can be selected
 *
 */
class BrowseDecksScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new Browse Decks Scene object
     *
     * @param uiManager
     * @param goBack action to take when the back button is pressed
     * @param openDeck action to take when the openDeck button pressed
     */
    BrowseDecksScene(ConsoleUI::UIManager &uiManager,
                     std::function<void()> goBack,
                     std::function<void(const FlashCardDeck &)> openDeck);
    /**
     * @brief called each frame to update the scene's state or perform any necessary logic
     *
     */
    void update() override;

    /**
     * @brief Called every farme to render the scenes UI elements using the provided ConsoleWindow instance
     *
     * @param window
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handles the user input for the scene
     *
     */
    void handleInput() override;

    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string &text,
                         int x,
                         int y,
                         size_t width);
    /**
     * @brief Loads the available decks to be displayed
     *
     */
    void loadDecks();

private:
    /** the UI manager for the scene */
    ConsoleUI::UIManager &m_uiManager;
    /** all available decks */
    std::vector<FlashCardDeck> m_decks;
    /** the index of the selected deck */
    size_t m_selectedDeckIndex = 0;
    /** the scene to return to */
    std::function<void()> m_goBack;
    /** the current deck of flash cards */
    std::function<void(const FlashCardDeck &)> m_openDeck;
    /** determines if the scene needs redrawn */
    bool m_needsRedraw = true;
    /** the current page of cards */
    int m_currentPage = 0;
    /** the maximum nuber of cards per 'page' */
    size_t m_maxCardsPerPage = 0;
};

class EditDecksScene : public ConsoleUI::Scene
{
public:
    EditDecksScene(ConsoleUI::UIManager &uiManager,
                   std::function<void()> goBack,
                   std::function<void(const FlashCardDeck &)> openDeck);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string &text,
                         int x,
                         int y,
                         size_t width);
    void loadDecks();

private:
    ConsoleUI::UIManager &m_uiManager;
    std::vector<FlashCardDeck> m_decks;
    size_t m_selectedDeckIndex = 0;
    std::function<void()> m_goBack;
    std::function<void(const FlashCardDeck &)> m_openDeck;
    bool m_needsRedraw = true;
    int m_currentPage = 0;
    size_t m_maxCardsPerPage = 0;
};


class EditFlashcardScene : public ConsoleUI::Scene
{
public:
    EditFlashcardScene(ConsoleUI::UIManager &uiManager,
                       const FlashCardDeck &deck,
                       std::function<void()> goBack,
                       std::function<void(const std::vector<int> &)> editFlashcardScene);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string &text,
                         int x,
                         int y,
                         size_t width);

private:
    // void selectDifficulty(int difficulty);
    void nextCard();
    void endSession();

    ConsoleUI::UIManager &m_uiManager;
    FlashCardDeck m_deck;
    // std::vector<size_t> m_cardOrder;
    size_t m_currentCardIndex = 0;
    // bool m_showAnswer = false;
    // std::vector<int> m_difficultyCount = {0, 0, 0};  // Easy, Medium, Hard
    std::function<void()> m_goBack;
    // std::function<void(const std::vector<int>&)> m_showResults;
    // bool m_needsRedraw;
};


class FlashcardScene : public ConsoleUI::Scene
{
public:
    FlashcardScene(ConsoleUI::UIManager &uiManager,
                   const FlashCardDeck &deck,
                   std::function<void()> goBack,
                   std::function<void(const std::vector<int> &)> showResults);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string &text,
                         int x,
                         int y,
                         size_t width);

private:
    void selectDifficulty(int difficulty);
    void nextCard();
    void endSession();

    ConsoleUI::UIManager &m_uiManager;
    FlashCardDeck m_deck;
    std::vector<size_t> m_cardOrder;
    size_t m_currentCardIndex = 0;
    bool m_showAnswer = false;
    std::vector<int> m_difficultyCount = {0, 0, 0}; // Easy, Medium, Hard
    std::function<void()> m_goBack;
    std::function<void(const std::vector<int> &)> m_showResults;
    bool m_needsRedraw;
};

class ResultsScene : public ConsoleUI::Scene
{
public:
    ResultsScene(ConsoleUI::UIManager &uiManager,
                 const std::vector<int> &difficultyCount,
                 std::function<void()> goToMainMenu,
                 std::function<void()> goToDeckSelection);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager;
    std::vector<int> m_difficultyCount;
    std::function<void()> m_goToMainMenu;
    std::function<void()> m_goToDeckSelection;
    bool m_needsRedraw;
};

} // namespace FlashcardApp

#endif
