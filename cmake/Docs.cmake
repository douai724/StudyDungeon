find_package(Doxygen)



if (DOXYGEN_FOUND)
# Configure the Doxyfile from Doxyfile.in
configure_file(
    ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in
    ${CMAKE_SOURCE_DIR}/docs/Doxyfile
    @ONLY
)
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs/
        COMMENT "Generating HTML documentation with Doxygen"
        VERBATIM
    )
    message("Directory " ${CMAKE_SOURCE_DIR}/docs/)
    else (DOXYGEN_FOUND)
    message("Doxygen not found")
endif (DOXYGEN_FOUND)
