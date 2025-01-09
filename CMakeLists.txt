cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Tetris")

# Set the thirdparty directory
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")

# Check if the raylib folder exists in the thirdparty directory
if (EXISTS "${THIRDPARTY_DIR}/raylib")
	message(STATUS "Found raykib in the thirdparty directory.")
	# Use the existing raylib source
	set(raylib_SOURCE_DIR "${THIRDPARTY_DIR}/raylib")
	set(raylib_BINARY_DIR "${THIRDPARTY_DIR}/_deps/raylib-build")
else()
	message(STATUS "raylib not found in thirdparty, fetching from Github.")
	# If raylib is not found locally, fetch from github
	include(FetchContent)

	FetchContent_Declare(
		raylib
		GIT_REPOSITORY https://github.com/raysan5/raylib.git # Use Github repo
		GIT_TAG master # or specify the version eg v5.5
	)
	
	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED)
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(raylib)

		#Set the source and binary directories
		set(raylib_SOURCE_DIR ${raylib_SOURCE_DIR})
		set(raylib_BINARY_DIR ${raylib_BINARY_DIR})

		# Additional config for raylib
		set(BUILD_EXAMPLES OFF CACHE BOOL "Do not build examples" FORCE)
	endif()
endif()

# Add raylib as a subdirectory
add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add source to this project executable
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/assets"
	"$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


