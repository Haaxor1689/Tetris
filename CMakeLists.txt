IF(MSVC) # CMake 3.8 requiered for VS_DEBUGGER_WORKING_DIRECTORY command
CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
ELSE(MSVC)
CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
ENDIF(MSVC)

# Project name
PROJECT(Tetris)

IF(MSVC)
###################################################
####               Visual Studio               ####
###################################################
# Compilation options
SET(COMPILER "MSVC" CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /wd4251 /wd4275" )

# Set Debug and Release configurations for project
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
MARK_AS_ADVANCED(CMAKE_INSTALL_PREFIX)

# Set compilation output directory to bin
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Copying of resources to outpud directories
FILE(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/src/resources/*.png ${CMAKE_SOURCE_DIR}/src/resources/*.ttf)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/resources)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/resources)

# Project sources
FILE(GLOB SOURCES src/*.hpp src/*.cpp)

# Copying of Dlls to output directories
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/dll/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/dll/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

# Include and library directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libs/inc/)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/libs/lib/)

# Libraries list
SET(LIBS SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2main SDL2test)

# Project executable
ADD_EXECUTABLE(Tetris ${SOURCES})
TARGET_LINK_LIBRARIES(Tetris debug ${LIBS} optimized ${LIBS})

# Set working directory for debugger in Visual Studio
SET_TARGET_PROPERTIES(Tetris PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug")

ELSEIF(Clang)
###################################################
####                   Clang                   ####
###################################################
# Compilation options
SET(COMPILER "Clang" CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )

# Set compilation output directory to bin
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Copying of resources to outpud directories
FILE(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/src/resources/*.png ${CMAKE_SOURCE_DIR}/src/resources/*.ttf)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/resources)
FILE(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/resources)

# Project sources
FILE(GLOB SOURCES src/*.hpp src/*.cpp)

FIND_PACKAGE(SDL2 REQUIRED)
STRING(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

# Include directories
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

# Project executable
ADD_EXECUTABLE(Tetris ${SOURCES})
TARGET_LINK_LIBRARIES(Tetris ${SDL2_LIBRARIES} SDL2_ttf SDL2_image SDL2_mixer)

ENDIF(MSVC)