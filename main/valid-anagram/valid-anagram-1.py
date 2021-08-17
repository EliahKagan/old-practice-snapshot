class Solution:
    def isAnagram(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        return len(s) == len(t) and sorted(s) == sorted(t)
