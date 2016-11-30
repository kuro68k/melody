/*
 * melody.c
 */

#include <avr/io.h>
#include "melody.h"
#include "test.h"


int main(void)
{
	MEL_play(test);
	for(;;);
}

