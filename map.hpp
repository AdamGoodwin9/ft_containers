#ifndef MAP_HPP
#define MAP_HPP

#include "iterator.hpp"
#include "bst.hpp"
#include <memory>

namespace ft
{

    template <class Key,                                       // map::key_type
              class T,                                         // map::mapped_type
              class Compare = std::less<Key>,              // map::key_compare
              class Alloc = std::allocator<pair<const Key, T> > // map::allocator_type
              >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef ft::bidirectional_iterator<value_type> iterator;
        typedef ft::bidirectional_iterator<const value_type> const_iterator;

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

        typedef typename allocator_type::size_type size_type;

    private:
        allocator_type _allocator;
        bst<value_type, Compare, Alloc> _tree;

    public:
        // Member functions

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            : _tree()
        {
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
        {
        }

        map(const map &x)
        {
        }

        ~map()
        {
        }

        map &operator=(const map &x)
        {
        }

#pragma region Iterators
        iterator begin()
        {
        }

        const_iterator begin() const
        {
        }

        iterator end()
        {
        }

        const_iterator end() const
        {
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

#pragma region ElementAccess

        mapped_type &operator[](const key_type &k)
        {
            value_type ret = _tree.search(make_pair<key_type, mapped_type>(k, NULL));
            return ret.second;
        }

#pragma endregion ElementAccess

#pragma region Modifiers

        pair<iterator, bool> insert(const value_type &val)
        {
            pair<iterator, bool> ret;
            ret.first = _tree.insert(val);
        }

        iterator insert(iterator position, const value_type &val)
        {
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
        }

        void erase(iterator position)
        {
        }

        size_type erase(const key_type &k)
        {
        }

        void erase(iterator first, iterator last)
        {
        }

        void swap(map &x)
        {
        }

        void clear()
        {
        }

#pragma endregion Modifiers

#pragma region Observers

        key_compare key_comp() const
        {
        }

        // value_compare value_comp() const
        // {
        // }

#pragma endregion Observers

#pragma region Operations

        iterator find(const key_type &k)
        {
            return iterator(_tree.search(make_pair(k, mapped_type())));
        }

        const_iterator find(const key_type &k) const
        {
            return const_iterator(_tree.search(make_pair(k, mapped_type())));
        }

        size_type count(const key_type &k) const
        {

        }

        iterator lower_bound(const key_type &k)
        {
        }

        const_iterator lower_bound(const key_type &k) const
        {
        }

        iterator upper_bound(const key_type &k)
        {
        }

        const_iterator upper_bound(const key_type &k) const
        {
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
        }

#pragma endregion Operations

#pragma region Allocator

        allocator_type get_allocator() const
        {
            return _allocator;
        }

#pragma endregion Allocator
    };
}

#endif
