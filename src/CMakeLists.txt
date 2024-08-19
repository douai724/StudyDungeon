add_library(${LIBRARY_NAME} STATIC "artwork.cpp" "deck.cpp" "menu.cpp" "util.cpp" "gameloop.cpp" "player.cpp" "playing_card.cpp")
target_include_directories(${LIBRARY_NAME} PUBLIC "./")
