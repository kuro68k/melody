/*
 * hw_misc.c
 *
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "hw_misc.h"

/**************************************************************************************************
** Write a CCP protected register.
**
** Interrupts are temporarily disabled during the write. Code mostly adapted/stolen from Atmel's
** clksys_driver.c and avr_compiler.h.
*/
void HW_CCPWrite(volatile uint8_t *address, uint8_t value)
{
        uint8_t	saved_sreg;

        // disable interrupts if running
		saved_sreg = SREG;
		cli();
		
		volatile uint8_t * tmpAddr = address;
        RAMPZ = 0;

        asm volatile(
                "movw r30,  %0"       "\n\t"
                "ldi  r16,  %2"       "\n\t"
                "out   %3, r16"       "\n\t"
                "st     Z,  %1"       "\n\t"
                :
                : "r" (tmpAddr), "r" (value), "M" (CCP_IOREG_gc), "i" (&CCP)
                : "r16", "r30", "r31"
                );

        SREG = saved_sreg;
}
