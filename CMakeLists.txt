# CMake 3.8 requiered for VS_DEBUGGER_WORKING_DIRECTORY command
CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

# Project name
PROJECT(Tetris)

# Compilation options
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /nologo /W4 /GL /Gw" )
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /nologo /W4" )

# Set Debug and Release configurations for project
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
MARK_AS_ADVANCED(CMAKE_INSTALL_PREFIX)

# Project sources
FILE(GLOB SOURCES src/*.cpp src/*.hpp)

# Set compilation output directory to bin
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Copying of resources to outpud directories
FILE(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/src/resources/*.png ${CMAKE_SOURCE_DIR}/src/resources/*.ttf)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/resources)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/resources)

# Copying of Dlls to output directories
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/dll/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/dll/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

# Include and library directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libs/inc/)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/libs/lib/)

# Libraries list
SET(LIBS SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_FontCache SDL2main SDL2test)

# Project executable
ADD_EXECUTABLE(Tetris ${SOURCES})
TARGET_LINK_LIBRARIES(Tetris debug ${LIBS} optimized ${LIBS})

# Set Visual Studio specific settings
SET_TARGET_PROPERTIES(Tetris PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug")
SET_PROPERTY(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tetris)

