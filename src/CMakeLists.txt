set(LIBRARY_SOURCES
    "artwork.cpp"
    # "card_types.cpp"
    "deck.cpp"
    "menu.cpp"
    "test_scene.cpp"
    "util.cpp"
    "gameloop.cpp"
    "player.cpp"
    "playing_card.cpp"
    "example_test.cpp"
)

set(LIBRARY_HEADERS
    "artwork.h"
    "card_types.h"
    "deck.h"
    "menu.h"
    "test_scene.h"
    "util.h"
    "gameloop.h"
    "player.h"
    "playing_card.h"
    "example_test.h")

set(LIBRARY_INCLUDES
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${LIBRARY_INCLUDES})

    if (ENABLE_WARNINGS)
    target_set_warnings(
        ${LIBRARY_NAME}
        ON
        OFF
    )
endif()
