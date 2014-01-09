file(GLOB_RECURSE SRC_FILES *.cpp *.c *.h)

add_library(coldet STATIC ${SRC_FILES})
