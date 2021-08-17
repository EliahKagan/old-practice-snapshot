static inline int min(const int a, const int b) {
    return a < b ? a : b;
}

bool canJump(int *const nums, const int numsSize) {
    const int last = numsSize - 1;
    bool reach[numsSize];
    reach[0] = true;
    memset(reach + 1, 0, last * sizeof reach[1]);

    for (int i = 0; i != numsSize; ++i) {
        if (reach[i]) {
            for (int j = min(last, i + nums[i]); j != i; --j)
                reach[j] = true;
        }
    }

    return reach[last];
}
