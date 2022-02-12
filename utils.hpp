#ifndef UTILS_HPP
#define UTILS_HPP

namespace me
{
    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };
    static class nullptr_t
    {
    public:
        /*
        ** @brief For conversion to any type
        ** of null non-member pointer.
        */
        template <class T>
        operator T *() const { return (0); }

        /*
        ** @brief For conversion to any type of null
        ** member pointer.
        */
        template <class C, class T>
        operator T C::*() const { return (0); }

    private:
        /*
        ** @brief It's imposible to get an address of
        ** a nullptr.
        */
        void operator&() const;

    } u_nullptr = {};
}

#endif