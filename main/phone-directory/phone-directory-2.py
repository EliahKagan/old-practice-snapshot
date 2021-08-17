#!/usr/bin/env python3

FALLBACK = '0'  # text to print when there are no matches

for _ in range(int(input())):
    input()  # don't need n
    words = sorted(frozenset(input().split()))
    pattern = input().strip()

    left = 0
    right = len(words)

    for prefix in (pattern[:length] for length in range(1, len(pattern) + 1)):
        while left != right and not words[left].startswith(prefix):
            left += 1

        if left == right:
            print(FALLBACK)
            continue

        right = left + 1
        try:
            while words[right].startswith(prefix):
                right += 1
        except IndexError:
            pass

        print(' '.join(words[i] for i in range(left, right)))
