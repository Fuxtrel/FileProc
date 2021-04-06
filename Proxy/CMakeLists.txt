project(Proxy)

add_executable(Proxy main.cpp client.cpp proxy.h)

target_link_libraries(Proxy zmq)
