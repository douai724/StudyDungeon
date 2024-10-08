#include "settings_scene.h"
#include <catch2/catch_test_macros.hpp>

StudySettings test_settings;
int default_fc_limit = 15;
int default_n_min = 25;
TEST_CASE("Settings initialisation with defaults")
{
    // check defaults
    REQUIRE(test_settings.getStudyDurationMin() == default_n_min);
    REQUIRE(test_settings.getFlashCardLimit() == default_fc_limit);

    SECTION("reset to default")
    {
        test_settings.setFlashCardLimit(33);
        test_settings.setStudyDurationMin(32);
        test_settings.reset();
        REQUIRE(test_settings.getStudyDurationMin() == default_n_min);
        REQUIRE(test_settings.getFlashCardLimit() == default_fc_limit);
    }
}


TEST_CASE("flashcard limits")
{
    // standard input
    test_settings.setFlashCardLimit(13);
    REQUIRE(test_settings.getFlashCardLimit() == 13);

    // non starndard input sizes
    test_settings.setFlashCardLimit(0);
    REQUIRE(test_settings.getFlashCardLimit() == 1);
    test_settings.setFlashCardLimit(-1);
    REQUIRE(test_settings.getFlashCardLimit() == 1);
    test_settings.setFlashCardLimit(3000);
    REQUIRE(test_settings.getFlashCardLimit() == 3000);

    // reset to default
    test_settings.reset();
    REQUIRE(test_settings.getFlashCardLimit() == default_fc_limit);


    SECTION("test lower bounds")
    {
        // lower limit should be 1
        test_settings.setFlashCardLimit(2);
        test_settings.decFCLimit();
        REQUIRE(test_settings.getFlashCardLimit() == 1);
        // shouldn't go below 1
        test_settings.decFCLimit();
        REQUIRE(test_settings.getFlashCardLimit() == 1);
    }

    SECTION("test upper bounds")
    {
        // upper limit should be
        test_settings.setFlashCardLimit(89);
        test_settings.incFCLimit();
        REQUIRE(test_settings.getFlashCardLimit() == 90);
        // shouldn't go below 1
        test_settings.incFCLimit();
        REQUIRE(test_settings.getFlashCardLimit() == 90);
    }
}


TEST_CASE("Session limits")
{
    SECTION("lower bounds")
    {
        test_settings.setStudyDurationMin(1);
        REQUIRE(test_settings.getStudyDurationMin() == 1);
        // minimum should be 1
        test_settings.setStudyDurationMin(0);
        REQUIRE(test_settings.getStudyDurationMin() == 1);
        test_settings.decStudyDuration();
        REQUIRE(test_settings.getStudyDurationMin() == 1);
    }

    SECTION("upper bounds")
    {
        // max after increment should be 60
        test_settings.setStudyDurationMin(59);
        REQUIRE(test_settings.getStudyDurationMin() == 59);
        test_settings.incStudyDuration();
        REQUIRE(test_settings.getStudyDurationMin() == 60);
        test_settings.incStudyDuration();
        REQUIRE(test_settings.getStudyDurationMin() == 60);
    }
}


TEST_CASE("Session control")
{

    REQUIRE_FALSE(test_settings.sessionUnderway());
    test_settings.startSession();
    REQUIRE(test_settings.sessionUnderway());
}
