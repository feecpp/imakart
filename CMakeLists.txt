cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(C:/SFML-2.1/include)
link_directories(C:/SFML-2.1_build/lib)

include_directories(third-party/glew-1.10.0/include)
include_directories(third-party/glm)

file(COPY application/shaders DESTINATION ./application)
file(COPY application/shaders DESTINATION ./)

add_definitions(-DGLEW_STATIC=1)
add_definitions(-Wall)
add_subdirectory(third-party/glew-1.10.0)

include_directories(glimac/include)
add_subdirectory(glimac)

set(ALL_LIBRARIES glew ${OPENGL_LIBRARIES} glimac sfml-graphics sfml-system sfml-window)

add_subdirectory(application)

