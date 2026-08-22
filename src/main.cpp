/*!
 * @file
 * @brief
 */

#include "Board.hpp"
#include "tiny/Rtt.hpp"
#include "tiny/Timer.hpp"

using namespace tiny;

int main()
{
  Interrupts::disable();

  Clock::init();
  TimerGroup timer_group{ SystemTick::get_instance() };
  Watchdog watchdog{ timer_group };
  Heartbeat heartbeat{ timer_group };

  Interrupts::enable();

  Rtt::init();
  Rtt::printf("Hello, RTT!");

  auto& uart = Uart::get_instance();
  uart.send(0xE2);

  while(1) {
    if(timer_group.run()) {
      Interrupts::wait_for_interrupt();
    }
  }
}
