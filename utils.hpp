#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
    template<bool Condition, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

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

#pragma region nullPointer

    static class nullptr_t
    {
    public:
        template <class T>
        operator T *() const { return (0); }

        template <class C, class T>
        operator T C::*() const { return (0); }

    private:
        void operator&() const;

    } u_nullptr = {};

#pragma endregion nullPointer

#pragma region pair

    template <class T1, class T2>
    struct pair
    {
    public:
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;

        pair(): first(), second()
        {
        }

        template <class U, class V>
        pair(const pair<U, V> &p) : first(p.first), second(p.second)
        {
        }

        pair(const T1 &a, const T2 &b) : first(a), second(b)
        {
        }

        pair &operator=(const pair &p)
        {
            this->first = p.first;
            this->second = p.second;
            return (*this);
        }
    };

    template <class T1, class T2>
    bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template <class T1, class T2>
    bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (ft::pair<T1, T2>(x, y));
    }

#pragma endregion pair

#pragma region lexicographicalCompare

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 start1, InputIterator1 end1,
                                 InputIterator2 start2, InputIterator2 end2)
    {
        while (start1 != end1)
        {
            if (start2 == end2 || *start2 < *start1)
                return false;
            else if (*start1 < *start2)
                return true;
            ++start1;
            ++start2;
        }
        return (start2 != end2);
    }

#pragma endregion lexicographicalCompare

#pragma region equal

    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
            {
                return false;
            }
            ++first1;
            ++first2;
        }
        return true;
    }

#pragma endregion

}

#endif
