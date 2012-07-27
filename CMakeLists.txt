PROJECT(ZephyrGC)

ENABLE_TESTING()
#CTEST_FULL_OUTPUT

SET(GC_Sources src/zephyrgc.cpp)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

ADD_TEST(cppcheck cppcheck --template=gcc --enable=all ${GC_Sources})
ADD_TEST(valgrind valgrind ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}gc)

ADD_EXECUTABLE(gc ${GC_Sources})


