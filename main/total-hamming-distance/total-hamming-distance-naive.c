int totalHammingDistance(int *const nums, const int numsSize) {
    if (numsSize == 0) return 0;

    int acc = 0;

    const int istop = numsSize - 1;
    for (int i = 0; i != istop; ++i) {
        for (int j = i + 1; j != numsSize; ++j)
            acc += __builtin_popcount(nums[i] ^ nums[j]);
    }

    return acc;
}
