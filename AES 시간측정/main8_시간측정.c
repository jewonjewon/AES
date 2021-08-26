#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "aes8.h"
#include "mode8.h"

int main()
{
    // 파라미터
    uint8_t k[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

    uint8_t a[64] = {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
        0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
        0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
        0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10};

    uint8_t IV[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    uint8_t ctr[16] = {
        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff};

    uint32_t rk32[80] = {
        0,
    };
    uint8_t rk8[300] = {
        0,
    };
    // 파라미터
    // cnt: 전체 시행 횟수
    double cnt = 100000;
    // 1: 전체 시간, 2: 암호화 시간, 3: 복호화 시간, 4: 키생성 시간
    double start1, start2, start3, start4;
    double end1, end2, end3, end4;

    uint64_t blknum = sizeof(a) / 16;
    printf("block num: %llu\n", blknum);

    start1 = (double)clock() / CLOCKS_PER_SEC;

    start4 = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        keyExpansion(k, rk32, 16);
        wordToByte(rk32, rk8, 44);
    }
    end4 = (((double)clock()) / CLOCKS_PER_SEC);

    start2 = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
        // 운용모드 넣고싶은거 넣기 ex) encrypt8_ecb |or| encrypt8_cbc |or| encrypt8_ofb |or| encrypt8_cfb |or| encrypt8_ctr
        encrypt8_cbc(rk8, IV, a, blknum);
    end2 = (((double)clock()) / CLOCKS_PER_SEC);

    // print test
    show8(a, blknum);

    start3 = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
        // 운용모드 넣고싶은거 넣기 ex) decrypt8_ecb |or| decrypt8_cbc |or| encrypt8_ofb |or| decrypt8_cfb |or| encrypt8_ctr
        decrypt8_cbc(rk8, IV, a, blknum);

    end3 = (((double)clock()) / CLOCKS_PER_SEC);

    end1 = (((double)clock()) / CLOCKS_PER_SEC);

    // print test
    show8(a, blknum);

    printf("저언체 수행 시간 :%lf\n", (end1 - start1));
    printf("암호화 수행 시간 :%lf\n", (end2 - start2));
    printf("복호화 수행 시간 :%lf\n", (end3 - start3));
    printf("키생성 수행 시간 :%lf\n", (end4 - start4));
    return 0;
}