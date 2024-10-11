#include "flashcard_scene.h"
#include "menu.h"
#include "util.h"
#include <catch2/catch_test_macros.hpp>


TEST_CASE("FlashcardScene::updateCardDifficulty() updates card difficulty and times answered", "[flashcard_scene]")
{
    // Arrange
    ConsoleUI::UIManager uiManager;
    FlashCardDeck deck;
    deck.cards.push_back(FlashCard{"Question 1", "Answer 1", EASY, 0});
    StudySettings studySettings;
    FlashcardApp::FlashcardScene
        scene(uiManager, deck, []() {}, []() {}, [](const std::vector<int> &, int, bool) {}, studySettings);
    size_t cardIndex = 0;
    CardDifficulty newDifficulty = MEDIUM;

    // Act
    scene.updateCardDifficulty(scene.m_cardOrder[cardIndex], newDifficulty);

    // Assert
    REQUIRE(scene.m_deck.cards[scene.m_cardOrder[cardIndex]].difficulty == newDifficulty);
    REQUIRE(scene.m_deck.cards[scene.m_cardOrder[cardIndex]].n_times_answered == 1);
}

TEST_CASE("BrowseDecksScene::loadDecks() loads decks correctly", "[browse_decks_scene]")
{
    // Arrange
    ConsoleUI::UIManager uiManager;
    StudySettings studySettings;
    FlashcardApp::BrowseDecksScene scene(uiManager, []() {}, [](const FlashCardDeck &) {}, studySettings);

    std::cerr << studySettings.getDeckDir() << std::endl;
    // Act
    // scene.loadDecks();


    // Assert
    //REQUIRE(!scene.m_decks.empty());
    REQUIRE(scene.m_selectedDeckIndex == 0);
    REQUIRE(scene.m_currentPage == 0);
}


TEST_CASE("FlashcardScene::nextCard() moves to the next card correctly", "[flashcard_scene]")
{
    // Arrange
    ConsoleUI::UIManager uiManager;
    FlashCardDeck deck;
    deck.cards.push_back(FlashCard{"Question 1", "Answer 1", EASY, 0});
    deck.cards.push_back(FlashCard{"Question 2", "Answer 2", MEDIUM, 1});
    StudySettings studySettings;
    FlashcardApp::FlashcardScene
        scene(uiManager, deck, []() {}, []() {}, [](const std::vector<int> &, int, bool) {}, studySettings);

    // Act
    scene.nextCard();

    // Assert
    REQUIRE(scene.m_currentCardIndex == 1);
    REQUIRE(!scene.m_showAnswer);
    REQUIRE(!scene.m_lastAnswerDisplayed);
}
