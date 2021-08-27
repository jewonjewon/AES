#include <stdio.h>
#include <stdint.h>
#include "mode32.h"

void encrypt32_ecb(uint32_t *k, uint32_t *a, uint64_t n)
{
    for (int j = 0; j < n; j++)
    {
        encrypt32(k, a + 4 * j);
        // show32(a);
    }
}

void decrypt32_ecb(uint32_t *k, uint32_t *a, uint64_t n)
{
    for (int j = 0; j < n; j++)
        decrypt32(k, a + 4 * j);
}

void encrypt32_cbc(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n)
{
    uint32_t c[4] = {
        0,
    };

    for (int j = 0; j < 4; j++)
        c[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < 4; i++)
            c[i] = *(a + (4 * j + i)) ^ c[i];

        encrypt32(k, c);
        for (int i = 0; i < 4; i++)
            *(a + (4 * j + i)) = c[i];
    }
}

void decrypt32_cbc(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n)
{
    uint32_t c[8] = {
        0,
    };
    for (int j = 0; j < 4; j++)
        c[j] = IV[j];

    for (int j = 4; j < 8; j++)
        c[j] = a[4 - j];

    decrypt32(k, a);

    for (int i = 0; i < 4; i++)
        *(a + i) = *(a + i) ^ c[i];
    for (int j = 1; j < n; j++)
    {

        for (int i = 0; i < 4; i++)
        {
            c[i] = c[4 + i];
            c[4 + i] = a[i + 4 * j];
        }
        decrypt32(k, a + 4 * j);

        for (int i = 0; i < 4; i++)
            *(a + (4 * j + i)) = *(a + (4 * j + i)) ^ c[i];
    }
}

void encrypt32_ofb(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n)
{
    uint32_t t[4] = {
        0,
    };

    for (int j = 0; j < 4; j++)
        t[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        encrypt32(k, t);

        for (int i = 0; i < 4; i++)
            *(a + (4 * j + i)) = *(a + (4 * j + i)) ^ t[i];
    }
}

void encrypt32_cfb(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n)
{
    uint32_t c[4] = {
        0,
    };

    for (int j = 0; j < 4; j++)
        c[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        encrypt32(k, c);

        for (int i = 0; i < 4; i++)
            *(a + (4 * j + i)) = *(a + (4 * j + i)) ^ c[i];
        for (int i = 0; i < 4; i++)
            c[i] = *(a + (4 * j + i));
    }
}

void decrypt32_cfb(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n)
{
    uint32_t c[8] = {
        0,
    };

    for (int j = 0; j < 4; j++)
        c[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < 4; i++)
            c[4 + i] = *(a + (4 * j + i));

        encrypt32(k, c);

        for (int i = 0; i < 4; i++)
            *(a + (4 * j + i)) = *(a + (4 * j + i)) ^ c[i];

        for (int i = 0; i < 4; i++)
            c[i] = c[4 + i];
    }
}

void CTR(uint32_t *t)
{
    t[3] = t[3] + 1;

    int i = 3;

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
}

void encrypt32_ctr(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n)
{
    uint32_t ctr[4] = {
        0,
    };

    uint32_t t[4] = {
        0,
    };

    for (int j = 0; j < 4; j++)
        ctr[j] = IV[j];

    for (int j = 0; j < 4; j++)
        t[j] = IV[j];

    for (int j = 0; j < n; j++)
    {

        for (int j = 0; j < 4; j++)
            ctr[j] = t[j];

        encrypt32(k, ctr);

        for (int i = 0; i < 4; i++)
            *(a + (4 * j + i)) = *(a + (4 * j + i)) ^ ctr[i];

        CTR(t);
    }
}