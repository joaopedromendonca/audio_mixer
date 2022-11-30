#include "../headers/file_access.h"

Wav_t *read_wave_file(Wav_t *wav_file, char *file_name)
{
    // Left and Right channels samples arrays
    int16_t *L, *R;

    printf("------------------------Reading file: %s", file_name);

    // Open file in read mode
    FILE *file = fopen(file_name, "rb");

    // Read RIFF block
    fread(wav_file->_riff.ChunkID, sizeof(char), 4, file);
    fread(&wav_file->_riff.ChunkSize, sizeof(uint32_t), 1, file);
    fread(wav_file->_riff.Format, sizeof(char), 4, file);

    // Read fmt block
    fread(wav_file->_fmt.SubChunk1ID, sizeof(char), 4, file);
    fread(&wav_file->_fmt.SubChunk1Size, sizeof(uint32_t), 1, file);
    fread(&wav_file->_fmt.Audio_format, sizeof(uint16_t), 1, file);
    fread(&wav_file->_fmt.Num_chanels, sizeof(uint16_t), 1, file);
    fread(&wav_file->_fmt.Sample_rate, sizeof(uint32_t), 1, file);
    fread(&wav_file->_fmt.Byte_rate, sizeof(uint32_t), 1, file);
    fread(&wav_file->_fmt.Block_align, sizeof(uint16_t), 1, file);
    fread(&wav_file->_fmt.Bits_per_sample, sizeof(uint16_t), 1, file);

    // Read data block
    fread(wav_file->_data.SubChunk2ID, sizeof(char), 4, file);
    fread(&wav_file->_data.SubChunk2Size, sizeof(uint32_t), 1, file);

    // Start reading audio data
    printf("\nStart the reading of the audio data\n");

    size_t size_LR = 0;
    L = malloc(sizeof(int16_t));
    R = malloc(sizeof(int16_t));
    size_LR++;

    // Consider the reading of samples with 2 channels
    int i = 0;
    int16_t *tmp_reader = malloc(sizeof(int16_t));

    /*
    Each iteration gets Left and Right channel samples
    According to wav information, the field Subchunk2Size is calculated this way:

        Subchunk2Size = NumSamples * NumChannels * BitsPerSample/8

    Since we have 2 channels, and the last argument means the size of each sample in bytes
    We have this:

        NumSamples = Subchunk2Size / (NumChannels*BitsPerSample/8)

    That is:

        NumSamples = Subchunk2Size / (2*2)

    */
    int NumSamples = wav_file->_data.SubChunk2Size / 4;
    while (i < NumSamples)
    {

        // Reading data to the samples arrays
        fread(tmp_reader, sizeof(int16_t), 1, file);
        L[i] = *tmp_reader;
        fread(tmp_reader, sizeof(int16_t), 1, file);
        R[i] = *tmp_reader;

        // Reallocation of the samples arrays
        size_LR++;
        L = realloc(L, size_LR * sizeof(int16_t));
        R = realloc(R, size_LR * sizeof(int16_t));

        // In case realloc fails
        if (L == NULL || R == NULL)
        {
            fprintf(stderr, "Array could not be alocated!");
            exit(1);
        }
        i++;
    }
    size_LR--;

    // Code below for testing data sample persistence
    // for (int i = size_LR - 200; i < size_LR; i++)
    // {
    //     printf("\n%d | x: %d", L[i], R[i]);
    // }
    // printf("\n\nChecksum of read data: %d/%d", (int)size_LR, NumSamples);

    return wav_file;
}
