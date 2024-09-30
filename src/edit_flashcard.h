/**
 * @file edit_flashcard.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDIT_DECK_SCENE_H
#define EDIT_DECK_SCENE_H

#include "deck.h"
#include "menu.h"
#include <functional>
#include <memory>
#include <vector>

namespace FlashcardEdit
{


/**
 * @class EditDeckScene
 * @brief Represents the scene for editing flashcard decks.
 *
 * This class manages the user interface for editing flashcard decks, including
 * functionality to view, add, delete, and rename decks, as well as to edit
 * individual flashcards within a deck.
 */
class EditDeckScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Constructs an EditDeckScene object.
     * @param uiManager Reference to the UIManager for handling UI operations.
     * @param goBack Function to return to the previous scene.
     * @param openEditFlashcardScene Function to open the EditFlashcardScene for a specific deck.
     */
    EditDeckScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> goBack,
                  std::function<void(FlashCardDeck &)> openEditFlashcardScene);


    void init() override;
    /**
     * @brief Updates the scene state.
     *
     * This function is called every frame to update the scene's state.
     * Currently, it doesn't perform any operations as the scene doesn't require continuous updates.
     */
    void update() override;

    /**
     * @brief Renders the scene on the console window.
     * @param window Shared pointer to the ConsoleWindow to render on.
     *
     * This function draws the list of decks, the contents of the selected deck,
     * and navigation instructions on the console window.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handles user input for the scene.
     *
     * This function processes keyboard input to navigate through decks,
     * change pages, and perform actions like adding, deleting, or renaming decks.
     */
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager;                             ///< Reference to the UI manager.
    std::function<void()> m_goBack;                                ///< Function to return to the previous scene.
    std::function<void(FlashCardDeck &)> m_openEditFlashcardScene; ///< Function to open the EditFlashcardScene.
    std::vector<FlashCardDeck> m_decks;                            ///< Vector of all loaded flashcard decks.
    size_t m_selectedDeckIndex;                                    ///< Index of the currently selected deck.
    int m_currentPage;                                             ///< Current page number for deck content display.
    int m_maxCardsPerPage;                                         ///< Maximum number of cards displayed per page.
    bool m_needsRedraw;                                            ///< Flag indicating if the scene needs redrawing.

    /**
     * @brief Loads all flashcard decks from the file system.
     *
     * This function reads all .deck files from the "Decks/" directory
     * and populates the m_decks vector with the loaded FlashCardDeck objects.
     */
    void loadDecks();

    /**
     * @brief Adds a new flashcard deck.
     *
     * This function prompts the user for a deck name, creates a new .deck file,
     * and adds the new deck to the m_decks vector.
     */
    void addNewDeck();

    /**
     * @brief Deletes the currently selected flashcard deck.
     *
     * This function removes the selected deck's .deck file from the file system
     * and removes the deck from the m_decks vector.
     */
    void deleteDeck();

    /**
     * @brief Renames the currently selected flashcard deck.
     *
     * This function prompts the user for a new deck name, renames the .deck file,
     * and updates the deck's name in the m_decks vector.
     */
    void renameDeck();
};

/**
 * @class EditFlashcardScene
 * @brief Represents the scene for editing individual flashcards within a deck.
 *
 * This class manages the user interface for editing flashcards, including
 * functionality to view, add, edit, and delete flashcards within a specific deck.
 */
class EditFlashcardScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Constructs an EditFlashcardScene object.
     * @param uiManager Reference to the UIManager for handling UI operations.
     * @param deck Reference to the FlashCardDeck being edited.
     * @param goBack Function to return to the previous scene.
     */
    EditFlashcardScene(ConsoleUI::UIManager &uiManager, FlashCardDeck &deck, std::function<void()> goBack);

    void init() override;

    /**
     * @brief Updates the scene state.
     *
     * This function is called every frame to update the scene's state.
     * Currently, it doesn't perform any operations as the scene doesn't require continuous updates.
     */
    void update() override;

    /**
     * @brief Renders the scene on the console window.
     * @param window Shared pointer to the ConsoleWindow to render on.
     *
     * This function draws the list of flashcards in the current deck,
     * displaying the question, answer, and difficulty of each card.
     * It also shows navigation instructions and handles pagination if necessary.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Handles user input for the scene.
     *
     * This function processes keyboard input to navigate through flashcards,
     * change pages, and perform actions like adding, editing, or deleting flashcards.
     */
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    FlashCardDeck &m_deck;             ///< Reference to the flashcard deck being edited.
    std::function<void()> m_goBack;    ///< Function to return to the previous scene.
    size_t m_selectedCardIndex;        ///< Index of the currently selected flashcard.
    int m_currentPage;                 ///< Current page number for flashcard list display.
    int m_maxCardsPerPage;             ///< Maximum number of flashcards displayed per page.
    bool m_needsRedraw;                ///< Flag indicating if the scene needs redrawing.

    /**
     * @brief Edits the currently selected flashcard.
     *
     * This function allows the user to modify the question, answer, and difficulty
     * of the selected flashcard. It updates the flashcard in the deck and saves
     * changes to the file.
     */
    void editSelectedCard();

    /**
     * @brief Adds a new flashcard to the deck.
     *
     * This function prompts the user for a question, answer, and difficulty level
     * for a new flashcard. It then adds the new card to the deck and saves
     * changes to the file.
     */
    void addNewCard();

    /**
     * @brief Deletes the currently selected flashcard from the deck.
     *
     * This function removes the selected flashcard from the deck after
     * confirming with the user. It then saves the changes to the file.
     */
    void deleteSelectedCard();
};

} // namespace FlashcardEdit

#endif // EDIT_DECK_SCENE_H
