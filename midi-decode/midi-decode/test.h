/* test.h
 */

#include <avr/pgmspace.h>
#include "melody.h"

const __flash NOTE_t test[] = {
	// time (ms), channel, key, velocity
	{ 0, 2, 48, 96 },
	{ 0, 2, 60, 96 },
	{ 500, 1, 67, 64 },
	{ 1000, 0, 76, 32 },
	{ 2000, 2, 48, 0 },
	{ 2000, 2, 60, 0 },
	{ 2000, 1, 67, 0 },
	{ 2000, 0, 76, 0 },
	{ -1, 0, 0, 0 },
};
