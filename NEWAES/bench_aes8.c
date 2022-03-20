#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "aes8.h"

void time_measurement_shift_rows(void (*func)(byte *), byte *state, int cnt)
{
    double start, end;

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        func(state);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

void time_measurement_mix_columns(void (*func)(byte *), byte *state, int cnt)
{
    double start, end;

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        func(state);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

void time_measurement_word_to_byte(void (*func)(byte *, word), word in, int cnt)
{
    double start, end;
    byte blk[4] = {
        0,
    };

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        func(blk, in);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

void time_measurement_byte_to_word(void (*func)(word *, byte *), byte *in, int cnt)
{
    double start, end;
    word blk = 0;

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        func(&blk, in);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

void time_measurement_aes_enc(void (*func)(byte *, byte *, byte *), byte *rk8, int cnt)
{
    double start, end;

    byte p[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    byte c[16] = {
        0,
    };

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        func(c, p, rk8);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("Enc 수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

void time_measurement_aes_dec(void (*func)(byte *, byte *, byte *), byte *rk8, int cnt)
{
    double start, end;

    byte c[16] = {0x39, 0x02, 0xdc, 0x19, 0x25, 0xdc, 0x11, 0x6a, 0x84, 0x09, 0x85, 0x0b, 0x1d, 0xfb, 0x97, 0x32};
    byte p[16] = {
        0,
    };

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        func(p, c, rk8);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("Dec 수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

void time_measurement_key_expansion(void (*func)(word *, byte *), int cnt)
{
    double start, end;

    byte k[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    word rk32[44] = {
        0,
    };
    byte rk8[176] = {
        0,
    };

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < cnt; i++)
    {
        func(rk32, k);
        for (int j = 0; j < 44; j++)
            word_to_byte(rk8 + (4 * j), *(rk32 + j));
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("KeyGen 수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}
