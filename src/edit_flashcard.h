
#ifndef EDIT_DECK_SCENE_H
#define EDIT_DECK_SCENE_H

#include "deck.h"
#include "menu.h"
#include <functional>
#include <memory>
#include <vector>

namespace FlashcardEdit {

/**
 * @brief The EditDeckScene class represents the scene for editing flashcard decks.
 */
class EditDeckScene : public ConsoleUI::Scene {
public:
    /**
     * @brief Constructor for the EditDeckScene class.
     * @param uiManager The UI manager.
     * @param goBack Function to go back to the previous scene.
     * @param openEditFlashcardScene Function to open the EditFlashcardScene.
     */
    EditDeckScene(ConsoleUI::UIManager& uiManager, 
                  std::function<void()> goBack,
                  std::function<void(FlashCardDeck&)> openEditFlashcardScene);

    /**
     * @brief Updates the EditDeckScene.
     */
    void update() override;

    /**
     * @brief Renders the EditDeckScene.
     * @param window The console window.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handles input for the EditDeckScene.
     */
    void handleInput() override;

private:
    ConsoleUI::UIManager& m_uiManager; ///< The UI manager.
    std::function<void()> m_goBack; ///< Function to go back to the previous scene.
    std::function<void(FlashCardDeck&)> m_openEditFlashcardScene; ///< Function to open the EditFlashcardScene.
    std::vector<FlashCardDeck> m_decks; ///< The flashcard decks.
    size_t m_selectedDeckIndex; ///< The index of the selected deck.
    int m_currentPage; ///< The current page of decks.
    int m_maxCardsPerPage; ///< The maximum number of cards per page.
    bool m_needsRedraw; ///< Flag indicating if the scene needs to be redrawn.

    /**
     * @brief Loads the flashcard decks.
     */
    void loadDecks();

    /**
     * @brief Adds a new flashcard deck.
     */
    void addNewDeck();

    /**
     * @brief Deletes the selected flashcard deck.
     */
    void deleteDeck();

    /**
     * @brief Renames the selected flashcard deck.
     */
    void renameDeck();

    /**
     * @brief Draws wrapped text on the console window.
     * @param window The console window.
     * @param text The text to be drawn.
     * @param x The x-coordinate of the text position.
     * @param y The y-coordinate of the text position.
     * @param width The maximum width of the text.
     */
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string& text,
                         int x,
                         int y,
                         int width);
};

/**
 * @brief The EditFlashcardScene class represents the scene for editing flashcards.
 */
class EditFlashcardScene : public ConsoleUI::Scene {
public:
    /**
     * @brief Constructor for the EditFlashcardScene class.
     * @param uiManager The UI manager.
     * @param deck The flashcard deck to edit.
     * @param goBack Function to go back to the previous scene.
     */
    EditFlashcardScene(ConsoleUI::UIManager& uiManager, 
                       FlashCardDeck& deck,
                       std::function<void()> goBack);

    /**
     * @brief Updates the EditFlashcardScene.
     */
    void update() override;

    /**
     * @brief Renders the EditFlashcardScene.
     * @param window The console window.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handles input for the EditFlashcardScene.
     */
    void handleInput() override;

private:
    ConsoleUI::UIManager& m_uiManager; ///< The UI manager.
    FlashCardDeck& m_deck; ///< The flashcard deck being edited.
    std::function<void()> m_goBack; ///< Function to go back to the previous scene.
    size_t m_selectedCardIndex; ///< The index of the selected flashcard.
    int m_currentPage; ///< The current page of flashcards.
    int m_maxCardsPerPage; ///< The maximum number of flashcards per page.
    bool m_needsRedraw; ///< Flag indicating if the scene needs to be redrawn.

    /**
     * @brief Edits the selected flashcard.
     */
    void editSelectedCard();

    /**
     * @brief Adds a new flashcard to the deck.
     */
    void addNewCard();

    /**
     * @brief Deletes the selected flashcard from the deck.
     */
    void deleteSelectedCard();

    /**
     * @brief Draws wrapped text on the console window.
     * @param window The console window.
     * @param text The text to be drawn.
     * @param x The x-coordinate of the text position.
     * @param y The y-coordinate of the text position.
     * @param width The maximum width of the text.
     */
    void drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                         const std::string& text,
                         int x,
                         int y,
                         int width);
};

} // namespace FlashcardApp

#endif // EDIT_DECK_SCENE_H