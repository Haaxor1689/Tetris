CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

# Project name
PROJECT(Tetris)

# Compilation options
IF(MSVC) # For Visual Studio compiler
	SET(COMPILER "MSVC" CACHE STRING "" FORCE)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /wd4251 /wd4275" )
ELSEIF(Clang) # For Clang compilers
	SET(COMPILER "Clang" CACHE STRING "" FORCE)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )
ENDIF(MSVC)

# Set Debug and Release configurations for project
SET(INSTRUCTIONS "Source folder should be in same folder as cmakelists." CACHE STRING "" FORCE)
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
MARK_AS_ADVANCED(CMAKE_INSTALL_PREFIX)

# Set compilation output directory to bin
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Libraries list
SET(LIBS SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2main SDL2test)

# Copying of Dlls to output directories
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/dll/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/dll/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

# Copying of resources to outpud directories
FILE(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/src/resources/*.png ${CMAKE_SOURCE_DIR}/src/resources/*.ttf)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/resources)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/resources)

# Include and library directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libs/inc/)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/libs/lib/)

# Project sources
FILE(GLOB SOURCES src/*.hpp src/*.cpp)

# Example project executable
ADD_EXECUTABLE(Tetris ${SOURCES})
TARGET_LINK_LIBRARIES(Tetris debug ${LIBS} optimized ${LIBS})

IF(MSVC) # Set working directory for debugger in Visual Studio
	SET_TARGET_PROPERTIES(Tetris PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug")
ENDIF(MSVC)