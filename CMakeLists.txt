
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)
project(Loopy)

find_package( OpenCV REQUIRED )
add_executable( Loopy LoopyNode.cpp LoopyInputNode.cpp LoopyNodeTest.cpp  )
set(CMAKE_CXX_FLAGS "-g")
target_link_libraries( Loopy ${OpenCV_LIBS} )