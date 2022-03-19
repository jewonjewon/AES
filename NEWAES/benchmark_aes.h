#ifndef __BENCHMARK_AES_H__
#define __BENCHMARK_AES_H__

void time_measurement_shift_rows(void (*func)(byte *), byte *state, int cnt);
void time_measurement_mix_columns(void (*func)(byte *), byte *state, int cnt);

void inline_time_measurement_shift_rows(byte *state, int cnt);

void time_measurement_word_to_byte(void (*func)(byte *, word), word in, int cnt);
void time_measurement_byte_to_word(void (*func)(word *, byte *), byte *in, int cnt);

void time_measurement_aes_dec(void (*func)(byte *, byte *, byte *), byte *rk8, int cnt);
void time_measurement_aes_enc(void (*func)(byte *, byte *, byte *), byte *rk8, int cnt);

void time_measurement_key_expansion(void (*func)(word *, byte *), int cnt);

#endif