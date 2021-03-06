/* kamata4.h
 */

#include "melody.h"

const NOTE_t kamata4[] = {
	// time (ms), channel, key, velocity
	{ 0, 0, 66, 120 },
	{ 0, 1, 78, 100 },
	{ 0, 2, 66, 100 },
	{ 270, 2, 66, 0 },
	{ 300, 2, 73, 100 },
	{ 300, 2, 69, 100 },
	{ 540, 0, 66, 0 },
	{ 540, 1, 78, 0 },
	{ 570, 2, 73, 0 },
	{ 570, 2, 69, 0 },
	{ 600, 0, 68, 120 },
	{ 600, 1, 80, 100 },
	{ 600, 2, 66, 100 },
	{ 870, 0, 68, 0 },
	{ 870, 1, 80, 0 },
	{ 870, 2, 66, 0 },
	{ 900, 0, 69, 120 },
	{ 900, 1, 81, 100 },
	{ 900, 2, 69, 100 },
	{ 900, 2, 73, 100 },
	{ 1170, 2, 69, 0 },
	{ 1170, 2, 73, 0 },
	{ 1200, 2, 66, 100 },
	{ 1470, 0, 69, 0 },
	{ 1470, 1, 81, 0 },
	{ 1470, 2, 66, 0 },
	{ 1500, 0, 68, 120 },
	{ 1500, 1, 80, 100 },
	{ 1500, 2, 69, 100 },
	{ 1500, 2, 73, 100 },
	{ 1770, 0, 68, 0 },
	{ 1770, 1, 80, 0 },
	{ 1770, 2, 69, 0 },
	{ 1770, 2, 73, 0 },
	{ 1800, 0, 69, 120 },
	{ 1800, 1, 81, 100 },
	{ 1800, 2, 66, 100 },
	{ 2070, 0, 69, 0 },
	{ 2070, 1, 81, 0 },
	{ 2070, 2, 66, 0 },
	{ 2100, 0, 68, 120 },
	{ 2100, 1, 80, 100 },
	{ 2100, 2, 69, 100 },
	{ 2100, 2, 73, 100 },
	{ 2370, 0, 68, 0 },
	{ 2370, 1, 80, 0 },
	{ 2370, 2, 69, 0 },
	{ 2370, 2, 73, 0 },
	{ 2400, 0, 66, 120 },
	{ 2400, 1, 78, 100 },
	{ 2400, 2, 66, 100 },
	{ 2670, 2, 66, 0 },
	{ 2700, 2, 69, 100 },
	{ 2700, 2, 73, 100 },
	{ 2940, 0, 66, 0 },
	{ 2940, 1, 78, 0 },
	{ 2970, 2, 69, 0 },
	{ 2970, 2, 73, 0 },
	{ 3000, 0, 68, 120 },
	{ 3000, 1, 80, 100 },
	{ 3000, 2, 66, 100 },
	{ 3270, 0, 68, 0 },
	{ 3270, 1, 80, 0 },
	{ 3270, 2, 66, 0 },
	{ 3300, 0, 69, 120 },
	{ 3300, 1, 81, 100 },
	{ 3300, 2, 69, 100 },
	{ 3300, 2, 73, 100 },
	{ 3570, 2, 69, 0 },
	{ 3570, 2, 73, 0 },
	{ 3600, 2, 66, 100 },
	{ 3870, 0, 69, 0 },
	{ 3870, 1, 81, 0 },
	{ 3870, 2, 66, 0 },
	{ 3900, 0, 68, 120 },
	{ 3900, 1, 80, 100 },
	{ 3900, 2, 69, 100 },
	{ 3900, 2, 73, 100 },
	{ 4170, 0, 68, 0 },
	{ 4170, 1, 80, 0 },
	{ 4170, 2, 69, 0 },
	{ 4170, 2, 73, 0 },

	{ 4200, 0, 69, 120 },
	{ 4200, 1, 81, 100 },
	{ 4200, 2, 66, 100 },
	{ 4470, 0, 69, 0 },
	{ 4470, 1, 81, 0 },
	{ 4470, 2, 66, 0 },
	{ 4500, 0, 68, 120 },
	{ 4500, 1, 80, 100 },
	{ 4500, 2, 69, 100 },
	{ 4500, 2, 73, 100 },
	{ 4770, 0, 68, 0 },
	{ 4770, 1, 80, 0 },
	{ 4770, 2, 69, 0 },
	{ 4770, 2, 73, 0 },
	{ 4800, 0, 73, 120 },
	{ 4800, 1, 85, 100 },
	{ 4800, 2, 61, 100 },
	{ 5070, 2, 61, 0 },
	{ 5100, 2, 68, 100 },
	{ 5100, 2, 65, 100 },
	{ 5340, 0, 73, 0 },
	{ 5340, 1, 85, 0 },
	{ 5370, 2, 68, 0 },
	{ 5370, 2, 65, 0 },
	{ 5400, 0, 73, 120 },
	{ 5400, 1, 85, 100 },
	{ 5400, 2, 61, 100 },
	{ 5670, 2, 61, 0 },
	{ 5700, 2, 68, 100 },
	{ 5700, 2, 65, 100 },
	{ 5940, 0, 73, 0 },
	{ 5940, 1, 85, 0 },
	{ 5970, 2, 68, 0 },
	{ 5970, 2, 65, 0 },
	{ 6000, 0, 73, 120 },
	{ 6000, 1, 85, 100 },
	{ 6000, 2, 61, 100 },
	{ 6270, 2, 61, 0 },
	{ 6300, 2, 68, 100 },
	{ 6300, 2, 65, 100 },
	{ 6405, 0, 73, 0 },
	{ 6405, 1, 85, 0 },
	{ 6450, 0, 73, 120 },
	{ 6450, 1, 85, 100 },
	{ 6570, 2, 68, 0 },
	{ 6570, 2, 65, 0 },
	{ 6585, 0, 73, 0 },
	{ 6585, 1, 85, 0 },
	{ 6600, 0, 75, 120 },
	{ 6600, 1, 87, 100 },
	{ 6600, 2, 61, 100 },
	{ 6870, 0, 75, 0 },
	{ 6870, 1, 87, 0 },
	{ 6870, 2, 61, 0 },
	{ 6900, 0, 77, 120 },
	{ 6900, 1, 89, 100 },
	{ 6900, 2, 71, 100 },
	{ 6900, 2, 65, 100 },
	{ 7170, 0, 77, 0 },
	{ 7170, 1, 89, 0 },
	{ 7170, 2, 71, 0 },
	{ 7170, 2, 65, 0 },
	{ 7200, 0, 78, 120 },
	{ 7200, 1, 90, 100 },
	{ 7200, 2, 66, 100 },
	{ 7470, 2, 66, 0 },
	{ 7500, 2, 69, 100 },
	{ 7500, 2, 73, 100 },
	{ 7770, 2, 69, 0 },
	{ 7770, 2, 73, 0 },
	{ 7800, 2, 66, 100 },
	{ 8137, 2, 66, 0 },
	{ 8175, 2, 69, 100 },
	{ 8175, 2, 73, 100 },
	{ 8512, 2, 69, 0 },
	{ 8512, 2, 73, 0 },
	{ 8550, 2, 69, 100 },
	{ 8550, 2, 73, 100 },
	{ 10150, 0, 78, 0 },
	{ 10150, 1, 90, 0 },
	{ 10350, 2, 69, 0 },
	{ 10350, 2, 73, 0 },

	{ -1, 0, 0, 0 },
};
