#ifndef SOREING_DES_H
#define SOREING_DES_H

// Encrypts 8 bytes of plaintext with a set of 16 round keys
void DES_Encrypt(const char data[8], const char roundKeys[16][8], char result[8]);

// Deecrypts 8 bytes of ciphertext with a set of 16 round keys
void DES_Decrypt(const char data[8], const char roundKeys[16][8], char result[8]);

// Creates 16 round keys from an input of a 64bit key
void DES_CreateKeys(const char key[8], char roundKeys[16][8]);

#endif