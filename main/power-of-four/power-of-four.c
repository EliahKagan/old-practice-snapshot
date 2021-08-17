bool isPowerOfFour(const int num) {
    if (num <= 0) return false;

    const unsigned n = num;
    return __builtin_popcount(n) == 1 && __builtin_ctz(n) % 2 == 0;
}
