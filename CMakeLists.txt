# Make sure to do "cmake -DCMAKE_C_COMPILER=/usr/bin/gcc" before running this the first time.
# after that, it _should_ be cached.
# This is bad, instead, should be managed through environment variables.


cmake_minimum_required(VERSION 3.14)
# TODO: do this from cmake options instead.
SET(CMAKE_BUILD_TYPE Debug)


PROJECT (RTree)
set(CMAKE_VERBOSE_MAKEFILE ON)
# GoogleTest requires at least C++11
SET(CMAKE_CXX_STANDARD 11)



INCLUDE(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  all_tests
  src/Node.c
  tests/all_tests.cc
  tests/node_test.cc
  

)

target_link_libraries(
  all_tests
  gtest_main
)


include(GoogleTest)
gtest_discover_tests(all_tests)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#main
add_executable(
  rtree
  src/main.c 
  src/BBox.c 
  src/Node.c
  src/RTree.c
  
)

