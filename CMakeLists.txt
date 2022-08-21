cmake_minimum_required(VERSION 3.16)

project(EsafeNetDecrypt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

find_package(Qt5 COMPONENTS Widgets Concurrent REQUIRED)

add_executable(decrypt_gui
               main.cpp
               main_window.cpp
               main_window.h
               main_window.ui
               about_dialog.cpp
               about_dialog.h 
               about_dialog.ui
)

target_link_libraries(decrypt_gui PRIVATE Qt5::Widgets Qt5::Concurrent)
set_target_properties(decrypt_gui PROPERTIES WIN32_EXECUTABLE TRUE)

add_executable(decrypt decrypt.cpp)
set_target_properties(decrypt PROPERTIES OUTPUT_NAME notepad++)

install(TARGETS decrypt_gui decrypt
        DESTINATION "")

set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
include (InstallRequiredSystemLibraries)

include(windeployqt)
windeployqt(decrypt_gui "bin")
