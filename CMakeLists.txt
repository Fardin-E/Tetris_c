cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Tetris")

# Set the thirdparty directory
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(raylib_DIR "${THIRDPARTY_DIR}/raylib")

# Check if raylib folder exists in the thirdparty directory
if (NOT EXISTS "${raylib_DIR}/CMakeLists.txt")
	message(STATUS "raylib not found in thirdparty, fetching from GitHub.")

	# Use FetchContent to fetch raylib from GitHub and place it in the thirdparty directory
	include(FetchContent)
	FetchContent_Declare(
			raylib
			GIT_REPOSITORY https://github.com/raysan5/raylib.git
			GIT_TAG master # Replace 'master' with a specific version tag if needed
			SOURCE_DIR ${raylib_DIR}  # Fetch to the thirdparty folder
	)

	FetchContent_MakeAvailable(raylib)

	message(STATUS "Fetched raylib to ${raylib_DIR}")
else()
	message(STATUS "Found raylib in the thirdparty directory.")
endif()

# Locate source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add the Tetris executable
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

# Copy assets to the build directory after building the executable
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/assets"
		"$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets"
)

# Link raylib and include directories
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
