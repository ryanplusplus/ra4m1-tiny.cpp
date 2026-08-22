/*!
 * @file
 * @brief
 */

#ifndef RegisterProtection_hpp
#define RegisterProtection_hpp

#include "Device.hpp"

class RegisterProtection {
 public:
  static void enable()
  {
    R_SYSTEM->PRCR = 0xA500;
  }

  static void disable()
  {
    R_SYSTEM->PRCR = 0xA50B;
  }

  static uint16_t save()
  {
    uint16_t prcr = R_SYSTEM->PRCR;
    disable();
    return prcr;
  }

  static void restore(uint16_t prcr)
  {
    R_SYSTEM->PRCR = prcr;
  }

  template <typename t>
  static void unprotect(t body)
  {
    auto state = RegisterProtection::save();
    body();
    RegisterProtection::restore(state);
  }
};

#endif
