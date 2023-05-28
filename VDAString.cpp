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
        copy_str(old);
        //  @todo check further
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

    // MARK: - private methods
    //  Data management
    void VDAString::_reset_split_array() const
    {
        // Iterate the array and reset each element
        if (_split_count)
        {
            while (_split_count)
            {
                _split_array[--_split_count].reset();
            }
            _split_array.reset();
            _split_count = 0;
        }
    }
    void VDAString::_append_split_array(const VDAString &s) const
    {
        // check if there is enough space
        if (_split_count >= _vdastring_max_split)
            return;
        // check if _split_count is null, then allocates all of the shared_ptr for all the possible elements of the array
        if (!_split_count)
        {
            _split_array.reset(new _vdasp[_vdastring_max_split + 1]);
            // this makes memory management easier
        }
        // add a new object in the array using _split_count as index
        _split_array[_split_count] = std::make_shared<VDAString>(s);
        // update _split_count
        ++_split_count;
    }

    // MARK: -operators
    // copy-and-swap assignment
    VDAString &VDAString::operator=(VDAString other)
    {
        swap(other);
        return *this;
    }
    // concatenation operator
    VDAString &VDAString::operator+=(const char *rhs)
    {
        if (rhs)
        {
            // defines a newlen
            size_t newlen = _str_len + strnlen(rhs, _vdastring_max_len);
            // check if is the combine length ot higher than the max
            if (newlen > _vdastring_max_len)
            {
                newlen = _vdastring_max_len; // resize to maxlen
            }
            // define the length of the new combined string
            // in case, _str_len is higher, means nothing was added, instead it was corrupted.
            size_t rhslen = newlen - _str_len;
            if (rhslen < 1)
                return *this;
            // creates a buffer with the new space
            char *buf = new char[newlen + 1]();
            // copy the previous values in the new buffer
            if (_str && _str_len)
            {
                memcpy(buf, _str, _str_len);
            }
            // copy the new values in the new buffer
            memcpy(buf, rhs, rhslen); // why +_str_len ?
            copy_str(buf);            // copies the buff to _str, I mean, here, this could cause some duplicate ?
            // I mean, I do not remember if we were reseting something
            delete[] buf;
        }

        return *this;
    }
    VDAString &VDAString::operator+=(const VDAString &rhs)
    {
        operator+=(rhs.c_str()); // calls the c-string versionn
        return *this;
    }
    const char VDAString::operator[](const int index) const
    {
        if (index < 0)
            return 0;
        if (index >= (int)_str_len)
            return 0;
        else
            return _str[index]; // returns a character of the _str.
    }

    // MARK: - comparison operators
    // run  std::strncmp and then compare the result to 0
    // strncmp compares count of each array characters
    bool VDAString::operator==(const VDAString &rhs) const
    {
        if (std::strncmp(this->c_str(), rhs.c_str(), _vdastring_max_len) == 0)
        {
            return true;
        }
        else
            return false;
    }

    bool VDAString::operator!=(const VDAString &rhs) const
    {
        if (std::strncmp(this->c_str(), rhs.c_str(), _vdastring_max_len) != 0)
        {
            return true;
        }
        else
            return false;
    }

    bool VDAString::operator>(const VDAString &rhs) const
    {
        if (std::strncmp(this->c_str(), rhs.c_str(), _vdastring_max_len) > 0)
        {
            return true;
        }
        else
            return false;
    }

    bool VDAString::operator<(const VDAString &rhs) const
    {
        if (std::strncmp(this->c_str(), rhs.c_str(), _vdastring_max_len) < 0)
        {
            return true;
        }
        else
            return false;
    }
    bool VDAString::operator>=(const VDAString &rhs) const
    {
        if (std::strncmp(this->c_str(), rhs.c_str(), _vdastring_max_len) >= 0)
        {
            return true;
        }
        else
            return false;
    }

    bool VDAString::operator<=(const VDAString &rhs) const
    {
        if (std::strncmp(this->c_str(), rhs.c_str(), _vdastring_max_len) <= 0)
        {
            return true;
        }
        else
            return false;
    }

    // conversion operator
    VDAString::operator const char *() const
    {
        return c_str();
    }

    // MARK: - non member operator oveloads
    // This allows strings of concatenations mixed with c strings
    VDAString operator+(const VDAString &lhs, const VDAString rhs)
    {
        VDAString rs = lhs;
        rs += rhs;
        return rs;
    }
}
