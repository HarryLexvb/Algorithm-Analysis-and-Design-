cmake_minimum_required(VERSION 3.24)
project(DenseSubgraph)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.74.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(DenseSubgraph main.cpp Args.cpp Args.h EdgeFN.cpp EdgeFN.h FlowNetwork.cpp FlowNetwork.h Graph.cpp Graph.h)

target_link_libraries(DenseSubgraph ${Boost_LIBRARIES})