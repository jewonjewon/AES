#include <stdio.h>
#include <stdlib.h>

// pkcs7 padding
void pkcs7(uint8_t* msg, uint8_t* pad_msg, uint64_t pad_num) {
    uint64_t pad = 0;
    //printf("pad num = %d\n", pad_num);
    pad = 16 - (pad_num % 16);

    if (pad == 16) {
        for (int j = 0; j < 16; j++)
            pad_msg[j] = pad;	
    }

    else {
        for (int j = 0; j < (16 - pad) % 16; j++)
            pad_msg[j] = msg[16 * (pad_num / 16) + j];

        for (int j = (16 - pad) % 16; j < 16; j++)
            pad_msg[j] = pad;
    }
}

int main(){

    // 파라미터
    uint8_t a[16] = { 0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0};
    uint8_t k[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t t[100] = {0x0, };

    // 파라미터

    pkcs7(a, t, 14);
    printf("ciphertext \n");
        for(int j = 0;j<16;j++)
        printf("%02x", t[j]);
    printf("\n");
    
    return 0;


}