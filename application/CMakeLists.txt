add_subdirectory(shaders)
add_subdirectory(src)#Pour le voir dans le projet
add_subdirectory(include)#idem

INCLUDE_DIRECTORIES(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
file(GLOB SHADERS_FILES  shaders/*.glsl)#pour les voirs dans son IDE
add_library(glimac ${SRC_FILES} ${SHADERS_FILES})
target_link_libraries(glimac glew ${OPENGL_LIBRARIES} ${SDL_LIBRARY})
