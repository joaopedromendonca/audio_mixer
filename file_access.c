#include "file_access.h"

int main(int argc, char const *argv[])
{
    Wave_t *wav = (Wave_t *)malloc(sizeof(Wave_t));
    // strcpy(wav->_riff.ChunkID, "xdxd");
    wav = read_wave_file(wav, "music.wav");
    return 0;
}