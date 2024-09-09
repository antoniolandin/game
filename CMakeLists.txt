# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(game VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create a symlink to the compile_commands.json file in the source directory
execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

# Set the project directory
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Find SFML package
set(SFML_DIR ".")  # Adjust this if SFML is in a different directory
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Specify the source files
file(GLOB SRC_FILES "src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SFML_INCLUDE_DIR}
)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Add a custom target for cleaning
add_custom_target(clean-all COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Add command for running the executable
add_custom_target(run
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
