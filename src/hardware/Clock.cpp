/*!
 * @file
 * @brief
 */

#include "Clock.hpp"
#include "Device.hpp"
#include "Prcr.hpp"

void Clock::init()
{
  // Switch to HOCO
  Prcr::unprotect(+[]() {
    // Disable flash cache
    R_FCACHE->FCACHEE = 0;
    {
      // Select high-speed mode (defaults to low-voltage mode)
      R_SYSTEM->OPCCR = 0;
      while(R_SYSTEM->OPCCR_b.OPCMTSF != 0) {
      }

      // Start the HOCO
      R_SYSTEM->HOCOCR = 0;
      while(R_SYSTEM->OSCSF_b.HOCOSF != 1) {
      }

      // Enable wait states since ICLK is going to be set higher than 32 MHz
      R_SYSTEM->MEMWAIT = 1;

      // Set dividers
      R_SYSTEM->SCKDIVCR =
        (0 << 0) | // PCKD = 1/1 => 48 MHz
        (0 << 4) | // PCKC = 1/1 => 48 MHz
        (1 << 8) | (1 << 16) | // PCKB = 1/2 => 24 MHz
        (0 << 12) | // PCKA = 1/1 => 48 MHz
        (0 << 24) | // ICK = 1/1 => 48 MHz
        (1 << 28); // FCK = 1/2 => 24 MHz

      // Select the HOCO as the system clock source
      R_SYSTEM->SCKSCR = 0;
    }
    // Enable flash cache
    R_FCACHE->FCACHEE = 1;
  });

  // Reset TRNG to minimize power usage
  Prcr::unprotect(+[]() {
    // Start SCE to start TRNG
    R_MSTP->MSTPCRC_b.MSTPC31 = 0;

    // Wait at least 3 PCLKB cycles
    volatile uint8_t dummy;
    dummy = R_PFS->PORT[0].PIN[0].PmnPFS_b.PODR;
    dummy = R_PFS->PORT[0].PIN[0].PmnPFS_b.PODR;
    dummy = R_PFS->PORT[0].PIN[0].PmnPFS_b.PODR;
    (void)dummy;

    // Stop SCE
    R_MSTP->MSTPCRC_b.MSTPC31 = 1;
  });
}
