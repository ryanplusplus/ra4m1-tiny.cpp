/*!
 * @file
 * @brief
 */

#include <stdint.h>
#include "Device.hpp"

extern uint32_t _stack_start;
extern uint32_t _vectors_start;
extern uint32_t _dtc_vectors_start;
extern uint32_t _mappable_vectors_start;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;
extern uint32_t _sstack;
extern uint32_t _estack;

int main(void);
void start(void);

void __libc_init_array(void);

void Dummy_Handler(void)
{
  while(1) {
  }
}

void NMI_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Dummy_Handler")));

void (*vector_table[])(void) __attribute__((section(".vectors"), used)) = {
  (void (*)(void))(uintptr_t)(&_stack_start),
  start,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
};

void start(void)
{
  uint32_t *src, *dst;

  src = &_etext;
  dst = &_data;

  if(src != dst) {
    for(; dst < &_edata;) {
      *dst++ = *src++;
    }
  }

  for(dst = &_bss; dst < &_ebss;) {
    *dst++ = 0;
  }

  src = (uint32_t*)&_vectors_start;
  SCB->VTOR = ((uint32_t)src & SCB_VTOR_TBLOFF_Msk);

  main();
}
