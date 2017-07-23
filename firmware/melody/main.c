/*
 * melody.c
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "melody.h"
#include "test.h"
#include "kamata4.h"
#include "hw_misc.h"


int main(void)
{
	// set up 32.768kHz RTC clock (for DFLL)
	CLK.RTCCTRL = CLK_RTCSRC_EXTCLK_gc;

	// set 32MHz CPU clock, 128MHz PWM clock
	HW_CCPWrite(&OSC.CTRL, OSC.CTRL | OSC_RC32MEN_bm);
	while (!(OSC.STATUS & OSC_RC32MRDY_bm));

	OSC.PLLCTRL = OSC_PLLSRC_RC32M_gc | 16;				// source is actually RC32M divided by 4!
	HW_CCPWrite(&OSC.CTRL, OSC.CTRL | OSC_PLLEN_bm);
	while (!(OSC.STATUS & OSC_PLLRDY_bm));

	HW_CCPWrite(&CLK.PSCTRL, CLK_PSADIV_1_gc | CLK_PSBCDIV_2_2_gc);
	HW_CCPWrite(&CLK.CTRL, CLK_SCLKSEL_PLL_gc);

	// DFLL for RC oscillator
	HW_CCPWrite(&OSC.CTRL, OSC.CTRL | OSC_RC32KEN_bm);
	while (!(OSC.STATUS & OSC_RC32KRDY_bm));
	OSC.DFLLCTRL = OSC_RC32MCREF_RC32K_gc;
	DFLLRC32M.COMP2 = 0x7A;
	DFLLRC32M.COMP1 = 0x12;
	DFLLRC32M.CTRL = DFLL_ENABLE_bm;
	

	//PORTD.DIRSET = PIN7_bm;
	//PORTCFG.CLKOUT = PORTCFG_CLKOUTSEL_CLK1X_gc | PORTCFG_CLKOUT_PD7_gc;


	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	sei();

	MEL_play(kamata4);
	//MEL_play(test);
	for(;;);
}

