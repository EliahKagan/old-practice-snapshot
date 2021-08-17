#!/usr/bin/env python3

END_MARK = None  # any singleton could be used for this
FALLBACK = '0'   # text to print when there are no matches

for _ in range(int(input())):
    input()  # don't need n

    # Build the trie.
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

        cur[END_MARK] = word

    # Define a generator to enumerate all words under a root.
    def dfs(node):
        try:
            yield node[END_MARK]
        except KeyError:
            pass

        for ch in sorted(key for key in node if key is not END_MARK):
            yield from dfs(node[ch])

    # Look up the specified word, (re)enumerating all words at each step.
    for ch in input().strip():
        try:
            trie = trie[ch]
        except TypeError:   # the trie has already been discarded
            print(FALLBACK)
        except KeyError:    # the trie does not contain this prefix
            trie = None
            print(FALLBACK)
        else:
            print(' '.join(dfs(trie)))
