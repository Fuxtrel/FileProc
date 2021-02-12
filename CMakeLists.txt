cmake_minimum_required(VERSION 3.17)
project(FileProc)

set(CMAKE_CXX_STANDARD 20)

set (Boost_USE_STATIC_LIBS OFF)

find_package (Boost REQUIRED COMPONENTS system filesystem unit_test_framework)
find_package(OpenSSL REQUIRED)

include_directories (${Boost_INCLUDE_DIRS})
include_directories (${OpenSSL_INCLUDE_DIRS})

add_executable(FileProc main.cpp file_proc.cpp file_proc.h)

link_directories(FileProc ${Boost_LIBRARY_DIRS})
target_link_libraries (FileProc ${Boost_LIBRARIES})

link_directories(FileProc ${OpenSSL_LIBRARY_DIRS})
target_link_libraries (FileProc OpenSSL::SSL)







