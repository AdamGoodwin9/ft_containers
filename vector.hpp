#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"

#define THROW_EXCEEDS_MAXSIZE std::__throw_invalid_argument("argument exceeds max_size()");
#define THROW_OUT_OF_RANGE std::__throw_out_of_range("argument out of range");

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
            return _array;
        }

        const_iterator begin() const
        {
            return _array;
        }

        iterator end()
        {
            return _array + _size;
        }

        const_iterator end() const
        {
            return _array + _size;
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
#pragma region Capacity //done
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
            if (n > max_size()) THROW_EXCEEDS_MAXSIZE;

            if (n <= _size)
            {
                for (size_t i = n; i < _size; i++)
                {
                    _allocator.destroy(_array + i);
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
            if (n > max_size()) THROW_EXCEEDS_MAXSIZE;

            if (n <= _capacity) return;

            size_type new_capacity = _capacity;
            if (new_capacity == 0) new_capacity = 1;
            do
            {
                new_capacity *= 2;
            } while (new_capacity < n);
            
            pointer new_array = _allocator.allocate(new_capacity);
            for (size_type i = 0; i < _size; i++)
            {
                _allocator.construct(new_array + i, _array[i]);
            }

            _allocator.deallocate(_array, _capacity);
            _array = new_array;
            _capacity = new_capacity;
        }
#pragma endregion Capacity
#pragma region Element access //done
        reference operator[] (size_type n)
        {
            return _array[n];
        }

        const_reference operator[] (size_type n) const
        {
            return _array[n];
        }

        reference at (size_type n)
        {
            if (n < 0 || n >= _size) THROW_OUT_OF_RANGE;

            return *this[n];
        }

        const_reference at (size_type n) const
        {
            if (n < 0 || n >= _size) THROW_OUT_OF_RANGE;

            return *this[n];
        }

        reference front()
        {
            return _array[0];
        }

        const_reference front() const
        {
            return _array[0];
        }

        reference back()
        {
            return _array[_size - 1];
        }

        const_reference back() const
        {
            return _array[_size - 1];
        }
#pragma endregion Element access
#pragma region Modifiers
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last)
        {
            //range assign
        }

        void assign (size_type n, const value_type& val)
        {
            //fill assign
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
            if (*this == x) return;

            pointer tmp = x._array;
        }

        void clear()
        {
            for (size_type i = 0; i < _size; i++)
            {
                _allocator.destroy(_array + i);
            }
            _size = 0;
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