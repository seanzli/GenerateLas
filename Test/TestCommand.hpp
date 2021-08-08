/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-06 17:27:52
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-08 09:59:27
 */


#include <iostream>
#include <gtest/gtest.h>

#include "Command.hpp"

class TestClass1{
public:
    TestClass1(int _val) :val(_val) {}
    void TestFunction(int x) {
        std::cout << "TestClase1 + " << val << ", " << x << std::endl;
    }
private:
    int val;
};

int x() {
    std::cout << "x " << std::endl;
    return 0;
}

TEST(Command, handleFunction) {
    CommandSystem::Manager m;

    TestClass1 tet1(1);
    
    m.attach("test1", CommandSystem::Command<>(x));
    std::function<void(int)> c = std::bind(&TestClass1::TestFunction, tet1, std::placeholders::_1);
    m.attach("tet1", CommandSystem::Command<int>(c));
    m.execute("test1");
    m.execute("tet1", 123);
}