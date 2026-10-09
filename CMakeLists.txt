cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(learnply2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(glfw-3.5.1)

add_subdirectory(glm)

set(SRC "src")
add_executable(learnply2
	${SRC}/camera.cpp ${SRC}/camera.h
	${SRC}/edge.cpp ${SRC}/edge.h
	${SRC}/main.cpp
	${SRC}/mesh.cpp ${SRC}/mesh.h
	${SRC}/ply.c ${SRC}/ply.h
	${SRC}/triangle.cpp ${SRC}/triangle.h
	${SRC}/vertex.cpp ${SRC}/vertex.h	
)

target_link_libraries(learnply2 glfw glm OpenGL::GL)
