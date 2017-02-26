#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "wav.h"

/**************************************************************************************************
** Set up a new wave file header
*/
void wav_init_header(WAV_FILE_HEADER_t *header, unsigned int channels, unsigned int sample_rate, unsigned int data_size)
{
	memset(header, 0, sizeof(WAV_FILE_HEADER_t));

	// fill out fixed values in file header
	// note that strings are stored big-endian but 16 bit waveform data is little-endian
	header->ChunkID[0] = 'R';
	header->ChunkID[1] = 'I';
	header->ChunkID[2] = 'F';
	header->ChunkID[3] = 'F';
	// ChunkSize filled in later
	header->Format[0] = 'W';
	header->Format[1] = 'A';
	header->Format[2] = 'V';
	header->Format[3] = 'E';

	header->FormatSubchunkID[0] = 'f';
	header->FormatSubchunkID[1] = 'm';
	header->FormatSubchunkID[2] = 't';
	header->FormatSubchunkID[3] = ' ';
	header->FormatSubchunkSize = 16;	// PCM format subchunk
	header->AudioFormat = 1;			// PCM
	header->NumChannels = channels;
	header->SampleRate = sample_rate;
	header->BitsPerSample = 32;
	header->ByteRate = header->SampleRate * header->NumChannels * (header->BitsPerSample / 8);
	header->BlockAlign = header->NumChannels * (header->BitsPerSample / 8);
	header->ChunkSize = sizeof(WAV_FILE_HEADER_t) + data_size - 8;

	header->WaveformSubchunkID[0] = 'd';
	header->WaveformSubchunkID[1] = 'a';
	header->WaveformSubchunkID[2] = 't';
	header->WaveformSubchunkID[3] = 'a';
	header->WaveformSubchunkSize = data_size;
}

/**************************************************************************************************
** Write buffer to WAV file
*/
void WAV_write_file(char *file_name, int32_t *buffer, uint32_t num_samples)
{
	FILE	*wav_fp;

	// output wav file
	char wav_file_name[MAX_PATH];
	char *ext;
	wav_fp = fopen(file_name, "wb");
	if (!wav_fp)
	{
		printf("Unable to open wav output file (%s)", wav_file_name);
		return;
	}

	// wav header
	WAV_FILE_HEADER_t	header;
	wav_init_header(&header, 1, 32000, num_samples * 4);
	fwrite(&header, sizeof(header), 1, wav_fp);

	// audio data
	fwrite(buffer, num_samples * 4, 1, wav_fp);
	fclose(wav_fp);
}
