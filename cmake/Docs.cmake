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
