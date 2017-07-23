// text2wav.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "wav.h"


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("text2wave <multiplier> <file.txt>\n");
		printf("output is file.txt.wav\n");
		return 0;
	}

	int multiplier = atoi(argv[1]);
	if (multiplier == 0)
	{
		printf("Bad multiplier \"%s\".\n", argv[1]);
		return -1;
	}

	FILE *fp;
	fp = fopen(argv[2], "r");
	if (fp == NULL)
	{
		printf("Unable to open \"%s\".\n", argv[2]);
		return -1;
	}

	// count lines
	uint32_t sample_count = 0;
	while (!feof(fp))
	{
		char line[256];
		char *c = fgets(line, sizeof(line), fp);
		if (c != line)
			continue;
		sample_count++;
	}
	fseek(fp, 0, SEEK_SET);
	printf("%u samples read.\n", sample_count);

	// read samples
	int16_t *buffer = malloc(sample_count * sizeof(int16_t));
	if (buffer == NULL)
	{
		printf("Unable to allocate sample buffer.\n");
		return -1;
	}

	sample_count = 0;
	while (!feof(fp))
	{
		char line[256];
		char *c = fgets(line, sizeof(line), fp);
		if (c != line)
			continue;
		int i = atoi(line);
		i *= multiplier;
		if (i > INT16_MAX) i = INT16_MAX;
		if (i < INT16_MIN) i = INT16_MIN;
		buffer[sample_count++] = i;
	}

	char filename[1024];
	strncpy(filename, argv[2], sizeof(filename));
	strncat(filename, ".wav", sizeof(filename));
	WAV_write_file(filename, buffer, sample_count);

	printf("%s written.\n", filename);

	fclose(fp);

	return 0;
}

