set(PROJECT_DEBUG_FLAGS "-g")
set(PROJECT_LINKER_FLAGS "-shared")
set(PROJECT_SOURCE_FLAGS "-fPIC -ansi -std=c99 -pedantic -Wall")
set(CMAKE_C_FLAGS " \
    ${PROJECT_DEBUG_FLAGS} \
    ${PROJECT_SOURCE_FLAGS} \
    ${PROJECT_LINKER_FLAGS} \
")

# Set the output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/maps)

# Add each map
foreach (i RANGE 1 8)

    # The plugin should always export a single binary with a .so extension
    add_executable (map${i} map${i}.c)

    # Add the install target
    install (
        TARGETS         map${i}
        DESTINATION     lib/${PROJECT_NAME}/maps)

endforeach ()
