CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# Name of the project
PROJECT(A1)

# Is this the solution?
# Override with `cmake -DSOL=ON ..`
OPTION(SOL "Solution" OFF)

# Use glob to get the list of all source files.
# We don't really need to include header and resource files to build, but it's
# nice to have them also show up in IDEs.
IF(${SOL})
	FILE(GLOB_RECURSE SOURCES "src0/*.cpp")
	FILE(GLOB_RECURSE HEADERS "src0/*.h")
ELSE()
	FILE(GLOB_RECURSE SOURCES "src/*.cpp")
	FILE(GLOB_RECURSE HEADERS "src/*.h")
ENDIF()

# Set the executable.
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

# OS specific options and libraries
IF(WIN32)
	# c++11 is enabled by default.
	# -Wall produces way too many warnings.
	# -pedantic is not supported.
	# Disable warning 4996.
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
	SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})
ELSE()
	# Enable all pedantic warnings.
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")
ENDIF()
