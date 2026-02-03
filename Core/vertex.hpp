
/**
 * @file vertex.hpp
 * @brief Main Vertex framework header file.
 * @version 5.0.1
 * @date 03.02.26
 * @author Matvey Rybalkin
 */

#ifndef VERTEX_5_HPP_
#define VERTEX_5_HPP_

#if !defined(__cplusplus) || (__cplusplus < 201402L)
#   error "<Vertex 5>: Requires at least the 2014 C++ language standard."
#else

#define VERTEX_VERSION_MAJOR 5
#define VERTEX_VERSION_MINOR 0
#define VERTEX_VERSION_PATCH 1

#define VERTEX_VERSION_ID ((VERTEX_VERSION_MAJOR * 10000) + \
                           (VERTEX_VERSION_MINOR * 100) + \
                            VERTEX_VERSION_PATCH)


// General
#include "types.hpp"

// VSL
#include "../VSL/string.hpp"

#endif // !defined(__cplusplus) || (__cplusplus < 201402L)
#endif // VERTEX_5_HPP_
