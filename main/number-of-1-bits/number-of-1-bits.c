int hammingWeight(uint32_t n) {
    _Static_assert(sizeof(unsigned) == sizeof(uint32_t)
                   && UINT_MAX == UINT32_MAX,
                   "uint32_t may not be compatible with unsigned int");

    return __builtin_popcount(n);
}
