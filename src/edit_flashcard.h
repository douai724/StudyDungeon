#ifndef EDIT_DECK_SCENE_H
#define EDIT_DECK_SCENE_H

#include "deck.h"
#include "menu.h"
#include <functional>
#include <memory>
#include <vector>

namespace FlashcardEdit
{

class EditDeckScene : public ConsoleUI::Scene
{


public:
    EditDeckScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> goBack,
                  std::function<void(FlashCardDeck &)> openEditFlashcardScene);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager;
    std::function<void()> m_goBack;
    std::function<void(FlashCardDeck &)> m_openEditFlashcardScene;
    std::vector<FlashCardDeck> m_decks;
    size_t m_selectedDeckIndex;
    int m_currentPage;
    int m_maxCardsPerPage;
    bool m_needsRedraw;

    void loadDecks();
    void addNewDeck();
    void deleteDeck();
    void renameDeck();
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string &text,
                         int x,
                         int y,
                         int width);
};

class EditFlashcardScene : public ConsoleUI::Scene
{
public:
    EditFlashcardScene(ConsoleUI::UIManager &uiManager, FlashCardDeck &deck, std::function<void()> goBack);

    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager;
    FlashCardDeck &m_deck;
    std::function<void()> m_goBack;
    size_t m_selectedCardIndex;
    int m_currentPage;
    int m_maxCardsPerPage;
    bool m_needsRedraw;

    void editSelectedCard();
    void addNewCard();
    void deleteSelectedCard();
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string &text,
                         int x,
                         int y,
                         int width);
};

} // namespace FlashcardEdit

#endif // EDIT_DECK_SCENE_H
