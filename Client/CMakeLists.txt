project(Client)

add_executable(Client main.cpp client.cpp client.h)

target_link_libraries(Client zmq)

link_directories(Client ${Boost_LIBRARY_DIRS})
target_link_libraries (Client ${Boost_LIBRARIES})
