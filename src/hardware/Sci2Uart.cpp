/*!
 * @file
 * @brief
 */

#include "Device.hpp"
#include "Isr.hpp"
#include "Pfs.hpp"
#include "Sci2Uart.hpp"
#include "tiny/SingleSubscriberEvent.hpp"

typedef void (*VectorTableVector)(void);

extern VectorTableVector _mappable_vectors_start;

#define VectorTable_DefineIsr(_isr) \
  void _isr(void);                  \
  static const VectorTableVector _isr##IsrPlacement __attribute__((section(".mappable_vectors"))) __attribute__((__used__)) = _isr

#define VectorTable_DefineStaticIsr(_isr) \
  static void _isr(void);                 \
  static const VectorTableVector _isr##IsrPlacement __attribute__((section(".mappable_vectors"))) __attribute__((__used__)) = _isr

#define VectorTable_VectorNumber(_isr) \
  (IRQn_Type)(&_isr##IsrPlacement - &_mappable_vectors_start)

#define VectorTable_RegisterIsr(_isr, _event)              \
  do {                                                     \
    R_ICU->IELSR[VectorTable_VectorNumber(_isr)] = _event; \
  } while(0)

static class Sci2UartImplementation : public tiny::IUart {
 public:
  Sci2UartImplementation() : send_complete(), receive()
  {
  }

  void init();

  void send(uint8_t byte) override
  {
    R_SCI2->TDR = byte;
  }

  tiny::IEvent<>& on_send_complete() override
  {
    return send_complete;
  }

  tiny::IEvent<uint8_t>& on_receive() override
  {
    return receive;
  }

 public:
  tiny::SingleSubscriberEvent<> send_complete;
  tiny::SingleSubscriberEvent<uint8_t> receive;
} instance;

tiny::IUart& Sci2Uart::get_instance()
{
  instance.init();
  return instance;
}

Isr(TransmitDataEmptyIsr, ELC_EVENT_SCI2_TXI)
{
  TransmitDataEmptyIsr::clear_interrupt_flag();
  instance.send_complete.publish();
}

Isr(ReceiveDataFullIsr, ELC_EVENT_SCI2_RXI)
{
  ReceiveDataFullIsr::clear_interrupt_flag();
  instance.receive.publish(R_SCI2->RDR);
}

Isr(ReceiveErrorIsr, ELC_EVENT_SCI2_ERI)
{
  ReceiveErrorIsr::clear_interrupt_flag();

  while(R_SCI2->SSR_b.PER) {
    R_SCI2->SSR_b.PER = 0;
  }

  while(R_SCI2->SSR_b.ORER) {
    R_SCI2->SSR_b.ORER = 0;
  }

  while(R_SCI2->SSR_b.FER) {
    R_SCI2->SSR_b.FER = 0;
  }

  volatile uint8_t dummy = R_SCI2->RDR;
  (void)dummy;
}

void Sci2UartImplementation::init()
{
  // Enable SCI2
  R_MSTP->MSTPCRB_b.MSTPB29 = 0;

  // [1] Set the FCR.FM bit to 0
  {
    // > Disable the FIFO
    R_SCI2->FCR_b.FM = 0;
  }

  // [2] Set the clock selection in SCR
  {
    // Use internal baud rate generator
    R_SCI2->SCR_b.CKE = 1;
  }

  // [3] Set the SIMR1.IICM bit to 0
  // Set the SPMR.CKPH and CKPOL bits to 0
  // Step [3] can be skipped if the values have not changed from the initial values
  {
    // Skipped
  }

  // [4] Set data transmission/reception format in SMR, SCMR, and SEMR
  {
    // PCLKA/1
    R_SCI2->SMR_b.CKS = 0;

    // 8N1 is the default, no need to further touch SMR

    // Noise filter disabled
    R_SCI2->SEMR_b.NFEN = 0;

    // Clock cycle for 1-bit period is determined with combination of BGDM and ABCS bits
    R_SCI2->SEMR_b.ABCSE = 0;

    // 16 base clock cycles for 1-bit period
    R_SCI2->SEMR_b.ABCS = 0;

    // Baud rate generator outputs the clock with double frequency
    R_SCI2->SEMR_b.BGDM = 1;

    // Bit Rate Modulation (via MDDR) enabled
    R_SCI2->SEMR_b.BRME = 1;
  }

  // [5] Write a value associated with the bit rate to BRR
  // [6] Write the value obtained by correcting a bit rate error in MDDR
  {
    // 230.4k with 0.124% error
    R_SCI2->BRR = 10;
    R_SCI2->MDDR = 216;
  }

  // [7] Specify the I/O port settings to enable input and output functions
  // as required for the TXDn, RXDn, and SCKn pins
  {
    Pfs::modify(+[]() {
      // Assign P3.01 to RX
      R_PFS->PORT[3].PIN[1].PmnPFS_b.PMR = 1;
      R_PFS->PORT[3].PIN[1].PmnPFS_b.PSEL = 4;

      // Assign P3.02 to TX
      R_PFS->PORT[3].PIN[2].PmnPFS_b.PMR = 1;
      R_PFS->PORT[3].PIN[2].PmnPFS_b.PSEL = 4;
    });
  }

  // [8] Set the SCR.TE or RE bit to 1
  // Also set the SCR.TIE and RIE bits
  {
    // Enable receive and transmit
    R_SCI2->SCR_b.RE = 1;
    R_SCI2->SCR_b.TE = 1;

    ReceiveDataFullIsr::enable();
    TransmitDataEmptyIsr::enable();
    ReceiveErrorIsr::enable();

    ReceiveDataFullIsr::set_priority(12);
    TransmitDataEmptyIsr::set_priority(12);
    ReceiveErrorIsr::set_priority(12);

    R_SCI2->SCR_b.RIE = 1;
    R_SCI2->SCR_b.TIE = 1;
  }
}
