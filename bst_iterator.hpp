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
        bst_node<T> *node;
        Compare compare;

    public:

        bst_iterator()
        {

        }

        bst_iterator()
        {

        }

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

        bst_iterator& operator++()
        {
            if (_node->right != NULL)
            {
                _node = _node->right;
                while(_node->left)
                {
                    _node = _node->left;
                }
                return (*this);
            }
            while (_node->parent != NULL)
            {
                if (_node->parent == NULL)
                {
                    _node = NULL;
                    return (*this);
                }
                if (_node->parent->left == _node)
                {
                    _node = _node->parent;    
                    return (*this);              
                }
                _node = _node->parent;
            }
        }
    };
}

#endif