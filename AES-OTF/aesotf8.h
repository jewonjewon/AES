// #pragma once
#ifndef __AES8_H__
#define __AES8_H__

#include <stdio.h>
#include <stdint.h>

void show8(uint8_t *state, const uint8_t blknum);

void wordToByte(uint32_t *input, uint8_t *output, uint8_t wordnum);
void byteToWord(uint8_t *input, uint32_t *output, uint8_t bytenum);

void rotWord(uint32_t *temp);
void subWord(uint32_t *temp);

void otfEncKeyGen(uint8_t *key, int n);
void otfDecKeyGen(uint8_t *key, int n);

// 8비트 말고 32비트로 처리 시 백만번 수행 기준 0.4초 더 빠름
uint32_t x_time(uint32_t x);

void addRoundKey(uint8_t *roundkey, uint8_t *state);
void subBytes(uint8_t *state);
void shiftRows(uint8_t *state);
void mixColumns(uint8_t *plaintext);

void encrypt8(uint8_t *rk8, uint8_t *a);

void invShiftRows(uint8_t *ciphertext);
void invSubBytes(uint8_t ciphertext[]);
void invMixColumns(uint8_t *plaintext);

void decrypt8(uint8_t *rk8, uint8_t *a);

#endif /* __AES8_H__ */
