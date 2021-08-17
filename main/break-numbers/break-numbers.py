#!/usr/bin/env python3

def read_val():
    return int(input())

def count_three_addend_decompositions(n):
    # https://www.wolframalpha.com/input/?i=sum_k%3D0%5En+(n+-+k+%2B+1)
    return (n + 1) * (n + 2) // 2

for _ in range(read_val()):
    print(count_three_addend_decompositions(read_val()))
