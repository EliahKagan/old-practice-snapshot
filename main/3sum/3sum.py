class Solution:
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        compl_idxs = {}
        for i, e in enumerate(nums):
            try:
                compl_idxs[-e].append(i)
            except KeyError:
                compl_idxs[-e] = [i]

        results = set()

        n = len(nums)
        for j in range(n - 1):
            for k in range(j + 1, n):
                try:
                    for i in compl_idxs[nums[j] + nums[k]]:
                        if i != j and i != k:
                            triple = [nums[i], nums[j], nums[k]]
                            triple.sort()
                            results.add(tuple(triple))
                            break
                except KeyError:
                    pass

        return list(map(list, sorted(results)))
