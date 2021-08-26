// #pragma once
#ifndef __AES8_H__
#define __AES8_H__

#include <stdio.h>
#include <stdint.h>

void show8(uint8_t *state, const uint8_t blknum);

void rotWord(uint32_t *temp);
void subWord(uint32_t *temp);

// keyExpansion(master key, round key, Nk:16 or 24 or 32)
void keyExpansion(uint8_t *key, uint32_t *rk, int Nk);
void wordToByte(uint32_t *input, uint8_t *output, uint8_t wordnum);

// 8비트 말고 32비트로 처리 시 백만번 수행 기준 0.4초 더 빠름
uint32_t x_time(uint32_t x);

void addRoundKey(uint8_t *state, uint8_t *roundkey, uint8_t round);
void subBytes(uint8_t *state);
void shiftRows(uint8_t *state);
void mixColumns(uint8_t *plaintext);

void encrypt8(uint8_t *rk8, uint8_t *a);

void invShiftRows(uint8_t *ciphertext);
void invSubBytes(uint8_t ciphertext[]);
void invMixColumns(uint8_t *plaintext);

void decrypt8(uint8_t *rk8, uint8_t *a);

#endif /* __AES8_H__ */
