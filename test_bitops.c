#include "bitops.h"

int main() {
    unsigned int value = 15;

    printf("Initial value:\n");
    PrintBinary(value);
    PrintHex(value);

    value = SetBit(value, 0);
    printf("\nAfter setting bit 0:\n");
    PrintBinary(value);
    PrintHex(value);

    value = ClearBit(value, 1);
    printf("\nAfter clearing bit 1:\n");
    PrintBinary(value);
    PrintHex(value);

    value = ToggleBit(value, 2);
    printf("\nAfter toggling bit 2:\n");
    PrintBinary(value);
    PrintHex(value);

    int bitValue = GetBit(value, 3);
    printf("\nValue of bit 3: %d\n", bitValue);

    int count = CountBits(value);
    printf("Number of set bits: %d\n", count);

    int firstSet = FindFirstSetBit(value);
    printf("First set bit position: %d\n", firstSet);

    int lastSet = FindLastSetBit(value);
    printf("Last set bit position: %d\n", lastSet);

    value = ShiftLeft(value, 2);
    printf("\nAfter shifting left by 2:\n");
    PrintBinary(value);
    PrintHex(value);

    value = ShiftRight(value, 1);
    printf("\nAfter shifting right by 1:\n");
    PrintBinary(value);
    PrintHex(value);

    return 0;
}