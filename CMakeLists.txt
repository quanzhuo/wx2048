cmake_minimum_required(VERSION 3.18)
project(wx2048
        VERSION 0.1
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
add_executable(wx2048 WIN32 MyFrame.cpp MyFrame.h MyApp.cpp MyApp.h ScorePad.cpp ScorePad.h)
set_property(TARGET wx2048 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_link_libraries(wx2048 PRIVATE ${wxWidgets_LIBRARIES})