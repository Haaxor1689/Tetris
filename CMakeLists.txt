CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

# Project name
PROJECT(Tetris)

# Compilation options
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /wd4251 /wd4275" )

# Set Debug and Release configurations for project
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Set compilation output directory to bin
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Libraries
#FILE(GLOB LIBS "${CMAKE_SOURCE_DIR}/libs/lib/*.lib")
SET(LIBS SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2main SDL2test)

# Copying of Dlls to output directories
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/bin/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
FILE(COPY ${CMAKE_SOURCE_DIR}/libs/bin/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

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
set_target_properties(Tetris PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug")