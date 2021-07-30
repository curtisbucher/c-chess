#include "tools.h"

const int num_ones[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

int pop_cnt(bitboard n)
{
    // Counts the number of '1' bits in the given integer.
    return num_ones[n & 0xFF] +
           num_ones[n >> 8 & 0xFF] +
           num_ones[n >> 16 & 0xFF] +
           num_ones[n >> 24 & 0xFF] +
           num_ones[n >> 32 & 0xFF] +
           num_ones[n >> 40 & 0xFF] +
           num_ones[n >> 48 & 0xFF] +
           num_ones[n >> 56 & 0xFF];
}

int lowest_bit(bitboard n)
{
    // Returns the lowest bit in the given integer.
    return n & -n;
}

int highest_bit(bitboard n)
{
    // Returns the highest bit in the given integer.
    return (pop_cnt(n) - 1) ? n & (n - 1) : n;
}

int get_index(bitboard n)
{
    // TODO: Create a type that is a bitboard with only one bit set.
    // Returns the number of the square indicated. ie) A1 = 0, B1 = 1, ..., H8 = 63.
    return pop_cnt(n - 1);
}

bitboard gen_shift(bitboard n, int s)
{
    // Generates a bitboard with the given bit shifted by s (pos or neg shift).
    return (s > 0) ? (n << s) : (n >> -s);
}

double timeit(void (*f)(), int n)
{
    // Time the given function and return the result.
    // The function is called n times.
    double t = 0;
    for (int i = 0; i < n; i++)
    {
        clock_t start = clock();
        f();
        clock_t end = clock();
        t += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    }
    return t / n;
}
