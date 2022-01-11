#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace me
{
#pragma region is_integral

    template <bool is_integral, typename T>
    struct is_integral_s
    {
        typedef T type;
        static const bool value = is_integral;
    };

    template <typename>
    struct is_integral_type : public is_integral_s<false, bool>
    {
    };

    template <>
    struct is_integral_type<bool> : public is_integral_s<true, bool>
    {
    };

    template <>
    struct is_integral_type<char> : public is_integral_s<true, char>
    {
    };

    template <>
    struct is_integral_type<signed char> : public is_integral_s<true, signed char>
    {
    };

    template <>
    struct is_integral_type<short int> : public is_integral_s<true, short int>
    {
    };

    template <>
    struct is_integral_type<int> : public is_integral_s<true, int>
    {
    };

    template <>
    struct is_integral_type<long int> : public is_integral_s<true, long int>
    {
    };

    template <>
    struct is_integral_type<long long int> : public is_integral_s<true, long long int>
    {
    };

    template <>
    struct is_integral_type<unsigned char> : public is_integral_s<true, unsigned char>
    {
    };

    template <>
    struct is_integral_type<unsigned short int> : public is_integral_s<true, unsigned short int>
    {
    };

    template <>
    struct is_integral_type<unsigned int> : public is_integral_s<true, unsigned int>
    {
    };

    template <>
    struct is_integral_type<unsigned long int> : public is_integral_s<true, unsigned long int>
    {
    };

    template <>
    struct is_integral_type<unsigned long long int> : public is_integral_s<true, unsigned long long int>
    {
    };

    template <typename T>
    struct is_integral : public is_integral_type<T>
    {
    };

#pragma endregion is_integral

#pragma region iterator_tag
    struct input_iterator_tag {};

    struct output_iterator_tag {};

    struct forward_iterator_tag {};

    struct bidirectional_iterator_tag {};

    struct random_access_iterator_tag {};

    template <bool is_valid, typename T>
    struct valid_iterator_tag_s
    {
        typedef T type;
        const static bool value = is_valid;
    };

    /* Is iter an input iterator (all except output iterator)*/

    template <typename T>
    struct is_input_iterator_tagged : public valid_iterator_tag_s<false, T>
    {
    };

    template <>
    struct is_input_iterator_tagged<me::input_iterator_tag>
        : public valid_iterator_tag_s<true, me::input_iterator_tag>
    {
    };

    template <>
    struct is_input_iterator_tagged<me::random_access_iterator_tag>
        : public valid_iterator_tag_s<true, me::random_access_iterator_tag>
    {
    };

    template <>
    struct is_input_iterator_tagged<me::bidirectional_iterator_tag>
        : public valid_iterator_tag_s<true, me::bidirectional_iterator_tag>
    {
    };

    template <>
    struct is_input_iterator_tagged<me::forward_iterator_tag>
        : public valid_iterator_tag_s<true, me::forward_iterator_tag>
    {
    };

    /* Is iterator tagged*/
    
    template <typename T>
    struct is_iterator_tagged : public valid_iterator_tag_s<false, T>
    {
    };

    template <>
    struct is_iterator_tagged<me::random_access_iterator_tag>
        : public valid_iterator_tag_s<true, me::random_access_iterator_tag>
    {
    };

    template <>
    struct is_iterator_tagged<me::bidirectional_iterator_tag>
        : public valid_iterator_tag_s<true, me::bidirectional_iterator_tag>
    {
    };

    template <>
    struct is_iterator_tagged<me::forward_iterator_tag>
        : public valid_iterator_tag_s<true, me::forward_iterator_tag>
    {
    };

    template <>
    struct is_iterator_tagged<me::input_iterator_tag>
        : public valid_iterator_tag_s<true, me::input_iterator_tag>
    {
    };

    template <>
    struct is_iterator_tagged<me::output_iterator_tag>
        : public valid_iterator_tag_s<true, me::output_iterator_tag>
    {
    };

    /* Invalid iterator tag exception */

    template <typename T>
    class InvalidIteratorException : public std::exception
    {
        private:
            std::string _msg;
        
        public :
            InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
            InvalidIteratorException (const InvalidIteratorException&) throw() {}
            InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
            virtual ~InvalidIteratorException() throw() {}
            virtual const char* what() const throw() { return (_msg.c_str()); }
    };

#pragma endregion iterator_tag

#pragma region iterator_traits

    /* Generic iterator traits */

    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;

        typedef typename Iterator::value_type value_type;

        typedef typename Iterator::pointer pointer;

        typedef typename Iterator::reference reference;

        typedef typename Iterator::iterator_category iterator_category;
    };

    /* Specializations for when the iterator is a pointer or a const pointer */

    template <class T>
    struct iterator_traits<T *>
    {
        typedef ptrdiff_t difference_type;

        typedef T value_type;

        typedef T *pointer;

        typedef T &reference;

        typedef me::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T *>
    {
        typedef ptrdiff_t difference_type;

        typedef T value_type;

        typedef const T *pointer;

        typedef const T &reference;

        typedef me::random_access_iterator_tag iterator_category;
    };

template <class InputIterator>
    typename me::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
    {
        typename me::iterator_traits<InputIterator>::difference_type rtn = 0;
        while (first != last)
        {
            first++;
            rtn++;
        }
        return (rtn);
    }

#pragma endregion iterator_traits

#pragma region iterator
    template <class Category, class T,
              class Distance = ptrdiff_t,
              class Pointer = T *,
              class Reference = T &>
    class iterator
    {
    public:
        typedef T value_type;

        typedef Distance difference_type;

        typedef Pointer pointer;

        typedef Reference reference;

        typedef Category iterator_category;
    };

    template <class T>
    class bidirectional_iterator : me::iterator<me::bidirectional_iterator_tag, T>
    {
        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::iterator_category iterator_category;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::value_type value_type;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::difference_type difference_type;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::pointer pointer;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::reference reference;

    private:
        pointer _elem;
    };
#pragma endregion iterator
   
#pragma region reverseIterator
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator iterator_type;

        typedef typename me::iterator_traits<Iterator>::iterator_category iterator_category;

        typedef typename me::iterator_traits<Iterator>::value_type value_type;

        typedef typename me::iterator_traits<Iterator>::difference_type difference_type;

        typedef typename me::iterator_traits<Iterator>::pointer pointer;

        typedef typename me::iterator_traits<Iterator>::reference reference;


        reverse_iterator()
            : _elem()
        {
        }

        explicit reverse_iterator(iterator_type iter)
            : _elem(iter)
        {
        }

        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> &rev_iter)
            : _elem(rev_iter.base())
        {
        }

        virtual ~reverse_iterator() {}

        iterator_type base() const
        {
            return (_elem);
        }

        reference operator*() const
        {
            iterator_type tmp = _elem;
            return (*(--tmp));
        }

        reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_elem - n)); }


        reverse_iterator &operator++()
        {
            --_elem;
            return (*this);
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            ++(*this);
            return (tmp);
        }

        reverse_iterator &operator+=(difference_type n)
        {
            _elem -= n;
            return (*this);
        }

        reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_elem + n)); }


        reverse_iterator &operator--()
        {
            ++_elem;
            return (*this);
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            --(*this);
            return (tmp);
        }

        reverse_iterator &operator-=(difference_type n)
        {
            _elem += n;
            return (*this);
        }

        pointer operator->() const { return &(operator*()); }

        reference operator[](difference_type n) const { return (this->base()[-n - 1]); }

    private:
        iterator_type _elem;
    };

    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator==(const reverse_iterator<Iterator_L> &lhs,
                    const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator!=(const reverse_iterator<Iterator_L> &lhs,
                    const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() != rhs.base()); }


    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> &lhs,
                   const reverse_iterator<Iterator> &rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator<(const reverse_iterator<Iterator_L> &lhs,
                   const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator<=(const reverse_iterator<Iterator_L> &lhs,
                    const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> &lhs,
                   const reverse_iterator<Iterator> &rhs) { return (lhs.base() < rhs.bash()); }

    template <class Iterator_L, class Iterator_R>
    bool operator>(const reverse_iterator<Iterator_L> &lhs,
                   const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() < rhs.base()); }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator>=(const reverse_iterator<Iterator_L> &lhs,
                    const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator>
    reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator> &rev_it) { return (rev_it + n); }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(
        const reverse_iterator<Iterator> &lhs,
        const reverse_iterator<Iterator> &rhs) { return (lhs.base() - rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator-(const reverse_iterator<Iterator_L> &lhs,
                   const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() - rhs.base()); }

#pragma endregion reverseIterator

#pragma region randomAccessIterator

    template <typename T>
    class random_access_iterator : me::iterator<random_access_iterator_tag, T>
    {
    public:
        typedef typename me::iterator<me::random_access_iterator_tag, T>::iterator_category iterator_category;

        typedef typename me::iterator<me::random_access_iterator_tag, T>::value_type value_type;

        typedef typename me::iterator<me::random_access_iterator_tag, T>::difference_type difference_type;

        typedef T *pointer;

        typedef T &reference;

        random_access_iterator(void)
            : _elem(u_nullptr)
        {
        }

        random_access_iterator(pointer elem)
            : _elem(elem)
        {
        }

        random_access_iterator(const random_access_iterator &that)
            : _elem(that._elem)
        {
        }

        virtual ~random_access_iterator() {}

        random_access_iterator &operator=(const random_access_iterator &that)
        {
            if (this == &that)
                return (*this);
            this->_elem = that._elem;
            return (*this);
        }
        pointer base() const
        {
            return (this->_elem);
        }

        reference operator*(void) const { return (*_elem); }

        pointer operator->(void) { return &(this->operator*()); }

        random_access_iterator &operator++(void)
        {
            _elem++;
            return (*this);
        }

        random_access_iterator operator++(int)
        {
            random_access_iterator rtn(*this);
            operator++();
            return (rtn);
        }

        random_access_iterator &operator--(void)
        {
            _elem--;
            return (*this);
        }

        random_access_iterator operator--(int)
        {
            random_access_iterator rtn(*this);
            operator--();
            return (rtn);
        }

        random_access_iterator operator+(difference_type n) const { return (_elem + n); }

        random_access_iterator operator-(difference_type n) const { return (_elem - n); }

        random_access_iterator &operator+=(difference_type n)
        {
            _elem += n;
            return (*this);
        }

        random_access_iterator &operator-=(difference_type n)
        {
            _elem -= n;
            return (*this);
        }

        reference operator[](difference_type n) { return (*(operator+(n))); }

        operator random_access_iterator<const T>() const
        {
            return (random_access_iterator<const T>(this->_elem));
        }

    private:
        pointer _elem;
    };

    template <typename T>
    typename me::random_access_iterator<T>::difference_type
    operator==(const me::random_access_iterator<T> lhs,
               const me::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T_L, typename T_R>
    typename me::random_access_iterator<T_L>::difference_type
    operator==(const me::random_access_iterator<T_L> lhs,
               const me::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    typename me::random_access_iterator<T>::difference_type
    operator!=(const me::random_access_iterator<T> lhs,
               const me::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T_L, typename T_R>
    typename me::random_access_iterator<T_L>::difference_type
    operator!=(const me::random_access_iterator<T_L> lhs,
               const me::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    typename me::random_access_iterator<T>::difference_type
    operator<(const me::random_access_iterator<T> lhs,
              const me::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T_L, typename T_R>
    typename me::random_access_iterator<T_L>::difference_type
    operator<(const me::random_access_iterator<T_L> lhs,
              const me::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename me::random_access_iterator<T>::difference_type
    operator>(const me::random_access_iterator<T> lhs,
              const me::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T_L,
              typename T_R>
    typename me::random_access_iterator<T_L>::difference_type
    operator>(const me::random_access_iterator<T_L> lhs,
              const me::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename me::random_access_iterator<T>::difference_type
    operator<=(const me::random_access_iterator<T> lhs,
               const me::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T_L, typename T_R>
    typename me::random_access_iterator<T_L>::difference_type
    operator<=(const me::random_access_iterator<T_L> lhs,
               const me::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename me::random_access_iterator<T>::difference_type
    operator>=(const me::random_access_iterator<T> lhs,
               const me::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T_L,
              typename T_R>
    typename me::random_access_iterator<T_L>::difference_type
    operator>=(const me::random_access_iterator<T_L> lhs,
               const me::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T>
    me::random_access_iterator<T> operator+(
        typename me::random_access_iterator<T>::difference_type n,
        typename me::random_access_iterator<T> &rai)
    {
        return (&(*rai) + n);
    }

    template <typename T>
    typename me::random_access_iterator<T>::difference_type
    operator-(const me::random_access_iterator<T> lhs,
              const me::random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template <typename T_L, typename T_R>
    typename me::random_access_iterator<T_L>::difference_type
    operator-(const me::random_access_iterator<T_L> lhs,
              const me::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }

#pragma endregion randomAccessIterator

}

#endif
