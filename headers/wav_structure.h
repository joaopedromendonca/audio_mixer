#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct RIFF
{
    char ChunkID[4];
    uint32_t ChunkSize;
    char Format[4];
} RIFF;

typedef struct fmt
{
    char SubChunk1ID[4];
    uint32_t SubChunk1Size;
    uint16_t Audio_format;
    uint16_t Num_chanels;
    uint32_t Sample_rate;
    uint32_t Byte_rate;
    uint16_t Block_align;
    uint16_t Bits_per_sample;
} fmt;

typedef struct data
{
    char SubChunk2ID[4];
    uint32_t SubChunk2Size;
    void *Audio_data;
} data;

typedef struct Wav_t
{
    RIFF _riff;
    fmt _fmt;
    data _data;
} Wav_t;