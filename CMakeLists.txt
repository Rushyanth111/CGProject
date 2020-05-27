cmake_minimum_required(VERSION 3.0.0)
project(graphicsdemo VERSION 0.1.0)
set(CXX_STANDARD 11)
find_package(GLUT REQUIRED)

set(SOURCES 
    CGProject.cpp
    Utility.h
    Utility.cpp
)

include_directories(${GLUT_INCLUDE_DIRS})
add_executable(graphicsdemo ${SOURCES})
target_link_libraries(graphicsdemo PRIVATE GLUT::GLUT)