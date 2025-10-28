include(${CMAKE_HOME_DIRECTORY}/cmake/global.cmake)
include(${CMAKE_HOME_DIRECTORY}/cmake/pre_include.cmake)
include(${CMAKE_HOME_DIRECTORY}/cmake/resources.cmake)

project(menu)

file(GLOB_RECURSE source_files src/*.cpp)
add_library(menu STATIC ${source_files})

target_include_directories(menu PUBLIC src)
target_link_libraries(menu PUBLIC common)

add_resources(menu FONT_SIZES 13 14 16)
