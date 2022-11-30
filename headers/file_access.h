#ifndef __FILE_ACCESS__
#define __FILE_ACCESS__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wav_structure.h"

Wav_t *read_wave_file(Wav_t *wav_file, char *file_name);
void print_wav(Wav_t *wav);

#endif