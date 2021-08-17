from collections import Counter

WIDTH = 10

class Solution:
    def findRepeatedDnaSequences(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        freqs = Counter(s[i:(i + WIDTH)] for i in range(0, len(s) - WIDTH + 1))
        return [key for key, value in freqs.items() if value > 1]
