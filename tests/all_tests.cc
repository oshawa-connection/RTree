
#include <gtest/gtest.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    srand(0);
    return RUN_ALL_TESTS();
}