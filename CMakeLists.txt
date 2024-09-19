# CMakeLists files/configuration based on https://github.com/franneck94/UdemyCmake/
cmake_minimum_required(VERSION 3.5.0)
project(StudyDungeon VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Get the current Git commit SHA
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_SHA
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Print the commit SHA
message(STATUS "Git commit SHA: ${GIT_COMMIT_SHA}")

# Optionally, set it as a definition for later use in your project
add_definitions(-DGIT_COMMIT_SHA=\"${GIT_COMMIT_SHA}\")

option(ENABLE_TESTING "Enable a Unit Testing Build" ON)
option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." ON)
option(ENABLE_SANITIZE_ADDR "Enable address sanitizer" OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitizer" OFF)

set(LIBRARY_NAME "Library")
set(EXECUTABLE_NAME "StudyDungeon")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(Docs)
include(FetchContent)

if(ENABLE_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.5.3
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(Sanitizers)
    add_sanitizer_flags(ENABLE_SANITIZE_ADDR ENABLE_SANITIZE_UNDEF)
endif()

add_subdirectory(configured)
add_subdirectory(src)
add_subdirectory(app)

# TODO Create a post-build command that will copy the Deck directory to where the exe is
set(DECK_TEMPLATE_DIR ${CMAKE_SOURCE_DIR}/Decks)
set(DECK_DEST EXECUTABLE_OUTPUT_PATH)

if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION "${PROJECT_SOURCE_DIR}/bin")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/Decks" DESTINATION "${PROJECT_SOURCE_DIR}/bin" )
