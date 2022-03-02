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
        typedef typename bst_node<T> node;

    private:
        node *_node;
        
        bst_iterator() : _node(NULL);
        {
        }

    public:

        bst_iterator(node *start) : _node(start)
        {
        }

        bst_iterator(bst_iterator that) : _node(that._node)
        {
        }

        bst_iterator &operator=(const bst_iterator &that)
        {
            if (*this == that)
                return (*this);
            this->_node = that._node;
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
                if (_node->parent->left == _node)
                {
                    _node = _node->parent;    
                    return (*this);              
                }
                _node = _node->parent;
            }
            _node = NULL;
            return (*this);
        }

        bst_iterator operator++(int)
        {
            bst_iterator tmp(*this);
            operator++();
            return tmp;
        }

        bst_iterator& operator--()
        {
            if (_node->left != NULL)
            {
                _node = _node->left;
                while(_node->right)
                {
                    _node = _node->right;
                }
                return (*this);
            }
            while (_node->parent != NULL)
            {
                if (_node->parent->right == _node)
                {
                    _node = _node->parent;    
                    return (*this);              
                }
                _node = _node->parent;
            }
            _node = NULL;
            return (*this);
        }

        bst_iterator operator--(int)
        {
            bst_iterator tmp(*this);
            operator--();
            return tmp;
        }
    };
}

#endif