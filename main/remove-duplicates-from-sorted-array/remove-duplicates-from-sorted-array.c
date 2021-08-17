int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int i = 1;
    for (int j = 1; j != numsSize; ++j)
        if (nums[j - 1] != nums[j]) nums[i++] = nums[j];

    return i;
}
