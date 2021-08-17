END_MARK = None

def recursive_defaultdict():
    return collections.defaultdict(recursive_defaultdict)

class Solution:
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """
        # build the trie
        trie = recursive_defaultdict()
        for word in wordDict:
            node = trie
            for ch in word:
                node = node[ch]
            node[END_MARK] = END_MARK

        # create the initial table
        slen = len(s)
        table = [False] * slen
        table.append(True)

        # attempt to build a chain of words
        for i in range(slen - 1, -1, -1):
            node = trie
            for j in range(i, slen):
                node = node.get(s[j])
                if node is None:
                    break
                if table[j + 1] and END_MARK in node:
                    table[i] = True
                    break

        return table[0]