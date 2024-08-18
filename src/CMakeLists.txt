add_library(${LIBRARY_NAME} STATIC "artwork.cpp" "deck.cpp" "menu.cpp" "util.cpp")
target_include_directories(${LIBRARY_NAME} PUBLIC "./")
