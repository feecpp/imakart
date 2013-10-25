add_subdirectory(shaders)
add_subdirectory(src)#Pour le voir dans le projet
add_subdirectory(include)#idem

INCLUDE_DIRECTORIES(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
file(GLOB SHADERS_FILES  shaders/*.glsl)#pour les voirs dans son IDE

