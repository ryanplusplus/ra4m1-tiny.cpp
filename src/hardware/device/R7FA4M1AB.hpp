/*!
 * @file
 * @brief
 */

#ifndef R7FA4M1AB_hpp
#define R7FA4M1AB_hpp

typedef enum IRQn {
  Reset_IRQn = -15, /*  1 Reset Vector invoked on Power up and warm reset */
  NonMaskableInt_IRQn = -14, /*  2 Non maskable Interrupt cannot be stopped or preempted */
  HardFault_IRQn = -13, /*  3 Hard Fault all classes of Fault */
  MemoryManagement_IRQn = -12, /*  4 Memory Management MPU mismatch, including Access Violation and No Match */
  BusFault_IRQn = -11, /*  5 Bus Fault Pre-Fetch-, Memory Access, other address/memory Fault */
  UsageFault_IRQn = -10, /*  6 Usage Fault i.e. Undef Instruction, Illegal State Transition */
  SecureFault_IRQn = -9, /*  7 Secure Fault Interrupt */
  SVCall_IRQn = -5, /* 11 System Service Call via SVC instruction */
  DebugMonitor_IRQn = -4, /* 12 Debug Monitor */
  PendSV_IRQn = -2, /* 14 Pendable request for system service */
  SysTick_IRQn = -1, /* 15 System Tick Timer */
} IRQn_Type;

#include "R7FA4M1AB.h"
#include "bsp_elc.h"

#endif
