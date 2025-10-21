#include <stdio.h>

// Basic bit operations - implement these or equivalent functions
unsigned int SetBit(unsigned int value, int position);     // Set bit to 1
unsigned int ClearBit(unsigned int value, int position);   // Set bit to 0
unsigned int ToggleBit(unsigned int value, int position);  // Flip bit
int GetBit(unsigned int value, int position);              // Get bit value

// Counting and finding
int CountBits(unsigned int value);        // Count 1 s
int FindFirstSetBit(unsigned int value);  // Find first set bit
int FindLastSetBit(unsigned int value);   // Find last set bit

// Shift operations
unsigned int ShiftLeft(unsigned int value, int positions);
unsigned int ShiftRight(unsigned int value, int positions);

// Display functions
void PrintBinary(unsigned int value);  // Show in binary
void PrintHex(unsigned int value);     // Show in hex

// LongLong Operations
unsigned long long SetBitLL(unsigned long long value, int position);     // Set bit to 1
unsigned long long ClearBitLL(unsigned long long value, int position);   // Set bit to 0
unsigned long long GetBitLL(unsigned long long value, int position);     // Get bit value
int CountBitsLL(unsigned long long value);