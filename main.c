/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2018.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include <stdio.h>
#include "interrupts.h"
#include "stm8s.h"
#include "gpio.h"
#include "uart.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//// Functions prototypes

// main -- start of firmware and main loop
int main (void);

// With SDCC, interrupt service routine function prototypes must be placed in the file that contains main ()
// in order for an vector for the interrupt to be placed in the the interrupt vector space.  It's acceptable
// to place the function prototype in a header file as long as the header file is included in the file that
// contains main ().  SDCC will not generate any warnings or errors if this is not done, but the vector will
// not be in place so the ISR will not be executed when the interrupt occurs.

// Calling a function from interrupt not always works, SDCC manual says to avoid it. Maybe the best is to put
// all the code inside the interrupt

// Local VS global variables
// Sometimes I got the following error when compiling the firmware: motor.asm:750: Error: <r> relocation error
// when I have this code inside a function: "static uint8_t ui8_cruise_counter = 0;"
// and the solution was define the variable as global instead
// Another error example:
// *** buffer overflow detected ***: sdcc terminated
// Caught signal 6: SIGABRT

// UART2 Receive interrupt
void UART2_IRQHandler(void) __interrupt(UART2_IRQHANDLER);

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

// This is the interrupt that happesn when UART2 receives data.
void UART2_IRQHandler(void) __interrupt(UART2_IRQHANDLER)
{
  if(UART2_GetFlagStatus(UART2_FLAG_RXNE) == SET)
  {
//    ui8_byte_received = UART2_ReceiveData8 ();
  }
}

int main (void)
{
  //set clock at the max 16MHz
//  CLK_HSIPrescalerConfig (CLK_PRESCALER_HSIDIV1); // FAILS if enabled, system seems to block aftersome time

  gpio_init ();
  uart_init ();

  while (1)
  {
    printf ("Hello world -- Flexible OpenSource firmware for TongSheng TSDZ2 mid drive motor\n");
  }

  return 0;
}
