/*!
 * @file
 * @brief
 */

#ifndef Clock_hpp
#define Clock_hpp

class Clock {
 public:
  enum {
    ick_frequency = 48 * 1000000,
    fck_frequency = 24 * 1000000,
    pcka_frequency = 48 * 1000000,
    pckb_frequency = 24 * 1000000,
    pckc_frequency = 48 * 1000000,
    pckd_frequency = 48 * 1000000,
  };

 public:
  static void init();
};

#endif
