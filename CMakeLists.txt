cmake_minimum_required(VERSION 3.14)
project(ttf2png)

include(FetchContent)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype
    GIT_TAG master
    GIT_SHALLOW TRUE)
set(FT_DISABLE_BROTLI ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BZIP2 ON CACHE BOOL "" FORCE)
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG ON CACHE BOOL "" FORCE)
set(FT_DISABLE_ZLIB ON CACHE BOOL "" FORCE)
set(FT_ENABLE_ERROR_STRINGS ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(freetype)

file(GLOB_RECURSE sources src/*.h src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /utf-8>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-W -Wall>)
target_link_libraries(${PROJECT_NAME} PRIVATE
    freetype)