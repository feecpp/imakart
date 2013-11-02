add_subdirectory(shaders)
add_subdirectory(src)#Pour le voir dans le projet
add_subdirectory(include)#idem

INCLUDE_DIRECTORIES(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
file(GLOB SHADERS_FILES  shaders/*.glsl)#pour les voirs dans son IDE

add_executable(imakart src/main.cxx ${SRC_FILES} ${SHADERS_FILES})
target_link_libraries(imakart ${ALL_LIBRARIES})

add_executable(testRace src/testRace.cxx ${SRC_FILES} ${SHADERS_FILES})
target_link_libraries(testRace ${ALL_LIBRARIES})
