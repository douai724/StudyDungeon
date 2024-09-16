include(Catch)

set(TEST_MAIN "unit_tests")
set(TEST_SOURCES
    "tests.cpp"
    "deck_test.cpp"
    "player_test.cpp"
    "playing_card_test.cpp"
    "gameloop_test.cpp"
    "util_test.cpp"
)
set(TEST_INCLUDES "./")

add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_include_directories(${TEST_MAIN} PUBLIC ${TEST_INCLUDES})
target_link_libraries(${TEST_MAIN} PUBLIC ${LIBRARY_NAME} Catch2::Catch2WithMain)


set(DECK_DEST EXECUTABLE_OUTPUT_PATH)

add_custom_command(TARGET ${TEST_MAIN} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Decks $<TARGET_FILE_DIR:${TEST_MAIN}>/TEST_Decks
    COMMENT "Copying Decks/ from ${PROJECT_SOURCE_DIR}/Decks to $<TARGET_FILE_DIR:${TEST_MAIN}>/TEST_Decks"
)

# add_test(NAME ${TEST_MAIN}
# COMMAND ${TEST_MAIN})
catch_discover_tests(${TEST_MAIN})
