class Solution:
    def replaceWords(self, roots, sentence):
        """
        :type roots: List[str]
        :type sentence: str
        :rtype: str
        """
        roots = frozenset(roots)

        def root_or_full_word(word):
            for i in range(1, len(word) + 1):
                prefix = word[:i]
                if prefix in roots:
                    return prefix

            return word

        return ' '.join(map(root_or_full_word, sentence.split()))
