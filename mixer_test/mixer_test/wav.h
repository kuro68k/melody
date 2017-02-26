typedef struct
{
	char		ChunkID[4];
	uint32_t	ChunkSize;
	char		Format[4];

	// format sub-chunk
	char		FormatSubchunkID[4];
	uint32_t	FormatSubchunkSize;
	uint16_t	AudioFormat;
	uint16_t	NumChannels;
	uint32_t	SampleRate;
	uint32_t	ByteRate;
	uint16_t	BlockAlign;
	uint16_t	BitsPerSample;

	// raw waveform chunk
	char		WaveformSubchunkID[4];
	uint32_t	WaveformSubchunkSize;
	// data follows
} WAV_FILE_HEADER_t;

typedef struct
{
	uint16_t	AudioFormat;
	uint16_t	NumChannels;
	uint32_t	SampleRate;
	uint32_t	ByteRate;
	uint16_t	BlockAlign;
	uint16_t	BitsPerSample;
} WAV_FORMAT_CHUNK_t;



extern void WAV_write_file(char *file_name, int32_t *buffer, uint32_t num_samples);
