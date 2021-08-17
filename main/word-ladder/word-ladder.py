NO_PATH = 0

class Solution:
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        try:
            end = wordList.index(endWord)
        except ValueError:
            return NO_PATH

        wordList.append(beginWord)
        adj = Solution._makeGraph(wordList)
        del wordList[-1]

        hops = Solution._minHops(adj, -1, end)
        return NO_PATH if hops is None else hops + 1

    @staticmethod
    def _minHops(adj, cur, end):
        assert cur != end
        vis = [False] * len(adj)
        vis[cur] = True

        q = collections.deque((cur,))
        hops = 1

        while q:
            for _ in range(len(q)):
                cur = q.popleft()

                for nxt in adj[cur]:
                    if vis[nxt]:
                        continue
                    if nxt == end:
                        return hops
                    vis[nxt] = True
                    q.append(nxt)

            hops += 1

        return None

    @staticmethod
    def _makeGraph(words):
        count = len(words)
        adj = [[] for _ in range(count)]

        for i, s in enumerate(words):
            for j in range(i + 1, count):
                if Solution._haveEdge(s, words[j]):
                    adj[i].append(j)
                    adj[j].append(i)

        return adj

    @staticmethod
    def _haveEdge(s, t):
        diff = False

        for x, y in zip(s, t):
            if x != y:
                if diff:
                    return False
                diff = True

        return diff
