#!/usr/bin/env python3

for _ in range(int(input())):
    n = int(input())
    # https://www.wolframalpha.com/input/?i=sum_k%3D(n(n-1)%2B1)%5E(n(n-1)%2B2n)+k
    print(n * (n * n * 2 + 1))
