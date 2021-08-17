#!/usr/bin/env python3

END_MARK = None

for _ in range(int(input())):
    input() # don't need n

    # build the trie
    trie = {}
    for word in input().split():
        cur = trie
        for ch in word:
            try:
                cur = cur[ch]
            except KeyError:
                nxt = {}
                cur[ch] = nxt
                cur = nxt
        cur[END_MARK] = END_MARK

    # read the input string and create an initial table
    text = input().strip()
    length = len(text)
    table = [False] * length
    table.append(True)

    # attempt to build a chain of words
    for i in range(length - 1, -1, -1):
        try:
            node = trie
            for j in range(i, length):
                node = node[text[j]]
                if table[j + 1] and END_MARK in node:
                    table[i] = True
                    break
        except KeyError:
            pass

    # report if there is a chain all the way from the beginning to the end
    print(int(table[0]))
