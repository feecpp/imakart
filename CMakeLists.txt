cmake_minimum_required(VERSION 2.8)
PROJECT(Imakart)
find_package(OpenGL REQUIRED)
find_package(SFML 2.1 COMPONENTS graphics window system REQUIRED)

set(CMAKE_CXX_FLAGS "-std=gnu++0x ${CMAKE_CXX_FLAGS}")

include_directories(${OPENGL_INCLUDE_DIR} ${SFML_INCLUDE_DIR})

#-----THIRD PARTY LIBS-------------
#glew
include_directories(third-party/glew-1.10.0/include)
add_definitions(-DGLEW_STATIC=1)
add_subdirectory(third-party/glew-1.10.0)

#assimp
include_directories(third-party/assimp--3.0.1270/include)
add_definitions(-DENABLE_BOOST_WORKAROUND=ON)
SET(ENABLE_BOOST_WORKAROUND ON)
SET(BUILD_STATIC_LIB ON)
SET(BUILD_ASSIMP_TOOLS OFF)
add_subdirectory(third-party/assimp--3.0.1270)
#desactive les warnings degueulasses
set_target_properties(assimp PROPERTIES COMPILE_FLAGS "-w")

#glm
include_directories(third-party/glm)

#--------Imakart------------------
add_definitions(-Wall)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
file(COPY application/shaders DESTINATION ./application)
file(COPY application/data DESTINATION ./application)
file(COPY application/fonts DESTINATION ./application)
file(COPY application/textures DESTINATION ./application)
file(COPY application/karts DESTINATION ./application)
file(COPY application/maps DESTINATION ./application)

#Windows : copie des DLL a cote de l'exe
IF(WIN32)
  file(GLOB dllfiles $ENV{SFML_ROOT}/bin/*.dll)
  file(COPY ${dllfiles} DESTINATION ./application/)
ENDIF(WIN32)

include_directories(glimac/include)
add_subdirectory(glimac)

set(ALL_LIBRARIES assimp glew glimac ${OPENGL_LIBRARIES} ${SFML_LIBRARIES} )

add_subdirectory(application)

