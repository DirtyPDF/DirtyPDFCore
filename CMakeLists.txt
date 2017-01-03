project(DirtyPDFCore)
cmake_minimum_required(VERSION 3.5)

set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src)
add_subdirectory(tests)
#add_subdirectory(cmake)
add_subdirectory(doc)
