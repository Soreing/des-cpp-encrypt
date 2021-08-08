# des-cpp-encrypt

# Description

des-cpp-encrypt is a simple C++ library for generating DES keys and encrypting or decrypting data. Encryption is only implemented for 1 block of data. If you want to encrypt more than 8 bytes, you will need to implement different modes of operation, like des-ecb.

# Installation
Include `DES.h` in your project for defining the functions. If you want to compile the library from source, include the cpp file  `DES.cpp` for the implementation. Alternatively, you can compile the source code to a static library and include it that way.

# Usage

## Creating Keys
To create round keys, you need a character array of 8 bytes. The `DES_CreateKeys` function will create 16 round keys based on your input key, which is stored as a `[16][8]` 2D character array.
```c++
char key[8] = {0xAA,0xBB,0x09,0x18,0x27,0x36,0xCC,0xDD};
char roundKeys[16][8];

DES_CreateKeys(key, roundKeys);

```

## Encryption
After you generated the round keys, you can encrypt some data. You need to provide this data in the form of a character array of 8 bytes. The result is stored in an 8 byte large buffer you also need to provide.
**The buffer MUST be initialized to 0**
```c++
char plainText[8]  = {'T','e','s','t','D','a','t','a'};
char cipherText[8] = {0,0,0,0,0,0,0,0};

DES_Encrypt(plainText, roundKeys, cipherText);
```

## Decryption
To Decrypt the ciphertext, you need to perform similar steps to encryption. You need to have the round keys, and you need to have an 8 byte ciphertext, and the result is stored in an 8 byte buffer.
**The buffer MUST be initialized to 0**
```c++
// 1 Extra character for the null terminator
char original[9] = {0,0,0,0,0,0,0,0,0};
DES_Decrypt(cipherText, roundKeys, original);
```
