cmake_minimum_required(VERSION 2.6)

PROJECT(ZephyrGC)

INCLUDE(cmake/CppcheckTargets.cmake)

ENABLE_TESTING()
#CTEST_FULL_OUTPUT

SET(GC_Sources src/zephyrgc.cpp)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
SET(CheckSources cppcheck --template=gcc --enable=all ${GC_Sources})
ADD_TEST(cppcheck ${CheckSources})
ADD_TEST(valgrind valgrind ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}gc)



ADD_EXECUTABLE(gc ${GC_Sources})

ADD_CPPCHECK(gc UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FAIL_ON_WARNINGS)

ADD_CUSTOM_TARGET(Cppcheck ALL ${CheckSources} COMMENT Checking sources with cppcheck)
ADD_DEPENDENCIES(gc Cppcheck)
