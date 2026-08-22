/*!
 * @file
 * @brief
 */

#include "Clock.hpp"
#include "Device.hpp"
#include "Watchdog.hpp"

using namespace tiny;

Watchdog::Watchdog(tiny::TimerGroup& timer_group)
{
  // The watchdog is enabled by default and configured in OFS

  timer_group.start_periodic(
    this->timer, period, +[](void*) {
      R_IWDT->IWDTRR = 0x00;
      R_IWDT->IWDTRR = 0xFF;
    });
}
