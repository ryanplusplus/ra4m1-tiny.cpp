/*!
 * @file
 * @brief
 */

#ifndef HeartbeatTemplate_hpp
#define HeartbeatTemplate_hpp

#include <limits>
#include "Device.hpp"
#include "tiny/Timer.hpp"

template <unsigned port, unsigned pin>
class HeartbeatTemplate {
 public:
 private:
  enum {
    pin_mask = 1 << pin,
    half_period_in_msec = 500,
  };

 public:
  HeartbeatTemplate(tiny::TimerGroup& timer_group)
  {
    switch(port) {
      case 0:
        R_PORT0->PCNTR1_b.PDR |= pin_mask;
        break;

      case 1:
        R_PORT1->PCNTR1_b.PDR |= pin_mask;
        break;

      case 2:
        R_PORT2->PCNTR1_b.PDR |= pin_mask;
        break;

      case 3:
        R_PORT3->PCNTR1_b.PDR |= pin_mask;
        break;

      case 4:
        R_PORT4->PCNTR1_b.PDR |= pin_mask;
        break;

      case 5:
        R_PORT5->PCNTR1_b.PDR |= pin_mask;
        break;

      case 6:
        R_PORT6->PCNTR1_b.PDR |= pin_mask;
        break;

      case 7:
        R_PORT7->PCNTR1_b.PDR |= pin_mask;
        break;

      case 8:
        R_PORT8->PCNTR1_b.PDR |= pin_mask;
        break;

      case 9:
        R_PORT9->PCNTR1_b.PDR |= pin_mask;
        break;
    }

    timer_group.start_periodic(
      this->timer, half_period_in_msec, +[](void*) {
        switch(port) {
          case 0:
            R_PORT0->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 1:
            R_PORT1->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 2:
            R_PORT2->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 3:
            R_PORT3->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 4:
            R_PORT4->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 5:
            R_PORT5->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 6:
            R_PORT6->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 7:
            R_PORT7->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 8:
            R_PORT8->PCNTR1_b.PODR ^= pin_mask;
            break;

          case 9:
            R_PORT9->PCNTR1_b.PODR ^= pin_mask;
            break;
        }
      });
  }

 private:
  tiny::Timer timer{};
};

#endif
