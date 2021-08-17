int search(int *const nums, const int numsSize, const int target) {
    enum { not_found = -1 };

    if (numsSize == 0) return not_found;
    if (*nums == target) return 0;

    *nums = target;
    const int *q = nums + numsSize;
    while (*--q != target) { }

    ptrdiff_t i = q - nums;
    return i == 0 ? not_found : (int)i;
}
