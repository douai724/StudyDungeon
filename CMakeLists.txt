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

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set location of doxyfile
    set(DOXYFILE ${CMAKE_SOURCE_DIR}/Doxyfile)

    message("Doxygen build started")

    add_custom_target( doc_doxygen ALL COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen not found")
endif (DOXYGEN_FOUND)
