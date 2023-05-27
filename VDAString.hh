#ifndef __VDASTRING__H__
#define __VDASTRING__H__
#include <cstdio>
#include <memory>

namespace vda
{
    class VDAString
    {
        char const *_str = nullptr; // char const makes this pointer immutable.
        size_t _str_len = 0;

    public:
        VDAString();
        VDAString(const char *s);        // Parameterized constructor, will not change the content pf the value.
        VDAString(const VDAString &old); // Copy Consttructor
        ~VDAString();
        void setString(const char *s);
        const char *getString() const;
        void reset();
    };
}

#endif // __VDASTRING__H__
