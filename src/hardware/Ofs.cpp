/*!
 * @file
 * @brief
 */

#include <cstdint>

#define OFS0                                                                        \
  0 | /* (IWDT clock is 15 KHz, 2048 period, 1/32 divider => ~4.37 seconds) */      \
    (1U << 0) | /* Fixed */                                                         \
    (0U << 1) | /* IWDT enabled after reset */                                      \
    (3U << 2) | /* IWDT timeout period 2048 cycles */                               \
    (3U << 4) | /* IWDT clock divider is 1/32 */                                    \
    (3U << 8) | /* IWDT no window end position setting */                           \
    (3U << 10) | /* IWDT no window start position setting */                        \
    (1U << 12) | /* IWDT reset when timeout occurs */                               \
    (1U << 13) | /* Fixed */                                                        \
    (0U << 14) | /* IWDT count during sleep, snooze, and software statndby modes */ \
    (1U << 15) | /* Fixed */                                                        \
    (1U << 16) | /* Fixed */                                                        \
    (1U << 17) | /* WDT disabled after reset */                                     \
    (0U << 18) | /* WDT timeout period 1024 cycles */                               \
    (1U << 20) | /* WDT clock divider is 1/4 */                                     \
    (3U << 24) | /* WDT no window end position setting */                           \
    (3U << 26) | /* WDT no window start position setting */                         \
    (1U << 28) | /* WDT reset when timeout occurs */                                \
    (1U << 29) | /* Fixed */                                                        \
    (0U << 30) | /* WDT count during sleep mode */                                  \
    (1U << 31) /* Fixed */

#define OFS1                                                \
  0 |                                                       \
    (0x3U << 0) | /* Fixed */                               \
    (0U << 2) | /* Voltage monitor 0 enabled after reset */ \
    (1U << 3) | /* Voltage detection 0 threshold 2.82 V */  \
    (0x3U << 6) | /* Fixed */                               \
    (0U << 8) | /* Enable HOCO after reset */               \
    (0x7U << 9) | /* Fixed */                               \
    (4U << 12) | /* HOCO frequency 48 MHz */                \
    (0x1FFFFU << 15) /* Fixed */

static const uint32_t ofs[] __attribute__((section(".ofs"))) __attribute__((__used__)) = {
  OFS0,
  OFS1,
};
