/**
 * @file string.hpp
 * @brief Static capacity string implementation for embedded systems.
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

/**
 * @brief A fixed-capacity string that does not use dynamic memory allocation.
 * @tparam Capacity Maximum number of characters (excluding null terminator).
 */
template <vsl::len Capacity>
class string {
    static_assert(Capacity < platform::strlen_max, "<Vertex 5>: Too much string capacity for this microcontroller.");

private:
    char     _buffer[Capacity + 1]; // Internal buffer with space for null terminator
    vsl::len _size;                 // Current number of characters

    /**
     * @brief Calculates how many characters can be safely copied.
     */
    static constexpr vsl::len max_copy(const char* s) {
        vsl::len n = 0;
        while (s[n] && n < Capacity) {
            ++n;
        }
        return n;
    }

public:
    /* ================== constructors ================== */

    /**
     * @brief Default constructor. Creates an empty string.
     */
    constexpr string() noexcept
        : _buffer{0}, _size(0)
    {}

    /**
     * @brief Construct from a C-style string.
     * @param cstr Source null-terminated string.
     */
    string(const char* cstr) noexcept
        : _buffer{0}, _size(0)
    {
        if (!cstr) return;

        _size = max_copy(cstr);
        memcpy(_buffer, cstr, _size);
        _buffer[_size] = '\0';
    }

    /* ================== basic access ================== */

    /**
     * @brief Returns a pointer to the underlying null-terminated C-string.
     */
    const char* c_str() const noexcept {
        return _buffer;
    }

    /**
     * @brief Returns a pointer to the raw data buffer.
     */
    char* data() noexcept {
        return _buffer;
    }

    /**
     * @brief Returns the current number of characters.
     */
    vsl::len size() const noexcept {
        return _size;
    }

    /**
     * @brief Returns the maximum possible size of the string.
     */
    static constexpr vsl::len capacity() noexcept {
        return Capacity;
    }

    /**
     * @brief Checks if the string is empty.
     */
    bool empty() const noexcept {
        return _size == 0;
    }

    /* ================== modification ================== */

    /**
     * @brief Clears the string content.
     */
    void clear() noexcept {
        _size = 0;
        _buffer[0] = '\0';
    }

    /**
     * @brief Replaces current content with a C-style string.
     * @return true if successful.
     */
    bool assign(const char* cstr) noexcept {
        if (!cstr) return false;

        _size = max_copy(cstr);
        memcpy(_buffer, cstr, _size);
        _buffer[_size] = '\0';
        return true;
    }

    /**
     * @brief Appends a single character to the end.
     * @return false if the capacity is exceeded.
     */
    bool push_back(char c) noexcept {
        if (_size >= Capacity) {
            return false;
        }

        _buffer[_size++] = c;
        _buffer[_size] = '\0';
        return true;
    }

    /* ================== numeric conversion ================== */

    /**
     * @brief Converts an integer to string representation.
     * @return false if result doesn't fit in Capacity.
     */
    bool from_int(int value) noexcept {
        clear();
        
        char tmp[12]; // Buffer for int32 (including sign)
        bool negative = false;

        // Note: Handle INT_MIN carefully in production if needed
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

        // Reverse characters from tmp to _buffer
        for (int j = 0; j < i; ++j) {
            _buffer[j] = tmp[i - j - 1];
        }

        _size = i;
        _buffer[_size] = '\0';
        return true;
    }

    /* ================== operators ================== */

    /**
     * @brief Safe character access. Returns null-terminator if out of bounds.
     */
    char at(vsl::len index) const noexcept {
        return (index < _size) ? _buffer[index] : '\0';
    }

    /**
     * @brief Unsafe character access (no bounds check).
     */
    char operator[](vsl::len index) const noexcept {
        return _buffer[index];
    }

    /**
     * @brief Equality comparison with a C-style string.
     */
    bool operator==(const char* cstr) const noexcept {
        if (!cstr) return false;
        return strcmp(_buffer, cstr) == 0;
    }
};

} // namespace vsl

#endif // VERTEX_5_VSL_STRING_H_