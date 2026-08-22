/*!
 * @file
 * @brief
 */

#ifndef Pfs_hpp
#define Pfs_hpp

#include "Device.hpp"

class Pfs {
 public:
  static void unlock()
  {
    R_PMISC->PWPR_b.B0WI = 0;
    R_PMISC->PWPR_b.PFSWE = 1;
  }

  static void lock()
  {
    R_PMISC->PWPR_b.PFSWE = 0;
    R_PMISC->PWPR_b.B0WI = 1;
  }

  template <typename t>
  static void modify(t body)
  {
    Pfs::unlock();
    body();
    Pfs::lock();
  }
};

#endif
