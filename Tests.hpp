#ifndef TESTS_HPP
#define TESTS_HPP

#ifdef USE_STD
	#include <vector>
	#include <stack>
	#include <map>
	namespace lib = std;
#else
	#include "vector.hpp"
	#include "stack.hpp"
	#include "map.hpp"
    namespace lib = ft;
#endif

#include <iostream>

void vectorTest();
void stackTest();
void mapTest();

#endif