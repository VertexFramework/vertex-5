/**
 * @file platform.hpp
 * @brief 
 * @version 5.0.1
 * @date 03.02.26
 * @author Matvey Rybalkin
 */

#ifndef VERTEX_5_PLATFORM_SELECTOR_H_
#define VERTEX_5_PLATFORM_SELECTOR_H_

#if (!defined(VERTEX_VERSION_MAJOR)) || (VERTEX_VERSION_MAJOR < 5)
#   error "<Vertex 5>: types.hpp couldn't be used without vertex.hpp version >= 5."
#endif

#include <stdlib.h>

namespace platform {

#       if defined(__AVR__)
#   include "AVR/avr_driver.hpp"
#     elif defined(__arm__) || defined(__thumb__)
#   include "STM32/"
#else // ...
#   error "<Vertex 5>: This CPU isn't supported. Try setting macro identifier. (__AVR__, etc.)"
#endif

}

#endif //  VERTEX_5_PLATFORM_SELECTOR_H_
