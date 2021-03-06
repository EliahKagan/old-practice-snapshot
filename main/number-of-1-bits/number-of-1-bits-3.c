int hammingWeight(uint32_t n) {
    int count = 0;
    for (; n; n >>= 1) count += (n & 1u);
    return count;
}
