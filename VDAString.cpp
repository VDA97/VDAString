#include "VDAString.hh"

namespace vda
{
    VDAString::VDAString()
    {
        printf("Constructor\n");
        reset();
    }
    VDAString::VDAString(const char *s)
    {
        // copy_str(s);
    }
    VDAString::VDAString(const VDAString &old)
    {
        // copy_str(old);
    }
    VDAString::~VDAString()
    {
        printf("Destructor\n");
    }
    void VDAString::setString(const char *str)
    {
        _str = str;
    }
    const char *VDAString::getString() const
    {
        return _str;
    }

    void VDAString::reset()
    {
        //  _reset_split_array(); //
        if (_str)
        {
            delete[] _str;
            _str = nullptr;
            _str_len = 0;
        }
    }
}
