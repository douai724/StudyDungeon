/**
 * @file edit_flashcard.h
 * @author your name (you@domain.com)
 * @brief Classes and functions that are used in the UI scene for editing flashcards
 * @version @PROJECT_VERSION@
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef EDIT_DECK_SCENE_H
#define EDIT_DECK_SCENE_H

#include "artwork.h"
#include "deck.h"
#include "menu.h"
#include "settings_scene.h"
#include "util.h"
#include <algorithm>
#include <conio.h>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
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
                  std::function<void(FlashCardDeck &)> openEditFlashcardScene,
                  StudySettings &studySettings);


    /**
     * @brief Initialises the scene
     *
     */
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

    void setStaticDrawn(bool staticDrawn) override;

    /**
     * @brief Draws the books shelf art
     *
     * @param window The console window to add the bookshelf art to
     */
    void drawBookshelf(std::shared_ptr<ConsoleUI::ConsoleWindow> window);

    /**
     * @brief Loads all flashcard decks from the file system.
     *
     * This function reads all .deck files from the "Decks/" directory
     * and populates the m_decks vector with the loaded FlashCardDeck objects.
     */
    void loadDecks();

    const std::vector<FlashCardDeck> &getDecks() const
    {
        return m_decks;
    }

    size_t getSelectedDeckIndex() const
    {
        return m_selectedDeckIndex;
    }

    void setSelectedDeckIndex(size_t index)
    {
        m_selectedDeckIndex = index;
    }

    int getCurrentPage() const
    {
        return m_currentPage;
    }

    void setCurrentPage(int page)
    {
        m_currentPage = page;
    }

    size_t getMaxCardsPerPage() const
    {
        return m_maxCardsPerPage;
    }

    void setMaxCardsPerPage(size_t maxCards)
    {
        m_maxCardsPerPage = maxCards;
    }

    bool getNeedsRedraw() const
    {
        return m_needsRedraw;
    }

    void setNeedsRedraw(bool needsRedraw)
    {
        m_needsRedraw = needsRedraw;
    }

    StudySettings &getStudySettings()
    {
        return m_settings;
    }

    void setStudySettings(const StudySettings &settings)
    {
        m_settings = settings;
    }

private:
    ConsoleUI::UIManager &m_uiManager;                             ///< Reference to the UI manager.
    std::function<void()> m_goBack;                                ///< Function to return to the previous scene.
    std::function<void(FlashCardDeck &)> m_openEditFlashcardScene; ///< Function to open the EditFlashcardScene.
    std::vector<FlashCardDeck> m_decks;                            ///< Vector of all loaded flashcard decks.
    size_t m_selectedDeckIndex;                                    ///< Index of the currently selected deck.
    int m_currentPage;                                             ///< Current page number for deck content display.
    size_t m_maxCardsPerPage;                                      ///< Maximum number of cards displayed per page.
    bool m_needsRedraw;                                            ///< Flag indicating if the scene needs redrawing.

    bool m_staticDrawn = false;
    int m_prevBookshelfIndex = -1;
    bool m_paging = false;
    std::chrono::steady_clock::time_point m_lastPageChangeTime;
    const std::chrono::milliseconds m_pageChangeDelay{200};
    int bookshelfIndex = 0;
    StudySettings m_settings;


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

    //TODO comment
    void drawLibrarianComment();
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
    EditFlashcardScene(ConsoleUI::UIManager &uiManager,
                       FlashCardDeck &deck,
                       std::function<void()> goBack,
                       StudySettings &studySettings);

    /**
     * @brief Initialises the scene
     *
     */
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

    void setStaticDrawn(bool staticDrawn) override;

    const FlashCardDeck &getDeck() const
    {
        return m_deck;
    }

    size_t getSelectedCardIndex() const
    {
        return m_selectedCardIndex;
    }

    void setSelectedCardIndex(size_t index)
    {
        m_selectedCardIndex = index;
    }

    int getCurrentPage() const
    {
        return m_currentPage;
    }

    void setCurrentPage(int page)
    {
        m_currentPage = page;
    }

    size_t getMaxCardsPerPage() const
    {
        return m_maxCardsPerPage;
    }

    void setMaxCardsPerPage(size_t maxCards)
    {
        m_maxCardsPerPage = maxCards;
    }

    bool getNeedsRedraw() const
    {
        return m_needsRedraw;
    }

    void setNeedsRedraw(bool needsRedraw)
    {
        m_needsRedraw = needsRedraw;
    }

    StudySettings &getStudySettings()
    {
        return m_settings;
    }

    void setStudySettings(const StudySettings &settings)
    {
        m_settings = settings;
    }

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    FlashCardDeck &m_deck;             ///< Reference to the flashcard deck being edited.
    std::function<void()> m_goBack;    ///< Function to return to the previous scene.
    size_t m_selectedCardIndex;        ///< Index of the currently selected flashcard.
    int m_currentPage;                 ///< Current page number for flashcard list display.
    size_t m_maxCardsPerPage;          ///< Maximum number of flashcards displayed per page.
    bool m_needsRedraw;                ///< Flag indicating if the scene needs redrawing.

    bool m_staticDrawn = false;
    StudySettings m_settings;

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

    //TODO comment
    void drawLibrarianComment();
};

} // namespace FlashcardEdit

#endif // EDIT_DECK_SCENE_H
