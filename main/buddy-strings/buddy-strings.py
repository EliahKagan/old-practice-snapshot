class Solution:
    def buddyStrings(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: bool
        """
        if len(a) != len(b) or len(a) < 2:
            return False
        
        mismatches = [i for i in range(len(a)) if a[i] != b[i]]
        
        if not mismatches:
            return len(set(a)) != len(a) # exchange identical characters
        
        if len(mismatches) != 2:
            return False
        
        i, j = mismatches
        return a[i] == b[j] and a[j] == b[i]
