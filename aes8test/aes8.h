#include <stdint.h>

void rotWord(uint32_t *temp);
void subWord(uint32_t *temp);
void keyExpansion(uint8_t *key, uint32_t *rk, int Nk);

uint32_t x_time(uint32_t x);

void byteToWord(uint8_t *input, uint32_t *output, uint8_t bytenum);
void wordToByte(uint32_t *input, uint8_t *output, uint8_t wordnum);

void addRoundKey(uint8_t *state, uint8_t *roundkey, uint8_t round);
void subBytes(uint8_t *state);
void shiftRows(uint8_t *state);
void mixColumns(uint8_t *plaintext);

void encrypt8(uint8_t *roundkey, uint8_t *state);

void invShiftRows(uint8_t *state);
void invSubBytes(uint8_t *state);
void invMixColumns(uint8_t *plaintext);

void decryptAES(uint8_t *roundkey, uint8_t *state);

#pragma once
