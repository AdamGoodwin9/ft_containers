#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include <memory>

#define THROW_EXCEEDS_MAXSIZE std::__throw_invalid_argument("argument exceeds max_size()");
#define THROW_OUT_OF_RANGE std::__throw_out_of_range("argument out of range");


namespace ft
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

        typedef ft::random_access_iterator<value_type> iterator;
        typedef ft::random_access_iterator<const value_type> const_iterator;

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        
        typedef typename allocator_type::size_type size_type;

    private:
        pointer _array;
        size_type _size;
        size_type _capacity;
        allocator_type  _allocator;

    public:
        // Member functions
        explicit vector(const allocator_type &alloc = allocator_type())
            : _array(u_nullptr), _size(0), _capacity(0), _allocator(alloc)
        {
        }

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
            : _array(u_nullptr), _size(0), _capacity(0), _allocator(alloc)
        {
            assign(n, val);
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            :  _array(u_nullptr), _size(0), _capacity(0), _allocator(alloc)
        {
            assign(first, last);
        }

        vector(const vector& x)
            : _array(u_nullptr), _size(0), _capacity(0), _allocator(x._allocator)
        {
            *this = x;
        }

        ~vector()
        {
            for (size_type i = 0; i < _size; i++)
            {
				_allocator.destroy(_array + i);
            }
            _allocator.deallocate(_array, _capacity);
        }

        vector& operator=(const vector& x)
        {
            if (x == *this)
                return *this;
            assign(x.begin(), x.end());
            return *this;
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
            if (n >= _size) THROW_OUT_OF_RANGE;
            
            return (*this)[n];
        }

        const_reference at (size_type n) const
        {
            if (n >= _size) THROW_OUT_OF_RANGE;

            return (*this)[n];
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
        void assign (InputIterator first, InputIterator last,
			        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
        {
            clear();
            insert(begin(), first, last);
        }

        void assign (size_type n, const value_type& val)
        {
            clear();
            insert(begin(), n, val);
        }

        void push_back (const value_type& val)
        {
            insert(end(), val);
        }

        void pop_back()
        {
            _allocator.destroy(_array + _size - 1);
            _size--;
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
                _allocator.construct(_array + index + i, val);
                _size++;
            }
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
			        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
        {
       
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
                _allocator.construct(_array + index + i, *first);
                first++;
                _size++;
            }
        }

        iterator erase (iterator position)
        {
            return erase(position, position + 1);
        }

        iterator erase (iterator first, iterator last)
        {
            size_type count = 0;

            while (first != last)
            {
                _allocator.destroy(&(*first));
                first++;
                count++;
            }

            iterator ret = last - count;
            while (last != end())
            {
                *(last - count) = *last;
                last++;
            }
            _size -= count;
            
            return ret;
        }

        void swap (vector& x)
        {
            if (*this == x) return;

            pointer tmpArray = x._array;
            size_type tmpSize = x._size;
            size_type tmpCapacity = x._capacity;
            allocator_type tmpAllocator = x._allocator; 
            
            x._array = this->_array;
            x._size = this->_size;
            x._capacity = this->_capacity;
            x._allocator = this->_allocator;
            
            this->_array = tmpArray;
            this->_size = tmpSize;
            this->_capacity = tmpCapacity;
            this->_allocator = tmpAllocator;
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
    //Non-member functions

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        typename ft::vector<T>::const_iterator first1 = lhs.begin();
        typename ft::vector<T>::const_iterator first2 = rhs.begin();
        while (first1 != lhs.end())
        {
            if (first2 == rhs.end() || *first1 != *first2)
                return (false);
            ++first1;
            ++first2;
        }
        return (true);
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

}

#endif