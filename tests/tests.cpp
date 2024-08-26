#include <catch2/catch_test_macros.hpp>

// EXAMPLE OF HOW TESTS WORK


#include "artwork.h"
#include "deck.h"
#include "example_test.h"
#include "gameloop.h"
#include "menu.h"
#include "player.h"
#include "playing_card.h"
#include "util.h"


TEST_CASE("deck_h enum converters")
{
    REQUIRE(strToCardDifficulty("") == UNKNOWN);
    REQUIRE(strToCardDifficulty("SOMETHING") == UNKNOWN);
    REQUIRE(strToCardDifficulty("UNKNOWN") == UNKNOWN);
    REQUIRE(strToCardDifficulty("LOW") == LOW);
    REQUIRE(strToCardDifficulty("MEDIUM") == MEDIUM);
    REQUIRE(strToCardDifficulty("HIGH") == HIGH);

    REQUIRE(cardDifficultyToStr(UNKNOWN) == "UNKNOWN");
    REQUIRE(cardDifficultyToStr(LOW) == "LOW");
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
}

TEST_CASE("enum converters")
{
    REQUIRE(strToCardDifficulty("") == UNKNOWN);
    REQUIRE(strToCardDifficulty("SOMETHING") == UNKNOWN);
    REQUIRE(strToCardDifficulty("LOW") == LOW);
    REQUIRE(strToCardDifficulty("MEDIUM") == MEDIUM);
    REQUIRE(strToCardDifficulty("HIGH") == HIGH);
}

TEST_CASE("factorial1")
{
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}

TEST_CASE("factorial2")
{
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}

TEST_CASE("vectors can be sized and resized", "[vector]")
{
    // This setup will be done 4 times in total, once for each section
    std::vector<int> v(5);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);

    SECTION("resizing bigger changes size and capacity")
    {
        v.resize(10);

        REQUIRE(v.size() == 10);
        REQUIRE(v.capacity() >= 10);
    }
    SECTION("resizing smaller changes size but not capacity")
    {
        v.resize(0);

        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() >= 5);
    }
    SECTION("reserving bigger changes capacity but not size")
    {
        v.reserve(10);

        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() >= 10);
    }
    SECTION("reserving smaller does not change size or capacity")
    {
        v.reserve(0);

        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() >= 5);
    }
}
