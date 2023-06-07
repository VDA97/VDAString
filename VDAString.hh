#ifndef __VDASTRING__H__
#define __VDASTRING__H__
#include <cstdio>
#include <cstring> //for strlen().
#include <cstdarg> //for using va_start, see VDAString format(...);
#include <memory>

namespace vda
{
    constexpr size_t _vdastring_max_len = 65535;
    constexpr size_t _vdastring_max_split = 1023;

    class VDAString
    {
        char *_str = nullptr; //
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
        bool operator==(const VDAString &rhs) const;
        bool operator!=(const VDAString &rhs) const;
        bool operator>(const VDAString &rhs) const;
        bool operator<(const VDAString &rhs) const;
        bool operator>=(const VDAString &rhs) const;
        bool operator<=(const VDAString &rhs) const;

        // conversion operators
        operator const char *() const; // c-string type

        // Utility methods
        bool have_value() const;
        // string format, allows the string to be used with printf
        VDAString &format(const char *format, ...);
        // & foo() means function will return by reference.VDAString & format(const char *format, ...);
        //  This can be used to e.g.create a pointer to a function.
        // trim leading and trailing process, removes leading and trailling spaces
        VDAString &trim();
        // lower()
        VDAString lower();
        // upper(), takes the obj, iterate _str, uses toupper() and tolower
        VDAString upper();
        // back returns the last char of the string
        const char &back();
        // front
        const char &front();
        // length() = size(), both names are available in std library
        const size_t length() { return _str_len; }
        // size()
        const size_t size() { return _str_len; }
    };
}

#endif // __VDASTRING__H__
