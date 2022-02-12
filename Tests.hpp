#ifndef TESTS_HPP
#define TESTS_HPP

#ifdef USE_STD
	#include <vector>
	namespace lib = std;
#else
	#include "vector.hpp"
    namespace lib = me;
#endif

void vectorTest();

#endif