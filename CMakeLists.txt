# Specify a minimum version
cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

# Specify project name
project (a-vim-story C)

# Enable tests
set (tests_enabled 1)

# Set version numbers
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)
set (PROJECT_VERSION_PATCH 0)

# Set directories
set (EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set (LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}")

# Generate a config file with the options
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_BINARY_DIR}/include/config.h"
)

# Add include directory
include_directories ("${CMAKE_SOURCE_DIR}/include")
include_directories ("${CMAKE_BINARY_DIR}/include")

# Add compiler flags
set (PROJECT_DEBUG_FLAGS "-g")
set (PROJECT_LINKER_FLAGS "")
set (PROJECT_SOURCE_FLAGS "-ansi -std=c99 -Wall")
set (CMAKE_C_FLAGS " \
    ${PROJECT_DEBUG_FLAGS} \
    ${PROJECT_SOURCE_FLAGS} \
    ${PROJECT_LINKER_FLAGS} \
")

# Find and add external libraries
find_library (NCURSES_LIB ncurses)
find_library (DL_LIB dl)
set (LIBRARIES ${NCURSES_LIB} ${DL_LIB})

# Setup list of source files
set (PROJECT_SOURCES
    src/main.c
    src/interface.c
    src/map.c
    src/command.c
    src/key.c
    src/msg.c
    src/game.c
    src/menu.c
)

# Add the maps
add_subdirectory (maps)

# Add tests
if (tests_enabled)

    # Find the criterion library for tests
    find_library (CRITERION_LIB criterion)

    set (TESTS
        test/key.c
        src/key.c
        test/msg.c
        src/msg.c
        src/interface.c
        src/command.c
        src/map.c
        src/game.c
        src/menu.c
    )

    add_executable (run_test ${TESTS})
    target_link_libraries (run_test ${LIBRARIES} ${CRITERION_LIB})

    add_custom_command (
        OUTPUT run_test
        COMMAND run_test
        )

    add_custom_target (
        check run_test
        DEPENDS ${PROJECT_NAME}
        COMMENT "Running tests"
        )
endif ()

# Add the executable
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})

# Link the libraries
target_link_libraries (${PROJECT_NAME} ${LIBRARIES})

# Add install target
install (TARGETS ${PROJECT_NAME} DESTINATION bin)
