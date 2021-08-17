class Solution:
    def rotateString(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: bool
        """
        return len(a) == len(b) and a in b * 2
