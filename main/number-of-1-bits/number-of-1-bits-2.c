int hammingWeight(uint32_t n) {
    int count = 0;

    for (; n; n >>= 1)
        if (n & 1u) ++count;

    return count;
}
