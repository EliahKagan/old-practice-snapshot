import contextlib

WORD_MARK = None

def build_trie(words):
    trie = {}

    for word in words:
        node = trie

        for ch in word:
            try:
                node = node[ch]
            except KeyError:
                child = {}
                node[ch] = child
                node = child

        node[WORD_MARK] = None

    return trie

def known_prefix_or_full_word(trie, word):
    with contextlib.suppress(KeyError):
        for i, ch in enumerate(word):
            trie = trie[ch]
            if WORD_MARK in trie:
                return word[:(i + 1)]

    return word

class Solution:
    def replaceWords(self, roots, sentence):
        """
        :type dic: List[str]
        :type sentence: str
        :rtype: str
        """
        trie = build_trie(roots)
        in_words = sentence.split()
        out_words = (known_prefix_or_full_word(trie, word)
                     for word in in_words)
        return ' '.join(out_words)
