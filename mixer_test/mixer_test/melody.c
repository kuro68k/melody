/*
 * melody.c
 */

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "melody.h"
#include "wave1.h"
#include "wav.h"


#define _countof(array)		(sizeof(array) / sizeof(array[0]))

#define SAMPLE_TC			TCC5
#define SAMPLE_EVENT_MUX	EVSYS_CHMUX_TCC5_OVF_gc
#define	PWM_TC				TCC4

#define NUM_VOICES			6
#define BUFFER_SAMPLES		32

// sample step size * 65536
const uint32_t key_lut[] = {	4286,4540,4810,5099,5400,5723,6061,6423,6805,7209,7639,8092,8572,
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
const uint8_t decay_lut[] = {	255,252,250,247,245,243,240,238,235,233,231,228,226,224,222,219,
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
	uint16_t	decay;
	uint32_t	sample_ptr;
} VOICE_t;


volatile uint8_t	dma_ch0_complete_SIG = 0;
volatile uint8_t	dma_ch2_complete_SIG = 0;
volatile uint16_t	buffer_a[32];
volatile uint16_t	buffer_b[32];


/**************************************************************************************************
** Play a melody
*/
void MEL_play(const NOTE_t *melody)
{
	int32_t max = INT32_MIN;
	int32_t min = INT32_MAX;

	int32_t *raw_buffer;
	int32_t *scaled_buffer;
	uint32_t sample_count = 0;

	raw_buffer = malloc(1024 * 1024 * 10);
	scaled_buffer = malloc(1024 * 1024 * 10);

	VOICE_t voices[NUM_VOICES];
	memset(voices, 0, sizeof(voices));

	uint16_t ms_counter = 0;
	bool exit_flag = false;
	bool all_silent = false;

	uint8_t decay_scaler = 0;


	uint32_t limit_scaled = (uint32_t)(wave1.attack_len + wave1.sustain_len) << 16;
	uint32_t sustain_length_scaled = (uint32_t)wave1.sustain_len << 16;

	do
	{
		// wait for a buffer to complete
		//while (!dma_ch0_complete_SIG && !dma_ch2_complete_SIG);

		//volatile uint16_t *ptr;
		//ptr = buffer_a;



		// process any note start/stop events
		while (melody->time == ms_counter)
		{
			printf("%u\t", ms_counter);
			printf("%u, ", melody->channel);
			printf("%u, ", melody->key);
			printf("%u\n", melody->velocity);

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

			melody++;	// next note
			if (melody->time == 0xFFFF)
				exit_flag = true;
		}

		ms_counter++;


		// generate buffer
		all_silent = true;
		for (uint8_t sample = 0; sample < 32; sample++)
		{
			int32_t a = 0;
			//for (uint8_t i = 0; i < NUM_VOICES; i++)
			for (uint8_t i = 0; i < 1; i++)
			{
				if (voices[i].velocity != 0)
				{
					uint16_t idx = voices[i].sample_ptr >> 16;
					//__int24 s = wave1.wave[idx];
					int32_t s = wave1.wave[idx];
					s *= voices[i].velocity;
					s *= decay_lut[voices[i].decay];
					a += s;

					voices[i].sample_ptr += key_lut[voices[i].key];
					if (voices[i].sample_ptr > limit_scaled)
					{
						voices[i].sample_ptr -= sustain_length_scaled;
						if (decay_scaler == 0)
							voices[i].decay++;
						if (voices[i].decay > sizeof(decay_lut))	// note faded out
							voices[i].velocity = 0;
					}

					all_silent = false;
				}
			}
			raw_buffer[sample_count] = a * (1<<8);
			a >>= 16;
			//a /= (1 << 15);
			if (max < a) max = a;
			if (min > a) min = a;
			if (a > 255) a = 255;
			if (a < -255) a = -255;
			//*ptr++ = a + 0xFF;
			scaled_buffer[sample_count++] = a * (1 << 23);
		}

		decay_scaler++;
		if (decay_scaler > 1)
			decay_scaler = 0;
	} while(!exit_flag || !all_silent);

	printf("Min: %d\n", min);
	printf("Max: %d\n", max);

	WAV_write_file("o_raw.wav", raw_buffer, sample_count);
	WAV_write_file("o_scaled.wav", scaled_buffer, sample_count);
}
