END_MARK = None

class Solution:
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        # build the trie
        trie = {}
        for word in wordDict:
            cur = trie
            for ch in word:
                try:
                    cur = cur[ch]
                except KeyError:
                    nxt = {}
                    cur[ch] = nxt
                    cur = nxt
            cur[END_MARK] = END_MARK

        # create the initial adjacency list
        slen = len(s)
        adj = [[] for _ in range(slen)]
        adj.append(True)

        # insert edges into the graph for words that might be part of a path
        for i in range(slen - 1, -1, -1):
            try:
                node = trie
                for j in range(i, slen):
                    node = node[s[j]]
                    if adj[j + 1] and END_MARK in node:
                        adj[i].append(j + 1)
            except KeyError:
                pass

        # temporary and permanent storage for path representations
        path = []
        ret = []

        # define a function to enumerate all the paths via backtracking
        def dfs(i):
            path.append(i)

            if i == slen:
                words = (s[path[k - 1]:path[k]] for k in range(1, len(path)))
                ret.append(' '.join(words))
            else:
                for j in adj[i]:
                    dfs(j)

            del path[-1]

        # actually enumerate the paths, and return them as joined strings
        dfs(0)
        return ret
