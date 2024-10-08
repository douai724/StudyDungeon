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
     * @param studySettings Reference to the StudySettings object.
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

    /**
     * @brief Sets the static drawn state of the scene.
     * @param staticDrawn Boolean indicating whether the static elements have been drawn.
     */
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

    /**
     * @brief Gets the vector of loaded flashcard decks.
     * @return const std::vector<FlashCardDeck>& The vector of loaded flashcard decks.
     */
    const std::vector<FlashCardDeck>& getDecks() const {
        return m_decks;
    }

    /**
     * @brief Gets the index of the currently selected deck.
     * @return size_t The index of the currently selected deck.
     */
    size_t getSelectedDeckIndex() const {
        return m_selectedDeckIndex;
    }

    /**
     * @brief Sets the index of the currently selected deck.
     * @param index The index to set as the selected deck.
     */
    void setSelectedDeckIndex(size_t index) {
        m_selectedDeckIndex = index;
    }

    /**
     * @brief Gets the current page number for deck content display.
     * @return int The current page number.
     */
    int getCurrentPage() const {
        return m_currentPage;  
    }

    /**
     * @brief Sets the current page number for deck content display.
     * @param page The page number to set as the current page.
     */
    void setCurrentPage(int page) {
        m_currentPage = page;
    }

    /**
     * @brief Gets the maximum number of cards displayed per page.
     * @return size_t The maximum number of cards per page.
     */
    size_t getMaxCardsPerPage() const {
        return m_maxCardsPerPage;
    }

    /**
     * @brief Sets the maximum number of cards displayed per page.
     * @param maxCards The maximum number of cards to display per page.
     */
    void setMaxCardsPerPage(size_t maxCards) {
        m_maxCardsPerPage = maxCards;
    }

    /**
     * @brief Gets the flag indicating if the scene needs redrawing.
     * @return bool True if the scene needs redrawing, false otherwise.
     */
    bool getNeedsRedraw() const {
        return m_needsRedraw;
    }
    
    /**
     * @brief Sets the flag indicating if the scene needs redrawing.
     * @param needsRedraw Boolean value to set as the needs redraw flag.
     */
    void setNeedsRedraw(bool needsRedraw) {
        m_needsRedraw = needsRedraw;
    }

    /**
     * @brief Gets the study settings object.
     * @return StudySettings& Reference to the study settings object.
     */
    StudySettings& getStudySettings() {
        return m_settings;
    }

    /**
     * @brief Sets the study settings object.
     * @param settings The study settings object to set.
     */
    void setStudySettings(const StudySettings& settings) {
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
    
    bool m_staticDrawn = false;                                    ///< Flag indicating if the static elements have been drawn.
    int m_prevBookshelfIndex = -1;                                 ///< Index of the previously displayed bookshelf.
    bool m_paging = false;                                         ///< Flag indicating if paging is in progress.
    std::chrono::steady_clock::time_point m_lastPageChangeTime;    ///< Time point of the last page change.
    const std::chrono::milliseconds m_pageChangeDelay{200};        ///< Delay between page changes in milliseconds.
    int bookshelfIndex = 0;                                        ///< Index of the current bookshelf.
    StudySettings m_settings;                                      ///< Study settings object.


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
    
    /**
     * @brief Draws the librarian comment on the console window.
     */
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
     * @param studySettings Reference to the StudySettings object.
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

    /**
     * @brief Sets the static drawn state of the scene.
     * @param staticDrawn Boolean indicating whether the static elements have been drawn.
     */
    void setStaticDrawn(bool staticDrawn) override;

    /**
     * @brief Gets the flashcard deck being edited.
     * @return const FlashCardDeck& Reference to the flashcard deck.
     */
    const FlashCardDeck& getDeck() const {
        return m_deck;
    }

    /**
     * @brief Gets the index of the currently selected flashcard.
     * @return size_t The index of the currently selected flashcard.
     */
    size_t getSelectedCardIndex() const {
        return m_selectedCardIndex;
    }

    /**
     * @brief Sets the index of the currently selected flashcard.
     * @param index The index to set as the selected flashcard.
     */
    void setSelectedCardIndex(size_t index) {
        m_selectedCardIndex = index;
    }

    /**
     * @brief Gets the current page number for flashcard list display.
     * @return int The current page number.
     */
    int getCurrentPage() const {
        return m_currentPage;
    }

    /**
     * @brief Sets the current page number for flashcard list display.
     * @param page The page number to set as the current page.
     */
    void setCurrentPage(int page) {
        m_currentPage = page;
    }

    /**
     * @brief Gets the maximum number of flashcards displayed per page.
     * @return size_t The maximum number of flashcards per page.
     */
    size_t getMaxCardsPerPage() const {
        return m_maxCardsPerPage;
    }

    /**
     * @brief Sets the maximum number of flashcards displayed per page.
     * @param maxCards The maximum number of flashcards to display per page.
     */
    void setMaxCardsPerPage(size_t maxCards) {
        m_maxCardsPerPage = maxCards;
    }
    
    /**
     * @brief Gets the flag indicating if the scene needs redrawing.
     * @return bool True if the scene needs redrawing, false otherwise.
     */
    bool getNeedsRedraw() const {
        return m_needsRedraw;
    }

    /**
     * @brief Sets the flag indicating if the scene needs redrawing.
     * @param needsRedraw Boolean value to set as the needs redraw flag.
     */
    void setNeedsRedraw(bool needsRedraw) {
        m_needsRedraw = needsRedraw;
    }

    /**
     * @brief Gets the study settings object.
     * @return StudySettings& Reference to the study settings object.
     */
    StudySettings& getStudySettings() {
        return m_settings;
    }

    /**
     * @brief Sets the study settings object.
     * @param settings The study settings object to set.
     */
    void setStudySettings(const StudySettings& settings) {
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
    
    bool m_staticDrawn = false;        ///< Flag indicating if the static elements have been drawn.
    StudySettings m_settings;          ///< Study settings object.
    
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
    
    /**
     * @brief Draws the librarian comment on the console window.
     */
    void drawLibrarianComment();
};

} // namespace

#endif