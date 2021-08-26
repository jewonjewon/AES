#include "mode8.h"

// 운용모드(ecb mode)

// encrypt8_ecb(128비트 마스터키, 128비트 평문, 평문의 블록 길이)
void encrypt8_ecb(uint8_t *k, uint8_t *a, uint64_t n)
{
    for (int j = 0; j < n; j++)
        encrypt8(k, a + 16 * j);
}

// decrypt8_ecb(128비트 마스터키, 128비트 평문, 평문의 블록 길이)
void decrypt8_ecb(uint8_t *k, uint8_t *a, uint64_t n)
{
    for (int j = 0; j < n; j++)
        decrypt8(k, a + 16 * j);
}
// end 운용모드(ecb mode)

// 운용모드(cbc mode)

void encrypt8_cbc(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n)
{
    uint8_t c[16] = {
        0,
    };

    for (int j = 0; j < 16; j++)
        c[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < 16; i++)
            c[i] = *(a + (16 * j + i)) ^ c[i];

        encrypt8(k, c);
        for (int i = 0; i < 16; i++)
            *(a + (16 * j + i)) = c[i];
    }
}

void decrypt8_cbc(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n)
{
    uint8_t c[32] = {
        0,
    };
    for (int j = 0; j < 16; j++)
        c[j] = IV[j];

    for (int j = 16; j < 32; j++)
        c[j] = a[16 - j];

    decrypt8(k, a);

    for (int i = 0; i < 16; i++)
        *(a + i) = *(a + i) ^ c[i];
    for (int j = 1; j < n; j++)
    {

        for (int i = 0; i < 16; i++)
        {
            c[i] = c[16 + i];
            c[16 + i] = a[i + 16 * j];
        }
        decrypt8(k, a + 16 * j);

        for (int i = 0; i < 16; i++)
            *(a + (16 * j + i)) = *(a + (16 * j + i)) ^ c[i];
    }
}
// end 운용모드(cbc mode)

// 운용모드(ofb mode)
void encrypt8_ofb(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n)
{
    uint8_t t[16] = {
        0,
    };

    for (int j = 0; j < 16; j++)
        t[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        // printf("Input  ");
        // show8(t);
        encrypt8(k, t);
        // printf("Output ");
        // show8(t);
        // printf("plain  ");
        // show8(a);
        for (int i = 0; i < 16; i++)
            *(a + (16 * j + i)) = *(a + (16 * j + i)) ^ t[i];
        // printf("cipher ");
        // show8(a);
    }
}

// end 운용모드(ofb mode)

// 운용모드(cfb mode)
void encrypt8_cfb(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n)
{
    uint8_t c[16] = {
        0,
    };

    for (int j = 0; j < 16; j++)
        c[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        // printf("Input  ");
        // show8(c);
        encrypt8(k, c);
        // printf("Output ");
        // show8(c);

        for (int i = 0; i < 16; i++)
            *(a + (16 * j + i)) = *(a + (16 * j + i)) ^ c[i];
        for (int i = 0; i < 16; i++)
            c[i] = *(a + (16 * j + i));
        // printf("Result ");

        // show8(c);
    }
}

// end 운용모드(cfb mode)

void decrypt8_cfb(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n)
{
    uint8_t c[32] = {
        0,
    };

    for (int j = 0; j < 16; j++)
        c[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < 16; i++)
            c[16 + i] = *(a + (16 * j + i));
        // printf("Input  ");
        // show8(c);
        encrypt8(k, c);
        // printf("Output ");
        // show8(c);

        // printf("Cipher ");
        // show8(a + (16 * j));

        for (int i = 0; i < 16; i++)
            *(a + (16 * j + i)) = *(a + (16 * j + i)) ^ c[i];

        for (int i = 0; i < 16; i++)
            c[i] = c[16 + i];
        // printf("Plian  ");
        // // show8(c);
    }
}

void CTR(uint8_t *t)
{
    t[15] = t[15] + 1;

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

// 운용모드(ctr mode)
void encrypt8_ctr(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n)
{
    uint8_t ctr[16] = {
        0,
    };

    uint8_t t[16] = {
        0,
    };

    for (int j = 0; j < 16; j++)
        ctr[j] = IV[j];

    for (int j = 0; j < 16; j++)
        t[j] = IV[j];

    for (int j = 0; j < n; j++)
    {
        // printf("Input  ");
        // show8(ctr);

        for (int j = 0; j < 16; j++)
            ctr[j] = t[j];

        encrypt8(k, ctr);

        // printf("Output ");
        // show8(ctr);

        // printf("Plain  ");
        // show8(a + (16 * j));

        for (int i = 0; i < 16; i++)
            *(a + (16 * j + i)) = *(a + (16 * j + i)) ^ ctr[i];
        // printf("Cipher ");
        // show8(a + (16 * j));

        CTR(t);
    }
}

// end 운용모드(ctr mode)