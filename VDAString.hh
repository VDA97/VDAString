#ifndef __VDASTRING__H__
#define __VDASTRING__H__
#include <cstdio>
#include <cstring> //for strlen().
#include <memory>

namespace vda
{
    constexpr size_t _vdastring_max_len = 65535;
    constexpr size_t _vdastring_max_split = 1023;

    class VDAString
    {
        char const *_str = nullptr; // char const makes this pointer immutable.
        size_t _str_len = 0;

        // Regarding data management
        typedef std::shared_ptr<VDAString> _vdasp;    //
        typedef std::unique_ptr<_vdasp[]> _split_ptr; // We could use stl vector for this
        // 1. Its important that this class actually manage the memory for the array
        // 2. Unique ptr is the only smart pointer class that natively support arrays
        mutable _split_ptr _split_array; // mutable here is to work with const parameters.
        mutable size_t _split_count = 0;

        void _reset_split_array() const;
        void _append_split_array(const VDAString &s) const; // const here means no modifications on the member variables are possible.

    public:
        VDAString();
        VDAString(const char *s);     // Parameterized constructor, will not change the content pf the value.
        VDAString(const VDAString &); // Copy Consttructor
        VDAString(VDAString &&) noexcept;
        ~VDAString();
        // void setString(const char *s);
        // const char *getString() const;

        // data management
        const char *alloc_str(size_t sz); // smart alloc string;
        void reset();
        void swap(VDAString &other);
        const char *c_str() const;          // getter
        const char *copy_str(const char *); // alloc and copy

        // copy_and_swap assignment operator
        VDAString &operator=(VDAString other);
        // concatenation operator
        VDAString &operator+=(const char *rhs);      // for c-string
        VDAString &operator+=(const VDAString &rhs); // for VDAString object
        // subscript operator
        const char operator[](const int index) const;
        // comparison operator

        // conversion operators
        operator const char *() const; // c-string type
    };
}

#endif // __VDASTRING__H__
