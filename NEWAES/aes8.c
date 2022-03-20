#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aes8.h"

void word_to_byte(byte *out, word in)
{
    out[0] = (byte)(in >> 24);
    out[1] = (byte)(in >> 16);
    out[2] = (byte)(in >> 8);
    out[3] = (byte)(in);
}

void byte_to_word(word *out, byte *in)
{
    *out = (word)in[0] << 24 | (word)in[1] << 16 | (word)in[2] << 8 | (word)in[3];
}

void print_state(byte *state)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("0x%02x ", state[i + 4 * j]);
        }
        newline;
    }
    newline;
}

void copy_state(byte *new_state, byte *state)
{
    memcpy(new_state, state, 16);
}

void rot_word(word *t)
{
    byte tmp[Nb] = {
        0,
    };

    word_to_byte(tmp, *t);

    byte tt = tmp[0];
    tmp[0] = tmp[1];
    tmp[1] = tmp[2];
    tmp[2] = tmp[3];
    tmp[3] = tt;

    byte_to_word(t, tmp);
}

void sub_word(word *t)
{
    byte tmp[Nb] = {
        0,
    };

    word_to_byte(tmp, *t);

    for (int j = 0; j < 4; j++)
        tmp[j] = sbox[tmp[j]];

    byte_to_word(t, tmp);
}

void key_expansion(word *rk, byte *k)
{
    word t;

    for (int i = 0; i < l; i++)
        byte_to_word(rk + i, k + (4 * i));

    for (int i = l; i < 4 * (Nr + 1); i++)
    {
        t = rk[i - 1];

        if (i % l == 0)
        {
            rot_word(&t);
            sub_word(&t);
            t ^= rcon[(i / l) - 1];
        }
        else if (l > 6 and i % l == 4)
            sub_word(&t);

        rk[i] = rk[i - l] ^ t;
    }
}

void addroundkey(byte *state, byte *rk)
{
    for (int j = 0; j < 16; j++)
        state[j] = state[j] ^ rk[j];
}

void sub_bytes(byte *state)
{
    for (int j = 0; j < 16; j++)
        state[j] = sbox[state[j]];
}

/* 천만번 수행 기준 약 0.7초 걸림 */
void shift_row(byte *state)
{
    byte t;

    /* 2nd row */
    t = state[1];
    state[1] = state[5];
    state[5] = state[9];
    state[9] = state[13];
    state[13] = t;

    /* 3rd row */
    t = state[2];
    state[2] = state[10];
    state[10] = t;

    t = state[6];
    state[6] = state[14];
    state[14] = t;

    /* 4th row */
    t = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7] = state[3];
    state[3] = t;
}

/* 천만번 수행 기준 약 3.3초 걸림 */
void mix_columns(byte *state)
{
    byte t[16] = {
        0,
    };

    for (int j = 0; j < 4; j++)
    {
        t[4 * j + 0] = gmul_2[state[4 * j + 0]] ^ gmul_3[state[4 * j + 1]] ^ state[4 * j + 2] ^ state[4 * j + 3];
        t[4 * j + 1] = state[4 * j + 0] ^ gmul_2[state[4 * j + 1]] ^ gmul_3[state[4 * j + 2]] ^ state[4 * j + 3];
        t[4 * j + 2] = state[4 * j + 0] ^ state[4 * j + 1] ^ gmul_2[state[4 * j + 2]] ^ gmul_3[state[4 * j + 3]];
        t[4 * j + 3] = gmul_3[state[4 * j + 0]] ^ state[4 * j + 1] ^ state[4 * j + 2] ^ gmul_2[state[4 * j + 3]];
    }

    copy_state(state, t);
}

void inv_sub_bytes(byte *state)
{
    for (int j = 0; j < 16; j++)
        state[j] = inv_sbox[state[j]];
}

void inv_shift_row(byte *state)
{
    byte t;

    /* 2nd row */
    t = state[13];
    state[13] = state[9];
    state[9] = state[5];
    state[5] = state[1];
    state[1] = t;

    /* 3rd row */
    t = state[2];
    state[2] = state[10];
    state[10] = t;

    t = state[6];
    state[6] = state[14];
    state[14] = t;

    /* 4th row */
    t = state[3];
    state[3] = state[7];
    state[7] = state[11];
    state[11] = state[15];
    state[15] = t;
}

void inv_mix_columns(byte *state)
{
    byte t[16] = {
        0,
    };

    for (int j = 0; j < 4; j++)
    {
        t[4 * j + 0] = gmul_e[state[4 * j + 0]] ^ gmul_b[state[4 * j + 1]] ^ gmul_d[state[4 * j + 2]] ^ gmul_9[state[4 * j + 3]];
        t[4 * j + 1] = gmul_9[state[4 * j + 0]] ^ gmul_e[state[4 * j + 1]] ^ gmul_b[state[4 * j + 2]] ^ gmul_d[state[4 * j + 3]];
        t[4 * j + 2] = gmul_d[state[4 * j + 0]] ^ gmul_9[state[4 * j + 1]] ^ gmul_e[state[4 * j + 2]] ^ gmul_b[state[4 * j + 3]];
        t[4 * j + 3] = gmul_b[state[4 * j + 0]] ^ gmul_d[state[4 * j + 1]] ^ gmul_9[state[4 * j + 2]] ^ gmul_e[state[4 * j + 3]];
    }
    copy_state(state, t);
}

void aes_encrypt(byte *c, byte *p, byte *rk)
{
    byte t[16];
    copy_state(t, p);

    addroundkey(t, rk);

    for (int r = 1; r < Nr; r++)
    {
        sub_bytes(t);
        shift_row(t);
        mix_columns(t);
        addroundkey(t, rk + (16 * r));
    }

    sub_bytes(t);
    shift_row(t);
    addroundkey(t, rk + (16 * Nr));

    copy_state(c, t);
}

void aes_decrypt(byte *p, byte *c, byte *rk)
{
    byte t[16];
    copy_state(t, c);

    addroundkey(t, rk + (16 * Nr));

    for (int r = Nr - 1; r > 0; r--)
    {
        inv_shift_row(t);
        inv_sub_bytes(t);
        addroundkey(t, rk + (16 * r));
        inv_mix_columns(t);
    }

    inv_shift_row(t);
    inv_sub_bytes(t);
    addroundkey(t, rk);

    copy_state(p, t);
}
