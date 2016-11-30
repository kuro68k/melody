// midi-decode.c
//

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"


#define byteswap32(word)	do { word = ((word << 24) & 0xFF000000) | ((word << 8) & 0xFF0000) | ((word >> 8) & 0xFF00) | ((word >> 24) & 0xFF); } while(0);
#define byteswap16(word)	do { word = ((word << 8) & 0xFF00) | ((word >> 8) & 0xFF); } while(0);

#define MAX_TRACK_SIZE		500


#pragma pack(1)
struct
{
	char		id[4];
	uint32_t	length;
	uint16_t	format;
	uint16_t	num_tracks;
	uint16_t	division;
} file_header;

struct
{
	char		id[4];
	uint32_t	length;
} track_header;

struct
{
	int			time;
	int			channel;
	int			key;
	int			velocity;
} track[MAX_TRACK_SIZE];

int tick_rate = 1000;	// ticks per second of note timer
int ppq = 0;			// parts per quarter note
double ms_per_midi_tick = 0;
int track_index = 0;


// read a variable length number
uint32_t read_var_len(FILE *fin)
{
	uint32_t v = 0;
	int c;

	for (int i = 0; i < 4; i++)		// limit to 32 bits
	{
		c = fgetc(fin);
		if (c == EOF)
			return v;
		v = (v << 7) | (c & 0x7f);
		if (!(c & 0x80))
			return v;
	}

	return v;
}

// read and decode the file header
int read_file_header(FILE *fin)
{
	fread(&file_header, sizeof(file_header), 1, fin);
	byteswap32(file_header.length);
	byteswap16(file_header.format);
	byteswap16(file_header.num_tracks);
	byteswap16(file_header.division);

	if ((memcmp(&file_header.id, "MThd", 4) != 0) ||
		(file_header.length != 6))
	{
		printf("Bad file header.\n");
		return 1;
	}

	if (file_header.format != 0)
	{
		printf("Only format 0 files supported.\n");
		return 1;
	}

	// decode timing information
	if (file_header.division & 0x8000)	// SMPTE format
	{
		uint8_t subd = abs((file_header.division >> 8) & 0xFF);
		uint8_t div = file_header.division & 0xFF;
		ppq = subd * div;
	}
	else								// simple ppq value
	{
		ppq = file_header.division;
	}
	printf("PPQ: %d\n", ppq);

	return 0;
}

// read and decode a track header
int read_track_header(FILE *fin)
{
	fread(&track_header, sizeof(track_header), 1, fin);
	byteswap32(track_header.length);

	if ((memcmp(&track_header.id, "MTrk", 4) != 0) ||
		(track_header.length > (1024L * 1024L * 10L)))	// let's not get carried away
	{
		printf("Bad track header.\n");
		return 1;
	}

	return 0;
}

// decode a system event
int decode_system_exclusive(FILE *fin)
{
	uint8_t type = fgetc(fin);
	printf("Unknown system exclusive event (%02X).\n", type);
	long int l = read_var_len(fin);
	fseek(fin, l, SEEK_CUR);	// skip event data
	return 0;
}

// decode a meta event
int decode_meta(FILE *fin)
{
	uint8_t meta_type = fgetc(fin);
	long int l;

	switch (meta_type)
	{
		case 0x58:	// time signature
			printf("Time signature\n");
			l = read_var_len(fin);
			fseek(fin, l, SEEK_CUR);	// skip meta event data
			break;

		case 0x51:	// tempo
			printf("Tempo\n");
			l = read_var_len(fin);
			if (l != 3)
			{
				printf("Bad length (%d)\n", l);
				return 1;
			}
			uint32_t tempo = ((fgetc(fin) & 0xFF) << 16) | ((fgetc(fin) & 0xFF) << 8) | (fgetc(fin) & 0xFF);
			printf("Tempo: %u us\n", tempo);
			tempo /= 1000;	// us -> ms conversion
			ms_per_midi_tick = (double)tempo / (double)ppq;
			printf("Milliseconds per MIDI tick: %lf\n", ms_per_midi_tick);
			break;

		case 0x2F:	// end of track
			printf("End of track\n");
			return 1;
			break;

		default:
			printf("Unknown meta event (%02X).\n", meta_type);
			l = read_var_len(fin);
			fseek(fin, l, SEEK_CUR);	// skip meta event data
			break;
	}

	return 0;
}

// decode a track
int decode_track(FILE *fin)
{
	uint8_t last_type_chan = 0;
	uint32_t abs_time_ticks = 0;
	double abs_time_ms = 0;

	for(;;)
	{
		uint32_t time = read_var_len(fin);
		int temp = fgetc(fin);
		if (temp == -1)
			break;
		uint8_t type_chan = temp;

		if (!(type_chan & 0x80))	// not a status byte, so use running status
		{
			type_chan = last_type_chan;
			fseek(fin, -1, SEEK_CUR);	// re-read this byte as data
		}

		abs_time_ticks += time;
		abs_time_ms += time * ms_per_midi_tick;
		printf("%u\t+%u\t%f\t%02X\t", abs_time_ticks, time, abs_time_ms, type_chan);

		switch (type_chan & 0xF0)
		{
			case 0x90:	// note on
			{
				uint8_t key, velocity;
				key = fgetc(fin);
				velocity = fgetc(fin);
				printf("Note on (ch %u, key %u, velocity %u)\n", type_chan & 0x0F, key, velocity);
				//printf("--> %u,%u,%u,\n", type_chan & 0x0F, key, velocity);
				track[track_index].time = (int)abs_time_ms;
				track[track_index].channel = type_chan & 0x0F;
				track[track_index].key = key;
				track[track_index].velocity = velocity;
				track_index++;
				break;
			}

			case 0x80:
			{
				uint8_t key, velocity;
				key = fgetc(fin);
				velocity = fgetc(fin);
				printf("Note off (ch %u, key %u, velocity %u)\n", type_chan & 0x0F, key, velocity);
				//printf("--> %u,%u,%u,\n", type_chan & 0x0F, key, 0);
				track[track_index].time = (int)abs_time_ms;
				track[track_index].channel = type_chan & 0x0F;
				track[track_index].key = key;
				track[track_index].velocity = 0;	// force to zero = off
				track_index++;
				break;
			}

			case 0xC0:	// program change
				printf("Program change (ignored)\n", type_chan & 0x0F);
				fgetc(fin);	// discard parameter
				break;

			case 0xF0:	// meta or system event
			{
				if (type_chan == 0xFF)
				{
					if (decode_meta(fin) != 0)		// end of track
						return 0;
				}
				else
					decode_system_exclusive(fin);
				break;
			}

			default:
				printf("Unknown event type (%X).\n", type_chan >> 4);
				return 1;
				break;
		}

		last_type_chan = type_chan;
	}

	return 0;
}

int generate_output(char *name)
{
	// sanity check
	if (track_index == 0)
	{
		printf("No note data found.\n");
		return 1;
	}
	if (ms_per_midi_tick == 0)
	{
		printf("Timing information not found.\n");
		return 1;
	}

	// open output file
	char filename[256];
	strncpy(filename, name, sizeof(filename));
	strncat(filename, ".h", sizeof(filename));
	FILE *fout = fopen(filename, "w");
	if (fout == NULL)
	{
		printf("Uanable to open \"%s\".\n", filename);
		return 1;
	}

	// file header
	fprintf(fout, "/* %s\n", filename);
	fprintf(fout, " */\n");
	fprintf(fout, "\n");
	fprintf(fout, "#include <avr/pgmspace.h>\n");
	fprintf(fout, "#include \"melody.h\"\n");
	fprintf(fout, "\n");
	fprintf(fout, "const __flash NOTE_t %s[] = {\n", name);
	fprintf(fout, "\t// time (ms), channel, key, velocity\n");

	for (int i = 0; i < track_index; i++)
	{
		//printf("%u ms, ch %u, key %u, velocity %u\n", track[i].time, track[i].channel, track[i].key, track[i].velocity);
		// time, channel, key, velocity
		fprintf(fout, "\t{ %d, %d, %d, %d },\n", track[i].time, track[i].channel, track[i].key, track[i].velocity);
	}

	fprintf(fout, "\t{ %d, %d, %d, %d },\n", -1, 0, 0, 0);		// end of melody
	fprintf(fout, "};\n");
	fclose(fout);

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("midi-decode <input.mid> <output_name>\n");
		printf("E.g. \"midi-decode test.mid test\" generates test.h\n");
		return 1;
	}

	FILE *fin;
	fin = fopen(argv[1], "rb");
	if (fin == NULL)
	{
		printf("Could not open \"%s\".\n", argv[1]);
		return 1;
	}

	int res;
	if ((res = read_file_header(fin)) != 0)
		return res;
	if ((res = read_track_header(fin)) != 0)
		return res;
	if ((res = decode_track(fin)) != 0)
		return res;
	if ((res = generate_output(argv[2])) != 0)
		return res;

	return 0;
}
