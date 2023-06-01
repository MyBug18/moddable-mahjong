cmake_minimum_required(VERSION 3.0.0)
project(moddable-mahjong VERSION 0.1.0)
include(FetchContent)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_SOURCE_DIR}/src/*.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(moddable-mahjong ${SRC_FILES})

find_package(Lua REQUIRED)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

target_include_directories(moddable-mahjong PUBLIC ${LUA_INCLUDE_DIR})
target_include_directories(moddable-mahjong PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(moddable-mahjong ${LUA_LIBRARIES})
target_link_libraries(moddable-mahjong fmt)

target_compile_features(moddable-mahjong PUBLIC cxx_std_20)

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/Resource
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resource)
