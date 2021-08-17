class Solution:
    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """
        indices = {} # indexes into groups
        groups = []

        for word in strs:
            key = ''.join(sorted(word))
            try:
                groups[indices[key]].append(word)
            except KeyError:
                indices[key] = len(groups)
                groups.append([word])

        return groups
