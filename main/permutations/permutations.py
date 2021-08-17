def generate_permutations(nums):
    if not nums:
        yield []
        return

    for i, x in enumerate(nums):
        for tail in generate_permutations(nums[:i] + nums[(i + 1):]):
            yield [x, *tail]

class Solution:
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        return list(generate_permutations(nums))
