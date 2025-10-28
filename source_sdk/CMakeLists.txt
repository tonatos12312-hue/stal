include(${CMAKE_HOME_DIRECTORY}/cmake/global.cmake)
include(${CMAKE_HOME_DIRECTORY}/cmake/pre_include.cmake)

project(source_sdk)

file(GLOB_RECURSE source_files src/*.cpp)
add_library(source_sdk STATIC ${source_files})

target_include_directories(source_sdk PUBLIC src)
target_link_libraries(source_sdk PUBLIC common)
