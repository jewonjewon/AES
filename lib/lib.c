#include <stdio.h>
#include <stdint.h>
#include <time.h>

void wordToByte(uint32_t *input, uint8_t *output, uint8_t wordnum)
{
    for (int j = 0; j < (wordnum << 2); j++)
        output[j] = ((input[j >> 2] >> (24 - ((j & 3) << 3)))) & 0xff;
}