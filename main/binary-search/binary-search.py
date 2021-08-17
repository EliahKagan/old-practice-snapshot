#!/usr/bin/env python3

def binary_search(words, low, high, key):
    if high < low:
        return -1

    mid = (low + high) // 2 # the // operation does integer division

    if words[mid] < key:
        return binary_search(words, mid + 1, high, key) # check right of mid
    elif words[mid] > key:
        return binary_search(words, low, mid - 1, key) # check left of mid
    else:
        return mid # we found the word at mid

words = input('Please enter some words to populate the dictionary.\n').split()

words.sort() # binary search only works on *sorted* arrays
print(f'\nSorted, that list looks like:\n{" ".join(words)}\n')

keys = input('What words do you want to find in the sorted list?\n').split()
print()

for key in keys:
    print(f'{key}: {binary_search(words, 0, len(words) - 1, key)}')
