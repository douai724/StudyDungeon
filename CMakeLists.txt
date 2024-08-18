cmake_minimum_required(VERSION 3.5.0)
project(StudyDungeon VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_FILES
    StudyDungeon.cpp
    includes/deck.cpp
    includes/menu.cpp
    includes/util.cpp
)
add_executable(StudyDungeon ${SOURCE_FILES} )



option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/
        COMMENT "Generating HTML documentation with Doxygen"
    )
endif()

include(CTest)
enable_testing()
