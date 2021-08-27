#ifndef __MODE32_H__
#define __MODE32_H__

#include <stdlib.h>
#include "aes32.h"

void encrypt32_ecb(uint32_t *k, uint32_t *a, uint64_t n);
void decrypt32_ecb(uint32_t *k, uint32_t *a, uint64_t n);

void encrypt32_cbc(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n);
void decrypt32_cbc(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n);

void encrypt32_ofb(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n);

void encrypt32_cfb(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n);
void decrypt32_cfb(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n);

void CTR(uint32_t *t);
void encrypt32_ctr(uint32_t *k, uint32_t *IV, uint32_t *a, uint8_t n);

#endif /* __MODE32_H__ */
