int singleNumber(int* nums, int numsSize) {
    // Counting the bits in each position yields a multiple of 3 for each bit
    // not set in the unique value, and 1 greater than a multiple of 3 for
    // those that are. Bitwise addition modulo 3 requires two accumulators: a
    // sum (low-order, 1's place) bitfield and a carry (high-order, 2's place)
    // bitfield. I choose always to represent zero as 00, never as 11, which
    // gives this partial truth table:
    //
    //     old carry  old sum  element  |  new carry  new sum
    //         0         0        0     |      0         0
    //         0         0        1     |      0         1
    //         0         1        0     |      0         1
    //         0         1        1     |      1         0
    //         1         0        0     |      1         0
    //         1         0        1     |      0         0
    //         1         1        0     |  undefined  undefined
    //         1         1        1     |  undefined  undefined
    //
    // Multiple truth functions satisfy those constraints. I find these choices
    // intuitive (but I have not checked if they are the simplest or fastest):
    //
    //     new carry  :=  (old carry AND NOT elem) OR (old sum AND elem)
    //     new low    :=  NOT old carry AND (old sum XOR elem)
    assert(nums != NULL && numsSize > 0);

    int carry = 0, sum = 0;
    for (int i = 0; i != numsSize; ++i) {
        const int new_carry = (carry & ~nums[i]) | (sum & nums[i]);
        sum = ~carry & (sum ^ nums[i]);
        carry = new_carry;
    }

    assert(!carry); // nonzero final carry would mean unmet precondition or bug
    return sum;
}
