/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-06 17:27:52
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-06 17:28:45
 */


#include <iostream>
#include <gtest/gtest.h>

#include "Command.hpp"

TEST(Command, handleFunction) {
    CommandSystem::Manager m;

    TestClass1 tet1(1);
    
    m.attach("test1", CommandSystem::Command<>(x));
    std::function<void(int)> c = std::bind(&TestClass1::TestFunction, tet1, std::placeholders::_1);
    m.attach("tet1", CommandSystem::Command<int>(c));
    m.execute("test1");
    m.execute("tet1", 123);
}