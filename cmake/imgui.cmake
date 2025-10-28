set(IMGUI_WITH_BACKEND ON)
set(IMGUI_BACKEND_DX11 ON)
set(IMGUI_BACKEND_PLATFORM "WIN32")

FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/thedmd/imgui.git
        GIT_TAG feature/hidpi-support
)
FetchContent_MakeAvailable(imgui)

file(GLOB imgui_source_files "${imgui_SOURCE_DIR}/*.cpp")
list(APPEND imgui_source_files ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp)

include_directories(${imgui_SOURCE_DIR})
include_directories(${imgui_SOURCE_DIR}/backends)
