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
    char *L, *R;

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

    // Consider the reading of samples with 2 channels
    // int isOver = 0;
    // while (!isOver)
    // {

    //     fread(wav_file->_data.Audio_data, sizeof(char), 4, file);
    //     fread(wav_file->_data.Audio_data, sizeof(char), 4, file);
    // }

    return wav_file;
}

// int main(int argc, char const *argv[])
// {
//     wav_t *wav = (Wave_t *)malloc(sizeof(Wave_t));
//     // strcpy(wav->_riff.ChunkID, "xdxd");
//     wav = read_wav_file(wav, "music.wav");
//     return 0;
// }