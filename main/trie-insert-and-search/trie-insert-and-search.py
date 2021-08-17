#!/usr/bin/env python3

END_MARK = None  # could be any hashable object that is not a single character

def insert(trie, word):
    for ch in word:
        try:
            child = trie[ch]
        except KeyError:
            child = {}
            trie[ch] = child

        trie = child

    trie[END_MARK] = None

def search(trie, word):
    try:
        for ch in word:
            trie = trie[ch]

        return END_MARK in trie
    except KeyError:
        return False

for _ in range(int(input())):
    input()  # don't need n

    trie = {}
    for word in input().split():
        insert(trie, word)

    print(int(search(trie, input().strip())))
