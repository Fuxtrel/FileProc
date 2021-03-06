cmake_minimum_required(VERSION 3.17)
project(FileProc)

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ROOT  "/home/alex/Загрузки/boost_1_75_0/stage")


set (Boost_USE_STATIC_LIBS ON)
set (OpenSSL_USE_STATIC_LIBS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package (Boost 1.75.0 COMPONENTS system iostreams filesystem)

include_directories (${Boost_INCLUDE_DIRS})
include_directories (${OpenSSL_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp file_proc.h file_proc.cpp)
add_executable(FileProc ${SOURCE_FILES} )

add_subdirectory(Google_tests)

add_subdirectory(Proxy)
add_subdirectory(Client)
add_subdirectory(WebSocket_Client)
add_subdirectory(WebSocket_Server)

link_directories(FileProc ${Boost_LIBRARY_DIRS})
target_link_libraries (FileProc ${Boost_LIBRARIES})

target_link_libraries(FileProc ZLIB::ZLIB)

link_directories(FileProc ${OpenSSL_LIBRARY_DIRS})
target_link_libraries (FileProc OpenSSL::SSL)
