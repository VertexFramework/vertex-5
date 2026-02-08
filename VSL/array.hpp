/**
 * @file array.hpp
 * @brief Static capacity array container.
 * @version 5.0.1
 * @date 03.02.26
 * @author Matvey Rybalkin
 */

#ifndef VERTEX_5_VSL_ARRAY_H_
#define VERTEX_5_VSL_ARRAY_H_

#include <stdbool.h>
#include <string.h>

#include "basic_types.hpp"

namespace vsl {
    
/**
 * @brief Fixed-size array wrapper.
 * @tparam Capacity Maximum number of elements.
 * @tparam T Element type.
 */
template <vsl::len Capacity, typename T>
class array {
private:
    len _size;             // Current number of elements used
    T _buffer[Capacity];   // Static storage

public:

    /**
     * @brief Default constructor.
     * @param clear If true, initializes buffer (currently only used for member init list).
     */
    constexpr array(bool clear=false) noexcept 
        : _buffer{0}, _size(0) {
        // Note: 'clear' parameter is not explicitly used for logic here
    }

    /**
     * @brief Returns current number of elements.
     */
    vsl::len size(void) const noexcept {
        return _size;
    }

    /**
     * @brief Returns the maximum capacity.
     */
    static constexpr vsl::len capacity(void) noexcept {
        return Capacity;
    }

    /**
     * @brief Returns raw pointer to the underlying data.
     */
    constexpr T* data(void) noexcept {
        return _buffer;
    }

    /**
     * @brief Returns true if the array contains no elements.
     */
    bool empty(void) const noexcept {
        return _size == 0;
    }

    /**
     * @brief Element access with debug bounds checking.
     */
    T& at(vsl::len index) const noexcept {
#if defined(VSL_DEBUG)
    if (index >= _size)
        __builtin_trap(); // Halt execution on out-of-bounds in debug
#endif
        return _buffer[index]; 
    }

    /**
     * @brief Returns element at index or default_value if out of bounds.
     */
    T at_or(vsl::len index, T default_value) const noexcept {
        return (index < _size) ? _buffer[index] : default_value;
    }

    /**
     * @brief Unsafe element access.
     */
    T& operator[](vsl::len index) const noexcept {
        return _buffer[index];
    }

    /**
     * @brief Copies data from a raw pointer into the array.
     * @return false if the data is too large for the capacity.
     */
    bool assign(const T* data, len size) {
        if (size > Capacity)
            return false;

        memcpy(_buffer, data, sizeof(T) * size);
        _size = size;
        return true;
    }

    /**
     * @brief Copy assignment operator.
     */
    array& operator=(const array& other) noexcept {
        _size = other._size;
        memcpy(_buffer, other._buffer, sizeof(T) * _size);
        return *this;
    }

    /* ================== Iterators ================== */

    /**
     * @brief Returns a pointer to the first element.
     */
    constexpr T* begin() noexcept {
        return &_buffer[0];
    }

    /**
     * @brief Returns a pointer to the element following the last element.
     */
    constexpr T* end() noexcept {
        return &_buffer[_size];
    }

    /**
     * @brief Const-version of begin().
     */
    constexpr const T* begin() const noexcept {
        return &_buffer[0];
    }

    /**
     * @brief Const-version of end().
     */
    constexpr const T* end() const noexcept {
        return &_buffer[_size];
    }

    /* ================== Comparison ================== */

    /**
     * @brief Compares two arrays of the same type and capacity.
     */
    bool operator==(const array& other) const noexcept {
        if (_size != other._size) return false;
        return memcmp(_buffer, other._buffer, sizeof(T) * _size) == 0;
    }

};

} // namespace vsl

#endif // VERTEX_5_VSL_ARRAY_H_
