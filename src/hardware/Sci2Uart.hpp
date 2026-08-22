/*!
 * @file
 * @brief
 */

#ifndef Sci2Uart_hpp
#define Sci2Uart_hpp

#include "tiny/hal/IUart.hpp"

class Sci2Uart : tiny::IUart {
 public:
  static tiny::IUart& get_instance();
};

#endif
