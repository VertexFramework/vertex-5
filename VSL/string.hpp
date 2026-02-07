
/**
 * @file string.hpp
 * @brief 
 * @version 5.0.1
 * @date 03.02.26
 * @author Matvey Rybalkin
 */

#ifndef VERTEX_5_VSL_STRING_H_
#define VERTEX_5_VSL_STRING_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <platform.hpp>

#include "basic_types.hpp"

namespace vsl {

template <vsl::len Capacity>
class string {
    static_assert(Capacity < platform::strlen_max, "<Vertex 5>: Too much string capacity for this microcontroller.");

private:
    char     _buffer[Capacity + 1]; // +1 for '\0'
    vsl::len _size;

    static constexpr vsl::len max_copy(const char* s) {
        vsl::len n = 0;
        while (s[n] && n < Capacity) {
            ++n;
        }
        return n;
    }

public:
    /* ================== constructors ================== */

    constexpr string() noexcept
        : _buffer{0}, _size(0)
    {}

    string(const char* cstr) noexcept
        : _buffer{0}, _size(0)
    {
        if (!cstr) return;

        _size = max_copy(cstr);
        memcpy(_buffer, cstr, _size);
        _buffer[_size] = '\0';
    }

    /* ================== basic access ================== */

    const char* c_str() const noexcept {
        return _buffer;
    }

    char* data() noexcept {
        return _buffer;
    }

    vsl::len size() const noexcept {
        return _size;
    }

    static constexpr vsl::len capacity() noexcept {
        return Capacity;
    }

    bool empty() const noexcept {
        return _size == 0;
    }

    // modification

    void clear() noexcept {
        _size = 0;
        _buffer[0] = '\0';
    }

    bool assign(const char* cstr) noexcept {
        if (!cstr) return false;

        _size = max_copy(cstr);
        memcpy(_buffer, cstr, _size);
        _buffer[_size] = '\0';
        return true;
    }

    bool push_back(char c) noexcept {
        if (_size >= Capacity) {
            return false;
        }

        _buffer[_size++] = c;
        _buffer[_size] = '\0';
        return true;
    }

    // numeric conversion

    bool from_int(int value) noexcept {
        clear();
        
        char tmp[12]; // enough for int32
        bool negative = false;

        if (value < 0) {
            negative = true;
            value = -value;
        }

        int i = 0;
        do {
            tmp[i++] = char('0' + (value % 10));
            value /= 10;
        } while (value && i < int(sizeof(tmp)));

        if (negative) {
            tmp[i++] = '-';
        }

        if (i > int(Capacity)) {
            return false;
        }

        // reverse
        for (int j = 0; j < i; ++j) {
            _buffer[j] = tmp[i - j - 1];
        }

        _size = i;
        _buffer[_size] = '\0';
        return true;
    }

    /* ================== operators ================== */

    char at(vsl::len index) const noexcept {
        return (index < _size) ? _buffer[index] : '\0';
    }

    char operator[](vsl::len index) const noexcept {
        return _buffer[index];
    }

    bool operator==(const char* cstr) const noexcept {
        if (!cstr) return false;
        return strcmp(_buffer, cstr) == 0;
    }
};

}


#endif // VERTEX_5_VSL_STRING_H_