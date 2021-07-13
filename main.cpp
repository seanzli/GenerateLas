/*
 * @Description: 
 * @Author: Sean
 * @Date: 2021-07-13 21:11:37
 * @LastEditTime: 2021-07-13 21:53:24
 * @LastEditors: Sean
 * @Reference: 
 */
#include <iostream>

#include <GenerateLas.hpp>


#include "StructDef.h"

int main(int argc, char* argv[]) {

    Point<float> a(1.1,2.2,3.3);
    Point<double> b(1.1,2.2,3.3);

    std::cout << a + b;

    return 0;
}