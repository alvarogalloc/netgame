cmake_minimum_required(VERSION 3.20)
project(netgame CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(
  SFML
  COMPONENTS system window graphics audio CONFIG
  REQUIRED)

file(GLOB ASSETS ./assets/*)
file(GLOB SOURCES ./src/*.cpp ./include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${PROJECT_NAME} PRIVATE sfml-system sfml-audio sfml-graphics sfml-window)
if(APPLE)
target_link_libraries(
  ${PROJECT_NAME} PRIVATE "-framework CoreFoundation" "-framework CoreAudio"
                          "-framework AudioUnit")
endif()
target_include_directories(${PROJECT_NAME} PRIVATE include)
