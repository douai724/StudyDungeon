#include <catch2/catch_test_macros.hpp>

#include "deck.h"

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
