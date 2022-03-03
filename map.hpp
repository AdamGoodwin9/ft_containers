#ifndef MAP_HPP
#define MAP_HPP

#include "iterator.hpp"
#include "bst.hpp"
#include "bst_iterator.hpp"
#include <memory>

namespace ft
{
    template <class Key,                                       // map::key_type
              class T,                                         // map::mapped_type
              class Compare = std::less<Key>,                  // map::key_compare
              class Alloc = std::allocator<pair<const Key, T> >// map::allocator_type
              >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef ft::bst_iterator<value_type> iterator;
        typedef ft::bidirectional_iterator<const value_type> const_iterator; // TO do 

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

        typedef typename allocator_type::size_type size_type;

        class value_compare
        {
            friend class map;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

    private:
        allocator_type _allocator;
        bst<value_type, Compare, Alloc> _tree;
        Compare _comp;

    public:
        // Member functions

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            : _comp(comp), _allocator(alloc), _tree()
        {
        }

        template <class InputIterator>
        map(typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
            const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
        {
            insert(first, last);
        }

        map(const map &x) : _comp(x._comp), _tree(x._tree) { }

        ~map() { }

        map &operator=(const map &x)
        {
            _comp = x._comp;
            _tree = x._tree;
            return *this;
        }

#pragma region Iterators
        iterator begin()
        {
            return new_iterator(_tree.min(_tree.get_root()));
        }

        const_iterator begin() const
        {
            return new_const_iterator(_tree.min(_tree.get_root()));
        }

        iterator end()
        {
            return new_iterator(_tree.get_end_node());
        }

        const_iterator end() const
        {
            return new_const_iterator(_tree.get_end_node());
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

        bool empty() const
        {
            return _tree.size() == 0;
        }

        size_type size() const
        {
            return _tree.size();
        }

        size_type max_size() const
        {
            return _allocator.max_size();
        }

#pragma endregion Capacity

#pragma region ElementAccess //done

        mapped_type &operator[](const key_type &k)
        {
            return insert(ft::make_pair(k, mapped_type())).first->second;
        }

#pragma endregion ElementAccess

#pragma region Modifiers //done

        pair<iterator, bool> insert(const value_type &val)
        {
            iterator it = find(val.first);

			if (it != end())
            {
				return ft::make_pair(it, false);
            }
            else
            {
                return ft::make_pair(new_iterator(_tree.insert(val)), true);
            }
        }

        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
			return insert(val).first;
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
				insert(*first++);
            }
        }

        void erase(iterator position)
        {
            _tree.erase(*position);
        }

        size_type erase(const key_type &k)
        {
            return !(!_tree.erase(ft::make_pair<Key, T>(k, NULL)));
        }

        void erase(iterator first, iterator last)
        {
            iterator position = first;
            
            while (position != last)
            {
                _tree.erase(*position);
                position++;
            }
        }

        void swap(map &x)
        {
            _tree.swap(x._tree);
        }

        void clear()
        {
            _tree.clear();
        }

#pragma endregion Modifiers

#pragma region Observers //done

        key_compare key_comp() const
        {
            return key_compare();
        }

        value_compare value_comp() const
        {
            return value_compare(key_comp());
        }

#pragma endregion Observers

#pragma region Operations //done

        iterator find(const key_type &k)
        {
            return new_iterator(_tree.search(ft::make_pair(k, mapped_type())));
        }

        const_iterator find(const key_type &k) const
        {
            return new_const_iterator(_tree.search(ft::make_pair(k, mapped_type())));
        }

        size_type count(const key_type &k) const
        {
            return !(!_tree.search(ft::make_pair<Key, T>(k, NULL)));
        }

        iterator lower_bound(const key_type &k)
        {
            for (iterator it = begin(); it != end(); it++)
            {
                if (!_comp((*it).first, k))
                {
                    return it;
                }
            }
            return end();
        }

        const_iterator lower_bound(const key_type &k) const
        {
            for (const_iterator it = begin(); it != end(); it++)
            {
                if (!_comp((*it).first, k))
                {
                    return it;
                }
            }
            return end();
        }

        iterator upper_bound(const key_type &k)
        {
            for (iterator it = begin(); it != end(); it++)
            {
                if (_comp(k, (*it).first))
                {
                    return it;
                }
            }
            return end();
        }

        const_iterator upper_bound(const key_type &k) const
        {
            for (const_iterator it = begin(); it != end(); it++)
            {
                if (_comp(k, (*it).first))
                {
                    return it;
                }
            }
            return end();
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

#pragma endregion Operations

#pragma region Allocator //done

        allocator_type get_allocator() const
        {
            return _allocator;
        }

#pragma endregion

    private:
        iterator new_iterator(bst_node<value_type> *node)
        {
            return iterator(node, _tree.get_end_node());
        }
        const_iterator new_const_iterator(bst_node<value_type> *node)
        {
            return const_iterator(node, _tree.get_end_node());
        }

    };
}

#endif
