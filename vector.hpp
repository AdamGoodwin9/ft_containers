#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"

#define THROW_EXCEEDS_MAXSIZE std::__throw_invalid_argument("argument exceeds max_size()");
#define THROW_OUT_OF_RANGE std::__throw_out_of_range("argument out of range");


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

        typedef me::random_access_iterator<value_type> iterator;
        typedef me::random_access_iterator<const value_type> const_iterator;

        typedef me::reverse_iterator<iterator> reverse_iterator;
        typedef me::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef typename me::iterator_traits<iterator>::difference_type difference_type;
        
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
#pragma region Iterators //done
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
            return reverse_iterator(this->end());
        }

        const_reverse_iterator rbegin() const
        {
            return reverse_iterator(this->end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(this->begin());
        }

        const_reverse_iterator rend() const
        {
            return reverse_iterator(this->begin());
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
            while (new_capacity < n)
            {
                new_capacity *= 2;
            }
            
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
        void assign (InputIterator first, InputIterator last) //maybe just call insert?
        {
            //call erase, 
			// clear();

            // size_type n;
			// for (InputIterator temp = first, n = 0; temp != last; temp++, n++);

			// reserve(n);

			// while (n-- != 0)
            // {
			// 	_alloc.construct(_first + _size++, *first++);
            // }
        }

        void assign (size_type n, const value_type& val)
        {
            // clear();
			// if (n > _capacity)
			// {
			// 	_allocator.deallocate(_first, _capacity);
            //     _capacity = n;
			// 	_first = _alloc.allocate(_capacity);
			// }

			// while (n-- != 0)
            // {
			// 	_alloc.construct(_first + _size++, val);
            // }
        }

        void push_back (const value_type& val)
        {

        }

        void pop_back()
        {

        }

        iterator insert (iterator position, const value_type& val)
        {
            size_type i = position - begin(); //get index of position in vector

            insert(position, 1, val);

            //calculate position of inserted element in case of resizing
            return begin() + i;
        }

        void insert (iterator position, size_type n, const value_type& val)
        {
            size_type index = position - begin();
            reserve(_size + n);
            iterator pos = begin() + index;

            //move all elements over by n (from end to pos)
            for (iterator it = end() - 1; it >= pos; it--)
            {
                *(it + n) = *it;
            }
            
            //construct n new elements at pos
            for (size_type i = 0; i < n; i++)
            {
                _allocator.construct(pos + i, val);
                _size++;
            }
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last)
        {
            // if (!(me::is_iterator_tagged<typename me::iterator_traits<InputIterator>::iterator_category >::value))
            //         throw;
            //get count of total elements to insert
            size_type n = 0;
			for (InputIterator ii = first; ii != last; ii++)
            {
				n++;
            }
            
			size_type index = position - begin();
            reserve(_size + n);
            iterator pos = begin() + index;

            //move all elements over by n (from end to pos)
            for (iterator it = end() - 1; it >= pos; it--)
            {
                *(it + n) = *it;
            }
            
            //construct n new elements at pos
            for (size_type i = 0; i < n; i++)
            {
                _allocator.construct(pos + i, *first);
                first++;
                _size++;
            }
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