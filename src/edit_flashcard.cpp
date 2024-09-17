#include "edit_flashcard.h"
#include <iostream>
#include <conio.h>
#include "util.h"
#include <algorithm>
#include <sstream>
#include <limits>

namespace FlashcardEdit {

/*------EDIT FLASHCARD SCENE------*/

EditFlashcardScene::EditFlashcardScene(ConsoleUI::UIManager& uiManager, 
                                       FlashCardDeck& deck,
                                       std::function<void()> goBack)
    : m_uiManager(uiManager), m_deck(deck), m_goBack(goBack), 
      m_selectedCardIndex(0), m_currentPage(0), m_maxCardsPerPage(0), m_needsRedraw(true)
{
    // No need to create a menu here, we'll handle navigation directly
}

void EditFlashcardScene::update()
{
    // No continuous updates needed
}

void EditFlashcardScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_needsRedraw) return;

    window->clear();
    window->drawBorder();
    window->drawCenteredText("Edit Flashcards - " + m_deck.name, 2);

    int cardListY = 4;
    m_maxCardsPerPage = (window->getSize().Y - cardListY - 5) / 3; // 3 lines per card, leave space for instructions
    int totalPages = (static_cast<int>(m_deck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;

    window->drawText("Flashcards (Page " + std::to_string(m_currentPage + 1) + "/" + std::to_string(totalPages) + "):", 2, cardListY - 1);

    for (size_t i = m_currentPage * m_maxCardsPerPage;
         i < min(m_deck.cards.size(), (m_currentPage + 1) * m_maxCardsPerPage);
         ++i)
    {
        const auto& card = m_deck.cards[i];
        int yOffset = cardListY + ((i % m_maxCardsPerPage) * 3);
        std::string prefix = (i == m_selectedCardIndex) ? "> " : "  ";
        drawWrappedText(window, prefix + "Q: " + card.question, 2, yOffset, window->getSize().X - 4);
        drawWrappedText(window, "  A: " + card.answer, 2, yOffset + 1, window->getSize().X - 4);
        window->drawText("  D: " + cardDifficultyToStr(card.difficulty), 2, yOffset + 2);
    }

    // Draw instructions
    window->drawText("Up/Down: Navigate Cards, Left/Right: Change Page, Enter: Edit Card, A: Add Card, D: Delete Card, Esc: Back to Decks", 2, window->getSize().Y - 2);

    m_needsRedraw = false;
}

void EditFlashcardScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();
        bool inputHandled = true;

        if (key == 224) // Arrow key prefix
        {
            key = _getch(); // Get the actual arrow key code
            switch (key)
            {
            case 72: // Up arrow
                if (m_selectedCardIndex > 0)
                    m_selectedCardIndex--;
                break;
            case 80: // Down arrow
                if (m_selectedCardIndex < m_deck.cards.size() - 1)
                    m_selectedCardIndex++;
                break;
            case 75: // Left arrow
                if (m_currentPage > 0)
                    m_currentPage--;
                break;
            case 77: // Right arrow
                {
                    int totalPages = (static_cast<int>(m_deck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;
                    if (m_currentPage < totalPages - 1)
                        m_currentPage++;
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
            case 13: // Enter
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
            case 27: // Esc
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
    if (m_selectedCardIndex >= m_deck.cards.size()) return;

    auto& card = m_deck.cards[m_selectedCardIndex];
    
    // Clear the screen
    clearScreen();
    
    std::cout << "Editing card " << m_selectedCardIndex + 1 << " of " << m_deck.cards.size() << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // Edit question
    std::cout << "Current question: " << card.question << std::endl;
    std::cout << "Enter new question (or press Enter to keep current): ";
    std::string newQuestion;
    std::getline(std::cin, newQuestion);
    if (!newQuestion.empty()) card.question = newQuestion;

    std::cout << std::endl;

    // Edit answer
    std::cout << "Current answer: " << card.answer << std::endl;
    std::cout << "Enter new answer (or press Enter to keep current): ";
    std::string newAnswer;
    std::getline(std::cin, newAnswer);
    if (!newAnswer.empty()) card.answer = newAnswer;

    std::cout << std::endl;

    // Edit difficulty
    std::cout << "Current difficulty: " << cardDifficultyToStr(card.difficulty) << std::endl;
    std::cout << "Enter new difficulty (0: Easy, 1: Medium, 2: Hard, or press Enter to keep current): ";
    std::string newDifficultyStr;
    std::getline(std::cin, newDifficultyStr);
    if (!newDifficultyStr.empty()) {
        try {
            int newDifficulty = std::stoi(newDifficultyStr);
            if (newDifficulty >= 0 && newDifficulty <= 2) {
                card.difficulty = static_cast<CardDifficulty>(newDifficulty);
            } else {
                std::cout << "Invalid difficulty. Keeping current difficulty." << std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Keeping current difficulty." << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Card updated successfully!" << std::endl;
    std::cout << "Press any key to continue...";
    _getch(); // Wait for a key press

    // Save changes to file
    //saveFlashCardDeck(m_deck, "Decks/" + m_deck.name + ".deck");
    
    m_needsRedraw = true;
}

void EditFlashcardScene::addNewCard()
{
}

void EditFlashcardScene::deleteSelectedCard()
{
}

void EditFlashcardScene::drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                                         const std::string& text,
                                         int x,
                                         int y,
                                         int width)
{
    std::istringstream words(text);
    std::string word;
    std::string line;
    int currentY = y;

    while (words >> word)
    {
        if (line.length() + word.length() + 1 > width)
        {
            window->drawText(line, x, currentY++);
            line = word + " ";
        }
        else
        {
            line += word + " ";
        }
    }

    if (!line.empty())
    {
        window->drawText(line, x, currentY);
    }
}

/*------EDIT DECK SCENE------*/

EditDeckScene::EditDeckScene(ConsoleUI::UIManager& uiManager, 
                             std::function<void()> goBack,
                             std::function<void(FlashCardDeck&)> openEditFlashcardScene)
    : m_uiManager(uiManager), m_goBack(goBack), m_openEditFlashcardScene(openEditFlashcardScene),
      m_selectedDeckIndex(0), m_needsRedraw(true), m_currentPage(0), m_maxCardsPerPage(0)
{
    loadDecks();
}

void EditDeckScene::loadDecks()
{
    m_decks = loadFlashCardDecks("Decks/");
    m_selectedDeckIndex = 0;
    m_currentPage = 0;
    m_needsRedraw = true;
}

void EditDeckScene::update()
{
    // No continuous updates needed
}

void EditDeckScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_needsRedraw) return;

    window->clear();
    window->drawBorder();
    window->drawCenteredText("Edit Decks", 2);

    // Draw deck list
    int deckListY = 4;
    for (size_t i = 0; i < m_decks.size(); ++i)
    {
        std::string deckText = (i == m_selectedDeckIndex ? "> " : "  ") + m_decks[i].name;
        window->drawText(deckText, 2, deckListY + static_cast<int>(i));
    }

    // Draw selected deck contents with paging
    if (!m_decks.empty())
    {
        const auto& selectedDeck = m_decks[m_selectedDeckIndex];
        int cardListX = window->getSize().X / 2;
        int cardListY = 4;
        m_maxCardsPerPage = (window->getSize().Y - cardListY - 5) / 5; // 5 lines per card, leave space for instructions
        int totalPages = (static_cast<int>(selectedDeck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;

        window->drawText("Deck Contents (Page " + std::to_string(m_currentPage + 1) + "/" + std::to_string(totalPages) + "):",
                         cardListX,
                         cardListY - 1);

        for (size_t i = m_currentPage * m_maxCardsPerPage;
             i < min(selectedDeck.cards.size(), (m_currentPage + 1) * m_maxCardsPerPage);
             ++i)
        {
            const auto& card = selectedDeck.cards[i];
            int yOffset = cardListY + (i % m_maxCardsPerPage) * 5;
            drawWrappedText(window, "Q: " + card.question, cardListX, yOffset, window->getSize().X - cardListX - 2);
            drawWrappedText(window, "A: " + card.answer, cardListX, yOffset + 2, window->getSize().X - cardListX - 2);
            window->drawText("D: " + cardDifficultyToStr(card.difficulty), cardListX, yOffset + 4);
        }

        window->drawText("Use Left/Right arrows to change pages", cardListX, window->getSize().Y - 3);
    }

    // Draw instructions
    window->drawText("Up/Down: Navigate Decks, Enter: Edit Deck, A: Add Deck, D: Delete Deck, R: Rename Deck, Backspace: Go Back", 2, window->getSize().Y - 2);

    m_needsRedraw = false;
}

void EditDeckScene::handleInput()
{
    if (_kbhit())
    {
        int key = _getch();
        bool inputHandled = true;

        if (key == 224)
        { // Arrow key prefix
            key = _getch(); // Get the actual arrow key code
            switch (key)
            {
            case 72: // Up arrow
                if (m_selectedDeckIndex > 0)
                    m_selectedDeckIndex--;
                break;
            case 80: // Down arrow
                if (m_selectedDeckIndex < m_decks.size() - 1)
                    m_selectedDeckIndex++;
                break;
            case 75: // Left arrow
                if (m_currentPage > 0)
                    m_currentPage--;
                break;
            case 77: // Right arrow
                if (!m_decks.empty())
                {
                    const auto& selectedDeck = m_decks[m_selectedDeckIndex];
                    int totalPages = (static_cast<int>(selectedDeck.cards.size()) + m_maxCardsPerPage - 1) / m_maxCardsPerPage;
                    if (m_currentPage < totalPages - 1)
                        m_currentPage++;
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
            case 13: // Enter
                if (!m_decks.empty())
                {
                    m_openEditFlashcardScene(m_decks[m_selectedDeckIndex]);
                }
                break;
            case 'A':
            case 'a':
                addNewDeck();
                break;
            case 'D':
            case 'd':
                deleteDeck();
                break;
            case 'R':
            case 'r':
                renameDeck();
                break;
            case 8: // Backspace
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

void EditDeckScene::addNewDeck() 
{
}

void EditDeckScene::deleteDeck()
{
}

void EditDeckScene::renameDeck()
{
}

void EditDeckScene::drawWrappedText(std::shared_ptr<ConsoleUI::ConsoleWindow> window,
                                    const std::string& text,
                                    int x,
                                    int y,
                                    int width)
{
    std::istringstream words(text);
    std::string word;
    std::string line;
    int currentY = y;

    while (words >> word)
    {
        if (line.length() + word.length() + 1 > width)
        {
            window->drawText(line, x, currentY++);
            line = word + " ";
        }
        else
        {
            line += word + " ";
        }
    }

    if (!line.empty())
    {
        window->drawText(line, x, currentY);
    }
}

} // namespace FlashcardEdit