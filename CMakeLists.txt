cmake_minimum_required(VERSION 3.5.0)
project(StudyDungeon VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_NAME Library)

add_subdirectory(src)
add_subdirectory(app)






option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
set(DOXYFILE ${CMAKE_SOURCE_DIR}/Doxyfile)
if (DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/
        COMMENT "Generating HTML documentation with Doxygen"
    )
    message("DIrectory " ${CMAKE_CURRENT_SOURCE_DIR}/docs/)
    else (DOXYGEN_FOUND)
    message("Doxygen not found")
endif (DOXYGEN_FOUND)
include(CTest)
enable_testing()
