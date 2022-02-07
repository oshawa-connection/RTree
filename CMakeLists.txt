# Make sure to do "cmake -DCMAKE_C_COMPILER=/usr/bin/gcc" before running this the first time.
# after that, it _should_ be cached.


cmake_minimum_required(VERSION 3.14)
# TODO: do this from cmake options instead.
SET(CMAKE_BUILD_TYPE Debug)


PROJECT (RTree)
set(CMAKE_VERBOSE_MAKEFILE ON)
# GoogleTest requires at least C++11
SET(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")


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
  src/BBox.c 
  src/Node.c
  src/PriorityQueue.c
  src/RTree.c
  src/Point.c
  tests/all_tests.cc
  tests/node_test.cc
  tests/RTree_test.cc
  tests/point_tests.cc
  tests/bbox_tests.cc
  tests/priority_queue_test.cc
)

target_link_libraries(
  all_tests
  gtest_main
)


include(GoogleTest)
gtest_discover_tests(all_tests)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Glib REQUIRED)
include_directories(${Glib_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Glib_LIBRARIES})


#main
add_executable(
  rtree
  src/main.c 
  src/BBox.c 
  src/Node.c
  src/RTree.c
  src/Point.c
  src/PriorityQueue.c
)

target_link_libraries(rtree ${LIBS} m)
target_link_libraries(all_tests ${LIBS} m)

message(${Glib_INCLUDE_DIRS})
