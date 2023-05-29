cmake_minimum_required(VERSION 3.23)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

set(Headers src/Graph.h src/VertexEdge.h src/GraphManager.h)

add_executable(untitled1 ${PROJECT_SOURCE_DIR}/ main.cpp src/Graph.cpp src/GraphManager.cpp src/VertexEdge.cpp)
