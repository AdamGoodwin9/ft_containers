#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace me
{
    struct input_iterator_tag { };

    struct output_iterator_tag { };

    struct forward_iterator_tag { };

    struct bidirectional_iterator_tag { };

    struct random_access_iterator_tag { };

    template   <class Category,
                class T,
                class Distance = ptrdiff_t,
                class Pointer = T*,
                class Reference = T&>
    struct iterator
    {
        public:
            typedef Category iterator_category;
            typedef T value_type;
            typedef Distance difference_type;
            typedef Pointer pointer;
            typedef Reference reference;
    };

    template <class T>
    class bidirectional_iterator : me::iterator<me::bidirectional_iterator_tag, T>
    {
        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::iterator_category     iterator_category;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::value_type            value_type;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::difference_type       difference_type;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::pointer               pointer;

        typedef typename me::iterator<me::bidirectional_iterator_tag, T>::reference             reference;

        private:
            pointer _elem;
    };

    template <class Iterator> class iterator_traits;
    template <class T> class iterator_traits<T*>;
    template <class T> class iterator_traits<const T*>;
}

#endif
