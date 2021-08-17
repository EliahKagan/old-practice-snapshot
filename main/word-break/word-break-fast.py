END_MARK = None

class Solution:
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
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

        # create the initial table
        slen = len(s)
        table = [False] * slen
        table.append(True)

        # attempt to build a chain of words
        for i in range(slen - 1, -1, -1):
            try:
                node = trie
                for j in range(i, slen):
                    node = node[s[j]]
                    if table[j + 1] and END_MARK in node:
                        table[i] = True
                        break
            except KeyError:
                pass

        return table[0]
