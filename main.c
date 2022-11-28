#include "headers/main.h"
#include "headers/file_access.h"

int main(int argc, char const *argv[])
{
    Wav_t *wav = (Wav_t *)malloc(sizeof(Wav_t));
    char *path = realpath("samples/music.wav", NULL);
    wav = read_wave_file(wav, path);
    return 0;
}
