cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR})

include_directories(third-party/glew-1.10.0/include)
add_definitions(-DGLEW_STATIC=1)
add_definitions(-Wall)
add_subdirectory(third-party/glew-1.10.0)

include_directories(glimac/include)
add_subdirectory(glimac)

set(ALL_LIBRARIES glew ${OPENGL_LIBRARIES} ${SDL_LIBRARY} glimac)

add_subdirectory(application)

