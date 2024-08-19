find_package(Doxygen)

if (DOXYGEN_FOUND)
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs/
        COMMENT "Generating HTML documentation with Doxygen"
    )
    message("Directory " ${CMAKE_SOURCE_DIR}/docs/)
    else (DOXYGEN_FOUND)
    message("Doxygen not found")
endif (DOXYGEN_FOUND)
