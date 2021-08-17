class Trie:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._children = {}

    def __repr__(self):
        return 'Trie' + repr(self._children)

    def insert(self, word):
        """
        Inserts a word into the trie.
        :type word: str
        :rtype: void
        """
        cur = self
        for ch in itertools.chain(word, ('\0',)):
            try:
                cur = cur._children[ch]
            except KeyError:
                nxt = cur._children[ch] = Trie()
                cur = nxt

    def search(self, word):
        """
        Returns if the word is in the trie.
        :type word: str
        :rtype: bool
        """
        return self.startsWith(itertools.chain(word, ('\0',)))

    def startsWith(self, prefix):
        """
        Returns if there is any word in the trie that starts with the given prefix.
        :type prefix: str
        :rtype: bool
        """
        if not self._children:
            return False # so the empty trie doesn't have a "" prefix
        try:
            cur = self
            for ch in prefix:
                cur = cur._children[ch]
            return True
        except KeyError:
            return False

# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)
