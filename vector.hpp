#ifndef vector_HPP
#define vector_HPP

#include "iterator.hpp"

namespace lib = std;

namespace me
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {   
    public:
        //Member types
        typedef T value_type;
        typedef Alloc allocator_type;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

//MUST IMPLEMENT NEW TYPES FOR THESE FROM SCRATCH
        typedef std::vector<int>::iterator iterator;
        typedef std::vector<int>::const_iterator const_iterator;
        typedef std::vector<int>::reverse_iterator reverse_iterator;
        typedef std::vector<int>::const_reverse_iterator const_reverse_iterator;
        
        typedef iterator_traits<iterator>::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;

    private:
        pointer _array;
        size_type _size;
        size_type _capacity;
        allocator_type  _allocator;

    public:
        //Member functions
        explicit vector (const allocator_type& alloc = allocator_type())
                : _array(NULL), _size(0), _capacity(0)
        {

        }
	
        explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
        {

        }

        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
        {
            
        }

        vector(const vector& x)
        {
            *this = x;
        }

        ~vector()
        {

        }

        vector& operator=(const vector& x)
        {
            
        }
#pragma region Iterators
        iterator begin()
        {

        }

        const_iterator begin() const
        {

        }

        iterator end()
        {

        }

        const_iterator end() const
        {
            
        }

        reverse_iterator rbegin()
        {

        }

        const_reverse_iterator rbegin() const
        {

        }

        reverse_iterator rend()
        {

        }

        const_reverse_iterator rend() const
        {

        }
#pragma endregion Iterators
#pragma region Capacity
        size_type size() const
        {
            return _size;
        }

        size_type max_size() const
        {
            return _allocator.max_size();
        }
        
        void resize (size_type n, value_type val = value_type())
        {
            if (n > max_size()) throw std::invalid_argument("n exceeds max_size()");

            if (n <= _size)
            {
                for (size_t i = n; i < _size; i++)
                {
                    _allocator.destroy(_array[i]);
                }
                _size = n;
            }
            else
            {
                insert(_array + _size, n - _size, val);
            }
        }

        size_type capacity() const
        {
            return _capacity;
        }

        bool empty() const
        {
            return _size == 0;
        }

        void reserve (size_type n)
        {

        }
#pragma endregion Capacity
#pragma region Element access
        reference operator[] (size_type n)
        {

        }

        const_reference operator[] (size_type n) const
        {

        }

        reference at (size_type n)
        {
            
        }

        const_reference at (size_type n) const
        {

        }

        reference front()
        {

        }

        const_reference front() const
        {

        }

        reference back()
        {

        }

        const_reference back() const
        {

        }
#pragma endregion Element access
#pragma region Modifiers
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last)
        {

        }

        void assign (size_type n, const value_type& val)
        {

        }

        void push_back (const value_type& val)
        {

        }

        void pop_back()
        {

        }

        iterator insert (iterator position, const value_type& val)
        {
            //_THROW_BAD_ALLOC; //on _allocator fail?
        }

        void insert (iterator position, size_type n, const value_type& val)
        {

        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last)
        {

        }

        iterator erase (iterator position)
        {

        }

        iterator erase (iterator first, iterator last)
        {

        }

        void swap (vector& x)
        {

        }

        void clear()
        {

        }
#pragma endregion Modifiers
#pragma region Allocator //done
        allocator_type get_allocator() const
        {
            return _allocator;
        }
#pragma endregion Allocator
    };
}

#endif