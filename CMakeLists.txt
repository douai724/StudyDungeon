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

include(CTest)
enable_testing()

