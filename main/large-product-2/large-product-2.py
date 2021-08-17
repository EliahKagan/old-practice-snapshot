#!/usr/bin/env python3

# The task is to find the ceiling of the geometric mean of all n elements of a.
# Call the exact answer geo_mean and big pi (accumulate-and-multiply) mul.
# Then geo_mean**n == mul(a), so n*log(geo_mean) == sum(map(log, a)), so
# geo_mean == exp(sum(map(log, a)) / n).

import math

for _ in range(int(input())):
    n = int(input())
    a = list(map(float, input().split()))
    assert len(a) == n

    geo_mean = math.exp(sum(map(math.log, a)) / n)
    print(math.ceil(geo_mean))
