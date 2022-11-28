#include "../headers/file_access.h"

void print_wav(Wav_t *wav)
{
    // Printing RIFF block
    printf("\nRIFF: ");
    for (int i = 0; i < 4; i++)
        printf("%c", wav->_riff.ChunkID[i]);
    printf("\nChunkSize: %d", wav->_riff.ChunkSize);
    printf("\nFormat: ");
    for (int i = 0; i < 4; i++)
        printf("%c", wav->_riff.Format[i]);

    // Printing fmt block
    printf("\n\nSubChunk1ID: ");
    for (int i = 0; i < 4; i++)
        printf("%c", wav->_fmt.SubChunk1ID[i]);
    printf("\nSubChunk1Size: %d", wav->_fmt.SubChunk1Size);
    printf("\nAudio format: %d", wav->_fmt.Audio_format);
    printf("\nNumber of chanels: %d", wav->_fmt.Num_chanels);
    printf("\nSample rate: %d", wav->_fmt.Sample_rate);
    printf("\nByte rate: %d", wav->_fmt.Byte_rate);
    printf("\nBlock align: %d", wav->_fmt.Block_align);
    printf("\nBits per sample: %d", wav->_fmt.Bits_per_sample);

    // Printing data block
    printf("\nSubChunk2ID: ");
    for (int i = 0; i < 4; i++)
        printf("%c", wav->_data.SubChunk2ID[i]);
    printf("\nSubChunk2Size: %d", wav->_data.SubChunk2Size);
    printf("\n------------------------End of header");
    printf("\n");
}

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

    print_wav(wav_file);
    // Start reading audio data
    printf("\nStart the reading of the audio data\n");

    size_t size_LR = 0;
    L = malloc(sizeof(int16_t));
    R = malloc(sizeof(int16_t));
    size_LR++;

    printf("\nInit size of L: %lu\n", sizeof(L));
    // Consider the reading of samples with 2 channels
    int i = 0;
    int16_t *tmp_reader = malloc(sizeof(int16_t));
    while (i < wav_file->_data.SubChunk2Size)
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
            fprintf(stderr, "Array not alocated!");
            exit(1);
        }

        i++;
    }
    for (int i = 0; i < wav_file->_data.SubChunk2Size; i++)
    {
        printf("\nLeft: %i - Right: %i\n", L[i], R[i]);
    }
    printf("\nLeft: %i - Right: %i\n", L[3], L[4]);
    return wav_file;
}

int main(int argc, char const *argv[])
{
    Wav_t *wav = (Wav_t *)malloc(sizeof(Wav_t));
    // strcpy(wav->_riff.ChunkID, "xdxd");
    char *path = realpath("../samples/music.wav", NULL);
    wav = read_wave_file(wav, path);
    return 0;
}