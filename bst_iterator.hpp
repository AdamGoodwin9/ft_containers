#ifndef BST_ITERATOR_HPP
#define BST_ITERATOR_HPP

#include "iterator.hpp"
#include "bst.hpp"

namespace ft
{
    template <typename T, class Compare>
    class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename T::value_type value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;


    private:
        T *node;
        Compare compare;

    public:
        bst_iterator &operator=(const bst_iterator &that)
        {
            if (*this == that)
                return (*this);
            this->_node = that._node;
            // this->_last_node = that._last_node;
            this->_comp = that._comp;
            return (*this);
        }

        bool operator==(const bst_iterator &that)
        {
            return (this->_node == that._node);
        }

        bool operator!=(const bst_iterator &that)
        {
            return (this->_node != that._node);
        }

        reference operator*() const
        {
            return (this->_node->value);
        }

        pointer operator->() const
        {
            return (&this->_node->value);
        }
    };
}

#endif