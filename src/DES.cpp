#include "DES.h"

// Bit Location structure
// Used to get 1 bit from 8 bytes
struct bloc
{	int byte;	// Byte number in an 8 byte structure
	int mask;	// Bit mask to get a bit from 1 byte
};

const bloc DES_IP_BOX[]
{	{ 7, 0x40 },{ 6, 0x40 },{ 5, 0x40 },{ 4, 0x40 },{ 3, 0x40 },{ 2, 0x40 },{ 1, 0x40 },{ 0, 0x40 },
	{ 7, 0x10 },{ 6, 0x10 },{ 5, 0x10 },{ 4, 0x10 },{ 3, 0x10 },{ 2, 0x10 },{ 1, 0x10 },{ 0, 0x10 },
	{ 7, 0x04 },{ 6, 0x04 },{ 5, 0x04 },{ 4, 0x04 },{ 3, 0x04 },{ 2, 0x04 },{ 1, 0x04 },{ 0, 0x04 },
	{ 7, 0x01 },{ 6, 0x01 },{ 5, 0x01 },{ 4, 0x01 },{ 3, 0x01 },{ 2, 0x01 },{ 1, 0x01 },{ 0, 0x01 },
	{ 7, 0x80 },{ 6, 0x80 },{ 5, 0x80 },{ 4, 0x80 },{ 3, 0x80 },{ 2, 0x80 },{ 1, 0x80 },{ 0, 0x80 },
	{ 7, 0x20 },{ 6, 0x20 },{ 5, 0x20 },{ 4, 0x20 },{ 3, 0x20 },{ 2, 0x20 },{ 1, 0x20 },{ 0, 0x20 },
	{ 7, 0x08 },{ 6, 0x08 },{ 5, 0x08 },{ 4, 0x08 },{ 3, 0x08 },{ 2, 0x08 },{ 1, 0x08 },{ 0, 0x08 },
	{ 7, 0x02 },{ 6, 0x02 },{ 5, 0x02 },{ 4, 0x02 },{ 3, 0x02 },{ 2, 0x02 },{ 1, 0x02 },{ 0, 0x02 }
};

const bloc DES_IIP_BOX[]
{	{ 4, 0x01 },{ 0, 0x01 },{ 5, 0x01 },{ 1, 0x01 },{ 6, 0x01 },{ 2, 0x01 },{ 7, 0x01 },{ 3, 0x01 },
	{ 4, 0x02 },{ 0, 0x02 },{ 5, 0x02 },{ 1, 0x02 },{ 6, 0x02 },{ 2, 0x02 },{ 7, 0x02 },{ 3, 0x02 },
	{ 4, 0x04 },{ 0, 0x04 },{ 5, 0x04 },{ 1, 0x04 },{ 6, 0x04 },{ 2, 0x04 },{ 7, 0x04 },{ 3, 0x04 },
	{ 4, 0x08 },{ 0, 0x08 },{ 5, 0x08 },{ 1, 0x08 },{ 6, 0x08 },{ 2, 0x08 },{ 7, 0x08 },{ 3, 0x08 },
	{ 4, 0x10 },{ 0, 0x10 },{ 5, 0x10 },{ 1, 0x10 },{ 6, 0x10 },{ 2, 0x10 },{ 7, 0x10 },{ 3, 0x10 },
	{ 4, 0x20 },{ 0, 0x20 },{ 5, 0x20 },{ 1, 0x20 },{ 6, 0x20 },{ 2, 0x20 },{ 7, 0x20 },{ 3, 0x20 },
	{ 4, 0x40 },{ 0, 0x40 },{ 5, 0x40 },{ 1, 0x40 },{ 6, 0x40 },{ 2, 0x40 },{ 7, 0x40 },{ 3, 0x40 },
	{ 4, 0x80 },{ 0, 0x80 },{ 5, 0x80 },{ 1, 0x80 },{ 6, 0x80 },{ 2, 0x80 },{ 7, 0x80 },{ 3, 0x80 }
};

const bloc DES_E_BOX[]
{	{ 3, 0x01 },  { 0, 0x80 },{ 0, 0x40 },{ 0, 0x20 },{ 0, 0x10 },  { 0, 0x08 },
	{ 0, 0x10 },  { 0, 0x08 },{ 0, 0x04 },{ 0, 0x02 },{ 0, 0x01 },  { 1, 0x80 },
	{ 0, 0x01 },  { 1, 0x80 },{ 1, 0x40 },{ 1, 0x20 },{ 1, 0x10 },  { 1, 0x08 },
	{ 1, 0x10 },  { 1, 0x08 },{ 1, 0x04 },{ 1, 0x02 },{ 1, 0x01 },  { 2, 0x80 },
	{ 1, 0x01 },  { 2, 0x80 },{ 2, 0x40 },{ 2, 0x20 },{ 2, 0x10 },  { 2, 0x08 },
	{ 2, 0x10 },  { 2, 0x08 },{ 2, 0x04 },{ 2, 0x02 },{ 2, 0x01 },  { 3, 0x80 },
	{ 2, 0x01 },  { 3, 0x80 },{ 3, 0x40 },{ 3, 0x20 },{ 3, 0x10 },  { 3, 0x08 },
	{ 3, 0x10 },  { 3, 0x08 },{ 3, 0x04 },{ 3, 0x02 },{ 3, 0x01 },  { 0, 0x80 }
};

const bloc DES_P_BOX[]
{	{ 1, 0x01 },{ 0, 0x02 },{ 2, 0x10 },{ 2, 0x08 },{ 3, 0x08 },{ 1, 0x10 },{ 3, 0x10 },{ 2, 0x80 },
	{ 0, 0x80 },{ 1, 0x02 },{ 2, 0x02 },{ 3, 0x40 },{ 0, 0x08 },{ 2, 0x40 },{ 3, 0x02 },{ 1, 0x40 },
	{ 0, 0x40 },{ 0, 0x01 },{ 2, 0x01 },{ 1, 0x04 },{ 3, 0x01 },{ 3, 0x20 },{ 0, 0x20 },{ 1, 0x80 },
	{ 2, 0x20 },{ 1, 0x08 },{ 3, 0x04 },{ 0, 0x04 },{ 2, 0x04 },{ 1, 0x20 },{ 0, 0x10 },{ 3, 0x80 }
};

const int DES_S1_BOX[64]
{	14, 0, 4, 15, 13, 7, 1, 4, 2, 14, 15, 2, 11, 13, 8, 1,
	3, 10, 10, 6, 6, 12, 12, 11, 5, 9, 9, 5, 0, 3, 7, 8,
	4, 15, 1, 12, 14, 8, 8, 2, 13, 4, 6, 9, 2, 1, 11, 7,
	15, 5, 12, 11, 9, 3, 7, 14, 3, 10, 10, 0, 5, 6, 0, 13
};

const int DES_S2_BOX[64]
{	15, 3, 1, 13, 8, 4, 14, 7, 6, 15, 11, 2, 3, 8, 4, 14,
	9, 12, 7, 0, 2, 1, 13, 10, 12, 6, 0, 9, 5, 11, 10, 5,
	0, 13, 14, 8, 7, 10, 11, 1, 10, 3, 4, 15, 13, 4, 1, 2,
	5, 11, 8, 6, 12, 7, 6, 12, 9, 0, 3, 5, 2, 14, 15, 9
};

const int DES_S3_BOX[64]
{	10, 13, 0, 7, 9, 0, 14, 9, 6, 3, 3, 4, 15, 6, 5, 10,
	1, 2, 13, 8, 12, 5, 7, 14, 11, 12, 4, 11, 2, 15, 8, 1,
	13, 1, 6, 10, 4, 13, 9, 0, 8, 6, 15, 9, 3, 8, 0, 7,
	11, 4, 1, 15, 2, 14, 12, 3, 5, 11, 10, 5, 14, 2, 7, 12
};

const int DES_S4_BOX[64]
{	7, 13, 13, 8, 14, 11, 3, 5, 0, 6, 6, 15, 9, 0, 10, 3,
	1, 4, 2, 7, 8, 2, 5, 12, 11, 1, 12, 10, 4, 14, 15, 9,
	10, 3, 6, 15, 9, 0, 0, 6, 12, 10, 11, 1, 7, 13, 13, 8,
	15, 9, 1, 4, 3, 5, 14, 11, 5, 12, 2, 7, 8, 2, 4, 14
};

const int DES_S5_BOX[64]
{	2, 14, 12, 11, 4, 2, 1, 12, 7, 4, 10, 7, 11, 13, 6, 1,
	8, 5, 5, 0, 3, 15, 15, 10, 13, 3, 0, 9, 14, 8, 9, 6,
	4, 11, 2, 8, 1, 12, 11, 7, 10, 1, 13, 14, 7, 2, 8, 13,
	15, 6, 9, 15, 12, 0, 5, 9, 6, 10, 3, 4, 0, 5, 14, 3,
};

const int DES_S6_BOX[64]
{	12, 10, 1, 15, 10, 4, 15, 2, 9, 7, 2, 12, 6, 9, 8, 5,
	0, 6, 13, 1, 3, 13, 4, 14, 14, 0, 7, 11, 5, 3, 11, 8,
	9, 4, 14, 3, 15, 2, 5, 12, 2, 9, 8, 5, 12, 15, 3, 10,
	7, 11, 0, 14, 4, 1, 10, 7, 1, 6, 13, 0, 11, 8, 6, 13,
};

const int DES_S7_BOX[64]
{	4, 13, 11, 0, 2, 11, 14, 7, 15, 4, 0, 9, 8, 1, 13, 10,
	3, 14, 12, 3, 9, 5, 7, 12, 5, 2, 10, 15, 6, 8, 1, 6,
	1, 6, 4, 11, 11, 13, 13, 8, 12, 1, 3, 4, 7, 10, 14, 7,
	10, 9, 15, 5, 6, 0, 8, 15, 0, 14, 5, 2, 9, 3, 2, 12
};

const int DES_S8_BOX[64]
{	13, 1, 2, 15, 8, 13, 4, 8, 6, 10, 15, 3, 11, 7, 1, 4,
	10, 12, 9, 5, 3, 6, 14, 11, 5, 0, 0, 14, 12, 9, 7, 2,
	7, 2, 11, 1, 4, 14, 1, 7, 9, 4, 12, 10, 14, 8, 2, 13,
	0, 15, 6, 12, 10, 9, 13, 0, 15, 3, 3, 5, 5, 6, 8, 11,
};

const bloc DES_PC1_BOX[]
{	{ 7, 0x80 },{ 6, 0x80 },{ 5, 0x80 },{ 4, 0x80 },{ 3, 0x80 },{ 2, 0x80 },{ 1, 0x80 },
	{ 0, 0x80 },{ 7, 0x40 },{ 6, 0x40 },{ 5, 0x40 },{ 4, 0x40 },{ 3, 0x40 },{ 2, 0x40 },
	{ 1, 0x40 },{ 0, 0x40 },{ 7, 0x20 },{ 6, 0x20 },{ 5, 0x20 },{ 4, 0x20 },{ 3, 0x20 },
	{ 2, 0x20 },{ 1, 0x20 },{ 0, 0x20 },{ 7, 0x10 },{ 6, 0x10 },{ 5, 0x10 },{ 4, 0x10 },
	{ 7, 0x02 },{ 6, 0x02 },{ 5, 0x02 },{ 4, 0x02 },{ 3, 0x02 },{ 2, 0x02 },{ 1, 0x02 },
	{ 0, 0x02 },{ 7, 0x04 },{ 6, 0x04 },{ 5, 0x04 },{ 4, 0x04 },{ 3, 0x04 },{ 2, 0x04 },
	{ 1, 0x04 },{ 0, 0x04 },{ 7, 0x08 },{ 6, 0x08 },{ 5, 0x08 },{ 4, 0x08 },{ 3, 0x08 },
	{ 2, 0x08 },{ 1, 0x08 },{ 0, 0x08 },{ 3, 0x10 },{ 2, 0x10 },{ 1, 0x10 },{ 0, 0x10 },
};

const bloc DES_PC2_BOX[]
{	{ 1, 0x04 },{ 2, 0x80 },{ 1, 0x20 },{ 2, 0x01 },{ 0, 0x80 },{ 0, 0x08 },{ 0, 0x20 },{ 3, 0x10 },
	{ 1, 0x02 },{ 0, 0x04 },{ 2, 0x08 },{ 1, 0x40 },{ 2, 0x02 },{ 2, 0x20 },{ 1, 0x10 },{ 0, 0x10 },
	{ 3, 0x40 },{ 0, 0x01 },{ 1, 0x01 },{ 0, 0x02 },{ 3, 0x20 },{ 2, 0x10 },{ 1, 0x08 },{ 0, 0x40 },
	{ 5, 0x80 },{ 6, 0x10 },{ 3, 0x02 },{ 4, 0x08 },{ 5, 0x02 },{ 6, 0x02 },{ 3, 0x04 },{ 4, 0x01 },
	{ 6, 0x20 },{ 5, 0x08 },{ 4, 0x80 },{ 5, 0x01 },{ 5, 0x10 },{ 6, 0x80 },{ 4, 0x02 },{ 6, 0x01 },
	{ 4, 0x40 },{ 6, 0x08 },{ 5, 0x04 },{ 5, 0x40 },{ 6, 0x40 },{ 4, 0x10 },{ 3, 0x08 },{ 3, 0x01 }

};

const int DES_SHIFT_BOX[]
{	1, 1, 2, 2, 2, 2, 2, 2, 
	1, 2, 2, 2, 2, 2, 2, 1
};

// Permutes the bits of a byte array with the help of a Bit Location array
// The function assumes that the result is initialized to 0, then if the input bits specified 
// by the Bit Location array were 1, it proceeds to set the value of the bits of every byte left to right 
// with the help of a shifting mask.
void permutation(const char input[], const bloc box[], const int size, char result[])
{
	for (int i = 0, j = 0; i < size; i++)
	{	for (int mask = 0x80; mask > 0; mask >>= 1, j++)
		{	if (input[box[j].byte] & box[j].mask)
			{	result[i] |= mask;
			}
		}
	}
}

// Shifts the intermediate DES key by some positions specified by count.
// The key is transformed into little endian notation in an intermediary space, then it is shifted
// to the left as a 64 bit variable. The result is manually adjusted on the 1st and 4th bytes 
// by masking and modifying bits to create a circular shift.
// The result is converted back into big endian.
void keyShift(char key[8], int count)
{
	char space[8];
	char mask = (count == 1 ? 0x10 : count == 2 ? 0x30 : 0x00);
	
	space[0] = key[6]; /**/ space[1] = key[5]; /**/ space[2] = key[4];
	space[4] = key[2]; /**/ space[5] = key[1]; /**/ space[6] = key[0];
	space[3] = key[3]; /**/ space[7] = 0;

	*(long long*)space <<= count;
	space[0] |= (space[3] & mask ) >> 4;
	space[3]  = (space[3] & ~mask) | (space[7] << 4);

	key[0] = space[6]; /**/ key[1] = space[5]; /**/ key[2] = space[4];
	key[4] = space[2]; /**/ key[5] = space[1]; /**/ key[6] = space[0];
	key[3] = space[3]; /**/ key[7] = 0;
}

// 1 round of the Feistel encryption
// The data is first permuted, then combined with the round key
// The data is passed through the substitution boxes and permuted again
void feistel(const char* input, const char* key, char* result)
{
	static const int* SBoxes[4][2] =
	{	{ (const int*)DES_S2_BOX, (const int*)DES_S1_BOX },
		{ (const int*)DES_S4_BOX, (const int*)DES_S3_BOX },
		{ (const int*)DES_S6_BOX, (const int*)DES_S5_BOX },
		{ (const int*)DES_S8_BOX, (const int*)DES_S7_BOX }
	};

	char data[8] = { 0,0,0,0,0,0,0,0 };
	char endi[8] = { 0,0,0,0,0,0,0,0 };
	char subs[4] = { 0,0,0,0 };
	
	permutation(input, DES_E_BOX, 6, data);

	*(long long*)(data) ^= *(long long*)(key);

	endi[0] = data[5]; /**/ endi[1] = data[4]; /**/ endi[2] = data[3];
	endi[3] = data[2]; /**/ endi[4] = data[1]; /**/ endi[5] = data[0];

	for (int i = 3; i >= 0; i--)
	{	subs[i] |= SBoxes[i][0][(*endi & 0x3F)];
		*(long long*)endi >>= 6;
		subs[i] |= SBoxes[i][1][(*endi & 0x3F)] << 4;
		*(long long*)endi >>= 6;
	}

	permutation(subs, DES_P_BOX, 4, result);
}

// Encrypts 8 bytes of plaintext with a set of 16 round keys
void DES_Encrypt(const char data[8], const char roundKeys[16][8], char result[8])
{
	long feistelResult   = 0;
	long long intermData = 0;

	long* leftHalf  = (long*)&intermData;
	long* rightHalf = (long*)&intermData + 1;

	permutation(data, DES_IP_BOX, 8, (char*)&intermData);

	for (int i = 0; i < 16; i++)
	{	feistel((char*)rightHalf, roundKeys[i], (char*)&feistelResult);
		intermData = *rightHalf & 0xFFFFFFFF | ((long long)((*leftHalf) ^ feistelResult) << 32);

		feistelResult = 0;
	}

	intermData = ((intermData & 0xFFFFFFFF00000000) >> 32) | ((intermData & 0x00000000FFFFFFFF) << 32);
	permutation((char*)&intermData, DES_IIP_BOX, 8, result);
}

// Deecrypts 8 bytes of ciphertext with a set of 16 round keys
void DES_Decrypt(const char data[8], const char roundKeys[16][8], char result[8])
{
	long feistelResult = 0;
	long long intermData = 0;

	long* leftHalf = (long*)&intermData;
	long* rightHalf = (long*)&intermData + 1;

	permutation(data, DES_IP_BOX, 8, (char*)&intermData);

	for (int i = 0; i < 16; i++)
	{
		feistel((char*)rightHalf, roundKeys[15-i], (char*)&feistelResult);
		intermData = *rightHalf & 0xFFFFFFFF | ((long long)((*leftHalf) ^ feistelResult) << 32);

		feistelResult = 0;
	}

	intermData = ((intermData & 0xFFFFFFFF00000000) >> 32) | ((intermData & 0x00000000FFFFFFFF) << 32);
	permutation((char*)&intermData, DES_IIP_BOX, 8, result);
}

// Creates 16 round keys from an input of a 64bit key
// The key is first permuted and parity bits are dropped to create 56 bits.
// The permuted key is shifted to the left in 2 halves of 24 bits by 1-2 bits specified
// by the DES shift table, then permuted again with dropped bits to create round keys of 48 bit length.
void DES_CreateKeys(const char key[8], char roundKeys[16][8])
{
	char volatileKey[8] = {0,0,0,0,0,0,0,0};
	
	for(int i=0; i<16; i++)
	{	for(int j=0; j<8; j++)
		{	roundKeys[i][j] = 0;
		}
	}

	permutation(key, DES_PC1_BOX, 7, volatileKey);

	for (int i = 0; i < 16; i++)
	{	keyShift(volatileKey, DES_SHIFT_BOX[i]);
		permutation(volatileKey, DES_PC2_BOX, 6, roundKeys[i]);
	}
}