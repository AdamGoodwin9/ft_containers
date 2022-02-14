#ifndef TESTS_HPP
#define TESTS_HPP

#ifdef USE_STD
	#include <vector>
	namespace lib = std;
#else
	#include "vector.hpp"
    namespace lib = ft;
#endif

void vectorTest();
void stackTest();

#endif