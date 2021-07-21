#include <iostream>
#include <gtest/gtest.h>

// #include "TestStructDef.hpp"
// #include "TestCoordinate.hpp"
// #include "TestDecodeFile.hpp"
#include "TestBuffer.hpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}