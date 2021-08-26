#ifdef __MODE8_H__
#define __MODE8_H__

#include <stdlib.h>
#include "aes8.h"

void encrypt8_ecb(uint8_t *k, uint8_t *a, uint64_t n);
void decrypt8_ecb(uint8_t *k, uint8_t *a, uint64_t n);

void encrypt8_cbc(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n);
void decrypt8_cbc(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n);

void encrypt8_ofb(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n);

void encrypt8_cfb(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n);
void decrypt8_cfb(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n);

void encrypt8_ctr(uint8_t *k, uint8_t *IV, uint8_t *a, uint8_t n);

#endif /* __MODE8_H__ */