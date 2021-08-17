NO_PATH = 0

class Solution:
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        vis = [False] * len(wordList)
        q = collections.deque((beginWord,))
        length = 2

        while q:
            for _ in range(len(q)):
                s = q.popleft()

                for j, t in enumerate(wordList):
                    if vis[j] or not Solution._haveEdge(s, t):
                        continue
                    if t == endWord:
                        return length
                    q.append(t)
                    vis[j] = True

            length += 1

        return NO_PATH

    @staticmethod
    def _haveEdge(s, t):
        diff = False

        for x, y in zip(s, t):
            if x != y:
                if diff:
                    return False
                diff = True

        return diff
