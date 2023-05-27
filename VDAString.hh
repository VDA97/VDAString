#ifndef __VDASTRING__H__
#define __VDASTRING__H__
#include <cstdio>
#include <memory>

namespace vda
{
    class VDAString
    {
        char const *s;

    public:
        VDAString();
        ~VDAString();
        void setString(char const *s);
        char const *getString();
    };
}

#endif // __VDASTRING__H__
