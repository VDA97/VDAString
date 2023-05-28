#ifndef __VDASTRING__H__
#define __VDASTRING__H__
#include <cstdio>
#include <cstring> //for strlen().
#include <memory>

namespace vda
{

    class VDAString
    {
        char const *_str = nullptr; // char const makes this pointer immutable.
        size_t _str_len = 0;
        static constexpr size_t _vdastring_max_len = 1024;

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

        // conversion operators
        operator const char *() const; // c-string type
    };
}

#endif // __VDASTRING__H__
