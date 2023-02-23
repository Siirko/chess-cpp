cmake_minimum_required(VERSION 3.16)
project(chess-cpp)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

# SDL2
# ignore SDL2 test
set(SDL_TEST OFF CACHE BOOL "Enable building of the test suite" FORCE)
# ignore SDL2 examples
set(SDL_EXAMPLES OFF CACHE BOOL "Enable building of the example programs" FORCE)

FetchContent_Declare(
    sdl2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL/
    GIT_TAG release-2.26.2
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    sdl2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-2.6.2
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(sdl2)

if(NOT sdl2_POPULATED)
    FetchContent_Populate(sdl2)
    message (STATUS "SDL2 source dir: ${sdl2_SOURCE_DIR}")
    message (STATUS "SDL2 binary dir: ${sdl2_BINARY_DIR}")
    add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
endif()

FetchContent_GetProperties(sdl2_image)

if(NOT sdl2_image_POPULATED)
    FetchContent_Populate(sdl2_image)
    message (STATUS "SDL2_image source dir: ${sdl2_image_SOURCE_DIR}")
    message (STATUS "SDL2_image binary dir: ${sdl2_image_BINARY_DIR}")
    add_subdirectory(${sdl2_image_SOURCE_DIR} ${sdl2_image_BINARY_DIR})
endif()


add_custom_target(
    copy-textures ALL
    COMMENT "Copying textures"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/tex ${CMAKE_BINARY_DIR}/tex)



file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tex/*.png
    ${CMAKE_CURRENT_SOURCE_DIR}/tex/*.jpg
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_dependencies(${PROJECT_NAME} copy-textures)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2_image SDL2_ttf stdc++fs)

target_include_directories(${PROJECT_NAME} 
                            PUBLIC ${sdl2_SOURCE_DIR}/include
                            PUBLIC ${sdl2_image_SOURCE_DIR}/include
                            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)