#include <stdio.h>
#include <stdint.h>     //for int8_t
#include <string.h>     //for memcmp
#include <wmmintrin.h>  //for intrinsics for AES-NI



// function to encrypt 128 bit plaintext using aesenc instruction set and using the aes key generated
__m128i encriptBlockAesenc(__m128i stagingText,__m128i *k){ 
    
        //_mm_aesenc_si128 completes all the 4 steps that is ShiftRows, SubBytes, MixColumns & AddRoundKey into a single instruction except for the last round (10)
        // _mm_aesenclast_si128 only combines the ShiftRows, SubBytes, & AddRoundKey steps into one instruction.
        stagingText = _mm_xor_si128       (stagingText, k[ 0]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 1]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 2]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 3]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 4]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 5]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 6]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 7]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 8]); 
        stagingText = _mm_aesenc_si128    (stagingText, k[ 9]); 
        stagingText = _mm_aesenclast_si128(stagingText, k[10]);
    
    return stagingText;
 }   



static __m128i expanded_key[11];//the expanded key declaration

//key expansion involved 3 steps 1)left shift of 4 bytes of Wi-1 column 2)Replace using S-box 3) xor operation between Wi-4 column and Wi-1 column after the previous
// steps and rcon values
// source for the key expansion psuedo code : http://tab.snarc.org/posts/technical/2012-04-12-aes-intrinsics.html
static __m128i aesKey128BitExpansion(__m128i key, __m128i keygened){
	keygened = _mm_shuffle_epi32(keygened, _MM_SHUFFLE(3,3,3,3));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4)); //_mm_slli_si128 does left shift
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4)); // _mm_xor_si128 does xor operation
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	return _mm_xor_si128(key, keygened);
}








//function to generate the expanded key from the encrypted key given by the user
void generateKey(int8_t *enc_key){
    
    // k[0] is shared by first encryption round and last decryption round and is the original user key

    // k[10] is shared by last encryption and first decryption rounds
    // 0x01,0x02 to 0x36 are the rcon values with which the XOR operation happens at the end
    // _mm_aeskeygenassist_si128 -This instruction generates a round key for AES encryption

    expanded_key[0] = _mm_loadu_si128((const __m128i*) enc_key);
	expanded_key[1]  = aesKey128BitExpansion(expanded_key[0], _mm_aeskeygenassist_si128(expanded_key[0], 0x01));
	expanded_key[2]  = aesKey128BitExpansion(expanded_key[1], _mm_aeskeygenassist_si128(expanded_key[1], 0x02));
	expanded_key[3]  = aesKey128BitExpansion(expanded_key[2], _mm_aeskeygenassist_si128(expanded_key[2], 0x04));
	expanded_key[4]  = aesKey128BitExpansion(expanded_key[3], _mm_aeskeygenassist_si128(expanded_key[3], 0x08));
	expanded_key[5]  = aesKey128BitExpansion(expanded_key[4], _mm_aeskeygenassist_si128(expanded_key[4], 0x10));
	expanded_key[6]  = aesKey128BitExpansion(expanded_key[5], _mm_aeskeygenassist_si128(expanded_key[5], 0x20));
	expanded_key[7]  = aesKey128BitExpansion(expanded_key[6], _mm_aeskeygenassist_si128(expanded_key[6], 0x40));
	expanded_key[8]  = aesKey128BitExpansion(expanded_key[7], _mm_aeskeygenassist_si128(expanded_key[7], 0x80));
	expanded_key[9]  = aesKey128BitExpansion(expanded_key[8], _mm_aeskeygenassist_si128(expanded_key[8], 0x1B));
	expanded_key[10] = aesKey128BitExpansion(expanded_key[9], _mm_aeskeygenassist_si128(expanded_key[9], 0x36));

	
    

}

//This function take plain text as input and then calls encriptBlockAesenc function to generate the cipher using the expanded key
void encriptPlainText(int8_t *plainText,int8_t *cipherGenerated){
    __m128i m = _mm_loadu_si128((__m128i *) plainText);

    //The generated cipher is stored in the below reference using the _mm_storeu_si128 intsruction

    _mm_storeu_si128((__m128i *) cipherGenerated, encriptBlockAesenc(m,expanded_key));
}


//function to print the generated cipher text.
void printCipher(int8_t *cipherExpected,int8_t *cipherGenerated){

    printf("%s\n", "Expected cipher");
	for (int i = 0; i < 16; ++i)
	{
		printf("%#04x\t", cipherExpected[i]);
	}

	printf("\n");
    printf("%s\n","Generated Cipher" );

	for (int i = 0; i < 16; ++i)
	{
		printf("%#04x\t", cipherGenerated[i]);
	}

}



//Entry point for the AES_NI encryption code
int main(void)
{
    //text to be encrypted
    int8_t plainText[]      = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    //encryption key or user key to be used
    int8_t encryptedKey[]    = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    //expected cipher text
    int8_t cipherExpected[]     = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};
    //generated cipher text from the encyption
    int8_t cipherGenerated[16];

    //calling generate key function to expand 128 bit user or encryption key
    generateKey(encryptedKey);

    //calling encrypt function for the plainText provided
    encriptPlainText(plainText,cipherGenerated);
    printCipher(cipherExpected,cipherGenerated);

    return 0;
}