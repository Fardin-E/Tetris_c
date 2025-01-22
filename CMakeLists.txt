cmake_minimum_required(VERSION 3.25)

project("Tetris")

set(CMAKE_C_STANDARD 99)

# Set the thirdparty directory
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(raylib_DIR "${THIRDPARTY_DIR}/raylib")

# Locate source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Add the executables together
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

# MSVC-specific flags (only if MSVC is used and not Ninja)
if(MSVC AND NOT CMAKE_GENERATOR STREQUAL "Ninja")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
            /W4             # Enable warnings at level 4 (equivalent to -Wall for Clang/GCC)
            /WX             # Treat warnings as errors
            /O2             # Optimization level 2 (max speed)
            /Zi             # Generate debug information
    )
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
            /INCREMENTAL:NO  # Disable incremental linking
            /DEBUG            # Include debug information in the executable
    )
endif()

# Common flags for both MSVC and Clang
# MSVC will ignore them, so only Clang and GCC will apply
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        -O3             # Optimization level 3
        -g              # Generate debug information
)

# Set Clang-specific flags
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
            -Wall             # Enable all warnings for Clang
            -Wextra           # Enable extra warnings for Clang
            -Werror           # Treat warnings as errors for Clang
            -fdiagnostics-color=always
            -fsanitize=address # Enable AddressSanitizer
    )
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
            -fsanitize=address  # Link AddressSanitizer runtime explicitly
    )
endif()

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
