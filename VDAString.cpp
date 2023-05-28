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
        copy_str(s);
    }
    VDAString::VDAString(const VDAString &old)
    {
        // copy_str(old); @todo check further
    }
    VDAString::VDAString(VDAString &&other) noexcept
    {
        //@todo
        reset();
        _str = other._str; //= uses the assignment operator.
        _str_len = other._str_len;
        other._str = nullptr;
        other._str_len = 0;
        other.reset();
        // reset need to be call after _str = nullptr.
        // if we call reset() first, we'll have a ptr to something that doesn't exist
    }
    VDAString::~VDAString()
    {
        printf("Destructor\n");
    }

    const char *VDAString::alloc_str(size_t sz)
    {
        // allocate space for our string
        // if we have a _str value, reset it.
        if (_str)
            reset();
        // check if the space is not higher than the max
        _str_len = sz > _vdastring_max_len ? _vdastring_max_len : sz;
        // allocate memory for _str
        _str = new char[_str_len + 1](); // new char[](); fills with 0.
        // note that plus one will add the null terminator pointer.
        return _str;
    }
    void VDAString::reset()
    {
        //  _reset_split_array(); //
        if (_str) // if _str is not null
        {
            delete[] _str;  // clean _str, the data itsel is a c-string, its space is allocated with new
            _str = nullptr; // sets it to null
            _str_len = 0;   // set length to zero
        }
    }

    void VDAString::swap(VDAString &other)
    {
        std::swap(_str, other._str);
        std::swap(_str_len, other._str_len);
    }

    const char *VDAString::c_str() const
    {
        return _str;
    }
    const char *VDAString::copy_str(const char *s)
    {
        // Because of the conversion operator
        // check the conversion operator: operator const char * const();
        // copy_str can work either a VDAString object or a c-string.
        if (s) // if s is not null
        {
            // get the length of the string
            size_t len = strnlen(s, _vdastring_max_len);
            alloc_str(len);
            strncpy((char *)_str, s, len); // note that we need to cast, as required by function
            _str_len = len;                // update the len.
        }
        return _str;
    }
}
