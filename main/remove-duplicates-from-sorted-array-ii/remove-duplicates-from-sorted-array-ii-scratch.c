#include  <stdio.h>

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize < 3) return numsSize;

    int i = 2;
    for (int j = 2; j != numsSize; ++j) {
        printf("%d, %d, %d\n", nums[j - 2], nums[j - 1], nums[j]);
        // Using nums[j - 2] is an error, as it may have been overwritten.
        // Use nums[i - 2] != nums[j] instead.
        if (nums[j - 2] != nums[j]) nums[i++] = nums[j];
    }

    return i;
}

int main(void)
{
    int a[] = { 1, 1, 1, 2, 2, 3 };
    printf("%d\n", removeDuplicates(a, sizeof a / sizeof a[0]));
}
