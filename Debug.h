#pragma once
#include <iostream>

#define watch(a) std::cout << (#a) << " = " << (a) << std::endl;
#define breakpoint() int a; std::cin >> a;