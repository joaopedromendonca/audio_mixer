#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wave_structure.h"

Wave_t *read_wave_file(Wave_t *wave_file, char *file_name);
void print_wav(Wave_t *wav);