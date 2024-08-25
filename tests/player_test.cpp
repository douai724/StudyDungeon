#include <catch2/catch_test_macros.hpp>

#include "player.h"
#include "playing_card.h"
#include <vector>

TEST_CASE("Hit points are updated and retrieved"){
    Player testPlayer = Player(100, 100, std::vector<PlayingCard>());

    SECTION("Retrieving hit points"){
        REQUIRE( testPlayer.getHitPoints() == 100 );
    }

    SECTION("Updating hit points with positive int"){
        testPlayer.setHitPoints(50);
        REQUIRE( testPlayer.getHitPoints() == 50 );
    }

    SECTION("Updating hit points with negative int"){
        testPlayer.setHitPoints(-100);
        REQUIRE( testPlayer.getHitPoints() == -100);
    }
}

TEST_CASE("MAXIMUM hit points are updated and retrieved"){
    Player testPlayer = Player(100, 100, std::vector<PlayingCard>());

    SECTION("Retrieving MAXIMUM hit points"){
        REQUIRE( testPlayer.getMaxHitPoints() == 100 );
    }

    SECTION("Updating MAXIMUM hit points with positive int"){
        testPlayer.setMaxHitPoints(50);
        REQUIRE( testPlayer.getMaxHitPoints() == 50);
    }

    SECTION("MAXIMUM hit points that are negative are not accepted"){
        testPlayer.setMaxHitPoints(-1);
        REQUIRE( testPlayer.getMaxHitPoints() == 100);
    }
}