/*
 * melody.c
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "melody.h"
#include "test.h"


int main(void)
{
	// set up 32.768kHz RTC clock (for DFLL)
	CLK.RTCCTRL = CLK_RTCSRC_EXTCLK_gc;

	// set 32MHz clock
	OSC.DFLLCTRL = OSC_RC32MCREF_XOSC32K_gc;
	OSC.CTRL |= OSC_RC32MEN_bm;
	while (!(OSC.STATUS & OSC_RC32MRDY_bm));
	CLK.PSCTRL = CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;

	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();

	MEL_play(test);
	for(;;);
}

