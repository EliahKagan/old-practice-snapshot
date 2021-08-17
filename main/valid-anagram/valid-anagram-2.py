from collections import Counter

class Solution:
    def isAnagram(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        counts = Counter()
        for ch in s:
            counts[ch] += 1
        for ch in t:
            counts[ch] -= 1

        return all(c == 0 for c in counts.values())