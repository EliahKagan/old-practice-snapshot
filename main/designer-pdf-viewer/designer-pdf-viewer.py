#!/usr/bin/env python3

import string

table = dict(zip(string.ascii_lowercase, map(int, input().split())))
word = input().strip()
height = max(table[letter] for letter in word)
print(height * len(word))
