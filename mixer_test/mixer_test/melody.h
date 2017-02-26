/*
 * melody.h
 *
 */


#ifndef MELODY_H_
#define MELODY_H_


typedef struct
{
	uint16_t	time;
	uint8_t		channel;
	uint8_t		key;
	uint8_t		velocity;
} NOTE_t;

typedef struct
{
	uint16_t	attack_len;
	uint16_t	sustain_len;
	int8_t		wave[];
} WAVE_t;


extern void MEL_play(const NOTE_t *melody);


#endif /* MELODY_H_ */