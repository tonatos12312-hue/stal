include(FetchContent)
include(${CMAKE_HOME_DIRECTORY}/cmake/global.cmake)
include(${CMAKE_HOME_DIRECTORY}/cmake/pre_include.cmake)
include(${CMAKE_HOME_DIRECTORY}/cmake/resources.cmake)

project(stalcraft_chams)

add_subdirectory(${CMAKE_HOME_DIRECTORY}/common common)

file(GLOB_RECURSE source_files src/*.cpp)
add_library(stalcraft_chams SHARED ${source_files} ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

target_include_directories(stalcraft_chams PRIVATE src)
target_link_libraries(stalcraft_chams PRIVATE menu)

add_resources(stalcraft_chams NAMESPACE generated_sc FONT_SIZES 13 14 16)
