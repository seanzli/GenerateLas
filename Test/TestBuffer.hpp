#include <iostream>
#include <gtest/gtest.h>

#include "Buffer.hpp"

TEST(BufferTest, handleFunction) { 
    // Buffer<double> a;
    // ASSERT_EQ(a.max_size(), 500000) << "default size";
    Buffer<double> b(100);
    ASSERT_EQ(b.max_size(), 100) << "define size";

    std::vector<double> test_v;
    for (int i = 0; i < 100; i++) {
        b.push_back(i);
        test_v.push_back(i);
    }
    for (int i = 0; i < 100; i++)
        ASSERT_EQ(b.pop_front(), i) << "pop_front value: " << i;

    b.clear();
    ASSERT_EQ(b.size(), 0) << "clear";

    b.push_back(test_v);
    ASSERT_EQ(b.size(), test_v.size()) << "pop_back vector";
    for (int i = 0; i < 100; i++)
        ASSERT_EQ(b.pop_back(), 99 - i) << "pop_back value";
        
}