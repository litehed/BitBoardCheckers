#include "bitops.h"

unsigned int SetBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return value;
    return value | (1 << position);
}

// Alternative : Helper function approach
unsigned int Mask(int position) { return 1 << position; }

unsigned int ModifyBit(unsigned int value, int position, int operation) {
    // operation : 0= clear , 1= set , 2= toggle
    switch (operation) {
        case 0:
            return value & ~Mask(position);
        case 1:
            return value | Mask(position);
        case 2:
            return value ^ Mask(position);
    }
    return value;
}

unsigned int ClearBit(unsigned int value, int position) {
    return ModifyBit(value, position, 0);
}

unsigned int ToggleBit(unsigned int value, int position) {
    return ModifyBit(value, position, 2);
}
int GetBit(unsigned int value, int position) {
    if (position < 0 || position >= 32) return 0;
    return (value >> position) & 1;
}

// Counting and Finding

int CountBits(unsigned int value) {
    int count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

int FindFirstSetBit(unsigned int value) {
    if (value == 0) return -1;
    int position = 0;
    while ((value & 1) == 0) {
        value >>= 1;
        position++;
    }
    return position;
}

int FindLastSetBit(unsigned int value) {
    if (value == 0) return -1;
    int position = 31;
    while (((value >> position) & 1) == 0) {
        position--;
    }
    return position;
}

// Shift Operations

unsigned int ShiftLeft(unsigned int value, int positions) {
    if (positions < 0 || positions >= 32) return value;
    return value << positions;
}

unsigned int ShiftRight(unsigned int value, int positions) {
    if (positions < 0 || positions >= 32) return value;
    return value >> positions;
}

// Display Functions

void PrintBinary(unsigned int value) {
    for (int i = 31; i >= 0; i--) {
        printf("%d ", (value >> i) & 1);
    }
    printf("\n");
}

void PrintHex(unsigned int value) { printf("0x%X\n", value); }

// LongLong Operations
unsigned long long SetBitLL(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value | (1ULL << position);
}

unsigned long long ClearBitLL(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value & ~(1ULL << position);
}

unsigned long long GetBitLL(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return 0;
    return (value >> position) & 1ULL;
}