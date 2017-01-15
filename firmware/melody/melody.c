/*
 * melody.c
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include "melody.h"
#include "wave1.h"


#define _countof(array)		(sizeof(array) / sizeof(array[0]))

#define SAMPLE_TC			TCC5
#define SAMPLE_EVENT_MUX	EVSYS_CHMUX_TCC5_OVF_gc
#define	PWM_TC				TCC4

#define NUM_VOICES			6
#define BUFFER_SAMPLES		32

// sample step size * 65536
const __flash uint32_t key_lut[] = {	4286,4540,4810,5099,5400,5723,6061,6423,6805,7209,7639,8092,8572,
										9083,9623,10195,10800,11443,12124,12845,13608,14418,15275,16185,
										17147,18167,19247,20390,21603,22888,24248,25690,27218,28836,30550,
										32367,34291,36331,38491,40779,43204,45773,48497,51380,54434,57672,
										61101,64734,68585,72661,76981,81561,86411,91549,96991,102760,
										108868,115343,122201,129468,137167,145325,153965,163119,172818,
										183097,193984,205518,217739,230687,244405,258938,274334,290647,
										307930,326241,345639,366192,387968,411037,435479,461373,488809,
										517873,548667,581294,615860,652482,691279,732386,775936,822073,
										870958,922747,977616,1035749,1097337,1162588,1231718,1304961,
										1382558,1464769,1551869,1644149,1741915,1845494,1955232,2071496 };

// note decay multipliers
const __flash uint8_t decay_lut[] = {	255,252,250,247,245,243,240,238,235,233,231,228,226,224,222,219,
										217,215,213,211,209,207,205,203,201,199,197,195,193,191,189,187,
										185,183,182,180,178,176,174,173,171,169,168,166,164,163,161,159,
										158,156,155,153,152,150,149,147,146,144,143,141,140,139,137,136,
										134,133,132,130,129,128,127,125,124,123,122,120,119,118,117,116,
										115,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,
										98,97,96,95,94,93,92,91,90,89,88,87,87,86,85,84,
										83,82,82,81,80,79,78,78,77,76,75,75,74,73,72,72,
										71,70,69,69,68,67,67,66,65,65,64,64,63,62,62,61,
										60,60,59,59,58,57,57,56,56,55,55,54,54,53,53,52,
										51,51,50,50,49,49,48,48,48,47,47,46,46,45,45,44,
										44,43,43,43,42,42,41,40,40,39,39,38,38,37,37,36,
										35,35,34,34,33,33,32,31,31,30,30,29,29,28,28,27,
										26,26,25,25,24,24,23,22,22,21,21,20,20,19,19,18,
										17,17,16,16,15,15,14,13,13,12,12,11,11,10,10,9,
										8,8,7,7,6,6,5,4,4,3,3,2,2,1,1,0 };

typedef struct
{
	uint8_t		channel;
	uint8_t		key;
	uint8_t		velocity;
	uint8_t		decay;
	uint32_t	sample_ptr;
} VOICE_t;


volatile uint8_t	dma_ch0_complete_SIG = 0;
volatile uint8_t	dma_ch2_complete_SIG = 0;
volatile uint16_t	buffer_a[32];
volatile uint16_t	buffer_b[32];


/**************************************************************************************************
** Sample timer overflow interrupt
*/
ISR(TCC5_OVF_vect)
{
	static uint8_t sample = 0;
	static bool db = 0;
	static volatile uint16_t *buffer = buffer_a;

	SAMPLE_TC.INTFLAGS = TC5_OVFIF_bm;		// clear interrupt flag

	uint16_t s = buffer[sample++];
	PWM_TC.CCCBUF = s;
	PWM_TC.CCDBUF = (~s) & 0x1FF;

	if (sample >= BUFFER_SAMPLES)
	{
		if (!db)
		{
			dma_ch0_complete_SIG = 0xFF;
			buffer = buffer_b;
		}
		else
		{
			dma_ch2_complete_SIG = 0xFF;
			buffer = buffer_a;
		}
		db = !db;
		sample = 0;
	}
}

/**************************************************************************************************
** Configure melody generator hardware
*/
void mel_wake(void *buffer_a, void *buffer_b, uint16_t buffer_length_bytes)
{
	// DAC for audio output
	DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;
	DACA.CTRLB = DAC_CHSEL_SINGLE_gc;
	DACA.CTRLC = DAC_REFSEL_AVCC_gc;

	// PWM timer
	PORTC.DIRSET = PIN2_bm | PIN3_bm;
	//PORTCFG.SRLCTRL |= PORTCFG_SRLENRC_bm;	// slew rate limiting
	HIRESC.CTRLA = HIRES_HRPLUS_HRP4_gc | HIRES_HREN_HRP4_gc;
	PWM_TC.CTRLA = 0;	// stop if running
	PWM_TC.CTRLB = TC_TC4_WGMODE_NORMAL_gc;
	PWM_TC.CTRLC = 0;
	PWM_TC.CTRLD = 0;
	PWM_TC.CTRLE = TC_TC4_CCCMODE_COMP_gc | TC_TC4_CCDMODE_COMP_gc;
	PWM_TC.INTCTRLA = 0;
	PWM_TC.INTCTRLB = 0;
	PWM_TC.CNT = 0;
	PWM_TC.PER = 0x01FF;
	PWM_TC.CCC = 0xFF;
	PWM_TC.CCD = 0xFF;
	PWM_TC.CTRLA = TC_TC4_CLKSEL_DIV1_gc;

	// 32kHz sample timer
	SAMPLE_TC.CTRLA = 0;	// stop if running
	SAMPLE_TC.CTRLB = 0;
	SAMPLE_TC.CTRLC = 0;
	SAMPLE_TC.CTRLD = 0;
	SAMPLE_TC.CTRLE = 0;
	SAMPLE_TC.INTCTRLA = 0;
	SAMPLE_TC.INTCTRLB = 0;
	SAMPLE_TC.CNT = 0;
	SAMPLE_TC.PER = 0x03E7;	// 32kHz @ 32MHz
	SAMPLE_TC.CTRLA = TC_TC4_CLKSEL_DIV1_gc;

	// event channel to drive DMA
	EVSYS.CH0CTRL = 0;
	EVSYS.CH0MUX = SAMPLE_EVENT_MUX;

	// DMA to copy samples to DAC
	EDMA.CTRL = 0;
	EDMA.CTRL = EDMA_RESET_bm;
	EDMA.CTRL = EDMA_ENABLE_bm | EDMA_CHMODE_STD02_gc | EDMA_DBUFMODE_BUF0123_gc | EDMA_PRIMODE_RR0123_gc;

	EDMA_CH_t *ch = &EDMA.CH0;
	for (uint8_t i = 0; i < 2; i++)
	{
		ch->CTRLA = EDMA_CH_SINGLE_bm | EDMA_CH_BURSTLEN_bm;
		ch->ADDRCTRL = EDMA_CH_RELOAD_BLOCK_gc | EDMA_CH_DIR_INC_gc;
		ch->DESTADDRCTRL = EDMA_CH_RELOAD_BURST_gc | EDMA_CH_DIR_INC_gc;
		ch->TRIGSRC = EDMA_CH_TRIGSRC_EVSYS_CH0_gc;
		ch->TRFCNT = buffer_length_bytes;
		ch->DESTADDR = (uint16_t)&DACA.CH0DATA;
		ch = &EDMA.CH2;
	}
	EDMA.CH0.ADDR = (uint16_t)buffer_a;
	EDMA.CH2.ADDR = (uint16_t)buffer_b;
}

/**************************************************************************************************
** Shut down melody generator hardware
*/
void mel_sleep(void)
{
	DACA.CTRLA = 0;
	SAMPLE_TC.CTRLA = 0;
	EDMA.CTRL = 0;
	EDMA.CH0.CTRLA = 0;
}

/**************************************************************************************************
** Play a melody
*/
void MEL_play(const __flash NOTE_t *melody)
{
	for (uint8_t i = 0; i < 32; i++)
		buffer_a[i] = buffer_b[i] = 256;

	PORTC.OUT = 0x01;
	PORTC.DIR = 0xFF;
	mel_wake((void *)buffer_a, (void *)buffer_b, sizeof(buffer_a));

	VOICE_t voices[NUM_VOICES];
	memset(voices, 0, sizeof(voices));

	uint16_t ms_counter = 0;
	bool exit_flag = false;
	bool all_silent = false;

/*
	for(uint16_t i = 0; i < 500; i++)
	{
		for (uint16_t s = 0; s < 256; s++)
		{
			uint8_t s1 = sinewave.wave[s] - 0x80;
			uint8_t s2 = ~s1;
			
			PWM_TC.CCCBUF = (uint16_t)s1 * 2;
			PWM_TC.CCDBUF = (uint16_t)s2 * 2;
			_delay_us(4);
		}
	}
	for(;;);
*/
	DACA.CH0DATA = 2048;
	_delay_ms(50);

	//uint16_t idx = 0;
	//uint8_t sub = 0;
	//uint16_t limit = wave1.attack_len + wave1.sustain_len;
	//uint16_t limit = sinewave.attack_len + sinewave.sustain_len;
	
	//EDMA.CH2.CTRLA |= EDMA_CH_REPEAT_bm;
	//EDMA.CH0.CTRLA |= EDMA_CH_ENABLE_bm;
	SAMPLE_TC.INTCTRLA = TC_TC4_OVFINTLVL_HI_gc;

/*
	for(uint8_t j = 0; j < 254; j++)
	{
		// buffer A
		//EDMA.CH2.CTRLA |= EDMA_CH_REPEAT_bm;
		//while(!(EDMA.INTFLAGS & EDMA_CH0TRNFIF_bm));
		//EDMA.INTFLAGS = EDMA_CH0TRNFIF_bm;
		while (dma_ch0_complete_SIG == 0);
		dma_ch0_complete_SIG = 0;
		
		//for (uint8_t i = 0; i < _countof(buffer_a); i++)
		for (uint8_t i = 0; i < 32; i++)
		{
			//buffer_a[i] = ((int16_t)wave1.wave[idx] * 1) + 2048;
			uint8_t s = wave1.wave[idx] - 0x80;
			buffer_a[i] = (uint16_t)s * 1;
			sub++;
			if (sub > 0)
			{
				sub = 0;
				idx += 6;
				if (idx >= limit)
					idx -= wave1.sustain_len;
			}
		}
		
		// buffer B
		//EDMA.CH0.CTRLA |= EDMA_CH_REPEAT_bm;
		//while(!(EDMA.INTFLAGS & EDMA_CH2TRNFIF_bm));
		//EDMA.INTFLAGS = EDMA_CH2TRNFIF_bm;
		while (dma_ch2_complete_SIG == 0);
		dma_ch2_complete_SIG = 0;

		for (uint8_t i = 0; i < 32; i++)
		{
			//buffer_b[i] = ((int16_t)wave1.wave[idx] * 1) + 2048;
			uint8_t s = wave1.wave[idx] - 0x80;
			buffer_b[i] = (uint16_t)s * 1;
			sub++;
			if (sub > 0)
			{
				sub = 0;
				idx += 6;
				if (idx >= limit)
					idx -= wave1.sustain_len;
			}
		}

	}
	SAMPLE_TC.INTCTRLA = TC_TC4_OVFINTLVL_OFF_gc;
*/	

	//for(;;);

	uint32_t limit_scaled = (uint32_t)(wave1.attack_len + wave1.sustain_len) << 16;
	uint32_t sustain_length_scaled = (uint32_t)wave1.sustain_len << 16;

	do
	{
		// wait for a buffer to complete
		while (!dma_ch0_complete_SIG && !dma_ch2_complete_SIG);

		volatile uint16_t *ptr;
		if (dma_ch0_complete_SIG)
		{
			dma_ch0_complete_SIG = 0;
			ptr = buffer_a;
			//EDMA.CH0.CTRLA |= EDMA_CH_REPEAT_bm;
		}
		else
		{
			dma_ch2_complete_SIG = 0;
			ptr = buffer_b;
			//EDMA.CH2.CTRLA |= EDMA_CH_REPEAT_bm;
		}



		// process any note start/stop events
		while (melody->time == ms_counter)
		{
			//if (melody->channel != 0)
			//	goto hack1;
			if (melody->velocity != 0)	// start a voice
			{
				uint8_t i = melody->channel % NUM_VOICES;
				//for (uint8_t i = 0; i < NUM_VOICES; i++)
				//{
					//if (voices[i].velocity == 0)	// free voice
					//{
						voices[i].channel = melody->channel;
						voices[i].key = melody->key;
						voices[i].velocity = melody->velocity;
						voices[i].decay = 0;
						voices[i].sample_ptr = 0;
						//break;
					//}
				//}
			}
			else						// stop a voice
			{
				for (uint8_t i = 0; i < NUM_VOICES; i++)
				{
					if ((voices[i].channel == melody->channel) &&
						(voices[i].key == melody->key))
					{
						voices[i].velocity = 0;	// stop
					}
				}
			}
//hack1:
			melody++;	// next note
			if (melody->time == -1)
				exit_flag = true;
		}

		ms_counter++;


		// generate buffer
		all_silent = true;
		for (uint8_t sample = 0; sample < 32; sample++)
		{
			int32_t a = 0;
			for (uint8_t i = 0; i < NUM_VOICES; i++)
			{
				if (voices[i].velocity != 0)
				{
					uint16_t idx = voices[i].sample_ptr >> 16;
					//__int24 s = wave1.wave[idx];
					int32_t s = wave1.wave[idx];
					s *= voices[i].velocity;
					s *= decay_lut[voices[i].decay >> 1];
					a += s;

					voices[i].sample_ptr += key_lut[voices[i].key];
					if (voices[i].sample_ptr > limit_scaled)
					{
						voices[i].sample_ptr -= sustain_length_scaled;
						voices[i].decay++;
						if (voices[i].decay > sizeof(decay_lut))	// note faded out
							voices[i].velocity = 0;
					}

					all_silent = false;
				}
			}
			a >>= 16;
			if (a > 253) a = 253;
			if (a < -255) a = -255;
			*ptr++ = a + 0xFF;
		}
	} while(!exit_flag || !all_silent);

	mel_sleep();
}
