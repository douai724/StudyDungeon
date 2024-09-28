set(EXE_SOURCES
    "studydungeon.cpp")
set(EXE_INCLUDES
    "./")

add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES})
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${EXE_INCLUDES})
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${LIBRARY_NAME})

if (ENABLE_WARNINGS)
    target_set_warnings(
        ${EXECUTABLE_NAME}
        ON
        OFF
    )
endif()

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Decks $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/Decks
    COMMENT "Copying Decks/ from ${PROJECT_SOURCE_DIR}/Decks to $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/Decks"
)

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/artwork $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/artwork
    COMMENT "Copying artwork/ from ${PROJECT_SOURCE_DIR}/artwork to $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/artwork"
)
