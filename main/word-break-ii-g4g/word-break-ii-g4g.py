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

    # read the input string and create an initial adjacency list
    text = input().strip()
    length = len(text)
    adj = [[] for _ in range(length)]
    adj.append(True)

    # insert edges into the graph for words that might be part of a path
    for i in range(length - 1, -1, -1):
        try:
            node = trie
            for j in range(i, length):
                node = node[text[j]]
                if adj[j + 1] and END_MARK in node:
                    adj[i].append(j + 1)
        except KeyError:
            pass

    # create temporary and permanent storage for path representations
    path = []
    all_paths = []

    # define a function to enumerate the paths via backtracking
    def dfs(i):
        path.append(i)

        if i == length:
            words = (text[path[k - 1]:path[k]] for k in range(1, len(path)))
            all_paths.append(' '.join(words))
        else:
            for j in adj[i]:
                dfs(j)

        del path[-1]

    # enumerate, sort, parenthesize, join, and print the strings
    dfs(0)
    if all_paths:
        all_paths.sort()
        print('(' + ')('.join(all_paths) + ')')
    else:
        print('Empty')
