/*!
 * @file
 * @brief
 */

#ifndef Board_hpp
#define Board_hpp

#include "Clock.hpp"
#include "HeartbeatTemplate.hpp"
#include "Interrupts.hpp"
#include "SystemTick.hpp"
#include "Watchdog.hpp"

using Heartbeat = HeartbeatTemplate<0, 11>;
// using I2c = Sercom2Pa08Pa09I2c;
// using AsyncSpi = Sercom0Pa05Pa06Pa07AsyncSpi;
// using Spi = Sercom0Pa05Pa06Pa07Spi;
// using BufferedUart = Sercom4Pb08Pb09BufferedUart;
// using Uart = Sercom4Pb08Pb09Uart;
// using NeopixelBff = Neopixel::Neopixel<Neopixel::ByteOrder::grb, Clock::gclk0_frequency, PIN_PA11>;

#endif
