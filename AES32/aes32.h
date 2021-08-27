// #pragma once
#ifndef __AES32_H__
#define __AES32_H__

#include <stdint.h>

void show32(uint32_t *state, const uint8_t blknum);

uint32_t x_time(uint32_t x);

void rotWord(uint32_t *tmp);
void subWord(uint32_t *tmp);

void keyExpansion(uint8_t *key, uint32_t *rk, int Nk);

void wordToByte(uint32_t *input, uint8_t *output, uint8_t wordnum);
void byteToWord(uint8_t *input, uint32_t *output, uint8_t bytenum);

void addRoundKey32(uint32_t *roundkey, uint32_t *state);
void subMix(uint32_t *state);

void encrypt32(uint32_t *rk32, uint32_t *state);

void invSubMix(uint32_t *state);
void invMixColumns(uint8_t *plaintext);

void deckeyset(uint32_t *rk32);

void decrypt32(uint32_t *rk32, uint32_t *state);

#endif /* __AES32_H__ */
