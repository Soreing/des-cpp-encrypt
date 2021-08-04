#include "DES.h"
#include <iostream>

const char* HexaDigits = "0123456789abcdef";

void main()
{
	// Input values to the encryption
	char key[8] = { 0xAA, 0xBB, 0x09, 0x18, 0x27, 0x36, 0xCC, 0xDD };
	char plainText[8] = { 'T', 'e', 's', 't', 'D', 'a', 't', 'a' };

	// Round Keys for DES Encryption and Decryption
	char roundKeys[16][8];
	// Ciphertext returned after encryption, MUST be initialized to 0s
	char cipherText[8] = { 0 };
	// Plaintext from decrypting the ciphertext, MUST be initialized to 0s
	char original[9] = { 0 };

	DES_CreateKeys(key, roundKeys);
	DES_Encrypt(plainText, roundKeys, cipherText);

	for (int i = 0; i < 8; i++)
	{	std::cout << HexaDigits[((cipherText[i] & 0xF0) >> 4)];
		std::cout << HexaDigits[(cipherText[i] & 0x0F)] << " ";
	}

	DES_Decrypt(cipherText, roundKeys, original);
	std::cout << std::endl << original << std::endl;
}
