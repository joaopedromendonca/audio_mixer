#include "file_access.h"

void print_wav(Wave_t *wav)
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
    printf("\n------------------------Fim do cabeçalho");
    printf("\n");
}

Wave_t *read_wave_file(Wave_t *wave_file, char *file_name)
{
    // Format file name to match directory path
    char *s = (char *)malloc(9);
    strcpy(s, "samples/");
    strcat(s, file_name);
    printf("------------------------Lendo arquivo: %s", s);

    FILE *file = fopen(s, "rb");
    // Read RIFF block
    fread(wave_file->_riff.ChunkID, sizeof(char), 4, file);
    fread(&wave_file->_riff.ChunkSize, sizeof(uint32_t), 1, file);
    fread(wave_file->_riff.Format, sizeof(char), 4, file);

    // Read fmt block
    fread(wave_file->_fmt.SubChunk1ID, sizeof(char), 4, file);
    fread(&wave_file->_fmt.SubChunk1Size, sizeof(uint32_t), 1, file);
    fread(&wave_file->_fmt.Audio_format, sizeof(uint16_t), 1, file);
    fread(&wave_file->_fmt.Num_chanels, sizeof(uint16_t), 1, file);
    fread(&wave_file->_fmt.Sample_rate, sizeof(uint32_t), 1, file);
    fread(&wave_file->_fmt.Byte_rate, sizeof(uint32_t), 1, file);
    fread(&wave_file->_fmt.Block_align, sizeof(uint16_t), 1, file);
    fread(&wave_file->_fmt.Bits_per_sample, sizeof(uint16_t), 1, file);

    // Read data block
    fread(wave_file->_data.SubChunk2ID, sizeof(char), 4, file);
    fread(&wave_file->_data.SubChunk2Size, sizeof(uint32_t), 1, file);

    print_wav(wave_file);
    // Start reading audio data
    printf("\nStart the reading of the audio data\n");

    return wave_file;
}

int main(int argc, char const *argv[])
{
    Wave_t *wav = (Wave_t *)malloc(sizeof(Wave_t));
    // strcpy(wav->_riff.ChunkID, "xdxd");
    wav = read_wave_file(wav, "music.wav");
    return 0;
}