#!/usr/bin/env python3

END_MARK = None  # any non-string would work here

for _ in range(int(input())):
    input()  # don't need n

    # Build the trie.
    trie = {}
    for phrase in input().split():
        cur = trie

        for initial in filter(str.isupper, phrase):
            try:
                cur = cur[initial]
            except KeyError:
                nxt = {}
                cur[initial] = nxt
                cur = nxt

        try:
            cur[END_MARK].append(phrase)
        except KeyError:
            cur[END_MARK] = [phrase]

    # Attempt to move down to the subtrie for the given initials.
    try:
        for initial in input().strip():
            trie = trie[initial]
    except KeyError:
        print('No match found')
        continue

    # Define a function to recursively extract all this subtrie's phrases.
    matches = []
    def dfs(node):
        try:
            matches.extend(node.pop(END_MARK))
        except KeyError:
            pass

        for ch in sorted(node):
            dfs(node[ch])

    # Extract and print the phrases.
    dfs(trie)
    assert matches
    print(' '.join(matches))
