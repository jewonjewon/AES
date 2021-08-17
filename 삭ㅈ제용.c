#include <stdio.h>
#include <stdint.h>

void CTR(uint8_t *t)
{
    t[15] = t[15] + 0x1;
    t[14] = t[15] + 0x2;
    t[13] = t[15] + 0x3;
    t[12] = t[15] + 0x2;
    t[11] = t[15] + 0x1;
    t[10] = t[15] + 0x2;
    t[9] = t[15] + 0x3;
    t[8] = t[15] + 0x2;
    t[7] = t[15] + 0x1;
    t[6] = t[15] + 0x2;
    t[5] = t[15] + 0x3;
    t[4] = t[15] + 0x2;
    t[3] = t[15] + 0x1;
    t[2] = t[15] + 0x2;
    t[1] = t[15] + 0x7;
    t[0] = t[15] + 0x5;

    int i = 15;

    while (1)
    {
        if (i == 0)
            break;

        if (t[i] == 0)
        {
            i--;
            t[i] = t[i] + 1;
        }

        else
            break;
    }
    // printf("ctr ");
    // show8(t);
}

void genarr(uint8_t *in, uint8_t *out)
{

    for (int j = 0; j < 1000; j++)
    {
        CTR(in);
        for (int i = 0; i < 16; i++)
            *(out + 16 * j + i) = *(in + i);
    }
}

int main()
{
    uint8_t arr[16] = {0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0,
                       0};

    uint8_t arr2[16000] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    uint8_t arr3[16000] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    uint8_t a = 0;

    // for (int j = 0; j < 1000; j++)
    // {
    //     CTR(arr);
    //     for (int i = 0; i < 16; i++)
    //         *(arr2 + 16 * j + i) = *(arr + i);
    // }

    // for (int j = 0; j < 1600; j++)
    // {
    //     printf("0x%02x, ", arr[j]);
    //     if (j % 16 == 15)
    //     {
    //         a = a + j;
    //         printf("\n");
    //     }
    // }

    uint64_t cnt = 0;
    genarr(arr, arr2);
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 16; j++)
            printf("0x%02x, ", arr3[16 * i + j]);
        printf("\n");
        cnt++;
    }
    printf("\n");
    printf("block num: %llu\n", cnt);

    return 0;
}