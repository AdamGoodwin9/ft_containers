#ifndef STACK_HPP
#define STACK_HPP

#include "iterator.hpp"
#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename container_type::size_type size_type;

    protected:
        container_type _underCont;
    public:
        explicit stack(const container_type &ctnr = container_type()) : _underCont(ctnr)
        {
        }

        ~stack()
        {
        }
        
        bool empty() const
        {
            return _underCont.empty();
        }
        
        size_type size() const
        {
            return _underCont.size();
        }

        value_type &top()
        {
            return *(_underCont.end() - 1);
        }
        
        const value_type &top() const
        {
            return *(_underCont.end() - 1);
        }

        void push (const value_type& val)
        {
            _underCont.push_back(val);
        }

        void pop()
        {
            _underCont.pop_back();
        }

    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs._underCont == rhs._underCont;
    }
    
    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs._underCont != rhs._underCont;
    }
    
    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs._underCont < rhs._underCont;
    }
    
    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs._underCont <= rhs._underCont;
    }
    
    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs._underCont > rhs._underCont;
    }
    
    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs._underCont >= rhs._underCont;
    }
}

#endif