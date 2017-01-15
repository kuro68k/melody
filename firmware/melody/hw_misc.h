/*
 * hw_misc.h
 *
 * Created: 27/03/2015 15:21:00
 *  Author: kuro68k
 */ 


#ifndef HW_MISC_H_
#define HW_MISC_H_


/**************************************************************************************************
* Macros
*/

// port settings
#define DISABLE_DIGITAL_INPUT(A)	A = (A & ~PORT_ISC_gm) | PORT_ISC_INPUT_DISABLE_gc
#define ENABLE_PULLUP(A)			A = (A & ~PORT_OPC_gm) | PORT_OPC_PULLUP_gc
#define ENABLE_PULLDOWN(A)			A = (A & ~PORT_OPC_gm) | PORT_OPC_PULLDOWN_gc
#define ENABLE_TOTEM(A)				A = (A & ~PORT_OPC_gm) | PORT_OPC_TOTEM_gc

// wait for NVM to wake up for reading the signature row
#define HW_wait_for_sig_row()		while ((NVM.STATUS & NVM_NVMBUSY_bm) == NVM_NVMBUSY_bm)

// Watchdog timer
#define WATCHDOG_ON					do {	while (WDT.STATUS & WDT_SYNCBUSY_bm);									\
											WDR();																	\
											HW_CCPWrite(&WDT.CTRL, WDT_PER_8KCLK_gc | WDT_ENABLE_bm | WDT_CEN_bm);	\
									} while(0)

#define WATCHDOG_OFF				do {	while (WDT.STATUS & WDT_SYNCBUSY_bm);									\
											HW_CCPWrite(&WDT.CTRL, WDT_CEN_bm);										\
									} while(0)

#define WDR()						asm("wdr")

#define NOP()						asm("nop")


/**************************************************************************************************
* Public functions and variables
*/

extern void		HW_CCPWrite(volatile uint8_t *address, uint8_t value);


#endif /* HW_MISC_H_ */