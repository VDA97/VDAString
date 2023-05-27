#include "VDAString.hh"

namespace vda
{
    VDAString::VDAString()
    {
        printf("constructor");
        s = " ";
    }
    VDAString::~VDAString()
    {
        printf("Destructor");
    }
    void VDAString::setString(char const *str)
    {
        s = str;
    }
    char const *VDAString::getString()
    {

        return s;
    }
}
