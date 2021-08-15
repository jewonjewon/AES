#include <stdio.h>
#include <stdint.h>

void main()
{
    uint8_t arr[1600] = {
        0,
    };

    uint8_t a = 0;

    for (int j = 0; j < 1600; j++)
    {
        arr[j] = a;
        a++;
    }

    for (int j = 0; j < 1600; j++)
    {
        printf("0x%02x, ", arr[j]);
        if (j % 16 == 15)
        {
            a = a + j;
            printf("\n");
        }
    }
}