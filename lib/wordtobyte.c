#include <stdio.h>
#include <stdint.h>
#include <time.h>

void show8(uint8_t *a)
{
    printf("block: ");
    for (int j = 0; j < 16; j++)
        printf("%02x ", a[j]);
    printf("\n");
}

void show32(uint32_t *a32)
{
    printf("block: ");
    for (int j = 0; j < 4; j++)
        printf("%08x ", a32[j]);
    printf("\n");
}

void wordToByte1(uint32_t *input, uint8_t *output, uint8_t wordnum)
{
    for (int j = 0; j < (4 * wordnum); j++)
        output[j] = ((input[j / 4] >> (24 - ((j % 4) * 8)))) & 0xff;
}

void wordToByte2(uint32_t *input, uint8_t *output, uint8_t wordnum)
{
    for (int j = 0; j < (wordnum << 2); j++)
        output[j] = ((input[j >> 2] >> (24 - ((j & 3) << 3)))) & 0xff;
}

void byteToWord(uint8_t *input, uint32_t *output, uint8_t bytenum)
{
    for (int j = 0; j < bytenum; j++)
    {
        output[j] = input[(j << 2) + 0];
        output[j] = output[j] << 8;
        output[j] = output[j] | input[(j << 2) + 1];
        output[j] = output[j] << 8;
        output[j] = output[j] | input[(j << 2) + 2];
        output[j] = output[j] << 8;
        output[j] = output[j] | input[(j << 2) + 3];
    }
}

int main()
{
    double start1, end1, start2, end2;

    uint8_t a8[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    //uint8_t a32[4] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint32_t a32[4] = {
        0x00,
    };

    // uint32_t a32[4] = {0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c};
    // uint8_t a8[16] = {0x00};

    // start1 = (double)clock() / CLOCKS_PER_SEC;
    // for (int j = 0; j < 10000000; j++)
    //     wordToByte1(a32, a8, 4);
    // end1 = (((double)clock()) / CLOCKS_PER_SEC);
    // show8(a8);

    // start2 = (double)clock() / CLOCKS_PER_SEC;
    // for (int j = 0; j < 10000000; j++)
    //     wordToByte2(a32, a8, 4);
    // end2 = (((double)clock()) / CLOCKS_PER_SEC);
    // show8(a8);

    start1 = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < 10000000; j++)
        byteToWord(a8, a32, 4);
    end1 = (((double)clock()) / CLOCKS_PER_SEC);
    show32(a32);

    printf("수행 시간 :%lf\n", (end1 - start1));
    // printf("수행 시간 :%lf\n", (end2 - start2));

    return 0;
}