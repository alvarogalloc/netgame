cmake_minimum_required(VERSION 3.20)
project(netgame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

include(FetchContent)

FetchContent_Declare(
  Ginseng
  GIT_REPOSITORY https://github.com/apples/ginseng.git 
)

FetchContent_MakeAvailable(Ginseng)

find_package(
  SFML
  COMPONENTS system window graphics audio CONFIG
  REQUIRED)

file(GLOB ASSETS ./assets/*)
file(GLOB SOURCES ./src/*.cpp ./src/scenes/*.cpp ./include/*.h
  ./include/scenes/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} NETGAME_DEBUG)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-audio
                                              sfml-graphics sfml-window)
target_link_libraries(${PROJECT_NAME} PRIVATE ginseng)

if(APPLE)
  target_link_libraries(
    ${PROJECT_NAME} PRIVATE "-framework CoreFoundation" "-framework CoreAudio"
                            "-framework AudioUnit")
endif()
target_include_directories(${PROJECT_NAME} PRIVATE include)
