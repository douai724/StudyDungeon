set(LIBRARY_SOURCES
    "artwork.cpp"
    # "card_types.cpp"
    "deck.cpp"
    "menu.cpp"
    "flashcard_scene.cpp"
    "edit_flashcard.cpp"
    "mainmenu_scene.cpp"
    "settings_scene.cpp"
    "util.cpp"
    "gameloop.cpp"
    "player.cpp"
    "playing_card.cpp"
    "game_scene.cpp"
    "howto_scene.cpp"
)

set(LIBRARY_HEADERS
    "artwork.h"
    "card_types.h"
    "deck.h"
    "menu.h"
    "flashcard_scene.h"
    "edit_flashcard.h"
    "mainmenu_scene.h"
    "settings_scene.h"
    "util.h"
    "gameloop.h"
    "player.h"
    "playing_card.h"
    "game_scene.h"
    "howto_scene.h"
    )

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
