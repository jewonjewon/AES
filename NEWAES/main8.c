#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "aes8.h"
#include "benchmark_aes.h"

uint32_t x_time(uint32_t x)
{
    return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}

void mixColumns(uint8_t *state)
{
    uint8_t t[16] = {
        0,
    };

    for (int j = 0; j < 4; j++)
    {
        t[4 * j + 0] = x_time(state[4 * j + 0]) ^ (x_time(state[4 * j + 1]) ^ state[4 * j + 1]) ^ (state[4 * j + 2]) ^ (state[4 * j + 3]);
        t[4 * j + 1] = (state[4 * j + 0]) ^ x_time(state[4 * j + 1]) ^ (x_time(state[4 * j + 2]) ^ state[4 * j + 2]) ^ (state[4 * j + 3]);
        t[4 * j + 2] = (state[4 * j + 0]) ^ (state[4 * j + 1]) ^ x_time(state[4 * j + 2]) ^ (x_time(state[4 * j + 3]) ^ state[4 * j + 3]);
        t[4 * j + 3] = (x_time(state[4 * j + 0]) ^ state[4 * j + 0]) ^ (state[4 * j + 1]) ^ (state[4 * j + 2]) ^ x_time(state[4 * j + 3]);
    }

    for (int j = 0; j < 16; j++)
        state[j] = t[j];
}

// 천만번 수행 기준 약 5.7초 걸림
void shiftRows(uint8_t *state)
{
    uint8_t t[16] = {
        0,
    };

    for (int j = 0; j < 16; j++)
        t[j] = state[j];

    for (int j = 0; j < 16; j++)
        state[j] = t[(5 * j) % 16];
}

void inline_time_measurement_shift_rows_1(byte *state, int cnt)
{
    double start, end;

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        shift_row(state);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

void inline_time_measurement_shift_rows_2(byte *state, int cnt)
{
    double start, end;

    start = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        shiftRows(state);
    }
    end = (((double)clock()) / CLOCKS_PER_SEC);

    printf("수행 시간(%d번 기준) :%lf\n", cnt, (end - start));
}

int main()
{
    byte a[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    byte k[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    word rk32[44] = {
        0,
    };
    byte rk8[176] = {
        0,
    };

    byte c[16] = {
        0,
    };
    byte msg[16] = {
        0,
    };

    int cnt = 1000000;

    key_expansion(rk32, k);

    for (int j = 0; j < 44; j++)
        word_to_byte(rk8 + (4 * j), *(rk32 + j));

    aes_encrypt(c, a, rk8);
    print_state(c);

    aes_decrypt(msg, c, rk8);
    print_state(msg);

    /* shift rows 시간 측정 */

    inline_time_measurement_shift_rows_1(a, cnt);
    inline_time_measurement_shift_rows_2(a, cnt);
    // time_measurement_shift_rows(shift_row, a, cnt);
    // time_measurement_shift_rows(shiftRows, a, cnt);

    /* Mix Columns 시간 측정 */
    // time_measurement_shift_rows(mix_columns, a, cnt);
    // time_measurement_shift_rows(mixColumns, a, cnt);

    // byte test[4] = {0x11, 0x22, 0x33, 0x44};
    word test = 0x11223344;
    // word ttt = 0;

    /* word_to_byte 시간 측정 */
    // time_measurement_word_to_byte(word_to_byte, test, cnt);
    // time_measurement_word_to_byte(word_to_byte, test, cnt);
    /* byte_to_word 시간 측정 */
    // time_measurement_byte_to_word()

    /* AES 복호화 시간 측정*/
    // time_measurement_aes_dec(aes_decrypt, rk8, cnt);
    // /* AES 암호화 시간 측정*/
    // time_measurement_aes_enc(aes_encrypt, rk8, cnt);

    // time_measurement_key_expansion(key_expansion, cnt);

    /* 2022-03-20 00:18
     * Enc 수행 시간(10000000번 기준) :10.860441
     * Dec 수행 시간(10000000번 기준) :10.335889
     * KeyGen 수행 시간(10000000번 기준) :5.182727
     */
    return 0;
}
