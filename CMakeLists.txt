PROJECT(ZephyrGC)

SET(GC_Sources src/zephyrgc.cpp)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

ADD_EXECUTABLE(gc ${GC_Sources})
