cmake_minimum_required(VERSION 3.23)
project(caos-photoshop)

set(CMAKE_CXX_STANDARD 17)

add_executable(caos-photoshop
        main.c
        pic.h
        pic.c
        lut.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(caos-photoshop ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(caos-photoshop m)
