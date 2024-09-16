#pragma once

#include "menu.h"
#include "deck.h"
#include <memory>
#include <vector>
#include <random>
#include <functional>
#include <chrono>

namespace FlashcardApp {

class BrowseDecksScene : public ConsoleUI::Scene {
public:
    BrowseDecksScene(ConsoleUI::UIManager& uiManager, 
                     std::function<void()> goBack,
                     std::function<void(const FlashCardDeck&)> openDeck);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window, const std::string& text, int x, int y, int width);
    void loadDecks();

private:
    ConsoleUI::UIManager& m_uiManager;
    std::vector<FlashCardDeck> m_decks;
    size_t m_selectedDeckIndex = 0;
    std::function<void()> m_goBack;
    std::function<void(const FlashCardDeck&)> m_openDeck;
    bool m_needsRedraw = true;
    int m_currentPage = 0;
    int m_maxCardsPerPage = 0;
};

class EditDecksScene : public ConsoleUI::Scene {
public:
    EditDecksScene(ConsoleUI::UIManager& uiManager, 
                     std::function<void()> goBack,
                     std::function<void(const FlashCardDeck&)> openDeck);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window, const std::string& text, int x, int y, int width);
    void loadDecks();

private:
    ConsoleUI::UIManager& m_uiManager;
    std::vector<FlashCardDeck> m_decks;
    size_t m_selectedDeckIndex = 0;
    std::function<void()> m_goBack;
    std::function<void(const FlashCardDeck&)> m_openDeck;
    bool m_needsRedraw = true;
    int m_currentPage = 0;
    int m_maxCardsPerPage = 0;
};



class EditFlashcardScene : public ConsoleUI::Scene {
public:
    EditFlashcardScene(ConsoleUI::UIManager& uiManager, 
                   const FlashCardDeck& deck,
                   std::function<void()> goBack,
                   std::function<void(const std::vector<int>&)> showResults);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window, const std::string& text, int x, int y, int width);

private:
    // void selectDifficulty(int difficulty);
    void nextCard();
    void endSession();

    ConsoleUI::UIManager& m_uiManager;
    FlashCardDeck m_deck;
    // std::vector<size_t> m_cardOrder;
    size_t m_currentCardIndex = 0;
    // bool m_showAnswer = false;
    // std::vector<int> m_difficultyCount = {0, 0, 0};  // Easy, Medium, Hard
    std::function<void()> m_goBack;
    // std::function<void(const std::vector<int>&)> m_showResults;
    // bool m_needsRedraw;
};



class FlashcardScene : public ConsoleUI::Scene {
public:
    FlashcardScene(ConsoleUI::UIManager& uiManager, 
                   const FlashCardDeck& deck,
                   std::function<void()> goBack,
                   std::function<void(const std::vector<int>&)> showResults);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window, const std::string& text, int x, int y, int width);

private:
    void selectDifficulty(int difficulty);
    void nextCard();
    void endSession();

    ConsoleUI::UIManager& m_uiManager;
    FlashCardDeck m_deck;
    std::vector<size_t> m_cardOrder;
    size_t m_currentCardIndex = 0;
    bool m_showAnswer = false;
    std::vector<int> m_difficultyCount = {0, 0, 0};  // Easy, Medium, Hard
    std::function<void()> m_goBack;
    std::function<void(const std::vector<int>&)> m_showResults;
    bool m_needsRedraw;
};

class ResultsScene : public ConsoleUI::Scene {
public:
    ResultsScene(ConsoleUI::UIManager& uiManager, 
                 const std::vector<int>& difficultyCount,
                 std::function<void()> goToMainMenu,
                 std::function<void()> goToDeckSelection);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;

private:
    ConsoleUI::UIManager& m_uiManager;
    std::vector<int> m_difficultyCount;
    std::function<void()> m_goToMainMenu;
    std::function<void()> m_goToDeckSelection;
    bool m_needsRedraw;
};

}