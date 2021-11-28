
#include <gtest/gtest.h>
#include "./hello_test.cc"
#include "./RTree_test.cc"
// #include "./node_test.cc"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}