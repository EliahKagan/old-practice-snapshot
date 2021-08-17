class WordDictionary:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._children = {}
        self._terminal = False

    def addWord(self, word):
        """
        Adds a word into the data structure.
        :type word: str
        :rtype: void
        """
        cur = self

        for ch in word:
            try:
                cur = cur._children[ch]
            except KeyError:
                nxt = cur._children[ch] = WordDictionary()
                cur = nxt

        cur._terminal = True

    def search(self, word):
        """
        Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
        :type word: str
        :rtype: bool
        """
        q = collections.deque()
        q.append(self)

        for ch in word:
            if ch == '.':
                for _ in range(len(q)):
                    q.extend(q.popleft()._children.values())
            else:
                for _ in range(len(q)):
                    try:
                        q.append(q.popleft()._children[ch])
                    except KeyError:
                        pass
            if not q:
                return False # a simple optimization

        return any(node._terminal for node in q)

# Your WordDictionary object will be instantiated and called as such:
# obj = WordDictionary()
# obj.addWord(word)
# param_2 = obj.search(word)
