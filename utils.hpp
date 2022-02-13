#ifndef UTILS_HPP
#define UTILS_HPP

namespace me
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
    bool operator==(const me::pair<T1, T2> &lhs, const me::pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=(const me::pair<T1, T2> &lhs, const me::pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const me::pair<T1, T2> &lhs, const me::pair<T1, T2> &rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template <class T1, class T2>
    bool operator<=(const me::pair<T1, T2> &lhs, const me::pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const me::pair<T1, T2> &lhs, const me::pair<T1, T2> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>=(const me::pair<T1, T2> &lhs, const me::pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T1, class T2>
    me::pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (me::pair<T1, T2>(x, y));
    }

#pragma endregion pair

}

#endif