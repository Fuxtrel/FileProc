project(Proxy)

add_executable(Proxy main.cpp proxy.cpp proxy.h)

target_link_libraries(Proxy zmq)

link_directories(FileProc ${Boost_LIBRARY_DIRS})
target_link_libraries (FileProc ${Boost_LIBRARIES})
