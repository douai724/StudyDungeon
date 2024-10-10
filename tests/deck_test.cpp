#include "deck.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

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
    REQUIRE(strToCardDifficulty("HARD") == HARD);

    REQUIRE(cardDifficultyToStr(UNKNOWN) == "UNKNOWN");
    REQUIRE(cardDifficultyToStr(EASY) == "EASY");
    REQUIRE(cardDifficultyToStr(MEDIUM) == "MEDIUM");
    REQUIRE(cardDifficultyToStr(HARD) == "HARD");
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
        decks_dir.append("Decks");
        std::filesystem::path new_deck = decks_dir;
        new_deck.append("new.deck");
        // std::cerr << "new deck path:" << new_deck << std::endl;

        if (std::filesystem::exists(new_deck))
        {
            std::cerr << "REMOVING FILE Decks/new.deck" << std::endl;
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
        decks_dir.append("Decks");
        std::filesystem::path example1_deck = decks_dir;
        example1_deck.append("example1.deck");
        FlashCardDeck example1 = readFlashCardDeck(example1_deck);
        example1.printDeckAsTemplate();
        // std::cerr << "EXample deck name:" << example1.name << std::endl;
        REQUIRE(example1.name == "test example deck 1");

        auto stdoutBuffer = std::cout.rdbuf();
        std::ostringstream oss;
        std::cout.rdbuf(oss.rdbuf());

        example1.printDeckAsTemplate();
        FlashCard fc1 = FlashCard{"What colour is #FFFFFF?", "White", HARD, 0};
        FlashCard fc2 = FlashCard{"What colour is #000000?", "Black", EASY, 3};
        FlashCard fc3 = FlashCard{"What colour is #FF0000?", "Red", UNKNOWN, 0};
        FlashCard fc4 = FlashCard{"What colour is #00FF00?", "Green", MEDIUM, 0};
        FlashCard fc5 = FlashCard{"What colour is #0000FF?", "Blue", UNKNOWN, 5};

        std::string c1 = fc1.stringCardAsTemplate();
        std::string c2 = fc2.stringCardAsTemplate();
        std::string c3 = fc3.stringCardAsTemplate();
        std::string c4 = fc4.stringCardAsTemplate();
        std::string c5 = fc5.stringCardAsTemplate();
        FlashCardDeck fd1{"test example deck 1", "", std::vector<FlashCard>{fc1, fc2, fc3, fc4, fc5}};
        REQUIRE(oss.str() == fd1.name + "\n" + c1 + c2 + c3 + c4 + c5);
        oss.clear();
        oss.str("");

        std::string h1 = "test example deck 1\nFile location: \"\"\nDeck size: 5 cards\n";
        c1 = "What colour is #FFFFFF?\nWhite\n\n";
        c2 = "What colour is #000000?\nBlack\n\n";
        c3 = "What colour is #FF0000?\nRed\n\n";
        c4 = "What colour is #00FF00?\nGreen\n\n";
        c5 = "What colour is #0000FF?\nBlue\n\n";
        std::string d1 = h1 + c1 + c2 + c3 + c4 + c5;
        example1.printDeck();
        REQUIRE(oss.str() == d1);
        oss.clear();
        oss.str("");

        std::vector<FlashCardDeck> fd = loadFlashCardDecks(decks_dir);


        std::cout.rdbuf(stdoutBuffer); // reset to original std::cout buffer
    }
}

TEST_CASE("enum converters")
{
    REQUIRE(strToCardDifficulty("") == UNKNOWN);
    REQUIRE(strToCardDifficulty("SOMETHING") == UNKNOWN);
    REQUIRE(strToCardDifficulty("EASY") == EASY);
    REQUIRE(strToCardDifficulty("MEDIUM") == MEDIUM);
    REQUIRE(strToCardDifficulty("HARD") == HARD);
}
