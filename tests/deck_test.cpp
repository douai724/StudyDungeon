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

    SECTION("FlashCard creation through method")
    {

        FlashCard fc_test = createFlashCard("question", "answer", MEDIUM, 1);

        REQUIRE(fc_test.question == "question");
        REQUIRE(fc_test.answer == "answer");
        REQUIRE(fc_test.difficulty == MEDIUM);
        REQUIRE(fc_test.n_times_answered == 1);
    }

    SECTION("Card methods")
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
