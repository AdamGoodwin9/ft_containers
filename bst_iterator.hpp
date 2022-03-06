#ifndef BST_ITERATOR_HPP
#define BST_ITERATOR_HPP

#include "iterator.hpp"
#include "bst.hpp"

#define MAP_ITERATOR_OUT_OF_RANGE "Map iterator out of range"

namespace ft
{
    template <typename T>
    class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef T value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
        typedef bst_node<value_type> node;

    private:
        node *_node;
        node *_end_node;

    public:
        node* get_node() const { return _node; }
        node* get_end_node() const { return _end_node; }

        bst_iterator() : _node(NULL), _end_node(NULL)
        {
        }

        bst_iterator(node *start, node *end_node) : _node(start), _end_node(end_node)
        {
        }

        bst_iterator(bst_iterator const &that) : _node(that._node), _end_node(that._end_node)
        {
        }

        virtual ~bst_iterator() {}


        bst_iterator &operator=(const bst_iterator &that)
        {
            if (*this == that)
                return (*this);
            this->_node = that._node;
            this->_end_node = that._end_node;
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
            return (this->_node->val);
        }

        pointer operator->() const
        {
            return (&this->_node->val);
        }

        bst_iterator &operator++()
        {
            if (_node == _end_node)
                return (*this);
            if (_node->right != NULL)
            {
                _node = _node->right;
                while (_node->left)
                {
                    _node = _node->left;
                }
                return (*this);
            }
            while (_node->parent != NULL)
            {
            // std::cout << _node->val.first << " - hey there\n";
                if (_node->parent->left == _node)
                {
                    _node = _node->parent;
                    return (*this);
                }
                _node = _node->parent;
            }
            _node = _end_node;
            return (*this);
        }

        bst_iterator operator++(int)
        {
            bst_iterator tmp(*this);
            operator++();
            return tmp;
        }

        bst_iterator &operator--()
        {
            if (_end_node == _node)
            {
                _node = _end_node->parent;
                return (*this);
            }
            if (_node->left != NULL)
            {
                _node = _node->left;
                while (_node->right)
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
            throw std::out_of_range(MAP_ITERATOR_OUT_OF_RANGE);
            // _node = NULL;
            // return (*this);
        }

        bst_iterator operator--(int)
        {
            bst_iterator tmp(*this);
            operator--();
            return tmp;
        }
    };

    template <typename T>
    class bst_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef T value_type;
        typedef typename ft::const_iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
        typedef typename ft::const_iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
        typedef typename ft::const_iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
        typedef typename ft::const_iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
        typedef bst_node<value_type> node;

    private:
        node *_node;
        node *_end_node;

    public:
        node* get_node() const { return _node; }
        node* get_end_node() const { return _end_node; }

        bst_const_iterator() : _node(NULL), _end_node(NULL)
        {
        }

        bst_const_iterator(node *start, node *end_node) : _node(start), _end_node(end_node)
        {
        }

        bst_const_iterator(bst_const_iterator const &that) : _node(that.get_node()), _end_node(that.get_end_node())
        {
        }
        bst_const_iterator(bst_iterator<T> const &that) : _node(that.get_node()), _end_node(that.get_end_node())
        {
        }
        
        virtual ~bst_const_iterator() {}

        bst_const_iterator &operator=(const bst_const_iterator &that)
        {
            if (*this == that)
                return (*this);
            this->_node = that._node;
            this->_end_node = that._end_node;
            return (*this);
        }

        bool operator==(const bst_const_iterator &that)
        {
            return (this->_node == that._node);
        }

        bool operator!=(const bst_const_iterator &that)
        {
            return (this->_node != that._node);
        }

        reference operator*() const
        {
            return (this->_node->val);
        }

        pointer operator->() const
        {
            return (&this->_node->val);
        }

        bst_const_iterator &operator++()
        {
            if (_node == _end_node)
                return (*this);
            if (_node->right != NULL)
            {
                _node = _node->right;
                while (_node->left)
                {
                    _node = _node->left;
                }
                return (*this);
            }
            while (_node->parent != NULL)
            {
            // std::cout << _node->val.first << " - hey there\n";
                if (_node->parent->left == _node)
                {
                    _node = _node->parent;
                    return (*this);
                }
                _node = _node->parent;
            }
            _node = _end_node;
            return (*this);
        }

        bst_const_iterator operator++(int)
        {
            bst_const_iterator tmp(*this);
            operator++();
            return tmp;
        }

        bst_const_iterator &operator--()
        {
            if (_end_node == _node)
            {
                _node = _end_node->parent;
                return (*this);
            }
            if (_node->left != NULL)
            {
                _node = _node->left;
                while (_node->right)
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
            throw std::out_of_range(MAP_ITERATOR_OUT_OF_RANGE);
            // _node = NULL;
            // return (*this);
        }

        bst_const_iterator operator--(int)
        {
            bst_const_iterator tmp(*this);
            operator--();
            return tmp;
        }
    };
}

#endif
