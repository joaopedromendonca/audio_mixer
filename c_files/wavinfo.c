#include "../headers/wavinfo.h"

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
    printf("\n\nSubChunk2ID: ");
    for (int i = 0; i < 4; i++)
        printf("%c", wav->_data.SubChunk2ID[i]);
    printf("\nSubChunk2Size: %d", wav->_data.SubChunk2Size);
    printf("\n------------------------End of header");
    printf("\n");
}

int main(int argc, char const *argv[])
{
    Wav_t *wav = (Wav_t *)malloc(sizeof(Wav_t));
    char *path = realpath("../samples/music.wav", NULL);
    wav = read_wave_file(wav, path);
    print_wav(wav);
    return 0;
}