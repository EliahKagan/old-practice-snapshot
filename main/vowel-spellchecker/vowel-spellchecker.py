import contextlib

VOWEL = re.compile(r'[aeiou]')

def fold_vowels(word):
    return VOWEL.sub('a', word.casefold())

class Solution:
    def spellchecker(self, wordlist, queries):
        """
        :type wordlist: List[str]
        :type queries: List[str]
        :rtype: List[str]
        """
        exacts = frozenset(wordlist)
        casefolds = {word.casefold(): word for word in reversed(wordlist)}
        vowelfolds = {fold_vowels(word): word for word in reversed(wordlist)}

        def fix(query):
            if query in exacts:
                return query
            with contextlib.suppress(KeyError):
                return casefolds[query.casefold()]
            with contextlib.suppress(KeyError):
                return vowelfolds[fold_vowels(query)]
            return ''

        return list(map(fix, queries))
