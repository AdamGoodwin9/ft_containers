#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"

namespace me
{
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
    }

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
}

#endif