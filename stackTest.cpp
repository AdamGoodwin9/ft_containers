#include <iostream>
#include "stack.hpp"

#ifndef BASE_HPP
# define BASE_HPP

# if !defined(USING_STD)
#  define TESTED_NAMESPACE ft
# else
#  define TESTED_NAMESPACE std
# endif /* !defined(STD) */

# include <iostream>
# include <string>

// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

#endif /* BASE_HPP */


template <typename T_STACK>
void	printSize(T_STACK &stck, bool print_content = 1)
{
	std::cout << "size: " << stck.size() << std::endl;
	if (print_content)
	{
		std::cout << std::endl << "Content was:" << std::endl;
		while (stck.size() != 0) {
			std::cout << "- " << stck.top() << std::endl;
			stck.pop();
		}
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T>
void stackPrint(ft::stack<T> &a)
{
    ft::stack<T> s(a);

    std::cout << "top-> ";
    while (!s.empty())
    {
        std::cout << s.top() << " - ";
        s.pop();
    }
    std::cout << std::endl;
}

#include <list>

#define TESTED_TYPE foo<int>
typedef std::list<TESTED_TYPE> container_type;
#define t_stack_ TESTED_NAMESPACE::stack<TESTED_TYPE, container_type>

int		listCopy(void)
{
	container_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	t_stack_		stck(ctnr);

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);

	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
	printSize(stck);

	return (0);
}

void stackTest()
{
    ft::stack<foo<int> > stck;
    ft::stack<foo<int> > a;
    ft::vector<foo<int> > vect(3, 100);


    ft::stack<foo<int> > b(vect);

    printSize(b);

    a.push(2);
    a.push(3);
    a.push(4);
    stackPrint(a);
    std::cout << "size" << a.size() << ";\nhey " << a.top() << "\n";
    a.pop();
    std::cout << "size" << a.size() << ";\nhey " << a.top() << "\n";
    stackPrint(a);

    std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
    
    std::cout << "a == s : " << (a == stck) << "| a <= s :" << (a <= stck) << "\n";
    printSize(a);
    printSize(stck);
    listCopy();
}
