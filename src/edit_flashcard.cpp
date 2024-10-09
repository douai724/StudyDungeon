/**
 * @file edit_flashcard.cpp
 * @author Green Alligators
 * @brief Functions used in the UI scene for editing flashcards
 * @version @PROJECT_VERSION@
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "edit_flashcard.h"


namespace FlashcardEdit
{


/*------EDIT FLASHCARD SCENE------*/

EditFlashcardScene::EditFlashcardScene(ConsoleUI::UIManager &uiManager,
                                       FlashCardDeck &deck,
                                       std::function<void()> goBack,
                                       StudySettings &studySettings)
    : m_uiManager(uiManager), m_deck(deck), m_goBack(goBack), m_selectedCardIndex(0), m_currentPage(0),
      m_maxCardsPerPage(0), m_needsRedraw(true), m_settings(studySettings)
{
}

void EditFlashcardScene::init()
{
    // No init needed
}

void EditFlashcardScene::update()
{
    // No continuous updates needed
}

void EditFlashcardScene::setStaticDrawn(bool staticDrawn)
{
    m_staticDrawn = staticDrawn;
}

void EditFlashcardScene::drawLibrarianComment()
{
    auto window = m_uiManager.getWindow();
    window->drawAsciiArt("lib2",
                         (window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib2")->getWidth())) - 7,
                         6);
    window->drawText(getRandomPhrase(),
                     window->getAsciiArtByName("lib2")->getX() + 34,
                     window->getAsciiArtByName("lib2")->getY() + 9);
}

void EditFlashcardScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{

    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        window->drawCenteredText("Edit Flashcards - " + m_deck.name, 2);
        window->drawAsciiArt("lib1",
                             window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib1")->getWidth()) - 7,
                             6);
        m_staticDrawn = true;
    }

    if (!m_needsRedraw)
        return;

    int cardListY = 4;
    m_maxCardsPerPage = (window->getSize().Y - cardListY - 5) / 3; // 3 lines per card, leave space for instructions
    size_t totalPages = (m_deck.cards.size() + m_maxCardsPerPage - 1) / m_maxCardsPerPage;

    // Clear the entire card list area
    for (int i = cardListY; i < window->getSize().Y - 3; ++i)
    {
        window->drawText(std::string(window->getSize().X / 2, ' '), 2, i);
    }

    window->drawText("Flashcards (Page " + std::to_string(m_currentPage + 1) + "/" + std::to_string(totalPages) + "):",
                     2,
                     cardListY - 1);

    for (size_t i = m_currentPage * m_maxCardsPerPage;
         i < min(m_deck.cards.size(), (m_currentPage + 1) * m_maxCardsPerPage);
         ++i)
    {
        const auto &card = m_deck.cards[i];
        int yOffset = cardListY + static_cast<int>((i % m_maxCardsPerPage) * 3);
        std::string prefix = (i == m_selectedCardIndex) ? "> " : "  ";
        window->drawWrappedText(prefix + "Q: " + card.question, 2, yOffset, window->getSize().X - 4);
        window->drawWrappedText("  A: " + card.answer, 2, yOffset + 1, window->getSize().X - 4);
        window->drawText("  D: " + cardDifficultyToStr(card.difficulty), 2, yOffset + 2);
        window->drawText("---", 2, yOffset + 3);
    }

    // Draw instructions
    window->drawText("Up/Down: Navigate Cards, Left/Right: Change Page, Enter: Edit Card, A: Add Card, D: Delete Card, "
                     "Esc: Back to Decks",
                     2,
                     window->getSize().Y - 2);

    m_needsRedraw = false;
}


void EditFlashcardScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();
        bool inputHandled = true;

        if (key == _arrow_prefix || key == _numlock) // Arrow key prefix
        {
            key = _getch(); // Get the actual arrow key code
            switch (key)
            {
            case _key_up: // Up arrow
                if (m_selectedCardIndex > 0)
                {
                    m_selectedCardIndex--;
                    m_needsRedraw = true;
                }
                break;
            case _key_down: // Down arrow
                if (m_selectedCardIndex < m_deck.cards.size() - 1)
                {
                    m_selectedCardIndex++;
                    m_needsRedraw = true;
                }
                break;
            case _key_left: // Left arrow
                if (m_currentPage > 0)
                {
                    m_currentPage--;
                    m_selectedCardIndex = m_currentPage * m_maxCardsPerPage;

                    m_needsRedraw = true;
                }
                break;
            case _key_right: // Right arrow
            {
                size_t totalPages = (m_deck.cards.size() + m_maxCardsPerPage - 1) / m_maxCardsPerPage;
                if (m_currentPage < totalPages - 1)
                {
                    m_currentPage++;
                    m_selectedCardIndex = m_currentPage * m_maxCardsPerPage;

                    m_needsRedraw = true;
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
            case _key_enter: // Enter
                if (!m_deck.cards.empty())
                    editSelectedCard();
                break;
            case 'A':
            case 'a':
                addNewCard();
                break;
            case 'D':
            case 'd':
                deleteSelectedCard();
                break;
            case _key_esc: // Esc
                m_goBack();
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

void EditFlashcardScene::editSelectedCard()
{
    if (m_selectedCardIndex >= m_deck.cards.size())
        return;

    auto &card = m_deck.cards[m_selectedCardIndex];
    auto window = m_uiManager.getWindow();
    m_staticDrawn = false;
    window->clear();
    window->drawBorder();
    int lib1_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib1")->getWidth());
    int lib2_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib2")->getWidth());
    window->drawAsciiArt("lib1", lib1_x_pos - 7, 6);
    window->drawCenteredText("Edit Flashcard", 2);

    // Display current card info
    window->drawText("Editing card " + std::to_string(m_selectedCardIndex + 1) + " of " +
                         std::to_string(m_deck.cards.size()),
                     2,
                     4);
    window->drawText("----------------------------------------", 2, 5);

    // Edit question
    window->drawText("Current question: " + card.question, 2, 7);
    window->drawText("Enter new question (or press Enter to keep current, Esc to abort):", 2, 8);
    std::string newQuestion =
        window->getLine(2, 9, (window->getSize().X - window->getAsciiArtByName("lib2")->getWidth()) - 10);
    if (newQuestion == "\x1B") // Esc key
    {
        window->drawText("Editing aborted. Press any key to continue...", 2, 11);
        drawLibrarianComment();
        _getch();
        m_needsRedraw = true;
        return;
    }
    if (!newQuestion.empty())
        card.question = newQuestion;

    // Edit answer
    window->drawText("Current answer: " + card.answer, 2, 11);
    window->drawText("Enter new answer (or press Enter to keep current, Esc to abort):", 2, 12);
    std::string newAnswer =
        window->getLine(2, 13, (window->getSize().X - window->getAsciiArtByName("lib2")->getWidth()) - 10);
    if (newAnswer == "\x1B") // Esc key
    {
        window->drawText("Editing aborted. Press any key to continue...", 2, 15);
        drawLibrarianComment();
        _getch();
        m_needsRedraw = true;
        return;
    }
    if (!newAnswer.empty())
        card.answer = newAnswer;


    //Save changes to file
    writeFlashCardDeckWithChecks(m_deck, m_deck.filename, true);

    window->drawText("Card updated successfully!", 2, 21);
    window->drawText("Press any key to continue...", 2, 22);
    drawLibrarianComment();

    _getch(); // Wait for a key press

    m_needsRedraw = true;
}

void EditFlashcardScene::addNewCard()
{
    auto window = m_uiManager.getWindow();
    m_staticDrawn = false;
    window->clear();
    window->drawBorder();
    int lib1_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib1")->getWidth());
    int lib2_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib2")->getWidth());
    window->drawAsciiArt("lib1", lib1_x_pos - 7, 6);
    window->drawCenteredText("Add New Card", 2);

    FlashCard newCard;

    window->drawText("Enter the question:", 2, 4);
    newCard.question = window->getLine(2, 6, lib2_x_pos - 10);
    if (newCard.question == "\x1B") // Esc key
    {
        window->drawText("Editing aborted. Press any key to continue...", 2, 19);
        drawLibrarianComment();

        _getch();
        m_needsRedraw = true;
        return;
    }

    window->drawText("Enter the answer:", 2, 8);
    newCard.answer = window->getLine(2, 10, lib2_x_pos - 10);
    if (newCard.answer == "\x1B") // Esc key
    {
        window->drawText("Editing aborted. Press any key to continue...", 2, 19);
        drawLibrarianComment();

        _getch();
        m_needsRedraw = true;
        return;
    }


    newCard.difficulty = UNKNOWN;

    newCard.n_times_answered = 0;

    m_deck.cards.push_back(newCard);

    // Write the updated deck to the file
    if (writeFlashCardDeckWithChecks(m_deck, m_deck.filename, true))
    {
        window->drawText("New card added successfully!", 2, 16);
        drawLibrarianComment();
    }
    else
    {
        window->drawText("Failed to update the deck file.", 2, 16);
        drawLibrarianComment();
    }

    window->drawText("Press any key to continue...", 2, 18);
    _getch();

    m_needsRedraw = true;
}

void EditFlashcardScene::deleteSelectedCard()
{
    if (m_deck.cards.empty())
        return;

    auto window = m_uiManager.getWindow();
    m_staticDrawn = false;
    window->clear();
    window->drawBorder();
    window->drawCenteredText("Delete Card", 2);
    int lib1_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib1")->getWidth());
    int lib2_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib2")->getWidth());
    window->drawAsciiArt("lib1", lib1_x_pos - 7, 6);

    window->drawText("Are you sure you want to delete the selected card? (Y/N)", 2, 4);
    int key = _getch();
    if (key == 'Y' || key == 'y')
    {
        m_deck.cards.erase(m_deck.cards.begin() + m_selectedCardIndex);
        if (m_selectedCardIndex >= m_deck.cards.size())
            m_selectedCardIndex = m_deck.cards.size() - 1;

        // Write the updated deck to the file

        if (writeFlashCardDeckWithChecks(m_deck, m_deck.filename, true))
        {
            window->drawText("Card deleted successfully!", 2, 6);
            drawLibrarianComment();
        }
        else
        {
            window->drawText("Failed to update the deck file.", 2, 6);
            drawLibrarianComment();
        }
    }
    else
    {
        window->drawText("Card deletion canceled.", 2, 6);
        drawLibrarianComment();
    }

    window->drawText("Press any key to continue...", 2, 8);
    _getch();

    m_needsRedraw = true;
}


/*------EDIT DECK SCENE------*/

EditDeckScene::EditDeckScene(ConsoleUI::UIManager &uiManager,
                             std::function<void()> goBack,
                             std::function<void(FlashCardDeck &)> openEditFlashcardScene,
                             StudySettings &studySettings)
    : m_uiManager(uiManager), m_goBack(goBack), m_openEditFlashcardScene(openEditFlashcardScene),
      m_selectedDeckIndex(0), m_needsRedraw(true), m_currentPage(0), m_maxCardsPerPage(0), m_settings(studySettings)
{
    loadDecks();
}

void EditDeckScene::loadDecks()
{
    m_decks = loadFlashCardDecks(m_settings.getDeckDir());
    m_selectedDeckIndex = 0;
    m_currentPage = 0;
    m_needsRedraw = true;
}

void EditDeckScene::init()
{
    // No init needed
}


void EditDeckScene::update()
{
    // No continuous updates needed
}

void EditDeckScene::setStaticDrawn(bool staticDrawn)
{
    m_staticDrawn = staticDrawn;
}

void EditDeckScene::drawBookshelf(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
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

void EditDeckScene::drawLibrarianComment()
{
    auto window = m_uiManager.getWindow();
    window->drawAsciiArt("lib2",
                         (window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib2")->getWidth())) - 7,
                         6);
    window->drawText(getRandomPhrase(),
                     window->getAsciiArtByName("lib2")->getX() + 34,
                     window->getAsciiArtByName("lib2")->getY() + 9);
}

void EditDeckScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    int deckListY = 4;
    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        window->drawCenteredText("Edit Decks", 2);

        m_staticDrawn = true;
    }

    if (!m_needsRedraw)
        return;


    // Clear the deck list area
    for (int i = deckListY; i < window->getSize().Y - 2; ++i)
    {
        window->drawText(std::string(window->getSize().X - 4, ' '), 2, i);
    }
    // Draw deck list
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
    window->drawText(
        "Up/Down: Navigate Decks, Enter: Edit Deck, A: Add Deck, D: Delete Deck, R: Rename Deck, Escape: Go Back",
        2,
        window->getSize().Y - 2);

    m_needsRedraw = false;
}

void EditDeckScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();
        bool inputHandled = true;

        if (key == _arrow_prefix || key == 0)
        {                   // Arrow key prefix
            key = _getch(); // Get the actual arrow key code
            switch (key)
            {
            case _key_up: // Up arrow
                if (m_selectedDeckIndex > 0)
                {
                    m_selectedDeckIndex--;
                    m_currentPage = 0;
                    m_paging = true;
                    m_needsRedraw = true;
                }
                break;
            case _key_down: // Down arrow
                if (m_selectedDeckIndex < m_decks.size() - 1)
                {
                    m_selectedDeckIndex++;
                    m_currentPage = 0;
                    m_paging = true;
                    m_needsRedraw = true;
                }
                break;
            case _key_left: // Left arrow
                if (m_currentPage > 0 && std::chrono::steady_clock::now() - m_lastPageChangeTime >= m_pageChangeDelay)
                {
                    m_currentPage--;
                    m_paging = false;
                    m_needsRedraw = true;
                    m_lastPageChangeTime = std::chrono::steady_clock::now();
                }
                break;
            case _key_right: // Right arrow
                if (!m_decks.empty() && std::chrono::steady_clock::now() - m_lastPageChangeTime >= m_pageChangeDelay)
                {
                    const auto &selectedDeck = m_decks[m_selectedDeckIndex];
                    size_t totalPages =
                        (static_cast<int>(selectedDeck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;
                    if (m_currentPage < totalPages - 1)
                    {
                        m_currentPage++;
                        m_paging = false;
                        m_needsRedraw = true;
                        m_lastPageChangeTime = std::chrono::steady_clock::now();
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
            case _key_enter: // Enter
                if (!m_decks.empty())
                {
                    m_needsRedraw = true;
                    m_openEditFlashcardScene(m_decks[m_selectedDeckIndex]);
                }
                break;
            case 'A':
            case 'a':
                addNewDeck();
                m_needsRedraw = true;
                break;
            case 'D':
            case 'd':
                deleteDeck();
                m_needsRedraw = true;
                break;
            case 'R':
            case 'r':
                renameDeck();
                m_needsRedraw = true;
                break;
            case _key_esc:
                m_needsRedraw = true;
                m_goBack();

                break;
            default:
                inputHandled = false;
            }
        }
    }
}

void EditDeckScene::addNewDeck()
{
    auto window = m_uiManager.getWindow();
    window->clear();
    window->drawBorder();
    window->drawCenteredText("Add New Deck", 2);
    int lib1_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib1")->getWidth());
    int lib2_x_pos = window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib2")->getWidth());
    window->drawAsciiArt("lib1", lib1_x_pos - 7, 6);

    window->drawText("Enter the name for the new deck (max 30 characters):", 2, 4);
    std::string deckName = window->getLine(2, 6, 30);

    if (deckName == "\x1B") // Esc key
    {
        window->drawText("Editing aborted. Press any key to continue...", 2, 19);
        drawLibrarianComment();

        _getch();
        m_needsRedraw = true;
        return;
    }

    // Replace spaces with underscores in the filename
    std::string deckFilename = deckName;
    std::replace(deckFilename.begin(), deckFilename.end(), ' ', '_');

    fs::path deckPath = "Decks/" + deckFilename + ".deck";
    FlashCardDeck newDeck{deckName, "", std::vector<FlashCard>{}};
    newDeck.filename = deckPath;
    writeFlashCardDeckWithChecks(newDeck, deckPath, false);
    m_decks.push_back(newDeck);

    // select this deck
    m_selectedDeckIndex = (int)m_decks.size() - 1;

    window->drawText("New deck added successfully!", 2, 6);
    drawLibrarianComment();

    window->drawText("Press any key to continue...", 2, 10);
    _getch();

    m_needsRedraw = true;
}

void EditDeckScene::deleteDeck()
{
    if (m_decks.empty())
        return;

    auto window = m_uiManager.getWindow();
    window->clear();
    window->drawBorder();
    window->drawCenteredText("Delete Deck", 2);
    int lib1_x_pos =
        window->getSize().X -
        static_cast<int>(
            window->getAsciiArtByName("lib1")
                ->getWidth()); //TODO these variables are repeated a lot in this file, could chuck em at the
    int lib2_x_pos =
        window->getSize().X -
        static_cast<int>(window->getAsciiArtByName("lib2")->getWidth()); // top of the file or in the header somewhere
    window->drawAsciiArt("lib1", lib1_x_pos - 7, 6);

    window->drawText("Are you sure you want to delete the deck '" + m_decks[m_selectedDeckIndex].name + "'?", 2, 4);
    window->drawText("Type \"delete\" and press enter to confirm.", 2, 5);
    std::string key = window->getLine(2, 6, 6);
    if (key == "delete")
    {
        fs::remove(m_decks[m_selectedDeckIndex].filename);
        m_decks.erase(m_decks.begin() + m_selectedDeckIndex);
        if (m_selectedDeckIndex >= m_decks.size())
            m_selectedDeckIndex = m_decks.size() - 1;

        drawLibrarianComment();
        window->drawText("Deck deleted successfully!", 2, 6);
    }
    else
    {
        drawLibrarianComment();
        window->drawText("Deck deletion canceled.", 2, 6);
    }

    window->drawText("Press any key to continue...", 2, 8);
    _getch();

    m_needsRedraw = true;
}

void EditDeckScene::renameDeck()
{
    if (m_decks.empty())
        return;

    auto window = m_uiManager.getWindow();
    window->clear();
    window->drawBorder();
    window->drawCenteredText("Rename Deck", 2);
    window->drawAsciiArt("lib1",
                         (window->getSize().X - static_cast<int>(window->getAsciiArtByName("lib1")->getWidth())) - 7,
                         6);

    window->drawText("Enter the new name for the deck '" + m_decks[m_selectedDeckIndex].name + "' (max 30 characters):",
                     2,
                     4);
    std::string newDeckName = window->getLine(2, 6, 30);
    if (newDeckName == "\x1B") // Esc key
    {
        window->drawText("Renaming aborted. Press any key to continue...", 2, 19);
        drawLibrarianComment();

        _getch();
        m_needsRedraw = true;
        return;
    }

    // Replace spaces with underscores in the filename
    std::string newDeckFilename = newDeckName;
    std::replace(newDeckFilename.begin(), newDeckFilename.end(), ' ', '_');

    fs::path oldFilename = m_decks[m_selectedDeckIndex].filename;
    fs::path newFilename = oldFilename.parent_path() / (newDeckFilename + ".deck");
    fs::rename(oldFilename, newFilename);
    m_decks[m_selectedDeckIndex].name = newDeckName;
    m_decks[m_selectedDeckIndex].filename = newFilename;
    window->drawText("Deck renamed successfully!", 2, 8);
    drawLibrarianComment();

    window->drawText("Press any key to continue...", 2, 10);
    _getch();

    m_needsRedraw = true;
}


} // namespace FlashcardEdit
