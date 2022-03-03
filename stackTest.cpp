#include "Tests.hpp"

void stackTest()
{
	std::cout << "==========================TESTING STACK=====================================\n\n";

	std::cout << "EMPTY TEST\n";
	lib::stack<int> emptier;
	int sum (0);

	for (int i=1;i<=10;i++) emptier.push(i);

	while (!emptier.empty())
	{
		sum += emptier.top();
		emptier.pop();
  	}
  	std::cout << "total: " << sum << "\n\n";


	std::cout << "SIZE TEST\n";
	lib::stack<int> sizer;
	std::cout << "0. size: " << sizer.size() << '\n';

	for (int i=0; i<5; i++) sizer.push(i);
	std::cout << "1. size: " << sizer.size() << '\n';

	sizer.pop();
	std::cout << "2. size: " << sizer.size() << "\n\n";


	std::cout << "TOP TEST\n";
	lib::stack<int> topper;

	topper.push(10);
	topper.push(20);

	topper.top() -= 5;
	std::cout << "mystack.top() is now " << topper.top() << "\n\n";


	std::cout << "PUSH / POP TEST\n";
	lib::stack<int> pushpop;

	for (int i=0; i<5; ++i) pushpop.push(i);

	std::cout << "Popping out elements...";
	while (!pushpop.empty())
	{
		std::cout << ' ' << pushpop.top();
		pushpop.pop();
	}
	std::cout << "\n\n";
}
