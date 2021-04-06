project(Client)

add_executable(Client main.cpp client.cpp client.h)

target_link_libraries(Client zmq)
