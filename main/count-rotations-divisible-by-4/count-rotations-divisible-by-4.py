#!/usr/bin/env python3

def count_rotations_divisible_by_4(digits):
    assert len(digits) != 0
    
    if len(digits) == 1:
        return 1 if int(digits) % 4 == 0 else 0
    
    count = (1 if int(digits[-1] + digits[0]) % 4 == 0 else 0)
    
    for i in range(len(digits) - 1):
        if int(digits[i:(i + 2)]) % 4 == 0:
            count += 1
    
    return count

for t in range(int(input())):
    print(count_rotations_divisible_by_4(input().strip()))
