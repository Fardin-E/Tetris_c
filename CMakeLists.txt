cmake_minimum_required(VERSION 3.25)
project("Tetris")
set(CMAKE_C_STANDARD 99)

# Set the thirdparty directory
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(raylib_DIR "${THIRDPARTY_DIR}/raylib")

# MSVC-specific compiler flags - setting global flags before target creation
if(MSVC)
    # Enable optimization flags for Release builds
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /Oi /GL")
    set(CMAKE_LINK_FLAGS_RELEASE "${CMAKE_LINK_FLAGS_RELEASE} /LTCG")
endif()

# Locate source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Add the executables together
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

# MSVC-specific target compile options - after target creation
if(MSVC)
    # Enable multi-processor compilation
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /MP)
    
    # Warning level and error handling
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE 
        /W4     # Warning level 4
        /WX     # Treat warnings as errors
        /wd4100 # Unreferenced formal parameter
        /wd4505 # Unreferenced local function removed
        /permissive- # Enforce strict standard compliance
    )
    
    # Runtime library selection
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /MDd)
    else()
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /MD)
    endif()
    
    # Buffer security check
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /GS)
    
    # Enable debug information in all builds
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /Zi)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
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