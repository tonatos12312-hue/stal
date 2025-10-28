include(${CMAKE_HOME_DIRECTORY}/cmake/global.cmake)
include(${CMAKE_HOME_DIRECTORY}/cmake/pre_include.cmake)

project(common)

include(FetchContent)

FetchContent_Declare(
        hde64
        GIT_REPOSITORY https://github.com/Cerbersec/HDE64.git
        GIT_TAG main
)
FetchContent_Declare(
        stb_image
        URL https://raw.githubusercontent.com/planetack/stb_image/refs/heads/master/stb_image.h
        DOWNLOAD_NO_EXTRACT true
)

FetchContent_MakeAvailable(hde64 stb_image)

find_package(OpenGL REQUIRED)

include(${CMAKE_HOME_DIRECTORY}/cmake/imgui.cmake)

file(GLOB_RECURSE source_files src/*.cpp)
add_library(common STATIC ${source_files} ${imgui_source_files})

target_include_directories(common PUBLIC
        src
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${CMAKE_HOME_DIRECTORY}/thirdparty/directx11_sdk/include
        ${stb_image_SOURCE_DIR}
        ${hde64_SOURCE_DIR}
        ${CMAKE_HOME_DIRECTORY}/thirdparty/keyauth/include
)

target_link_libraries(common PUBLIC
        ${OPENGL_LIBRARIES}
        ${CMAKE_HOME_DIRECTORY}/thirdparty/keyauth/lib/library_x64.lib
)

set(imgui_SOURCE_DIR ${imgui_SOURCE_DIR} PARENT_SCOPE)
