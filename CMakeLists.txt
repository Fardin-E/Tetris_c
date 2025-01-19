cmake_minimum_required(VERSION 3.30)

project("Test")

set(CMAKE_C_STANDARD 99)

# Set the thirdparty directory
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(raylib_DIR "${THIRDPARTY_DIR}/raylib")

# Locate source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Add the executables together
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

# Set Clang-specific flags locally
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
            -fdiagnostics-color=always
            -fsanitize=address
    )
endif()

# local compiler flags
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Werror
        -O3
        -g
)

# Add the include directories where your code resides
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link raylib and include directories
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib)

# Explicitly set the include directory for raylib
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${raylib_DIR}/src  # Add raylib's src directory to the include path
)

# If raylib isn't building automatically, this will force it to be built recursively
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ensure that Raylib's CMakeLists.txt is properly configured and invoked
if (NOT TARGET raylib)
    add_subdirectory("${raylib_DIR}" "${CMAKE_BINARY_DIR}/raylib-build")
endif()
