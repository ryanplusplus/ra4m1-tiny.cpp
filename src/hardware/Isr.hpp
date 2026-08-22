/*!
 * @file
 * @brief
 */

#ifndef Isr_hpp
#define Isr_hpp

typedef void (*_VectorTableVector)(void);

extern _VectorTableVector _mappable_vectors_start;

#define Isr(_name, _event)                                                                                                                             \
  static void _name##Implementation(void);                                                                                                             \
  static const _VectorTableVector _name##IsrPlacement __attribute__((section(".mappable_vectors"))) __attribute__((__used__)) = _name##Implementation; \
                                                                                                                                                       \
  namespace _name {                                                                                                                                    \
    constexpr auto vector_number = []() { return (IRQn_Type)(&_name##IsrPlacement - &_mappable_vectors_start); };                                      \
    auto set_priority = [](uint32_t priority) { NVIC_SetPriority(vector_number(), priority); };                                                        \
    auto enable = []() { NVIC_EnableIRQ(vector_number()); };                                                                                           \
    auto disable = []() { NVIC_DisableIRQ(vector_number()); };                                                                                         \
    auto clear_interrupt_flag = []() { R_ICU->IELSR_b[vector_number()].IR = 0; };                                                                      \
    auto _register = []() { R_ICU->IELSR[_name::vector_number()] = _event; };                                                                          \
  }                                                                                                                                                    \
                                                                                                                                                       \
  static class _name##IsrRegistrar {                                                                                                                   \
   public:                                                                                                                                             \
    _name##IsrRegistrar()                                                                                                                              \
    {                                                                                                                                                  \
      _name::_register();                                                                                                                              \
    }                                                                                                                                                  \
  } _name##IsrRegistrarInstance;                                                                                                                       \
                                                                                                                                                       \
  static void _name##Implementation(void)

#endif
