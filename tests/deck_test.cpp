#include "deck.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>


struct cout_redirect
{
    cout_redirect(std::streambuf *new_buffer) : old(std::cout.rdbuf(new_buffer))
    {
    }

    ~cout_redirect()
    {
        std::cout.rdbuf(old);
    }

private:
    std::streambuf *old;
};

TEST_CASE("deck_h enum converters")
{
    REQUIRE(strToCardDifficulty("") == UNKNOWN);
    REQUIRE(strToCardDifficulty("SOMETHING") == UNKNOWN);
    REQUIRE(strToCardDifficulty("UNKNOWN") == UNKNOWN);
    REQUIRE(strToCardDifficulty("EASY") == EASY);
    REQUIRE(strToCardDifficulty("MEDIUM") == MEDIUM);
    REQUIRE(strToCardDifficulty("HIGH") == HIGH);

    REQUIRE(cardDifficultyToStr(UNKNOWN) == "UNKNOWN");
    REQUIRE(cardDifficultyToStr(EASY) == "EASY");
    REQUIRE(cardDifficultyToStr(MEDIUM) == "MEDIUM");
    REQUIRE(cardDifficultyToStr(HIGH) == "HIGH");
}

TEST_CASE("FlashCard Creation")
{
    SECTION("Initialise object")
    {
        FlashCard fc{};
        REQUIRE(fc.question == "");
        REQUIRE(fc.answer == "");
        REQUIRE(fc.difficulty == UNKNOWN);
        REQUIRE(fc.n_times_answered == 0);

        FlashCard fc1 = FlashCard("question", "answer", MEDIUM, 1);
        REQUIRE(fc1.question == "question");
        REQUIRE(fc1.answer == "answer");
        REQUIRE(fc1.difficulty == MEDIUM);
        REQUIRE(fc1.n_times_answered == 1);
    }


    SECTION("Card printing methods")
    {
        FlashCard fc{};
        auto stdoutBuffer = std::cout.rdbuf();
        std::ostringstream oss;
        std::cout.rdbuf(oss.rdbuf());

        fc.printCard();
        REQUIRE(oss.str() == "\n\n\n");
        // clear out the buffer ready to take next output
        oss.str("");
        oss.clear();

        fc.printCardAsTemplate();
        REQUIRE(oss.str() == "Q: \nA: \nD: UNKNOWN\nN: 0\n-\n");
        // clear out the buffer ready to take next output
        oss.str("");
        oss.clear();
        FlashCard fc_test = FlashCard("question", "answer", MEDIUM, 1);
        fc_test.printCardAsTemplate();
        REQUIRE(oss.str() == "Q: question\nA: answer\nD: MEDIUM\nN: 1\n-\n");

        std::cout.rdbuf(stdoutBuffer); // reset to original std::cout buffer
    }
}

TEST_CASE("Deck reading and writing")
{

    FlashCard fc_test0 = FlashCard("question0", "answer0", MEDIUM, 1);
    FlashCard fc_test1 = FlashCard("question1", "answer1", MEDIUM, 1);

    // empty deck
    FlashCardDeck d0{"Example Deck 0", "", std::vector<FlashCard>{}};

    std::vector<FlashCardDeck> example_decks = createExampleDecks();
    example_decks.emplace(example_decks.begin(), d0);
    SECTION("Deck file names")
    {
        // createDeckFilename();
    }

    SECTION("writing")
    {
        std::filesystem::path app_path = getAppPath();
        std::filesystem::path decks_dir = app_path;
        decks_dir.append("TEST_Decks");
        std::filesystem::path new_deck = decks_dir;
        new_deck.append("new.deck");
        // std::cerr << "new deck path:" << new_deck << std::endl;

        if (std::filesystem::exists(new_deck))
        {
            std::cerr << "REMOVING FILE TEST_decks/new.deck" << std::endl;
            std::filesystem::remove(new_deck);
        }
        REQUIRE(writeFlashCardDeckWithChecks(example_decks.at(1), new_deck, false));
        // force overwrite
        REQUIRE(writeFlashCardDeck(example_decks.at(1), new_deck));
    }

    SECTION("reading")
    {
        std::filesystem::path app_path = getAppPath();
        std::filesystem::path decks_dir = app_path;
        decks_dir.append("TEST_Decks");
        std::filesystem::path example1_deck = decks_dir;
        example1_deck.append("example1.deck");
        FlashCardDeck example1 = readFlashCardDeck(example1_deck);
        // std::cerr << "EXample deck name:" << example1.name << std::endl;
        REQUIRE(example1.name == "example deck 1");

        auto stdoutBuffer = std::cout.rdbuf();
        std::ostringstream oss;
        std::cout.rdbuf(oss.rdbuf());

        example1.printDeckAsTemplate();
        std::string c1 = "example deck 1\nQ:  What colour is #FFFFFF?\nA:  White\nD: UNKNOWN\nN: 0\n-\n";
        c1.append("Q:  What colour is #000000?\nA:  Black\nD: UNKNOWN\nN: 3\n-\n");
        REQUIRE(oss.str() == c1);
        oss.clear();
        oss.str("");
        std::cout.rdbuf(stdoutBuffer); // reset to original std::cout buffer
    }
}

TEST_CASE("enum converters")
{
    REQUIRE(strToCardDifficulty("") == UNKNOWN);
    REQUIRE(strToCardDifficulty("SOMETHING") == UNKNOWN);
    REQUIRE(strToCardDifficulty("EASY") == EASY);
    REQUIRE(strToCardDifficulty("MEDIUM") == MEDIUM);
    REQUIRE(strToCardDifficulty("HIGH") == HIGH);
}
